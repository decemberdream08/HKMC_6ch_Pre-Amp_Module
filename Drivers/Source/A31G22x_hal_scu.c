/**
 *******************************************************************************
 * @file        A31G22x_hal_scu.c
 * @author      ABOV R&D Division
 * @brief       Contains all functions support for SCU(System Control Unit) dirver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "A31G22x_hal_scu.h"
#include "A31G22x_hal_pcu.h"
#include "A31G22x_hal_cfmc.h"


/******************************************************************************
* @brief      Control LSE(low Speed External oscillator)
*             Before LSE enable setting,
*             you have to set clock ports as SXIN, SXOUT in MOD, AFSRx reg
* @param      LSE_Control, should be:
*              - LSE_STOP    : 0x00
*              - LSE_EN      : 0x08
*              - LSE_EN_DIV2 : 0x09
*              - LSE_EN_DIV4 : 0x0A
* @return     None
*******************************************************************************/
void HAL_SCU_LSE_ClockConfig(uint32_t LSE_Control) {
    volatile uint32_t reg_val32;

    // To use LSE clock, PF2 and PF3 ports must be set to SXIN and SXOUT before the LSE clock is enabled.
    // Setting SXIN Port

    HAL_GPIO_ConfigOutput((PORT_Type *)PF, 2, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction((PORT_Type *)PF, 2, PCU_ALT_FUNCTION_3);
    HAL_GPIO_ConfigPullup((PORT_Type *)PF, 2, PCU_PUPD_DISABLE);

    // Setting SXOUT Port
    HAL_GPIO_ConfigOutput((PORT_Type *)PF, 3, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction((PORT_Type *)PF, 3, PCU_ALT_FUNCTION_3);
    HAL_GPIO_ConfigPullup((PORT_Type *)PF, 3, PCU_PUPD_DISABLE);

    reg_val32 = SCU->CSCR;
    reg_val32 &= ~(SCU_CSCR_LSECON_Msk);
    reg_val32 |= (LSE_Control << SCU_CSCR_LSECON_Pos);
    SCU->CSCR = SCU_CSCR_WTIDKY | reg_val32;

    // Default LSE current and noise option
    HAL_SCU_LSE_ClockConfigCurrentAndNoiseCancel(LSE_ISEL_1_79, DISABLE);
}

/******************************************************************************
* @brief      Waiting LSE starting up
* @param      None
* @return     None
*******************************************************************************/
Status HAL_SCU_LSE_ClockMonitoring(void) {
    Status Result;
    volatile uint32_t i;
    volatile uint16_t Status;
    volatile uint32_t StartUpCounter;

    // Monitoring LSE
    SCU->CMR |= (0x01UL << SCU_CMR_LSEMNT_Pos);

    // Wait till LSE is ready and if timeout is reached exit
    StartUpCounter = 0;
    do {
        Status = (SCU->CMR & SCU_CMR_LSESTS_Msk);
        StartUpCounter++;
    } while ((Status == 0) && (StartUpCounter < LSE_STARTUP_TIMEOUT));

    // Need more Wait for LSE stable, check LSE pin oscillation
    for (i = 0; i < 0x800; i++) {
        __NOP();
    }

    // Check LSE status finally
    if (SCU->CMR & SCU_CMR_LSESTS_Msk) {
        Result = SUCCESS;
    } else {
        Result = ERROR;
    }

    return Result;
}

/******************************************************************************
* @brief      Control LSI(Low Speed Internal oscillator)
* @param      LSI_Control, should be:
*              - LSI_STOP    : 0
*              - LSI_EN      : 8
*              - LSI_EN_DIV2 : 9
*              - LSI_EN_DIV4 : 10
* @return     None
*******************************************************************************/
void HAL_SCU_LSI_ClockConfig(uint32_t LSI_Control) {
    volatile uint32_t reg_val32;

    reg_val32 = SCU->CSCR;
    reg_val32 &= ~(SCU_CSCR_LSICON_Msk);
    reg_val32|=(LSI_Control << SCU_CSCR_LSICON_Pos);
    SCU->CSCR = SCU_CSCR_WTIDKY | reg_val32;
}

/******************************************************************************
* @brief      Control HSI(How Speed Internal oscillator)
* @param      HSI_Control, should be:
*              - HSI_STOP     : 0
*              - HSI_EN       : 8
*              - HSI_EN_DIV2  : 9
*              - HSI_EN_DIV4  : 10
*              - HSI_EN_DIV8  : 11
*              - HSI_EN_DIV16 : 12
*              - HSI_EN_DIV32 : 13
* @return     None
*******************************************************************************/
void HAL_SCU_HSI_ClockConfig(uint32_t HSI_Control) {
    volatile uint32_t reg_val32;

    reg_val32 = SCU->CSCR;
    reg_val32 &= ~(SCU_CSCR_HSICON_Msk);
    reg_val32 |= (HSI_Control << SCU_CSCR_HSICON_Pos);
    SCU->CSCR = SCU_CSCR_WTIDKY | reg_val32;
}

/******************************************************************************
* @brief      Control HSE(How Speed External oscillator)
*             Before exteranl enable setting,
*             you have to set clock ports as XIN, XOUT in MR.
* @param      HSE_Control, should be:
*              - HSE_STOP    : 0
*              - HSE_EN      : 8
*              - HSE_EN_DIV2 : 9
*              - HSE_EN_DIV4 : 10
* @return     None
*******************************************************************************/
void HAL_SCU_HSE_ClockConfig(uint32_t HSE_Control) {
    volatile uint32_t reg_val32;

    // To use HSE clock, PF1 and PF0 ports must be set to XIN and XOUT before the HSE clock is enabled.
    // Setting XIN Port

    HAL_GPIO_ConfigOutput((PORT_Type *)PF, 1, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction((PORT_Type *)PF, 1, PCU_ALT_FUNCTION_3);
    HAL_GPIO_ConfigPullup((PORT_Type *)PF, 1, PCU_PUPD_DISABLE);

    // Setting XOUT Port
    HAL_GPIO_ConfigOutput((PORT_Type *)PF, 0, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction((PORT_Type *)PF, 0, PCU_ALT_FUNCTION_3);
    HAL_GPIO_ConfigPullup((PORT_Type *)PF, 0, PCU_PUPD_DISABLE);

    reg_val32 = SCU->CSCR;
    reg_val32 &= ~(SCU_CSCR_HSECON_Msk);
    reg_val32 |= (HSE_Control << SCU_CSCR_HSECON_Pos);
    SCU->CSCR = SCU_CSCR_WTIDKY | reg_val32;

    HAL_SCU_SetHSECurrentAndNoiseCancel(HSE_ISEL_6_41, DISABLE);

}

/******************************************************************************
* @brief      Waiting HSE starting up
* @param      None
* @return     Status enumeration value:
*              - ERROR   : 0
*              - SUCCESS : 1
*******************************************************************************/
Status HAL_SCU_HSE_ClockMonitoring(void) {
    Status Result;
    volatile uint32_t i;
    volatile uint16_t Status;
    volatile uint32_t StartUpCounter;

    // Monitoring HSE
    SCU->CMR |= (0x01UL << SCU_CMR_HSEMNT_Pos);

    // Wait till HSE is ready and if timeout is reached exit
    StartUpCounter = 0;
    do {
        Status = (SCU->CMR & SCU_CMR_HSESTS_Msk);
        StartUpCounter++;
    } while ((Status == 0) && (StartUpCounter < HSE_STARTUP_TIMEOUT));

    // Need more Wait for HSE stable, check XOUT pin oscillation
    for (i = 0; i < 0x800; i++) {
        __NOP();
    }

    // Check HSE status finally
    if (SCU->CMR & SCU_CMR_HSESTS_Msk) {
        Result = SUCCESS;
    } else {
        Result = ERROR;
    }

    return Result;
}

/**********************************************************************//**
 * @brief     monitoring Main Clock
 * @param  none
 * @return  status enumeration value:
 *              - ERROR
 *              - SUCCESS
 **********************************************************************/
Status HAL_SCU_MCLK_ClockMonitoring(void)
{
    __IO uint32_t StartUpCounter = 0;
    __IO uint16_t status;

    // MCLK Monitoring Set
    SCU->CMR |= (1 << SCU_CMR_MCLKSTS_Pos); // 0: MCLK monitoring disabled, 1: MCLK monitoring enable

    /* Wait still MCLK is ready and if timeout is reached exit */
    do
    {
        status = (SCU->CMR & SCU_CMR_MCLKSTS_Msk);
        StartUpCounter++;
    } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (status != SCU_CMR_MCLKSTS_Msk));

    status = (SCU->CMR & SCU_CMR_MCLKSTS_Msk);
    if (status != SCU_CMR_MCLKSTS_Msk){
        return ERROR;
    }
    else {
        return SUCCESS;
    }
}

/******************************************************************************
* @brief      Change system control
* @param      SystemClock, should be:
*              - SCCR_LSI     : 0
*              - SCCR_LSE     : 1
*              - SCCR_HSI     : 2
*              - SCCR_HSI_PLL : 3
*              - SCCR_HSE     : 6
*              - SCCR_HSE_PLL : 7
* @return     None
*******************************************************************************/
void HAL_SCU_SystemClockChange(uint32_t SystemClock) {
    volatile uint32_t reg_val32;

    reg_val32 = SCU->SCCR;
    reg_val32 &= ~(SCU_SCCR_MCLKSEL_Msk | SCU_SCCR_PLLINCLKSEL_Msk);
    reg_val32 |= SystemClock;
    SCU->SCCR = (SCU_SCCR_WTIDKY | reg_val32);
}

/**********************************************************************//**
 * @brief       change system clock control
 * @param[in]   sysclkcon mode, should be:
 *                  - SC_FIN_HSI               : 0
 *                  - SC_FIN_HSE               : 1
 * @return      None
 **********************************************************************/
void HAL_SCU_SystemClockFinClock(uint32_t sysclkcon)
{
  uint32_t reg_val32;

    reg_val32=SCU->SCCR;
    reg_val32&=~(1<<2);
    reg_val32|=(sysclkcon<<2);
    SCU->SCCR=reg_val32 | (0x570aUL<<16);
}

/******************************************************************************
* @brief        Configure clock out  on PF4
*               Before this function setting, you have to set PF4 as CLKO in PF.MODand PF.AFSR0.
* @param[in]    divval(=CLKODIV) : 0~15  // CLKO=MCLK/(2*(CLKODIV+1))
*               Ex) MCLK=20Mh, CLKODIV=4,    20MHz/ (2*(4+1)) = 2MHz
* @param[in]    FunctionalState, should be:
*                     - DISABLE          : 0
*                     - ENABLE           : 1
* @return       None
******************************************************************************/
void HAL_SCU_ClockOutput(uint8_t divval, FunctionalState endis) {

    // PF4
    HAL_GPIO_ConfigOutput((PORT_Type *)PF, 4, PCU_MODE_ALT_FUNC);
    HAL_GPIO_ConfigFunction((PORT_Type *)PF, 4, PCU_ALT_FUNCTION_1);

    if (endis == ENABLE) {
        SCU->COR = (endis << SCU_COR_CLKOEN_Pos) | ((divval & 0xF) << SCU_COR_CLKODIV_Pos);
    } else {
        SCU->COR = 0;
    }
}

/******************************************************************************
* @brief       Monitoring External oscillator
* @param  none
* @return      Status enumeration value:
*              - ERROR
*              - SUCCESS
**********************************************************************/
Status HAL_SCU_PLL_ClockConfig(FunctionalState pllsetstate, uint8_t selbypass, uint8_t selfin,  uint8_t PREDIV, uint8_t POSTDIV1, uint8_t POSTDIV2, uint8_t OUTDIV) {
    __IO uint32_t StartUpCounter = 0;
    __IO uint32_t status;
    static volatile uint32_t i;

    if (pllsetstate == DISABLE) {
        SCU->PLLCON = 0;
        return SUCCESS;
    } else {
      SCU->PLLCON = (1 << SCU_PLLCON_PLLEN_Pos);               // PLLEn
      __NOP(); __NOP(); __NOP(); __NOP(); __NOP();    // Delay for stabilization
			SCU->PLLCON = 0
				|(6<<24)	// CTRLOPT  01:Current option = 10uA / 10:VCO bias = x1			
        | (1 << SCU_PLLCON_PLLRSTB_Pos)             // PLL reset is negated
        | (1 << SCU_PLLCON_PLLEN_Pos)               // PLLEn
        | (selbypass << SCU_PLLCON_BYPASSB_Pos)     //BYPASS 0:FOUT is bypassed as FIN, 1:FOUT is PLL output
        | (selfin << SCU_PLLCON_PLLMODE_Pos)        //PLL VCO mode  0:VCO is the same with FOUT, 1:VCO frequency is x2 of FOUT   D
        | (PREDIV << SCU_PLLCON_PREDIV_Pos)         //PREDIV     R
        | (POSTDIV1 << SCU_PLLCON_POSTDIV1_Pos)     //POSTDIV1   N1
        | (POSTDIV2 << SCU_PLLCON_POSTDIV2_Pos)     //POSTDIV2   N2
        | (OUTDIV << SCU_PLLCON_OUTDIV_Pos)         //OUTDIV     P
        ;


      // Wait till PLL LOCK is ready and if timeout is reached exit
					StartUpCounter = PLL_STARTUP_TIMEOUT;
					while(--StartUpCounter);
		
					while((SCU->PLLCON & (1UL<<31)) == 0);
    }

	return SUCCESS;
}

#if 1
/**
************************************************************************************
* @ Name : SCU_SetPLLFreq
*
* @ Parameters
*		- pllInClk 			XTAL1MHz, TAL4MHz, XTAL8MHz, XTAL16MHz, IRC32MHz
*		- setPLLFreq		PLL48MHz, PLL47MHz, ..., PLL1MHz
*
* @ Description : this function helps users easily set the value of PLL operating frequency.
************************************************************************************
*/

int32_t HAL_SCU_SetPLLFreq(PLLINCLK_Type pllInClk, PLLFREQ_Type setPllFreq) {
	uint32_t r      = 0;							// PLL input clock divider (R)
	uint32_t n1 	= 0;							// PLL multiplyer (N1)
	uint32_t n2 	= 0;							// PLL divider (N2)
	uint32_t p 		= 0;							// PLL post-divider (P)
	uint32_t d		= 0;							// PLL VCO doubler bit value (D)
	uint32_t f_in   = 0;							// PLL input clock freq.
	uint32_t f_vco  = 0;							// PLL VCO freq.

    // enable and change clock source
	if (pllInClk == XTAL1MHz || pllInClk == XTAL4MHz || pllInClk == XTAL6MHz || pllInClk == XTAL8MHz ||  pllInClk == XTAL10MHz || pllInClk == XTAL12MHz || pllInClk == XTAL16MHz) {
        HAL_SCU_HSE_ClockConfig(HSE_EN);              // Enable HSE
        HAL_SCU_HSE_ClockMonitoring();         // Wait for HSE stable
		HAL_SCU_SystemClockChange(SCCR_HSE);      // Change HSE clock

        // Update system clock speed
        SystemCoreClock = (pllInClk*1000000);
        SystemPeriClock = (pllInClk*1000000);
	} else if (pllInClk == IRC32MHz) {
        HAL_SCU_HSI_ClockConfig(HSI_EN_DIV4);          // Enable HSI (32/4 = 8MHz)
        HAL_SCU_SystemClockChange(SCCR_HSI);       // Change HSI clock
//				pllInClk = pllInClk / 4;
        // Update system clock speed
        SystemCoreClock = (pllInClk/4)*1000000; // 32/4 = 8MHz
        SystemPeriClock = (pllInClk/4)*1000000; // 32/4 = 8MHz
	} else {
		return PLL_WRONG;
	}

	// Set Dividers
    if (pllInClk == XTAL1MHz) {
        r = 0;                            // FIN = 1/(1+0) == 1
    } else if (pllInClk == XTAL4MHz) {
		r = 1;                            // FIN = 4/(1+1) == 2
    } else if (pllInClk == XTAL6MHz) {
		r = 2;							  // FIN = 6/(1+2) == 2
    } else if (pllInClk == XTAL8MHz) {
		r = 3;							  // FIN = 8/(1+3) == 2		, IRC32MHz / 4 = 8Mhz
    } else if (pllInClk == XTAL10MHz) {
		r = 4;							  // FIN = 10/(1+4) == 2
    } else if (pllInClk == XTAL12MHz) {
		r = 5;							  // FIN = 12/(1+5) == 2
    } else if (pllInClk == XTAL16MHz) {
		r = 7;							  // FIN = 16/(1+7) == 2
    }	else if (pllInClk == IRC32MHz) {
		r = 3;						      // FIN = (32/4)/(1+3) == 2
    } 
		else {
        return PLL_WRONG;
    }

		if (pllInClk == IRC32MHz) 
			f_in = ((pllInClk/4) / (r + 1));          // PLL Input clock setting for IRC32Mhz
		else
			f_in = (pllInClk / (r + 1));              // PLL Input clock setting

    // Calculate the value of each PLL divider
    if (setPllFreq > 1) {    // When pllInClk is larger than 1MHz, calculate the value of pll dividers
        // recommended f_in : 1 MHz to 3 MHz
        if (f_in == 1) {
            n1 = (setPllFreq - 1);
            n2 = 0;
            p = 0;
            d = 0;
        } else if (f_in == 2) {
            n1 = (setPllFreq - 1);
            n2 = 1;
            p = 0;
            d = 0;
        } else if (f_in == 3) {
            n1 = (setPllFreq - 1);
            n2 = 2;
            p = 0;
            d = 0;
        } else if (f_in == 4 ) {
            // PLL Input Clock is 16MHz (IRC32MHz clock is divided by 2 in SCU->CSCR<HSICON> register.)
            n1 = (setPllFreq - 1);
            n2 = 1;
            p = 0;
            d = 0;
        } else {
            return PLL_WRONG;
        }
    } else {                // When pllInClk = 1MHz, fix the value of pll dividers (Exceptional)
        n1 = 4;
        n2 = 9;
        p = 0;
        d = 0;
    }

    f_vco = f_in * n1;  // get f_vco frequency

    // Check f_vco frequency less than 200MHz?
    if(f_vco <= 200) {
        // Check if pll setting and pll lock are working properly.
        if (HAL_SCU_PLL_ClockConfig(ENABLE, PLLCON_BYPASS_PLL, d, r, n1, n2, p) == SUCCESS) {
            // Use PLL clock as the Main clock.
            if (pllInClk == XTAL1MHz || pllInClk == XTAL4MHz || pllInClk == XTAL6MHz || pllInClk == XTAL8MHz ||  pllInClk == XTAL10MHz || pllInClk == XTAL12MHz || pllInClk == XTAL16MHz) {
                HAL_SCU_SystemClockChange(SCCR_HSE_PLL);      // Change HSE_PLL clock
            } else if (pllInClk == IRC32MHz) {
                HAL_SCU_SystemClockChange(SCCR_HSI_PLL);      // Change HSI_PLL clock
            }
             // Update system clock speed
            SystemCoreClock = (setPllFreq*1000000);
            SystemPeriClock = (setPllFreq*1000000);

            HAL_CFMC_SetflashAccesstiming(SystemCoreClock, 0, ENABLE);  // automatically code flash access time calibration
            return PLL_OK;
        } else {
            return PLL_WRONG;
        }
    } else {
		return	PLL_WRONG;
	}

}
#endif


/*----------------------------------------------------------------------------
   @brief        Set Timer1n Clock
   @param[in]    t1nclk                           T1NCLK_MCCR1, T1NCLK_PCLK
   @explain      This macro sets timer1n clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_Timer1n_ClockConfig(uint32_t t1nclk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_T1xCLK_Msk);
    temp |= (t1nclk << SCU_PPCLKSR_T1xCLK_Pos);
    SCU->PPCLKSR = temp;
}

/*----------------------------------------------------------------------------
   @brief        Set Timer20 Clock
   @param[in]    t20clk                           T20CLK_MCCR2, T20CLK_PCLK
   @explain      This macro sets timer20 clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_Timer20_ClockConfig(uint32_t t20clk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_T20CLK_Msk);
    temp |= (t20clk << SCU_PPCLKSR_T20CLK_Pos);
    SCU->PPCLKSR = temp;
}

/*----------------------------------------------------------------------------
   @brief        Set Timer30 Clock
   @param[in]    t30clk                           T30CLK_MCCR2, T30CLK_PCLK
   @explain      This macro sets timer30 clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_Timer30_ClockConfig(uint32_t t30clk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_T30CLK_Msk);
    temp |= (t30clk << SCU_PPCLKSR_T30CLK_Pos);
    SCU->PPCLKSR = temp;
}

/*----------------------------------------------------------------------------
   @brief        Set Watch Timer Clock
   @param[in]    wtclk                           WTCLK_MCCR3, WTCLK_SOSC, WTCLK_WDTRC
   @explain      This macro sets watch timer clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_WT_ClockConfig(uint32_t wtclk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_WTCLK_Msk);
    temp |= (wtclk << SCU_PPCLKSR_WTCLK_Pos);
    SCU->PPCLKSR = temp;
}

/*----------------------------------------------------------------------------
   @brief        Set WatchDog Timer Clock
   @param[in]    wdtclk                           WDTCLK_WDTRC, WDTCLK_MCCR3
   @explain      This macro sets watchdog timer clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_WDT_ClockConfig(uint32_t wdtclk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_WDTCLK_Msk);
    temp |= (wdtclk << SCU_PPCLKSR_WDTCLK_Pos);
    SCU->PPCLKSR = temp;
}

/*----------------------------------------------------------------------------
   @brief        Set LCD Clock
   @param[in]    lcdclk                           WDTCLK_WDTRC, WDTCLK_MCCR5
   @explain      This macro sets watchdog timer clock
 *----------------------------------------------------------------------------*/
void HAL_SCU_LCD_ClockConfig(uint32_t lcdclk) {
    uint32_t temp;

    temp = SCU->PPCLKSR;
    temp &= ~(SCU_PPCLKSR_LCDCLK_Msk);
    temp |= (lcdclk << SCU_PPCLKSR_LCDCLK_Pos);
    SCU->PPCLKSR = temp;
}

/**********************************************************************
* @brief         Configure peri clock setting
* @param[in]     mccrnum: select REG number
*                     - MCCR1 : 1, * - MCCR2 : 2
*                     - MCCR3 : 3, * - MCCR4 : 4
*                     - MCCR5 : 5, * - MCCR6 : 6
*                     - MCCR7 : 7, * - MCCR6 : 6
* @param[in]     type :
*                         SYSTICK_TYPE, TIMER1n_TYPE,
*                         TIMER2n_TYPE, TIMER3n_TYPE,
*                         WDT_TYPE, WT_TYPE,
*                         PD0_TYPE, PD1_TYPE,
*                         LCD_TYPE,
* @param[in]     clksrc :
*                        - CLKSRC_LSI=0,
*                        - CLKSRC_LSE=3,
*                        - CLKSRC_MCLK=4,
*                        - CLKSRC_HSI=5,
*                        - CLKSRC_HSE=6,
*                     - CLKSRC_PLL=7
* @param[in]     clkdiv : Clock division value (0 to 255)
                         -
* @return        None
**********************************************************************/
void HAL_SCU_MiscClockConfig(uint8_t mccrnum, uint8_t type, uint8_t clksrc, uint8_t clkdiv) {
    volatile uint32_t tmp;

    switch (mccrnum) {
        case 1:
            tmp = SCU->MCCR1;
            if (type == SYSTICK_TYPE) {
                tmp &= 0xFFFFF800;
                tmp |= (((clksrc & 7) << 8) | ((clkdiv & 0xFF) << 0));
            } else if (type == TIMER1n_TYPE) {
                tmp &= 0xF800FFFF;
                tmp |= (((clksrc & 7) << 24) | ((clkdiv & 0xFF) << 16));
            }
            SCU->MCCR1 = tmp;
            break;

        case 2:
            SCU->MCCR2 = 0;
            tmp = SCU->MCCR2;
            if (type == TIMER2n_TYPE) {
                tmp &= 0xFFFFF800;
                tmp |= (((clksrc & 7) << 8) | ((clkdiv & 0xFF) << 0));
            } else if (type == TIMER3n_TYPE) {
                tmp &= 0xF800FFFF;
                tmp |= (((clksrc & 7) << 24) | ((clkdiv & 0xFF) << 16));
            }
            SCU->MCCR2 = tmp;
            break;

        case 3:
            tmp = SCU->MCCR3;
            if (type == WDT_TYPE) {
                tmp &= 0xFFFFF800;
                tmp |= (((clksrc & 7) <<  8) | ((clkdiv & 0xFF) << 0));
            } else if (type == WT_TYPE) {
                tmp &= 0xF800FFFF;
                tmp |= (((clksrc & 7) << 24) |((clkdiv & 0xFF) << 16));
            }
            SCU->MCCR3 = tmp;
            break;

        case 4:
            tmp = SCU->MCCR4;
            if (type == PD0_TYPE) {
                tmp &= 0xFFFFF800;
                tmp |= (((clksrc & 7) << 8) | ((clkdiv & 0xFF) << 0));
            } else if (type == PD1_TYPE) {
                tmp &= 0xF800FFFF;
                tmp |= (((clksrc & 7) << 24) | ((clkdiv & 0xFF) << 16));
            }
            SCU->MCCR4 = tmp;
            break;

        case 5:
            // This code will be modified
            tmp = SCU->MCCR5;
            if (type == LCD_TYPE) {
                tmp &= ~(SCU_MCCR5_LCDDIV_Msk | SCU_MCCR5_LCDCSEL_Msk);
                tmp |= (((clkdiv & 0xFF) << SCU_MCCR5_LCDDIV_Pos) | ((clksrc & 0x07)  << SCU_MCCR5_LCDCSEL_Pos));
            } else if (type == TS_TYPE) {}
            SCU->MCCR5 = tmp;
            break;
        case 6:
            break;
        case 7:
            tmp = SCU->MCCR7;
            if (type == ADC_TYPE) {
                tmp &= ~(SCU_MCCR7_ADCCDIV_Msk | SCU_MCCR7_ADCCSEL_Msk);
                tmp |= (((clkdiv & 0xFF) << SCU_MCCR7_ADCCDIV_Pos) | ((clksrc & 0x07)  << SCU_MCCR7_ADCCSEL_Pos));
            }
            SCU->MCCR7 = tmp;
            break;
    }
}

/**********************************************************************
* @brief         enable/disable WakeUp Source
* @param[in]     WakeUpSrc, oring is possible:
*                     - WAKEUP_GPIOD :    (1UL<<11)
*                     - WAKEUP_GPIOC :    (1UL<<10)
*                     - WAKEUP_GPIOB :    (1UL<<9)
*                     - WAKEUP_GPIOA :    (1UL<<8)
*                     - WAKEUP_FRT   :    (1UL<<2)
*                     - WAKEUP_WDT   :    (1UL<<1)
*                     - WAKEUP_LVD   :    (1UL<<0)
* @param[in]     NewState
*                     - ENABLE      :Set WakeUp Source enable
*                     - DISABLE     :Disable WakeUp Source
* @return         None
**********************************************************************/
void HAL_SCU_WakeUpSRCCmd(uint32_t WakeUpSrc, FunctionalState NewState) {
    if (NewState == ENABLE) {
        SCU->WUER |=  (WakeUpSrc);
    } else {
        SCU->WUER &= ~(WakeUpSrc);
    }
}

/*********************************************************************
* @brief        Get current value of WakeUpSRC Status.
* @param[in]    None.
* @return       Current value of WakeUpSRC Status register.
*********************************************************************/
uint32_t HAL_SCU_GetWakeUpSRCStatus(void) {
    return SCU->WUSR;
}


/*********************************************************************
* @brief         Get current value of NMI Status.
* @param[in]     None.
* @return        Current value of NMI Status register.
 *********************************************************************/
uint32_t HAL_SCU_GetNMIStatus(void) {
    return (SCU->NMIR);
}

/**********************************************************************
* @brief         enable/disable NMI Source
* @param[in]     nmisrc
* @return        None
**********************************************************************/
void HAL_SCU_SetNMI(uint32_t nmisrc) {
    SCU->NMIR = (0xA32CUL << 16) | (nmisrc & 0x3F);
}

/**********************************************************************
* @brief        enable/disable Reset Source
* @param[in]    RstSrc, oring is possible:
*                    - RST_PINRST   :    (1UL<<6)
*                    - RST_CPURST   :    (1UL<<5)
*                    - RST_SWRST    :    (1UL<<4)
*                    - RST_WDTRST   :    (1UL<<3)
*                    - RST_MCKFRST  :    (1UL<<2)
*                    - RST_HSEFRST  :    (1UL<<1)
*                    - RST_LVDRST   :    (1UL<<0)
* @param[in]    NewState
*                    - ENABLE      :Set Reset Source enable
*                    - DISABLE     :Disable Reset Source
* @return       None
**********************************************************************/
void HAL_SCU_SetResetSrc(uint32_t RstSrc, FunctionalState NewState) {
    if (NewState == ENABLE) {
        SCU->RSER |= (RstSrc);
    } else {
        SCU->RSER &= ~(RstSrc);
    }
}

/***************************************************************************//**
* @brief         Get current value of RSSR Status.
* @param[in]     None.
* @return        Current value of RSSR Status register.
*******************************************************************************/
uint32_t HAL_SCU_GetResetSrc(void) {
    return (SCU->RSSR);
}

/***************************************************************************//**
* @brief         clear Reset Status
* @param[in]     rststatus
*                    - RST_PINRST   :    (1UL<<6)
*                    - RST_CPURST   :    (1UL<<5)
*                    - RST_SWRST    :    (1UL<<4)
*                    - RST_WDTRST   :    (1UL<<3)
*                    - RST_MCKFRST  :    (1UL<<2)
*                    - RST_HSEFRST  :    (1UL<<1)
*                    - RST_LVDRST   :    (1UL<<0)
* @return        None
*******************************************************************************/
void HAL_SCU_ClearResetStatus(uint32_t rststatus) {
    SCU->RSSR |= rststatus;
}

/***************************************************************************//**
* @brief         Get current value of EMODR Status.
* @param[in]     None.
* @return        Current value of EMODR Status register.
*******************************************************************************/
Bool HAL_SCU_GetExtModeStatus(void) {
    return (Bool) SCU->EMODR;
}

/***************************************************************************//**
* @brief        Control Reset Pin Debounce. This function must be operated with 500kHz LSI Clock.
* @param[in]    En
*                     - ENABLE
*                     - DISABLE
* @param[in]    CntVal
*                     - Noise cancel delay option of Reset Pin
*                     - Count Value range(0 to 31)
* @return       None
*******************************************************************************/
void HAL_SCU_SetResetPinDebounce(FunctionalState En, uint32_t CntVal) {
    uint32_t Reg32;

    if (En == ENABLE) {
        Reg32 = SCU->RSTDBCR = (SCU_RSTDBCR_WTIDKY << SCU_RSTDBCR_WTIDKY_Pos) \
                    | (1 << SCU_RSTDBCR_EN_Pos) \
                    | (CntVal << SCU_RSTDBCR_CLKCNT_Pos);
    } else {
        Reg32 = (SCU_RSTDBCR_WTIDKY << SCU_RSTDBCR_WTIDKY_Pos) \
                        | (0 << SCU_RSTDBCR_EN_Pos) \
                        | (0 << SCU_RSTDBCR_CLKCNT_Pos);
    }

    SCU->RSTDBCR = Reg32;
}

/***************************************************************************//**
* @brief         Get previous mode before current reset event
* @param[in]     None
* @return        Previous Mode
*                    - PREVMODE_RUN
*                    - PREVMODE_SLEEP
*                    - PREVMODE_DEEPSLEEP
*                    - PREVMODE_INIT
*                    - ERROR
*******************************************************************************/
uint32_t HAL_SCU_GetPreviousModeBeforeResetEvent(void) {
    uint32_t Reg32;

    Reg32 = (SCU->SMR & SCU_SMR_PREVMODE_Msk);

    if ( (Reg32 & SCU_SMR_PREVMODE_Msk) == SCU_SMR_PREVMODE_RUN)                return PREMODE_RUN;
    else if ( (Reg32 & SCU_SMR_PREVMODE_Msk) == SCU_SMR_PREVMODE_SLEEP)         return PREMODE_SLEEP;
    else if ( (Reg32 & SCU_SMR_PREVMODE_Msk) == SCU_SMR_PREVMODE_DEEPSLEEP)     return PREMODE_DEEPSLEEP;
    else if ( (Reg32 & SCU_SMR_PREVMODE_Msk) == SCU_SMR_PREVMODE_INIT)          return PREMODE_INIT;
    else                                                                        return ERROR;
}

/***************************************************************************//**
* @brief         Set TS(Temparature Sensor) clock
* @param[in]     LSI_TS : LSI TS clock
*                     - ENABLE
*                     - DISABLE
* @param[in]     ReferenceClock
*                     - SCU_TS_REFERENCE_HSI
*                     - SCU_TS_REFERENCE_MCLK
*                     - SCU_TS_REFERENCE_HSE
*                     - SCU_TS_REFERENCE_LSE
* @param[in]     SensingClock
*                     - SCU_TS_SESNING_LSI_TS
*                     - SCU_TS_SESNING_LSI
*                     - SCU_TS_SESNING_HSI
* @return        None
*******************************************************************************/
void HAL_SCU_TS_ClockConfig(FunctionalState LSI_TS, SCU_TS_REFERENCE_Type ReferenceClock, SCU_TS_SENSING_Type SensingClock) {
    volatile uint32_t Reg32;

    Reg32 = SCU->MCCR5;
    Reg32 &= ~(SCU_MCCR5_TSRCSEL_Msk | SCU_MCCR5_TSSCSEL_Msk | SCU_MCCR5_TSSLSITSEN_Msk);
    Reg32 |= 0x00UL
        | ((ReferenceClock << SCU_MCCR5_TSRCSEL_Pos) & SCU_MCCR5_TSRCSEL_Msk)
        | ((SensingClock << SCU_MCCR5_TSSCSEL_Pos) & SCU_MCCR5_TSSCSEL_Msk)
        | ((LSI_TS << SCU_MCCR5_TSSLSITSEN_Pos) & SCU_MCCR5_TSSLSITSEN_Msk);
    SCU->MCCR5 = Reg32;
}

/*******************************************************************************
* @brief      Check Bootmode
* @param      None
* @return     None
*******************************************************************************/
FunctionalState HAL_SCU_BootCheck(void) {
    volatile uint32_t Reg32;

    Reg32 = SCU->EMODR;

    if ((Reg32 & SCU_EMODR_BOOT_Msk) == SCU_EMODR_BOOT_Msk) {
        return ENABLE;          // Boot Pin (PB3) is High (Normal Mode)
    } else {
        return DISABLE;         // Boot Pin (PB3) is Low (Boot Mode)
    }
}

/*******************************************************************************
* @brief      Check Bootmode
* @param[in]      clksrc
*                   - SYSCLK_LSI
*                   - SYSCLK_LSE
*                   - SYSCLK_HSI
*                   - SYSCLK_HSE
* @param[in]      div
*                   - SYSDIV_NONE
*                   - SYSDIV_2
*                   - SYSDIV_4
*                   - SYSDIV_8
*                   - SYSDIV_16
*                   - SYSDIV_32
* @return     Status
*                    - ERROR
*                    - SUCCESS
*******************************************************************************/
Status HAL_SCU_SetSystemClock(SYSCLK_Type clksrc, SYSCLK_DIV_Type div) {
    volatile uint32_t Reg32;

    switch(clksrc) {
        case SYSCLK_LSI:
            if (div == SYSDIV_NONE) {
                HAL_SCU_LSI_ClockConfig(LSI_EN);
                HAL_SCU_SystemClockChange(SCCR_LSI);

                SystemCoreClock = LSI_CLOCK;
                SystemPeriClock = LSI_CLOCK;
                return SUCCESS;
            } else if (div == SYSDIV_2) {
                HAL_SCU_LSI_ClockConfig(LSI_EN_DIV2);
                HAL_SCU_SystemClockChange(SCCR_LSI);

                SystemCoreClock = LSI_CLOCK/2;
                SystemPeriClock = LSI_CLOCK/2;
                return SUCCESS;
            } else if (div == SYSDIV_4) {
                HAL_SCU_LSI_ClockConfig(LSI_EN_DIV4);
                HAL_SCU_SystemClockChange(SCCR_LSI);

                SystemCoreClock = LSI_CLOCK/4;
                SystemPeriClock = LSI_CLOCK/4;
                return SUCCESS;
            } else {
                return ERROR;
            }
        case SYSCLK_LSE:
            HAL_SCU_HSI_ClockConfig(HSI_EN);
            if (div == SYSDIV_NONE) {
                HAL_SCU_LSE_ClockConfig(LSE_EN);
                HAL_SCU_LSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_LSE);

                SystemCoreClock = LSE_CLOCK;
                SystemPeriClock = LSE_CLOCK;
                HAL_SCU_HSI_ClockConfig(HSI_STOP);
                return SUCCESS;
            } else if (div == SYSDIV_2) {
                HAL_SCU_LSE_ClockConfig(LSE_EN_DIV2);
                HAL_SCU_LSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_LSE);

                SystemCoreClock = LSE_CLOCK/2;
                SystemPeriClock = LSE_CLOCK/2;
                HAL_SCU_HSI_ClockConfig(HSI_STOP);
                return SUCCESS;
            } else if (div == SYSDIV_4) {
                HAL_SCU_LSE_ClockConfig(LSE_EN_DIV4);
                HAL_SCU_LSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_LSE);

                SystemCoreClock = LSE_CLOCK/4;
                SystemPeriClock = LSE_CLOCK/4;
                HAL_SCU_HSI_ClockConfig(HSI_STOP);
                return SUCCESS;
            } else {
                return ERROR;
            }
        case SYSCLK_HSE:
            if (div == SYSDIV_NONE) {
                HAL_SCU_HSE_ClockConfig(HSE_EN);
                HAL_SCU_HSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_HSE);

                SystemCoreClock = HSE_CLOCK;   // XTAL 8MHz (Default)
                SystemPeriClock = HSE_CLOCK;   // XTAL 8MHz (Default)
                return SUCCESS;
            } else if (div == SYSDIV_2) {
                HAL_SCU_HSE_ClockConfig(HSE_EN_DIV2);
                HAL_SCU_HSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_HSE);

                SystemCoreClock = HSE_CLOCK/2;
                SystemPeriClock = HSE_CLOCK/2;
                return SUCCESS;
            } else if (div == SYSDIV_4) {
                HAL_SCU_HSE_ClockConfig(HSE_EN_DIV4);
                HAL_SCU_HSE_ClockMonitoring();
                HAL_SCU_SystemClockChange(SCCR_HSE);

                SystemCoreClock = HSE_CLOCK/4;
                SystemPeriClock = HSE_CLOCK/4;
                return SUCCESS;
            } else {
                return ERROR;
            }
        case SYSCLK_HSI:
            if (div == SYSDIV_NONE) {
                HAL_SCU_HSI_ClockConfig(HSI_EN);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK;
                SystemPeriClock = HSI_CLOCK;
                return SUCCESS;
            } else if (div == SYSDIV_2) {
                HAL_SCU_HSI_ClockConfig(HSI_EN_DIV2);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK/2;
                SystemPeriClock = HSI_CLOCK/2;
                return SUCCESS;
            } else if (div == SYSDIV_4) {
                HAL_SCU_HSI_ClockConfig(HSI_EN_DIV4);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK/4;
                SystemPeriClock = HSI_CLOCK/4;
                return SUCCESS;
            } else if (div == SYSDIV_8) {
                HAL_SCU_HSI_ClockConfig(HSI_EN_DIV8);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK/8;
                SystemPeriClock = HSI_CLOCK/8;
                return SUCCESS;
             } else if (div == SYSDIV_16) {
                HAL_SCU_HSI_ClockConfig(HSI_EN_DIV16);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK/16;
                SystemPeriClock = HSI_CLOCK/16;
                return SUCCESS;
              } else if (div == SYSDIV_32) {
                HAL_SCU_HSI_ClockConfig(HSI_EN_DIV32);
                HAL_SCU_SystemClockChange(SCCR_HSI);

                SystemCoreClock = HSI_CLOCK/32;
                SystemPeriClock = HSI_CLOCK/32;
                return SUCCESS;
            } else {
                return ERROR;
            }
        default:
            return ERROR;
    }
}

