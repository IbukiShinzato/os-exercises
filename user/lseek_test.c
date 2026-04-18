#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_HOLE 3
#define SEEK_DATA 4

void test_failed(char *msg) {
    fprintf(2, "Test Failed: %s\n", msg);
    exit(1);
}

int main(int argc, char* argv[])
{
    int fd;
    char buf[1];

    printf("--- All lseek tests start! ---\n\n");

    // [A] (offset 0) --- (Hole: 1-999) --- [B] (offset 1000)
    fd = open("test_file", O_CREATE | O_RDWR);
    write(fd, "A", 1);

    char hole[999];
    memset(hole, 0, 999);        
    write(fd, hole, 999);

    write(fd, "B", 1);
    close(fd);

    fd = open("test_file", O_RDWR);

    // 1. SEEK_SET TEST 
    printf("Testing SEEK_SET...\n");
    if(lseek(fd, 1000, SEEK_SET) != 1000) test_failed("SEEK_SET to 1000");
    read(fd, buf, 1);
    if(buf[0] != 'B') test_failed("Read 'B' after SEEK_SET");
    
    if(lseek(fd, -1, SEEK_SET) != -1) test_failed("SEEK_SET negative (should fail)");

    // 2. SEEK_CUR TEST
    printf("Testing SEEK_CUR...\n");
    lseek(fd, 0, SEEK_SET); 
    lseek(fd, 1000, SEEK_CUR); 
    read(fd, buf, 1);
    if(buf[0] != 'B') test_failed("Read 'B' after SEEK_CUR positive");

    lseek(fd, 1001, SEEK_SET); 
    lseek(fd, -1, SEEK_CUR); 
    read(fd, buf, 1);
    if(buf[0] != 'B') test_failed("Read 'B' after SEEK_CUR negative");

    // 3. SEEK_END TEST 
    printf("Testing SEEK_END...\n");
    if(lseek(fd, 0, SEEK_END) != 1001) test_failed("SEEK_END 0");
    if(lseek(fd, -1, SEEK_END) != 1000) test_failed("SEEK_END -1");
    read(fd, buf, 1);
    if(buf[0] != 'B') test_failed("Read 'B' after SEEK_END -1");

    // 4. SEEK_HOLE TEST 
    printf("Testing SEEK_HOLE...\n");
    uint64 hole_pos = lseek(fd, 1, SEEK_HOLE);
    if(hole_pos < 1 || hole_pos >= 1000) test_failed("SEEK_HOLE not found in gap");
    
    if(lseek(fd, 1001, SEEK_HOLE) != 1001) test_failed("SEEK_HOLE at EOF");

    // 5. SEEK_DATA TEST
    printf("Testing SEEK_DATA...\n");
    uint64 data_pos = lseek(fd, 500, SEEK_DATA);
    if(data_pos != 1000) test_failed("SEEK_DATA failed to find 'B' at 1000");

    if(lseek(fd, 1002, SEEK_DATA) != -1) test_failed("SEEK_DATA after EOF (should fail)");

    printf("\n--- All lseek tests passed! ---\n");
    
    close(fd);
    exit(0);
}
