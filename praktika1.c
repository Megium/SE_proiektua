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

sem_t sinc;
sem_t sinc2;

sem_t sche;

pthread_mutex_t mutex;
int MAIZT;
int MAX;//kanpotik hasieratu behar da.

int main(int argc, char const *argv[])
{
	pthread_t clock_hari, timer_hari, process_hari, scheduler_hari;
	
	MAIZT = atoi(argv[1]);
	MAX = atoi(argv[2]);

	pthread_mutex_init(&mutex, 0);
	sem_init(&sche, 1, 1);
	sem_init(&sinc, 1, 1);
	sem_init(&sinc2, 1, 0);

	pthread_create(&clock_hari, NULL, clock_f,NULL);
	pthread_create(&timer_hari, NULL, timer_f,NULL);
	pthread_create(&process_hari, NULL, generateProcess_f, NULL);
	pthread_create(&scheduler_hari, NULL, scheduler_f, NULL);
	
	pthread_join(clock_hari, NULL);
	pthread_join(timer_hari, NULL);
	pthread_join(process_hari, NULL);
	pthread_join(scheduler_hari, NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&sche);
	sem_destroy(&sinc);
	sem_destroy(&sinc2);
}