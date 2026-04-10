#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    uint64 satp_pa = get_pgdir();
    fprintf(1, "Physical address of the root page table: 0x%lx\n", satp_pa);

    exit(0);
}
