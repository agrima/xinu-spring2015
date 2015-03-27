#include<xinu.h>

void printprocstks(){

//create(myprogA(12), 2048, 20, "myprogramA", 1);
//create(myfuncA('12'), 2048, 20, "myfunctionA", 1);

struct procent *ptr;
int32 i;
pid32 pid;

kprintf("hello we are printing stack details now!!\n");

for(i=0; i<NPROC; i++){
	if ( ((ptr = &proctab[i])->prstate) != PR_FREE) {

	
	kprintf("Proc[%s].PID:%d\n",ptr->prname,i);
	kprintf("Stack:");
	kprintf("Base:%x \n", ptr->prstkbase);
	kprintf("\tLen:%x \n", ptr->prstklen);
	kprintf("\tLimit:%x \n", ptr->prstkbase-ptr->prstklen);
	
	if ( ((ptr = &proctab[i])->prstate) != PR_CURR) {
	kprintf("\tStkPtr:%x \n", ptr->prstkptr);
	}
	else{
		register int sp asm ("sp");
		kprintf("\tStkPtr:%x\n", sp);
	
	}
	}
}
}
