/**
 *******************************************************************************
 * @file        TestCode_I2C_Master_Interrupt.c
 * @author      ABOV R&D Division
 * @brief       Contains the external function prototypes for TestCode
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/*******************************************************************************
* Pre-processor Definition & Macro
*******************************************************************************/
#include "main_conf.h"
#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
#include "i2c.h"
#ifdef TIMER21_ONESHOT_MODE
#include "timer21.h"
#endif

/** Select Test I2C Channel before project compile (Must be set a channel) */
//#define TEST_I2Cn	(0) // I2C0
//#define TEST_I2Cn	(1) // I2C1
#define TEST_I2Cn	(2) // I2C2

/** Max buffer length */
#define BUFFER_SIZE	(63) //KMS241125_2 Data Buffer Size (Excluded slave address byte size)
//#define LONG_BUFFER_SIZE (3958) //KMS241125_2 : This buffer size includes I2C sub-address also !!!
#define LONG_BUFFER_SIZE (1030) //KMS250314_2 : Max buffer size is defined by ADAU1452.c/ADAU1761.c and the size is 1020.

/** Max I2C Channel Number */
#define I2C_IP_INDEX_MAX			(3)


/** Slave Address Setting */
/** Master and Slave Address */
#define MASTER_ADDR	                (0xC0 >> 1) // Master Address
#ifdef I2C_1_SLAVE_ENABLE 
//## I2C_1(Slave Mode) = 8bit : 0xD4/7bit : 0x6A(TAS6422Q1) : A2B Recevier write only 4 Bytes(0x00:0x10, 0x03:0x44, 0x04:0x00, 0x05:0xFF)
//## I2C_0(Master Mode) = If I2C Switch is High(PF2 = 1), DSP/Ext.A2B is connected with I2C_0. If I2C Switch is Low(PF2 = 0), Codec ICs is connected with I2C_1.
#define SLAVE_ADDR	                (0x6A) // Slave Address
#else //I2C_1_SLAVE_ENABLE
#define SLAVE_ADDR	                (0xC0 >> 1) // Slave Address
#endif //I2C_1_SLAVE_ENABLE

#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4
#define READ_BUFFER_SIZE			(5)
#endif

/** INTERVAL TEST */
//#define INTERVAL_TEST

/** SCL Low Time-out Function */
//#define SCL_TIMEOUT //KMS241210_2 : This define makes A2B i2c communication error when master try to init peripheral of slave node.

/** Manual Bus Control Test */
//#define I2C_MANUAL_BUS_CONTROL //KMS241210_3 : Can't use this one


/*******************************************************************************
* Private Typedef
*******************************************************************************/
// I2C_PORT_Type Structure
typedef struct {
	// Base Address
	I2C_Type *pI2Cx;
 	// SCL
	PORT_Type *pSclPort;
	uint32_t SclPort_Number;
	PCU_ALT_FUNCTION_Type SclAltFunc;
	// SDA
	PORT_Type *pSdaPort;
	uint32_t SdaPort_Number;
	PCU_ALT_FUNCTION_Type SdaAltFunc;
	// Interrupt Handler
	IRQn_Type IRQ_Type;
	// Module Name
	uint8_t I2cName[5];
} I2Cn_PORT_Type;

#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4
I2C_S_SETUP_Type SlaveCfg;
#endif

/*******************************************************************************
* Private Variable
*******************************************************************************/
static const I2Cn_PORT_Type I2C_PORT_CFG[I2C_IP_INDEX_MAX] = {
#ifdef ESTEC_BOARD
#ifdef I2C_0_ENABLE
	{I2C0, (PORT_Type *)PF,  6, PCU_ALT_FUNCTION_2, (PORT_Type *)PF, 7, PCU_ALT_FUNCTION_2, I2C0_IRQn,       "I2C0"},
#endif
#ifdef I2C_1_ENABLE
	{I2C1, (PORT_Type *)PF,  0, PCU_ALT_FUNCTION_1, (PORT_Type *)PF, 1, PCU_ALT_FUNCTION_1, I2C1_IRQn,       "I2C1"},
#endif
#else //ESTEC_BOARD
	{I2C0, (PORT_Type *)PF,  6, PCU_ALT_FUNCTION_2, (PORT_Type *)PF, 7, PCU_ALT_FUNCTION_2, I2C0_IRQn,       "I2C0"},
//	{I2C0,              PD,  0, PCU_ALT_FUNCTION_1,              PD, 1, PCU_ALT_FUNCTION_1, I2C0_IRQn,       "I2C0"},
	{I2C1,              PA,  1, PCU_ALT_FUNCTION_1,              PA, 0, PCU_ALT_FUNCTION_1, I2C1_IRQn,       "I2C1"},
//	{I2C1, (PORT_Type *)PF,  0, PCU_ALT_FUNCTION_1, (PORT_Type *)PF, 1, PCU_ALT_FUNCTION_1, I2C1_IRQn,       "I2C1"},
	{I2C2,              PC,  6, PCU_ALT_FUNCTION_1,              PC, 5, PCU_ALT_FUNCTION_1, I2C2_SPI20_IRQn, "I2C2"},
#endif //ESTEC_BOARD
};

