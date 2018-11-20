//Includes *******************************
//#include "PIC24F Serial Bootloader/config.h"

#include <xc.h>
#include "config.h"
#include "Config_Bit.h"
//****************************************


//Globals ********************************
DWORD_VAL sourceAddr; //general purpose address variable
BYTE buffer[512];
BYTE TR_BL_PSWD[] = {0x54, 0x52, 0x5F, 0x31, 0x30, 0x0A}; //TR_BL_INIT
BYTE TR_UPGRADE[] = {0x54, 0x52, 0x5F, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45}; // TR_UPGRADE
BYTE TR_UPGOV[] = {0x54, 0x52, 0x5F, 0x55, 0x50, 0x47, 0x4F, 0x56, 0x0D}; // TR_UPGOV 
BYTE P15_UPG_TIP[] = {0x50, 0x31, 0x35, 0x5F, 0x55, 0x50, 0x47, 0x5F, 0x4F, 0x4B, '\r', '\n'}; //P15_UPG_OK

static void Copy_Data(BYTE* out_buf, const BYTE* in_buf, const BYTE size);
static void RemoveCode2RunAdd(void);
static void FullTip(BYTE id, BYTE is_ok);

/********************************************************************
 * Function: 	int main()
 *
 * Precondition: None.
 *
 * Input: 		None.
 *
 * Output:		None.
 *
 * Side Effects:	Enables 32-bit Timer2/3.  Enables UART.
 *
 * Overview: 	Initialization of program and main loop.
 *			
 * Note:		 	None.
 ********************************************************************/
