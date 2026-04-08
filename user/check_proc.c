#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(2, "Usage: check_proc <pid>\n");
        exit(1);
    }

    int target_pid = atoi(argv[1]);

    printf("--- System Call Connectivity Test ---\n");

    printf("1. Checking PID 1 (init): %s\n", check_proc(1) == 0 ? "ALIVE" : "NOT FOUND");

    printf("2. Checking PID 999 (invalid): %s\n", check_proc(999) == 0 ? "ALIVE" : "NOT FOUND");

    int my_pid = getpid();
    printf("3. Checking my own PID (%d): %s\n", my_pid,
           check_proc(my_pid) == 0 ? "ALIVE" : "NOT FOUND");

    printf("4. Checking specified PID (%d): %s\n", target_pid,
           check_proc(target_pid) == 0 ? "ALIVE" : "NOT FOUND");

    exit(0);
}
