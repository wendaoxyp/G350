#include "user.h"
#include "task.h"
#include "CheckData.h"
#include "SerialBuffer.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

///*************************************  08 00
//Function: CopPCorTCPTask 
//Description: ��������10s����PC��ģ��ͨѶ
//Input: ��
//Output: ��  
// *************************************/
//void CopPCTask(void) {
//    //������ݽ��յ�����PCͨѶ��������־Ϊ1������й���ѡ�񣬷�֮10s���˳�ͨѶ
//    u8 sendData[152]; //��ʱ��������
//    u8 flag = 0, cnt = 0; //hook
//    u8 bytes, head;
//
//    OpenRS485();
//    T3Delay10ms(10);
//    RS485SendString("SSSSSSSSSS", 10); //�˻�����
//    Register2Read(&head, REG2_Arg_Postion[mi_add], 1); //��ȡ֡ͷ
//
//    do {//10s�ж��Ƿ�����������
//        bytes = UART1IsGet(sendData, &head, 1);
//        if (bytes) {
//            if (CheckIsRight(CRC16_Check, sendData, bytes - 2)) {
//                flag = CopFun(sendData, bytes, PC); //������˳����ã�gChangeParameterFlag=0��
//                if (flag == 'b') //���gChangeParameterFlagΪ0�������˳�
//                    break;
//
//            } //else//У��ʧ�� ����δִ��
//            // TCP_Error_Relay(sendData + 1, Do_Err, PC);
//            cnt = 0;
//        } else
//            cnt++;
//        if (cnt > 2)
//            break;
//        ClrWdt();
//    } while (flag);
//    RS485SendString("EEEEEEEEEE", 10); //�˻�����
//    CloseRS485();
//}
//
//void SettingArg(void) {
//    u8 head[2], bytes;
//    u8 receiveData[40];
//
//    Register2Read(head, REG2_Arg_Postion[mi_add], 1); //��ȡ֡ͷ
//    head[1] = 0x10;
//    bytes = UARTIsGet(BufferRead_UART1, receiveData, 10, head, 2);
//    //08 10 00 00 00 00 20 17 01 05 09 56 29 EC C9 
//    if (CheckIsRight(CRC16_Check, receiveData, (const u8) (bytes - 2))) {
//        Register2Write(receiveData + 2, REG2_Arg_Postion[mi_ofst], 4); //д��������
//        Register2Write(receiveData + 6, REG2_Arg_Postion[mi_year], 7); //д��ʱ��
//        StopRTCC();
//        CheckRTCC();
//        StartRTCC();
//        FM25L64B_Write(RST_Time, receiveData + 6, 7); //������������
//        FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //������������
//    }
//}