void HAL_SCU_SetHSECurrentAndNoiseCancel(HSE_ISEL_Type hse, FunctionalState NoiseCancelSkip) {
    uint32_t    Reg32;

    // This routine is used after HSE is Enable.

	// To set HSE trim value, Flash mode is selected as trim mode entry
	CFMC->MR = 0xA5;
	CFMC->MR = 0x5A;

    Reg32 = SCU->EOSCR;     // Get SCU->EOSCR reigster value
    Reg32 &= ~(SCU_EOSCR_EMEN_Msk | SCU_EOSCR_ISE_Msk | SCU_EOSCR_NCOPT_Msk | SCU_EOSCR_NCSKIP_Msk);

    // Set HSE Current and Noise Cancel Delay Option by HSE Op. Freq
    switch(hse) {
        case HSE_MAX_4MHz:
            Reg32 = (1 << SCU_EOSCR_EMEN_Pos) | (HSE_ISEL_2_71 << SCU_EOSCR_ISE_Pos) | (HSE_NCOPT_23<< SCU_EOSCR_NCOPT_Pos);
            break;
        case HSE_MAX_8MHz:
            Reg32 = (1 << SCU_EOSCR_EMEN_Pos) | (HSE_ISEL_5_78 << SCU_EOSCR_ISE_Pos) | (HSE_NCOPT_18<< SCU_EOSCR_NCOPT_Pos);
            break;
        case HSE_MAX_12MHz:
            Reg32 = (1 << SCU_EOSCR_EMEN_Pos) | (HSE_ISEL_6_41 << SCU_EOSCR_ISE_Pos) | (HSE_NCOPT_13<< SCU_EOSCR_NCOPT_Pos);
            break;
        case HSE_MAX_16MHz:
            Reg32 = (1 << SCU_EOSCR_EMEN_Pos) | (HSE_ISEL_6_72 << SCU_EOSCR_ISE_Pos) | (HSE_NCOPT_8<< SCU_EOSCR_NCOPT_Pos);
            break;
    }

    // Set HSE Noise Cancel Skip
    if (NoiseCancelSkip == ENABLE) {
        Reg32 |= SCU_EOSCR_NCSKIP_Msk;      // Enable Noise Cancel Skip
    } else {
       Reg32 &= ~(SCU_EOSCR_NCSKIP_Msk);    // Disable Noise Cancel Skip (Default)
    }

    // Update EOSCR Register
    SCU->EOSCR = Reg32;

    // Exit trim mode
    CFMC->MR = 0;
}

