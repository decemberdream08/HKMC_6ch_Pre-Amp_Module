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

/** Select Test I2C Channel before project compile (Must be set a channel) */
//#define TEST_I2Cn	(0) // I2C0
//#define TEST_I2Cn	(1) // I2C1
#define TEST_I2Cn	(2) // I2C2

/** Max buffer length */
#define BUFFER_SIZE	(64-1) // Data Buffer Size (Excluded slave address byte size)

/** Max I2C Channel Number */
#define I2C_IP_INDEX_MAX			(3)


/** Slave Address Setting */
/** Master and Slave Address */
#define MASTER_ADDR	                (0xC0 >> 1) // Master Address
#define SLAVE_ADDR	                (0xC0 >> 1) // Slave Address

/** INTERVAL TEST */
//#define INTERVAL_TEST

/** SCL Low Time-out Function */
#define SCL_TIMEOUT

/** Manual Bus Control Test */
//#define I2C_MANUAL_BUS_CONTROL //Can't use this one

//#define SCL_TIMEOUT

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
static const I2Cn_PORT_Type * i2c0_Master = &(I2C_PORT_CFG[0]);
static const I2Cn_PORT_Type * i2c1_Master = &(I2C_PORT_CFG[1]);


static Bool complete;  // Interrupt Flag
static Bool isMasterMode = TRUE; // Interrupt Master FLag

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
static void Buffer_Init(uint8_t* buffer, uint8_t type, uint16_t len);
static void I2C_ChannelConfig(const I2Cn_PORT_Type * pConfig, uint32_t Speed, I2Cn_Type Type);

/*******************************************************************************
* Public Function
*******************************************************************************/
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

	/* Set Own Slave Address for I2C device */
    if (Type == SLAVE) {
        HAL_I2C_SetOwnSlaveAddr0(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
        HAL_I2C_SetOwnSlaveAddr1(pConfig->pI2Cx, SLAVE_ADDR, DISABLE);
    }

	// Initialize Master I2C peripheral
	HAL_I2C_Init(pConfig->pI2Cx, Speed);
}

#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
void I2C_Configure(I2C_SPEED_STEP speed, I2Cn_Type mode) //Define I2C Speed and Master/Slave
{
#if 1//def I2C_MANUAL_BUS_CONTROL
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
	HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
#endif

	I2C_ChannelConfig(i2c0_Master, speed, mode); //I2C0 Config
	//I2C_ChannelConfig(i2c1_Master, speed, mode); //I2C1 Config
}
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
	}
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
 * @brief		I2C_Interrupt_Write_Data
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_8bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of write data
 *				uDataSize : Size of write data
 * @return 		None
 **********************************************************************/
void I2C0_Interrupt_Write_Data_8bit_SubAdd(uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize)
{
	uint8_t MasterWriteBuffer[BUFFER_SIZE];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;
	
	cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);

	if(uDataSize > BUFFER_SIZE)
	{
		cputs("\r\n I2C0_Interrupt_Write_Data_8bit_SubAdd() : Error !!!\r\n");
		return;
	}
#ifdef I2C_MANUAL_BUS_CONTROL
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
#endif

#ifdef SCL_TIMEOUT
	HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
#endif

    cprintf("Buffer Size : %d", BUFFER_SIZE);

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

  	cputs("\r\n MASTER Write Test START\r\n");
    HAL_I2C_MasterTransmitData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
    while(!complete);
 	cputs("\r\n MASTER Write Test OK \r\n");
}

/**********************************************************************
 * @brief		I2C_Interrupt_Read_Data
 * @param[in]	uDeviceId : I2C Device Address
 *				uSubAddr_8bit : I2C Sub Address(Register Address)
 *				*uData : Pointer of Read buffer
 *				uDataSize : Size of Read data
 * @return 		None
 **********************************************************************/
void I2C0_Interrupt_Read_Data_8bit_SubAdd(uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize)
{
	uint8_t MasterReadBuffer[BUFFER_SIZE-1];
	I2C_M_SETUP_Type MasterCfg;
	int i = 0;
	
	cprintf("%s_Interrupt_Write_Data_8bit_SubAdd\r\n", i2c0_Master->I2cName);

	if(uDataSize > BUFFER_SIZE)
	{
		cputs("\r\n I2C0_Interrupt_Read_Data_8bit_SubAdd() : Error !!!\r\n");
		return;
	}

#ifdef I2C_MANUAL_BUS_CONTROL
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_LOW, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SCL, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_LOW, ENABLE);
    HAL_I2C_SetManualBus(i2c0_Master->pI2Cx, I2C_SDA, I2C_OUTPUT_HIGH_OPENDRAIN, ENABLE);
#endif

#ifdef SCL_TIMEOUT
	HAL_I2C_SetSclLowTimeout(i2c0_Master->pI2Cx, ENABLE, ENABLE, 0x0000FF); // SCL Low Time Period : (1/PCLK)*4*(SLTPDR+1) = (1/32MHz)*4*(0xFFFFFF+1)2.09s
#endif

    cprintf("Buffer Size : %d", BUFFER_SIZE);

    /* MASTER READ: the data is transmitted by slave */
    //--------------------------------------------------------
    //| Slave Address | Data [0] | Data [1] | ... | Data [n] |
    //--------------------------------------------------------
    Buffer_Init(MasterReadBuffer, 0, BUFFER_SIZE-1);
    MasterCfg.sl_addr7bit = uDeviceId;
    MasterCfg.tx_data = &uSubAddr_8bit;
    MasterCfg.tx_length = 1;
    MasterCfg.rx_data = MasterReadBuffer;
    MasterCfg.rx_length = uDataSize;

  	cputs("\r\n MASTER Read Test START\r\n");
    HAL_I2C_MasterReceiveData(i2c0_Master->pI2Cx, &MasterCfg, I2C_TRANSFER_INTERRUPT);
     while(!complete);
  	cputs("\r\n MASTER Read Test OK \r\n");

	 for(i=0;i<uDataSize;i++)
	{
		uData[i] = MasterReadBuffer[i];
#ifdef _I2C_DEBUG_MSG
		cprintf("\n+++I2C Read Data : %d\n",uData[i]);
#endif		
	}
}


/*********************************************************************//**
 * @brief		Initialize buffer
 * @param[in]	buffer	buffer to initialize
 * @param[in]	type:
 * 				- 0: Initialize buffer with 0
 * 				- 1: Initialize buffer with increment value from 0
 * @return 		None
 **********************************************************************/
static void Buffer_Init(uint8_t* buffer, uint8_t type, uint16_t len) {
	uint8_t i;

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
