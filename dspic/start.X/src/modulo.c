#include "xc.h"
#include "proj.h"
void initModBuff(volatile int * xi, volatile int * yi, int RegX, int RegY) {
    int mask = 0xC000
    mask |= RegX;
    mask |= RegY<<4;

    XMODSRT = (int) xi;
    XMODEND = ((int) xi)+(NoO*2)-1;
    YMODSRT = (int) yi;
    YMODEND = ((int) yi)+(NoO*2)-1;
    MODCON  = MASK;
    asm ("nop");

    for(int i=0; i<NoO; i++) {
        W2XS(0,&xi);
        CLYS(&yi);
    }
}
void setXMOD(int buff) {
	XMODSRT = buff;
        XMODEND = buff + (NoO*2)-1;
        asm ("nop");   
}
void clearBuff(volatile int * buff) {
	setXMOD((int) buff);
        for(int i=0; i<NoO;i++)
          W2XS(0,&buff);
}
void wbyteBuff(int val, volatile int * buff) {
        volatile int lastModB;
        lastModB = XMODSRT;
	setXMOD((int) buff);
        W2XS(val,&buff);
        setXMOD(lastModB);
}
int  rbyteBuff(volatile int * buff) {
        volatile int lastModB;
        int temp;
        lastModB = XMODSRT;
	setXMOD((int) buff);
        temp = RFXS(&buff);
        setXMOD(lastModB);
        return temp;
}
