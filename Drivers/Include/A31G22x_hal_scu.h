/**
 *******************************************************************************
 * @file        A31G22x_hal_scu.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for SCU (System Control Unit) driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_HAL_SCU_H_
#define _A31G22x_HAL_SCU_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------- */
#include "A31G22x.h"
#include "A31G22x_hal_aa_types.h"

/* Private macros ------------------------------------------------------------- */
/*!< Low speed external oscillator control */
#define LSE_STOP                    (0x00UL)
#define LSE_EN                      (0x08UL)
#define LSE_EN_DIV2                 (0x09UL)
#define LSE_EN_DIV4                 (0x0AUL)

/*!< Low speed external oscillator stable timeout */
#define LSE_STARTUP_TIMEOUT         (0xFFFFFFFFUL)

/*!< Low speed interanl oscillator control */
#define LSI_STOP                    (0x00UL)
#define LSI_EN                      (0x08UL)
#define LSI_EN_DIV2                 (0x09UL)
#define LSI_EN_DIV4                 (0x0AUL)

/*!< High speed internal oscillator control */
#define HSI_STOP                    (0x00UL)
#define HSI_EN                      (0x08UL)
#define HSI_EN_DIV2                 (0x09UL)
#define HSI_EN_DIV4                 (0x0AUL)
#define HSI_EN_DIV8                 (0x0BUL)
#define HSI_EN_DIV16                (0x0CUL)
#define HSI_EN_DIV32                (0x0DUL)

/*!< High speed external oscillator control */
#define HSE_STOP                    (0x00UL)
#define HSE_EN                      (0x08UL)
#define HSE_EN_DIV2                 (0x09UL)
#define HSE_EN_DIV4                 (0x0AUL)

/*!< High speed external oscillator stable timeout */
#define HSE_STARTUP_TIMEOUT         (0xFFFFFFFFUL)

/*!< PLL stable timeout */
#define PLL_STARTUP_TIMEOUT         (240)
/*!< PLL Lock status bit */
#define PLL_LOCK                    (0x01UL << 31)



/*!< PLLCON[BYPASS] */
#define PLLCON_BYPASS_FIN           (0x00UL)
#define PLLCON_BYPASS_PLL           (0x01UL)

// PLL freq = (FIN or FIN/2) * M / N
/*!< PLLCON[PREDIV] */
#define PLLCON_FIN_DIV_1            (0x00UL)
#define PLLCON_FIN_DIV_2            (0x01UL)

/*!< PLLCON[FBCTRL] */
#define PLLCON_M_6                  (0x00UL)
#define PLLCON_M_8                  (0x01UL)
#define PLLCON_M_10                 (0x02UL)
#define PLLCON_M_12                 (0x03UL)
#define PLLCON_M_16                 (0x04UL)
#define PLLCON_M_18                 (0x05UL)
#define PLLCON_M_20                 (0x06UL)
#define PLLCON_M_26                 (0x07UL)
#define PLLCON_M_32                 (0x08UL)
#define PLLCON_M_36                 (0x09UL)
#define PLLCON_M_40                 (0x0AUL)
#define PLLCON_M_64                 (0x0BUL)

/*!< PLLCON[POSTDIV] */
#define PLLCON_N_1                  (0x00UL)
#define PLLCON_N_2                  (0x01UL)
#define PLLCON_N_3                  (0x02UL)
#define PLLCON_N_4                  (0x03UL)
#define PLLCON_N_6                  (0x04UL)
#define PLLCON_N_8                  (0x05UL)
#define PLLCON_N_16                 (0x07UL)

/*!< system clock control setting */
#define SCCR_LSI                    (0x00UL)
#define SCCR_LSE                    (0x01UL)
#define SCCR_HSI                    (0x02UL)
#define SCCR_HSI_PLL                (0x03UL)
#define SCCR_HSE                    (0x06UL)
#define SCCR_HSE_PLL                (0x07UL)

/*!< System Control Register - Write Identification Key */
#define SCU_SCR_WTIDKY              (0x9EB3UL)
#define SCB_AIRCR_VECTKEY           (0x05FAUL)

/*!< SCUCC CHIP ID */
#define CHIPID_G226 (0x4D31A00AUL)
#define CHIPID_G224 (0x4D31A00BUL)

