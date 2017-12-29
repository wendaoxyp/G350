#include "user.h"
#include "25L64B.h"
//#include "SPI.h"
#include "Miot1601.h"
#include "RS485.h"
#include "math.h"
#include "CheckData.h"
/*********************************************
 * REG1: 铁电存储数据寄存器。一组数数
 * REG2：MIOT1601参数寄存器。一组数据
 * REG3：发送缓冲数据寄存器。两组数据：BUF1用于24组存放指定时间采集数据，BUF2用于存放报警或是测试的数据
 ***********************************************/
//通径参数
//const u8 Mi_Arg1[7] = {32, 40, 50, 80, 100, 150, 200};
//const u8 Mi_Arg2[3] = {1, 10, 100};
const u8 Ver[5] = {"1.0.1"};
/*static*/
u8 Register3Buffer1[REG3_BUF1_CNT][REG3_BYTES]; //用于存放采集的数据
u8 Register3Buffer2[REG3_BYTES]; //用于存放报警和测试的数据
struct Reg3_Record Reg3_Buf1_Recordbits; //采集数据类型参数
struct MiotArgs miotArgs; //MIOT的参数
extern u8 AlarmType;

//模块参数初始化
///*static*/ u8 Register1[REG1_BYTES]; //debug1
/*static*/ u8 Register2[REG2_BYTES] = {
    0x08, 0x7F, 0xF9, 0x02, 0x01, 0x00, 0x00, 0x00, 0x08, 0x02,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x20, 0x17, 0x05, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x0A, 0x00, 0x00, 0x01, //10分钟采集一次，10分钟上传一次，便于设备验证
    0x04, 0x00, 0x01, 0x03, 0x42, 0xF0, 0x00, 0x00, 0x42, 0xB4,
    0x00, 0x00, 0x42, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x59, 0x99, 0x9A, 0x00, 0x00, 0x00, 0x00//电压和脉冲总数
};
//static u8 Register2_tmp[REG2_BYTES + 3];

const u8 REG2_Arg_Postion[REG2_ARG_NUM + 1] = {
    0, 1, 9, 10, 16, 18, 19, 20, 21, 22,
    23, 25, 27, 29, 30, 31, 32, 33, 34, 38,
    42, 46, 50, 54, 58
};

/*************************************
Function: GetSize 
Description: 获取数据长度
Input: 寄存器地址 寄存器数量
Output: 数据长度
 *************************************/
u8 GetSize(u16 reg_add, u8 arg_num) {//配套判断函数执行
    u8 arg_Now = 0;
    u8 bytes = 0; // count = 0;

    for (arg_Now = 0; arg_Now < REG2_ARG_NUM; arg_Now++) //判断当前参数是哪个
    {
        if (reg_add == REG2_Arg_Postion[arg_Now])
            break;
    }
    bytes = REG2_Arg_Postion[arg_num + arg_Now] - REG2_Arg_Postion[arg_Now];
    return bytes;
}

/*************************************
Function: Register2_Write 
Description: 写寄存器2参数
Input: 源数据指针dat 寄存器地址 寄存器数量
Output: 无
 *************************************/
void Register2Write(u8 * dat, const u8 reg_add, const u8 bytes) {
    u8 count = 0; //声明计数变量      
    //    u16 add_base = reg_add - REG2_Arg_Postion[0]; //获取地址偏移量

    while (count < bytes) {
        Register2[reg_add + count] = *(dat + count); //寄存器导入参数
        count++;
    }
}

/*************************************
Function: Register2_Read 
Description: 读取寄存器2
Input: 数据源指针dat 寄存器地址reg_add  字节数bytes 
Output: 无
 *************************************/
void Register2Read(u8* dat, const u8 reg_add, const u8 bytes) {
    u8 count = 0;
    //    u16 add_base = reg_add - REG2_Arg_Postion[0];

    for (count = 0; count < bytes; count++)
        *(dat + count) = Register2[count + reg_add];
}

/*************************************
Function: EnRegister1 
Description: 写入采集数据到寄存器1中
Input: 缓冲区选择BufferCnt，数据源指针ptr_dat
Output: 无
 *************************************/
void EnRegister1(u8 InputSource, u8 * ptr_dat) {
    u8 cnt_For;

    switch (InputSource) {
        case SampleData:
        {
            ptr_dat[mp_alarm + 1] = SampleData; //添加数据值报警位，表示该数据为正常数据
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)//different
                Register3Buffer1[Reg3_Buf1_Recordbits.Buffer_ID][cnt_For] = *(ptr_dat + cnt_For);
            Reg3_Buf1_Recordbits.Buffer_ID += 1; //如果是gCnt_Reg1=0的话，数据是24组或是没有，处理一个是当前通道号，另一个是累计的数据
            Reg3_Buf1_Recordbits.Record += 1;
            Reg3_Buf1_Recordbits.Buffer_ID = Reg3_Buf1_Recordbits.Buffer_ID % REG3_BUF1_CNT; //cnt_Reg1取16的余数+1 0-23
            break;
        }
        case AlarmData:
        {

            ptr_dat[mp_alarm + 1] = LowPowerData; //添加数据值报警位，表示该数据为现场采集一次的数据 
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                Register3Buffer2[cnt_For] = *(ptr_dat + cnt_For);
            break;
        }
        case LowPowerData:
        {
            ptr_dat[mp_alarm + 1] = AlarmType; //添加数据值报警位，表示该数据为现场采集一次的数据 
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                Register3Buffer2[cnt_For] = *(ptr_dat + cnt_For);
            break;
        }
        case TestData:
        {
            ptr_dat[mp_alarm + 1] = TestData; //添加数据值报警位，表示该数据为测试的数据
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                Register3Buffer2[cnt_For] = *(ptr_dat + cnt_For);
            break;
        }
        default:break;
    }
}

