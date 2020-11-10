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


void gorde(int core, int proz);

void *scheduler_f(){
	int desp;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		
		//Ilarako prozesuak prozesadoreetan banatu
		pthread_mutex_lock(&mutex2);
		//prozesuak exekuziora eraman, gordetzean identifikadoreak bakarrik gorde eta ilara nagusitik hartu.
			if(ilara.buff[desp].erabilera == 0){
				gorde(desp%CORE, desp);
				ilara.buff[desp].erabilera = 1;
			}
			
		}
		pthread_mutex_unlock(&mutex2);

		exek();
	}


}



void exek(){
	
}