#define I2C_EERAM_ENABLED

#ifdef I2C_EERAM_ENABLED

#ifndef _I2C_EERAM_APP_H_
#define _I2C_EERAM_APP_H_

#include "../mcc.h"

#include "../i2c1.h"

#include <stdint.h>   

#define EERAMSIZE     2048

        
typedef uint8_t I2C_CHANNEL;
#define I2C_EERAM_CH0 0
#define I2C_EERAM_CH1 1
#define I2C_EERAM_CH2 2
#define I2C_EERAM_CH3 3
#define I2C_EERAM_MSSP 4
#define I2C_EERAM_MSSP1 5
#define I2C_EERAM_MSSP2 6

typedef struct
{
  unsigned char busAddress; ///< Slave Address bits A2, A1
  I2C_CHANNEL channel; ///< I2C channel identifier
} I2C_EERAM_T;

typedef union statusRegister
{
  unsigned char value;
  struct {
  unsigned AM      :1; ///< Array Modified bit
  unsigned RESERVED:2; ///< Additional byte-wide padding, bits not used in status register
  unsigned BP      :3; ///< Block Protect bits
  unsigned ASE     :1; ///< Auto Store Enable bit
  unsigned EVENT   :1; ///< Event bit
  };
} I2C_EERAM_STATUS_REGISTER_T;


/** @enum ERR_STATUS_T 
 * Defines the error codes returned from I2C API.
 */
typedef enum
{
    ERR_I2C_MESSAGE_FAIL,           /**< The I2C communication failed.*/
    ERR_I2C_MESSAGE_PENDING,        /**< The I2C communication is stuck. Usually, this is because of wrong MCC settings.*/
    ERR_I2C_MESSAGE_COMPLETE,       /**< The communication was successful.*/
    ERR_I2C_STUCK_START,            /**< Other I2C error*/
    ERR_I2C_MESSAGE_ADDRESS_NO_ACK, /**< Other I2C error*/
    ERR_I2C_DATA_NO_ACK,            /**< Other I2C error*/
    ERR_I2C_LOST_STATE              /**< Other I2C error*/
} ERR_STATUS_T;

#define BP_NONE_BITS       0x00
#define BP_UPPER64_BITS    0x04
#define BP_UPPER32_BITS    0x08
#define BP_UPPER16_BITS    0x0C
#define BP_UPPER8_BITS     0x10
#define BP_UPPER4_BITS     0x14
#define BP_UPPER2_BITS     0x18
#define BP_ALLBLOCKS_BITS  0x1C
#define ASE_BIT            0x02
#define EVENT_BIT          0x01

extern I2C_EERAM_T eeram;
/**
 * \brief I2C Write wrapper function. It calls MCC generated code for the selected I2C peripheral
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	data				    pointer of unsigned char type, pointing to the data to be written
 * @param	[in]	size				    number of bytes to be written
 * @param	[in]	busAddress  		    unsigned char, value of the most significant 7 bits of the control byte
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 *
 * Example Usage:
 * @code
 *	I2Cx_MasterWrite(eeramInstance, dataPtr, 10, 0x50, &status); 
 *  Writes 10 bytes starting from dataPtr+2, starting at address *dataPtr. EERAM has address pins A2 and A1 tied to GND.
 * @endcode
 */
void I2Cx_MasterWrite(I2C_EERAM_T * eeramInstance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_STATUS_T *pstatus);


/**
 * \brief I2C read wrapper function. It calls MCC generated code for the selected I2C peripheral
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	data				    pointer of unsigned char type, pointing to the data to be written
 * @param	[in]	size				    number of bytes to be written
 * @param	[in]	busAddress  		    unsigned char, value of the most significant 7 bits of the control byte
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 *
 * Example Usage:
 * @code
 *	I2Cx_MasterRead(eeramInstance, dataPtr, 10, 0x50, &status); 
 *  Reads 10 bytes into dataPtr+2, starting from address *dataPtr.  EERAM has address pins A2 and A1 tied to GND.
 * @endcode
 */
void I2Cx_MasterRead (I2C_EERAM_T * eeramInstance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_STATUS_T *pstatus);


