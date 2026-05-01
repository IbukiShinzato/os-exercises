#include "kernel/types.h"
#include "user/user.h"

int global_count = 0;

int main(int argc, char* argv[])
{
    void* stack = malloc(4096);
    int pid = clone((uint64)stack, 4096);

    if (pid == 0)
    {
        printf("hello!\n");
        printf("Child: working...\n");
        global_count = 100;
        printf("Child: done.\n");
        exit(0);
    }
    else
    {
        printf("Parent: waiting for child...\n");

        for (int i = 0; i < 1000000; i++)
        {
            __asm__("nop");
        }

        printf("Parent: global_count is %d\n", global_count);
        if (global_count == 100)
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
