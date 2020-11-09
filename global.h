extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern int POSIZIO;
extern int CORE;
extern int HARI;
extern pthread_mutex_t mutex;
extern sem_t sche;ººº
extern sem_t sinc;
extern sem_t sinc2;
extern sem_t queue1;
extern sem_t queue2;
extern struct queue ilara;
extern volarile int sig;

//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;
int lehentasuna;
int cuantum;
//1=zai, 2=exekuzioan, 3=
int egoera;
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
	bool erabilgarri;
};
struct core
{
	int coreID
	struct haria *harikop;
};
struct cpu
{
	struct core *corekop;
};