#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4
uint8_t SlaveReadBuffer[READ_BUFFER_SIZE] = {0,}; 
#endif

static const I2Cn_PORT_Type * i2c0_Master = &(I2C_PORT_CFG[0]);
static const I2Cn_PORT_Type * i2c1_Master = &(I2C_PORT_CFG[1]);

static Bool complete;  // Interrupt Flag
static Bool isMasterMode = TRUE; // Interrupt Master FLag

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
static void Buffer_Init(uint8_t* buffer, uint8_t type, uint16_t len);
static void I2C_ChannelConfig(const I2Cn_PORT_Type * pConfig, uint32_t Speed, I2Cn_Type Type);
static void Main_I2CnIRQHandler(I2C_Type *pI2Cx);

/*******************************************************************************
* Public Function
*******************************************************************************/

#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4
Bool Slave_Read_Buffer_Not_Empty(void)
{
#ifdef _I2C_1_DEBUG_MSG
	uint8_t i;
#endif
	Bool B_Ret = FALSE;

	if(SlaveReadBuffer[0])
	{
#ifdef _I2C_1_DEBUG_MSG
		for(i=0;i<5;i++)
			cprintf("0x%02x ", SlaveReadBuffer[i]);
#endif
		if(SlaveReadBuffer[0] == 0xD4) //KMS250306_3 : Just check wheter A2B Receiver get Amp data from A2B Master.  More condition : //&& SlaveReadBuffer[1] == 0x05 && SlaveReadBuffer[2] == 0xFF
			B_Ret = TRUE;
		else
			B_Ret = FALSE;
		
		Slave_Read_Init();
		
		return B_Ret;
	}
	else
	{
		B_Ret = FALSE;
		
		return B_Ret;
	}
}

void Slave_Read_Init(void)
{
	//-----------------------------------------------------------------------------------------------
	//| Slave Address | Data [0] | Data [1] | ... | Data [n] |
	//-----------------------------------------------------------------------------------------------
	Buffer_Init(SlaveReadBuffer, 0, READ_BUFFER_SIZE);
	SlaveCfg.rx_data = SlaveReadBuffer;
	SlaveCfg.rx_length = 5;

#ifdef _I2C_1_DEBUG_MSG
	cputs("\r\n Slave Read Test START\r\n");
#endif
	//complete=FALSE;
	HAL_I2C_SlaveReceiveData(i2c1_Master->pI2Cx, &SlaveCfg, I2C_TRANSFER_INTERRUPT);
	//while(!complete);
	__NOP();
#ifdef _I2C_1_DEBUG_MSG
	cputs("\r\n Slave Read Test OK \r\n");
#endif
}
#endif

/**********************************************************************
 * @brief		I2C channel configuration
 * @param[in]	pConfig
 *                  - I2C base address
 * @param[in]	Speed
 *                  - I2C communication speed
 * @param[in]	Type
 *                  - MASTER (0)
 *                  - SLAVE  (1)
 * @return 		None
 **********************************************************************/
