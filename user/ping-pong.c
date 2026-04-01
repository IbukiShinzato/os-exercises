#include "kernel/types.h"
#include "user/user.h"

// 実行回数
#define TRIALS 10000

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: ping-pong <one-byte>\n");
        exit(1);
    }

    char* data = argv[1];
    char b = data[0];

    // p2c: Parent to Child, c2p: Child to Parent
    int p2c[2], c2p[2];

    if (pipe(p2c) < 0 || pipe(c2p) < 0)
    {
        printf("pipe() failed\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0)
    {
        printf("fork failed\n");
        exit(1);
    }

    if (pid == 0)
    {
        close(p2c[1]);
        close(c2p[0]);

        char buf;
        while (read(p2c[0], &buf, 1) > 0)
        {
            write(c2p[1], &buf, 1);
        }

        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    }
    else
    {
        close(p2c[0]);
        close(c2p[1]);

        printf("Starting %d exchanges with byte '%c'...\n", TRIALS, b);

        int start_tick = uptime();

        for (int i = 0; i < TRIALS; i++)
        {
            if (write(p2c[1], &b, 1) != 1)
            {
                printf("write error\n");
                break;
            }
            if (read(c2p[0], &b, 1) != 1)
            {
                printf("read error\n");
                break;
            }
        }

        int end_tick = uptime();
        int total_ticks = end_tick - start_tick;

        if (total_ticks > 0)
        {
            // ask for the very first timer interrupt.
            // w_stimecmp(r_time() + 1000000);
            // 1 tick = 1,000,000 cycles = 1 second (想定)

            int per_second = TRIALS / total_ticks;
            printf("%d exchanges in %d ticks\n", TRIALS, total_ticks);
            printf("Exchanges per second: %d\n", per_second);
        }
        else
        {
            printf("The measurement was too fast (0 ticks elapsed).\n");
            printf("Please increase TRIALS to 100000 or more.\n");
        }

        close(p2c[1]);
        close(c2p[0]);
        wait(0);
    }

    exit(0);
}
