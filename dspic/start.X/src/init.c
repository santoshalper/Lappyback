#include "xc.h"
#include "proj.h"

void clearIO(void) {
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


