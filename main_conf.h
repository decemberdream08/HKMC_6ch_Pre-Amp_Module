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
//Feature
#define DEEP_SLEEP_MODE_ENABLE		(1) //KMS241128_1 : Added DEEP SLEEP mode code.
#ifdef DEEP_SLEEP_MODE_ENABLE
#define MCU_RESET_AFTER_WAKE_UP		(1) //KMS241129_1 : Implemented MCU reset after wake-up from Deep-sleep.
#define DEEP_SLEEP_LOWEST_POWER_CONSUMPTION	(1) //KMS241129_2 : Implemented lowest power consumption under MCU deep-sleep mode.
#endif

#define ESTEC_A2B_STACK_PORTING		(1) //KMS241129_4 : To merge A2B Stack, we use "ESTEC_A2B_STACK_PORTING" define.
#ifdef ESTEC_A2B_STACK_PORTING
#define A2B_STACK_CODE_FROM_ADI			(1) //KMS241211_1 : To make A2B Stack code as module code. So we can remove A2B Stack without disabling "A2B_STACK_CODE_FROM_ADI".
#define A2B_SLAVE_DISCOVERY_WO_ID_VER		(1) //KMS250204_1 : Changed ESTec Board doesn't check Device ID and Version of Slave Node's A2B transceiver when ESTec Board works as A2B Master.
#endif

#define A2B_SLAVE_WORKING_SUPPORT_TMD8_32BIT			(1) //KMS250110_1 : To support TDM8 under A2B Slave mode like NE-N

//Functions
#define ESTEC_BOARD					(1)
#define ESTEC_2ND_BOARD_SUPPORT		(1) //KMS250219_1 : To support ESTec 2nd Board which has I2C Slave and some additional GPIOs.
#define I2C_0_ENABLE				(1) //Use I2C 0 for the communication with DSP/A2B Transceiver - PF6:SCL0, PF7:SDA0. If you don't use I2C0, please make sure to disable this macro !!!
#define I2C_1_ENABLE				(1) //Use I2C 1 for the communication with ADC/DAC - PF0:SCL1, PF1:SDA1.
#ifdef ESTEC_2ND_BOARD_SUPPORT
#define I2C_1_SLAVE_ENABLE			(1) //I2C_1 : Work for Slave to control vitual Amp communicatoin reqested from Front two A2B Transceivers.
#endif

#define GPIO_ENABLE					(1) //KMS241125_5 : Added GPIO code.
#define TIMER20_ENABLE				(1) //KMS241127_4 : Added TIMER20 code. This is timer for ACC OFF only.
#define SYSTICK_TIMER_ENABLE		(1) //KMS241220_1 : Added SYSTEM TICK Timer instead of TIMER21.
#ifdef ESTEC_2ND_BOARD_SUPPORT
#define TIMER21_ENABLE				(1) //KMS250227_5 : Added TIMER21 code. This is timer for OP_OUT_RELAY_CNTRL only.
#endif

//Pheriperal Devices
#define ADAU1452_ENABLE				(1) //KMS241126_1 : Added ADAU1452(DSP) code //I2C_0
#define ADAU1761_ENABLE				(1) //KMS241125_2 : Added ADAU1761(ADC/DAC) code //I2C_1

//Features
#ifdef GPIO_ENABLE
#define INTPUT_SOURCE_SELECTION_UPON_POWER_ON			(1) //KMS241213_3 : The input souce selection is only working one time when power is turned on.
#endif

//Tests
//#define MCU_EVK_FUNCTION_TEST			(1) //KMS241127_1 : Defined test codes for MCU EVK board and ADI A2B Master EVK(using I2C1 for DSP/DAC and A2B Transceiver) 
#ifdef MCU_EVK_FUNCTION_TEST
#define MCU_EVK_I2C_TEST				(1) //I2C0, I2C1
#define MCU_EVK_GPIO_TEST				(1) //GPIO, External Interrupt
#endif //MCU_EVK_FUNCTION_TEST

//Debug Messages
#ifdef _DEBUG_MSG
#ifdef I2C_0_ENABLE
//#define _I2C_DEBUG_MSG		(1) //Debug message for I2C especially ADAU1452
#endif
#ifdef I2C_1_SLAVE_ENABLE
//#define _I2C_1_DEBUG_MSG		(1) //Debug message for I2C_1(I2C Slave)
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
#ifdef ADAU1452_ENABLE
//#define ADAU1452_DEBUG_ENABLE	(1) //Debug message for ADAU1452
//#define ADAU1452_DUMP			(1) //Debug message for ADAU1452 Register Dump
#endif
#ifdef ADAU1761_ENABLE
//#define ADAU1761_DEBUG_ENABLE	(1) //Debug message for ADAU1761
#endif
#ifdef ESTEC_A2B_STACK_PORTING
//#define ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE		(1) //Debug message for A2B STack Porting
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
#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT) //KMS250228_3
extern Bool B_Mute_TimerOn;
#endif
#ifdef ESTEC_A2B_STACK_PORTING
extern uint32_t MilliSec;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __A31G22x_CONF_H */
