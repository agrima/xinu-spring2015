#include<xinu.h>
#define INNERB 1000
#define OUTERB 5
void printloop(int val){
	int i, j;
	for(i=0; i<OUTERB; i++){
		printf("The value of argument is : %d",val);
		for(j=0; j<INNERB; j++){

			//do nothing

		}
	}
}
