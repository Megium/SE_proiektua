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


void *scheduler_f(){
	
	while(1){
			sem_wait(&sche);
			printf("-----------------Seinale bat bidali da-----------------\n");
			
	}

}