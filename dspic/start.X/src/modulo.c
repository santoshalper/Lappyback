#include "xc.h"
#include "../include/proj.h"

int __attribute__((address(0x090C))) modflag = 0;
void initModBuff(volatile int * xi, volatile int * yi, int RegX, int RegY) {
    int mask = 0xC000;
    mask |= RegX;
    mask |= RegY<<4;

    XMODSRT = (int) xi;
    XMODEND = ((int) xi)+(NoO*2)-1;
    YMODSRT = (int) yi;
    YMODEND = ((int) yi)+(NoO*2)-1;
    MODCON  = mask;
    asm ("nop");

    for(int i=0; i<NoO; i++) {
        W2XS(0,&xi);
        CLYS(&yi);
    }
}
void setXMOD(int buff) {
    XMODSRT = (buff&0xF00);
    XMODEND = (buff&0xF00) + (NoO*2)-1;
    asm ("nop");   
}
void clearBuff(volatile int ** buff) {
	setXMOD((int) *buff);
    for(int i=0; i<NoO;i++)
       W2XS(0,buff);
}
void wbyteBuff(int val, volatile int ** buff) {
	modflag = 1;
    setXMOD((int) *buff);
    W2XS(val,buff);
    modflag = 0;
}
int  rbyteBuff(volatile int ** buff) {
     int temp;
     modflag = 1;
	 setXMOD((int) *buff);
     temp = RFXS(buff);
     modflag = 0;
     return temp;
}
