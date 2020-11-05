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



struct priority sche1[POSIZIO];
struct priority sche2[POSIZIO];

int sig;

void *scheduler_f(){
	sig = 0;
	while(1){
			sem_wait(&sche);
			printf("-----------------\n-   Scheduler   -\n-----------------\n");
			hasieratu(sig);

			
			
	}


}

void hasieratu(int sig){
	//Schedulerreko ilarak hasieratu eta bete
	int max, i, j, k, lehen;
	sem_wait(&queue2);
	max = ilara.indizea;

	if (sig == 0)
	{
		for (k = 0; k < POSIZIO; ++k)
		{
			sche1[k].zenbat = 0;
			sche2[k].zenbat = 0;
		}
		sig = 1;
	}
	else if(sig == 1)	
	{
		for (i = 0; i < max; ++i)
		{
			lehen = ilara.buff[i].lehentasuna;
			sche1[lehen].zerrenda[sche1[lehen].zenbat] = ilara.buff[i];
			sche1[lehen].zenbat++;
		}
		ilara.indizea = 0;
		sig = 2;
	}else{
		for (j = 0; j < max; ++j)
		{
			lehen = ilara.buff[i].lehentasuna;
			sche2[lehen].zerrenda[sche2[lehen].zenbat] = ilara.buff[j];;
			sche2[lehen].zenbat++;
		}
		ilara.indizea = 0;
		sig = 1;
	}
	sem_post(&queue1);
}

void prozesuak_banatu(){
	if (sig == 1)
	{
		
	}
}