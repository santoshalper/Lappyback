/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */


#include "xc.h"

int main(void) {
    int count = 0x0000;
    int delay = 0x0000;
    TRISA = 0x0000;
    TRISB = 0x1000;
    PORTB = 0x0000;
    TRISC = 0x0000;
    PORTD = 0x0000;
    TRISD = 0x0000;
    TRISF = 0x0000;
    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
    PORTBbits.RB7 = 1;
    PORTBbits.RB8 = 1;
    PORTBbits.RB9 = 1;
    PORTBbits.RB10 = 1;
    PORTBbits.RB11 = 1;
    PORTB = 0x0000;
    
    while (1) {
        if(PORTBbits.RB12 == 1) {
            count++;
            switch (count) {
                case 1:
                    PORTB = 0x0001;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    PORTB <<= 1;
                    break;
                case 7:
                    PORTB = 0x0000;
                    PORTBbits.RB8 = 1;
                    break;
                case 8:
                case 9:
                case 10:
                    PORTB <<= 1;
                    break;                    
                case 11:
                    PORTB = 0x0000;
                    PORTD = 0x0001;
                    break;                    
                case 12:
                case 13:
                case 14:
                    PORTD <<= 1;
                    break;                   
                case 15:
                    PORTD = 0x0000;
                    PORTF = 0x0001;
                    break;                 
                case 16:
                case 17:
                case 18:
                    PORTF <<= 1;
                    break;
                case 19:
                    PORTF = 0x0000;
                    count = 0x0000;
                    break;
            }
            while(delay < 0xC000) delay++;
            delay = 0x0000;   
           }
    }
    return 0;
}












































