/*************************************
Function: GetRegister1 
Description: 读取采集数据到寄存器1中
Input: 缓冲区选择BufferCnt，数据源指针ptr_dat，指定通道reg_cnt
Output: 无
 *************************************/
void GetRegister1(u8 BufferCnt, u8 *ptr_dat, u8 reg_cnt) {
    u8 cnt_For;
    //    u8 cnt_Reg1 = Reg3_Buf1_Recordbits.Buffer_ID; //把可用的通道记录下来

    switch (BufferCnt) {
        case REG3_BUF1:
        {
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                *(ptr_dat + cnt_For) = Register3Buffer1[reg_cnt][cnt_For];
            break;
        }
        case REG3_BUF2:
        {
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                *(ptr_dat + cnt_For) = Register3Buffer2[cnt_For];
            break;
        }
        default:break;
    }
}

/*************************************
Function: EmptyRegister1 
Description:清空寄存器1缓冲区1的数据
Input: 无
Output: 无
 *************************************/
void EmptyRegister1(void) {
    u8 cnt_For, cnt_Reg;
    for (cnt_Reg = 0; cnt_Reg < REG3_BUF1_CNT; cnt_Reg++)
        for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
            Register3Buffer1[cnt_Reg][cnt_For] = 0;
    Reg3_Buf1_Recordbits.Buffer_ID = Reg3_Buf1_Recordbits.Record = 0;
}

void Refresh_RTCC_Pulse(void) {
    //RTCC_Check
    u8 tmp[6] = {0, 0, 0, 0};
    StopRTCC();
    CheckRTCC(); //写入RTCC中
    StartRTCC();
    Register2Read(tmp, REG2_Arg_Postion[reg2_mi_ofst], 4);
    gPulseCount = tmp[3]+((u16) tmp[2] << 8)+((u32) tmp[1] << 16)+((u32) tmp[0] << 24);
}
//刷新miot的参数

void OutputMiotArg(void) {//输出miot参数值结构体中
    u8 Register2_tmp[REG2_BYTES];
    Register2Read(Register2_tmp, REG2_Arg_Postion[REG2_Arg_Postion[reg2_mi_add]], REG2_BYTES); //导出数中获取miot参数数组 different    
    miotArgs.mi_add = Register2_tmp[REG2_Arg_Postion[reg2_mi_add]]; //导出miot地址
    CopyDat(miotArgs.mi_ID, Register2_tmp + REG2_Arg_Postion[reg2_mi_id], 8); //导出miot的ID号
    miotArgs.mp_add = Register2_tmp[REG2_Arg_Postion[reg2_mp_add]]; //导出设备地址
    miotArgs.timemp = (Register2_tmp[REG2_Arg_Postion[reg2_mi_tmp]] << 8) + Register2_tmp[REG2_Arg_Postion[reg2_mi_tmp] + 1];
    miotArgs.timegprs = (Register2_tmp[REG2_Arg_Postion[reg2_mi_tgprs]] << 8) + Register2_tmp[REG2_Arg_Postion[reg2_mi_tgprs] + 1];
    miotArgs.timealarm = (Register2_tmp[REG2_Arg_Postion[reg2_mi_talarm]] << 8) + Register2_tmp[REG2_Arg_Postion[reg2_mi_talarm] + 1];
    miotArgs.mi_sp = Register2_tmp[REG2_Arg_Postion[reg2_mi_sp]];
    CharToFloat(&miotArgs.AlarmLT, Register2_tmp + REG2_Arg_Postion[reg2_mi_lt_alarm]);
    CharToFloat(&miotArgs.AlarmHT, Register2_tmp + REG2_Arg_Postion[reg2_mi_ht_alarm]);
    CharToFloat(&miotArgs.AlarmLP, Register2_tmp + REG2_Arg_Postion[reg2_mi_lp_alarm]);
    CharToFloat(&miotArgs.AlarmHP, Register2_tmp + REG2_Arg_Postion[reg2_mi_hp_alarm]);
    CharToFloat(&miotArgs.AlarmVoltage, Register2_tmp + REG2_Arg_Postion[reg2_mi_lv_alarm]);
}

void SaveMiotArg(void) {//保存MIOT参数
    u16 CRC_Result = 0;
    u8 Register2_tmp[REG2_BYTES + 3];
    //    Register2Read(Register2_tmp, REG2_Arg_Postion[mi_add], REG2_BYTES); //导出数中获取miot参数数组 different    
    Register2Read(Register2_tmp, REG2_Arg_Postion[reg2_mi_add], REG2_BYTES);
    CRC_Result = CRC16_Check(Register2_tmp, REG2_BYTES);
    Register2_tmp[REG2_BYTES] = (u8) (CRC_Result & 0x00ff); //赋值CRC低8位
    Register2_tmp[REG2_BYTES + 1] = (u8) ((CRC_Result >> 8)&0x00ff); //赋值CRC高8位
    FM25L64B_Write(RST_Data, Register2_tmp, REG2_BYTES + 2); //将miot参数和校验码写入铁电中
}

bool LoadMiotArg(void) {//加载miot参数
    u8 Register2_tmp[REG2_BYTES + 3];
    Register2Read(Register2_tmp, REG2_Arg_Postion[reg2_mi_add], REG2_BYTES); //导出数中获取miot参数数组 different    
    FM25L64B_Read(RST_Data, Register2_tmp, REG2_BYTES + 2); //将miot参数从从铁电中加载值Register2中
    if (CheckIsRight(CRC16_Check, Register2_tmp, REG2_BYTES))
        Register2Write(Register2_tmp, REG2_Arg_Postion[reg2_mi_add], REG2_BYTES);
}

