/*
 * File:   main.c
 * Author: Vijay Natarajan
 *
 * Created on August 7, 2017, 4:20 PM
 */


#include "xc.h"

int main(void) {
    TRISA = 0x0000;
    TRISB = 0x1000; // Rb12 set to input to be analog in. 
    TRISC = 0x0000;
    TRISD = 0x0000;
    TRISF = 0x0000;

    PORTA = 0x0000;
    PORTB = 0x0000;
    PORTC = 0x0000;
    PORTD = 0x0000;
    PORTF = 0x0000;

    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
       
    while (1) {
    }
    return 0;
}












































































