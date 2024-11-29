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
#ifndef __TIMER20_INTERRUPT_H__
#define __TIMER20_INTERRUPT_H__

#ifdef TIMER20_ENABLE

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
void TIMER20_Interrupt_Mode_Run(Bool On);
void TIMER20_Configure(void); //1sec one shot timer

#endif
#endif //__TIMER20_INTERRUPT_H__
/* --------------------------------- End Of File ------------------------------ */


