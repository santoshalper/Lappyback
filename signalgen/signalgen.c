/************************************************************
*****Single supply signal generator**************************
*****By Vijay Natarajan and Charles Wolfe*******************
************************************************************/
//control message for digital pot
#define WRITEWIPE0 0x00
#define WRITEWIPE1 0x10
//inits for soft spi - needed for microc functions
sbit SoftSpi_SDI at RB4_bit;
sbit SoftSpi_SDO at RC7_bit;
sbit SoftSpi_CLK at RB6_bit;

sbit SoftSpi_SDI_Direction at TRISB4_bit;
sbit SoftSpi_SDO_Direction at TRISC7_bit;
sbit SoftSpi_CLK_Direction at TRISB6_bit;

int WiperValue = 0;


void set_pot(int value, int control) {
 //this function writes the value to the pot by first
 //sending the control message, then the value that
 //needs to be writen
     Soft_SPI_Write(control);
     Soft_SPI_Write(value);
}
void PrintAString(char string[]) {
       int k;
     for(k=0;string[k]!=0;k++) // Recall: String is an array terminated by zero
             Uart1_Write(string[k]);
}
float calcFrequency(int wiper) {
    float freq;
    if(wiper > 118) freq= 974.2+7.3455*(129-wiper);
    else if(wiper > 108) freq=969.4788+8.2788*(129-wiper);
    else if(wiper > 98) freq= 938.0636+9.8182*(129-wiper);
    else if(wiper > 88) freq= 906.1394+10.824*(129-wiper);
    else if(wiper > 78) freq= 789.6909+13.673*(129-wiper);
    else if(wiper > 68) freq= 601.3273+17.345*(129-wiper);
    else if(wiper > 58) freq= 396.1636+20.727*(129-wiper);
    else if(wiper > 48) freq= 28.151*(129-wiper)-127.7394;
    else if(wiper > 38) freq= 39.890*(129-wiper)-1078.273;
    else if(wiper > 28) freq= 58.370*(129-wiper)-2765.206;
    else if(wiper > 18) freq= 97*(129-wiper)-6672.4;
    return freq;
   }
char crlf[] = "\r\n";
char prompt[] = 
"Frequency:press a to raise,z to lower";
char freqValue[] = "value = ";
char error[] = "\r\nInvalid Entry\r\n";
char temp[10];
void main() {
      char input;
      int a;
      TRISC = 0xFF;
      TRISB = 0xFF;
      TRISA = 0xFF;
      ANSEL = 0x00;
      ANSELH = 0x00;
      C1ON_bit = 0;
      C2ON_bit = 0;
      Soft_SPI_Init();
      Uart1_Init(9600);
      INTCON = 0;
      for(a=0;  a<130; a++)
              Uart1_Write('a');
      set_pot(WiperValue,WRITEWIPE0);
      for(a=0;  a<130; a++)
              Uart1_Write('a');
      Delay_ms(2000);
      while(1){
               PrintAString(prompt);
               while(!Uart1_Data_Ready());
               input = Uart1_Read();
               if(input == 'a') {
                  if(WiperValue<128) WiperValue++;
                  set_pot(WiperValue,WRITEWIPE0);
                  set_pot(WiperValue,WRITEWIPE1);
               }
               else if(input == 'z') {
                  if(WiperValue>0) WiperValue--;
                  set_pot(WiperValue,WRITEWIPE0);
                  set_pot(WiperValue,WRITEWIPE1);
                }
               else PrintAString(error);
               PrintAstring(crlf);
               PrintAstring(freqValue);
               InttoStr(WiperValue,temp);
               PrintAString(temp);
               PrintAstring(crlf);
      }
}