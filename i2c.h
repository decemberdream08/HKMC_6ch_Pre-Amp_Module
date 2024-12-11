/**
 *******************************************************************************
 * @file        TestCode_I2C_Master_Interrupt.h
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
#ifndef __TESTCODE_I2C_MASTER_INTERRUPT_H__
#define __TESTCODE_I2C_MASTER_INTERRUPT_H__

#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
#include "a31G22x_hal_i2c.h"

/*******************************************************************************
* Private Typedef
*******************************************************************************/
//KMS241120_1 : Add new function and new defines
typedef enum {
	I2C_SPEED_100K = 100000,
	I2C_SPEED_400K = 400000
} I2C_SPEED_STEP;

typedef enum {
    MASTER = 0,
    SLAVE = 1
} I2Cn_Type;

typedef enum {
	I2C_0,
	I2C_1
} I2C_Port_No;

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
void Main_TestI2CMasterInterrupt(void);

void I2C0_IRQHandler_MasterInterrupt(void);
void I2C1_IRQHandler_MasterInterrupt(void);
void I2C2_SPI20_IRQHandler_MasterInterrupt(void);

//KMS241211_2 : To share I2C function for I2C_0 & I2C_1, it's changed I2C related functions as the following.
void I2C_Interrupt_Write_Data_8bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize);
void I2C_Interrupt_Read_Data_8bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint8_t uSubAddr_8bit, uint8_t *uData, uint8_t uDataSize);

void I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint16_t uSubAddr_16bit, uint8_t *uData, uint16_t uDataSize);
void I2C_Interrupt_Read_Data_16bit_SubAdd(I2C_Port_No num, uint8_t uDeviceId, uint16_t uSubAddr_16bit, uint8_t *uData, uint16_t uDataSize);

void I2C_Interrupt_Write_Data_A2B_8bit_Bus(I2C_Port_No num, uint8_t uDeviceId, uint8_t *uData, uint16_t uDataSize); //KMS241210_1 : To commnunicate with A2B Bus through I2C.
void I2C_Interrupt_Read_Data_A2B_8bit_Bus(I2C_Port_No num, uint8_t uDeviceId, uint8_t *uWData, uint16_t uWDataSize, uint8_t *uRData, uint16_t uRDataSize); //KMS241210_1 : To commnunicate with A2B Bus through I2C.

//KMS241120_1 : Add new function and new defines
void I2C_Configure(I2C_SPEED_STEP speed, I2Cn_Type mode); //Define I2C Speed and Master/Slave
#endif
#endif
/* --------------------------------- End Of File ------------------------------ */
