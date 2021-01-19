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

struct queue ilara;
void gorde(int core, struct pcb proz);

void *loader_f(){
    //prozesuak sortzeko ausazko denboren hazia
	time_t t;
    srand((unsigned) time(&t));
    
    //Ilara objetua sortu eta hasieratu.
    
	ilara.indizea = 0;
    //Ilararen tamaina aldakora izango denez, ilara dinamiko bat sortu behar da.
    ilara.buff = malloc(MAX*sizeof(struct pcb));
	

    int i = 1;
	int d, l, c, k, j, m, p;
	int kont=0;
	k=0;
	j=0;

	for (int p = 0; p < MAX; p++)
	{
		ilara.buff[p].erabilera = 1;
		ilara.buff[p].pid = 0;
	}

	while(1){
		d = rand();
		//d = rand() % (MAIZT%7);
		l = rand() % POSIZIO;
		c = rand() % 100000;
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
			
			irakurri(prozesu);

			printf("%d. prozesua sortu da. Iraupena %d\n", i, prozesu.iraupena);

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
					//printf("Errore[2]\n");
				}else{
					ilara.indizea++;
					//printf("Errore[3]\n");
				}
				pthread_mutex_unlock(&mutex2);
            }
			k=0;


			j++;
			i++;
		}	
	}
}

void gorde(int core, struct pcb proz){

	if(proz.pid != 0){
		if (prozesagailu.corekop[core].zein == 1){
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}else{
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}

		}else{
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}else{
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}
		}
	}
	
}

void irakurri(struct pcb proz){
	unsingend char bufData[12];
	unsingend char bufData[12];
	unsingend int buffer[8];
	char prog[12];
	
	size_t irakurritakoak;
	int k, kont, i, erren, text, data;
	struct memM hau;
	struct lag
	{
		char lerroa[];
	};
	struct lag testua[20];
	struct lag _text[20];
	struct lag _data[20];
	char kodea[];

//Programaren pid erabiliz programa bat edo beste irakurriko du.
	else if(proz.pid/100 >= 1){
		prog = {'p', 'r', 'o', 'g', zb+'0', '.', 'e', 'l', 'f'};
	}else if(proz.pid/10 >= 1){
		prog = {'p', 'r', 'o', 'g', '0', zb+'0', '.', 'e', 'l', 'f'};
	}else{
		prog = {'p', 'r', 'o', 'g', '0', '0', zb+'0', '.', 'e', 'l', 'f'};
	}

	FILE * fp;
	fp = fopen(prog, r);

	if(fp == NULL){
		printf("Errore bat %s programa irakurtzean \n", prog);
	}else{
		//.text eta .data lerroak irakurri eta hauen helbideak eskuratu.
		irakurritakoak = fread(bufText, sizeof(char), sizeof(bufText), fp);
		irakurritakoak = fread(bufData, sizeof(char), sizeof(bufData), fp);
		
		hau.text = bufText;
		hau.data = bufData;
		proz.mm = hau;

		erren = 0;
		while(!feof(fp)){
			irakurritakoak = fread(buffer, sizeof(int), sizeof(buffer) fp)
			testua[erren].lerroa = buffer;
			erren++;
		}

	//.text eta .data zatiak memoria nagusian gorde
	//.dataren helbide hamaseitarra gorde.
	for(i = 0; i<6; i++){
		kodea[i] = bufData[i+6];
	}
	//helbide hamaseitarra hamartarrera itzuli
	int zenbat = hamaseitarHamartar(kodea, 6);

	//_text eta _data .text eta .data kodeak gordetzeko estrukturak.
	for (i = 0; i < zenbat/4; i++)
	{
		_text[i] = testua[i];
		_data[i] = testua[i+(zenbat/4)];
	}


//Orri taulan libre dagoen posizio bat bilaten du eta
// prozesu bati esleitzen dio.
void orri_taula(struct pcb proz){

	int i, k;
	k = 0;
	for(i = 0; i < KERNEL; i++){
		if(nagusi[i] == -1){
			proz.mm.pgb = i;
			k = 1;
		}
	}
	if(k == 0){
		printf("Orri taulan ez dago lekurik!");
	}
}
	

//Hamaseitarrezko kateak dezimal bihurgailua.
int *hamaseitarHamartar(char zenb, int luzera) {
  int hamar = 0;
  int ber = 0;
  for (int i = luzera - 1; i >= 0; i--) {

    int balioa = hamaseiKarakterea(hamaseiKarakterea[i]);
    // 16 rekin handitu berretzailea eta balioarekin biderkatu.
    int goi = pow(16, potencia) * balioa;
 
    // Zenbakia gehitu
    hamar += goi;
    // Berretzailea handitu
    ber++;
  }
  return hamar;
}
//hamaseitarrak dauzkan karaktereak dezimaletara aldatu.
int *hamaseiKarakterea(char karak) {
  if (isdigit(karak))
    return karak - '0';
  return 10 + (toupper(karak) - 'A');
}

//Programaren kodea eta datuak memoria nagusian gordetzeko funtzioa
void programa_gorde(struct lag text, struct lag data, int pgb){
	int kodL = sizeof(testua);
	int datL = sizeof(data);
	int kont, k, bul, i, j, k;
	/*
	Leku nahikoa dagoen lehen tokian sartu bai kodea eta datua.
	Biak elkarren jarraian jarri ditut errazagoa izan dadin 
	datu egitura.
	*/
	for(i = KERNEL; i<sizeof(nagusi); i++){
		kont = 0;
		bul = 0;
		k = i;
		if(nagusi[i] == "-1"){
			while(kont<kodL+datL){
				if(nagusi[k] == "-1"){
					kont++;
				}else{
					bul = 1;
					kont = kodL+1;
				}
			}
			if(bul == 0){
				kont = 0;
				for (j = i; j < kodL; j++)
				{
					nagusi[j] = text[kont];
					kont++;
				}
				kont = 0;
				for (k = j; k < datL; k++)
				{
					nagusi[k] = data[kont];
					kont++;
				}
				bul = 2;
			}
		}
		if(bul == 2){
			//Orri taulan helbide birtuala eta fisikoa elkartu.
			nagusi[pgb] = i;
			break;
		}		
	}
}

	///////////////////////////////////////////////////////////////////