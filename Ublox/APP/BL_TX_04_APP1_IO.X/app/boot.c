//Includes *******************************
#include <xc.h>
#include "config.h"
#include "Common.h"
#include "../bsp/Flash.h"
#include "UART2.h"
//****************************************

//Globals ********************************
DWORD_VAL sourceAddr; //general purpose address variable

char TR_UPGRAD[9] = {0x54, 0x52, 0x5F, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44}; // TR_UPGRAD
char TR_UPGOV[9] = {0x54, 0x52, 0x5F, 0x55, 0x50, 0x47, 0x4F, 0x56, 0x0D}; // TR_UPGOV 
char P15_UPG_TIP[12] = {0x50, 0x31, 0x35, 0x5F, 0x55, 0x50, 0x47, 0x5F, 0x4F, 0x4B, '\r', '\n'}; //P15_UPG_OK
const char BL_REMOTE_PASSWD[6] = {0x54, 0x52, 0x5F, 0x31, 0x30, 0x0B}; //Զ����������TR_10?

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
Bool BootLoader(void) {
    BYTE buffer[540];
    BYTE readdata[520];
    WORD cnt, getsize = 0, headsize = 0, offset; // = 0xFFFF;
    WORD page_id = 0;
    Bool is_read_Right = False, is_write_Right = False;

    SENDCH_U(1)('W'); //���ͷ������ʾ
    SENDCH_U(1)('0');
    SENDSTR_U(2)((uint8_t*) "Remote Upgrade Start!!!", 23); //���͸��Ǳ��
    //    sourceAddr.Val = BUF_CODE; //���û������ĵ�ַ
    while (1) {
        /********************Enter HMInterface***********************/
        while (1) {//��bootloader�����У��ж�0xA000�ĵ�ַ���ж����ݣ��Ƿ���GPU�������ַ����Ѿ���������λ��������ˣ�Ȼ����˵���������
            /********************Get Command***********************/
            //��ȡ����
            getsize = UARTGetDat(BufferRead_UART1, buffer, sizeof (buffer), 100); //��ȡ����˵�����
            headsize = Str_Find_Head(buffer, TR_UPGRAD, getsize, sizeof (TR_UPGRAD)); //�Ƿ��ȡ�����ߵ����ݣ��ж������Ƿ���ȷ
            if (headsize) {//�����ȡ������
                for (cnt = 0; cnt < 3; cnt++) {//�������������д�����
                    getsize += UARTGetDat(BufferRead_UART1, buffer + getsize, sizeof (buffer) - getsize, 10); //514byte time=514/1920=0.27s �ֶλ�ȡ�����������     
                    if (getsize > 535) {//������յ��ֽڴ���535��˵�������������������ֽ���
                        getsize = 0;
                        break;
                    }
                }
                offset = headsize + sizeof (TR_UPGRAD); //����ƫ����(�������)
                if ((getsize >= 514 + offset) && CRCIsRight(buffer + offset, 512, buffer + offset + 512)) {//���CRCУ����ȷ���ֽ������Ƿ���ȷ
                    /********************Handle Command***********************/
                    if (sourceAddr.Val >= 0xA800) {//���д���ݵĵ�ַ��������λ���ڵ�ҳ����ô�˳�
                        PrintErr(19); //���Ǳ�˷�����ʾ
                        return False;
                    }
                    page_id = buffer[offset - 1]; //��ȡҳ��
                    sourceAddr.Val = BUF_CODE + (page_id << 8);
                    if (!(sourceAddr.Val % PM_PAGE_SIZE))//����պ���һҳ�Ŀ�ͷ�Ļ�����ô���в���ָ��
                        Erase(sourceAddr.word.HW, sourceAddr.word.LW); //�������
                    WriteFlashByRow(sourceAddr.Val, buffer + offset, 1); //д��FLASH 512�ֽ�    
                    getsize = 0;
                    is_write_Right = True; //д��ɹ���־��1
                    break; //������ָ����Ӧ����
                } else {//����û�н�����ȫ��
                    getsize = 0;
                    is_write_Right = False; //д��ʧ��
                }
            }
            headsize = Str_Find_Head(buffer, TR_UPGOV, getsize, sizeof (TR_UPGOV)); //������յ�������ʾ��
            if (headsize) {//�ж��Ƿ�������
                for (cnt = 0; cnt < 10; cnt++) {//ָʾ����ʾ 100ms��˸ 5��
                    GLED ^= 1;
                    Delay100ms(1);
                }
                GLED = 0; //�������
                return True; //�����ɹ��˳�
            }
        }
        if (is_write_Right) {//���д��ɹ��������ݶ�ȡ�������жϣ��Ƿ�д����ȷ
            /********************Response Command***********************/
            //�Աȴ�С���Ա�512���յ��������Ƿ�Ͷ�����������һ��
            ReadArgFromFlash(sourceAddr.Val, readdata, 512); //��ȡ512bytes
            for (cnt = 0; cnt < 512; cnt++) {
                if (readdata[cnt] != *(buffer + offset + cnt)) {
                    is_read_Right = False;
                    break;
                } else
                    is_read_Right = True;
            }
        }
        if (is_read_Right) {//�����ȡ����У����ȷ����ҳ��+1������ɹ���ʾ
            P15_UPG_TIP[8] = 'O';
            P15_UPG_TIP[9] = 'K';
        } else {//�����ȡ����У��ʧ�ܣ�����ʧ����ʾ
            P15_UPG_TIP[8] = 'E';
            P15_UPG_TIP[9] = 'R';
        }
        P15_UPG_TIP[1] = (char) (page_id / 10 % 10 + 0x30);
        P15_UPG_TIP[2] = (char) (page_id % 10 + 0x30);
        SENDSTR_U(2)(P15_UPG_TIP, sizeof (P15_UPG_TIP)); //���Ǳ�˷�����ʾ
        SENDSTR_U(1)(P15_UPG_TIP, sizeof (P15_UPG_TIP)); //�����˷�����ʾ
        if (page_id > ALL_PAGE) {//���ҳ�����ڹ涨��ҳ�������ش���
            return False;
        }
    }
    return False;
}


