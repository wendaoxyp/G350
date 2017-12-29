#include "HL6528.h"
#include "ATCommand.h"
#include "Common.h"
//#include "StringDeal.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/eusart2.h"

#define AT_COMMAND 0x50
#define USER_DATA 0x51 


enum GPRSSta {
    AT_K3 = 0x10, AT_CPIN = 0x11, AT_CIMI = 0x12, AT_CREG = 0x13, AT_CGREG = 0x14, AT_CSCA = 0x15,
    AT_KCNXCFG = 0x16, AT_KTCPCFG = 0x17, AT_KTCPSTART = 0x18
};

struct GPRSARG {
    uint8_t gprscnt;
    char* gprsIP;
    uint16_t gprsPort;
    char *gprsAPN;
};

void SendDat2GPRS(const uint8_t* ATcmd, const uint8_t cmdlgt) {
    uint8_t cnt = 0;

    for (cnt = 0; cnt < cmdlgt; cnt++) {
        EUSART1_Write(*(ATcmd + cnt));
    }
}

void GPRSDialing(struct StringCmpResult*scr, uint8_t Dialing) {
    uint8_t str1[80];
    //    bool isbreak = false;

    scr->inputstring = str1;
    scr->inputlgt = sizeof (str1);
    while (Dialing) {
        switch (Dialing) {
            case AT_K3:
            {
                SendDat2GPRS(&K3, strlen(K3));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                scr->cmpstring = (uint8_t*) (&REC_OK);
                scr->cmplgt = 2;
                Dialing = (RecIsRight(scr)) ? AT_CPIN : AT_K3;
                break;
            }
            case AT_CPIN:
            {
                SendDat2GPRS(&CPIN, strlen(CPIN));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                Dialing = (RecIsRight(scr)) ? AT_CIMI : AT_CPIN;
                break;
            }
            case AT_CIMI:
            {
                SendDat2GPRS(&CIMI, strlen(CIMI));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                Dialing = (RecIsRight(scr)) ? AT_CREG : AT_CIMI; // : AT_CPIN;
                break;
            }
            case AT_CREG:
            {
                SendDat2GPRS(&CREG, strlen(CREG));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                scr->cmpstring = (uint8_t*) (&REC_CREG);
                scr->cmplgt = 10;
                Dialing = (RecIsRight(scr)) ? AT_CGREG : AT_CREG;
                break;
            }
            case AT_CGREG:
            {
                SendDat2GPRS(&CGREG, strlen(CGREG));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                scr->cmpstring = (uint8_t*) (&REC_CGREG);
                scr->cmplgt = 11;
                Dialing = (RecIsRight(scr)) ? AT_KCNXCFG : AT_CGREG;
                break;
            }
                //            case AT_CSCA:
                //            {
                //                SendDat2GPRS(UARTWrite, &CSCA, strlen(K3));
                //                Delay100ms(1);
                //                GetBuffer(UARTRead, str1, sizeof (str1));
                //                Dialing = (RecIsRight(&scr)) ? AT_KCNXCFG : AT_CSCA;
                //                break;
                //            }
            case AT_KCNXCFG:
            {
                SendDat2GPRS(&KCNXCFG, strlen(KCNXCFG));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                scr->cmpstring = (uint8_t*) (&REC_OK);
                scr->cmplgt = 2;
                Dialing = (RecIsRight(scr)) ? AT_KTCPCFG : AT_KCNXCFG;
                break;
            }
            case AT_KTCPCFG:
            {
                SendDat2GPRS(&KTCPCFG, strlen(KTCPCFG));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                Dialing = (RecIsRight(scr)) ? AT_KTCPSTART : AT_KTCPCFG;
                break;
            }
            case AT_KTCPSTART:
            {
                SendDat2GPRS(&KTCPSTART, strlen(KTCPSTART));
                Delay1s(1);
                GetBuffer(str1, sizeof (str1), EUSART1_Read);
                Dialing = 0;
                break;
            }
            default:
            {
                //                PORTDbits.RD6 = 0;
                //                Delay1s(1);
                //                PORTDbits.RD6 = 1;
                //            Dialing = EUSART2_Read();
                //                isbreak = true;
                break;
            }
        }
        //        if (isbreak) break;
    }
}

bool CloseGPRS(struct StringCmpResult*scr) {
    uint8_t str1[30];
    scr->inputstring = str1;
    scr->inputlgt = sizeof (str1);
    scr->cmpstring = (uint8_t*) (&REC_OK);
    scr->cmplgt = 2;
    SendDat2GPRS(&KTCPSTART, strlen(KTCPSTART));
    Delay1s(1);
    GetBuffer(str1, sizeof (str1), EUSART1_Read);
    return RecIsRight(scr);
}


