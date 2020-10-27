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

//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;
//aurreago gauza gehio	
};

//Prozesuak sartzeko ilara, bertan buffer bat prozesuen informazioekin eta sorturiko prozesu kopuruarekin.
struct queue
{
	struct pcb *buff;
	int indizea;
};


void *generateProcess_f(){
    //prozesuak sortzeko ausazko denboren hazia
	time_t t;
    srand((unsigned) time(&t));
    
    //Ilara objetua sortu eta hasieratu.
    struct queue ilara;
	ilara.indizea = 0;
    //Ilararen tamaina aldakora izango denez, ilara dinamiko bat sortu behar da.
    ilara.buff = malloc(MAX*sizeof(struct pcb));
	
    int i = 0;
	int d;
	
	while(1){

		d = rand() % (MAIZT%7);
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko
		if(d!=0){
			sleep(d);
            //Prozesu berri bat sortu, pcb motakoa
			struct pcb prozesu;

			//Prozesu berriari pid bat esleitu
			prozesu.pid = i;

            //bufferrean sartu beharreko prozesua sortzeko deia egin
			ilara.buff[i] = prozesu;
            //eguneratu indizea
			ilara.indizea++;
            
			printf("%d. prozesua sortu da.\n", i);
			i++;
		}
		
	}


}



