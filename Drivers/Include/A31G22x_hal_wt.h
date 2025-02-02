/**
 *******************************************************************************
 * @file        A31G22x_hal_wt.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for watch timer driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_HAL_WT_H_
#define _A31G22x_HAL_WT_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Included File
*******************************************************************************/
#include "A31G22x.h"
#include "A31G22x_hal_aa_types.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/
#define    WT_INTERRUPT_FLAG        (0x1UL)

/*******************************************************************************
* Public Typedef
*******************************************************************************/
/**
 * @brief  watch timer clock divider selection enumerated definition
 */
typedef enum {
    WT_DIVIDER_2_7              = 0x00UL, /*!< WT Clock / (2 ^ 7) */
    WT_DIVIDER_2_13             = 0x01UL, /*!< WT Clock / (2 ^ 13) */
    WT_DIVIDER_2_14             = 0x02UL, /*!< WT Clock / (2 ^ 14) */
    WT_DIVIDER_2_14_MUL_WTDR    = 0x03UL  /*!< WT Clock / ((2 ^ 14) * (WTDR + 1)) */
} WT_DIVIDER_Type;

/**
 * @brief  watch timer configuration structure definition
 */
typedef struct {
    WT_DIVIDER_Type ClockDivider;     /*!< watch timer clock divider selection */
    uint32_t MatchData;                /*!< Data of watch timer, 0x001 ~ 0xFFF */
} WT_CFG_Type;


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
HAL_Status_Type HAL_WT_Init(WT_CFG_Type *pConfig);
HAL_Status_Type HAL_WT_Start(void);

void HAL_WT_DeInit(void);
void HAL_WT_ConfigInterrupt(FunctionalState Interrupt);
uint32_t HAL_WT_GetCurrentCount(void);
FlagStatus HAL_WT_GetStatus(void);
HAL_Status_Type HAL_WT_ClearStatus(void);
void HAL_WT_Stop(void);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_WT_H_ */
/* --------------------------------- End Of File ------------------------------ */
