/**
 *******************************************************************************
 * @file        A31G22x_it.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes
 *              support for PCU firmware library
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __A31G22x_IT_H
#define __A31G22x_IT_H

/* Includes ------------------------------------------------------------------*/
#include "main_conf.h"

/* prototypes ----------------------------------------------------------------*/
extern void I2C0_IRQHandler_MasterInterrupt(void);
extern void I2C1_IRQHandler_MasterInterrupt(void);
extern void I2C2_SPI20_IRQHandler_MasterInterrupt(void);


#ifdef __cplusplus
extern "C" {
#endif



#endif /* __A31G22x_IT_H */

