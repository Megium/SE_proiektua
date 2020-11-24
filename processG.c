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

struct queue ilara;
void *gorde(int core, struct pcb proz);

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
		ilara.buff[k].erabilera = 1;
		ilara.buff[k].pid = 0;
	}

	while(1){
		d = rand();
		//d = rand() % (MAIZT%7);
		l = rand() % POSIZIO;
		c = rand() % 10000;
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko
		if(d!=0){
			sleep(d%2);
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
			printf("%d. prozesua sortu da.\n", i);

            //bufferrean sartu beharreko prozesua sortzeko deia egin
            while(k==0){
				pthread_mutex_lock(&mutex2);
            	if (ilara.buff[j%MAX].erabilera == 1){
					ilara.buff[j%MAX] = prozesu;
            		gorde(j%CORE, prozesu);
					ilara.indizea++;
            		k=1;
					//printf("Errore[1]\n");
				}else{
            		j++;
            	}if(ilara.indizea == MAX){
					ilara.indizea = 0;
					//printf("Errore[2]");
				}else{
					ilara.indizea++;
					//printf("Errore[3]");
				}
				pthread_mutex_unlock(&mutex2);
            }
			k=0;


			j++;
			i++;
		}	
	}
}

void *gorde(int core, struct pcb proz){

	if(proz.pid != 0){
		if (prozesagailu.corekop[core].zein == 1){
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat+1] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da. \n", proz.pid, core);
			}else{
				proz.erabilera = 1;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat+1] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d prozesua %d corean sartu da. \n",proz.pid, core);
			}

		}else{
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat+1] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d prozesua %d corean sartu da. \n",proz.pid, core);
			}else{
				proz.erabilera = 1;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat+1] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da. \n",proz.pid, core);
			}
		}
	}
	
}


