/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */

#include "xc.h"
#include "proj.h"

// DSPIC30F3014 Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = FRC_PLL16       // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)
// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF             // Watchdog Timer (Enabled)
// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)
// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define X_B  0x0A00
#define FDB  0x0B00
#define Y_B  0x0C00

#define DEL 32//<NoO
#define GAIN (1/2)
#define FDG  (1/2)
//

volatile int __attribute__((address(0x0800))) * x  = (volatile int *) X_B;
volatile int __attribute__((address(0x0802))) * xo = (volatile int *) X_B;
volatile int __attribute__((address(0x0804))) * f  = (volatile int *) FDB;
volatile int __attribute__((address(0x0806))) * fo = (volatile int *) FDB;
volatile int __attribute__((address(0x0808))) * y  = (volatile int *) Y_B;
volatile int __attribute__((address(0x080A))) * yo = (volatile int *) Y_B;

void __attribute__((interrupt,auto_psv))_T2Interrupt (void) {
    OC2RS = rbyteBuff(yo);
    IFS0 &= 0xFFBF;
}

void __attribute__((interrupt,auto_psv))_ADCInterrupt (void) {
    int temp=0;
    volatile int lastModB;
    while(!(ADCON1&&0x0001));
    lastModB = XMODSRT;
    setXMOD(X_B);
    for(int i=0;i<NoB; i++) {
      temp = *((&ADCBUF0)+i) >> 4;
      W2XS(temp,&x);
    }
    setXMOD(lastModB);	
    IFS0 &= 0xF7FF;
}


int main(void) { 
    int currIn,currFeed,currOut = 0;
    clearIO();
    initModBuff(x,y,10,11);   
    f = f + DEL;
    clearBuff(f);
    inita2d();
    initPWMdac(); 
   
    while (1) {
        currIn   = rbyteBuff(xo);
        currFeed = rbyteBuff(fo);
        currOut  = currIn + GAIN*currFeed;
        currFeed = currIn + FBG *currFeed;
        wbyteBuff(currOut,y);
        wbyteBuff(currFeed,f);
    }
    return 0;
}
