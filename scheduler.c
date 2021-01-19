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

void exek();

void *scheduler_f(){
	int desp;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		//Ilarako prozesuak prozesadoreetan banatu
		pthread_mutex_lock(&mutex2);
		exek();

		pthread_mutex_unlock(&mutex2);

		
	}


}


//prozesuak exekuzioan jarri.
void exek(){
	int i, j, k, l;
	int buk = 0;

	for (i = 0; i < CORE; ++i)
	{
		//printf("Core: %d\n", i);
		buk = 0;
		for(j = 0; j < HARI; j++){
			buk = 0;
			//printf("Haria: %d\n", j);
			if(prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//haria ez badago erabilgarri hurrengo harira pasa.
				//printf("Haria ez dago erabilgarri\n");
				break;
			}else{
				if(prozesagailu.corekop[i].zein == 1){
					//lana errazteko aldagaiak eskuratu.
					int uneko = prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une; //lehentasun barruan zenbatgarren prozesuan doan.
					int nunD = prozesagailu.corekop[i].nun;  //wait ilarako zein lehentasunean doan.
					
					//Lehentasun ilara korritu prozesu erabigarri bat bilatu arte.
					for(k = 0; k < 10; k++){
						//lehentasun honen barruan ez badago prozesurik salto.
						if(prozesagailu.corekop[i].wait1[k].zenbat == 0){
							//printf("Lehentasun %d hutsa dago\n", k);
							//break;
						}else{
							//Lehentasuneko prozesuak korritu erabilgarri bat bilatu arte.
							for(l = 0; l < prozesagailu.corekop[i].wait1[k].zenbat; l++){
								//printf("Prozesuen bila 1\n");
								//begiratu ea prozesua erabilgarri ala exekutatzen dagoen
								if(prozesagailu.corekop[i].wait1[k].zerrenda[l].egoera == 1 ){
									prozesagailu.corekop[i].wait1[k].zerrenda[l].egoera = 2;
									prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une = l;
									prozesagailu.corekop[i].nun = k;
									prozesagailu.corekop[i].harikop[j].erabilgarri = 1;
									prozesagailu.corekop[i].harikop[j].prozesua = prozesagailu.corekop[i].wait1[k].zerrenda[l];
								// 3.zatiko aldaketak
									prozesagailu.corekop[i].harikop[j].pc = prozesagailu.corekop[i].harikop[j].prozesua.pid;
									prozesagailu.corekop[i].harikop[j].ptbr = prozesagailu.corekop[i].harikop[j].prozesua.mm.pgb;
									prozesagailu.corekop[i].harikop[j].prozesua.iraupena = exek_denbora(prozesagailu.corekop[i].harikop[j].ptbr, prozesagailu.corekop[i].harikop[j].prozesua);



									buk = 1;
									printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait1[k].zerrenda[l].pid, i, j);
									break;
								}
							}
							if(buk == 1){
								break;
							}
						}	
					}
					if(k == 10){
						prozesagailu.corekop[i].zein = 2;
						prozesagailu.corekop[i].nun = 0;
					}
					if(buk == 1){
						break;
					}
////////////////////////////////////////////////////////////////////////////////////////////////////////////					
				}else{
					int uneko = prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une; //lehentasun barruan zenbatgarren prozesuan doan.
					int nunD = prozesagailu.corekop[i].nun;  //wait ilarako zein lehentasunean doan.
					
					//Lehentasun ilara korritu prozesu erabigarri bat bilatu arte.
					for(k = 0; k < 10; k++){
						//lehentasun honen barruan ez badago prozesurik salto.
						if(prozesagailu.corekop[i].wait2[k].zenbat == 0){
							//printf("Lehentasun %d hutsa dago\n", k);
							//break;
						}else{
							for(l = 0; l < prozesagailu.corekop[i].wait2[k].zenbat; l++){
								//printf("Prozesuen bila 2\n");
								//begiratu ea prozesua erabilgarri ala exekutatzen dagoen
								if(prozesagailu.corekop[i].wait2[k].zerrenda[l].egoera == 1 ){
									prozesagailu.corekop[i].wait2[k].zerrenda[l].egoera = 2;
									prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une = l;
									prozesagailu.corekop[i].nun = k;
									prozesagailu.corekop[i].harikop[j].erabilgarri = 1;
									prozesagailu.corekop[i].harikop[j].prozesua = prozesagailu.corekop[i].wait2[k].zerrenda[l];
									buk = 1;
									printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait2[k].zerrenda[l].pid, i, j);
									break;
								}
							}
							if(buk == 1){
								break;
							}
						}
						//Lehentasuneko prozesuak korritu erabilgarri bat bilatu arte.
					}
					if(k == 10){
						prozesagailu.corekop[i].zein = 1;
						prozesagailu.corekop[i].nun = 0;
					}
					if(buk == 1){
						break;
					}
				}
			}
		}
	}
}

/*
Denborak:
	ld = 2 ziklo
	st = 2 ziklo
	add = 4 ziklo
	exit = ziklo 1
*/

//Programaren kodea hartuta honen exekuzio denbora itzultzen du.
int exek_denbora(int orriZb, struct pcb proz){

	int denb, i, has;
	char helb[] = proz.mm.data;
	int desp = hamaseitarHamartar(helb, sizeof(helb));
	has = nagusi[orriZb];

	for (i = 0; i < desp; i++)
	{
		switch(nagusi[has].memNa[0]){
			case '0':
				denb = denb + 2;
				break;
			case '1':
				denb = denb + 2;
				break;
			case '2':
				denb = denb + 4;
				break;
			case'F':
				denb = denb + 1;
				break;
		}	
		has++;
	}
	return denb;
}