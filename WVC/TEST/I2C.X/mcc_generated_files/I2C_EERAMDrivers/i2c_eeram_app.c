/**
 * \file I2C_EERAM_app.c
 * \brief Header file containing implementations for EERAM API Function Library with MCC
 * \brief v1.1
 * \author Dragos Ciofu
 * \date December 2016

 *
 * @see www.microchip.com
 */

#include "i2c_eeram_app.h"

#ifdef I2C_EERAM_ENABLED

#define I2C_EERAM_GENERIC_RETRY_MAX           5
#define I2C_EERAM_GENERIC_DEVICE_TIMEOUT      50000   // define slave timeout 
#define I2C_EERAM_GENERIC_SLAVE_TIMEOUT      50000

uint8_t eeramBuffer[64];

void I2Cx_MasterWrite(I2C_EERAM_T * eeramInstance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_STATUS_T *pstatus)
{   
    switch(eeramInstance->channel){
        case I2C_EERAM_CH0:
        break;
        
        case I2C_EERAM_CH1:
            I2C1_MasterWrite(data, size, busAddress,((I2C1_MESSAGE_STATUS *)pstatus));
        break;
        
        case I2C_EERAM_CH2:
        break;
        
        case I2C_EERAM_CH3:
        break;
        
        case I2C_EERAM_MSSP:
        break;

        case I2C_EERAM_MSSP1:
        break;

        case I2C_EERAM_MSSP2:
        break;
    }      
}

void I2Cx_MasterRead(I2C_EERAM_T * eeramInstance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_STATUS_T *pstatus)
{
    switch(eeramInstance->channel){
        case I2C_EERAM_CH0:
        break;
        
        case I2C_EERAM_CH1:
            I2C1_MasterRead(data, size, busAddress,((I2C1_MESSAGE_STATUS *)pstatus));
        break;
        
        case I2C_EERAM_CH2:
        break;
        
        case I2C_EERAM_CH3:
        break;
        
        case I2C_EERAM_MSSP:
        break;
        case I2C_EERAM_MSSP1:
        break;
        case I2C_EERAM_MSSP2:
        break;
    }  
}

ERR_STATUS_T I2C_EERAM_SequentialWrite	   (I2C_EERAM_T * eeramInstance, uint8_t * data, uint16_t size, uint16_t startAddress)
{   
    static uint16_t        counter, timeOut, slaveTimeOut;

    eeramBuffer[0] = (startAddress >> 8);                // high address
    eeramBuffer[1] = (uint8_t)(startAddress);            // low low address
    
    for (counter=0;counter < size;counter++)
        eeramBuffer[counter+2]=*(data+counter);
         
    timeOut = 0;
    slaveTimeOut = 0;
    
    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;
    while(status != ERR_I2C_MESSAGE_FAIL)
    {
        I2Cx_MasterWrite(eeramInstance, eeramBuffer, size+2, eeramInstance->busAddress, &status);
        while(status == ERR_I2C_MESSAGE_FAIL)
        {                
            if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                break;
            else
                slaveTimeOut++;
        } 
        if ((slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT) || 
            (status == ERR_I2C_MESSAGE_COMPLETE))
            break;
        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            return ERR_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }
    return status;    
}

ERR_STATUS_T I2C_EERAM_ByteWrite (I2C_EERAM_T * eeramInstance, uint8_t data, uint16_t startAddress)
{
     return I2C_EERAM_SequentialWrite	   ( eeramInstance, &data, 1, startAddress);
}

