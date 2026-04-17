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

    // ファイル内に普通に読み書きする
    write(fd, "ABCDE", 5);
    close(fd);

    fd = open("lseek_file", O_RDONLY);

    char buf[5];
    read(fd, buf, 5);

    printf("buf: %s\n", buf);

   // lseek(fd, 2, 0);

   // char buf[1];
   // read(fd, buf, 1);
   // if (buf[0] == 'C')
   // {
   //     // Success
   //     printf("lseek test passed!\n");
   // }
   // else
   // {
   //     // Failed
   //     printf("lseek test failed: expected C, got %c\n", buf[0]);
   // }

    close(fd);

    exit(0);
}
