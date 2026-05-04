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
