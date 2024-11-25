/**
 *******************************************************************************
 * @file        A31G22x_hal_ts.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for Temp Sensor driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_HAL_TS_H_
#define _A31G22x_HAL_TS_H_

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


/*******************************************************************************
* Public Typedef
*******************************************************************************/
/**
 * @brief  TS configuration structure definition
 */
typedef struct {
    /* CR */
    FunctionalState TsInterrupt; /*!< Ts Interrupt */
    /* REFPERIOD */
    uint32_t ReferencePeriod; /*!< Reference Period, 0x00000 ~ 0xFFFFF */
} TS_CFG_Type;

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void HAL_TS_Init(TS_CFG_Type *pConfig);
void HAL_TS_DeInit(void);
FlagStatus HAL_TS_GetStatus(void);
void HAL_TS_ClearStatus(void);
uint32_t HAL_TS_GetSensingCount(void);
void HAL_TS_Start(void);
void HAL_TS_Stop(void);


#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_TS_H_ */
/* --------------------------------- End Of File ------------------------------ */
