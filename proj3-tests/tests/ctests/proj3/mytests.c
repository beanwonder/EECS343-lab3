#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   // testing multithreaded
   void *stack0 = malloc(PGSIZE*2);
   assert(stack0 != NULL);
   if((uint)stack0 % PGSIZE) {
     stack0 = stack0 + (PGSIZE - (uint)stack0 % PGSIZE);
   }
   void *stack1 = malloc(PGSIZE*2);
   assert(stack1 != NULL);
   if((uint)stack1 % PGSIZE) {
     stack1 = stack1 + (PGSIZE - (uint)stack1 % PGSIZE);
   }
   int new_thread_pid0 = clone(worker, 0, stack0);
   int new_thread_pid1 = clone(worker, 0, stack1);

   new_thread_pid0 += 0;
   new_thread_pid1 += 0;

   int join_pid0 = join(new_thread_pid0);
   int join_pid1 = join(new_thread_pid1);

   join_pid0 += 0;
   join_pid1 += 1;

   assert(global == 3);

   printf(1, "global: %d\n", global);
   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   global += 1;
   exit();
}