ERR_STATUS_T I2C_EERAM_CurrentAddressRead (I2C_EERAM_T * eeramInstance, uint8_t * data)
{
    static uint16_t timeOut, slaveTimeOut;

    timeOut = 0;
    slaveTimeOut = 0;

    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;
   
    while(status != ERR_I2C_MESSAGE_FAIL)
    {           
        I2Cx_MasterRead(eeramInstance, eeramBuffer, 1,  eeramInstance->busAddress, &status);
        while(status == ERR_I2C_MESSAGE_PENDING)
        {
            if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                return (0);
            else
                slaveTimeOut++;
        }
        if (status == ERR_I2C_MESSAGE_COMPLETE)
            break;           
        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    *data = eeramBuffer[0];
    return status;
    
}

ERR_STATUS_T I2C_EERAM_RandomAddressRead  (I2C_EERAM_T * eeramInstance, uint8_t * data, uint16_t size, uint16_t startAddress)
{
   
    uint16_t    timeOut, slaveTimeOut, i;  
     
    eeramBuffer[0] = (startAddress >> 8);                        // high address
    eeramBuffer[1] = (uint8_t)(startAddress);                    // low low address

    timeOut = 0;
    slaveTimeOut = 0;
    
    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;
    while(status != ERR_I2C_MESSAGE_FAIL)
    {
        I2Cx_MasterWrite(eeramInstance,  eeramBuffer, 2, eeramInstance->busAddress, &status);
        while(status == ERR_I2C_MESSAGE_PENDING)
        {                
            if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                break;
            else
                slaveTimeOut++;
        } 
        if ((slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT) || 
            (status == ERR_I2C_MESSAGE_COMPLETE))
            break;
        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            return ERR_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }
    
    if (status == ERR_I2C_MESSAGE_COMPLETE)
    {
        timeOut = 0;
        slaveTimeOut = 0;
        
        while(status != ERR_I2C_MESSAGE_FAIL)
        {           
            I2Cx_MasterRead(eeramInstance, eeramBuffer, 1,  eeramInstance->busAddress, &status);
            while(status == ERR_I2C_MESSAGE_PENDING)
            {
                if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                    return (0);
                else
                    slaveTimeOut++;
            }
            if (status == ERR_I2C_MESSAGE_COMPLETE)
                break;           
            if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
                break;
            else
                timeOut++;
        }
    }
    for (i = 0 ; i < size ; i++)
        data[i] = eeramBuffer[i+2];
    return status;
}  

ERR_STATUS_T I2C_EERAM_StatusRegisterGet (I2C_EERAM_T * eeramInstance, uint8_t *statusVal)
{

    static uint16_t    timeOut, slaveTimeOut;

    timeOut = 0;
    slaveTimeOut = 0;
    
    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;
    while(status != ERR_I2C_MESSAGE_FAIL)
    {
        I2Cx_MasterRead(eeramInstance, eeramBuffer, 1,(eeramInstance->busAddress & 0x06) | 0x18, &status);
        while(status == ERR_I2C_MESSAGE_PENDING)
        {
            if (slaveTimeOut == I2C_EERAM_GENERIC_SLAVE_TIMEOUT)
                return ERR_I2C_MESSAGE_FAIL;
            else
                slaveTimeOut++;
        }
        if ((slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT) || 
            (status == ERR_I2C_MESSAGE_COMPLETE))
            break;

        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            return ERR_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }
    *statusVal=eeramBuffer[0];
    return status;
}

ERR_STATUS_T I2C_EERAM_StatusRegisterSet (I2C_EERAM_T * eeramInstance, uint8_t statusVal)
{
    static uint16_t timeOut, slaveTimeOut;    

    eeramBuffer[0] = 0x00;
    eeramBuffer[1] = statusVal;
 
    timeOut = 0;
    slaveTimeOut = 0;

    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;    
    while(status != ERR_I2C_MESSAGE_FAIL)
    {
        I2Cx_MasterWrite(eeramInstance, eeramBuffer, 2, (eeramInstance->busAddress& 0x06) |0x18 , &status);

        while(status == ERR_I2C_MESSAGE_PENDING)
        {                
            if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                return ERR_I2C_MESSAGE_FAIL;
            else
                slaveTimeOut++;
        } 
        if ((slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT) || 
            (status == ERR_I2C_MESSAGE_COMPLETE))
            break;
        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    } 
    return status;  
}

ERR_STATUS_T I2C_EERAM_CommandRegisterSet (I2C_EERAM_T * eeramInstance, uint8_t cmdVal)
{
    static uint16_t timeOut, slaveTimeOut;

    eeramBuffer[0] = 0x55;       
    eeramBuffer[1] = cmdVal;
 
    timeOut = 0;
    slaveTimeOut = 0;
    

    ERR_STATUS_T status = ERR_I2C_MESSAGE_PENDING;  
    while(status != ERR_I2C_MESSAGE_FAIL)
    {
        I2Cx_MasterWrite(eeramInstance, eeramBuffer, 2, (eeramInstance->busAddress& 0x06) |0x18 , &status);

        while(status == ERR_I2C_MESSAGE_PENDING)
        {                
            if (slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT)
                return ERR_I2C_MESSAGE_FAIL;
            else
                slaveTimeOut++;
        } 
        if ((slaveTimeOut == I2C_EERAM_GENERIC_DEVICE_TIMEOUT) || 
            (status == ERR_I2C_MESSAGE_COMPLETE))
            break;

        if (timeOut == I2C_EERAM_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    return status;
}


ERR_STATUS_T I2C_EERAM_BlockProtectBitsGet	(I2C_EERAM_T * eeramInstance, uint8_t *bpVal)
{
    ERR_STATUS_T status;
    uint8_t temp;
    status = I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    temp = temp & 0x18;
    *bpVal=temp;  
    return status;
}


ERR_STATUS_T I2C_EERAM_BlockProtectBitsSet	(I2C_EERAM_T * eeramInstance, uint8_t bpVal)
{
    uint8_t temp;
    I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    temp &= ~0x18;
    temp |= bpVal;    
    return I2C_EERAM_StatusRegisterSet(eeramInstance,temp); 
}


ERR_STATUS_T I2C_EERAM_AutoStoreEnableBitGet	(I2C_EERAM_T * eeramInstance, uint8_t *aseVal)
{
    ERR_STATUS_T status;
    uint8_t temp;
    status = I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    *aseVal= temp & 0x2;
    return status;    
}


ERR_STATUS_T I2C_EERAM_AutoStoreEnableBitSet	(I2C_EERAM_T * eeramInstance, uint8_t aseVal)
{
    uint8_t temp;
    I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    temp &= ~0x2; 
    temp |= aseVal << 1;    
    return I2C_EERAM_StatusRegisterSet(eeramInstance,temp);     
}


ERR_STATUS_T I2C_EERAM_EventStatusBitGet(I2C_EERAM_T * eeramInstance, uint8_t *eventVal)
{
    ERR_STATUS_T status;
    uint8_t temp;
    status = I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    *eventVal= (temp & 0x01);
    return status;     
}

ERR_STATUS_T I2C_EERAM_EventStatusBitClear		(I2C_EERAM_T * eeramInstance)
{
    uint8_t temp;
    I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    temp &= ~0x01;   
    return I2C_EERAM_StatusRegisterSet(eeramInstance,temp);       
}

ERR_STATUS_T I2C_EERAM_ArrayModifiedBitGet		(I2C_EERAM_T * eeramInstance, uint8_t *amVal)
{
    ERR_STATUS_T status;
    uint8_t temp;
    status = I2C_EERAM_StatusRegisterGet (eeramInstance,&temp);
    *amVal= (temp & 0x80) >> 7;
    return status;      
}

ERR_STATUS_T I2C_EERAM_SoftwareStore			(I2C_EERAM_T * eeramInstance)
{
    return I2C_EERAM_CommandRegisterSet (eeramInstance, 0x33);    
}


ERR_STATUS_T I2C_EERAM_SoftwareRecall		(I2C_EERAM_T * eeramInstance)
{
    return I2C_EERAM_CommandRegisterSet (eeramInstance, 0xDD);    
}

I2C_EERAM_T* I2C_EERAM_EeramInstanceAppend(I2C_EERAM_T * eeramInstance, uint8_t busAddress, I2C_CHANNEL channel)
{    
    eeramInstance->busAddress=busAddress;
    eeramInstance->channel=channel;
    return eeramInstance;
}



void I2C_EERAM_Initialize(I2C_EERAM_T *eeram)
{
    eeram->channel=I2C_EERAM_CH1;

    eeram->busAddress=0x50;
    
}
#endif