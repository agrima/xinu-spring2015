#include <xinu.h>

int iscycle(){
	int visited[NPROC + NSEM]= {-1};
	int i,j;
	int visit,adj,iter;
	int is_cycle = 0;
	for(i=0;i<NPROC+NSEM;i++){
		visit=0;
		is_cycle=0;
		for(j=0;j<NSEM+NPROC;j++){
			if(cycle_detect[i][j]==1){
				visited[visit++]=j;


			}
             
		}
		
		int node;
		for(adj=0;adj<visit;adj++){
			node=visited[adj];
			for(iter=0;iter<NSEM+NPROC;iter++){
				if(cycle_detect[node][iter]==1){
					if(iter==i){
						is_cycle=1;
					
						break;
					}
					else{
						visited[visit++] = iter;

					}

				}

			}
			if(is_cycle==1){
				break;
			}
		}
		if(is_cycle==1){
			break;
		}
	}
	return is_cycle;




}
