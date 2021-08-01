/*
 * File:   main_UART.c
 * Author: Tuan Anh
 *
 * Created on January 17, 2021, 5:17 PM
 */

// CONFIG
#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// End of configuration

#include <xc.h>
#include "uart.h"

void main(void) 
{
    char getValue;
    TRISB = 0x00; 
    UART_init(9600);                   
    UART_sendString("Giao tiep UART da duoc khoi tao");
    while (1) 
    {
        getValue = UART_getChar();
        if (getValue == '1') 
        {
            RB3 = 1; 
            UART_sendString(" LED -> ON "); 
            UART_sendChar(10); 
        }
        if (getValue == '0') 
        {
            RB3 = 0; 
            UART_sendString(" LED-> OFF "); 
            UART_sendChar(10); 
        }
    }
}

