/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mcc.h"
#include "spi1_driver.h"

inline void spi1_close(void)
{
    SPI1CON1Lbits.SPIEN = 0;
}

//con1l == SPIxCON1L, con1h == SPIxCON1H, con2l == SPIxCON2L, statl == SPIxSTATL, stath == SPIxSTATH, brgl == SPIxBRGL, imskl == SPIxIMSKL, imskh == SPIxIMSKH, urdtl == SPIxURDTL, urdth == SPIxURDTH
typedef struct { uint16_t con1l; uint16_t con1h; uint16_t con2l; uint16_t statl; uint16_t stath; uint16_t brgl; uint16_t imskl; uint16_t imskh; uint16_t urdtl; uint16_t urdth;} spi1_configuration_t;
static const spi1_configuration_t spi1_configuration[] = {   
    {0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000 }
};

bool spi1_master_open(spi1_modes spiUniqueConfiguration)
{
    if(!SPI1CON1Lbits.SPIEN)
    {
        SPI1CON1H = spi1_configuration[spiUniqueConfiguration].con1h;
        SPI1CON2L = spi1_configuration[spiUniqueConfiguration].con2l;
        SPI1STATL = spi1_configuration[spiUniqueConfiguration].statl;
        SPI1STATH = spi1_configuration[spiUniqueConfiguration].stath;
        SPI1BRGL = spi1_configuration[spiUniqueConfiguration].brgl;
        SPI1IMSKL = spi1_configuration[spiUniqueConfiguration].imskl;
        SPI1IMSKH = spi1_configuration[spiUniqueConfiguration].imskh;
        SPI1URDTL = spi1_configuration[spiUniqueConfiguration].urdtl;
        SPI1URDTH = spi1_configuration[spiUniqueConfiguration].urdth;
        
        SCK1OUT_SetDigitalOutput();

        SPI1CON1L = spi1_configuration[spiUniqueConfiguration].con1l | 0x8020;

        return true;
    }
    return false;
}

//Setup SPI for Slave Mode
bool spi1_slave_open(spi1_modes spiUniqueConfiguration)
{
    if(!SPI1CON1Lbits.SPIEN)
    {
        SPI1CON1H = spi1_configuration[spiUniqueConfiguration].con1h;
        SPI1CON2L = spi1_configuration[spiUniqueConfiguration].con2l;
        SPI1STATL = spi1_configuration[spiUniqueConfiguration].statl;
        SPI1STATH = spi1_configuration[spiUniqueConfiguration].stath;
        SPI1BRGL = spi1_configuration[spiUniqueConfiguration].brgl;
        SPI1IMSKL = spi1_configuration[spiUniqueConfiguration].imskl;
        SPI1IMSKH = spi1_configuration[spiUniqueConfiguration].imskh;
        SPI1URDTL = spi1_configuration[spiUniqueConfiguration].urdtl;
        SPI1URDTH = spi1_configuration[spiUniqueConfiguration].urdth;
        
        SCK1OUT_SetDigitalInput();

        SPI1CON1L = spi1_configuration[spiUniqueConfiguration].con1l | 0x8000;
        
        return true;
    }
    return false;
}

// Full Duplex SPI Functions
uint8_t spi1_exchangeByte(uint8_t b)
{
    SPI1BUFL = b;
    while(!SPI1STATLbits.SPIRBF);
    return SPI1BUFL;
}

void spi1_exchangeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data = spi1_exchangeByte(*data );
        data++;
    }
}

// Half Duplex SPI Functions
void spi1_writeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        spi1_exchangeByte(*data++);
    }
}

void spi1_readBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data++ = spi1_exchangeByte(0);
    }
}
