/*
 * File:   main.c
 * Author: Tuan Anh
 *
 * Created on January 5, 2021, 10:31 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "led7.h"


void adc_init() {
    ADCON0 = 0x41; // cai dat thanh ghi ADCON0: bat che do ADC, voi tan so lay mau la Fosc/8
    ADCON1 = 0xF0; // 1111 0000, cai dat Vref voi chan AN3(+) va AN2(-)
}

double adc_readChannel(unsigned int channel) {
    if (channel > 13) return 0;
    ADCON0 &= 0xC1; // 1100 0001, xoa cac bit 2-5 cua thanh ghi ADCON0 
    ADCON0 |= channel << 2; // ghi gia tri kenh chon len cac bit 2-5 
    __delay_ms(2);
    GO_nDONE = 1; // dua bit Go/DONE len muc 1, bat dau chuyen doi ADC
    while (GO_nDONE); //cho qua trinh AD ket thuc thi bit GO/DONE se xuong muc 0 
    return ((ADRESH << 8) + ADRESL); // tra lai gia tri doc duoc vao 2 thanh ghi
}



void main() {
    double adc_input, volt, temp;
    TRISA0 = 1; // cai dat RA0 la input
    TRISC = 0x00; // cai dat output cho port C
    TRISD = 0x00; // cai dat output cho port D
    adc_init(); // khoi tao ADC
    while (1) {
        adc_input = adc_readChannel(0);// Doc gia tri ADC kenh AN0
        volt = adc_input * 5000.0 / 1023;//dien ap tham chieu ADC
        temp = volt / 10.0f; // gia tri nhiet do
        Led7_display(temp); // hien thi len LED 7 thanh
    }
}
