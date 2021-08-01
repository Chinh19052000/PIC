/*
 * File:   SPI.c
 * Author: Tuan Anh
 *
 * Created on January 25, 2021, 10:37 AM
 */

#include "SPI.h"

static void SPI_receiveAndWait() {
    while (!SSPSTATbits.BF); // cho qua trinh nhan du lieu 
}

unsigned char SPI_read(void) 
{
    SPI_receiveAndWait(); 
    return (SSPBUF); // doc gia tri nhan duoc tu bo dem
}

unsigned char SPI_ready(void) 
{
    if (SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

void SPI_init(SPI_type sType, SPI_dataSample sDataSample, SPI_clockIdle sClockIdle, SPI_transmitEdge sTransmitEdge) {
    TRISC5 = 0;
    if (sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    } else //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    SSPCON = sType | sClockIdle;
}

void SPI_sendData(char data) {
    SSPBUF = data;
}

