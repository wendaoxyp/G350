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
const char BL_REMOTE_PASSWD[6] = {0x54, 0x52, 0x5F, 0x31, 0x30, 0x0B}; //远程升级密码TR_10?

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

    SENDCH_U(1)('W'); //发送服务端提示
    SENDCH_U(1)('0');
    SENDSTR_U(2)((uint8_t*) "Remote Upgrade Start!!!", 23); //发送给仪表端
    //    sourceAddr.Val = BUF_CODE; //设置缓冲区的地址
    while (1) {
        /********************Enter HMInterface***********************/
        while (1) {//在bootloader程序中，判断0xA000的地址（中断数据）是否是GPU（类似字符，已经在升级上位机中添加了）然后搬运到运行区域
            /********************Get Command***********************/
            //获取数据
            getsize = UARTGetDat(BufferRead_UART1, buffer, sizeof (buffer), 100); //获取服务端的数据
            headsize = Str_Find_Head(buffer, TR_UPGRAD, getsize, sizeof (TR_UPGRAD)); //是否获取到上线的数据，判断密码是否正确
            if (headsize) {//如果获取到密码
                for (cnt = 0; cnt < 3; cnt++) {//避免数据溢出，写入代码
                    getsize += UARTGetDat(BufferRead_UART1, buffer + getsize, sizeof (buffer) - getsize, 10); //514byte time=514/1920=0.27s 分段获取避免数据溢出     
                    if (getsize > 535) {//如果接收的字节大于535，说明数据溢出，清除数据字节数
                        getsize = 0;
                        break;
                    }
                }
                offset = headsize + sizeof (TR_UPGRAD); //设置偏移量(包含序号)
                if ((getsize >= 514 + offset) && CRCIsRight(buffer + offset, 512, buffer + offset + 512)) {//如果CRC校验正确，字节数量是否正确
                    /********************Handle Command***********************/
                    if (sourceAddr.Val >= 0xA800) {//如果写数据的地址大于配置位所在的页，那么退出
                        PrintErr(19); //向仪表端发送提示
                        return False;
                    }
                    page_id = buffer[offset - 1]; //获取页码
                    sourceAddr.Val = BUF_CODE + (page_id << 8);
                    if (!(sourceAddr.Val % PM_PAGE_SIZE))//如果刚好是一页的开头的话，那么进行擦除指令
                        Erase(sourceAddr.word.HW, sourceAddr.word.LW); //清除数据
                    WriteFlashByRow(sourceAddr.Val, buffer + offset, 1); //写入FLASH 512字节    
                    getsize = 0;
                    is_write_Right = True; //写入成功标志置1
                    break; //跳出，指令响应处理
                } else {//数据没有接受完全，
                    getsize = 0;
                    is_write_Right = False; //写入失败
                }
            }
            headsize = Str_Find_Head(buffer, TR_UPGOV, getsize, sizeof (TR_UPGOV)); //如果接收到结束提示符
            if (headsize) {//判断是否接收完成
                for (cnt = 0; cnt < 10; cnt++) {//指示灯提示 100ms闪烁 5次
                    GLED ^= 1;
                    Delay100ms(1);
                }
                GLED = 0; //必须灭灯
                return True; //升级成功退出
            }
        }
        if (is_write_Right) {//如果写入成功，将数据读取出来做判断，是否写入正确
            /********************Response Command***********************/
            //对比大小：对比512接收到的数据是否和读出来的数据一样
            ReadArgFromFlash(sourceAddr.Val, readdata, 512); //获取512bytes
            for (cnt = 0; cnt < 512; cnt++) {
                if (readdata[cnt] != *(buffer + offset + cnt)) {
                    is_read_Right = False;
                    break;
                } else
                    is_read_Right = True;
            }
        }
        if (is_read_Right) {//如果读取数据校验正确，则页数+1，处理成功提示
            P15_UPG_TIP[8] = 'O';
            P15_UPG_TIP[9] = 'K';
        } else {//如果读取数据校验失败，则处理失败提示
            P15_UPG_TIP[8] = 'E';
            P15_UPG_TIP[9] = 'R';
        }
        P15_UPG_TIP[1] = (char) (page_id / 10 % 10 + 0x30);
        P15_UPG_TIP[2] = (char) (page_id % 10 + 0x30);
        SENDSTR_U(2)(P15_UPG_TIP, sizeof (P15_UPG_TIP)); //向仪表端发送提示
        SENDSTR_U(1)(P15_UPG_TIP, sizeof (P15_UPG_TIP)); //向服务端发送提示
        if (page_id > ALL_PAGE) {//如果页数大于规定的页数，返回错误
            return False;
        }
    }
    return False;
}


//                Erase(0, AVIT); //清除备用中断向量表所在的页的数据 
//                sourceAddr.Val = BUF_IVT; //设置获取数据的地址中断缓冲区前半部分
//                ReadArgFromFlash(sourceAddr.Val, buffer, 512); //读取中断前半部分
//                WriteFlashByRow(AVIT, buffer, 1); //写入中断前部分
//                sourceAddr.Val = BUF_IVT + PM_ROW_SIZE; //设置获取数据的地址中断缓冲区后半部分
//                ReadArgFromFlash(sourceAddr.Val, buffer, 512); //读取中断后半部分
//                WriteFlashByRow(AVIT + PM_ROW_SIZE, buffer, 1); //写入中断后部分
//                sourceAddr.Val = APP_ADDR; //设置获取数据的地址:代码的开始地址                                
//                for (cnt = 0; cnt < CODE_PAGES; cnt++) {
//                    if (!(sourceAddr.Val % PM_PAGE_SIZE))//如果被0x800整除，说明已经是一个页的开始，需要擦出该页
//                        Erase(sourceAddr.word.HW, sourceAddr.word.LW); //页清除数据
//                    ReadArgFromFlash(sourceAddr.Val + 0x4800, buffer, 512); //读取代码缓冲去数据
//                    WriteFlashByRow(sourceAddr.Val, buffer, 1); //写入代码
//                    sourceAddr.Val += PM_ROW_SIZE;
//                }
//                                    Erase(0, CONFIG_BIT); //清除备用中断向量表所在的页的数据 
//                                    ReadArgFromFlash(APP1_CONFIG_BIT, readdata, 512); //写入配置位的数据还是0xFFFFFF
//                                    WriteFlashByRow(CONFIG_BIT, readdata, 1);


