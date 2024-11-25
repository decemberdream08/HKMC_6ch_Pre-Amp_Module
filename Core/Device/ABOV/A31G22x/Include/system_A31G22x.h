/**
 *******************************************************************************
 * @file        system_A31G22x.h
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
 
#ifndef SYSTEM_A31G22x_H
#define SYSTEM_A31G22x_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
#define LSI_CLOCK           (500000)    // The clock speed of Internal Low Speed Oscillator
#define LSE_CLOCK           (32768)     // The clock speed of External Low Speed Oscillator (SXTAL)
#define HSI_CLOCK           (32000000)  // The clock speed of Internal High Speed Oscillator
#define HSE_CLOCK           (8000000)   // The clock speed of External High Speed Oscillator(XTAL)


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */
extern uint32_t SystemPeriClock;     /*!< System Clock Frequency (Peri Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

///**
// * Initialize the system
// *
// * @param  none
// * @return none
// *
// * @brief  Setup the microcontroller system.
// *         Initialize the System and update the SystemCoreClock variable.
// */
//extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_A31G22x_H */
