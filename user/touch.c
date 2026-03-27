#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int fd, i;

    if (argc < 2)
    {
        fprintf(2, "Usage: touch file...\n");
        exit(1);
    }

    for (i = 1; i < argc; i++)
    {
        if ((fd = open((char*)argv[i], O_CREATE | O_RDONLY)) < 0)
        {
            fprintf(2, "touch: %s open error\n", argv[i]);
            exit(1);
        }
        close(fd);
    }

    exit(0);
}
