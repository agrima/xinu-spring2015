/* resched.c - resched, resched_cntl */

#include <xinu.h>
#include<ts_init.h>
struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	struct ts_ent *tble,*tble_new;
	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
	/*RT process scheduling*/
        if(ptold->is_real==1){
	      if(ptold->prstate == PR_CURR){
                  if(ptold->rt_prprio > queuetab[firstid(60)].rt_qkey){
		         return ;
			 }
                 
	      ptold->prstate = PR_READY; 
	      insert_rt(currpid, readylist[60], (double) (ptold->rt_prprio));
	  }
        }



	/*When a process is sleeping, change the priority of process*/
	//	if(ptold->is_real!=1){
	else{	
	    if(ptold->prstate==PR_SLEEP){
		tble=&tstab[ptold->prprio];
		ptold->prprio=tble->ts_slpret;
		//return;
	       }
	/*When a process is current, change the priority of process and put it into ready list*/
	    else if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		/*Dont change the priority if it is a NULL process*/
			if (currpid!=NULLPROC) {
				tble=&tstab[ptold->prprio];
				ptold->prprio=tble->ts_tqexp;
			}

			/* Old process will no longer remain current */

			ptold->prstate = PR_READY;
			enqueue(currpid, readylist[ptold->prprio]);
			//	insert(currpid, readylist, ptold->prprio);
		}
      }



	/* Force context switch to highest priority ready process */
	int qsize=SIZE;
	/*run the highest priority process in ready list*/
	while(qsize>=0){
		if(!(isempty(readylist[qsize]))){	
			currpid = dequeue(readylist[qsize]);
			if(currpid==NULLPROC){			//if highest priority process is only NULL process then
				//check there is no other process in the ready list
				if(!(isempty(readylist[qsize]))){
					enqueue(currpid, readylist[qsize]);	//put the process in the ready list as current and enqueue null in the end
					currpid = dequeue(readylist[qsize]);
				}
			}
			break;
		}
		qsize--;
	}
	ptnew = &proctab[currpid];
	if(ptnew->is_real==1){
//	tble_new=&tstab[ptnew->rt_prprio];
	ptnew->prstate = PR_CURR;
	preempt = 60;		/* Reset time slice for process	*/
	}
	else {
	tble_new=&tstab[ptnew->prprio];
	ptnew->prstate = PR_CURR;
	preempt = tble_new->ts_quantum;	
	}
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
