/*
 * File:   ADC.c
 * Author: DELL
 *
 * Created on February 1, 2021, 8:18 PM
 */

#include"ADC.h"

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