typedef enum {
    PERI_DMA,       // 0
    PERI_GPIOA,     // 1
    PERI_GPIOB,     // 2
    PERI_GPIOC,     // 3
    PERI_GPIOD,     // 4
    PERI_GPIOE,     // 5
    PERI_GPIOF,     // 6
    PERI_TIMER10,        // 7
    PERI_TIMER11,            // 8
    PERI_TIMER12,             // 9
    PERI_TIMER13,             // 10
    PERI_TIMER14,             // 11
    PERI_TIMER15,             // 12
    PERI_TIMER16,             // 13
    PERI_TIMER20,             // 14
    PERI_TIMER21,             // 15
    PERI_TIMER30,             // 16
    PERI_WT, // 17
    PERI_I2C0,      // 18
    PERI_I2C1,      // 19
    PERI_I2C2,      // 20
    PERI_USART10,   // 21
    PERI_USART11,   // 22
    PERI_USART12,   // 23
    PERI_USART13,   // 24
    PERI_UART0,     // 25
    PERI_UART1,     // 26
    PERI_SPI20,     // 27
    PERI_SPI21,     // 28
    PERI_ADC,       // 29
    PERI_DAC,       // 30
    PERI_CMP,       // 31
    PERI_TS,        // 32
    PERI_LCD,       // 33
    PERI_CRC,       // 34
    PERI1_MAX = PERI_WT,   // 17
    PERI2_MAX = PERI_CRC   // 34
} PERI_TYPE;


enum {
    SYSTICK_TYPE = 0,
    TIMER1n_TYPE,
    TIMER2n_TYPE,
    TIMER3n_TYPE,
    WDT_TYPE,
    WT_TYPE,
    PD0_TYPE,
    PD1_TYPE,
    ADC_TYPE,
    LCD_TYPE,
    TS_TYPE,
};

typedef enum {
    CLKSRC_LSI = 0,
    CLKSRC_LSE = 3,
    CLKSRC_MCLK = 4,
    CLKSRC_HSI = 5,
    CLKSRC_HSE = 6,
    CLKSRC_PLL = 7
} CLKSRC_Type;

typedef enum {
    LVD_LEVEL_1_65 = 0,
    LVD_LEVEL_2_5,
    LVD_LEVEL_3_6,
    LVD_LEVEL_4_2
} LVD_LEVEL_Type;

typedef enum {
    LSE_ISEL_2_04 = 0,
    LSE_ISEL_1_93,
    LSE_ISEL_1_79,      // Not Use
    LSE_ISEL_1_57       // Not Use
} LSE_ISEL_Type;

typedef enum {
    HSE_ISEL_6_72 = 0,
    HSE_ISEL_6_41,
    HSE_ISEL_5_78,
    HSE_ISEL_2_71
} HSE_ISEL_Type;

typedef enum {
    HSE_NCOPT_23 = 0,
    HSE_NCOPT_18,
    HSE_NCOPT_13,
    HSE_NCOPT_8,
} HSE_NCOPT_Type;

typedef enum {
    PREMODE_RUN = 0,
    PREMODE_SLEEP = 1,
    PREMODE_DEEPSLEEP = 2,
    PREMODE_INIT = 3
} PREMODE_Type;

typedef enum {
    LSEAON_DISABLE = 0,
    LSEAON_ENABLE = 1
} LSEAON_Type;

typedef enum {
    LSIAON_DISABLE = 0,
    LSIAON_ENABLE = 1
} LSIAON_Type;

typedef enum {
    BGRAON_DISABLE = 0,
    BGRAON_ENABLE = 1
} BGRAON_Type;

typedef enum {
    VDCAON_DISABLE = 0,
    VDCAON_ENABLE = 1
} VDCAON_Type;

/**
 * @brief  System clock source selection enumerated definition
 */
typedef enum {
    SYSCLK_LSI,
    SYSCLK_LSE,
    SYSCLK_HSI,
    SYSCLK_HSE,
} SYSCLK_Type;

/**
 * @brief  System clock divider value selection enumerated definition
 */
typedef enum {
    SYSDIV_NONE = 0,
    SYSDIV_2 = 2,
    SYSDIV_4 = 4,
    SYSDIV_8 = 8,
    SYSDIV_16 = 16,
    SYSDIV_32 = 32,
} SYSCLK_DIV_Type;

/**
 * @brief HSE (XTAL) clock source selection enumerated definition
 */
typedef enum {
    HSE_MAX_4MHz,
    HSE_MAX_8MHz,
    HSE_MAX_12MHz,
    HSE_MAX_16MHz
} HSE_MAX_Type;


/**
 * @brief  PLL return status enumerated definition
 */
typedef enum _pllStatus {
    PLL_OK = 0,
    PLL_WRONG = -1,
} pllStatus;

/**
 * @brief  PLL input clock source selection enumerated definition
 */
