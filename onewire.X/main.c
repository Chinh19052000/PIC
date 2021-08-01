/*
 * File:   main.c
 * Author: DELL
 *
 * Created on February 2, 2021, 4:25 PM
 */

// CONFIG1
#pragma config FOSC = LP        // Oscillator Selection bits (LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = ON          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF       // Flash Program Memory Self Write Enable bits (0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdint.h>
#include "PIC_18DSB20.h"
#include "lcd.h"
uint16_t raw_temp;
char temp[] = "000.0000 C";

void main(void) {
    ANSELH = 0;
    __delay_ms(1000); // wait 1 second
    LCD_begin(); // initialize LCD module
    LCD_goTo(3, 1); // move cursor to column 3, row 1
    LCD_print("Temperature:");
    temp[8] = 223; // put degree symbol ( ° )
    while (1) {
        if (ds18b20_read(&raw_temp)) {
            if (raw_temp & 0x8000) // if the temperature is negative
            {
                temp[0] = '-'; // put minus sign (-)
                raw_temp = (~raw_temp) + 1; // change temperature value to positive form
            }
            else {
                if ((raw_temp >> 4) >= 100) // if the temperature >= 100 °C
                    temp[0] = '1'; // put 1 of hundreds
                else // otherwise
                    temp[0] = ' '; // put space ' '
            }
            // put the first two digits ( for tens and ones)
            temp[1] = ((raw_temp >> 4) / 10) % 10 + '0'; // put tens digit
            temp[2] = (raw_temp >> 4) % 10 + '0'; // put ones digit

            // put the 4 fraction digits (digits after the point)
            temp[4] = ((raw_temp & 0x0F) * 625) / 1000 + '0'; // put thousands digit
            temp[5] = (((raw_temp & 0x0F) * 625) / 100) % 10 + '0'; // put hundreds digit
            temp[6] = (((raw_temp & 0x0F) * 625) / 10) % 10 + '0'; // put tens digit
            temp[7] = ((raw_temp & 0x0F) * 625) % 10 + '0'; // put ones digit

            LCD_goTo(4, 2); // move cursor to column 4 row 2
            LCD_print(temp); // print temp
        }
        else {
            LCD_goTo(4, 2); // move cursor to column 4 row 2
            LCD_print("  Error!  ");
        }
        __delay_ms(1000); // wait 1 second
    }
}

