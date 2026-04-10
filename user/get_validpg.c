#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    uint64 satp_pa = get_pgdir();
    printf("Physical address of the root page table: 0x%lx\n\n", satp_pa);

    printf("Before: %ld\n", (uint64)get_validpg_num());
    sbrk(4096 * 10);
    printf("\n");
    printf("After: %ld\n", (uint64)get_validpg_num());

    exit(0);
}
