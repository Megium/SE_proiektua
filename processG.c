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



struct pcb
{
int pid;
//aurreago gauza gehio	
};

struct queue
{
	struct pcb buff[MAX];
	int indizea;
};

void generate(int id, struct pcb *prozesu);

void *generateProcess_f(){
	time_t t;
	struct queue ilara;
	ilara.indizea = 0;
	int i = 0;
	int d;
	srand((unsigned) time(&t));
	while(1){

		d = rand() % MAIZT;
		if(d!=0){
			struct pcb prozesu = malloc(1*sizeof(struct pcb));
			ilara.buff[i] = generate(i, prozesu);
			ilara.indizea++;
			printf("%d. prozesua sortu da.\n", i);
			i++;
		}
		
	}


}

void generate(int id, struct pcb *prozesu){
	prozesu->pid = id;
}