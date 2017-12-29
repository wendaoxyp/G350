/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                  Application-Defined uC/Probe Functions
*
*                                 (c) Copyright 2007; Micrium; Weston, FL
*                                           All Rights Reserved
*
* File    : APP_PROBE.C
* By      : Fabiano Kovalski
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                            GLOBAL DATA
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN    > 0) && \
    (uC_PROBE_COM_MODULE   > 0) && \
    (PROBE_COM_STAT_EN     > 0)
#if (OS_PROBE_USE_FP       > 0)
static  CPU_FP32      Probe_ComRxPktSpd;
static  CPU_FP32      Probe_ComTxPktSpd;
static  CPU_FP32      Probe_ComTxSymSpd;
static  CPU_FP32      Probe_ComTxSymByteSpd;
#else
static  CPU_INT32U    Probe_ComRxPktSpd;
static  CPU_INT32U    Probe_ComTxPktSpd;
static  CPU_INT32U    Probe_ComTxSymSpd;
static  CPU_INT32U    Probe_ComTxSymByteSpd;
#endif

static  CPU_INT32U    Probe_ComRxPktLast;
static  CPU_INT32U    Probe_ComTxPktLast;
static  CPU_INT32U    Probe_ComTxSymLast;
static  CPU_INT32U    Probe_ComTxSymByteLast;

static  CPU_INT32U    Probe_ComCtrLast;
#endif

#if (uC_PROBE_OS_PLUGIN > 0)
static  CPU_INT32U   Probe_Counts;
#endif


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0)
static  void  AppProbeCallback(void);
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                        INITIALIZE PROBE MODULES
*
* Description: This function initializes the modules required for uC/Probe.
*
* Arguments  : none.
*
* Note(s)    : none.
*********************************************************************************************************
*/

void  AppProbeInit (void)
{
#if (uC_PROBE_OS_PLUGIN > 0)
    (void)Probe_Counts;

#if (uC_PROBE_COM_MODULE   > 0) && \
    (PROBE_COM_STAT_EN     > 0)
    (void)Probe_ComRxPktSpd;
    (void)Probe_ComTxPktSpd;
    (void)Probe_ComTxSymSpd;
    (void)Probe_ComTxSymByteSpd;
#endif

    OSProbe_Init();
    OSProbe_SetCallback(AppProbeCallback);
    OSProbe_SetDelay(50);
#endif

#if (uC_PROBE_COM_MODULE > 0)
    ProbeCom_Init();                                                    /* Initialize the uC/Probe communications module            */

#if (PROBE_COM_METHOD_RS232 > 0)
    ProbeRS232_Init(38400);
    ProbeRS232_RxIntEn();
#endif

#if (PROBE_COM_METHOD_TCPIP > 0)
    ProbeTCPIP_Init();
#endif
#endif
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         AppProbeCallback()
*
* Description : This function is called by the uC/Probe uC/OS-II plug-in after updating task information.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0)
static  void  AppProbeCallback (void)
{
#if (uC_PROBE_COM_MODULE   > 0) && \
    (PROBE_COM_STAT_EN     > 0)
    CPU_INT32U  ctr_curr;
    CPU_INT32U  rxpkt_curr;
    CPU_INT32U  txpkt_curr;
    CPU_INT32U  sym_curr;
    CPU_INT32U  symbyte_curr;
#endif


    Probe_Counts++;

#if (uC_PROBE_COM_MODULE   > 0) && \
    (PROBE_COM_STAT_EN     > 0)
    ctr_curr     = OSTime;
    rxpkt_curr   = ProbeCom_RxPktCtr;
    txpkt_curr   = ProbeCom_TxPktCtr;
    sym_curr     = ProbeCom_TxSymCtr;
    symbyte_curr = ProbeCom_TxSymByteCtr;

    if ((ctr_curr - Probe_ComCtrLast) >= OS_TICKS_PER_SEC) {
        Probe_ComRxPktSpd     = (rxpkt_curr   - Probe_ComRxPktLast)     * OS_TICKS_PER_SEC / (ctr_curr - Probe_ComCtrLast);
        Probe_ComTxPktSpd     = (txpkt_curr   - Probe_ComTxPktLast)     * OS_TICKS_PER_SEC / (ctr_curr - Probe_ComCtrLast);
        Probe_ComTxSymSpd     = (sym_curr     - Probe_ComTxSymLast)     * OS_TICKS_PER_SEC / (ctr_curr - Probe_ComCtrLast);
        Probe_ComTxSymByteSpd = (symbyte_curr - Probe_ComTxSymByteLast) * OS_TICKS_PER_SEC / (ctr_curr - Probe_ComCtrLast);

        Probe_ComCtrLast       = ctr_curr;
        Probe_ComRxPktLast     = rxpkt_curr;
        Probe_ComTxPktLast     = txpkt_curr;
        Probe_ComTxSymLast     = sym_curr;
        Probe_ComTxSymByteLast = symbyte_curr;
    }
#endif
}
#endif



