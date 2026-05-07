#include "kernel/types.h"
#include "user/user.h"

#define FORK_COUNT 1000
#define PGSIZE 4096
#define PAGE_COUNT 100

int main(int argc, char* argv[])
{
    for (int b = 1; b <= PAGE_COUNT; b++)
    {
        char *p = sbrk(b * PGSIZE);
        if(p == (char*)-1) break;

        for(int j = 0; j < b; j++) p[j * PGSIZE] = 'A';

        int start_tick = uptime();
        for (int i = 0; i < FORK_COUNT; i++)
        {
            int pid = fork();
            if (pid < 0) {
                printf("fork failed\n");
                exit(1);
            }
            if (pid == 0) {
                exit(0);
            } else {
                wait(0);
            }
        }
        int end_tick = uptime();

        printf("%d %d\n", b, end_tick - start_tick);

        sbrk(-(b * PGSIZE));
    }

    exit(0);
}