static void I2C_ChannelConfig(const I2Cn_PORT_Type * pConfig, uint32_t Speed, I2Cn_Type Type) {
    /* MASTER CHANNEL INIT */
	// SCL port
	HAL_GPIO_ConfigOutput(pConfig->pSclPort, pConfig->SclPort_Number, PCU_MODE_ALT_FUNC);
	HAL_GPIO_ConfigFunction(pConfig->pSclPort, pConfig->SclPort_Number, pConfig->SclAltFunc);
//	HAL_PCU_ConfigureDebounce(pConfig->pSclPort, pConfig->SclPort_Number, ENABLE);	// debounce enable (for Chip Test)

	// SDA port
	HAL_GPIO_ConfigOutput(pConfig->pSdaPort, pConfig->SdaPort_Number, PCU_MODE_ALT_FUNC);
	HAL_GPIO_ConfigFunction(pConfig->pSdaPort, pConfig->SdaPort_Number, pConfig->SdaAltFunc);
//	HAL_PCU_ConfigureDebounce(pConfig->pSdaPort, pConfig->SdaPort_Number, ENABLE);	// debounce enable (for Chip Test)

#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4 : To support I2C slave setting, the Address setting should be next after I2C enable.
	// Initialize Master I2C peripheral
	HAL_I2C_Init(pConfig->pI2Cx, Speed);

	/* Set Own Slave Address for I2C device */
    if (Type == SLAVE) {
        HAL_I2C_SetOwnSlaveAddr0(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
        HAL_I2C_SetOwnSlaveAddr1(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
	
		Slave_Read_Init();	
    }
#else //I2C_1_SLAVE_ENABLE
	/* Set Own Slave Address for I2C device */
    if (Type == SLAVE) {
        HAL_I2C_SetOwnSlaveAddr0(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
        HAL_I2C_SetOwnSlaveAddr1(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
    }

	// Initialize Master I2C peripheral
	HAL_I2C_Init(pConfig->pI2Cx, Speed);
#endif
}

#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4
void I2C_Configure(I2C_Port_No port, I2C_SPEED_STEP speed, I2Cn_Type mode)
{
	if(port > I2C_1) //I2C_0
	{
		I2C_ChannelConfig(i2c0_Master, speed, mode); //I2C0 Config
	}
	else //I2C_1
	{
#ifdef _I2C_1_DEBUG_MSG
		cputs("\n\r I2C_Configure() : Slave !!!");
#endif
		I2C_ChannelConfig(i2c1_Master, speed, mode); //I2C0 Config
	}
}
#else //I2C_1_SLAVE_ENABLE
void I2C_Configure(I2C_SPEED_STEP speed, I2Cn_Type mode) //Define I2C Speed and Master/Slave
{
#ifdef I2C_MANUAL_BUS_CONTROL
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
#endif

	I2C_ChannelConfig(i2c0_Master, speed, mode); //I2C0 Config
	I2C_ChannelConfig(i2c1_Master, speed, mode); //I2C1 Config
}
#endif //I2C_1_SLAVE_ENABLE
#endif

/*******************************************************************************
* @brief      I2C IRQ Function
* @param      None
* @return     None
*******************************************************************************/
static void Main_I2CnIRQHandler(I2C_Type *pI2Cx) {
#ifdef SCL_TIMEOUT
	uint32_t Reg32;

	Reg32 = pI2Cx->ST;
	if ((Reg32 & I2C_ST_SLT_FLAG) == I2C_ST_SLT_FLAG) {
		HAL_I2C_ClearSclLowTimeoutFlag(pI2Cx); // Clear SCL Low Time-out
		complete = TRUE; //KMS241125_3 : Added code to break out of the infinite loop. But Need to check this code later !!!
	}
#endif
#ifdef I2C_1_SLAVE_ENABLE
	if(pI2Cx == I2C1)
		isMasterMode = FALSE;
	else
		isMasterMode = TRUE;
#endif
	if (isMasterMode) { // Master Mode
		HAL_I2C_Interrupt_MasterHandler(pI2Cx);
		if (HAL_I2C_MasterTransferComplete(pI2Cx)) {
			complete = TRUE;
		}
	} else { // Slave Mode
		HAL_I2C_Interrupt_SlaveHandler(pI2Cx);
		if (HAL_I2C_SlaveTransferComplete(pI2Cx)) {
			complete = TRUE;
		}
	}
}
/*******************************************************************************
* @brief      I2C0 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void I2C0_IRQHandler_MasterInterrupt(void) {
	Main_I2CnIRQHandler(I2C0);
}

/*******************************************************************************
* @brief      I2C1 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void I2C1_IRQHandler_MasterInterrupt(void) {
	Main_I2CnIRQHandler(I2C1);
}

/*******************************************************************************
* @brief      I2C2 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void I2C2_SPI20_IRQHandler_MasterInterrupt(void) {
	Main_I2CnIRQHandler(I2C2);
}


/**********************************************************************
 * @brief		I2C_Interrupt_Write_Data for ADAU1452 & ADAU1761
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_16bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of write data
 *				uDataSize : Size of write data only(excepting uSubAddr_16bit(2byte))
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint16_t uSubAddr_16bit, uint8_t *uData, uint16_t uDataSize)
{
	uint8_t MasterWriteBuffer[LONG_BUFFER_SIZE]; //1024 Byte = 2 byte(I2C Sub Address) + 1022 byte(Data)
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Write_Data_16bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Write_Data_16bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif
	if(uDataSize > LONG_BUFFER_SIZE)
	{
#ifdef _I2C_DEBUG_MSG
		cputs("\r\n I2C_Interrupt_Write_Data_16bit_SubAdd() : Error !!!\r\n");
#endif
		return;
	}
#ifdef I2C_MANUAL_BUS_CONTROL
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
	{
		HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
		HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
		HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
		HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
	else
	{
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
#endif

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); 
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); 
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", LONG_BUFFER_SIZE);
#endif

    /* MASTER WRITE : Ready Writebuffer to transmit data by master */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterWriteBuffer, 0, LONG_BUFFER_SIZE); // Buffer Init
    MasterCfg.sl_addr7bit = uDeviceId; // I2C Device address
	MasterWriteBuffer[0] = (uSubAddr_16bit&0xff00) >> 8; //High byte Sub address 
	MasterWriteBuffer[1] = (uSubAddr_16bit&0xff); //High byte Sub address 
	
	for(i=0;i<uDataSize;i++) //uDataSize includes only Data size(excepting I2C Sub-Address)
	{
	    MasterWriteBuffer[i+2] = uData[i];
	}
	
	MasterCfg.tx_data = MasterWriteBuffer;
    MasterCfg.tx_length = uDataSize+2; //KMS241125_4 : Need to add the size of sub-address(2byte) in total size.
	
	complete = FALSE;

#ifdef _I2C_DEBUG_MSG	
  	cputs("\r\n MASTER Write Test START\r\n");
#endif


#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 1");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 1");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif
	
    while(!complete);

#ifdef _I2C_DEBUG_MSG
 	cputs("\r\n MASTER Write Test OK\r\n");
#endif
}

/**********************************************************************
 * @brief		I2C_Interrupt_Read_Data for ADAU1452 & ADAU1761
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_16bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of Read buffer
 *				uDataSize : Size of write data only(excepting uSubAddr_16bit(2byte))
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Read_Data_16bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint16_t uSubAddr_16bit, uint8_t *uData, uint16_t uDataSize)
{
	uint8_t MasterReadBuffer[LONG_BUFFER_SIZE];
	uint8_t uSubAddr[2];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Read_Data_16bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Read_Data_16bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif

	if(uDataSize > LONG_BUFFER_SIZE)
	{
#ifdef _I2C_DEBUG_MSG
		cputs("\r\n I2C_Interrupt_Read_Data_16bit_SubAdd() : Error !!!\r\n");
#endif
		return;
	}

#ifdef I2C_MANUAL_BUS_CONTROL
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
	{
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
	else
	{
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
#endif

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", LONG_BUFFER_SIZE);
#endif

    /* MASTER READ: the data is transmitted by slave */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterReadBuffer, 0, LONG_BUFFER_SIZE);

	uSubAddr[0] = (uSubAddr_16bit&0xff00) >> 8; //High byte Sub address 
	uSubAddr[1] = (uSubAddr_16bit&0xff); //High byte Sub address 
	
	MasterCfg.sl_addr7bit = uDeviceId;
    MasterCfg.tx_data = uSubAddr;
    MasterCfg.tx_length = 2;
    MasterCfg.rx_data = MasterReadBuffer;
    MasterCfg.rx_length = uDataSize;
	
	complete = FALSE;

#ifdef _I2C_DEBUG_MSG
  	cputs("\r\n MASTER Read Test START\r\n");
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 2");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 2");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif
	
    while(!complete);
	
