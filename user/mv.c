#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"

char* fmtname(char* path)
{
    char* p;
    for (p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;
    return p;
}

int main(int argc, char* argv[])
{
    struct stat st_src, st_tgt;
    int i;
    char target_path[128];

    if (argc < 3)
    {
        fprintf(2, "Usage: mv source ... directory\n");
        exit(1);
    }

    char* dir_name = argv[argc - 1];

    if (stat(dir_name, &st_tgt) < 0)
    {
        fprintf(2, "mv: cannot stat directory %s\n", dir_name);
        exit(1);
    }
    if (st_tgt.type != T_DIR)
    {
        fprintf(2, "mv: %s is not a directory\n", dir_name);
        exit(1);
    }

    for (i = 1; i < argc - 1; i++)
    {
        char* src_path = argv[i];

        if (stat(src_path, &st_src) < 0)
        {
            fprintf(2, "mv: cannot stat %s\n", src_path);
            continue;
        }

        strcpy(target_path, dir_name);
        int n = strlen(target_path);
        if (n > 0 && target_path[n - 1] != '/')
        {
            target_path[n] = '/';
        }

        src_path = fmtname(src_path);
        for (int j = 0; j < strlen(src_path); j++)
        {
            target_path[n + j + 1] = src_path[j];
        }
        target_path[n + strlen(src_path) + 1] = '\0';

        if (link(src_path, target_path) < 0)
        {
            fprintf(2, "mv: failed to link %s to %s\n", src_path, target_path);
            continue;
        }

        if (unlink(src_path) < 0)
        {
            fprintf(2, "mv: failed to unlink %s\n", src_path);
        }
    }

    exit(0);
}
