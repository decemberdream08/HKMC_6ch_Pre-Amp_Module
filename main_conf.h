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
#define ESTEC_BOARD			(1)
#define I2C_0_ENABLE			(1) //Use I2C 0 for the communication with DSP/A2B Transceiver - PF6:SCL0, PF7:SDA0. If you don't use I2C0, please make sure to disable this macro !!!
#define I2C_1_ENABLE			(1) //Use I2C 1 for the communication with ADC/DAC - PF0:SCL1, PF1:SDA1.
#define TIMER20_COUNTER_ENABLE	(1) //Enable 100ms timer

#define ADAU1452_ENABLE			(1) //KMS241126_1 : Added ADAU1452(DSP) code
#define ADAU1761_ENABLE			(1) //KMS241125_2 : Added ADAU1761(ADC/DAC) code

#ifdef I2C_0_ENABLE
//#define _I2C_DEBUG_MSG		(1) //Debug message for I2C especially TAS3251
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern void delay_ms(uint32_t m_ms);
/* Initialize all port */
extern void Port_Init(void);
/* Configure the system clock initialization */
extern void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __A31G22x_CONF_H */
