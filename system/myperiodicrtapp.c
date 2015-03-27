#include <xinu.h>
#define OUTLOOP 20
void myperiodicrtapp(int rt_period, int rt_comp){
	int i,j,k, arr[OUTLOOP][2], m = 0;
	int negative=0;

	uint32 slp_til_next_period, period_end, period_start,time_a, time_b, time_diff, cpu_received ;	
	for(i=0;i<OUTLOOP;i++){
		cpu_received = 0;
		period_start = myglobalclock;
		for(j=0; j<200000; j++){
			time_a=myglobalclock;
			char src[50] = "hello,we are in program";
			char dest[50];
			/*do memcpy*/
			memcpy(dest, src,50);
			memcpy(src, dest,50);
			while(m<100000)
			{
				m++;

			}
			time_b=myglobalclock;
			time_diff=time_b-time_a;
			//kprintf("Not in the for loop %d\n", time_diff);
			if(time_diff<3){
				cpu_received += time_diff;
				if(cpu_received>=rt_comp){
					//kprintf("assigning negative value");
					negative = myglobalclock;
                                        
					//kprintf("In cpu received, waiting for -ve value, %d\n", arr[i][1]);
					break;
				}
			}

		}
		//period_end=myglobalclock;
		slp_til_next_period = rt_period - (myglobalclock - period_start);
		sleepms(slp_til_next_period);
		arr[i][0] = period_start;
		arr[i][1] = -1* negative;
		
	}
	for(k=0; k<OUTLOOP; k++){
	
	kprintf("arr[%d] ->  %d, arr[1]-->%d\n",k,arr[k][0],arr[k][1]);

	}


}
