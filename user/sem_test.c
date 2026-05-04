#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
  int count = 10;
  if (sem_init(count) < 0) {
    fprintf(2, "sem_init failed\n");
  }
  printf("sem_init success!\n");
  exit(0);
}