int main() {
    BYTE RXByte = 0; //, break_is_ok = 0; //, responseLen = 0;
    WORD CRC_Sumx, cnt; // = 0xFFFF;
    WORD dataCount;
    BYTE page_id = 0;
    DWORD_VAL rm_bl;

    /********************TIM23***********************/
    //Enable timer if not in always-BL mode
    T2CONbits.TON = 0;
    T2CONbits.T32 = 1; // Setup Timer 2/3 as 32 bit timer incrementing every clock
    IFS0bits.T3IF = 0; // Clear the Timer3 Interrupt Flag 
    IEC0bits.T3IE = 0; // Disable Timer3 Interrupt Service Routine 
    PR3 = 0x1E; // 0x5B; //setup timer timeout value
    PR2 = 0x8480; //0x8D80; //4000000=0x3d0900  very second 1E8480
    TMR2 = 0;
    TMR3 = 0;
    T2CONbits.TON = 1; //enable timer
    /********************IO Map***********************/
    __builtin_write_OSCCONL(OSCCON & 0xFFBF); //If using a part with PPS, map the UART I/O
    _U2RXR = 3; // U2RX on RP3
    _RP2R = 5; //RP2=U2TX    
    __builtin_write_OSCCONL(OSCCON | 0x0040); //Lock the IOLOCK bit so that the IO is not accedentally changed.
    //Setup Led IO
    TRISBbits.TRISB15 = 0; //����Ϊ���
    LATBbits.LATB15 = 0;
    //Configure UART pins to be digital I/O.
    ANSBbits.ANSB3 = 0;
    TRISBbits.TRISB3 = 1;
    /********************Configure UART1***********************/
    U2MODEbits.UARTEN = 1; //enable uar
    U2BRG = 26; //BAUDRATEREG;19200
    U2MODEbits.BRGH = 1; //use high speed mode
    U2STA = 0x1400; //Enable 
    U2STAbits.UTXEN = 1; //make sure TX is enabled

    /********************Setup user reset vector ***********************/
    rm_bl.Val = ReadLatch(0, BUF_IVT); //��ȡ���ݣ��������TR_UPGOV����ʾԶ����������Ҫ������ת�������ݵ���������
    if (rm_bl.Val == 0x475055) {
        RemoveCode2RunAdd(); //Զ��������������
        Erase(0, BUF_IVT); //ɾ������
        WriteFlashByDWord(BUF_IVT, 0); //������ݣ������´��ڽ���
        U2MODEbits.UARTEN = 0;
        ResetDevice(APP);
    }
    if (RxDataIsRight(TR_BL_PSWD, 6)) {//1s���ж������Ƿ���� �Ƿ���bootloader��������
        sourceAddr.Val = BUF_CODE; //���ô��뻺�����ĵ�ַ
        T2CONbits.TON = 0; //�رն�ʱ��
        LATBbits.LATB15 = 1; //ָʾ����
        PutChar('W'); //����������ʾ
        PutChar('0'); //����������ʾ
        //        Erase(0, CONFIG_BIT); //��������ж����������ڵ�ҳ������ 
    } else {
        U2MODEbits.UARTEN = 0;
        ResetDevice(APP); //ִ���û�����
    }
    /********************Enter HMInterface**********************/
    while (1) {
        //-------------------Get Command
        if (RxDataIsRight(TR_UPGRADE, 6)) { //�������ǰ��6���ֽ���ȷ�Ļ���
            GetChar(&RXByte); //��ȡһ���ֽ��жϣ��Ƿ��������������ݣ������������
            switch (RXByte) {//�жϽ����ֽڵ����ͣ���R��:�����У���O��:�������
                case 'R':
                {
                    if (RxDataIsRight(TR_UPGRADE + 7, 3)) {//�ж��ֽ�����
                        CRC_Sumx = 0xFFFF; //CRC CHECK��ʼ��
                        dataCount = 0; //�����ֽڳ�ʼ��
                        while (dataCount < 512) { //maximum num bytes
                            GetChar(&RXByte);
                            buffer[dataCount++] = RXByte;
                            CRC_Sumx ^= RXByte; //start of CRC16 Check
                            for (cnt = 0; cnt < 8; cnt++) {
                                if (CRC_Sumx & 0x01) {
                                    CRC_Sumx >>= 1;
                                    CRC_Sumx ^= 0xA001;
                                } else {
                                    CRC_Sumx >>= 1;
                                }
                            }//end of CRC16 Check
                        }//end get data               
                        GetChar(&RXByte); //��ȡ�ֽ�
                        if (RXByte == ((BYTE) CRC_Sumx)) {//�ж�CRC16У�����Ƿ�����
                            GetChar(&RXByte); //��ȡ�ֽ�
                            if (RXByte == ((BYTE) (CRC_Sumx >> 8))) {//�ж�CRC16У�����Ƿ�����
                                //---------------------------Handle Command
                                if (!(sourceAddr.Val % PM_PAGE_SIZE))//���%800��
                                    Erase(sourceAddr.word.HW, sourceAddr.word.LW); //��ʵ�����0x1000������
                                WriteFlashByRow(sourceAddr.Val, buffer, 1); //д��FLASH 512�ֽ�// 
                                FullTip(++page_id, 1);
                                sourceAddr.Val += 0x100; //��ַ����0x100
                            }//end Check high bytes
                            else
                                FullTip(page_id + 1, 0);
                        }//end Check low bytes
                        else {
                            FullTip(page_id + 1, 0);
                        }
                        //������ʾ
                        for (cnt = 0; cnt < 12; cnt++) {//����������ʾ
                            PutChar(P15_UPG_TIP[cnt]);
                        }
                        while (!U2STAbits.TRMT); //wait for transmit to finish
                    }//�ҵ��������ݵ�ͷ
                    break;
                }
                case 'O'://д��ɹ��󣬴�Ӧ����Fx(eg:x-1,2)
                {
                    GetChar(&RXByte);
                    if (RXByte == 'V') {
                        GetChar(&RXByte);
                        if (RXByte == 0x0D) {
                            RemoveCode2RunAdd();
                            //�رմ��ڣ�����λ�豸
                            LATBbits.LATB15 = 0; //ָʾ����
                            U2MODEbits.UARTEN = 0;
                            ResetDevice(APP);
                        }
                    }
                    break;
                }
            }//end switch
        }//end 
        if (page_id > CODE_PAGES) {//д���һҳ         
            U2MODEbits.UARTEN = 0;
            ResetDevice(APP); //ִ�е�ǰ�û�����
        }
    }//end while(1)
}//end main(void)

