#include <xinu.h>
#include<string.h>
void cpuintensive(void);
void cpuintensive(){
	int i,j;struct procent *ptr;
		ptr=&proctab[currpid];
	kprintf("PID\tinLoopVal\tpriority\ttimeSlice\n");
	for(i=0; i<15; i++){
		for(j=0; j<10000; j++){
			int k;
			const char src[50] = "hello,we are in cpuintensive program";
			   char dest[50];
			/*do memcpy*/
			memcpy(dest, src, strlen(src)+1);
			k+=i*j;
		
		}
		kprintf("%d\t%d\t\t%d\t\t%d\n",currpid,i,ptr->prprio,preempt);
	//	kprintf("The pid of current process is: %d and the loop1 value is %d\n", currpid,i);	
	//	kprintf("the process priority is %d and current time slice is %d\n", ptr->prprio,preempt);
			
	
	
	}
	kprintf("The process cputime is: %d\n", ptr->prcputime);

}
