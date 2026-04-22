#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

#define SEEK_SET 0
#define SEEK_HOLE 3
#define BLOCK 1024

int main(int argc, char* argv[])
{
    int total_lseek_ops = 5000;
    char buf[BLOCK];
    memset(buf, 'A', BLOCK);

    // printf("Starting Linear Search benchmark...\n");
    // printf("Starting Cache Search benchmark...\n");

    for (int b = 1; b <= 20; b++)
    {
        unlink("bench_file");
        int fd = open("bench_file", O_CREATE | O_RDWR);
        for (int k = 0; k < b; k++)
        {
            write(fd, buf, BLOCK);
        }
        write(fd, "\0", 1);

        int start_tick = uptime();
        for (int i = 0; i < total_lseek_ops; i++)
        {
            lseek(fd, 0, SEEK_HOLE);
        }
        int end_tick = uptime();

        printf("%d %d\n", b, end_tick - start_tick);
        close(fd);
    }

    exit(0);
}