typedef enum {
    XTAL1MHz = 0,
    XTAL4MHz = 4,
    XTAL6MHz = 6,
    XTAL8MHz = 8,
    XTAL10MHz = 10,
    XTAL12MHz = 12,
    XTAL16MHz = 16,
    IRC32MHz = 32,
} PLLINCLK_Type;

/**
 * @brief  PLL Output Frequency selection enumerated definition
 */
typedef enum _pllFreq {
    PLL1MHz = 1,
    PLL2MHz = 2,
    PLL3MHz = 3,
    PLL4MHz = 4,
    PLL5MHz = 5,
    PLL6MHz = 6,
    PLL7MHz = 7,
    PLL8MHz = 8,
    PLL9MHz = 9,
    PLL10MHz = 10,
    PLL11MHz = 11,
    PLL12MHz = 12,
    PLL13MHz = 13,
    PLL14MHz = 14,
    PLL15MHz = 15,
    PLL16MHz = 16,
    PLL17MHz = 17,
    PLL18MHz = 18,
    PLL19MHz = 19,
    PLL20MHz = 20,
    PLL21MHz = 21,
    PLL22MHz = 22,
    PLL23MHz = 23,
    PLL24MHz = 24,
    PLL25MHz = 25,
    PLL26MHz = 26,
    PLL27MHz = 27,
    PLL28MHz = 28,
    PLL29MHz = 29,
    PLL30MHz = 30,
    PLL31MHz = 31,
    PLL32MHz = 32,
    PLL33MHz = 33,
    PLL34MHz = 34,
    PLL35MHz = 35,
    PLL36MHz = 36,
    PLL37MHz = 37,
    PLL38MHz = 38,
    PLL39MHz = 39,
    PLL40MHz = 40,
    PLL41MHz = 41,
    PLL42MHz = 42,
    PLL43MHz = 43,
    PLL44MHz = 44,
    PLL45MHz = 45,
    PLL46MHz = 46,
    PLL47MHz = 47,
    PLL48MHz = 48
} PLLFREQ_Type;

/**
 * @brief  TS(Temperature Sensor) reference clock selection enumerated definition
 */
typedef enum {
    SCU_TS_REFERENCE_HSI = 0x00UL,  /*!< HSI */
    SCU_TS_REFERENCE_MCLK = 0x01UL, /*!< MCLK */
    SCU_TS_REFERENCE_HSE = 0x02UL,  /*!< HSE */
    SCU_TS_REFERENCE_LSE = 0x03UL   /*!< LSE */
} SCU_TS_REFERENCE_Type;

/**
 * @brief  TS(Temperature Sensor) sensing clock selection enumerated definition
 */
typedef enum {
    SCU_TS_SESNING_LSI_TS = 0x00UL, /*!< LSI TS, Temperature sensing */
    SCU_TS_SESNING_LSI = 0x01UL,    /*!< LSI, timer function */
    SCU_TS_SESNING_HSI = 0x03UL,    /*!< HSI, timer function */
} SCU_TS_SENSING_Type;

/**
 * @brief  BISC (Built-in Self Calibration) reference clock selection enumerated definition
 */
typedef enum {
    BISC_REF_HSE,
    BISC_REF_LSE
} BISC_REF_Type;

/**
 * @brief  BISC (Built-in Self Calibration) reference clock selection enumerated definition
 */
typedef enum {
    BISC_COMP_HSI,
    BISC_COMP_REF,
} BISC_COMP_Type;

//----------------- SCU Reset Source definition -----------------
#define RST_PINRST                  (0x01UL << 6)
#define RST_CPURST                  (0x01UL << 5)
#define RST_SWRST                   (0x01UL << 4)
#define RST_WDTRST                  (0x01UL << 3)
#define RST_MCKFRST                 (0x01UL << 2)
#define RST_HSEFRST                 (0x01UL << 1)
#define RST_LVDRST                  (0x01UL << 0)


#define WAKEUP_SYSTICK              (0x01UL << 16)
#define WAKEUP_GPIOF                (0x01UL << 13)
#define WAKEUP_GPIOE                (0x01UL << 12)
#define WAKEUP_GPIOD                (0x01UL << 11)
#define WAKEUP_GPIOC                (0x01UL << 10)
#define WAKEUP_GPIOB                (0x01UL << 9)
#define WAKEUP_GPIOA                (0x01UL << 8)
#define WAKEUP_WT                   (0x01UL << 2)
#define WAKEUP_WDT                  (0x01UL << 1)
#define WAKEUP_LVD                  (0x01UL << 0)


