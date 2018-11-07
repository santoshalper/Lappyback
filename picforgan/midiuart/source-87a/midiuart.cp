#line 1 "C:/projects/repository/picforgan/midiuart/source/midiuart.c"
#line 1 "c:/projects/repository/picforgan/midiuart/source/midi.h"
#line 12 "C:/projects/repository/picforgan/midiuart/source/midiuart.c"
sbit SoftSpi_SDI at RB4_bit;
sbit SoftSpi_SDO at RB5_bit;
sbit SoftSpi_CLK at RB6_bit;
sbit SoftSpi_SDI_Direction at TRISB4_bit;
sbit SoftSpi_SDO_Direction at TRISB5_bit;
sbit SoftSpi_CLK_Direction at TRISB6_bit;

int key=0;
char note=0;
char oct=0;
char chan=0;
char vel=0;
char triad[3] = {0x00,0x00,0x00};
int col= 8 ;
volatile int curr =  8 ;
int row = 0;
int octu = 4;

int inv=0;
int chordtype =  0 ;

void midi_write(char type, char chnl, char data1, char data2) {
 Uart1_Write(type+chnl);
 Uart1_Write(data1& (char)0x7F );
 Uart1_Write(data2& (char)0x7F );
}
void main() {
 TRISA = 0x00;
 TRISB = 0xFF;
 TRISC = 0x03;
 PORTA = 0x00;
 PORTC = 0x00;
 ANSEL = 0x00;
 ANSELH = 0x00;
 C1ON_bit = 0;
 C2ON_bit = 0;
 WPUB = 0x00;
 Uart1_Init(31250);
 IOCB = 0xC0;
 INTCON |= 0x88;
 while(1){
 col--;
 PORTA = 1<<(col);
 Delay_us(200);
 if(col == 0) col =  8 ;
 }
}
void Interrupt() {
 int ext,set = 0;
 if(PORTB.b7) row = 0;
 else row = 1;
 key = (8*row+col+1);
 note = ((key-1)%12);
 oct = ((key-1)/12 + octu);
 chordtype =  0 ;
 vel =0x60;
 inv = 0;
 if(PORTB.b0) chordtype =  1 ;
 else if(PORTB.b1 || PORTB.b2) {
 inv = 1;
 if(PORTB.b2) chordtype =  1 ;
 }
 else if(PORTB.b3 || PORTB.B4) {
 inv = 2;
 if(PORTB.b4) chordtype =  1 ;
 }
 else if(PORTB.b5) chordtype =  2 ;
 else if(PORTC.b0) chordtype =  3 ;
 else if(PORTC.b1) chordtype =  4 ;
 triad[0] =  (char)((note+(oct*0x0C))&0X7F) ;
 triad[1] = triad[0]+4;
 triad[2] = triad[1]+3;
 if(inv>0) {
 triad[0] += 0x0C;
 if(inv>1) triad[1] += 0x0C;
 }
 if (chordtype> 0 ) {
 if(chordtype<  3 ) {
 triad[1] -= 1;
 if(chordtype >  1 ) triad[2] -=1;
 }
 if(chordtype ==  3 ) triad[2] += 1;
 if(chordtype ==  4 ) triad[1] -= 2;
 }

 midi_write( (char)0x90 ,chan,triad[0], vel);
 midi_write( (char)0x90 ,chan,triad[1], vel);
 midi_write( (char)0x90 ,chan,triad[2], vel);
 while(PORTB.b6 || PORTB.b7);
 midi_write( (char)0x80 ,chan,triad[0], vel);
 midi_write( (char)0x80 ,chan,triad[1], vel);
 midi_write( (char)0x80 ,chan,triad[2], vel);
 INTCON &= 0xFE;
}
