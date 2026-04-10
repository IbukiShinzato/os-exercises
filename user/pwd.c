#include "kernel/types.h"
#include "user/user.h"

#define MAX_PATH_LEN 512

int main(int argc, char* argv[])
{
    char path[MAX_PATH_LEN]; 
    
    if (get_cwd(path) == 0) {
        printf("%s\n", path);
    } else {
        fprintf(2, "pwd failed\n");
    }

    exit(0);
}