//----------------- T1N SCU Clock Constant Definition -----------------
#define T1NCLK_MCCR1                (0x00UL)
#define T1NCLK_PCLK                 (0x01UL)

//----------------- T20 SCU Clock Constant Definition -----------------
#define T20CLK_MCCR2                (0x00UL)
#define T20CLK_PCLK                 (0x01UL)

//----------------- T30 SCU Clock Constant Definition -----------------
#define T30CLK_MCCR2                (0x00UL)
#define T30CLK_PCLK                 (0x01UL)

//--------------- Watch Timer Clock Constant Definition ---------------
#define WTCLK_MCCR3                 (0x00UL)
#define WTCLK_LSE                   (0x01UL)
#define WTCLK_WDTRC                 (0x02UL)

//------------- Watch-Dog Timer Clock Constant Definition -------------
#define WDTCLK_WDTRC                (0x00UL)
#define WDTCLK_MCCR3                (0x01UL)

//------------- LCD Clock Constant Definition -------------
#define LCDCLK_MCCR5                (0x00UL)
#define LCDCLK_LSE                  (0x01UL)
#define LCDCLK_WDTRC                (0x02UL)

//------------- SCU_NMI ENABLE / STATUS definition -------------------------------
#define SCU_NMI_ACCESSCODE          (0xA32C << SCU_NMIR_ACCESSCODE_Pos)
#define SCU_NMI_LVD_ENABLE          (1 << SCU_NMIR_LVDEN_Pos)
#define SCU_NMI_LVD_DISABLE         (0 << SCU_NMIR_LVDEN_Pos)
#define SCU_NMI_MCLKFAIL_ENABLE     (1 << SCU_NMIR_MCLKFAILEN_Pos)
#define SCU_NMI_MCLKFAIL_DIABLE     (0 << SCU_NMIR_MCLKFAILEN_Pos)
#define SCU_NMI_WDTINT_ENABLE       (1 << SCU_NMIR_WDTINTEN_Pos)
#define SCU_NMI_WDTINT_DISABLE      (0 << SCU_NMIR_WDTINTEN_Pos)
#define SCU_NMI_T30INT_ENABLE       (1 << SCU_NMIR_T30IEN_Pos)
#define SCU_NMI_T30INT_DISABLE      (0 << SCU_NMIR_T30IEN_Pos)
#define SCU_NMI_CMPINT_ENABLE       (1 << SCU_NMIR_CMPINTEN_Pos)
#define SCU_NMI_CMPINT_DIABLE       (0 << SCU_NMIR_CMPINTEN_Pos)
#define SCU_NMI_SWAPERR_ENABLE      (1 << SCU_NMIR_SWAPERRIEN_Pos)
#define SCU_NMI_SWAPERR_DISABLE     (0 << SCU_NMIR_SWAPERRIEN_Pos)

#define SCU_NMI_ACCESSCODE          (0xA32C << SCU_NMIR_ACCESSCODE_Pos)
#define SCU_NMI_LVD_STATUS          (1 << SCU_NMIR_LVDSTS_Pos)
#define SCU_NMI_MCLKFAIL_STATUS     (1 << SCU_NMIR_MCLKFAILSTS_Pos)
#define SCU_NMI_WDTINT_STATUS       (1 << SCU_NMIR_WDTINTSTS_Pos)
#define SCU_NMI_T30INT_STATUS       (1 << SCU_NMIR_T30INTSTS_Pos)
#define SCU_NMI_CMPINT_STSTUS       (1 << SCU_NMIR_CMPINTSTS_Pos)
#define SCU_NMI_SWAPERR_STATUS      (1 << SCU_NMIR_SWAPERRSTS_Pos)

//------------ SCU_SMR Constant Definition -------------
#define SCU_SMR_LSIAON_ENABLE       (1 << SCU_SMR_LSIAON_Pos)
#define SCU_SMR_LSIAON_DISABLE      (0 << SCU_SMR_LSIAON_Pos)
#define SCU_SMR_BGRAON_ENABLE       (1 << SCU_SMR_BGRAON_Pos)
#define SCU_SMR_BGRAON_DISABLE      (0 << SCU_SMR_BGRAON_Pos)
#define SCU_SMR_VDCAON_ENABLE       (1 << SCU_SMR_VDCAON_Pos)
#define SCU_SMR_VDCAON_DISABLE      (0 << SCU_SMR_VDCAON_Pos)

