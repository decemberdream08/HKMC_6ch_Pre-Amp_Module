/**
 *******************************************************************************
 * @file        main_conf.h
 * @author      ABOV R&D Division
 * @brief       Contains all A31G22x macro definitions and function prototypes
 *              for main code that build the example project for user
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef __MAIN_CONF_H
#define __MAIN_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
#include "A31G22x_libcfg.h"
#include "A31G22x_hal_pcu.h"
#include "A31G22x_hal_scu.h"
#include "A31G22x_hal_i2c.h"
#include "debug_frmwrk.h"
#include "debug_cmd.h"
#include "debug.h"

#include "A31G22x_hal_assert.h"
#include "A31G22x_it.h"

#ifdef __cplusplus
extern "C"
{
#endif
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//Functions
#define ESTEC_BOARD			(1)
#define I2C_0_ENABLE			(1) //Use I2C 0 for the communication with DSP/A2B Transceiver - PF6:SCL0, PF7:SDA0. If you don't use I2C0, please make sure to disable this macro !!!
#define I2C_1_ENABLE			(1) //Use I2C 1 for the communication with ADC/DAC - PF0:SCL1, PF1:SDA1.
#define TIMER20_COUNTER_ENABLE	(1) //Enable 100ms timer
#define GPIO_ENABLE				(1) //KMS241125_5 : Added GPIO code
#define TIMER20_ENABLE			(1) //KMS241127_4 : Added TIMER20 code. This is timer for ACC OFF only.
#define TIMER21_ENABLE			(1) //KMS241127_5 : Added TIMER20 code. This is just continueous tick.
#define DEEP_SLEEP_MODE_ENABLE		(1) //KMS241128_1 : Added DEEP SLEEP mode code.

//Pheriperal Devices
#define ADAU1452_ENABLE			(1) //KMS241126_1 : Added ADAU1452(DSP) code
#define ADAU1761_ENABLE			(1) //KMS241125_2 : Added ADAU1761(ADC/DAC) code

//Tests
#define MCU_EVK_FUNCTION_TEST			(1) //KMS241127_1 : Defined test codes for MCU EVK board

#ifdef MCU_EVK_FUNCTION_TEST
#define MCU_EVK_I2C_TEST				(1) //I2C0, I2C1
#define MCU_EVK_GPIO_TEST				(1) //GPIO, External Interrupt
#endif //MCU_EVK_FUNCTION_TEST

//Debug Messages
#ifdef _DEBUG_MSG
#ifdef I2C_0_ENABLE
//#define _I2C_DEBUG_MSG		(1) //Debug message for I2C especially TAS3251
#endif
#ifdef GPIO_ENABLE
//#define GPIO_DEBUG_MSG			(1)  //Debug message for GPIO
#endif //GPIO_DEBUG_MSG
#ifdef TIMER20_ENABLE
//#define TIMER20_DEBUG_MSG		(1) // Debug message for TIMER20
#endif
#ifdef TIMER21_ENABLE
//#define TIMER21_DEBUG_MSG		(1) // Debug message for TIMER21
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
//#define DEEP_SLEEP_MODE_DEBUG_MSG		(1) // Debug message for DEEP SLEEP MODE
#endif
#endif //_DEBUG_MSG


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern void delay_ms(uint32_t m_ms);
/* Initialize all port */
extern void Port_Init(void);
/* Configure the system clock initialization */
extern void SystemClock_Config(void);

#ifdef GPIO_ENABLE
extern void GPIOAB_IRQHandler_IT(void); //KMS24112_6 : External Interrupt Setting for PA0
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
extern Bool B_Deep_Sleep;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __A31G22x_CONF_H */
