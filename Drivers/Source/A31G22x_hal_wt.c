/**
 *******************************************************************************
 * @file        A31G22x_hal_wt.c
 * @author      ABOV R&D Division
 * @brief       Contains all functions support for watch timer driver on A31G22x
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
* Included File
*******************************************************************************/
#include "A31G22x_libcfg.h"
#ifdef _WT

#include "A31G22x_hal_scu.h"
#include "A31G22x_hal_wt.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/
#define SCU_PER1_WT_ENABLE_PERI              (0x01UL << SCU_PER1_WT_Pos)
#define SCU_PCER1_WT_ENABLE_CLOCK            (0x01UL << SCU_PCER1_WT_Pos)


#define WT_CR_WTEN_ENABLE_WT                 (0x01UL << WT_CR_WTEN_Pos)
#define WT_CR_WTIFLAG_INTERRUPT              (0x01UL << WT_CR_WTIFLAG_Pos)
#define WT_CR_WTCLR_CLEAR_COUNTER            (0x01UL << WT_CR_WTCLR_Pos)


/*******************************************************************************
* Private Typedef
*******************************************************************************/


/*******************************************************************************
* Private Variable
*******************************************************************************/


/*******************************************************************************
* Private Function Prototype
*******************************************************************************/


/*******************************************************************************
* Public Function
*******************************************************************************/

/***************************************************************************//**
* @brief      Initialize watch timer peripheral
* @param      pConfig : Pointer contains configuration of watch timer
* @return     None
*******************************************************************************/
HAL_Status_Type HAL_WT_Init(WT_CFG_Type *pConfig) {
    SCU->PER1 &= ~(SCU_PER1_WT_Msk);
    SCU->PCER1 &= ~(SCU_PCER1_WT_Msk);

    SCU->PER1 |= SCU_PER1_WT_ENABLE_PERI;
    SCU->PCER1 |= SCU_PCER1_WT_ENABLE_CLOCK;

    WT->CR = 0x00
        | ((pConfig->ClockDivider << WT_CR_WTINTV_Pos) & WT_CR_WTINTV_Msk)
        | WT_CR_WTCLR_CLEAR_COUNTER;
    WT->DR = (pConfig->MatchData & WT_DR_WTDATA_Msk);
    
    return HAL_OK;
}

/***************************************************************************//**
* @brief      De-Initialize watch timer peripheral
* @param      None
* @return     None
*******************************************************************************/
void HAL_WT_DeInit(void) {
    HAL_WT_Stop();
}

/***************************************************************************//**
* @brief      Configure interrupt of watch timer
* @param      Interrupt :
*              - ENABLE : Enable interrupt
*              - DISABLE : Disable interrupt
* @return     None
*******************************************************************************/
void HAL_WT_ConfigInterrupt(FunctionalState Interrupt) {
    volatile uint32_t Reg32;

    Reg32 = WT->CR;
    Reg32 &= ~(WT_CR_WTIEN_Msk);
    Reg32 |= (Interrupt << WT_CR_WTIEN_Pos);
    WT->CR = Reg32;
}

/***************************************************************************//**
* @brief      Get the current count of watch timer
* @param      None
* @return     Current count of watch timer
*******************************************************************************/
uint32_t HAL_WT_GetCurrentCount(void) {
    return (WT->CNT & WT_CNT_CNT_Msk);
}

/***************************************************************************//**
* @brief      Get interrupt status of watch timer
* @param      None
* @return     SET : Occurred, RESET : Not occurred
*******************************************************************************/
FlagStatus HAL_WT_GetStatus(void) {
    return (WT->CR & WT_CR_WTIFLAG_INTERRUPT) ? SET : RESET;
}

/***************************************************************************//**
* @brief      Clear interrupt status of watch timer
* @param      None
* @return     None
*******************************************************************************/
HAL_Status_Type HAL_WT_ClearStatus(void) {
    WT->CR |= WT_CR_WTIFLAG_INTERRUPT;
    
    return HAL_OK;
}

/***************************************************************************//**
* @brief      Start watch timer
* @param      None
* @return     None
*******************************************************************************/
HAL_Status_Type HAL_WT_Start(void) {
    volatile uint32_t Reg32;

    Reg32 = WT->CR;
    Reg32 &= ~WT_CR_WTEN_Msk;
    Reg32 |= (WT_CR_WTEN_ENABLE_WT | WT_CR_WTCLR_CLEAR_COUNTER);
    WT->CR = Reg32;
    
    return HAL_OK;
}

/***************************************************************************//**
* @brief      Stop watch timer
* @param      None
* @return     None
*******************************************************************************/
void HAL_WT_Stop(void) {
    volatile uint32_t Reg32;

    Reg32 = WT->CR;
    Reg32 &= ~WT_CR_WTEN_Msk;
    Reg32 |= WT_CR_WTCLR_CLEAR_COUNTER;
    WT->CR = Reg32;
}

#endif /* _WT */
/* --------------------------------- End Of File ------------------------------ */
