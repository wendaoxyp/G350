#include "user.h"
#include "task.h"
#include "CheckData.h"
#include "SerialBuffer.h"
#include "P-Miot1601.h"
#include "Miot1601.h"

///*************************************  08 00
//Function: CopPCorTCPTask 
//Description: 开机启动10s用于PC与模块通讯
//Input: 无
//Output: 无  
// *************************************/
//void CopPCTask(void) {
//    //如果数据接收到或是PC通讯任务挂起标志为1，则进行功能选择，反之10s后退出通讯
//    u8 sendData[152]; //临时发送数据
//    u8 flag = 0, cnt = 0; //hook
//    u8 bytes, head;
//
//    OpenRS485();
//    T3Delay10ms(10);
//    RS485SendString("SSSSSSSSSS", 10); //人机交互
//    Register2Read(&head, REG2_Arg_Postion[mi_add], 1); //获取帧头
//
//    do {//10s判断是否进入参数设置
//        bytes = UART1IsGet(sendData, &head, 1);
//        if (bytes) {
//            if (CheckIsRight(CRC16_Check, sendData, bytes - 2)) {
//                flag = CopFun(sendData, bytes, PC); //如果是退出设置，gChangeParameterFlag=0；
//                if (flag == 'b') //如果gChangeParameterFlag为0，立马退出
//                    break;
//
//            } //else//校验失败 发送未执行
//            // TCP_Error_Relay(sendData + 1, Do_Err, PC);
//            cnt = 0;
//        } else
//            cnt++;
//        if (cnt > 2)
//            break;
//        ClrWdt();
//    } while (flag);
//    RS485SendString("EEEEEEEEEE", 10); //人机交互
//    CloseRS485();
//}
//
//void SettingArg(void) {
//    u8 head[2], bytes;
//    u8 receiveData[40];
//
//    Register2Read(head, REG2_Arg_Postion[mi_add], 1); //获取帧头
//    head[1] = 0x10;
//    bytes = UARTIsGet(BufferRead_UART1, receiveData, 10, head, 2);
//    //08 10 00 00 00 00 20 17 01 05 09 56 29 EC C9 
//    if (CheckIsRight(CRC16_Check, receiveData, (const u8) (bytes - 2))) {
//        Register2Write(receiveData + 2, REG2_Arg_Postion[mi_ofst], 4); //写入脉冲量
//        Register2Write(receiveData + 6, REG2_Arg_Postion[mi_year], 7); //写入时间
//        StopRTCC();
//        CheckRTCC();
//        StartRTCC();
//        FM25L64B_Write(RST_Time, receiveData + 6, 7); //保存脉冲总量
//        FM25L64B_Write(BOR_Pulse, (u8*) (&gPulseCount), 4); //保存脉冲总量
//    }
//}



