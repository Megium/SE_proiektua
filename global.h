extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern pthread_mutex_t mutex;
extern sem_t sche;
extern sem_t sinc;
extern sem_t sinc2;
extern struct queue ilara;

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