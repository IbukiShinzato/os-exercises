struct sem {
  struct spinlock lk;
  int count;
};
