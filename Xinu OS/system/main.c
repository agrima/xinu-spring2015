/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
long host2netl_asm(long);
void printsegaddress(void);
int myprogA(int d);
char myfuncA(char d);
void printprocstks(void);
void someprogA(void);
int somefuncA(char c);
void someprogB(void);
int somefuncB(char c);
int somefunc(int a, int b);
void rogueB(void);
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

/*	create(printloop(11), 2048, 25, "process1", 1);
	create(printloop(22), 2048, 25, "process2", 1);
	create(printloop(33), 2048, 25, "process3", 1);
	create(printloop(44), 2048, 25, "process4", 1);
	kprintf("P");
	resume(process1);
	kprintf("P");
	resume(process2);
	kprintf("P");
	resume(process3);
	kprintf("P");
	resume(process4);
	sleepms(5);
*/




/*	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

//	 Wait for shell to exit and recreate it 

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/
/*	register int sp asm ("sp");
		int *p;
	p=sp;int i;
	kprintf("address of stack pointer before creating myprogA is: %x\n", sp);
	kprintf("value of stack pointer before creating myprogA is: %x\n", *p);
	kprintf("Next 12 values of stack pointer before creating myprogA are:\n");
	for(i=1;i<=12; i++){
	p++;	
	kprintf("%x\n", *p);
	}
	printprocstks();
	printsegaddress();
	//create(myprogA(12), 2048, 20, "myprogramA", 1);
	//create(myfuncA('12'), 2048, 20, "myfunctionA", 1);
	resume(create(rogueB, 256, 20,"someprogB", 0));
	resume(create(someprogA, 256, 20, "someprogA", 0));
	//someprogA();
	//someprogB();
	while(TRUE){
		//Do nothing
	}
	return OK;
	
	long x = 0xaabbccdd;
	long z = host2netl_asm(x);
	long y = net2hostl_asm(z);
	kprintf("value of host2netl_asm is 0x%x",z);
	kprintf("value of net2hostl_asm is 0x%x",y);
	*/
}
/*
int myprogA(int a){
	register int sp asm ("sp");
	int *p,i;
	p=sp;
	kprintf("address of stack pointer after calling myprogA is: %x\n", sp);
	kprintf("value of stack pointer after calling myprogA is: %x\n", *p);
	kprintf("Next 12 values of stack pointer after calling myprogA are: \n");
	for(i=1;i<=12; i++){
		p++;
		kprintf("%x\n", *p);
	}

	myfuncA('1');
	kprintf("inside my program after function!\n");
	return a+1;
}
char myfuncA(char b)
{
	register int sp asm ("sp");
	int *p,i;
	p=sp;
	kprintf("address of stack pointer after calling myfuncA is: %x\n", sp);
	kprintf("value of stack pointer after calling myfuncA is: %x\n", *p);
	kprintf("Next 12 values of stack pointer after calling myfuncA are:\n");


	for(i=1;i<=12; i++){
		p++;
		kprintf("%x\n", *p);
	}

	return b;

}
void someprogA(){
	int i;
	putc(CONSOLE, 'A');
	i=somefuncA('a');
	putc(CONSOLE, 'A');


}

int somefuncA(char c){

	sleepms(30);
	putc(CONSOLE, c);
	return 1;
}
void someprogB(){
	int i;
	putc(CONSOLE, 'B');
	i=somefuncB('b');
	putc(CONSOLE, 'B');

}

int somefuncB(char c){

	sleepms(30);
	putc(CONSOLE, c);
	return 1;
}
void rogueB(){
	int i;
	putc(CONSOLE, 'B');
	sleepms(30);
	i=somefunc(1,3);
	sleepms(30);
	putc(CONSOLE, 'B');

}

int somefunc(int a, int b){

	static int i=0;
	++i;
	if(i==400)
		return 1;
	int c = a*b;
	somefunc(c,a);
	return c;
}
*/