/********************************************************************
 * Function: 	void PutChar(BYTE Char)
 *
 * Precondition: UART Setup
 *
 * Input: 		Char - Character to transmit
 *
 * Output: 		None
 *
 * Side Effects:	Puts character into destination pointed to by ptrChar.
 *
 * Overview: 	Transmits a character on UART2. 
 *	 			Waits for an empty spot in TXREG FIFO.
 *
 * Note:		 	None
 ********************************************************************/
void PutChar(BYTE txChar) {
    while (U2STAbits.UTXBF); //wait for FIFO space
    U2TXREG = txChar; //put character onto UART FIFO to transmit
}//end PutChar(BYTE Char)

/********************************************************************
 * Function:        void GetChar(BYTE * ptrChar)
 *
 * PreCondition:    UART Setup
 *
 * Input:		ptrChar - pointer to character received
 *
 * Output:		
 *
 * Side Effects:	Puts character into destination pointed to by ptrChar.
 *				Clear WDT
 *
 * Overview:		Receives a character from UART2.  
 *
 * Note:			None
 ********************************************************************/
void GetChar(BYTE * ptrChar) {
    BYTE dummy;
    while (1) {
        asm("clrwdt"); //looping code, so clear WDT

        //check for receive errors
        if (U2STA & 0x000E) {
            dummy = U2RXREG; //dummy read to clear FERR/PERR
            U2STAbits.OERR = 0; //clear OERR to keep receiving
        }

        //get the data
        if (U2STAbits.URXDA == 1) {
            * ptrChar = U2RXREG; //get data from UART RX FIFO
            break;
        }

        //#ifndef USE_AUTOBAUD
        //if timer expired, jump to user code
        if (IFS0bits.T3IF == 1) {
            ResetDevice(APP);
        }
        //#endif
    }//end while(1)
}//end GetChar(BYTE *ptrChar)

/********************************************************************
 * Function:     void WriteTimeout()
 *
 * PreCondition: The programmed data should be verified prior to calling
 * 				this funtion.
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Side Effects:	None.
 *
 * Overview:		This function writes the stored value of the bootloader
 *				timeout delay to memory.  This function should only
 *				be called after sucessful verification of the programmed
 *				data to prevent possible bootloader lockout
 *
 * Note:			None
 ********************************************************************/
void WriteFlashByDWord(DWORD addr, DWORD jump_vector) {
    TBLPAG = 0xFA; //FA 00:д0x00����ģ��0x800�����ݱ����
    NVMADRL = addr & 0xFFFF;
    NVMADRH = addr >> 16; // set target write address
    NVMCON = 0x4001;
    WriteLatch(0, (jump_vector >> 16), (jump_vector & 0xFFFF));
    WriteLatch(1, (jump_vector >> 16), (jump_vector & 0xFFFF));
    //execute write sequence
    __builtin_write_NVM();

    while (NVMCONbits.WR == 1);
    Nop();
    Nop();
}//end WriteTimeout

void WriteFlashByRow(DWORD argadd, unsigned char const *dat, const BYTE size) {//, const uint8_t bytes) {
    DWORD_VAL tmp_dat, addr;
    WORD writebytes;
    BYTE cnt;

    addr.Val = argadd;

    for (cnt = 0; cnt < size; cnt++) {
        TBLPAG = 0xFA; //FA 00:д0x00����ģ��0x800�����ݱ����
        NVMADRL = addr.word.LW;
        NVMADRH = addr.word.HW; // set target write address
        //        writebytes = 0;
        for (writebytes = 0; writebytes < PM_ROW_SIZE; writebytes += 4) { // load write latches with data ��д��

            Copy_Data(tmp_dat.v, (writebytes + dat), 4);
            WriteLatch(writebytes >> 2, tmp_dat.word.HW, tmp_dat.word.LW);
        }
        __builtin_disi(5); // Disable interrupts
        WriteMem(0x4002);
        addr.Val += 0x100;
    }
}

