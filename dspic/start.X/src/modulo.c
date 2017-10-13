#include "xc.h"
#include "../include/proj.h"

void initModBuff(volatile int ** xi, int RegX) {
    int mask = 0x8000;
 
    mask |= RegX;

    XMODSRT = (int) *xi;
    XMODEND = ((int) *xi)+(NoO*2)-1;
    MODCON  = mask;
    asm ("nop");

    for(int i=0; i<NoO; i++) 
        W2XS(0,xi);
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
    setXMOD((int) *buff);
    W2XS(val,buff);
}
int  rbyteBuff(volatile int ** buff) {
     int temp;
	 setXMOD((int) *buff);
     temp = RFXS(buff);
     return temp;
}