void HAL_SCU_LSE_ClockConfigCurrentAndNoiseCancel(LSE_ISEL_Type lse_i, FunctionalState NoiseCancelSkip) {
    uint32_t    Reg32;

    // This routine is used after LSE is enable.

	// To set LSE trim value, Flash mode is selected as trim mode entry
	CFMC->MR = 0xA5;
	CFMC->MR = 0x5A;

    Reg32 = SCU->EOSCR;     // Get SCU->EOSCR reigster value
    Reg32 &= ~(SCU_EOSCR_ESEN_Msk | SCU_EOSCR_ESISEL_Msk | SCU_EOSCR_ESNCBYPS_Msk);

    // Set LSE Current and Noise Cancel Delay Option by HSE Op. Freq
    switch(lse_i) {
        case LSE_ISEL_2_04:
            Reg32 |= (1 << SCU_EOSCR_ESEN_Pos) | (LSE_ISEL_2_04 << SCU_EOSCR_ESISEL_Pos);
            break;
        case LSE_ISEL_1_93:
            Reg32 |= (1 << SCU_EOSCR_ESEN_Pos) | (LSE_ISEL_1_93 << SCU_EOSCR_ESISEL_Pos);
            break;
        case LSE_ISEL_1_79:
            Reg32 |= (1 << SCU_EOSCR_ESEN_Pos) | (LSE_ISEL_1_79 << SCU_EOSCR_ESISEL_Pos);
            break;
        case LSE_ISEL_1_57:
            Reg32 |= (1 << SCU_EOSCR_ESEN_Pos) | (LSE_ISEL_1_57 << SCU_EOSCR_ESISEL_Pos);
            break;
    }

    // Set LSE Noise Cancel Skip
    if (NoiseCancelSkip == ENABLE) {
        Reg32 |= SCU_EOSCR_ESNCBYPS_Msk;      // Enable Noise Cancel Skip
    } else {
       Reg32 &= ~(SCU_EOSCR_ESNCBYPS_Msk);    // Disable Noise Cancel Skip (Default)
    }

    // Update EOSCR Register
    SCU->EOSCR = Reg32;

    // Exit trim mode
    CFMC->MR = 0;
}

