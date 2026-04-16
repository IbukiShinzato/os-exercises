#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: settickets <tickets>\n");
        exit(1);
    }

    int tickets = atoi(argv[1]);

    if (settickets(tickets) < 0)
    {
        fprintf(2, "Error: failed to set tickets to %d. (Must be 10-150 and a multiple of 10)\n",
                tickets);
        exit(1);
    }

    printf("Success: tickets set to %d\n", tickets);

    if (fork() == 0)
    {
        for (volatile int i = 0;; i++)
        {
        }
    }

    exit(0);
}
