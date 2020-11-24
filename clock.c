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
void prozAld();

void *clock_f(){
	
	while(1){
		//sem_post(&sinc);
		pthread_mutex_lock(&mutex);
		//printf("Tack %d\n", tack);
		tack++;
		eguneratuD();
		prozAld();
		pthread_mutex_unlock(&mutex);

		//sem_wait(&sinc2);

		
	}
}


void eguneratuD(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++)
		{
			if(prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//Exekutzatzen jarraitu
				prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD++;
			}			
		}
	}
	
}



void prozAld(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++){
			//Lehendabizi begiratu ea haria exekuzioan dagoen ala ez
			if (prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//Prozesuak exekutatzen bukatzean
				//printf("%d prozesan igarotako denbora %d / %d-tik\n", prozesagailu.corekop[i].harikop[j].prozesua.pid, prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD, prozesagailu.corekop[i].harikop[j].prozesua.iraupena);
				if(prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD == prozesagailu.corekop[i].harikop[j].prozesua.iraupena){
					//Egoera exekutatura aldatu
					prozesagailu.corekop[i].harikop[j].prozesua.egoera = 4;
					//Haria erabilgarri jarri
					prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
					printf("%d hariko prozesuaren exekuzioa amaitu da\n", j);
				//Exekuzioak quantum-a pasaz gero
				}else if(prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD == prozesagailu.corekop[i].harikop[j].quantum){
					printf("%d hariko prozesuk kuantuma gainditu du\n", j);
					//Egoera blokeatura pasa.
					prozesagailu.corekop[i].harikop[j].prozesua.egoera = 3;
					//Haria erabilgarri jarri.
					prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
					//Prozesua berriro coreko ilarara itzuli.
					gorde(i, prozesagailu.corekop[i].harikop[j].prozesua);
				}
			}			
		}
	}
	
}