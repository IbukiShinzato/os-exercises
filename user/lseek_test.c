#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    // lseek(int fildes, off_t offset, int whence);

    // 1: fd, 2: offset, 3: whence
    int fd = open("lseek_file", O_CREATE | O_RDWR);
    if (fd < 0)
    {
        fprintf(2, "Error: could not open lseek_file\n");
        exit(1);
    }

    write(fd, "ABCDE", 5);
    close(fd);

    fd = open("lseek_file", O_RDONLY);
    char buf1[5];
    read(fd, buf1, 5);
    printf("buf1: %s\n", buf1);
    close(fd);

    fd = open("lseek_file", O_RDONLY);
    lseek(fd, 1, 0);
    char buf2[1];
    read(fd, buf2, 1);
    if (buf2[0] == 'B')
    {
        printf("lseek SEEK_SET test passed!\n");
    }
    else
    {
        printf("lseek SEEK_SET test failed: expected C, got %c\n", buf2[0]);
    }

    // now offset is 2
    lseek(fd, 1, 1);
    read(fd, buf2, 1);
    if (buf2[0] == 'D')
    {
        printf("lseek SEEK_CUR test passed!\n");
    }
    else
    {
        printf("lseek SEEK_CUR test failed: expected C, got %c\n", buf2[0]);
    }

    close(fd);

    exit(0);
}
