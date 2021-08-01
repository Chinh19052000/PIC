/*
 * File:   SPI.c
 * Author: DELL
 *
 * Created on January 25, 2021, 4:25 PM
 */

#include "SPI.h"

static void SPI_receiveAndWait() {
    while (!SSPSTATbits.BF); // Wait for Data Receipt complete
}

unsigned char SPI_read(void) // Read the received data
{
    SPI_receiveAndWait(); // Wait until all bits receive
    return (SSPBUF); // Read the received data from the buffer
}

unsigned char SPI_ready(void) //Check whether the data is ready to read
{
    if (SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

void SPI_initialize(SPI_type sType, SPI_dataSample sDataSample, SPI_clockIdle sClockIdle, SPI_transmitEdge sTransmitEdge) {
    TRISC5 = 0;
    if (sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    } 
    else //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    SSPCON = sType | sClockIdle;
}

void SPI_sendData(char data) {
    SSPBUF = data;
}