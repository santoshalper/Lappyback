/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */


#include "xc.h"

//LIMIT 16 DONT FUCK UP 
#define NUMoBUF(a) ADCON2 |= ((a-1)<<2) 
#define NoB 15
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
void initIntA2d(void);

int x[NoB];

void __attribute__((interrupt,auto_psv))_ADCInterrupt (void) {
	while(!(ADCON1&&0x0001));
    for(int i=0; i<NoB; i++)
        x[i] = *((&ADCBUF0) + i);
    PORTD ^= 0x0001;
    
    
	IFS0 &= 0xF7FF;
}

int main(void) {
    int m=0;
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

    inita2d();
      
    while (1) {
        while (m<10) m++;
        m = 0;
        PORTC ^= 0x8000;
    }
    return 0;
}


void inita2d(void) {

    TRISB |= 0x1000; // Rb12/AN12 set to input  

    ADCON1 = 0x0000; //ADON = 0    

    ADCON1 = 0x00E4; //Auto sampling/Auto Conversion;
    ADCON2 = 0x0000;
    NUMoBUF(NoB);
    ADCON3 = 0x0129; //set sampling rate to 95Khz
    ADCHS  = 0x000c; //Assign AN12 to chanel A
    ADPCFG = 0x0FFF; //RB12/AN12 set to analog in
    ADCSSL = 0x0000; //Not Doing Scan In. 	

//Clear I/O ports pre activation
    PORTB = 0x0000;
    initIntA2d();
    ADCON1 |= 0x8000; //turn on adc
}     

void initIntA2d() {
     IPC2 = 0X6000; 
     IEC0 = 0x0800; //adc int set
}









































































