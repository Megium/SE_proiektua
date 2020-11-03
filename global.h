extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern int POSIZIO;
extern pthread_mutex_t mutex;
extern sem_t sche;
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