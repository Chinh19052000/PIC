/*
 * File:   pwm.c
 * Author: DELL
 *
 * Created on January 10, 2021, 10:35 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 8000000
#define TMR2PRESCALE 4

#include <xc.h>

long PWM_freq = 5000;

void PWM1_Init() {
    PR2 = (_XTAL_FREQ /(PWM_freq * 4 * TMR2PRESCALE)) - 1; //Ghi gia tri cho thanh ghi PR2
    // cai che do PWM cho khoi CCP1
    CCP1M3 = 1;
    CCP1M2 = 1; 
    // chon bo chia 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    TMR2ON = 1; // cho timer 2 bat dau dem
    TRISC2 = 0; // chan RC2 la output
}

void PWM1_dutyCycle(unsigned int duty) {
    if (duty < 1023) {      
        duty = ((float)duty /1023)*(_XTAL_FREQ /(PWM_freq * TMR2PRESCALE)); 
        CCP1X = duty & 1;// ghi 2 bit vao CCP1CON<5:4>
        CCP1Y = duty & 2;
        CCPR1L = duty >> 2; // ghi 8 bit vao CCPR1L
    }
    return;
}

void ADC_Init() {
    ADCON0 = 0x41; //ADC ON and Fosc/16 is selected
    ADCON1 = 0xC0; // Internal reference voltage is selected
}

double ADC_readChannel(unsigned char channel) {
    if (channel > 13) return 0;
    ADCON0 &= 0xC5; //Clearing the Channel Selection Bits
    ADCON0 |= channel << 3; //Setting the required Bits
    __delay_ms(2); //Acquisition time to charge hold capacitor
    GO_nDONE = 1; //Initializes A/D Conversion
    while (GO_nDONE); //Wait for A/D Conversion to complete
    return ((ADRESH << 8) + ADRESL); //Returns Result
}

void main() {
    double adc_value;
    TRISA0 = 1; //chan A0 la input
    ADC_Init(); //khoi tao ADC
    PWM1_Init(); //khoi tao pwm cho khoi CCP1
    while (1){
        adc_value = ADC_readChannel(0); 
        PWM1_dutyCycle(adc_value);
        __delay_ms(50);
    }  
}