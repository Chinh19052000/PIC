/*
 * File:   uart.c
 * Author: DELL
 *
 * Created on January 20, 2021, 8:37 PM
 */

#include "uart.h"

void UART_init(long Baud_rate) {
    //*cau hinh chan uart*//
    TRISC6 = 0; // TX Pin set as output
    TRISC7 = 1; // RX Pin set as input

    // khoi tao thanh ghi SPBRG cho toc do truyen va chon mode toc do cao
    SPBRG = ((_XTAL_FREQ / 16) / Baud_rate) - 1;
    BRGH = 1; // baudrate toc do cao

    // chon che do bat dong bo
    SYNC = 0; // Asynchronous
    SPEN = 1; // cho phep cong noi tiep

    // cho phep truyen nhan du lieu
    TXEN = 1; // cho phep truyen 
    CREN = 1; // cho phep nhan

    //chon che do truyen nhan 8 bits 
    TX9 = 0;
    RX9 = 0;

}

void UART_sendChar(char bt) {
    while (!TXIF); //lam tre he thong khi bo dem TX dang trong
    TXREG = bt; // ghi gia tri truyen vao thanh ghi TXREG
}

char UART_getChar() {
    if (OERR) // check Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }

    while (!RCIF); // lam tre he thong khi bo dem RX dang trong
    return RCREG;
}

void UART_sendString(char* str) {
    while (*str) {
        UART_sendChar(*str++);
    }
}