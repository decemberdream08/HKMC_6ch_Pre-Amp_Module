/**
 *******************************************************************************
 * @file        A31G22x_hal_dmac.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for DMA Controller driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_DMAC_H_
#define _A31G22x_DMAC_H_

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
 * @brief  DMAC peripheral enumerated definition
 */
typedef enum {
    DMAC_PERIPHERAL_IDLE         = 0,     /*!< Idle */
    DMAC_PERIPHERAL_UART0_RX,              /*!< DMA of UART0 Rx */
    DMAC_PERIPHERAL_UART0_TX,             /*!< DMA of UART0 Tx */
    DMAC_PERIPHERAL_UART1_RX,             /*!< DMA of UART1 Rx */
    DMAC_PERIPHERAL_UART1_TX,            /*!< DMA of UART1 Tx */
    DMAC_PERIPHERAL_CRC,                 /*!< DMA of CRC (SRAM Only) */
    DMAC_PERIPHERAL_RESERVED0,             /*!< Reserved */
    DMAC_PERIPHERAL_RESERVED1,             /*!< Reserved */
    DMAC_PERIPHERAL_RESERVED2,             /*!< Reserved */
    DMAC_PERIPHERAL_SPI20_RX,             /*!< DMA of SPI20 Rx */
    DMAC_PERIPHERAL_SPI20_TX,             /*!< DMA of SPI20 Tx */
    DMAC_PERIPHERAL_SPI21_RX,             /*!< DMA of SPI21 Rx */
    DMAC_PERIPHERAL_SPI21_TX,             /*!< DMA of SPI21 Tx */
    DMAC_PERIPHERAL_ADC,                 /*!< DMA of ADC */
    DMAC_PERIPHERAL_DAC,                  /*!< DMA of DAC */
    DMAC_PERIPHERAL_RESERVED3,             /*!< Reserved */
    DMAC_PERIPHERAL_RESERVED4,             /*!< Reserved */
    DMAC_PERIPHERAL_USART10_RX,         /*!< DMA of USART10 Rx */
    DMAC_PERIPHERAL_USART10_TX,         /*!< DMA of USART10 Rx */
    DMAC_PERIPHERAL_USART11_RX,         /*!< DMA of USART11 Rx */
    DMAC_PERIPHERAL_USART11_TX,         /*!< DMA of USART11 Rx */
    DMAC_PERIPHERAL_USART12_RX,         /*!< DMA of USART12 Rx */
    DMAC_PERIPHERAL_USART12_TX,         /*!< DMA of USART12 Rx */
    DMAC_PERIPHERAL_USART13_RX,         /*!< DMA of USART13 Rx */
    DMAC_PERIPHERAL_USART13_TX,         /*!< DMA of USART13 Rx */
} DMAC_PERIPHERAL_Type;

/**
 * @brief  DMAC transfer width enumerated definition
 */
typedef enum {
    DMAC_WIDTH_BYTE      = 0x00UL, /*!< Byte size transfer (8-bit) */
    DMAC_WIDTH_HALF_WORD = 0x01UL, /*!< Half word size transfer (16-bit) */
    DMAC_WIDTH_WORD      = 0x02UL  /*!< Word size transfer (32-bit) */
} DMAC_WIDTH_Type;

/**
 * @brief  DMAC transfer width enumerated definition
 */
typedef enum {
    DMAC_DIRECTION_TX = 0x00UL, /*!< From memory to peripheral */
    DMAC_DIRECTION_RX = 0x01UL  /*!< From peripheral to memory */
} DMAC_DIRECTION_Type;

/**
 * @brief  DMAC Channel configuration structure type definition
 */
typedef struct {
    DMAC_PERIPHERAL_Type Peripheral; /*!< Peripheral selection */
    DMAC_WIDTH_Type Width; /*!< Transfer width */
    DMAC_DIRECTION_Type Direction; /*!< Transfer direction */
    uint32_t PeripheralAddress; /*!< Peripheral address */
} DMAC_CFG_Type;

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void HAL_DMAC_Init(DMAC_Type *pDMACx, DMAC_CFG_Type *pConfig);
void HAL_DMAC_DeInit(DMAC_Type *pDMACx);
uint32_t HAL_DMAC_GetTransferCount(DMAC_Type *pDMACx);
void HAL_DMAC_SetTransferCount(DMAC_Type *pDMACx, uint32_t Count);
uint32_t HAL_DMAC_GetMemoryAddress(DMAC_Type *pDMACx);
void HAL_DMAC_SetMemoryAddress(DMAC_Type *pDMACx, uint32_t Address);
FlagStatus HAL_DMAC_GetStatus(DMAC_Type *pDMACx);
void HAL_DMAC_Start(DMAC_Type *pDMACx);
void HAL_DMAC_Stop(DMAC_Type *pDMACx);
void HAL_DMAC_ClearBuffer(DMAC_Type *pDMACx);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_DMAC_H_ */
/* --------------------------------- End Of File ------------------------------ */