#define SCU_SMR_PREVMODE_RUN        (0 << SCU_SMR_PREVMODE_Pos)
#define SCU_SMR_PREVMODE_SLEEP      (1 << SCU_SMR_PREVMODE_Pos)
#define SCU_SMR_PREVMODE_DEEPSLEEP  (2 << SCU_SMR_PREVMODE_Pos)
#define SCU_SMR_PREVMODE_INIT       (3 << SCU_SMR_PREVMODE_Pos)

//------------ SCU WRITE KEY Definition -------------
#define SCU_CSCR_WTIDKY             (0xA507UL << SCU_CSCR_WTIDKY_Pos)
#define SCU_SCCR_WTIDKY             (0x570AUL << SCU_SCCR_WTIDKY_Pos)
#define SCU_RSTDBCR_WTIDKY          (0x0514UL)

#define SC_FIN_HSI                  (0x0)
#define SC_FIN_HSE                  (0x1)

/* Public Functions ----------------------------------------------------------- */
void HAL_SCU_LSE_ClockConfig(uint32_t LSE_Control);
Status HAL_SCU_LSE_ClockMonitoring(void);
void HAL_SCU_LSI_ClockConfig(uint32_t LSI_Control);
void HAL_SCU_HSI_ClockConfig(uint32_t HSI_Control);
void HAL_SCU_HSE_ClockConfig(uint32_t HSE_Control);
Status HAL_SCU_HSE_ClockMonitoring(void);
Status HAL_SCU_MCLK_ClockMonitoring(void);  // Check for MCLK monitoring

void HAL_SCU_SystemClockChange(uint32_t SystemClock);
void HAL_SCU_SystemClockFinClock(uint32_t sysclkcon);
void HAL_SCU_ClockOutput(uint8_t divval, FunctionalState endis);

Status HAL_SCU_PLL_ClockConfig(FunctionalState pllsetstate, uint8_t selbypass, uint8_t selfin,  uint8_t PREDIV, uint8_t POSTDIV1, uint8_t POSTDIV2, uint8_t OUTDIV);
int32_t HAL_SCU_SetPLLFreq(PLLINCLK_Type pllInClk, PLLFREQ_Type setPllFreq);
Status HAL_SCU_SetSystemClock(SYSCLK_Type clksrc, SYSCLK_DIV_Type div);

void HAL_SCU_Timer1n_ClockConfig(uint32_t t1nclk);
void HAL_SCU_Timer20_ClockConfig(uint32_t t20clk);
void HAL_SCU_Timer30_ClockConfig(uint32_t t30clk);
void HAL_SCU_WT_ClockConfig(uint32_t wtclk);
void HAL_SCU_WDT_ClockConfig(uint32_t wdtclk);
void HAL_SCU_LCD_ClockConfig(uint32_t Lcdclk);
void HAL_SCU_TS_ClockConfig(FunctionalState LSI_TS, SCU_TS_REFERENCE_Type ReferenceClock, SCU_TS_SENSING_Type SensingClock);

void HAL_SCU_MiscClockConfig(uint8_t mccrnum, uint8_t type, uint8_t clksrc, uint8_t clkdiv);

uint32_t HAL_SCU_LVI_GetLviFlag(void);
void HAL_SCU_LVI_ClrLviFlag(void);

void HAL_SCU_WakeUpSRCCmd(uint32_t WakeUpSrc, FunctionalState NewState);
uint32_t HAL_SCU_GetWakeUpSRCStatus(void);
void HAL_SCU_ClearWakeUpSRC(uint32_t WakeUpStatus);

uint32_t HAL_SCU_GetNMIStatus(void);
void HAL_SCU_SetNMI(uint32_t nmisrc);

void HAL_SCU_SetResetSrc(uint32_t RstSrc, FunctionalState NewState);
uint32_t HAL_SCU_GetResetSrc(void);
void HAL_SCU_ClearResetStatus(uint32_t rststatus);

Bool HAL_SCU_GetExtModeStatus(void);
void HAL_SCU_SetResetPinDebounce(FunctionalState En, uint32_t CntVal);

uint32_t HAL_SCU_GetPreviousModeBeforeResetEvent(void);

void HAL_SCU_SetHSECurrentAndNoiseCancel(HSE_ISEL_Type hse, FunctionalState NoiseCancelSkip);
void HAL_SCU_LSE_ClockConfigCurrentAndNoiseCancel(LSE_ISEL_Type lse_i, FunctionalState NoiseCancelSkip);

FunctionalState HAL_SCU_BootCheck(void);

Status HAL_SCU_PeripheralCmd(PERI_TYPE peripheral, FunctionalState endis);
Status HAL_SCU_PeripheralStatus(PERI_TYPE peripheral);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_SCU_H_ */
/* --------------------------------- End Of File ------------------------------ */
