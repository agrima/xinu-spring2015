#include <xinu.h>

void mydeadlockapp(sid32 sem1, sid32 sem2){
       //	kprintf("goind to wait on first sem:%d\n", sem1);
	waitd(sem1);
//	kprintf("Acquired sem1:%d\n", sem1);
//	signald(sem1);
	sleepms(5);

//	kprintf("going to wait on second sem:%d\n", sem2);
	waitd(sem2);
	//kprintf("Acquired sem2:%d\n", sem2);
//	sleepms(5);
	//signald(sem2);
	//kprintf("Gave up sem2: %d\n", sem2);
       // signald(sem1);
	//kprintf("Gave up sem1: %d\n", sem1);

	//kprintf("finish to wait on second sem:%d\n", sem2);

}
