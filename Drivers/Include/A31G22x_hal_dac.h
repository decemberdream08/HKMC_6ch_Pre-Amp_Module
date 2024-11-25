/**
 *******************************************************************************
 * @file        A31G22x_hal_dac.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for DAC (Digital to Analog) driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/
 
#ifndef _A31G22x_HAL_DAC_H_
#define _A31G22x_HAL_DAC_H_

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
 * @brief  DAC status enumerated definition
 */
typedef enum {
    DAC_STATUS_DMA_DONE_INT = (0x01UL << DAC_ICR_DMAIF_Pos), /*!< DMA done occurred */
    DAC_STATUS_DMA_UNDERRUN_INT = (0x01UL << DAC_ICR_DUDRUNF_Pos) /*!< DMA under-run occurred */
} DAC_STATUS_Type;

/**
 * @brief  DAC DMA Interrupt Enable status enumerated definition
 */
typedef enum {
    DAC_STATUS_DMA_DONE_ENABLE = (0x01UL << DAC_ICR_DAMIE_Pos), /*!< DMA done Interrupt Enable */
    DAC_STATUS_DMA_UNDERRUN_ENABLE = (0x01UL << DAC_ICR_DUDRUNE_Pos) /*!< DMA under-run Interrupt Enable */
} DAC_INTR_ENABLE_Type;


/**
 * @brief  DAC reload signal enumerated definition
 */
typedef enum {
    DAC_RELOAD_SIGNAL_ALWAYS = 0x00UL, /*!< always */
    DAC_RELOAD_SIGNAL_TIMER10 = 0x02UL, /*!< Timer 10 match signal */
    DAC_RELOAD_SIGNAL_TIMER11 = 0x03UL /*!< Timer 11 match signal */
} DAC_RELOAD_SIGNAL_Type;

/**
 * @brief  DAC DMA UnderrunInterrupt enumerated definition
 */
typedef enum {
    DAC_DMA_UNDERRUN_INTR_DISABLE,
    DAC_DMA_UNDERRUN_INTR_ENABLE,
} DAC_DMA_UNDERRUN_Type;

/**
 * @brief  DAC DMA Rx Interrupt enumerated definition
 */
typedef enum {
    DAC_DMA_RX_INTR_DISABLE,
    DAC_DMA_RX_INTR_ENABLE,
} DAC_DMA_RX_Type;


/**
 * @brief  DAC configuration structure definition
 */
typedef struct {
    /* CR */
    FunctionalState DAC_Out; /*!< DAC Out0 (DAO/PA6) */
    FunctionalState OutBuffer; /*!< DAC Buffer. If this is disabled, buffer is bypassed */
    DAC_RELOAD_SIGNAL_Type ReloadSignal; /*!< Select DAC reload signal */
} DAC_CFG_Type;

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void HAL_DAC_Init(DAC_Type *pDACx, DAC_CFG_Type *pConfig);
void HAL_DAC_DeInit(DAC_Type *pDACx);
DAC_STATUS_Type HAL_DAC_GetStatus(DAC_Type *pDACx);
void HAL_DAC_ClearStatus(DAC_Type *pDACx, DAC_STATUS_Type Status);
uint16_t HAL_DAC_GetData(DAC_Type *pDACx);
void HAL_DAC_SetData(DAC_Type *pDACx, uint16_t Data);
uint16_t HAL_DAC_GetBuffer(DAC_Type *pDACx);
void HAL_DAC_ClearBuffer(DAC_Type *pDACx);
void HAL_DAC_Start(DAC_Type *pDACx);
void HAL_DAC_Stop(DAC_Type *pDACx);
void HAL_DAC_DmaInterrupt(DAC_Type *pDACx, DAC_DMA_UNDERRUN_Type DmaUnderrun, DAC_DMA_RX_Type DmaRx);
DAC_INTR_ENABLE_Type HAL_DAC_GetIntrEn(DAC_Type *pDACx);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_DAC_H_ */
/* --------------------------------- End Of File ------------------------------ */
