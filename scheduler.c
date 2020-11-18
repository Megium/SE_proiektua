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
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
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
			if (prozesagailu.corekop[i].harikop[kont].erabilgarri == 0){
				
				//zein azpizerrendetan dagoen ikusi.
				if(prozesagailu.corekop[i].zein == 1){
					//lana errazteko aldagaiak eskuratu.
					int uneko = prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une;
					int nunD = prozesagailu.corekop[i].nun;

					//Core barrutik hurrengo prozesua hartu eta harira eraman.
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait1[nunD].zerrenda[uneko];
					//Exekuzioan jarritako prozesuari egoera aldatu(2 == exekuzioan)
					prozesagailu.corekop[i].harikop[kont].prozesua.egoera = 2;
					//Coreko azpi lista eguneratu.
					prozesagailu.corekop[i].wait1[nunD].une++;
					//konprobatu ea lehentasun hau bukatu den.
					if(prozesagailu.corekop[i].wait1[nunD].une == prozesagailu.corekop[i].wait1[nunD].zenbat){
						prozesagailu.corekop[i].nun++;
						//Konprobatu ea lehentasun guztiak pasa diren.
						if(prozesagailu.corekop[i].nun == 10){
							prozesagailu.corekop[i].zein =2;
						}
					}
					
					printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait1[nunD].zerrenda[uneko].pid, i, kont);
					j = 1;
					kont++;
				}else{
					//goiko berdina kopiatu wait2 aldatuta.
					//lana errazteko aldagaiak eskuratu.
					int uneko = prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une;
					int nunD = prozesagailu.corekop[i].nun;

					//Core barrutik hurrengo prozesua hartu eta harira eraman.
					prozesagailu.corekop[i].harikop[kont].prozesua = prozesagailu.corekop[i].wait2[nunD].zerrenda[uneko];
					//Exekuzioan jarritako prozesuari egoera aldatu(2 == exekuzioan)
					prozesagailu.corekop[i].harikop[kont].prozesua.egoera = 2;
					//Coreko azpi lista eguneratu.
					prozesagailu.corekop[i].wait2[nunD].une++;
					//konprobatu ea lehentasun hau bukatu den.
					if(prozesagailu.corekop[i].wait2[nunD].une == prozesagailu.corekop[i].wait2[nunD].zenbat){
						prozesagailu.corekop[i].nun++;
						//Konprobatu ea lehentasun guztiak pasa diren.
						if(prozesagailu.corekop[i].nun == 10){
							prozesagailu.corekop[i].zein = 1;
						}
					}
					
					printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait2[nunD].zerrenda[uneko].pid, i, kont);
					j = 1;
					kont++;
				}
			}if (kont == HARI){
				//Hari guztiak okupatuta badaude hurrengo corera salto.
				j = 1;
				printf("%d hari guztiak beteta daude.\n", prozesagailu.corekop[i].coreID);
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
				if(prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD == prozesagailu.corekop[i].harikop[j].prozesua.iraupena){
					//Egoera exekutatura aldatu
					prozesagailu.corekop[i].harikop[j].prozesua.egoera = 4;
					//Haria erabilgarri jarri
					prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
				//Exekuzioak quantum-a pasaz gero
				}else if(prozesagailu.corekop[i].harikop[j].prozesua.pasatakoD == prozesagailu.corekop[i].harikop[j].quantum){
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
