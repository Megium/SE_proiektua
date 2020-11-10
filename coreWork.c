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

void *core_f(){
	while(1){

		sem_wait(&coreT);



	}
}