#ifdef _I2C_DEBUG_MSG
	cputs("\r\n MASTER Read Test OK \r\n");
#endif

	 for(i=0;i<uDataSize;i++)
	{
		uData[i] = MasterReadBuffer[i];
#ifdef _I2C_DEBUG_MSG
		cprintf("\n+++I2C Read Data : %d\n",uData[i]);
#endif		
	}
}

/**********************************************************************
 * @brief		I2C_Interrupt_Write_Data_A2B_8bit_Bus for AD2428
 * @param[in]	num : I2C Port number. 0 : I2C_0 / 1 : I2C_1
 * 				uDeviceId : I2C Device Address
 *				*uData : Pointer of write data(including I2C Sub Address(Register Address))
 *				uDataSize : Size of write data
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Write_Data_A2B_8bit_Bus(I2C_Port_No num, uint8_t uDeviceId, uint8_t *uData, uint16_t uDataSize) //KMS241210_1 : To commnunicate with A2B Bus through I2C.
{
	I2C_M_SETUP_Type MasterCfg;
#ifdef _I2C_DEBUG_MSG	
	int i = 0;
#endif

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); 
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); 
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", LONG_BUFFER_SIZE);
#endif
	
	/* MASTER WRITE : Ready Writebuffer to transmit data by master */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    MasterCfg.sl_addr7bit = uDeviceId; // I2C Device address
		
	MasterCfg.tx_data = uData;
    MasterCfg.tx_length = uDataSize;

