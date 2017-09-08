#line 1 "C:/projects/pickupwinder/PickupWinder.c"
char crlf[] = "\r\n";
char script[] = "speed = ";
char script2[] = "counter = ";

unsigned int foot;
unsigned short duty = 0;
unsigned int counter=0;
int slow = 0;
void PrintAString(char string[]) {
 int k;
 for(k=0;string[k]!=0;k++)
 Uart1_Write(string[k]);
}
char temp[10];

void main() {
TRISA = 0X14;
TRISB = 0x00;
TRISC = 0x00;
PORTC = 0x00;
ANSEL = 0x04;
C1ON_bit = 0;
C2ON_bit = 0;
Uart1_Init(9600);
PWM1_Init(5000);
INTCON |= 0x90;
OPTION_REG |= 0x40;
PWM1_Start();
PWM1_Set_Duty(duty);
while(1) {
 foot = ADC_Read(3)/3;
 if(counter < 50) {
 duty = (short)foot;
 if(duty<60) duty = 0;
 PWM1_Set_Duty(duty);
 }
 else PWM1_Set_Duty(0);
 PrintAstring(script);
 InttoStr(foot,temp);
 PrintAString(temp);
 PrintAstring(script2);
 InttoStr(counter,temp);
 PrintAString(temp);
 PrintAstring(crlf);
 }
}
void interrupt() {
 counter ++;
 INTCON.INTF = 0;
 }
