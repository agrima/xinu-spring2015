/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
void printloop(int);
void cpuintensive(void);
void iointensive(int);
void myperiodicrtapp(int , int);
void mydeadlockapp(sid32, sid32);
process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	kprintf("\n...creating a shell\n");
	recvclr();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	sid32 s1, s2, s3,s4;
	s1 = semcreate(1);
	s2 = semcreate(1);
//	s3 = semcreate(1);
//	s4 = semcreate(1);
//	resume(create(mydeadlockapp, 2048, 20, "d1", 2, s1, s2));
//	resume(create(mydeadlockapp, 2048, 20, "d2", 2, s2, s1));
	//resume(create(mydeadlockapp, 2048, 20, "d1", 2, s3, s1));
	


	resume(rt_create(50,10,myperiodicrtapp, 2048, 20, "p1", 2, 50, 10 ));
	resume(rt_create(200,40,myperiodicrtapp, 2048, 20, "p2",2, 200, 40 ));
	resume(rt_create(100,15,myperiodicrtapp, 2048, 20, "p2",2, 100, 15 ));


	resume(create(cpuintensive, 2048, 20, "p1", 0));
	resume(create(cpuintensive, 2048, 20, "p2", 0));
	resume(create(cpuintensive, 2048, 20, "p3", 0));


/*	resume(create(iointensive, 2048, 20, "p4", 1, 5));
	resume(create(iointensive, 2048, 20, "p5", 1, 10));
	resume(create(iointensive, 2048, 20, "p6", 1, 20));
	
*/	
	/* Wait for shell to exit and recreate it */

	/*while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}

	return OK;*/
/*	
	pid32 p1,p2,p3,p4;
	p1 = create(printloop, 2048, 25, "process1",1, 11);
	p2 = create(printloop, 2048, 25, "process2",1, 22);
	p3 = create(printloop, 2048, 25, "process3",1, 33);
	p4 = create(printloop, 2048, 25, "process4",1, 44);
	kprintf("P\n");
	resume(p1);
	kprintf("P\n");
	resume(p2);
	kprintf("P\n");
	resume(p3);
	kprintf("P\n");
	resume(p4);
	sleepms(5000);
*/
}
