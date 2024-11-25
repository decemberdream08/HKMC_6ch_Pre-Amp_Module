/**
 *******************************************************************************
 * @file        system_A31G22x.c
 * @author      ABOV R&D Division
 * @brief       CMSIS Cortex-M0+ Device Peripheral Access Layer for A31G22x
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#include <stdint.h>
#include "A31G22x.h"
#include "system_A31G22x.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
 uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  HLCK */
 uint32_t SystemPeriClock;     /*!< System Clock Frequency (Peri Clock)  PCLK */

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/

void SystemInit (void)
{
	static int i;

    __disable_irq();

    // disable WDT - default ON so you must turn off
    WDT->CR = 0
        |(0x5A69 << 16)
        |(0x25 << 10)
        |(0x1A << 4);

    SCU->CSCR = (SCU->CSCR & 0x000F0FF) | 0xA5070880U;  // Enables LSI oscillator and disables HSE, LSE
    SCU->SCCR = 0x570A0002U;  // Select HSI (32MHz)
    for(i = 0 ; i < 0x100; i++);      // Stabilization of HSI (Min. 100 us)

    SystemCoreClock = HSI_CLOCK;  // System Code clock is set LSI clock (Global variable have to be called in main routine.)
    SystemPeriClock = HSI_CLOCK;  // System Peripheral clock is set LSI clock (Global variable have to be called in main routine.)

    // flash memory controller
    CFMC->MR = 0x81;       // after changing 0x81 -> 0x28 in MR reg, flash access timing will be able to be set.
    CFMC->MR = 0x28;       // enter flash access timing changing mode
    CFMC->CFG = (0x7858 << CFMC_CFG_WTIDKY_Pos) | (1 << CFMC_CFG_WAIT_Pos);     // 1-wait: 32MHz/(1+1) = 16MHz Access Freq.
    CFMC->MR = 0;	      // exit flash access timing --> normal mode
}
