#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"

volatile int tack;
pthread_mutex_t mutex;

void *clock_f(){
	
	while(1){
		sem_wait(&sinc);
		pthread_mutex_lock(&mutex);
		tack++;
		printf("Tack %d\n", tack);
		pthread_mutex_unlock(&mutex);

		sem_post(&sinc2);

		
	}
}