/**
 * \brief Function for performing a sequential byte write into the EERAM starting at a specified address
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	data				    pointer of unsigned char type, pointing to the data to be written
 * @param	[in]	size				    number of bytes to be written
 * @param	[in]	startAddress            unsigned integer representing the address at which the write starts
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 *
 * Example Usage:
 * @code
 *	I2C_EERAM_SequentialWrite(eeramInstance,dataPtr,10,0x0012); 
 *  Writes 10 bytes from data, starting at address 0x0012
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_SequentialWrite		(I2C_EERAM_T * eeramInstance, uint8_t * data, uint16_t size, uint16_t startAddress);


/**
 * \brief Function for performing a single byte write into the EERAM at a specified address
 *
 * @param [in]  	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param [in]		data				    unsigned char to be written
 * @param [in]		address				    unsigned integer representing the address at which the write occurs
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_ByteWrite(&eeramInstance, 0x58,0x0012); 
 *  Writes character 'X' at address 0x12;
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_ByteWrite				(I2C_EERAM_T * eeramInstance, uint8_t data, uint16_t address);


/**
 * \brief Function for performing a sequential byte read into the EERAM starting at the address in the EERAM's internal address pointer
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	data				    pointer of unsigned char type, pointing to data that has been read
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_CurrentAddressRead(&eeramInstance,dataPtr); 
 *  Reads a byte from the EERAM into dataPtr, starting at the address in the EERAM's internal address pointer
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_CurrentAddressRead (I2C_EERAM_T * eeramInstance, uint8_t * data);


/**
 * \brief Function for performing a sequential byte read from the EERAM starting at a specified address
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	data				    pointer of unsigned char type, pointing to data that has been read
 * @param	[in]	size				    number of bytes to be read
 * @param	[in]	startAddress            unsigned integer representing the address at which the read starts
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_RandomAddressRead(eeramInstance,dataPtr,10,0x0012); 
 *  Reads 10 bytes from the EERAM into dataPtr, starting from address 0x0012
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_RandomAddressRead  (I2C_EERAM_T * eeramInstance, uint8_t * data, uint16_t size, uint16_t startAddress);


/**
 * \brief Function for getting the value of the EERAM's Status Register
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	statusVal			    pointer of unsigned char type, pointing to data that has been read
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_StatusRegisterGet(&eeramInstancem, dataPtr); 
 *  Reads the Status Register into dataPtr
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_StatusRegisterGet (I2C_EERAM_T * eeramInstance, uint8_t *statusVal);


/**
 * \brief Function for setting the value of the EERAM's Status Register modifiable bits
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	statusVal			    pointer of unsigned char type, pointing to the data to be written
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_CommandRegisterSet(&eeramInstance,dataPtr); 
 *  Reads the Status Register into dataPtr
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_StatusRegisterSet (I2C_EERAM_T * eeramInstance, uint8_t statusVal);


/**
 * \brief Function for setting the value of the EERAM's Command Register
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	statusVal			    pointer of unsigned char type, pointing to the data to be written
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_CommandRegisterSet(&eeramInstance,dataPtr); 
 *  Reads the Status Register into dataPtr
 * @endcode
 */
ERR_STATUS_T I2C_EERAM_CommandRegisterSet (I2C_EERAM_T * eeramInstance, uint8_t statusVal);


