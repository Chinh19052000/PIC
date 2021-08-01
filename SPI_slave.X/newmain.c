/*
 * File:   newmain.c
 * Author: Tuan Anh
 *
 * Created on January 25, 2021, 3:47 PM
 */

// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include "SPI.h"
#define _XTAL_FREQ 8000000

void __interrupt() SPI_Slave_Read()
{
  if(SSPIF == 1)
  {
    PORTD = SPI_read();
    SPI_sendData(PORTB);
    SSPIF = 0;
  }
}

void main()
{
  nRBPU = 0;    //cho phep dien tro keo len PORTB
  TRISB = 0xFF; //PORTB la input
  TRISD = 0x00; //PORTD la output
  PORTD = 0x00; //tat het led
  PORTB = 0xFF;
  ANSEL = ANSELH = 0;
  GIE = 1;      // cho phep ngat toan cuc
  PEIE = 1;     // cho phep ngat ngoai vi
  SSPIE = 1;    // cho phep ngat khoi MSSP
  SSPIF = 0;    // co bao ngat = 0
  ADCON1 = 0;   
  TRISA5 = 1;   // RA5 la input
  SPI_initialize(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
  while(1)
  {
    //Do something here
    __delay_ms(5);
  }
}
