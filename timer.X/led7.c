/*
 * File:   led7.c
 * Author: Tuan Anh
 *
 * Created on January 10, 2021, 1:01 AM
 */

#include "led7.h"

const uint8_t LED7_HEX[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
    0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
unsigned char buffer[4];

char Led7_pointIndex(double num) {
    if (num > 99.9 && num <= 999.9) return 1;
    else if (num > 9.9 && num <= 99.9) return 2;
    else if (num >= 0 && num <= 9.9) return 3;
    return 0;

}

void Led7_displayUnit(unsigned char number) {
    PORTB = LED7_HEX[number];
}

void Led7_addFloatToBuffer(double num) {
    int newNum;
    char p = Led7_pointIndex(num);
    if (p == 0)
        newNum = (int) num;
    else if (p == 1)
        newNum = (int) (num * 10);
    else if (p == 2)
        newNum = (int) (num * 100);
    else if (p == 3)
        newNum = (int) (num * 1000);
    for (int i = 0; i < 4; i++) {
        buffer[i] = newNum % 10;
        newNum /= 10;
    }
    buffer[p] += 10;
}

void Led7_display(double num) {
    Led7_addFloatToBuffer(num);
    Led7_displayUnit(buffer[0]);
    RD3 = 1;
    __delay_ms(1);
    RD3 = 0;
    // bat den 2
    Led7_displayUnit(buffer[1]);
    RD2 = 1;
    __delay_ms(1);
    RD2 = 0;
    // bat den 3
    Led7_displayUnit(buffer[2]);
    RD1 = 1;
    __delay_ms(1);
    RD1 = 0;
    // bat den 4
    Led7_displayUnit(buffer[3]);
    RD0 = 1;
    __delay_ms(1);
    RD0 = 0;
}