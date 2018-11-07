sbit SoftSpi_SDI at RB4_bit;
sbit SoftSpi_CLK at RB6_bit;

sbit SoftSpi_SDI_Direction at TRISB4_bit;
sbit SoftSpi_CLK_Direction at TRISB6_bit;

void main() {
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
