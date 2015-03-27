#include <xinu.h>
#include<string.h>
void iointensive(int);
void iointensive(int sleeptime){
	int i,j;struct procent *ptr;uint32 x_globalclock, n_globalclock;
		ptr=&proctab[currpid];
	for(i=0; i<20; i++){
		for(j=0; j<1000; j++){
		x_globalclock = myglobalclock;
		sleepms(sleeptime);		
		n_globalclock=myglobalclock-x_globalclock;
		}
		kprintf("The difference is: %d\n", n_globalclock);
		kprintf("The pid of current process is: %d and the loop1 value is %d\n", currpid,i);	
		kprintf("the process priority is %d and current time slice is %d\n", ptr->prprio,preempt);
			
	
	
	}
	kprintf("The process cputime is: %d\n", ptr->prcputime);

}
