//LIMIT 16 DONT FUCK UP 
#define NUMoBUF(a) ADCON2 |= ((a-1)<<2) 
#define NoB 1//ADC BUFFER
#define NoO 384//IN/OUT DATA BUFFER

extern void W2XS(int, volatile int **);
extern int RFXS(volatile int **);
extern void CLYS(volatile int **);


void inita2d(void);
void initPWMdac(void);
void clearIO(void);

void initXModBuff(volatile int **,int);
void setXMOD(int);
void clearBuff(volatile int **);
void wbyteBuff(int,volatile int **);
int  rbyteBuff(volatile int **);


