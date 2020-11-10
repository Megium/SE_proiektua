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
#include "scheduler.h"




void *coretimer_f(){
	int kont;
	while(1){
		kont++;
		sem_wait(&sinc);
		if(kont == MAIZT){
			pthread_mutex_lock(&mutex);
			//printf("Ziklo bat pasa da\n");
			kont = 0;
			pthread_mutex_unlock(&mutex);

			sem_post(&coreT);

		}
		
		sem_post(&sinc);
	}
}