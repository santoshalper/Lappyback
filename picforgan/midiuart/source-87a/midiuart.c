#include "midi.h"

#define COLN 8
#define ROWN 2
#define SETN 8 // final
//chord types
#define MAJ        0        
#define MIN         1
#define DIM        2
#define AUG        3
#define PWR     4
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
int col=COLN;
volatile int curr = COLN;
int row = 0;
int octu = 4;

int inv=0;
int chordtype = MAJ;

void midi_write(char type, char chnl, char data1, char data2) {
       Uart1_Write(type+chnl);
       Uart1_Write(data1&DATA_MSK);
       Uart1_Write(data2&DATA_MSK);
}
void main() {
        TRISA = 0x00;
        TRISB = 0xFF;
        TRISC = 0x03;
        PORTA = 0x00;
        PORTC = 0x00;
        OPTION_REG = 0x80
        Uart1_Init(31250);
        IOCB = 0xC0;
        INTCON |= 0x88;
        while(1){
                col--;
                PORTA = 1<<(col);
                Delay_us(200);
                if(col == 0) col = COLN;
        }
}
void Interrupt() {
      int ext,set = 0;
      if(PORTB.b7) row = 0;
      else row = 1;
      key = (8*row+col+1);
      note = ((key-1)%12);
      oct = ((key-1)/12 + octu);
      chordtype = MAJ;
      vel =0x60;
      inv = 0;
      if(PORTB.b0) chordtype = MIN;
      else if(PORTB.b1 || PORTB.b2) {
             inv = 1;
             if(PORTB.b2) chordtype = MIN;
      }
      else if(PORTB.b3 || PORTB.B4) {
            inv = 2;
            if(PORTB.b4) chordtype = MIN;
      }
      else if(PORTB.b5) chordtype = DIM;
      else if(PORTC.b0) chordtype = AUG;
      else if(PORTC.b1) chordtype = PWR;
      triad[0] = NOTE(note,oct);
      triad[1] = triad[0]+4;
      triad[2] = triad[1]+3;
      if(inv>0) {
         triad[0] += 0x0C;
         if(inv>1) triad[1] += 0x0C;
      }
      if (chordtype>MAJ) {
         if(chordtype< AUG) {
           triad[1] -= 1;
           if(chordtype > MIN) triad[2] -=1;
         }
         if(chordtype == AUG) triad[2] += 1;
         if(chordtype == PWR) triad[1] -= 2;
      }

      midi_write(NOTE_ON,chan,triad[0], vel);
      midi_write(NOTE_ON,chan,triad[1], vel);
      midi_write(NOTE_ON,chan,triad[2], vel);
      while(PORTB.b6 || PORTB.b7);
      midi_write(NOTE_OFF,chan,triad[0], vel);
      midi_write(NOTE_OFF,chan,triad[1], vel);
      midi_write(NOTE_OFF,chan,triad[2], vel);
      INTCON &= 0xFE;
}