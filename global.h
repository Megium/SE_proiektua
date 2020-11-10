extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern int POSIZIO;
extern int CORE;
extern int HARI;
extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex2;
extern sem_t sche;
extern sem_t sinc;
extern sem_t coreT;
extern volatile struct queue ilara;
extern struct cpu prozesagailu;


//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;
int lehentasuna;
int iraupena;
//1=zai, 2=exekuzioan, 3=Blokeatuta
int egoera;
int erabilera;
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
	int zenbat;
	struct pcb zerrenda[20];
};


//Prozesagailearen egitura.
struct haria
{
	int hariID;
	int erabilgarri;
};
struct core
{
	int coreID;
	struct haria *harikop;
	struct priority wait1[10];
	struct priority wait2[10];
	int zein;
	int nun;
};
struct cpu
{
	struct core *corekop;
};