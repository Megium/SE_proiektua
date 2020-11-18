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
#include "scheduler.h"

volatile int tack;
void eguneratuD();

void *clock_f(){
	
	while(1){
		sem_post(&sinc);
		pthread_mutex_lock(&mutex);
		//printf("Tack %d\n", tack);
		tack++;
		eguneratuD();
		pthread_mutex_unlock(&mutex);

		sem_wait(&sinc2);

		
	}
}


void eguneratuD(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++)
		{
			if(prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//Exekutzatzen jarraitu
				//ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].pasatakoD++;

				prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD++;
				//printf("Denbora eguneratu da");
			}			
		}
	}
	
}
