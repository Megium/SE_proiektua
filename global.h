extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern int POSIZIO;
extern int CORE;
extern int HARI;
extern int QUAN;
extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex2;
extern sem_t sche;
extern sem_t sinc;
extern sem_t sinc2;
extern struct queue ilara;
extern struct cpu prozesagailu;


//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;
int lehentasuna;
//Prozesuak exekutatzeko beharko duen denbora
int iraupena;
//1=zai, 2=exekuzioan, 3=Blokeatuta, 4=Exekutatua
int egoera;
//Prozesua core-ren batean dagoen ala ez. 0 = erabili gabe; 1 = core baten barruan
int erabilera;
//Prozesua ilaratik atera daiteken ala ez
int aldatu;
//Prozesuak exekuzioan daraman denbora
int pasatakoD;
//aurreago gauza gehio	
};

//Prozesuak sartzeko ilara, bertan buffer bat prozesuen informazioekin eta sorturiko prozesu kopuruarekin.
struct queue
{
	struct pcb *buff;
	int indizea;
};

struct priority
{
	//Lehentasun maila honetan zenbat prozesu dauden
	int zenbat;
	//Une honetan uneko lehentasunean zenbatgarren prozesuan doan
	int une;
	//Lehentasun bakoitzeko prozesu zerrenda, prozesuen id-ak gordeko ditu
	int zerrenda[20];
};


//Prozesagailearen egitura.
struct haria
{
	int hariID;
	int erabilgarri;
	int quantum;
	int prozesua;
};
struct core
{
	int coreID;
	struct haria *harikop;
	struct priority wait1[10];
	struct priority wait2[10];
	//zein azpi ilara erabiltzen ari den une honetan
	int zein;
	//azpi ilarako zenbatgarren "lehentasun" posizioan dagoen
	int nun;
};
struct cpu
{
	struct core *corekop;
};