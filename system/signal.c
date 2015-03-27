/* signal.c - signal */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  signal  -  Signal a semaphore, releasing a process if one is waiting
 *------------------------------------------------------------------------
 */
syscall	signal(
	  sid32		sem		/* ID of semaphore to signal	*/
	)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct	sentry *semptr;		/* Ptr to sempahore table entry	*/
	pid32 pid_nowait;
	mask = disable();
	if (isbadsem(sem)) {
		restore(mask);
		return SYSERR;
	}
	semptr= &semtab[sem];
	if (semptr->sstate == S_FREE) {
		restore(mask);
		return SYSERR;
	}
	cycle_detect[currpid][NPROC+sem]=0;
	if ((semptr->scount++) < 0) {	/* Release a waiting process */
		pid_nowait=dequeue(semptr->squeue);
	//	cycle_detect[NPROC+sem][pid_nowait]=0;
		ready(pid_nowait);
	}
	restore(mask);
	return OK;
}
