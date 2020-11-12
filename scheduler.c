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
#include "coretimer.h"
#include "coreWork.h"
#include "stdbool.h"


void exek();

void *scheduler_f(){
	int desp;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		
		//Ilarako prozesuak prozesadoreetan banatu
		pthread_mutex_lock(&mutex2);
		//prozesuak exekuziora eraman, gordetzean identifikadoreak bakarrik gorde eta ilara nagusitik hartu.
		

		pthread_mutex_unlock(&mutex2);

		exek();
	}


}



void exek(){
	int i, kont, j;
	for ( i = 0; i < CORE; i++)
	{
		kont = 0;
		j = 0;
		while(j == 0){
			if (prozesagailu.corekop[i].harikop[kont].erabilgarri == 0){
				if(prozesagailu.corekop[i].zein == 1){
					ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].egoera = 2;
					ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].erabilera = 1;
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]; 
					j = 1;
				}else
				{
					ilara.buff[prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].egoera = 2;
					ilara.buff[prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].erabilera = 1;	
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]; 
					j = 1;
				}
			}else if (kont == HARI){
				j = 1;
			}
			kont++;
		}
	}
	
}