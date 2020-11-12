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
		sem_post(&sinc);
		pthread_mutex_lock(&mutex);
		printf("Tack %d\n", tack);
		tack++;
		eguneratuD();
		printf("Error 0");
		pthread_mutex_unlock(&mutex);

		sem_wait(&sinc);

		
	}
}


void eguneratuD(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++)
		{
			printf("Error 1");
			if (ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].pasatakoD == ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].iraupena){
				//Prozesuak exekutatzen bukatzean
				printf("Error 2");
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].aldatu = 1;
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].egoera = 4;
				prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
				if (prozesagailu.corekop[i].zein == 1){
					if(prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une < prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zenbat){
						prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une++;
					}else{
						prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une = 0;
						if(prozesagailu.corekop[i].nun < 10){
							prozesagailu.corekop[i].nun++;
						}else{
							prozesagailu.corekop[i].zein = 2;
						}
					}	
				}else{
					if(prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une < prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zenbat){
						prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une++;
					}else{
						prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une = 0;
						if(prozesagailu.corekop[i].nun < 10){
							prozesagailu.corekop[i].nun++;
						}else{
							prozesagailu.corekop[i].zein = 2;		
						}
					}
				}		
								

			}else if (prozesagailu.corekop[i].harikop[j].quantum == ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].pasatakoD){
				//Prozesuak quantuma gainditu ezkero
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].egoera = 3;
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].erabilera = 0;
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].aldatu = 0;
				prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
				if (prozesagailu.corekop[i].zein == 1){
					if(prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une < prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zenbat){
						prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une++;
					}else{
						prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une = 0;
						if(prozesagailu.corekop[i].nun < 10){
							prozesagailu.corekop[i].nun++;
						}else{
							prozesagailu.corekop[i].zein = 2;
						}
					}	
				}else{
					if(prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une < prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zenbat){
						prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une++;
					}else{
						prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une = 0;
						if(prozesagailu.corekop[i].nun < 10){
							prozesagailu.corekop[i].nun++;
						}else{
							prozesagailu.corekop[i].zein = 2;
						}
					}
				}	
			}else{
				//Exekutzatzen jarraitu
				ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].pasatakoD++;
			}
			
						
		}
	}
	
}