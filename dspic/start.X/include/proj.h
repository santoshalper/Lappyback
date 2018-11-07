//LIMIT 16 DONT FUCK UP 
#define NUMoBUF(a) ADCON2 |= ((a-1)<<2) 
#define NoB 1//ADC BUFFER
#define NoO 384//IN/OUT DATA BUFFER
#define NoOy 512//IN/OUT DATA BUFFER

#define X_B  0x0900
#define Y_B  0x0C00

extern void W2XS(int, volatile int **);
extern int RFXS(volatile int **);
<<<<<<< HEAD
=======
extern void CLYS(volatile int **);

>>>>>>> 4e35d1952ec0a293fbc6729cb0f7a99bd6f5d53d

void inita2d(void);
void initPWMdac(void);
void clearIO(void);
void initXModBuff(volatile int **,int);
void initUModBuff(volatile int **);
void wbyteUBuff(int,volatile int **);
int  rbyteUBuff(volatile int **);


