#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "semaphore.h"

struct sem s;

uint64
sem_init(int count)
{
  initlock(&s.lk, "semaphore");
  s.count = count;

  return 0;
}

uint64
sem_wait()
{
  acquire(&s.lk);
  while (s.count <= 0) {
    printf("DEBUG: s.count = %d\n", s.count);
    sleep(&s, &s.lk);
  }
  s.count--;
  release(&s.lk);
  return 0;
}
