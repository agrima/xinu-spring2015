#include<xinu.h>
extern int etext, edata, bss;
//void printsegaddress(void);
void printsegaddress(){
	int i;
	char *x, *y, *z;
	x=&etext;y=&edata; z=&bss;
/**********************************TEXT***********************************/
	kprintf("The value of text address is %x\n",&etext);
	for(i=1;i <=12; i++){
	x++;
	kprintf("The value of text address above %d is %x\n",i,*x);
//	kprintf("The value address of text address 3*%d is %x\n",i,x);
	}
	x=&etext;
	for(i=1;i <=12; i++){
	x--;
	kprintf("The value of text address below %d is %x\n",i,*x);
//	kprintf("The value address of text address 3*%d is %x\n",i,x);
	}
/************************************DATA**********************************/	
	kprintf("The value of data address is %x\n",&edata);
	for(i=1;i <=12; i++){
	y++;
	kprintf("The value of data address above %d is %x\n",i,*y);
//	kprintf("The value address of data address 3*%d is %x\n",i,y);
	}
	y=&edata;
	for(i=1;i <=12; i++){
	y--;
	kprintf("The value of data address below %d is %x\n",i,*y);
//	kprintf("The value address of data address 3*%d is %x\n",i,y);
	}
/********************************************BSS*********************************/
	kprintf("The value of bss address is %x\n",&bss);
	for(i=1;i <=12; i++){
	z++;
	kprintf("The value of bss address above %d is %x\n",i,*z);
//	kprintf("The value address of bss address 3*%d is %x\n",i,z);
	}
	z=&bss;
	for(i=1;i <=12; i++){
	z--;
	kprintf("The value of bss address below %d is %x\n",i,*z);
//	kprintf("The value address of bss address 3*%d is %x\n",i,z);
	}




}
