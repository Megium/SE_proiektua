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
#include "coretimer.h"
#include "coreWork.h"
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
	
    int i = 0;
	int d, l, c, k;
	k=0;
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

			//pthread_mutex_lock(&mutex2); 
            //bufferrean sartu beharreko prozesua sortzeko deia egin
            while(k==0){
				pthread_mutex_lock(&mutex2);
            	if (ilara.buff[i/MAX].aldatu == 1){
					if(ilara.buff[i%MAX].erabilera == 1){
						ilara.buff[i%MAX] = prozesu;
            			gorde(i%CORE, i);
            			k=1;
					}
            		if(ilara.indizea == MAX){
						ilara.indizea = 0;
					}else{
						ilara.indizea++;
					}
            	}else{
            		i++;
            	}
				pthread_mutex_unlock(&mutex2);
            }
			k=0;


            //eguneratu indizea
			
            //pthread_mutex_unlock(&mutex2);
			printf("%d. prozesua sortu da.\n", i);
			
		}
		
	}


}

void gorde(int core, int proz){

	if (prozesagailu.corekop[core].zein == 1){
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX; //ilara.buff[proz].pid
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}else{
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}

	}else{
		if (ilara.buff[proz].lehentasuna > prozesagailu.corekop[core].nun){
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait2[ilara.buff[proz].lehentasuna].zenbat++;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}else{
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat] = proz%MAX;
			prozesagailu.corekop[core].wait1[ilara.buff[proz].lehentasuna].zenbat++;
			printf("PID %d prozesua %d corean sartu da. \n",ilara.buff[proz].pid, core);
		}
	}
}