/**
 * \brief Function for getting the value of the EERAM's BP (Block Protect) bits
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[out]	bpVal			    	pointer of unsigned char type, pointing to data that has been read
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 *  
 * Example Usage:
 * @code
 *	I2C_EERAM_BlockProtectBitsGet(dataPtr); 
 *  Reads the Block Protect bits into dataPtr
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_BlockProtectBitsGet	(I2C_EERAM_T * eeramInstance, uint8_t *bpVal);


/**
 * \brief Function for setting the value of the EERAM's BP (Block Protect) bits
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	bpVal				    unsigned char type, containing the value to be written
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 *  
 * Example Usage:
 * @code
 *	I2C_EERAM_BlockProtectBitsSet(0x3); 
 *  Write 0x3 to the Block Protect bits; Upper 1/16 of array is write-protected
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_BlockProtectBitsSet	(I2C_EERAM_T * eeramInstance, uint8_t bpVal);


/**
 * \brief Function for getting the value of the Auto Store Enable Bit
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	aseVal				    pointer of unsigned char type, pointing to data that has been read
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_AutoStoreEnableBitGet(dataPtr); 
 *  Reads the Auto Store Enable bit into dataPtr
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_AutoStoreEnableBitGet	(I2C_EERAM_T * eeramInstance, uint8_t *aseVal);


/**
 * \brief Function for setting the value of the Auto Store Enable Bit
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	aseVal				    unsigned char type, containing the value to be written
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_AutoStoreEnableBitSet(0x1); 
 *  Set the Auto Store Enable bit
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_AutoStoreEnableBitSet	(I2C_EERAM_T * eeramInstance, uint8_t aseVal);


/**
 * \brief Function for reading the value of the Event bit
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	eventVal			    pointer of unsigned char type, pointing to data that has been read
  * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 *  
 * Example Usage:
 * @code
 *	I2C_EERAM_EventStatusBitGet(dataPtr); 
 *  Reads the Event bit into dataPtr
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_EventStatusBitGet		(I2C_EERAM_T * eeramInstance, uint8_t *eventVal);


/**
 * \brief Function for clearing the Event bit
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_EventStatusBitClear(); 
 *  Clears the Event bit
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_EventStatusBitClear		(I2C_EERAM_T * eeramInstance);


/**
 * \brief Function for reading the value of the Array Modified bit
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @param	[in]	amVal       		    pointer of unsigned char type, pointing to data that has been read
 * @retval			ERR_I2C_MESSAGE_COMPLETE read successful
 * @retval			other           		read failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_ArrayModifiedBitGet(dataPtr); 
 *  Reads the Array Modified bit into dataPtr
 * @endcode
 * @see Section 2.4.1 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_ArrayModifiedBitGet(I2C_EERAM_T * eeramInstance, uint8_t *amVal);


/**
 * \brief Function for performing a manual Store operation
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_SoftwareStore(); 
 *  Performs a manual Store
 * @endcode
 * @see Section 2.4.2 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_SoftwareStore			(I2C_EERAM_T * eeramInstance);


/**
 * \brief Function for performing a Software Recall
 *
 * @param	[in]	eeramInstance 		    pointer of I2C_EERAM_T type
 * @retval			ERR_I2C_MESSAGE_COMPLETE write successful
 * @retval			other           		write failed
 * 
 * Example Usage:
 * @code
 *	I2C_EERAM_SoftwareRecall(); 
 *  Performs a Software Recall
 * @endcode
 * @see Section 2.4.2 of the Datasheet
 */
ERR_STATUS_T I2C_EERAM_SoftwareRecall		(I2C_EERAM_T * eeramInstance);


/**
 * \brief Function for creating or modifying an I2C_EERAM_T object with given parameters
 *
 * @param	[in]	eeramInstance 		pointer of I2C_EERAM_T type
 * @param	[in]	busAddress			value for A2 and A1 bits	
 * @param	[in]	channel 			value for the chosen I2C channel  
 * @retval			I2C_EERAM_T		    pointer to modified I2C_EERAM_T structure 
 *
 * Example Usage:
 * @code
 * I2C_EERAM_T newEeramInstance;
 * I2C_EERAM_EeramInstanceAppend(&newEeramInstance,0x03, I2C_1);
 * @endcode
 */
I2C_EERAM_T* I2C_EERAM_EeramInstanceAppend(I2C_EERAM_T *eeramInstance, uint8_t busAddress, I2C_CHANNEL channel);


/**
 * \brief Function for initializing an instance of I2C_EERAM_T with default values passed from MCC
 *
 * @param	[in]	eeramInstance 		pointer of I2C_EERAM_T type
 * 
 * Example Usage:
 * @code
 * I2C_EERAM_T newEeramInstance;
 * I2C_EERAM_Initialize(&newEeramInstance);
 * @endcode
 */
void I2C_EERAM_Initialize(I2C_EERAM_T *eeramInstance);

#endif

#endif