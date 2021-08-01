/*
 * File:   main.c
 * Author: Tuan Anh
 *
 * Created on January 28, 2021, 8:18 PM
 */

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = ON       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF        // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = OFF       // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = ON      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF      // Flash Program Memory Self Write Enable bits (0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "ADC.h"
#include"led7.h"

static unsigned char adc_value, saved_adc_value = 0;

void main(void) {
    double volt, temp;
    TRISA = 0xFF; // cau hinh input
    TRISB = 0xFF; // cau hinh input
    TRISC = 0; // cau hinh output
    TRISD = 0; // cau hinh output
    ANSELH = 0; // tat che do ngo ra tuong tu port B
    adc_init(); // khoi tao ADC
    while (1) {
        adc_value = (unsigned char) adc_readChannel(0); // lay gia tri tu kenh AN0
        if (RB0 == 0) {
            eeprom_write(0, adc_value); // ghi gia tri doc duoc cua adc vao dia chi 0 cua EEPROM
        }
        if (RB4 == 0) {
            eeprom_write(0, 0); // ghi gia tri 0 vao dia chi 0 cua EEPROM
        }
        saved_adc_value = (double) eeprom_read(0); // doc gia tri tu dia chi 0 cua EEPROM
        volt = saved_adc_value * 5000.0 / 1023;
        temp = volt / 10.0f;
        Led7_display(temp);

    }
}
