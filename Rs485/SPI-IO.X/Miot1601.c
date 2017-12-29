#include "user.h"
#include "25L64B.h"
//#include "SPI.h"
#include "Miot1601.h"
#include "RS485.h"
#include "math.h"
/*********************************************
 * REG1: ����洢���ݼĴ�����һ������
 * REG2��MIOT1601�����Ĵ�����һ������
 * REG3�����ͻ������ݼĴ������������ݣ�BUF1����24����ָ��ʱ��ɼ����ݣ�BUF2���ڴ�ű������ǲ��Ե�����
 ***********************************************/
//ͨ������
const u8 Mi_Arg1[7] = {32, 40, 50, 80, 100, 150, 200};
const u8 Mi_Arg2[3] = {1, 10, 100};
const u8 Ver[5] = {'3', '.', '5', '.', '6'};
/*static*/
u8 Register3Buffer1[REG3_BUF1_CNT][REG3_BYTES]; //���ڴ�Ųɼ�������
u8 Register3Buffer2[REG3_BYTES]; //���ڴ�ű����Ͳ��Ե�����
struct Reg3_Record Reg3_Buf1_Recordbits; //�ɼ��������Ͳ���

//ģ�������ʼ��
///*static*/ u8 Register1[REG1_BYTES]; //debug1
/*static*/ u8 Register2[REG2_BYTES] = {
    0x08, 0x7F, 0xF9, 0x02, 0x01, 0x00, 0x00, 0x00, 0x09, 0x02,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x20, 0x17, 0x05, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x0A, 0x00, 0x00, 0x01, //10���Ӳɼ�һ�Σ�10�����ϴ�һ�Σ������豸��֤
    0x04, 0x00, 0x01, 0x03, 0x42, 0xF0, 0x00, 0x00, 0x42, 0xB4,
    0x00, 0x00, 0x42, 0x48, 0x00, 0x00, 0x40, 0xA0, 0x00, 0x00,
    0x40, 0x0A, 0xE1, 0x48, 0x00, 0x00, 0x00, 0x00//��ѹ����������
};

const u8 REG2_Arg_Postion[REG2_ARG_NUM + 1] = {
    0, 1, 9, 10, 16, 18, 19, 20, 21, 22,
    23, 25, 27, 29, 30, 31, 32, 33, 34, 38,
    42, 46, 50, 54, 58
};

/*************************************
Function: GetSize 
Description: ��ȡ���ݳ���
Input: �Ĵ�����ַ �Ĵ�������
Output: ���ݳ���
 *************************************/
u8 GetSize(u16 reg_add, u8 arg_num) {//�����жϺ���ִ��
    u8 arg_Now = 0;
    u8 bytes = 0; // count = 0;

    for (arg_Now = 0; arg_Now < REG2_ARG_NUM; arg_Now++) //�жϵ�ǰ�������ĸ�
    {
        if (reg_add == REG2_Arg_Postion[arg_Now])
            break;
    }
    bytes = REG2_Arg_Postion[arg_num + arg_Now] - REG2_Arg_Postion[arg_Now];
    return bytes;
}

/*************************************
Function: Register2_Write 
Description: д�Ĵ���2����
Input: Դ����ָ��dat �Ĵ�����ַ �Ĵ�������
Output: ��
 *************************************/
void Register2Write(u8 * dat, const u8 reg_add, const u8 bytes) {
    u8 count = 0; //������������      
    //    u16 add_base = reg_add - REG2_Arg_Postion[0]; //��ȡ��ַƫ����

    while (count < bytes) {
        Register2[reg_add + count] = *(dat + count); //�Ĵ����������
        count++;
    }
}

/*************************************
Function: Register2_Read 
Description: ��ȡ�Ĵ���2
Input: ����Դָ��dat �Ĵ�����ַreg_add  �ֽ���bytes 
Output: ��
 *************************************/
void Register2Read(u8* dat, const u8 reg_add, const u8 bytes) {
    u8 count = 0;
    //    u16 add_base = reg_add - REG2_Arg_Postion[0];

    for (count = 0; count < bytes; count++)
        *(dat + count) = Register2[count + reg_add];
}

/*************************************
Function: EnRegister1 
Description: д��ɼ����ݵ��Ĵ���1��
Input: ������ѡ��BufferCnt������Դָ��ptr_dat
Output: ��
 *************************************/
void EnRegister1(u8 BufferCnt, u8 * ptr_dat) {
    u8 cnt_For;

    switch (BufferCnt) {
        case REG3_BUF1:
        {
            for (cnt_For = 0; cnt_For < REG1_BYTES; cnt_For++)
                Register3Buffer1[Reg3_Buf1_Recordbits.Buffer_ID][cnt_For] = *(ptr_dat + cnt_For);
            Reg3_Buf1_Recordbits.Buffer_ID += 1; //�����gCnt_Reg1=0�Ļ���������24�����û�У�����һ���ǵ�ǰͨ���ţ���һ�����ۼƵ�����
            Reg3_Buf1_Recordbits.Record += 1;
            Reg3_Buf1_Recordbits.Buffer_ID = Reg3_Buf1_Recordbits.Buffer_ID % REG3_BUF1_CNT; //cnt_Reg1ȡ16������+1 0-23
            break;
        }
        case REG3_BUF2:
        {
            for (cnt_For = 0; cnt_For < REG3_BYTES; cnt_For++)
                Register3Buffer2[cnt_For] = *(ptr_dat + cnt_For);
            break;
        }
        default:break;
    }
}

/*************************************
Function: GetRegister1 
Description: ��ȡ�ɼ����ݵ��Ĵ���1��
Input: ������ѡ��BufferCnt������Դָ��ptr_dat��ָ��ͨ��reg_cnt
Output: ��
 *************************************/
void GetRegister1(u8 BufferCnt, u8 *ptr_dat, u8 reg_cnt) {
    u8 cnt_For;
    //    u8 cnt_Reg1 = gCnt_Reg1; //�ѿ��õ�ͨ����¼����
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
Description:��ռĴ���1������1������
Input: ��
Output: ��
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
    CheckRTCC(); //д��RTCC��
    StartRTCC();
    Register2Read(tmp, REG2_Arg_Postion[mi_ofst], 4);
    gPulseCount = tmp[3]+((u16) tmp[2] << 8)+((u32) tmp[1] << 16)+((u32) tmp[0] << 24);
    //    Nop();
}



