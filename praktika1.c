#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"


int main(int argc, char const *argv[])
{
	pthread_t clock_hari, timer_hari, process_hari, scheduler_hari;

	pthread_mutex_init(&mutex, 0);

	pthread_create(&clock_hari, NULL, clock_f,NULL);
	pthread_create(&timer_hari, NULL, timer_f,NULL);
	//pthread_create(process_hari, NULL, hari_funtzioa);
	//pthread_create(scheduler_hari, NULL, scheduler);
	
	pthread_join(clock_hari, NULL);
	pthread_join(timer_hari, NULL);
	//pthread_join(process, NULL);
	//pthread_join(scheduler, NULL);

	sem_destroy(&mutex);

}