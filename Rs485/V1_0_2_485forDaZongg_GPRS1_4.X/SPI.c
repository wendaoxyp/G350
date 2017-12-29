//#include <p24FV32KA301.h>
//#include "type.h"
#include "SPI.h"
#include "user.h"

void SPI2_Configuration(void) {
    TRISAbits.TRISA7 = 1;
    SPI2CON1 = 0x013F;
    // SPIFPOL disabled; SPIBEN enabled; SPIFE disabled; 
    SPI2CON2 = 0x0001;
    // SISEL SPI_INT_SPIRBF; SPIEN enabled; SPISIDL disabled; SPIROV disabled; 
    SPI2STAT = 0x800C;
}

uint8_t SPI2_Exchange(const uint8_t TransmitData) {
    uint8_t ReceiveData = 0;
    while (SPI2STATbits.SPITBF == true);
    SPI2BUF = TransmitData;
    while (SPI2STATbits.SR1MPT == true);
    ReceiveData = SPI2BUF;
    return ReceiveData;
}

void SPI2_Start(void) {
    SPI2STATbits.SPIEN = 1;
}

void SPI2_Stop(void) {
    SS2_TRIS = SCK2_TRIS = SDO2_TRIS = SCK2_TRIS = 0;
    SS2 = 1;
    SCK2 = 0;
    SDO2 = 0;
    SCK2 = 0;
    SPI2STATbits.SPIEN = 0;
}

