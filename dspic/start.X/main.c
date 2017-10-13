/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */

#include "xc.h"
#include "include/proj.h"

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

#define X_B  0x0900
#define FDB  0x0C00

#define DEL 256//<NoO
#define GAIN (1/4)
#define FBG  (1/4)
//

volatile int __attribute__((address(0x0800))) * x  = (volatile int *) X_B;
volatile int __attribute__((address(0x0802))) * f  = (volatile int *) FDB;
volatile int __attribute__((address(0x0804))) * fo = (volatile int *) FDB;
volatile int __attribute__((address(0x0806)))   currOut = 0;

void __attribute__((interrupt,auto_psv))_T2Interrupt (void) {
     int currIn,currFeed = 0;
     OC2RS = currOut;
     ADCON1 &= 0xFFFD;//start conversion
     while(!(ADCON1&&0x0001));
     currIn = ADCBUF0>>4;
     currFeed=rbyteBuff(&fo);
     currOut = currIn + GAIN*currFeed; 
     currFeed= currIn + FBG *currFeed;
     wbyteBuff(currFeed,&f);
     wbyteBuff(currIn,&x);
     ADCON1 |= 0x0002;//start sampling
     IFS0 &= 0xFFBF;
}


int main(void) { 
    clearIO();
    initXModBuff(x,10)

    clearBuff(&f);
    f = f + DEL;
    inita2d();
    initPWMdac(); 
   
    while (1) {
    }
    return 0;
}
