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
//Prozesuak exekuzioan daraman denbora
int pasatakoD;
//Memory managenment	
struct memM mm;
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
	struct pcb zerrenda[20];
};


//Prozesagailearen egitura.
struct haria
{
	int hariID;
	int erabilgarri;
	int quantum;
	struct pcb prozesua;
	//Memoria kudeatzeko hardwarea:
	struct mmuStr mmu;
	char[] pc;
	char[] ir;
	char[] ptbr;
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

struct memM
{
	//datuen segmentuaren helbide birtula
	char[] data;
	//kodearen segmentuaren helbide birtuala
	char[] code;
	//orri-taularen helbide fisikoa
	char[] pgb;
};

struct mmuSrt
{
	struct tlbBuffer tlb[];
};

struct tlbBuffer
{
	//TLB barruko taulak 2 parametro ditu, beraz taulako aldagai bakoitzean orri-zenbaki bakoitzari dagokion marko-zenbakia.
	struct barneTlb taula[];
};

struct barneTlb
{
	char[] orriZ;
	char[] markoZ;
};