void ReadArgFromFlash(DWORD addr, BYTE*dat, const WORD bytes) {//byte:2�ı���
    WORD readbyte;
    DWORD_VAL tmp;
    DWORD addr1;
    addr1 = addr;

    readbyte = 0;
    while (readbyte < bytes) // load write latches with data
    {
        tmp.Val = ReadLatch(0, addr1);
        Copy_Data(dat + readbyte, tmp.v, 4);
        readbyte += 4;
        addr1 += 2;
    }
}

unsigned char RxDataIsRight(const unsigned char *dat, const unsigned char dat_byte) {
    unsigned char cnt, rxByte;

    for (cnt = 0; cnt < dat_byte; cnt++) {
        GetChar(&rxByte); //Read second byte ���׿��ڴ˴���ͨ����ʱ��������
        if (rxByte != *(dat + cnt)) {
            return 0; //δ��ȡ
        }
    }
    //    Nop();
    return 1; //��ȡ��
}

static void Copy_Data(BYTE* out_buf, const BYTE* in_buf, const BYTE size) {
    BYTE cnt = 0;
    for (cnt = 0; cnt < size; cnt++)
        *(out_buf + cnt) = *(in_buf + cnt);
}

static void RemoveCode2RunAdd(void) {
    BYTE cnt;
    //д���ж�����
    Erase(0, AVIT); //��������ж����������ڵ�ҳ������ 
    sourceAddr.Val = BUF_IVT; //���û�ȡ���ݵĵ�ַ�жϻ�����ǰ�벿��
    ReadArgFromFlash(sourceAddr.Val, buffer, 512); //��ȡ�ж�ǰ�벿��
    WriteFlashByRow(AVIT, buffer, 1); //д���ж�ǰ����
    sourceAddr.Val = BUF_IVT + PM_ROW_ADD; //���û�ȡ���ݵĵ�ַ�жϻ�������벿��
    ReadArgFromFlash(sourceAddr.Val, buffer, 512); //��ȡ�жϺ�벿��
    WriteFlashByRow(AVIT + PM_ROW_ADD, buffer, 1); //д���жϺ󲿷�
    //д��������
    sourceAddr.Val = APP; //���û�ȡ���ݵĵ�ַ:����Ŀ�ʼ��ַ                                
    for (cnt = 0; cnt < CODE_PAGES; cnt++) {
        if (!(sourceAddr.Val % PM_PAGE_SIZE))//�����0x800������˵���Ѿ���һ��ҳ�Ŀ�ʼ����Ҫ������ҳ
            Erase(sourceAddr.word.HW, sourceAddr.word.LW); //ҳ�������
        ReadArgFromFlash(sourceAddr.Val + 0x4800, buffer, 512); //��ȡ���뻺��ȥ����
        WriteFlashByRow(sourceAddr.Val, buffer, 1); //д�����
        sourceAddr.Val += PM_ROW_ADD; //
    }
    //д����λ����
    //                                Erase(0, CONFIG_BIT); //�������λ���ڵ�ҳ������ 
    //                                sourceAddr.Val = BUF_CONFIG; //���û�ȡ���ݵĵ�ַ�жϻ�����ǰ�벿��
    //                                ReadArgFromFlash(sourceAddr.Val, buffer, 512); //��ȡ�ж�ǰ�벿��
    //                                WriteFlashByRow(CONFIG_BIT, buffer, 1); //д���ж�ǰ����

}

static void FullTip(BYTE id, BYTE is_ok) {
    if (is_ok) {
        P15_UPG_TIP[8] = 'O';
        P15_UPG_TIP[9] = 'K';
    } else {
        P15_UPG_TIP[8] = 'E';
        P15_UPG_TIP[9] = 'R';
    }
    P15_UPG_TIP[1] = id / 10 + 0x30;
    P15_UPG_TIP[2] = id % 10 + 0x30;
}

