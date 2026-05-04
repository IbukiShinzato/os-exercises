#include "kernel/types.h"
#include "user/user.h"

int total_count = 0;
#define PAGE 4096
#define LOOP 1000
#define MAX_THREADS 10

char stacks[MAX_THREADS][PAGE];

void worker()
{
    for (int i = 0; i < LOOP; i++)
    {
        sem_wait();
        total_count++;
        sem_post();
    }
    exit(0);
}

int main(int argc, char* argv[])
{
    int thread_count = 2;
    int sem_count = 1;

    if (argc >= 2) thread_count = atoi(argv[1]);
    if (argc >= 3) sem_count = atoi(argv[2]);

    if (thread_count > MAX_THREADS) thread_count = MAX_THREADS;

    printf("thread_count = %d, sem_count = %d\n", thread_count, sem_count);
    sem_init(sem_count);

    printf("Test start...\n");

    for (int i = 0; i < thread_count - 1; i++)
    {
        uint64 stack_top = (uint64)stacks[i] + PAGE;
        if (clone(stack_top, PAGE) == 0)
        {
            worker();
        }
    }

    for (int i = 0; i < LOOP; i++)
    {
        sem_wait();
        total_count++;
        sem_post();
    }

    for (int i = 0; i < thread_count - 1; i++)
    {
        wait(0);
    }

    printf("Final count: %d (Expected: %d)\n", total_count, thread_count * LOOP);
    exit(0);
}
