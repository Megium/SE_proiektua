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

void exek();
void prozAld();

void *scheduler_f(){
	int desp;

	while(1){

		sem_wait(&sche);
		//printf("-----------------\n-   Scheduler   -\n-----------------\n");
        printf(" ");
		//Ilarako prozesuak prozesadoreetan banatu
		pthread_mutex_lock(&mutex2);
		//prozesuak exekuziora eraman, gordetzean identifikadoreak bakarrik gorde eta ilara nagusitik hartu.
		prozAld();

		pthread_mutex_unlock(&mutex2);

		exek();
	}


}



void exek(){
	int i, kont, j;
	for ( i = 0; i < CORE; i++)
	{
		kont = 0;
		j = 0;
		while(j == 0){
			if (prozesagailu.corekop[i].harikop[kont].erabilgarri == 0 && ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].pid != 0){
				if(prozesagailu.corekop[i].zein == 1){
					ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].egoera = 2;
					ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].erabilera = 1;
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une];
					printf("%d prozesua exekutatzen.\n", ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].pid);
					j = 1;
				}else
				{
					ilara.buff[prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].egoera = 2;
					ilara.buff[prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].erabilera = 1;	
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]; 
					j = 1;
					printf("%d prozesua exekutatzen.\n", ilara.buff[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].zerrenda[prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une]].pid);
				}
			}if (kont == HARI){
				j = 1;
				//printf("%d hari guztiak beteta daude.\n", prozesagailu.corekop[i].coreID);
			}else
			{
				printf("Hasieratu gabe\n");
				j=1;
			}
			
			kont++;
		}
	}
	
}

void prozAld(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++){
			if (ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].pasatakoD == ilara.buff[prozesagailu.corekop[i].harikop[j].prozesua].iraupena){
				//Prozesuak exekutatzen bukatzean
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
			}			
		}
	}
	
}