#ifdef _I2C_DEBUG_MSG
	for(i=0;i<uDataSize;i++)
	{
		cprintf("\n\ruData[%d] = 0x%02x",i,uData[i]);
	}
#endif

	complete = FALSE;

#ifdef _I2C_DEBUG_MSG	
  	cputs("\r\n MASTER Write Test START\r\n");
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 3");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 3");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif
	
    while(!complete);

#ifdef _I2C_DEBUG_MSG
 	cputs("\r\n MASTER Write Test OK\r\n");
#endif
}

/**********************************************************************
 * @brief		I2C_Interrupt_Write_Data_A2B_8bit_Bus for AD2428
 * @param[in]	num : I2C Port number. 0 : I2C_0 / 1 : I2C_1
 * 				uDeviceId : I2C Device Address
 *				*uData : Pointer of write data(including I2C Sub Address(Register Address))
 *				uDataSize : Size of write data
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Read_Data_A2B_8bit_Bus(I2C_Port_No num, uint8_t uDeviceId, uint8_t *uWData, uint16_t uWDataSize, uint8_t *uRData, uint16_t uRDataSize) //KMS241210_1 : To commnunicate with A2B Bus through I2C.
{
	uint8_t MasterReadBuffer[BUFFER_SIZE];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Read_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Read_Data_8bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif

	if(uRDataSize > BUFFER_SIZE)
	{
#ifdef _I2C_DEBUG_MSG
		cputs("\r\n I2C_Interrupt_Read_Data_A2B_8bit_Bus() : Error !!!\r\n");
#endif
		return;
	}

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", BUFFER_SIZE);
#endif

    /* MASTER READ: the data is transmitted by slave */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterReadBuffer, 0, BUFFER_SIZE);
    MasterCfg.sl_addr7bit = uDeviceId;
    MasterCfg.tx_data = uWData;
    MasterCfg.tx_length = uWDataSize;
    MasterCfg.rx_data = MasterReadBuffer;
    MasterCfg.rx_length = uRDataSize;
	
	complete = FALSE;

#ifdef _I2C_DEBUG_MSG
  	cputs("\r\n MASTER Read Test START\r\n");
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 4");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 4");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif
	
    while(!complete);
	
#ifdef _I2C_DEBUG_MSG
	cputs("\r\n MASTER Read Test OK \r\n");
#endif

	for(i=0;i<uRDataSize;i++)
	{
		uRData[i] = MasterReadBuffer[i];
#ifdef _I2C_DEBUG_MSG
		cprintf("\n\r+++I2C Read Data : 0x%02x\r\n",uRData[i]);
#endif
	}
}

#ifdef MCU_EVK_I2C_TEST
/**********************************************************************
 * @brief		I2C_Interrupt_Write_Data
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_8bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of write data
 *				uDataSize : Size of write data
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Write_Data_8bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize)
{
	uint8_t MasterWriteBuffer[BUFFER_SIZE];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif
	if(uDataSize > BUFFER_SIZE)
	{
#ifdef _I2C_DEBUG_MSG
		cputs("\r\n I2C_Interrupt_Write_Data_8bit_SubAdd() : Error !!!\r\n");
#endif
		return;
	}
#ifdef I2C_MANUAL_BUS_CONTROL
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
	{
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
	else
	{
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
#endif

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); 
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", BUFFER_SIZE);
#endif

    /* MASTER WRITE : Ready Writebuffer to transmit data by master */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterWriteBuffer, 0, BUFFER_SIZE); // Buffer Init
    MasterCfg.sl_addr7bit = uDeviceId; // I2C Device address
	MasterWriteBuffer[0] = uSubAddr_8bit; //8bit Sub address
	
	for(i=0;i<uDataSize;i++)
	{
	    MasterWriteBuffer[i+1] = uData[i];
	}
	
	MasterCfg.tx_data = MasterWriteBuffer;
    MasterCfg.tx_length = uDataSize+1;
	
	complete = FALSE;

