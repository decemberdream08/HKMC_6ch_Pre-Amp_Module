/**
 *******************************************************************************
 * @file        A31G22x_SystemClock.c
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes
 *              support for system clock initialization
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "main_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config (void);
/* Private variables ---------------------------------------------------------*/

#ifdef ESTEC_BOARD
#define USED_HSI //KMS241125_1 : Change from USED_HSEPLL to USED_HSI due to no X-TAL
#else
//#define USED_LSI		
//#define USED_LSE		
//#define USED_HSE		
//#define USED_HSIPLL
#define USED_HSEPLL
#endif

/**************************************************************************
 * @brief			Initialize default clock for A33M11x Board
 * @param[in]		None
 * @return			None
 **************************************************************************/
void SystemClock_Config (void)
{

    HAL_SCU_ClockOutput(4, ENABLE);  // Enable Main CLK output via CLKO(PF4) port

#ifdef USED_LSI
    HAL_SCU_SetSystemClock(SYSCLK_LSI, SYSDIV_NONE);  // Use LSI clock (500kHz)
#endif

	#ifdef USED_LSE
    HAL_SCU_SetSystemClock(SYSCLK_LSE, SYSDIV_NONE);  // Use LSE clock (32.768kHz)
#endif

#ifdef USED_HSI
    HAL_SCU_SetSystemClock(SYSCLK_HSI, SYSDIV_NONE);  // Use HSI clock (32MHz)
#endif

#ifdef USED_HSE
    HAL_SCU_SetSystemClock(SYSCLK_HSE, SYSDIV_NONE);  // Use HSE clock (XTAL)
#endif


#ifdef USED_HSIPLL
        HAL_SCU_SetPLLFreq(IRC32MHz, PLL48MHz);     // Use PLL with HSI clock
#endif

#ifdef USED_HSEPLL
    HAL_SCU_SetPLLFreq(XTAL8MHz, PLL48MHz);   // Use PLL with HSE clock
#endif


}