Status HAL_SCU_PeripheralCmd(PERI_TYPE peripheral, FunctionalState sel) {
    uint32_t periBlock;
    uint32_t periClock;

    /*< Assign selected peripheral to variables     */
    if (peripheral == PERI_DMA)
    {
        // PERI_TYPE: 0, DMA
        periBlock = SCU_PER1_DMA_Msk;
        periClock = SCU_PCER1_DMA_Msk;
    }
    else if (peripheral == PERI_GPIOA)
    {
        // PERI_TYPE: 1, GPIOA
        periBlock = SCU_PER1_GPIOA_Msk;
        periClock = SCU_PCER1_GPIOA_Msk;
    }
    else if (peripheral == PERI_GPIOB)
    {
        // PERI_TYPE: 2, GPIOB
        periBlock = SCU_PER1_GPIOB_Msk;
        periClock = SCU_PCER1_GPIOB_Msk;
    }
    else if (peripheral == PERI_GPIOC)
    {
        // PERI_TYPE: 3, GPIOC
        periBlock = SCU_PER1_GPIOC_Msk;
        periClock = SCU_PCER1_GPIOC_Msk;
    }
    else if (peripheral == PERI_GPIOD)
    {
        // PERI_TYPE: 4, GPIOD
        periBlock = SCU_PER1_GPIOD_Msk;
        periClock = SCU_PCER1_GPIOD_Msk;
    }
    else if (peripheral == PERI_GPIOE)
    {
        // PERI_TYPE: 5, GPIOE
        periBlock = SCU_PER1_GPIOE_Msk;
        periClock = SCU_PCER1_GPIOE_Msk;
    }
    else if (peripheral == PERI_GPIOF)
    {
        periBlock = SCU_PER1_GPIOF_Msk;
        periClock = SCU_PCER1_GPIOF_Msk;
    }
    else if (peripheral == PERI_TIMER10)
    {
        periBlock = SCU_PER1_TIMER10_Msk;
        periClock = SCU_PCER1_TIMER10_Msk;
    }
    else if (peripheral == PERI_TIMER11)
    {
        periBlock = SCU_PER1_TIMER11_Msk;
        periClock = SCU_PCER1_TIMER11_Msk;
    }
    else if (peripheral == PERI_TIMER12)
    {
        periBlock = SCU_PER1_TIMER12_Msk;
        periClock = SCU_PCER1_TIMER12_Msk;
    }
    else if (peripheral == PERI_TIMER13)
    {
        periBlock = SCU_PER1_TIMER13_Msk;
        periClock = SCU_PCER1_TIMER13_Msk;
    }
    else if (peripheral == PERI_TIMER14)
    {
        periBlock = SCU_PER1_TIMER14_Msk;
        periClock = SCU_PCER1_TIMER14_Msk;
    }
    else if (peripheral == PERI_TIMER15)
    {
        periBlock = SCU_PER1_TIMER15_Msk;
        periClock = SCU_PCER1_TIMER15_Msk;
    }
    else if (peripheral == PERI_TIMER16)
    {
        periBlock = SCU_PER1_TIMER16_Msk;
        periClock = SCU_PCER1_TIMER16_Msk;
    }
    else if (peripheral == PERI_TIMER16)
    {
        periBlock = SCU_PER1_TIMER16_Msk;
        periClock = SCU_PCER1_TIMER16_Msk;
    }
    else if (peripheral == PERI_TIMER20)
    {
        periBlock = SCU_PER1_TIMER20_Msk;
        periClock = SCU_PCER1_TIMER20_Msk;
    }
    else if (peripheral == PERI_TIMER21)
    {
        periBlock = SCU_PER1_TIMER21_Msk;
        periClock = SCU_PCER1_TIMER21_Msk;
    }
    else if (peripheral == PERI_TIMER30)
    {
        periBlock = SCU_PER1_TIMER30_Msk;
        periClock = SCU_PCER1_TIMER30_Msk;
    }
    else if (peripheral == PERI_WT)
    {
        periBlock = SCU_PER1_WT_Msk;
        periClock = SCU_PCER1_WT_Msk;
    }
    else if (peripheral == PERI_I2C0)
    {
        periBlock = SCU_PER2_I2C0_Msk;
        periClock = SCU_PCER2_I2C0_Msk;
    }
    else if (peripheral == PERI_I2C1)
    {
        periBlock = SCU_PER2_I2C1_Msk;
        periClock = SCU_PCER2_I2C1_Msk;
    }
    else if (peripheral == PERI_I2C2)
    {
        periBlock = SCU_PER2_I2C2_Msk;
        periClock = SCU_PCER2_I2C2_Msk;
    }
    else if (peripheral == PERI_USART10)
    {
        periBlock = SCU_PER2_USART10_Msk;
        periClock = SCU_PCER2_USART10_Msk;
    }
    else if (peripheral == PERI_USART11)
    {
        periBlock = SCU_PER2_USART11_Msk;
        periClock = SCU_PCER2_USART11_Msk;
    }
    else if (peripheral == PERI_USART12)
    {
        periBlock = SCU_PER2_USART12_Msk;
        periClock = SCU_PCER2_USART12_Msk;
    }
    else if (peripheral == PERI_USART13)
    {
        periBlock = SCU_PER2_USART13_Msk;
        periClock = SCU_PCER2_USART13_Msk;
    }
    else if (peripheral == PERI_UART0)
    {
        periBlock = SCU_PER2_UART0_Msk;
        periClock = SCU_PCER2_UART0_Msk;
    }
    else if (peripheral == PERI_UART1)
    {
        periBlock = SCU_PER2_UART1_Msk;
        periClock = SCU_PCER2_UART1_Msk;
    }
    else if (peripheral == PERI_SPI20)
    {
        periBlock = SCU_PER2_SPI20_Msk;
        periClock = SCU_PCER2_SPI20_Msk;
    }
    else if (peripheral == PERI_SPI21)
    {
        periBlock = SCU_PER2_SPI21_Msk;
        periClock = SCU_PCER2_SPI21_Msk;
    }
    else if (peripheral == PERI_ADC)
    {
        periBlock = SCU_PER2_ADC_Msk;
        periClock = SCU_PCER2_ADC_Msk;
    }
    else if (peripheral == PERI_DAC)
    {
        periBlock = SCU_PER2_DAC_Msk;
        periClock = SCU_PCER2_DAC_Msk;
    }
    else if (peripheral == PERI_CMP)
    {
        periBlock = SCU_PER2_CMP_Msk;
        periClock = SCU_PCER2_CMP_Msk;
    }
    else if (peripheral == PERI_TS)
    {
        periBlock = SCU_PER2_TS_Msk;
        periClock = SCU_PCER2_TS_Msk;
    }
    else if (peripheral == PERI_LCD)
    {
        periBlock = SCU_PER2_LCD_Msk;
        periClock = SCU_PCER2_LCD_Msk;
    }
    else if (peripheral == PERI_CRC)
    {
        periBlock = SCU_PER2_CRC_Msk;
        periClock = SCU_PCER2_CRC_Msk;
    }
    else
    {
        // PERI_TYPE: Out of bound
        return ERROR;
    }

    /*< Update SCU_PER and SCU_PCER Register       */
    if (peripheral <= PERI1_MAX)
    {
        // PERI_TYPE: 0 ~ 17
        SCU->PER1 &= ~periBlock;
        SCU->PCER1 &= ~periClock;

        if (sel == ENABLE)
        {
            SCU->PER1 |= periBlock;
            SCU->PCER1 |= periClock;
        } else {
            ;
        }
    }
    else if ((peripheral > PERI1_MAX) && (peripheral <= PERI2_MAX))
    {
         // PERI_TYPE: 18 ~ 34
        SCU->PER2 &= ~periBlock;
        SCU->PCER2 &= ~periClock;

        if (sel == ENABLE)
        {
            SCU->PER2 |= periBlock;
            SCU->PCER2 |= periClock;
        } else {
            ;
        }
    }
    else
    {
        // PERI_TYPE: Out of bound
        return ERROR;
    }

    return SUCCESS;
}

/* --------------------------------- End Of File ------------------------------ */
