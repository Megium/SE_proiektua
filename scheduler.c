#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"
#include "processG.h"


void hasieratu();

struct pcb active[ilaraKop];
struct pcb expired[ilaraKop];
int sig;

void *scheduler_f(){
	sig = 0;
	while(1){
			sem_wait(&sche);
			printf("-----------------\n-   Scheduler   -\n-----------------\n");
			//hasieratu(sig);
	}


}

void hasieratu(int sig){
	//Schedulerreko ilarak hasieratu eta bete
	int max, i, j, lehen;
	max = ilara.indizea;

	if (sig == 0)
	{
		for (i = 0; i < max; ++i)
		{
			lehen = ilara.buff[i].lehentasuna;
			active[lehen] = ilara.buff[i];
		}
	}else{
		for (j = 0; j < max; ++j)
		{
			
		}
	}
}