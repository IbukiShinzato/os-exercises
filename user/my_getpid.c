#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int pid = my_getpid();
    printf("My PID: %d\n", pid);
    exit(0);
}