#ifdef _I2C_DEBUG_MSG	
  	cputs("\r\n MASTER Write Test START\r\n");
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 5");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 5");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterTransmitData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif

    while(!complete);

#ifdef _I2C_DEBUG_MSG
 	cputs("\r\n MASTER Write Test OK\r\n");
#endif
}

/**********************************************************************
 * @brief		I2C_Interrupt_Read_Data
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_8bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of Read buffer
 *				uDataSize : Size of Read data
 * @return 		None
 **********************************************************************/
void I2C_Interrupt_Read_Data_8bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize)
{
	uint8_t MasterReadBuffer[BUFFER_SIZE];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;

#ifdef _I2C_DEBUG_MSG
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		cprintf("%s_Interrupt_Read_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);
	else
		cprintf("%s_Interrupt_Read_Data_8bit_SubAdd\r\n", i2c1_Master->I2cName);
#endif

	if(uDataSize > BUFFER_SIZE)
	{
#ifdef _I2C_DEBUG_MSG
		cputs("\r\n I2C_Interrupt_Read_Data_8bit_SubAdd() : Error !!!\r\n");
#endif
		return;
	}

#ifdef I2C_MANUAL_BUS_CONTROL
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
	{
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
	else
	{
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	    HAL_I2C_SetManualBus(i2c1_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	}
#endif

#ifdef SCL_TIMEOUT
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	if(num > I2C_1)
#else
	if(num == I2C_0)
#endif
		HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
	else
		HAL_I2C_SetSclLowTimeout(i2c1_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
#endif

#ifdef _I2C_DEBUG_MSG
    cprintf("Buffer Size : %d", BUFFER_SIZE);
#endif

    /* MASTER READ: the data is transmitted by slave */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterReadBuffer, 0, BUFFER_SIZE);
    MasterCfg.sl_addr7bit = uDeviceId;
    MasterCfg.tx_data = &uSubAddr_8bit;
    MasterCfg.tx_length = 1;
    MasterCfg.rx_data = MasterReadBuffer;
    MasterCfg.rx_length = uDataSize;
	
	complete = FALSE;

#ifdef _I2C_DEBUG_MSG
  	cputs("\r\n MASTER Read Test START\r\n");
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
	if(num > I2C_1)
	{
		if(num == I2C_0_DSP)
		{
#ifdef _I2C_DEBUG_MSG		
			cputs("\n\r### I2C_0_DSP - 6");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low. I2C_0 can use DSP & Ext.A2B.
		}
		else
		{
#ifdef _I2C_DEBUG_MSG				
			cputs("\n\r### I2C_0_DAC - 6");
#endif
			HAL_GPIO_SetPin(PE, _BIT(0)); //Made PE0 to High. I2C_0 can use ADC & DAC.
		}
			
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	}
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#else
	if(num == I2C_0)
		HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
	else
		HAL_I2C_MasterReceiveData(i2c1_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
#endif

    while(!complete);
	
#ifdef _I2C_DEBUG_MSG
	cputs("\r\n MASTER Read Test OK \r\n");
#endif

	 for(i=0;i<uDataSize;i++)
	{
		uData[i] = MasterReadBuffer[i];
#ifdef _I2C_DEBUG_MSG
		cprintf("\n+++I2C Read Data : %d\n",uData[i]);
#endif		
	}
}
#endif //MCU_EVK_I2C_TEST

/*********************************************************************//**
 * @brief		Initialize buffer
 * @param[in]	buffer	buffer to initialize
 * @param[in]	type:
 * 				- 0: Initialize buffer with 0
 * 				- 1: Initialize buffer with increment value from 0
 * @return 		None
 **********************************************************************/
static void Buffer_Init(uint8_t* buffer, uint8_t type, uint16_t len) {
	uint16_t i; //KMS241125_4 : To fix 16 bit length for I2C Data

	if (type) {
		for (i = 0; i < len; i++) {
			buffer[i] = i;
		}
	}
	else {
		for (i = 0; i < len; i++) {
			buffer[i] = 0;
		}
	}
}
#endif //#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)

/* --------------------------------- End Of File ------------------------------ */
