#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    void* stack_base = malloc(4096);
    clone((uint64)stack_base, 4096);

    stack_base = malloc(4096);
    clone((uint64)stack_base, 4096);

    stack_base = malloc(4096);
    clone((uint64)stack_base, 4096);

    exit(0);
}
