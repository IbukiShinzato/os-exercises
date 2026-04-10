#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

#define MAX_MSG_LEN 512
static char k_msg[MAX_MSG_LEN];
static int k_msg_len = 0;

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_my_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_check_proc(void)
{
  extern struct proc proc[NPROC];

  int pid;
  argint(0, &pid);

  // enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
  // 0 -> success, -1 -> failed

  struct proc *p;

  int found = 0;
  for(p = proc; p < &proc[NPROC]; p++){
    acquire(&p->lock);
    if(p->pid == pid && p->state != UNUSED){
      found = 1;
    }
    release(&p->lock);
    if (found) return 0;
  }

  return -1; 
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if(t == SBRK_EAGER || n < 0) {
    if(growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if(addr + n < addr)
      return -1;
    if(addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_set_msg(void) {
  char *user_buf;
  int user_len;
  struct proc *p = myproc();

  argaddr(0, (uint64*)&user_buf);
  argint(1, &user_len); 
  
  if ((user_len + k_msg_len) > MAX_MSG_LEN || user_len < 0) {
    return -1;
  }

  if (copyin(p->pagetable, k_msg + k_msg_len, (uint64)user_buf, user_len) < 0) {
    return -1;
  }

  k_msg_len += user_len;

  return 0;
}

uint64
sys_get_msg(void) {
  char *user_buf;
  int user_len;

  argaddr(0, (uint64*)&user_buf);
  argint(1, &user_len);
  struct proc *p = myproc();

  if (k_msg_len <= 0) {
    return 0;
  }

  int actual_len = user_len;
  if (actual_len > k_msg_len) {
    actual_len = k_msg_len;
  }

  if (copyout(p->pagetable, (uint64)user_buf, k_msg, actual_len) < 0) {
    return -1;
  }

  return actual_len;
}

uint64
sys_get_pgdir(void) {
  return ((uint64)r_satp() & ~SATP_SV39) << 12;
}
