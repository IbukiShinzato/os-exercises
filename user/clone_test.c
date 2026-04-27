#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    void* stack = malloc(4096);
    uint64 stack_top = (uint64)stack + 4096;

    clone(stack_top);

    exit(0);
}
