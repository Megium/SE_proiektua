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


void *generateProcess_f(){
    //prozesuak sortzeko ausazko denboren hazia
	time_t t;
    srand((unsigned) time(&t));
    
    //Ilara objetua sortu eta hasieratu.
    extern struct queue ilara;
	ilara.indizea = 0;
    //Ilararen tamaina aldakora izango denez, ilara dinamiko bat sortu behar da.
    ilara.buff = malloc(MAX*sizeof(struct pcb));
	
    int i = 0;
	int d, l, c;
	
	while(1){

		d = rand() % (MAIZT%7);
		l = rand() % POSIZIO;
		c = rand() % 10;
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko
		if(d!=0){
			sleep(d);
            //Prozesu berri bat sortu, pcb motakoa
			struct pcb prozesu;

			//Prozesu berriari pid bat esleitu
			prozesu.pid = i;
			//prozesuari lehentasun bat esleitu ausaz
			prozesu.lehentasuna = l;
			prozesu.cuantum = c;
			prozesu.egoera = 1;

			sem_wait(&queue1);
            //bufferrean sartu beharreko prozesua sortzeko deia egin
			ilara.buff[i%MAX] = prozesu;
            //eguneratu indizea
			if(ilara.indizea == MAX){
				ilara.indizea = 0;
			}else{
				ilara.indizea++;
			}
            sem_post(&queue2);
			printf("%d. prozesua sortu da.\n", i);
			i++;
		}
		
	}


}



