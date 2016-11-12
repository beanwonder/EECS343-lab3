#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


// wrapper for create a thread
int thread_create(void (*start_routine)(void*), void* arg)
{
	void *stack = malloc(PGSIZE*2);
	if (stack == NULL)
		return -1;

   	if((uint)stack % PGSIZE) {
    	stack = stack + (PGSIZE - (uint)stack % PGSIZE);
   	}
	return clone(start_routine, arg, stack);
}


// wrapper for thread join
int thread_join(int pid)
{
	return join(pid);
}
