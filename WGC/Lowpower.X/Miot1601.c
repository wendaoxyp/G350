 #include "user.h"
#include "25L64B.h"
//#include "SPI.h"
#include "Miot1601.h"
#include "RS485.h"
#include "math.h"

//通径参数
const u8 Mi_Arg1[7] = {32, 40, 50, 80, 100, 150, 200};
const u8 Mi_Arg2[3] = {1, 10, 100};
const u8 Ver[5] = {'3', '.', '5', '.', '3'};
//static u8 Mi_Sp[5]={};
/*static*/ u8 Register1[REG1_MAX_CNT][19]; //用于存储时间7和工况量12
struct Reg1_Arg Reg1Argbits; //采集数据类型参数
u8 AlarmData[61]; //报警数据通道
//模块参数初始化
/*static*/ u8 Register2[REG_ARG_SIZE] = {
    0x08, 0x7F, 0xF9, 0x02, 0x01, 0x00, 0x00, 0x00, 0x12, 0x02,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x20, 0x16, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01,//1分钟采集一次，2分钟上传一次，便于设备验证
    0x04, 0x00, 0x01, 0x03, 0x42, 0xF0, 0x00, 0x00, 0x42, 0xB4,
    0x00, 0x00, 0x42, 0x48, 0x00, 0x00, 0x40, 0xA0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

//寄存器地址
const u16 mi_arg_add[REG_ARG_NUM + 1] = {
    0x200, 0x201, 0x209, 0x20A, 0x210, 0x212, 0x213, 0x214, 0x215,
    0x216, 0x217, 0x219, 0x21B, 0x21D, 0x21E, 0x21F, 0x220, 0x221,
    0x222, 0x226, 0x22A, 0x22E, 0x232, 0x236
};

//数据包地址
const u8 mi_dat_add[REG_DATA_ARG_NUM + 1] = {
    0x00, 0x07, 0x0B, 0x13, 0x17, 0x1B, 0x1F, 0x27, 0x28, 0x29
};

/*************************************
Function: GetSize 
Description: 获取数据长度
Input: 寄存器地址 寄存器数量
Output: 数据长度
 *************************************/
u8 GetSize(u16 reg_add, u8 arg_num) {
    u8 arg_Now = 0;
    u8 bytes = 0, count = 0;

    if (reg_add < mi_arg_add[REG_ARG_NUM] || reg_add >= mi_arg_add[0]) //获取Miot1601的参数字节数
    {
        for (count = 0; count < REG_ARG_NUM; count++) //判断当前参数是哪个
        {
            if (reg_add == mi_arg_add[count])
                break;
        }
        arg_Now = count; //记录当前参数
        bytes = (mi_arg_add[arg_Now + arg_num] - mi_arg_add[arg_Now]);
    } else //获取数据中参数的字节数//读高地址有问题
    {
        for (count = 0; count < REG_DATA_ARG_NUM; count++) //判断当前参数是哪个
        {
            if (reg_add == mi_dat_add[count])
                break;
        }
        arg_Now = count; //记录当前参数
        bytes = (mi_dat_add[arg_Now + arg_num ] - mi_dat_add[arg_Now]);
    }
    return bytes;
}

/*************************************
Function: Register2_Write 
Description: 写寄存器2参数
Input: 源数据指针dat 寄存器地址 寄存器数量
Output: 无
 *************************************/
void Register2Write(u8 * dat, u16 reg_add, u8 bytes) {
    u8 count = 0; //声明计数变量      
    u16 add_base = reg_add - mi_arg_add[0]; //获取地址偏移量
    //    u8 bytes = GetSize(reg_add, arg_num);

    while (count < bytes) {
        Register2[add_base + count] = *(dat + count); //寄存器导入参数
        count++;
    }
}

/*************************************
Function: Register2_Read 
Description: 读取寄存器2
Input: 数据源指针dat 寄存器地址reg_add  字节数bytes 
Output: 无
 *************************************/
void Register2Read(u8* dat, u16 reg_add, u8 bytes) {
    u8 count = 0;
    u16 add_base = reg_add - mi_arg_add[0];

    for (count = 0; count < bytes; count++)
        *(dat + count) = Register2[count + add_base];
}

//void GetArgForTest(void) {
//    //    u8 *ptr = Register2;
//    u8 ReceiveBuffer[50] = {
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//    };
//    float Vm_f[2];
//    //计算数据
//    Vm_f[0] = floor(gPulseCount / 10 / 10000); //初始值为124889  =1
//    Vm_f[1] = gPulseCount % 100000 * 1.0 / 10; //  =2488.9
//    FloatToChar(Vm_f, ReceiveBuffer + mi_dat_add[mp_Vm]); //工况总量1
//    FloatToChar(Vm_f + 1, ReceiveBuffer + mi_dat_add[mp_Vm] + 4); //工况总量2
//    RTCReadTime(ReceiveBuffer + mi_dat_add[mp_time]); //时间
//}

/*关于寄存器1的操作*/
bool EnRegister1(u8 * ptr_dat) {
    u8 cnt_For;

    for (cnt_For = 0; cnt_For < 19; cnt_For++)
        Register1[Reg1Argbits.Buffer_ID][cnt_For] = *(ptr_dat + cnt_For);
    Reg1Argbits.Buffer_ID += 1; //如果是gCnt_Reg1=0的话，数据是24组或是没有，处理一个是当前通道号，另一个是累计的数据
    Reg1Argbits.Record += 1;
    Reg1Argbits.Buffer_ID = Reg1Argbits.Buffer_ID % REG1_MAX_CNT; //cnt_Reg1取16的余数+1 0-23
    return true;
}

void GetRegister1(u8 *ptr_dat, u8 reg_cnt) {
    u8 cnt_For;
    //    u8 cnt_Reg1 = gCnt_Reg1; //把可用的通道记录下来
    for (cnt_For = 0; cnt_For < 19; cnt_For++) {
        *(ptr_dat + cnt_For) = Register1[reg_cnt][cnt_For];
        //        Register1[reg_cnt][cnt_For] = 0;
    }//如果数据没有取到的话
}

void EmptyRegister1(void) {
    u8 cnt_For, cnt_Reg;
    for (cnt_Reg = 0; cnt_Reg < REG1_MAX_CNT; cnt_Reg++)
        for (cnt_For = 0; cnt_For < 19; cnt_For++)
            Register1[cnt_Reg][cnt_For] = 0;
    Reg1Argbits.Buffer_ID = Reg1Argbits.Record = 0;
}

void Refresh_RTCC_Pulse(void) {
    //RTCC_Check
    u8 tmp[6] = {0, 0, 0, 0};
    StopRTCC();
    CheckRTCC(); //写入RTCC中
    StartRTCC();
    Register2Read(tmp, mi_arg_add[mi_ofst], 4);
    gPulseCount = tmp[3]+((u16) tmp[2] << 8)+((u32) tmp[1] << 16)+((u32) tmp[0] << 24);
    //    Nop();
}



