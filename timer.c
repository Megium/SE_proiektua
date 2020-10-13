#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"

/*
Megahertzio 10^6
*/

void *timer_f(){
	int kont = 0;
	int tack;
	
	while(1){
		printf("Tik %d\n", kont);
		if(tack == 1000000){
			//Megahertzio bat
			//zerbait();
			pthread_mutex_lock(&mutex);
			printf("Megahertzio bat pasa da\n");
			tack = 0;
			kont = 0;
			pthread_mutex_unlock(&mutex);
			
			
		}
		kont++;
	}
	
}