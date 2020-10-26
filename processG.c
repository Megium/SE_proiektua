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


//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;
//aurreago gauza gehio	
};

//Prozesuak sartzeko ilara, bertan buffer bat prozesuen informazioekin.
struct queue
{
	struct pcb buff[];
	int indizea;
};

void generate(int id, struct pcb *prozesu);

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

		d = rand() % MAIZT;
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko
		if(d!=0){
            //Prozesu berri bat sortu, pcb tamainakoa
			struct pcb prozesu = malloc(1*sizeof(struct pcb));
            //bufferrean sartu beharreko prozesua sortzeko deia egin
			ilara.buff[i] = generate(i, prozesu);
            //eguneratu indizea
			ilara.indizea++;
            
			printf("%d. prozesua sortu da.\n", i);
			i++;
		}
		
	}


}

//Prozesu berri bat sortu, pcb motako struct berri bat eta bertan honen id-a
void generate(int id, struct pcb *prozesu){
	prozesu->pid = id;
}
