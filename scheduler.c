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
#include "stdbool.h"


void gorde(int core, int proz);

void *scheduler_f(){
	int desp = 0;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		
		sem_wait(&queue2);

		gorde(desp%CORE, desp%MAX);
		//ilara.buff[desp%MAX] = NULL;

		sem_post(&queue1);
		desp++;	
	}


}



void gorde(int core, int proz){

	if (prozesagailu.corekop[core].zein == 1){
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = ilara.buff[proz];
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
		}else{
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = ilara.buff[proz];
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
		}

	}else{
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = ilara.buff[proz];
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
		}else{
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = ilara.buff[proz];
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
		}
	}
}