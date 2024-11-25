/**
 *******************************************************************************
 * @file        A31G22x_hal_crc.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for CRC driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_CRC_H_
#define _A31G22x_CRC_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Included File
*******************************************************************************/
#include "A31G22x.h"
#include "a31G22x_hal_aa_types.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/


/*******************************************************************************
* Public Typedef
*******************************************************************************/
/**
 * @brief  CRC polynomial enumerated definition. CRC mode only
 */
typedef enum {
    CRC_POLY_CRC32, /*!< CRC-32 */
    CRC_POLY_CRC16, /*!< CRC-16 */
    CRC_POLY_CRC8, /*!< CRC-8 */
    CRC_POLY_CRC7, /*!< CRC-7 */
} CRC_POLY_Type;

/**
 * @brief  CRC first bit selection enumerated definition
 */
typedef enum {
    CRC_FIRST_BIT_LSB, /*!< LSB-first */
    CRC_FIRST_BIT_MSB, /*!< MSB-first */
} CRC_FIRST_BIT_Type;

/**
 * @brief  CRC configuration structure definition
 */
typedef struct {
    /* CR */
    FunctionalState InverseOutput; /*! Inverse CRC Output data */
    FunctionalState ReverseOutput; /*! Reverse CRC Output data */
    CRC_FIRST_BIT_Type FirstBitInput; /*! First Bit of Input Data */
    FunctionalState DMADoneInterrupt; /*! DMA Done Interrupt */
    CRC_POLY_Type Polynomial; /*!< CRC Polynomial (CRC Mode only) */
} CRC_CFG_Type;


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void HAL_CRC_Init(CRC_CFG_Type *pConfig);
void HAL_CRC_DeInit(void);
void HAL_CRC_SetInitVal(uint32_t Init);
void HAL_CRC_ApplyInitVal(void);
void HAL_CRC_SetInputData8(uint8_t Data);
uint32_t HAL_CRC_GetOutputData(void);
FlagStatus HAL_CRC_GetInterruptStatus(void);
void HAL_CRC_ClearInterruptStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_CRC_H_ */
/* --------------------------------- End Of File ------------------------------ */
