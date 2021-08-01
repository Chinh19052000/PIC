/*
 * File:   timer.c
 * Author: Tuan Anh
 *
 * Created on January 7, 2021, 10:58 PM
 */

#include <xc.h>
#include "led7.h"
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

//void delayTimer0_ms(unsigned int t) 
//{
//    while (t--) 
//    {
//        TMR0 = 5;
//        INTCONbits.T0IF = 0;
//        while(!INTCONbits.T0IF); // de treo chuong trinh
//    }
//}

//void __interrupt() isr1() 
//{
//    if (INTCONbits.T0IF == 1) // phat hien co bao ngat 
//    {
//        TMR0 = 5;
//        INTCONbits.T0IF = 0; // dua co bao ngat ve gia tri 0
//        cnt ++;
//        if(cnt == 1000) // khi timer dem du 1s
//        {
//            PORTC = ~PORTC;
//            cnt = 0;
//        }
//    }
//}
//void controlRelay(char relay, char state)
//{
//    if(cnt == 100)
//    {
//        PORTD 
//    }
//}
void main(void) 
{    
    TRISC0 = 1;             // chan C0 la input de lay nguon xung ngoai
    T1CONbits.TMR1CS = 1;   // nguon xung ngoai
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;  // bo chia ty le 1:1
    T1CONbits.TMR1ON = 1;   // bat dau cho timer 1 dem
    TMR1H = TMR1L = 0;  
    TRISD = 0;
    TRISB = 0;
    ADCON1 |= 0x07; // khong cho phep che do ADC 
    while (1)
    {
        unsigned int cnt; 
        cnt = TMR1H;  // ghi 8 bit dau tien 
        cnt <<= 8;     // 
        cnt |= TMR1L;
        Led7_display(cnt);
    }
}