//                Erase(0, AVIT); //��������ж����������ڵ�ҳ������ 
//                sourceAddr.Val = BUF_IVT; //���û�ȡ���ݵĵ�ַ�жϻ�����ǰ�벿��
//                ReadArgFromFlash(sourceAddr.Val, buffer, 512); //��ȡ�ж�ǰ�벿��
//                WriteFlashByRow(AVIT, buffer, 1); //д���ж�ǰ����
//                sourceAddr.Val = BUF_IVT + PM_ROW_SIZE; //���û�ȡ���ݵĵ�ַ�жϻ�������벿��
//                ReadArgFromFlash(sourceAddr.Val, buffer, 512); //��ȡ�жϺ�벿��
//                WriteFlashByRow(AVIT + PM_ROW_SIZE, buffer, 1); //д���жϺ󲿷�
//                sourceAddr.Val = APP_ADDR; //���û�ȡ���ݵĵ�ַ:����Ŀ�ʼ��ַ                                
//                for (cnt = 0; cnt < CODE_PAGES; cnt++) {
//                    if (!(sourceAddr.Val % PM_PAGE_SIZE))//�����0x800������˵���Ѿ���һ��ҳ�Ŀ�ʼ����Ҫ������ҳ
//                        Erase(sourceAddr.word.HW, sourceAddr.word.LW); //ҳ�������
//                    ReadArgFromFlash(sourceAddr.Val + 0x4800, buffer, 512); //��ȡ���뻺��ȥ����
//                    WriteFlashByRow(sourceAddr.Val, buffer, 1); //д�����
//                    sourceAddr.Val += PM_ROW_SIZE;
//                }
//                                    Erase(0, CONFIG_BIT); //��������ж����������ڵ�ҳ������ 
//                                    ReadArgFromFlash(APP1_CONFIG_BIT, readdata, 512); //д������λ�����ݻ���0xFFFFFF
//                                    WriteFlashByRow(CONFIG_BIT, readdata, 1);


