/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_SPI_H
#define	XC_SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic16f887.h>
#define _XTAL_FREQ 8000000

typedef enum
{
  SPI_MASTER_OSC_DIV4  = 0b00100000,
  SPI_MASTER_OSC_DIV16 = 0b00100001,
  SPI_MASTER_OSC_DIV64 = 0b00100010,
  SPI_MASTER_TMR2      = 0b00100011,
  SPI_SLAVE_SS_EN      = 0b00100100,
  SPI_SLAVE_SS_DIS     = 0b00100101
} SPI_type; 


typedef enum
{
  SPI_DATA_SAMPLE_MIDDLE = 0b00000000,
  SPI_DATA_SAMPLE_END    = 0b10000000
} SPI_dataSample;


typedef enum
{
  SPI_CLOCK_IDLE_HIGH = 0b00001000,
  SPI_CLOCK_IDLE_LOW  = 0b00000000
} SPI_clockIdle;


typedef enum
{
  SPI_IDLE_2_ACTIVE = 0b00000000,
  SPI_ACTIVE_2_IDLE = 0b01000000
} SPI_transmitEdge;


void SPI_initialize(SPI_type sType, SPI_dataSample sDataSample, SPI_clockIdle sClockIdle, SPI_transmitEdge sTransmitEdge);
static void SPI_receiveAndWait();
void SPI_sendData(char data);
unsigned char SPI_ready(void);
unsigned char SPI_read(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

