/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>
#include <ts_init.h>
extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	void xdone(void);	/* System "shutdown" procedure		*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/
struct ts_ent tstab[SIZE];
/* Active system status */
int     numb_rt; 				/*number of RT processes*/
int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/
int cycle_detect[NPROC+NSEM][NPROC+NSEM];
/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */
void readTS(){
int32 i;
struct ts_ent *entry;

	for(i=0;i<SIZE;i++){
		entry=&tstab[i];
		if(i>=0 && i<10){
			entry->ts_quantum=200;
			entry->ts_tqexp=0;
			entry->ts_slpret=50;
		}
		if(i>=10 && i<20){
			entry->ts_quantum=160;
			entry->ts_tqexp=i-10;
			entry->ts_slpret=51;
		}
		if(i>=20 && i<30){
			entry->ts_quantum=120;
			entry->ts_tqexp=i-10;
			entry->ts_slpret=52;
		}
		if(i>=30 && i<40){
			entry->ts_quantum=80;
			entry->ts_tqexp=i-10;
			if(i>=30 && i<35){
				entry->ts_slpret=53;
			}
			else
				entry->ts_slpret=54;
		}
		if(i>=40 && i<50){
			entry->ts_quantum=40;
			entry->ts_tqexp=i-10;
			if(i>=40 && i<45){
				entry->ts_slpret=55;
			}
			else if(i==45)
				entry->ts_slpret=56;
			else if(i==46)
				entry->ts_slpret=57;
			else
				entry->ts_slpret=58;
		}
		if(i>=50 && i<59){
			entry->ts_quantum=40;
			entry->ts_tqexp=i-10;
			entry->ts_slpret=58;
		}
		if(i==59){

			entry->ts_quantum=20;
			entry->ts_tqexp=49;
			entry->ts_slpret=59;


		}
	}




}
void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */
		
	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);
	
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\r\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();

	/* Create a process to execute function main() */

	resume (
	   create((void *)main, INITSTK, INITPRIO, "Main process", 0,
           NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i,x,y;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/
	/*cycle matrix initialization*/
	for(x=0; x<NPROC+NSEM; x++){
		for(y=0; y<NPROC + NSEM; y++){
			cycle_detect[x][y]=0;
		}
	}
	/* global clock  Initialization */
	myglobalclock = 0;

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */
	
	numb_rt=0;

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
		/* CPU time  Initialization */
		prptr->prcputime=0;
		prptr->rt_period = 0;
		prptr->rt_comp = 0;
		prptr->is_real = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
	prptr->is_real = 0;

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create 60 ready list for processes */
	int32 w;
	for(w=0; w<=60; w++){
	readylist[w] = newqueue();
	}
	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}
	readTS();
	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
