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

void generate(int id, struct pcb *prozesu);

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

struct queue ilara;

ilara.indizea = 0;
time_t t;

srand((unsigned) time(&t));

void *generateProcess_f(){
	int i = 0;
	int t;
	while(1){

		t = rand() % MAIZT;
		if(t!=0){
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