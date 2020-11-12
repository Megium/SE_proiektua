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
#include "stdbool.h"

volatile struct queue ilara;
void gorde(int core, int proz);

void *generateProcess_f(){
    //prozesuak sortzeko ausazko denboren hazia
	time_t t;
    srand((unsigned) time(&t));
    
    //Ilara objetua sortu eta hasieratu.
    
	ilara.indizea = 0;
    //Ilararen tamaina aldakora izango denez, ilara dinamiko bat sortu behar da.
    ilara.buff = malloc(MAX*sizeof(struct pcb));
	

    int i = 1;
	int d, l, c, k, j, m;
	k=0;
	j=0;

	for (int k = 0; k < MAX; k++)
	{
		ilara.buff[k].aldatu = 1;
		ilara.buff[k].erabilera = 1;
		ilara.buff[k].pid = 0;
	}

	while(1){

		d = rand() % (MAIZT%7);
		l = rand() % POSIZIO;
		c = rand() % 10000;
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko
		if(d!=0){
			sleep(d);
            //Prozesu berri bat sortu, pcb motakoa
			struct pcb prozesu;

			//Prozesu berriari pid bat esleitu
			prozesu.pid = i;
			//prozesuari lehentasun bat esleitu ausaz
			prozesu.lehentasuna = l;
			prozesu.iraupena = c;
			prozesu.egoera = 1;
			prozesu.pasatakoD = 0;
			prozesu.erabilera = 0;
			prozesu.aldatu = 0;
			printf("%d. prozesua sortu da.\n", i);
			//pthread_mutex_lock(&mutex2); 
            //bufferrean sartu beharreko prozesua sortzeko deia egin
            while(k==0){
				pthread_mutex_lock(&mutex2);
            	if (ilara.buff[j%MAX].aldatu == 1){
					if(ilara.buff[j%MAX].erabilera == 1){
						ilara.buff[j%MAX] = prozesu;
            			gorde(i%CORE, j%MAX);
						ilara.indizea++;
            			k=1;
						//printf("Errore[1]\n");
					}
            		if(ilara.indizea == MAX){
						ilara.indizea = 0;
						//printf("Errore[2]");
					}else{
						ilara.indizea++;
						//printf("Errore[3]");
					}
            	}else{
            		j++;
            	}
				pthread_mutex_unlock(&mutex2);
            }
			k=0;


            //eguneratu indizea
			
            //pthread_mutex_unlock(&mutex2);
			j++;
			i++;
		}	
	}


}

void gorde(int core, int proz){

	if (prozesagailu.corekop[core].zein == 1){
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX; //ilara.buff[proz].pid
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
			ilara.buff[proz].aldatu = 0;
			printf("PID %d. prozesua %d. corean sartu da. \n",ilara.buff[proz].pid, core);
		}else{
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
			ilara.buff[proz].aldatu = 0;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}

	}else{
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
			ilara.buff[proz].aldatu = 0;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}else{
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
			ilara.buff[proz].aldatu = 0;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}
	}
}


