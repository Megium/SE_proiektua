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


void gorde(int core, int proz);



struct priority sche1[POSIZIO];
struct priority sche2[POSIZIO];

int sig;

void *scheduler_f(){
	int desp = 0;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		
		
		sem_wait(&queue2);
		gorde(desp%CORE, desp%MAX);


		sem_post(&queue1);
		desp++;	
	}


}



void gorde(int core, int proz){
	prozesagailu.corekop[core].
}