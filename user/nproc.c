#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    printf("%d\n", get_nproc());

    exit(0);
}
