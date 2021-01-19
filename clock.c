#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"
#include "loader.h"
#include "scheduler.h"

volatile int tack;
void eguneratuD();
void prozAld();

struct String{
	char str[8]
};
struct String text[13];
struct String data[13];

void *clock_f(){
	
	while(1){
		//sem_post(&sinc);
		pthread_mutex_lock(&mutex);
		//printf("Tack %d\n", tack);
		tack++;
		//eguneratuD();
		prozesua_exekutatu();
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
				if(prozesagailu.corekop[i].harikop[j].prozesua.egoera == 4){
					//Egoera exekutatura aldatu
					//prozesagailu.corekop[i].harikop[j].prozesua.egoera = 4;
					//Haria erabilgarri jarri
					prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
					printf("%d hariko prozesuaren exekuzioa amaitu da\n", j);
				//Exekuzioak quantum-a pasaz gero
			}			
		}
	}
	
}

void prozesua_exekutatu(){
	int i, j, datuHas, desp, k, l, er, bal, kont;
	int erreg[16];
	char datuak[];
	char text[];
	char data[];
	char helb[6];
	char agindua;
	for(i = 0; i < CORE; i++){
		for (j = 0; j < HARI; j++){
			if (prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//Exekuzioko datuak non hasten diren atera.
				datuHas = nagusi[prozesagailu.corekop[i].harikop[j].ptbr];
				datuak = prozesagailu.corekop[i].harikop[j].prozesua.mm.data;
				desp = hamaseitarHamartar(datuak, sizeof(datuak));
				//Memoria nagusitik kodea eta datuak berreskuratu.
				for (k = 0; k < desp; k++){
					text[k] = nagusi[datuHas];	
					data[k] = nagusi[datuHas+desp];
				}
				//Kodearen exekuzioa
				for (k = 0; k < desp; k++){
					agindua = text[k].str[0];
					switch (agindua)
					{
					case '0':	//ld
						/* 0 bita agindua, 1.bita erregistroa, gainerako 6ak datu helbidea */
						er = hamaseitarHamartar(text[k].str[1], 1);
						kont = 0;
						for (int i = 2; i < 7; i++){
							helb[kont] = text[k].str[i];
							kont++;
						}
						bal = hamaseitarHamartar(helb, sizeof(helb));
						bal = (bal - 52)/4;
						erreg[er] = hamaseitarHamartar(data[bal], sizeof(data[bal]));
						break;
					case '1':	//st
						/* 0 bita agindua, 1.bita erregistroa, gainerako 6ak datu helbidea */
						for (int i = 2; i < 7; i++){
							helb[kont] = text[k].str[i];
							kont++;
						}
						bal = hamaseitarHamartar(helb, sizeof(helb));
						bal = (bal - 52)/4;
						data[bal] = erreg[hamaseitarHamartar(text[k].str[1], 1)];
						break;	
					case '2':	//add
						/* 0.bita agindua, 1.bita emaitza erregostroa, 2 eta 3.bitak batugaien erregistroak */
						erreg[hamaseitarHamartar(text[k].str[1], 1)] = erreg[hamaseitarHamartar(text[k].str[2], 1)] + erreg[hamaseitarHamartar(text[k].str[3], 1)];
						break;
					case 'F':	//exit
						k = desp + 1;
						prozesagailu.corekop[i].harikop[j].prozesua.egoera = 4;
						break;
					}
				}
			}
		}
	}
}
