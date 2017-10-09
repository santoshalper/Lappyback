/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */


#include "xc.h"
#include <libpic30.h>

//LIMIT 16 DONT FUCK UP 
#define NUMoBUF(a) ADCON2 |= ((a-1)<<2) 
#define NoB 16 //ADC BUFFER
#define NoO 64//IN/OUT DATA BUFFER
//

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

void inita2d(void);
void initPWMdac(void);
extern void InpB(int, volatile int **);
extern void W2OB(int, volatile int **);
extern int R2OB(volatile int **);


volatile int __attribute__((address(0x0900))) * x  = (volatile int *) 0x0800;
//volatile int __attribute__((address(0x0902))) * y = (volatile int *) 0x0C00;
volatile int __attribute__((address(0x0906))) * xo = (volatile int *) 0x0800;
volatile int y = 0;

void __attribute__((interrupt,auto_psv))_T2Interrupt (void) {
    OC2RS = y;  
    IFS0 &= 0xFFBF;
}

void __attribute__((interrupt,auto_psv))_ADCInterrupt (void) {
    int temp=0; 
    while(!(ADCON1&&0x0001));
    for(int i=0;i<NoB; i++) {
      temp = *((&ADCBUF0)+i);
      InpB(temp,&x);
    }
    IFS0 &= 0xF7FF;
}


int main(void) {
//set all i/o to digital
    TRISA = 0x0000;
    TRISB = 0x0000;
    TRISC = 0x0000;
    TRISD = 0x0000;
    TRISF = 0x0000;
    
    PORTA = 0x0000;
    PORTB = 0x0000;
    PORTC = 0x0000;
    PORTD = 0x0000;
    PORTF = 0x0000;
    
    XMODSRT = (int) x;
    XMODEND = ((int) x)+(NoO*2)-1;
    YMODSRT = (int) y;
    YMODEND = ((int) y)+(NoO*2)-1;
    MODCON  = 0xC0BA;
    asm ("nop");
    for(int i=0; i<NoO; i++) {
        InpB(0,&x);
    }
  
    inita2d();
    initPWMdac(); 
   
    while (1) {
        y = (R2OB(&xo)) >>4;
    }
    return 0;
}


void inita2d(void) {

    TRISB |= 0x1000; // Rb12/AN12 set to input  

    ADCON1 = 0x0000; //ADON = 0    

    ADCON1 = 0x00E4; //Auto sampling/Auto Conversion;
    ADCON2 = 0x00000;   
    NUMoBUF(NoB);
    ADCON3 = 0x0129; //set sampling rate to 95Khz
    ADCHS  = 0x000c; //Assign AN12 to chanel A
    ADPCFG = 0x0FFF; //RB12/AN12 set to analog in
    ADCSSL = 0x0000; //Not Doing Scan In. 	

//Clear I/O ports pre activation
    PORTB = 0x0000;
      
    IPC2 |= 0X6000; 
    IFS0 &= 0xF7FF;
    IEC0 |= 0x0800; //adc int set


    ADCON1 |= 0x8000; //turn on adc
} 

void initPWMdac(void) {   
     OC2CON = 0x0006; //PWM MODE No fault protection TMR2 Selected
     T2CON = 0x0000;
     PR2 = 0x00FF;
     IPC1 |=0x0500;
     IFS0 &= 0xFFBF;
     IEC0 |= 0x0040;
     TRISD &= 0xFFFD;
     	 
     OC2RS = 0x0000; //Init PWM duty cycle to 0%
     OC2R = 0x0000;
     T2CON |= 0x8000;
}


              









































































