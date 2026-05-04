#include "kernel/types.h"
#include "user/user.h"

#define WAIT 1000000000

int global_count = 0;
char child_stack[4096];

int main(int argc, char* argv[])
{
    int pid = clone((uint64)child_stack, 4096);

    if (pid == 0)
    {
        printf("Child: working...\n");
        global_count = 200;
        printf("Child: done.\n");
        exit(0);
    }
    else
    {
        printf("Parent: waiting for child...\n");

        for (int i = 0; i < WAIT; i++)
        {
            __asm__("nop");
        }

        printf("Parent: global_count is %d\n", global_count);
        if (global_count == 200)
        {
            printf("SUCCESS: Clone Works!\n");
        }
        else
        {
            printf("FAILED: Count is %d\n", global_count);
        }
    }

    exit(0);
}
