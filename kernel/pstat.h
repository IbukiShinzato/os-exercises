#include "kernel/param.h" 

struct pstat {
  int inuse[NPROC];   
  int pids[NPROC];    
  int tickets[NPROC]; 
  int pass[NPROC];    
  int stride[NPROC];  
  int times[NPROC]; 
};

