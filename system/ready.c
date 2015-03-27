/* ready.c - ready */

#include <xinu.h>
#include<ts_init.h>
qid16	readylist[61];			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	if(prptr->is_real==1){
	insert_rt(pid, readylist[60], prptr->rt_prprio);
	}else{
	//insert into the ready list of process process priority number
	enqueue(pid, readylist[prptr->prprio]);
	}
	resched();

	return OK;
}
