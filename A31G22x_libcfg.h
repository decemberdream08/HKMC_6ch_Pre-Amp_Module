/**
 *******************************************************************************
 * @file        A31G22x_libcfg.h
 * @author      ABOV R&D Division
 * @brief       Library configuration file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_LIBCFG_H_
#define _A31G22x_LIBCFG_H_

#include "A31G22x_hal_aa_types.h"

/******************* PERIPHERAL FW LIBRARY CONFIGURATION DEFINITIONS ***********************/
/* Comment the line below to disable the specific peripheral inclusion */

/* SCU ------------------------------- */
#define _SCU

/* GPIO ------------------------------- */
#define _GPIO

/* CFMC -------------------------------- */
#define _CFMC

/* DFMC -------------------------------- */
//#define _DFMC

/* SRAM -------------------------------- */
//#define _SRAM

/* SCU ------------------------------- */
//#define _DMAC

/* WDT --------------------------------- */
//#define _WDT

/* WT --------------------------------- */
//#define _WT

/* TIMER1n ------------------------------- */
//#define _TIMER1n

/* TIMER2n ------------------------------- */
#define _TIMER2n //KMS241127_3

/* TIMER30 ------------------------------- */
//#define _TIMER30

/* UART ------------------------------- */
#define _USART1n

/* UART ------------------------------- */
#define _UART

/* SPI ------------------------------- */
//#define _SPI2n

/* I2C ------------------------------- */
#define _I2C

/* ADC ------------------------------- */
//#define _ADC

/* DAC ------------------------------- */
//#define _DAC

/* CMP ------------------------------- */
//#define _CMP

/* TS -------------------------------- */
//#define _TS

/* LCD ------------------------------- */
//#define _LCD

/* CRC ------------------------------- */
//#define _CRC

/* PWR ------------------------------- */
#define _PWR //KMS241128_1

/* CORE ------------------------------- */
#define _CORE


/*******************************************************************************************
* Included File
*******************************************************************************************/

 /* CHECK PARAM --------------------------------------------- */
 /* Un-comment the line below to compile the library in DEBUG mode, this will expanse
 the "CHECK_PARAM" macro in the FW library code */
//#define	USE_FULL_ASSERT

 /* DEBUG_FRAMWORK ---------------------------------------- */
#define _DEBUG_MSG

#endif /* _A31G22x_LIBCFG_H_ */
/* --------------------------------- End Of File ------------------------------ */
