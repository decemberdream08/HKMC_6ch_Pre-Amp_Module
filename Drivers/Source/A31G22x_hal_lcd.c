/**
 *******************************************************************************
 * @file        A31G22x_hal_lcd.c
 * @author      ABOV R&D Division
 * @brief       Contains all functions support for LCD dirver on A31G22x
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
#ifdef _LCD

#include "A31G22x_hal_scu.h"
#include "A31G22x_hal_lcd.h"
#include "A31G22x_hal_pcu.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/


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

void HAL_LCD_Module(FunctionalState state) {
    // Peri and Clock Disable
	SCU->PER2 &= ~(1 << SCU_PER2_LCD_Pos);
	SCU->PCER2 &= ~(1 << SCU_PER2_LCD_Pos);

    // Peri and Clock enable
    if (state == ENABLE) {
        SCU->PER2 |= (1 << SCU_PER2_LCD_Pos);
        SCU->PCER2 |= (1 << SCU_PER2_LCD_Pos);
    }
}

void HAL_LCD_Configuration(LCD_CFG_Type *lcdCfg) {
    volatile uint32_t Reg32;
    
    // LCD->CR
    Reg32 = LCD->CR;    // Get LCD->CR
    
    Reg32 = ( (((lcdCfg->InternalBiasResistor) & 0x3) << LCD_CR_IRSEL_Pos)
            | (((lcdCfg->LcdDutyandBias) & 0x7) << LCD_CR_DBS_Pos)
            | (((lcdCfg->LcdClock) & 0x3) << LCD_CR_LCLK_Pos) );

    LCD->CR = Reg32;    // Update LCD->CR Register
   
    
    // LCD->BCCR
    Reg32 = LCD->BCCR;  // Get LCD->BCCR
    
    Reg32 = ( (((lcdCfg->LcdAutoBias) & 0x1) << LCD_BCCR_LCDABC_Pos)
            | (((lcdCfg->BiasModeClk) & 0x7) << LCD_BCCR_BMSEL_Pos)
            | (((lcdCfg->LcdContrast) & 0x1) << LCD_BCCR_LCTEN_Pos)    
            | (((lcdCfg->VlcVoltage) & 0xF) << LCD_BCCR_VLCD_Pos) );
    
    LCD->BCCR = Reg32;    // Update LCD->BCCR Register
    
    
    // LCD->BSSR
    Reg32 = LCD->BSSR;    // Get LCD->BSSR
    
    Reg32 = ( (((lcdCfg->LcdExtBias) & 0x1) << LCD_BSSR_LCDDR_Pos)
            | (((lcdCfg->LcdExtBiasPath) & 0x1) << LCD_BSSR_LCDEPEN_Pos) );
            
    if (lcdCfg->LcdExtBias == ENABLE) {
        Reg32 |= (1 << LCD_BSSR_VLE_EN_Pos); 
    } else {
        Reg32 &= ~(1 << LCD_BSSR_VLE_EN_Pos);
    }
    LCD->BSSR = Reg32;    // Update LCD->BSSR Register
}

void HAL_LCD_SetVLC(LCD_VLC_Type vlc, FunctionalState state) {
    switch(vlc) {
        case LCD_VLC0:
            LCD->BSSR &= ~(LCD_BSSR_VLC0EN_Msk);
            if (state == ENABLE) {
                LCD->BSSR |= (1 << LCD_BSSR_VLC0EN_Pos);
            }
            break;
        case LCD_VLC1:
            LCD->BSSR &= ~(LCD_BSSR_VLC1EN_Msk);
            if (state == ENABLE) {
                LCD->BSSR |= (1 << LCD_BSSR_VLC1EN_Pos);
            }            
            break;
        case LCD_VLC2:
            LCD->BSSR &= ~(LCD_BSSR_VLC2EN_Msk);
            if (state == ENABLE) {
                LCD->BSSR |= (1 << LCD_BSSR_VLC2EN_Pos);
            }            
            break;
        case LCD_VLC3:
            LCD->BSSR &= ~(LCD_BSSR_VLC3EN_Msk);
            if (state == ENABLE) {
                LCD->BSSR |= (1 << LCD_BSSR_VLC3EN_Pos);
            }            
            break;
        }        
}

void HAL_LCD_Display (FunctionalState state) {   
    LCD->CR &= ~(LCD_CR_DISP_Msk);
    
    if (state == ENABLE) {
        LCD->CR |= (1 << LCD_CR_DISP_Pos);
    }
}


void HAL_LCD_PortInit(LCD_PORT_Type *lcdport) {
    HAL_GPIO_ConfigOutput(lcdport->port, lcdport->pin_number, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction(lcdport->port, lcdport->pin_number, PCU_ALT_FUNCTION_0);
}

#endif /* _LCD */
/* --------------------------------- End Of File ------------------------------ */
