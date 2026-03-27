#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

int main(int argc, char* argv[])
{
    int fd_src, fd_tgt;
    struct stat st_src, st_tgt;
    int n;

    if (argc != 3)
    {
        fprintf(2, "Usage: cp source_file target_file\n");
        exit(1);
    }

    if ((fd_src = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(2, "cp: cannot open %s\n", argv[1]);
        exit(1);
    }

    if (fstat(fd_src, &st_src) < 0)
    {
        fprintf(2, "cp: cannot stat %s\n", argv[1]);
        close(fd_src);
        exit(1);
    }

    if (st_src.type == T_DIR)
    {
        fprintf(2, "cp: %s is a directory (not supported)\n", argv[1]);
        close(fd_src);
        exit(1);
    }

    if (stat(argv[2], &st_tgt) == 0)
    {
        if (st_src.dev == st_tgt.dev && st_src.ino == st_tgt.ino)
        {
            fprintf(2, "cp: %s and %s are the same file.\n", argv[1], argv[2]);
            close(fd_src);
            exit(1);
        }
    }

    if ((fd_tgt = open(argv[2], O_CREATE | O_WRONLY | O_TRUNC)) < 0)
    {
        fprintf(2, "cp: cannot open %s\n", argv[2]);
        close(fd_src);
        exit(1);
    }

    while ((n = read(fd_src, buf, sizeof(buf))) > 0)
    {
        if (write(fd_tgt, buf, n) != n)
        {
            fprintf(2, "cp: write error\n");
            break;
        }
    }

    if (n < 0)
    {
        fprintf(2, "cp: read error\n");
    }

    close(fd_src);
    close(fd_tgt);

    exit(0);
}
