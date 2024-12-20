
/****************************************************************************************************//**
 * @file     A31G22x.h
 *
 * @brief    CMSIS Cortex-M0PLUS Peripheral Access Layer Header File for
 *           A31G22x from ABOV Semiconductor Co., Ltd..
 *
 * @version  V0.2
 * @date     24. January 2022
 *
 * @note     Generated with SVDConv V2.85b 
 *           from CMSIS SVD File 'A31G22x.svd' Version 0.2,
 *
 * @par      ARM Limited (ARM) is supplying this software for use with Cortex-M
 *           processor based microcontroller, but can be equally used for other
 *           suitable processor architectures. This file can be freely distributed.
 *           Modifications to this file shall be clearly marked.
 *           
 *           THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *           OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *           MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *           ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *           CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER. 
 *
 *******************************************************************************************************/


/** @addtogroup ABOV Semiconductor Co., Ltd.
  * @{
  */


/** @addtogroup A31G22x
  * @{
  */


#ifndef A31G22X_H
#define A31G22X_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum {
/* =======================================  ARM Cortex-M0+ Specific Interrupt Numbers  ======================================= */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
/* ==========================================  A31G22x Specific Interrupt Numbers  =========================================== */
  LVI_IRQn                  =   0,              /*!< 0  LVI                                                                    */
  SYSCLKFAIL_IRQn           =   1,              /*!< 1  SYSCLKFAIL                                                             */
  WDT_IRQn                  =   2,              /*!< 2  WDT                                                                    */
  GPIOAB_IRQn               =   3,              /*!< 3  GPIOAB                                                                 */
  GPIOCD_IRQn               =   4,              /*!< 4  GPIOCD                                                                 */
  GPIOE_IRQn                =   5,              /*!< 5  GPIOE                                                                  */
  GPIOF_IRQn                =   6,              /*!< 6  GPIOF                                                                  */
  TIMER10_IRQn              =   7,              /*!< 7  TIMER10                                                                */
  TIMER11_IRQn              =   8,              /*!< 8  TIMER11                                                                */
  TIMER12_IRQn              =   9,              /*!< 9  TIMER12                                                                */
  I2C0_IRQn                 =  10,              /*!< 10 I2C0                                                                   */
  USART10_IRQn              =  11,              /*!< 11 USART10                                                                */
  WT_IRQn                   =  12,              /*!< 12 WT                                                                     */
  TIMER30_IRQn              =  13,              /*!< 13 TIMER30                                                                */
  I2C1_IRQn                 =  14,              /*!< 14 I2C1                                                                   */
  TIMER20_IRQn              =  15,              /*!< 15 TIMER20                                                                */
  TIMER21_IRQn              =  16,              /*!< 16 TIMER21                                                                */
  USART11_IRQn              =  17,              /*!< 17 USART11                                                                */
  ADC_IRQn                  =  18,              /*!< 18 ADC                                                                    */
  UART0_IRQn                =  19,              /*!< 19 UART0                                                                  */
  UART1_IRQn                =  20,              /*!< 20 UART1                                                                  */
  TIMER13_IRQn              =  21,              /*!< 21 TIMER13                                                                */
  TIMER14_IRQn              =  22,              /*!< 22 TIMER14                                                                */
  TIMER15_IRQn              =  23,              /*!< 23 TIMER15                                                                */
  TIMER16_IRQn              =  24,              /*!< 24 TIMER16                                                                */
  I2C2_SPI20_IRQn           =  25,              /*!< 25 I2C2_SPI20                                                             */
  USART12_13_SPI21_IRQn     =  26,              /*!< 26 USART12_13_SPI21                                                       */
  DAC_IRQn                  =  27,              /*!< 27 DAC                                                                    */
  TEMP_SENSOR_IRQn          =  28,              /*!< 28 TEMP_SENSOR                                                            */
  CMP_CRC_IRQn              =  31               /*!< 31 CMP_CRC                                                                */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M0+ Processor and Core Peripherals  =========================== */
#define __CM0PLUS_REV                 0x0001U   /*!< CM0PLUS Core Revision                                                     */
#define __NVIC_PRIO_BITS               2        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __VTOR_PRESENT                 1        /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
#define __MPU_PRESENT                  0        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  0        /*!< FPU present or not                                                        */


/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals                             */
#include "system_A31G22x.h"                     /*!< A31G22x System                                                            */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
  #define __IOM  __IO
#endif


/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           SCUCC                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief SYSTEM CONTROL UNIT CHIP CONFIGURATION (SCUCC)
  */

typedef struct {                                /*!< (@ 0x4000F000) SCUCC Structure                                            */
  __IM  uint32_t  VENDORID;                     /*!< (@ 0x00000000) Vendor Identification Register                             */
  __IM  uint32_t  CHIPID;                       /*!< (@ 0x00000004) Chip Identification Register                               */
  __IM  uint32_t  REVNR;                        /*!< (@ 0x00000008) Revision Number Register                                   */
} SCUCC_Type;                                   /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                            SCU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SYSTEM CONTROL UNIT (SCU)
  */

typedef struct {                                /*!< (@ 0x40000000) SCU Structure                                              */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  SMR;                          /*!< (@ 0x00000004) System Mode Register                                       */
  __IOM uint32_t  SCR;                          /*!< (@ 0x00000008) System Control Register                                    */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  WUER;                         /*!< (@ 0x00000010) Wake up source enable register                             */
  __IOM uint32_t  WUSR;                         /*!< (@ 0x00000014) Wake up source status register                             */
  __IOM uint32_t  RSER;                         /*!< (@ 0x00000018) Reset source enable register                               */
  __IOM uint32_t  RSSR;                         /*!< (@ 0x0000001C) Reset source status register                               */
  __IOM uint32_t  PRER1;                        /*!< (@ 0x00000020) Peripheral reset enable register 1                         */
  __IOM uint32_t  PRER2;                        /*!< (@ 0x00000024) Peripheral reset enable register 2                         */
  __IOM uint32_t  PER1;                         /*!< (@ 0x00000028) Peripheral enable register 1                               */
  __IOM uint32_t  PER2;                         /*!< (@ 0x0000002C) Peripheral enable register 2                               */
  __IOM uint32_t  PCER1;                        /*!< (@ 0x00000030) Peripheral clock enable register 1                         */
  __IOM uint32_t  PCER2;                        /*!< (@ 0x00000034) Peripheral clock enable register 2                         */
  __IOM uint32_t  PPCLKSR;                      /*!< (@ 0x00000038) Peripheral clock selection register                        */
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  CSCR;                         /*!< (@ 0x00000040) Clock Source Control register                              */
  __IOM uint32_t  SCCR;                         /*!< (@ 0x00000044) System Clock Control register                              */
  __IOM uint32_t  CMR;                          /*!< (@ 0x00000048) Clock Monitoring register                                  */
  __IOM uint32_t  NMIR;                         /*!< (@ 0x0000004C) NMI control register                                       */
  __IOM uint32_t  COR;                          /*!< (@ 0x00000050) Clock Output Control register                              */
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  PLLCON;                       /*!< (@ 0x00000060) PLL Control register                                       */
  __IOM uint32_t  VDCCON;                       /*!< (@ 0x00000064) VDC Control register                                       */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  LSICON;                       /*!< (@ 0x0000006C) LSI Control Register                                       */
  __IM  uint32_t  RESERVED5[4];
  __IOM uint32_t  EOSCR;                        /*!< (@ 0x00000080) External Oscillator control register                       */
  __IOM uint32_t  EMODR;                        /*!< (@ 0x00000084) External mode pin read register                            */
  __IOM uint32_t  RSTDBCR;                      /*!< (@ 0x00000088) Pin Reset Debounce Control Register                        */
  __IM  uint32_t  RESERVED6;
  __IOM uint32_t  MCCR1;                        /*!< (@ 0x00000090) Miscellaneous Clock Control Register 1                     */
  __IOM uint32_t  MCCR2;                        /*!< (@ 0x00000094) Miscellaneous Clock Control Register 2                     */
  __IOM uint32_t  MCCR3;                        /*!< (@ 0x00000098) Miscellaneous Clock Control Register 3                     */
  __IOM uint32_t  MCCR4;                        /*!< (@ 0x0000009C) Miscellaneous Clock Control Register 4                     */
  __IOM uint32_t  MCCR5;                        /*!< (@ 0x000000A0) Miscellaneous Clock Control Register 5                     */
  __IOM uint32_t  MCCR6;                        /*!< (@ 0x000000A4) Miscellaneous Clock Control Register 6                     */
  __IOM uint32_t  MCCR7;                        /*!< (@ 0x000000A8) Miscellaneous Clock Control Register 7                     */
} SCU_Type;                                     /*!< Size = 172 (0xac)                                                         */



/* =========================================================================================================================== */
/* ================                                           SCULV                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Low Voltage Detector Indicator and Reset moudle (SCULV)
  */

typedef struct {                                /*!< (@ 0x40005100) SCULV Structure                                            */
  __IOM uint32_t  LVICR;                        /*!< (@ 0x00000000) Low Voltage Indicator Control Register                     */
  __IOM uint32_t  LVRCR;                        /*!< (@ 0x00000004) Low Voltage Reset Control Register                         */
  __IOM uint32_t  LVRCNFIG;                     /*!< (@ 0x00000008) Configuration for Low Voltage Reset                        */
} SCULV_Type;                                   /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                            PA                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief GENERAL PORT (PA)
  */

typedef struct {                                /*!< (@ 0x40001000) PA Structure                                               */
  __IOM uint32_t  MOD;                          /*!< (@ 0x00000000) Port n Mode Register                                       */
  __IOM uint32_t  TYP;                          /*!< (@ 0x00000004) Port n Output Type Selection Register                      */
  __IOM uint32_t  AFSR1;                        /*!< (@ 0x00000008) Port n Alternative Function Selection Register
                                                                    1                                                          */
  __IOM uint32_t  AFSR2;                        /*!< (@ 0x0000000C) Port n Alternative Function Selection Register
                                                                    2                                                          */
  __IOM uint32_t  PUPD;                         /*!< (@ 0x00000010) Port n Pull-up/down Resistor Selection Register            */
  __IM  uint32_t  INDR;                         /*!< (@ 0x00000014) Port n Input Data Register                                 */
  __IOM uint32_t  OUTDR;                        /*!< (@ 0x00000018) Port n Output Data Register                                */
  __OM  uint32_t  BSR;                          /*!< (@ 0x0000001C) Port n Output Bit Set Register                             */
  __OM  uint32_t  BCR;                          /*!< (@ 0x00000020) Port n Output Bit Clear Register                           */
  __IOM uint32_t  OUTDMSK;                      /*!< (@ 0x00000024) Port n Output Data Mask Register                           */
  __IOM uint32_t  DBCR;                         /*!< (@ 0x00000028) Port n Debounce Control Register                           */
  __IOM uint32_t  IER;                          /*!< (@ 0x0000002C) Port n interrupt enable register                           */
  __IOM uint32_t  ISR;                          /*!< (@ 0x00000030) Port n interrupt status register                           */
  __IOM uint32_t  ICR;                          /*!< (@ 0x00000034) Port n interrupt control register                          */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  STR;                          /*!< (@ 0x00000040) Port n Strength Configuration Register
                                                                    This function is only valid for PB[2:0]
                                                                    and PC[4:2] ports.                                         */
} PORT_Type;                                    /*!< Size = 68 (0x44)                                                          */



/* =========================================================================================================================== */
/* ================                                            PF                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief GENERAL PORT (PF)
  */

typedef struct {                                /*!< (@ 0x40001500) PF Structure                                               */
  __IOM uint32_t  MOD;                          /*!< (@ 0x00000000) Port n Mode Register                                       */
  __IOM uint32_t  TYP;                          /*!< (@ 0x00000004) Port n Output Type Selection Register                      */
  __IOM uint32_t  AFSR1;                        /*!< (@ 0x00000008) Port n Alternative Function Selection Register
                                                                    1                                                          */
  __IOM uint32_t  AFSR2;                        /*!< (@ 0x0000000C) Port n Alternative Function Selection Register
                                                                    2                                                          */
  __IOM uint32_t  PUPD;                         /*!< (@ 0x00000010) Port n Pull-up/down Resistor Selection Register            */
  __IM  uint32_t  INDR;                         /*!< (@ 0x00000014) Port n Input Data Register                                 */
  __IOM uint32_t  OUTDR;                        /*!< (@ 0x00000018) Port n Output Data Register                                */
  __OM  uint32_t  BSR;                          /*!< (@ 0x0000001C) Port n Output Bit Set Register                             */
  __OM  uint32_t  BCR;                          /*!< (@ 0x00000020) Port n Output Bit Clear Register                           */
  __IOM uint32_t  OUTDMSK;                      /*!< (@ 0x00000024) Port n Output Data Mask Register                           */
  __IOM uint32_t  DBCR;                         /*!< (@ 0x00000028) Port n Debounce Control Register                           */
  __IOM uint32_t  IER;                          /*!< (@ 0x0000002C) Port n interrupt enable register                           */
  __IOM uint32_t  ISR;                          /*!< (@ 0x00000030) Port n interrupt status register                           */
  __IOM uint32_t  ICR;                          /*!< (@ 0x00000034) Port n interrupt control register                          */
  __IOM uint32_t  PLSR;                         /*!< (@ 0x00000038) PORT F level select register                               */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  STR;                          /*!< (@ 0x00000040) Port n Strength Configuration Register
                                                                    This function is only valid for PB[2:0]
                                                                    and PC[4:2] ports.                                         */
} PORTF_Type;                                   /*!< Size = 68 (0x44)                                                          */



/* =========================================================================================================================== */
/* ================                                           PCU1                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PORT CONTROL UNIT 1 (PCU1)
  */

typedef struct {                                /*!< (@ 0x40001544) PCU1 Structure                                             */
  __IOM uint32_t  SPI2PMR;                      /*!< (@ 0x00000000) Port SPI2n Pin Re-Map Register                             */
} PCU1_Type;                                    /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                           PCU2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PORT CONTROL UNIT 2 (PCU2)
  */

typedef struct {                                /*!< (@ 0x40001F00) PCU2 Structure                                             */
  __IOM uint32_t  ISEGPEN;                      /*!< (@ 0x00000000) Port LED ISEG Port Enable Register                         */
  __IOM uint32_t  ISEGR;                        /*!< (@ 0x00000004) Port LED ISEG Register                                     */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  ISEGIR;                       /*!< (@ 0x00000010) Port LED ISEG Inversion Register                           */
  __IM  uint32_t  RESERVED1[55];
  __OM  uint32_t  PORTEN;                       /*!< (@ 0x000000F0) Port Access Enable Register                                */
} PCU2_Type;                                    /*!< Size = 244 (0xf4)                                                         */



/* =========================================================================================================================== */
/* ================                                           CFMC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief CODE FLASH MEMORY CONTROLLER (CFMC)
  */

typedef struct {                                /*!< (@ 0x40000100) CFMC Structure                                             */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  MR;                           /*!< (@ 0x00000004) Code Flash Memory Mode Register                            */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000008) Code Flash Memory Control Register                         */
  __IOM uint32_t  AR;                           /*!< (@ 0x0000000C) Code Flash Memory Address Register                         */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000010) Code Flash Memory Data Register                            */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  BUSY;                         /*!< (@ 0x00000018) Code Flash Memory Write Busy Status Register               */
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  CRCCCITT;                     /*!< (@ 0x00000020) Code Flash Memory CRC-CCITT Check Register                 */
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  CFG;                          /*!< (@ 0x00000030) Code Flash Memory Config Register                          */
  __IOM uint32_t  WPROT;                        /*!< (@ 0x00000034) Flash Memory Write Protection Register                     */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  RPROT;                        /*!< (@ 0x0000003C) Code Flash Memory Read Protection Register                 */
  __OM  uint32_t  PWIN;                         /*!< (@ 0x00000040) Code Flash Memory Password Input Register                  */
  __OM  uint32_t  PWPRST;                       /*!< (@ 0x00000044) Code Flash Memory Password Preset Register                 */
  __IOM uint32_t  BCR;                          /*!< (@ 0x00000048) Code Flash Memory Bank Control Register                    */
  __IOM uint32_t  BSR;                          /*!< (@ 0x0000004C) Code Flash Memory Bank Status Register                     */
  __IOM uint32_t  ABWPROT;                      /*!< (@ 0x00000050) Code Flash Memory Active Bootloader Area Write
                                                                    Protection Register                                        */
  __IOM uint32_t  NBWPROT;                      /*!< (@ 0x00000054) Code Flash Memory Non-active Bootloader Area
                                                                    Write Protection Register                                  */
} CFMC_Type;                                    /*!< Size = 88 (0x58)                                                          */



/* =========================================================================================================================== */
/* ================                                           DFMC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief DATA FLASH MEMORY CONTROLLER (DFMC)
  */

typedef struct {                                /*!< (@ 0x40000200) DFMC Structure                                             */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  MR;                           /*!< (@ 0x00000004) Data Flash Memory Mode Register                            */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000008) Data Flash Memory Control Register                         */
  __IOM uint32_t  AR;                           /*!< (@ 0x0000000C) Data Flash Memory Address Register                         */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000010) Data Flash Memory Data Register                            */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  BUSY;                         /*!< (@ 0x00000018) Data Flash Memory Write Busy Status Register               */
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  CRCCCITT;                     /*!< (@ 0x00000020) Data Flash Memory CRC-CCITT Check Register                 */
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  CFG;                          /*!< (@ 0x00000030) Data Flash Memory Config Register                          */
  __IOM uint32_t  WPROT;                        /*!< (@ 0x00000034) Data Flash Memory Write Protection Register                */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  RPROT;                        /*!< (@ 0x0000003C) Data Flash Memory Read Protection Register                 */
  __OM  uint32_t  PWIN;                         /*!< (@ 0x00000040) Data Flash Memory Password Input Register                  */
  __OM  uint32_t  PWPRST;                       /*!< (@ 0x00000044) Data Flash Memory Password Preset Register                 */
} DFMC_Type;                                    /*!< Size = 72 (0x48)                                                          */



/* =========================================================================================================================== */
/* ================                                           DMAC0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief DIRECT MEMORY ACCESS CONTROLLER (DMAC0)
  */

typedef struct {                                /*!< (@ 0x40000400) DMAC0 Structure                                            */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) DMA Channel n Control Register                             */
  __IOM uint32_t  SR;                           /*!< (@ 0x00000004) DMA Channel n Status Register                              */
  __IOM uint32_t  PAR;                          /*!< (@ 0x00000008) DMA Channel n Peripheral Address                           */
  __IOM uint32_t  MAR;                          /*!< (@ 0x0000000C) DMA Channel n Memory Address                               */
} DMAC_Type;                                    /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                            WDT                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief WATCH-DOG TIMER (WDT)
  */

typedef struct {                                /*!< (@ 0x40001A00) WDT Structure                                              */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Watch-dog Timer Control Register                           */
  __IOM uint32_t  SR;                           /*!< (@ 0x00000004) Watch-dog Timer Status Register                            */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000008) Watch-dog Timer Data Register                              */
  __IM  uint32_t  CNT;                          /*!< (@ 0x0000000C) Watch-dog Timer Counter Register                           */
  __IOM uint32_t  WINDR;                        /*!< (@ 0x00000010) Watch-dog Timer Window Data Register (Note: Once
                                                                    any value is written to this window data
                                                                    register, the register can't be changed
                                                                    until a system reset.)                                     */
  __OM  uint32_t  CNTR;                         /*!< (@ 0x00000014) Watch-dog Timer Counter Reload Register                    */
} WDT_Type;                                     /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                            WT                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief WATCH TIMER (WT)
  */

typedef struct {                                /*!< (@ 0x40002000) WT Structure                                               */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Watch Timer Control Register                               */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000004) Watch Timer Data Register                                  */
  __IM  uint32_t  CNT;                          /*!< (@ 0x00000008) Watch Timer Counter Register                               */
} WT_Type;                                      /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                          TIMER10                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief 16-BIT TIMER1n (TIMER10)
  */

typedef struct {                                /*!< (@ 0x40002100) TIMER10 Structure                                          */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Timer/Counter n Control Register                           */
  __IOM uint32_t  ADR;                          /*!< (@ 0x00000004) Timer/Counter n A Data Register                            */
  __IOM uint32_t  BDR;                          /*!< (@ 0x00000008) Timer/Counter n B Data Register                            */
  __IM  uint32_t  CAPDR;                        /*!< (@ 0x0000000C) Timer/Counter n Capture Data Register                      */
  __IOM uint32_t  PREDR;                        /*!< (@ 0x00000010) Timer/Counter n Prescaler Data Register                    */
  __IM  uint32_t  CNT;                          /*!< (@ 0x00000014) Timer/Counter n Counter Register                           */
} TIMER1n_Type;                                 /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                          TIMER20                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief 32-BIT TIMER2n (TIMER20)
  */

typedef struct {                                /*!< (@ 0x40002500) TIMER20 Structure                                          */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Timer/Counter n Control Register                           */
  __IOM uint32_t  ADR;                          /*!< (@ 0x00000004) Timer/Counter n A Data Register                            */
  __IOM uint32_t  BDR;                          /*!< (@ 0x00000008) Timer/Counter n B Data Register                            */
  __IM  uint32_t  CAPDR;                        /*!< (@ 0x0000000C) Timer/Counter n Capture Data Register                      */
  __IOM uint32_t  PREDR;                        /*!< (@ 0x00000010) Timer/Counter n Prescaler Data Register                    */
  __IM  uint32_t  CNT;                          /*!< (@ 0x00000014) Timer/Counter n Counter Register                           */
} TIMER2n_Type;                                 /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                          TIMER30                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER COUNTER30 (TIMER30)
  */

typedef struct {                                /*!< (@ 0x40002400) TIMER30 Structure                                          */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Timer/Counter 30 Control Register                          */
  __IOM uint32_t  PDR;                          /*!< (@ 0x00000004) Timer/Counter 30 Period Data Register                      */
  __IOM uint32_t  ADR;                          /*!< (@ 0x00000008) Timer/Counter 30 A Data Register                           */
  __IOM uint32_t  BDR;                          /*!< (@ 0x0000000C) Timer/Counter 30 B Data Register                           */
  __IOM uint32_t  CDR;                          /*!< (@ 0x00000010) Timer/Counter 30 C Data Register                           */
  __IM  uint32_t  CAPDR;                        /*!< (@ 0x00000014) Timer/Counter 30 Capture Data Register                     */
  __IOM uint32_t  PREDR;                        /*!< (@ 0x00000018) Timer/Counter 30 Prescaler Data Register                   */
  __IM  uint32_t  CNT;                          /*!< (@ 0x0000001C) Timer/Counter 30 Counter Register                          */
  __IOM uint32_t  OUTCR;                        /*!< (@ 0x00000020) Timer/Counter 30 Output Control Register                   */
  __IOM uint32_t  DLY;                          /*!< (@ 0x00000024) Timer/Counter 30 PWM Output Delay Data Register            */
  __IOM uint32_t  INTCR;                        /*!< (@ 0x00000028) Timer/Counter 30 Interrupt Control Register                */
  __IOM uint32_t  INTFLAG;                      /*!< (@ 0x0000002C) Timer/Counter 30 Interrupt Flag Register                   */
  __IOM uint32_t  HIZCR;                        /*!< (@ 0x00000030) Timer/Counter 30 High-Impedance Control Register           */
  __IOM uint32_t  ADTCR;                        /*!< (@ 0x00000034) Timer/Counter 30 A/DC Trigger Control Register             */
  __IOM uint32_t  ADTDR;                        /*!< (@ 0x00000038) Timer/Counter 30 A/DC Trigger Generator Data
                                                                    Register                                                   */
} TIMER3n_Type;                                 /*!< Size = 60 (0x3c)                                                          */



/* =========================================================================================================================== */
/* ================                                          USART10                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief UNIVERSAL SYNCHRONOUS/ASYNCHRONOUS RECEIVER/TRANSMITTER (USART10)
  */

typedef struct {                                /*!< (@ 0x40003800) USART10 Structure                                          */
  __IOM uint32_t  CR1;                          /*!< (@ 0x00000000) USARTn Control Register 1                                  */
  __IOM uint32_t  CR2;                          /*!< (@ 0x00000004) USARTn Control Register 2                                  */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  ST;                           /*!< (@ 0x0000000C) USARTn Status Register                                     */
  __IOM uint32_t  BDR;                          /*!< (@ 0x00000010) USARTn Baud Rate Generation Register                       */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000014) USARTn Data Register                                       */
  __IOM uint32_t  BFR;                          /*!< (@ 0x00000018) USARTn Baud-Rate Fraction Count Register                   */
  __IOM uint32_t  RTO;                          /*!< (@ 0x0000001C) USARTn Receive Time Out Register                           */
} USART_Type;                                   /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                           UART0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief UNIVERSAL ASYNCHRONOUS RECEIVER/TRANSMITTER (UART0)
  */

typedef struct {                                /*!< (@ 0x40004000) UART0 Structure                                            */
  
  union {
    __IM  uint32_t RBR;                         /*!< (@ 0x00000000) UARTn Receive Buffer Register                              */
    __OM  uint32_t THR;                         /*!< (@ 0x00000000) UARTn Transmit Data Hold Register                          */
  };
  __IOM uint32_t  IER;                          /*!< (@ 0x00000004) UARTn Interrupt Enable Register                            */
  __IOM uint32_t  IIR;                          /*!< (@ 0x00000008) UARTn Interrupt ID Register                                */
  __IOM uint32_t  LCR;                          /*!< (@ 0x0000000C) UARTn Line Control Register                                */
  __IOM uint32_t  DCR;                          /*!< (@ 0x00000010) UARTn Data Control Register                                */
  __IOM uint32_t  LSR;                          /*!< (@ 0x00000014) UARTn Line Status Register                                 */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  BDR;                          /*!< (@ 0x00000020) UARTn Baud rate Divisor Latch Register                     */
  __IOM uint32_t  BFR;                          /*!< (@ 0x00000024) UARTn Baud rate Fraction Counter Register                  */
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  IDTR;                         /*!< (@ 0x00000030) UARTn Inter-frame Delay Time Register                      */
} UART_Type;                                    /*!< Size = 52 (0x34)                                                          */



/* =========================================================================================================================== */
/* ================                                           SPI20                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief SERIAL PERIPHERAL INTERFACE (SPI20)
  */

typedef struct {                                /*!< (@ 0x40004C00) SPI20 Structure                                            */
  
  union {
    __OM  uint32_t TDR;                         /*!< (@ 0x00000000) SPI n Transmit Data Register                               */
    __IM  uint32_t RDR;                         /*!< (@ 0x00000000) SPI n Received Data Register                               */
  };
  __IOM uint32_t  CR;                           /*!< (@ 0x00000004) SPI n Control Register                                     */
  __IOM uint32_t  SR;                           /*!< (@ 0x00000008) SPI n Status Register                                      */
  __IOM uint32_t  BR;                           /*!< (@ 0x0000000C) SPI n Baud Rate Register                                   */
  __IOM uint32_t  EN;                           /*!< (@ 0x00000010) SPI n Enable Register                                      */
  __IOM uint32_t  LR;                           /*!< (@ 0x00000014) SPI n Delay Length Register                                */
} SPI_Type;                                     /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           I2C0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief INTER-INTEGRATED CIRCUIT (I2C0)
  */

typedef struct {                                /*!< (@ 0x40004800) I2C0 Structure                                             */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) I2C n Control Register                                     */
  __IOM uint32_t  ST;                           /*!< (@ 0x00000004) I2C n Status Register                                      */
  __IOM uint32_t  SAR1;                         /*!< (@ 0x00000008) I2C n Slave Address Register 1                             */
  __IOM uint32_t  SAR2;                         /*!< (@ 0x0000000C) I2C n Slave Address Register 2                             */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000010) I2C n Data Register                                        */
  __IOM uint32_t  SDHR;                         /*!< (@ 0x00000014) I2C n SDA Hold Time Register                               */
  __IOM uint32_t  SCLR;                         /*!< (@ 0x00000018) I2C n SCL Low Period Register                              */
  __IOM uint32_t  SCHR;                         /*!< (@ 0x0000001C) I2C n SCL High Period Register                             */
  __IOM uint32_t  SLTCR;                        /*!< (@ 0x00000020) I2C n SCL Low Timeout Control Register                     */
  __IOM uint32_t  SLTPDR;                       /*!< (@ 0x00000024) I2C n SCL Low Timeout Control Register                     */
  __IOM uint32_t  MBCR;                         /*!< (@ 0x00000028) I2C n Manual Bus Control Register                          */
} I2C_Type;                                     /*!< Size = 44 (0x2c)                                                          */



/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 12-BIT A/D CONVERTER (ADC)
  */

typedef struct {                                /*!< (@ 0x40003100) ADC Structure                                              */
  __IOM uint32_t  MR;                           /*!< (@ 0x00000000) ADC Mode Register                                          */
  __IOM uint32_t  CSCR;                         /*!< (@ 0x00000004) ADC Current Sequence_Channel Register                      */
  __IOM uint32_t  CCR;                          /*!< (@ 0x00000008) ADC Clock Control Register                                 */
  __IOM uint32_t  TRG;                          /*!< (@ 0x0000000C) ADC Trigger Selection Register                             */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  SCSR1;                        /*!< (@ 0x00000018) ADC Channel Selection Register 1                           */
  __IOM uint32_t  SCSR2;                        /*!< (@ 0x0000001C) ADC Channel Selection Register 2                           */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000020) ADC Control Register                                       */
  __IOM uint32_t  SR;                           /*!< (@ 0x00000024) ADC Status Register                                        */
  __IOM uint32_t  IER;                          /*!< (@ 0x00000028) ADC Interrupt Enable Register                              */
  __IM  uint32_t  DDR;                          /*!< (@ 0x0000002C) ADC DMA Data Register                                      */
  __IOM uint32_t  DR0;                          /*!< (@ 0x00000030) ADC Sequence Data Register0                                */
  __IOM uint32_t  DR1;                          /*!< (@ 0x00000034) ADC Sequence Data Register1                                */
  __IOM uint32_t  DR2;                          /*!< (@ 0x00000038) ADC Sequence Data Register2                                */
  __IOM uint32_t  DR3;                          /*!< (@ 0x0000003C) ADC Sequence Data Register3                                */
  __IOM uint32_t  DR4;                          /*!< (@ 0x00000040) ADC Sequence Data Register4                                */
  __IOM uint32_t  DR5;                          /*!< (@ 0x00000044) ADC Sequence Data Register5                                */
  __IOM uint32_t  DR6;                          /*!< (@ 0x00000048) ADC Sequence Data Register6                                */
  __IOM uint32_t  DR7;                          /*!< (@ 0x0000004C) ADC Sequence Data Register7                                */
  __IM  uint32_t  RESERVED1[8];
  __IOM uint32_t  CMPR;                         /*!< (@ 0x00000070) ADC Channel Compare Register                               */
  __IOM uint32_t  BCR;                          /*!< (@ 0x00000074) ADC Buffer Control Register                                */
} ADC_Type;                                     /*!< Size = 120 (0x78)                                                         */



/* =========================================================================================================================== */
/* ================                                            DAC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 12-BIT D/A CONVERTER (DAC)
  */

typedef struct {                                /*!< (@ 0x40003450) DAC Structure                                              */
  __IOM uint32_t  DR;                           /*!< (@ 0x00000000) D/A Converter Data Register                                */
  __IM  uint32_t  BR;                           /*!< (@ 0x00000004) D/A Converter Buffer Register                              */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000008) D/A Converter Control Register                             */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  ICR;                          /*!< (@ 0x00000014) D/A Converter Interrupt Control Register                   */
} DAC_Type;                                     /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                            CMP                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief COMPARATOR (CMP)
  */

typedef struct {                                /*!< (@ 0x40003420) CMP Structure                                              */
  __IOM uint32_t  CMP0CR;                       /*!< (@ 0x00000000) Comparator 0 Control Register                              */
  __IOM uint32_t  CMP1CR;                       /*!< (@ 0x00000004) Comparator 1 Control Register                              */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  DBNC;                         /*!< (@ 0x00000010) Comparator Debounce Register                               */
  __IOM uint32_t  ICON;                         /*!< (@ 0x00000014) Comparator Interrupt Control Register                      */
  __IOM uint32_t  IEN;                          /*!< (@ 0x00000018) Comparator Interrupt Enable Register                       */
  __IM  uint32_t  IST;                          /*!< (@ 0x0000001C) Comparator Interrupt Status Register                       */
  __IOM uint32_t  ICLR;                         /*!< (@ 0x00000020) Comparator Interrupt Clear Register                        */
} CMP_Type;                                     /*!< Size = 36 (0x24)                                                          */



/* =========================================================================================================================== */
/* ================                                            LCD                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief LCD DRIVER (LCD)
  */

typedef struct {                                /*!< (@ 0x40005000) LCD Structure                                              */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) LCD Driver Control Register                                */
  __IOM uint32_t  BCCR;                         /*!< (@ 0x00000004) LCD Automatic Bias and Contrast Control Register           */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  BSSR;                         /*!< (@ 0x0000000C) LCD Bias Source Selection Register                         */
  __IOM uint8_t   LCDDR0;                       /*!< (@ 0x00000010) LCD Display Data Register 0                                */
  __IOM uint8_t   LCDDR1;                       /*!< (@ 0x00000011) LCD Display Data Register 1                                */
  __IOM uint8_t   LCDDR2;                       /*!< (@ 0x00000012) LCD Display Data Register 2                                */
  __IOM uint8_t   LCDDR3;                       /*!< (@ 0x00000013) LCD Display Data Register 3                                */
  __IOM uint8_t   LCDDR4;                       /*!< (@ 0x00000014) LCD Display Data Register 4                                */
  __IOM uint8_t   LCDDR5;                       /*!< (@ 0x00000015) LCD Display Data Register 5                                */
  __IOM uint8_t   LCDDR6;                       /*!< (@ 0x00000016) LCD Display Data Register 6                                */
  __IOM uint8_t   LCDDR7;                       /*!< (@ 0x00000017) LCD Display Data Register 7                                */
  __IOM uint8_t   LCDDR8;                       /*!< (@ 0x00000018) LCD Display Data Register 8                                */
  __IOM uint8_t   LCDDR9;                       /*!< (@ 0x00000019) LCD Display Data Register 9                                */
  __IOM uint8_t   LCDDR10;                      /*!< (@ 0x0000001A) LCD Display Data Register 10                               */
  __IOM uint8_t   LCDDR11;                      /*!< (@ 0x0000001B) LCD Display Data Register 11                               */
  __IOM uint8_t   LCDDR12;                      /*!< (@ 0x0000001C) LCD Display Data Register 12                               */
  __IOM uint8_t   LCDDR13;                      /*!< (@ 0x0000001D) LCD Display Data Register 13                               */
  __IOM uint8_t   LCDDR14;                      /*!< (@ 0x0000001E) LCD Display Data Register 14                               */
  __IOM uint8_t   LCDDR15;                      /*!< (@ 0x0000001F) LCD Display Data Register 15                               */
  __IOM uint8_t   LCDDR16;                      /*!< (@ 0x00000020) LCD Display Data Register 16                               */
  __IOM uint8_t   LCDDR17;                      /*!< (@ 0x00000021) LCD Display Data Register 17                               */
  __IOM uint8_t   LCDDR18;                      /*!< (@ 0x00000022) LCD Display Data Register 18                               */
  __IOM uint8_t   LCDDR19;                      /*!< (@ 0x00000023) LCD Display Data Register 19                               */
  __IOM uint8_t   LCDDR20;                      /*!< (@ 0x00000024) LCD Display Data Register 20                               */
  __IOM uint8_t   LCDDR21;                      /*!< (@ 0x00000025) LCD Display Data Register 21                               */
  __IOM uint8_t   LCDDR22;                      /*!< (@ 0x00000026) LCD Display Data Register 22                               */
  __IOM uint8_t   LCDDR23;                      /*!< (@ 0x00000027) LCD Display Data Register 23                               */
  __IOM uint8_t   LCDDR24;                      /*!< (@ 0x00000028) LCD Display Data Register 24                               */
  __IOM uint8_t   LCDDR25;                      /*!< (@ 0x00000029) LCD Display Data Register 25                               */
  __IOM uint8_t   LCDDR26;                      /*!< (@ 0x0000002A) LCD Display Data Register 26                               */
  __IOM uint8_t   LCDDR27;                      /*!< (@ 0x0000002B) LCD Display Data Register 27                               */
  __IOM uint8_t   LCDDR28;                      /*!< (@ 0x0000002C) LCD Display Data Register 28                               */
  __IOM uint8_t   LCDDR29;                      /*!< (@ 0x0000002D) LCD Display Data Register 29                               */
  __IOM uint8_t   LCDDR30;                      /*!< (@ 0x0000002E) LCD Display Data Register 30                               */
  __IOM uint8_t   LCDDR31;                      /*!< (@ 0x0000002F) LCD Display Data Register 31                               */
  __IOM uint8_t   LCDDR32;                      /*!< (@ 0x00000030) LCD Display Data Register 32                               */
  __IOM uint8_t   LCDDR33;                      /*!< (@ 0x00000031) LCD Display Data Register 33                               */
  __IOM uint8_t   LCDDR34;                      /*!< (@ 0x00000032) LCD Display Data Register 34                               */
  __IOM uint8_t   LCDDR35;                      /*!< (@ 0x00000033) LCD Display Data Register 35                               */
  __IOM uint8_t   LCDDR36;                      /*!< (@ 0x00000034) LCD Display Data Register 36                               */
  __IOM uint8_t   LCDDR37;                      /*!< (@ 0x00000035) LCD Display Data Register 37                               */
  __IOM uint8_t   LCDDR38;                      /*!< (@ 0x00000036) LCD Display Data Register 38                               */
  __IOM uint8_t   LCDDR39;                      /*!< (@ 0x00000037) LCD Display Data Register 39                               */
  __IOM uint8_t   LCDDR40;                      /*!< (@ 0x00000038) LCD Display Data Register 40                               */
  __IOM uint8_t   LCDDR41;                      /*!< (@ 0x00000039) LCD Display Data Register 41                               */
  __IOM uint8_t   LCDDR42;                      /*!< (@ 0x0000003A) LCD Display Data Register 42                               */
  __IOM uint8_t   LCDDR43;                      /*!< (@ 0x0000003B) LCD Display Data Register 43                               */
} LCD_Type;                                     /*!< Size = 60 (0x3c)                                                          */



/* =========================================================================================================================== */
/* ================                                            CRC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief CYCLIC REDUNDANCY CHECK AND CHECKSUM (CRC)
  */

typedef struct {                                /*!< (@ 0x40000300) CRC Structure                                              */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) CRC Control Register                                       */
  __IOM uint32_t  INIT;                         /*!< (@ 0x00000004) CRC Initial Data Register                                  */
  
  union {
    __IM  uint32_t ODR;                         /*!< (@ 0x00000008) CRC Output Data Register                                   */
    __OM  uint8_t IDR;                          /*!< (@ 0x00000008) CRC Input Data Register                                    */
  };
  __IOM uint32_t  SR;                           /*!< (@ 0x0000000C) CRC Status Register                                        */
} CRC_Type;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                            TS                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief TEMPERATURE SENSOR (TS)
  */

typedef struct {                                /*!< (@ 0x40006300) TS Structure                                               */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) Temperature Sensor Control Register                        */
  __IOM uint32_t  RCCNT;                        /*!< (@ 0x00000004) Temperature Sensor Reference Clock Counter Register        */
  __IM  uint32_t  SCCNT;                        /*!< (@ 0x00000008) Temperature Sensor Sensing Clock Counter Register          */
  __IOM uint32_t  SR;                           /*!< (@ 0x0000000C) Temperature Sensor Status Register                         */
} TS_Type;                                      /*!< Size = 16 (0x10)                                                          */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define SCUCC_BASE                  0x4000F000UL
#define SCU_BASE                    0x40000000UL
#define SCULV_BASE                  0x40005100UL
#define PA_BASE                     0x40001000UL
#define PB_BASE                     0x40001100UL
#define PC_BASE                     0x40001200UL
#define PD_BASE                     0x40001300UL
#define PE_BASE                     0x40001400UL
#define PF_BASE                     0x40001500UL
#define PCU1_BASE                   0x40001544UL
#define PCU2_BASE                   0x40001F00UL
#define CFMC_BASE                   0x40000100UL
#define DFMC_BASE                   0x40000200UL
#define DMAC0_BASE                  0x40000400UL
#define DMAC1_BASE                  0x40000410UL
#define DMAC2_BASE                  0x40000420UL
#define DMAC3_BASE                  0x40000430UL
#define DMAC4_BASE                  0x40000440UL
#define DMAC5_BASE                  0x40000450UL
#define DMAC6_BASE                  0x40000460UL
#define DMAC7_BASE                  0x40000470UL
#define WDT_BASE                    0x40001A00UL
#define WT_BASE                     0x40002000UL
#define TIMER10_BASE                0x40002100UL
#define TIMER11_BASE                0x40002200UL
#define TIMER12_BASE                0x40002300UL
#define TIMER13_BASE                0x40002700UL
#define TIMER14_BASE                0x40002800UL
#define TIMER15_BASE                0x40002900UL
#define TIMER16_BASE                0x40002A00UL
#define TIMER20_BASE                0x40002500UL
#define TIMER21_BASE                0x40002600UL
#define TIMER30_BASE                0x40002400UL
#define USART10_BASE                0x40003800UL
#define USART11_BASE                0x40003900UL
#define USART12_BASE                0x40003A00UL
#define USART13_BASE                0x40003B00UL
#define UART0_BASE                  0x40004000UL
#define UART1_BASE                  0x40004100UL
#define SPI20_BASE                  0x40004C00UL
#define SPI21_BASE                  0x40004D00UL
#define I2C0_BASE                   0x40004800UL
#define I2C1_BASE                   0x40004900UL
#define I2C2_BASE                   0x40004A00UL
#define ADC_BASE                    0x40003100UL
#define DAC_BASE                    0x40003450UL
#define CMP_BASE                    0x40003420UL
#define LCD_BASE                    0x40005000UL
#define CRC_BASE                    0x40000300UL
#define TS_BASE                     0x40006300UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define SCUCC                       ((SCUCC_Type*)             SCUCC_BASE)
#define SCU                         ((SCU_Type*)               SCU_BASE)
#define SCULV                       ((SCULV_Type*)             SCULV_BASE)
#define PA                          ((PORT_Type*)              PA_BASE)
#define PB                          ((PORT_Type*)              PB_BASE)
#define PC                          ((PORT_Type*)              PC_BASE)
#define PD                          ((PORT_Type*)              PD_BASE)
#define PE                          ((PORT_Type*)              PE_BASE)
#define PF                          ((PORTF_Type*)             PF_BASE)
#define PCU1                        ((PCU1_Type*)              PCU1_BASE)
#define PCU2                        ((PCU2_Type*)              PCU2_BASE)
#define CFMC                        ((CFMC_Type*)              CFMC_BASE)
#define DFMC                        ((DFMC_Type*)              DFMC_BASE)
#define DMAC0                       ((DMAC_Type*)              DMAC0_BASE)
#define DMAC1                       ((DMAC_Type*)              DMAC1_BASE)
#define DMAC2                       ((DMAC_Type*)              DMAC2_BASE)
#define DMAC3                       ((DMAC_Type*)              DMAC3_BASE)
#define DMAC4                       ((DMAC_Type*)              DMAC4_BASE)
#define DMAC5                       ((DMAC_Type*)              DMAC5_BASE)
#define DMAC6                       ((DMAC_Type*)              DMAC6_BASE)
#define DMAC7                       ((DMAC_Type*)              DMAC7_BASE)
#define WDT                         ((WDT_Type*)               WDT_BASE)
#define WT                          ((WT_Type*)                WT_BASE)
#define TIMER10                     ((TIMER1n_Type*)           TIMER10_BASE)
#define TIMER11                     ((TIMER1n_Type*)           TIMER11_BASE)
#define TIMER12                     ((TIMER1n_Type*)           TIMER12_BASE)
#define TIMER13                     ((TIMER1n_Type*)           TIMER13_BASE)
#define TIMER14                     ((TIMER1n_Type*)           TIMER14_BASE)
#define TIMER15                     ((TIMER1n_Type*)           TIMER15_BASE)
#define TIMER16                     ((TIMER1n_Type*)           TIMER16_BASE)
#define TIMER20                     ((TIMER2n_Type*)           TIMER20_BASE)
#define TIMER21                     ((TIMER2n_Type*)           TIMER21_BASE)
#define TIMER30                     ((TIMER3n_Type*)           TIMER30_BASE)
#define USART10                     ((USART_Type*)             USART10_BASE)
#define USART11                     ((USART_Type*)             USART11_BASE)
#define USART12                     ((USART_Type*)             USART12_BASE)
#define USART13                     ((USART_Type*)             USART13_BASE)
#define UART0                       ((UART_Type*)              UART0_BASE)
#define UART1                       ((UART_Type*)              UART1_BASE)
#define SPI20                       ((SPI_Type*)               SPI20_BASE)
#define SPI21                       ((SPI_Type*)               SPI21_BASE)
#define I2C0                        ((I2C_Type*)               I2C0_BASE)
#define I2C1                        ((I2C_Type*)               I2C1_BASE)
#define I2C2                        ((I2C_Type*)               I2C2_BASE)
#define ADC                         ((ADC_Type*)               ADC_BASE)
#define DAC                         ((DAC_Type*)               DAC_BASE)
#define CMP                         ((CMP_Type*)               CMP_BASE)
#define LCD                         ((LCD_Type*)               LCD_BASE)
#define CRC                         ((CRC_Type*)               CRC_BASE)
#define TS                          ((TS_Type*)                TS_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif


/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */


/** @addtogroup PosMask_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           SCUCC                                           ================ */
/* =========================================================================================================================== */

/* =======================================================  VENDORID  ======================================================== */
#define SCUCC_VENDORID_VENDID_Pos         (0UL)                     /*!< SCUCC VENDORID: VENDID (Bit 0)                        */
#define SCUCC_VENDORID_VENDID_Msk         (0xffffffffUL)            /*!< SCUCC VENDORID: VENDID (Bitfield-Mask: 0xffffffff)    */
/* ========================================================  CHIPID  ========================================================= */
#define SCUCC_CHIPID_CHIPID_Pos           (0UL)                     /*!< SCUCC CHIPID: CHIPID (Bit 0)                          */
#define SCUCC_CHIPID_CHIPID_Msk           (0xffffffffUL)            /*!< SCUCC CHIPID: CHIPID (Bitfield-Mask: 0xffffffff)      */
/* =========================================================  REVNR  ========================================================= */
#define SCUCC_REVNR_REVNO_Pos             (0UL)                     /*!< SCUCC REVNR: REVNO (Bit 0)                            */
#define SCUCC_REVNR_REVNO_Msk             (0xffUL)                  /*!< SCUCC REVNR: REVNO (Bitfield-Mask: 0xff)              */


/* =========================================================================================================================== */
/* ================                                            SCU                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  SMR  ========================================================== */
#define SCU_SMR_LSEAON_Pos                (11UL)                    /*!< SCU SMR: LSEAON (Bit 11)                              */
#define SCU_SMR_LSEAON_Msk                (0x800UL)                 /*!< SCU SMR: LSEAON (Bitfield-Mask: 0x01)                 */
#define SCU_SMR_LSIAON_Pos                (10UL)                    /*!< SCU SMR: LSIAON (Bit 10)                              */
#define SCU_SMR_LSIAON_Msk                (0x400UL)                 /*!< SCU SMR: LSIAON (Bitfield-Mask: 0x01)                 */
#define SCU_SMR_BGRAON_Pos                (9UL)                     /*!< SCU SMR: BGRAON (Bit 9)                               */
#define SCU_SMR_BGRAON_Msk                (0x200UL)                 /*!< SCU SMR: BGRAON (Bitfield-Mask: 0x01)                 */
#define SCU_SMR_VDCAON_Pos                (8UL)                     /*!< SCU SMR: VDCAON (Bit 8)                               */
#define SCU_SMR_VDCAON_Msk                (0x100UL)                 /*!< SCU SMR: VDCAON (Bitfield-Mask: 0x01)                 */
#define SCU_SMR_PREVMODE_Pos              (4UL)                     /*!< SCU SMR: PREVMODE (Bit 4)                             */
#define SCU_SMR_PREVMODE_Msk              (0x30UL)                  /*!< SCU SMR: PREVMODE (Bitfield-Mask: 0x03)               */
/* ==========================================================  SCR  ========================================================== */
#define SCU_SCR_WTIDKY_Pos                (16UL)                    /*!< SCU SCR: WTIDKY (Bit 16)                              */
#define SCU_SCR_WTIDKY_Msk                (0xffff0000UL)            /*!< SCU SCR: WTIDKY (Bitfield-Mask: 0xffff)               */
#define SCU_SCR_SWRST_Pos                 (0UL)                     /*!< SCU SCR: SWRST (Bit 0)                                */
#define SCU_SCR_SWRST_Msk                 (0x1UL)                   /*!< SCU SCR: SWRST (Bitfield-Mask: 0x01)                  */
/* =========================================================  WUER  ========================================================== */
#define SCU_WUER_SYSTICKWUE_Pos           (16UL)                    /*!< SCU WUER: SYSTICKWUE (Bit 16)                         */
#define SCU_WUER_SYSTICKWUE_Msk           (0x10000UL)               /*!< SCU WUER: SYSTICKWUE (Bitfield-Mask: 0x01)            */
#define SCU_WUER_GPIOFWUE_Pos             (13UL)                    /*!< SCU WUER: GPIOFWUE (Bit 13)                           */
#define SCU_WUER_GPIOFWUE_Msk             (0x2000UL)                /*!< SCU WUER: GPIOFWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_GPIOEWUE_Pos             (12UL)                    /*!< SCU WUER: GPIOEWUE (Bit 12)                           */
#define SCU_WUER_GPIOEWUE_Msk             (0x1000UL)                /*!< SCU WUER: GPIOEWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_GPIODWUE_Pos             (11UL)                    /*!< SCU WUER: GPIODWUE (Bit 11)                           */
#define SCU_WUER_GPIODWUE_Msk             (0x800UL)                 /*!< SCU WUER: GPIODWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_GPIOCWUE_Pos             (10UL)                    /*!< SCU WUER: GPIOCWUE (Bit 10)                           */
#define SCU_WUER_GPIOCWUE_Msk             (0x400UL)                 /*!< SCU WUER: GPIOCWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_GPIOBWUE_Pos             (9UL)                     /*!< SCU WUER: GPIOBWUE (Bit 9)                            */
#define SCU_WUER_GPIOBWUE_Msk             (0x200UL)                 /*!< SCU WUER: GPIOBWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_GPIOAWUE_Pos             (8UL)                     /*!< SCU WUER: GPIOAWUE (Bit 8)                            */
#define SCU_WUER_GPIOAWUE_Msk             (0x100UL)                 /*!< SCU WUER: GPIOAWUE (Bitfield-Mask: 0x01)              */
#define SCU_WUER_WTWUE_Pos                (2UL)                     /*!< SCU WUER: WTWUE (Bit 2)                               */
#define SCU_WUER_WTWUE_Msk                (0x4UL)                   /*!< SCU WUER: WTWUE (Bitfield-Mask: 0x01)                 */
#define SCU_WUER_WDTWUE_Pos               (1UL)                     /*!< SCU WUER: WDTWUE (Bit 1)                              */
#define SCU_WUER_WDTWUE_Msk               (0x2UL)                   /*!< SCU WUER: WDTWUE (Bitfield-Mask: 0x01)                */
#define SCU_WUER_LVIWUE_Pos               (0UL)                     /*!< SCU WUER: LVIWUE (Bit 0)                              */
#define SCU_WUER_LVIWUE_Msk               (0x1UL)                   /*!< SCU WUER: LVIWUE (Bitfield-Mask: 0x01)                */
/* =========================================================  WUSR  ========================================================== */
#define SCU_WUSR_SYSTICKWU_Pos            (16UL)                    /*!< SCU WUSR: SYSTICKWU (Bit 16)                          */
#define SCU_WUSR_SYSTICKWU_Msk            (0x10000UL)               /*!< SCU WUSR: SYSTICKWU (Bitfield-Mask: 0x01)             */
#define SCU_WUSR_GPIOFWU_Pos              (13UL)                    /*!< SCU WUSR: GPIOFWU (Bit 13)                            */
#define SCU_WUSR_GPIOFWU_Msk              (0x2000UL)                /*!< SCU WUSR: GPIOFWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_GPIOEWU_Pos              (12UL)                    /*!< SCU WUSR: GPIOEWU (Bit 12)                            */
#define SCU_WUSR_GPIOEWU_Msk              (0x1000UL)                /*!< SCU WUSR: GPIOEWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_GPIODWU_Pos              (11UL)                    /*!< SCU WUSR: GPIODWU (Bit 11)                            */
#define SCU_WUSR_GPIODWU_Msk              (0x800UL)                 /*!< SCU WUSR: GPIODWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_GPIOCWU_Pos              (10UL)                    /*!< SCU WUSR: GPIOCWU (Bit 10)                            */
#define SCU_WUSR_GPIOCWU_Msk              (0x400UL)                 /*!< SCU WUSR: GPIOCWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_GPIOBWU_Pos              (9UL)                     /*!< SCU WUSR: GPIOBWU (Bit 9)                             */
#define SCU_WUSR_GPIOBWU_Msk              (0x200UL)                 /*!< SCU WUSR: GPIOBWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_GPIOAWU_Pos              (8UL)                     /*!< SCU WUSR: GPIOAWU (Bit 8)                             */
#define SCU_WUSR_GPIOAWU_Msk              (0x100UL)                 /*!< SCU WUSR: GPIOAWU (Bitfield-Mask: 0x01)               */
#define SCU_WUSR_WTWU_Pos                 (2UL)                     /*!< SCU WUSR: WTWU (Bit 2)                                */
#define SCU_WUSR_WTWU_Msk                 (0x4UL)                   /*!< SCU WUSR: WTWU (Bitfield-Mask: 0x01)                  */
#define SCU_WUSR_WDTWU_Pos                (1UL)                     /*!< SCU WUSR: WDTWU (Bit 1)                               */
#define SCU_WUSR_WDTWU_Msk                (0x2UL)                   /*!< SCU WUSR: WDTWU (Bitfield-Mask: 0x01)                 */
#define SCU_WUSR_LVIWU_Pos                (0UL)                     /*!< SCU WUSR: LVIWU (Bit 0)                               */
#define SCU_WUSR_LVIWU_Msk                (0x1UL)                   /*!< SCU WUSR: LVIWU (Bitfield-Mask: 0x01)                 */
/* =========================================================  RSER  ========================================================== */
#define SCU_RSER_PINRST_Pos               (6UL)                     /*!< SCU RSER: PINRST (Bit 6)                              */
#define SCU_RSER_PINRST_Msk               (0x40UL)                  /*!< SCU RSER: PINRST (Bitfield-Mask: 0x01)                */
#define SCU_RSER_CPURST_Pos               (5UL)                     /*!< SCU RSER: CPURST (Bit 5)                              */
#define SCU_RSER_CPURST_Msk               (0x20UL)                  /*!< SCU RSER: CPURST (Bitfield-Mask: 0x01)                */
#define SCU_RSER_SWRST_Pos                (4UL)                     /*!< SCU RSER: SWRST (Bit 4)                               */
#define SCU_RSER_SWRST_Msk                (0x10UL)                  /*!< SCU RSER: SWRST (Bitfield-Mask: 0x01)                 */
#define SCU_RSER_WDTRST_Pos               (3UL)                     /*!< SCU RSER: WDTRST (Bit 3)                              */
#define SCU_RSER_WDTRST_Msk               (0x8UL)                   /*!< SCU RSER: WDTRST (Bitfield-Mask: 0x01)                */
#define SCU_RSER_MCKFRST_Pos              (2UL)                     /*!< SCU RSER: MCKFRST (Bit 2)                             */
#define SCU_RSER_MCKFRST_Msk              (0x4UL)                   /*!< SCU RSER: MCKFRST (Bitfield-Mask: 0x01)               */
#define SCU_RSER_HSEFRST_Pos              (1UL)                     /*!< SCU RSER: HSEFRST (Bit 1)                             */
#define SCU_RSER_HSEFRST_Msk              (0x2UL)                   /*!< SCU RSER: HSEFRST (Bitfield-Mask: 0x01)               */
#define SCU_RSER_LVDRST_Pos               (0UL)                     /*!< SCU RSER: LVDRST (Bit 0)                              */
#define SCU_RSER_LVDRST_Msk               (0x1UL)                   /*!< SCU RSER: LVDRST (Bitfield-Mask: 0x01)                */
/* =========================================================  RSSR  ========================================================== */
#define SCU_RSSR_PORST_Pos                (7UL)                     /*!< SCU RSSR: PORST (Bit 7)                               */
#define SCU_RSSR_PORST_Msk                (0x80UL)                  /*!< SCU RSSR: PORST (Bitfield-Mask: 0x01)                 */
#define SCU_RSSR_PINRST_Pos               (6UL)                     /*!< SCU RSSR: PINRST (Bit 6)                              */
#define SCU_RSSR_PINRST_Msk               (0x40UL)                  /*!< SCU RSSR: PINRST (Bitfield-Mask: 0x01)                */
#define SCU_RSSR_CPURST_Pos               (5UL)                     /*!< SCU RSSR: CPURST (Bit 5)                              */
#define SCU_RSSR_CPURST_Msk               (0x20UL)                  /*!< SCU RSSR: CPURST (Bitfield-Mask: 0x01)                */
#define SCU_RSSR_SWRST_Pos                (4UL)                     /*!< SCU RSSR: SWRST (Bit 4)                               */
#define SCU_RSSR_SWRST_Msk                (0x10UL)                  /*!< SCU RSSR: SWRST (Bitfield-Mask: 0x01)                 */
#define SCU_RSSR_WDTRST_Pos               (3UL)                     /*!< SCU RSSR: WDTRST (Bit 3)                              */
#define SCU_RSSR_WDTRST_Msk               (0x8UL)                   /*!< SCU RSSR: WDTRST (Bitfield-Mask: 0x01)                */
#define SCU_RSSR_MCKFRST_Pos              (2UL)                     /*!< SCU RSSR: MCKFRST (Bit 2)                             */
#define SCU_RSSR_MCKFRST_Msk              (0x4UL)                   /*!< SCU RSSR: MCKFRST (Bitfield-Mask: 0x01)               */
#define SCU_RSSR_HSEFRST_Pos              (1UL)                     /*!< SCU RSSR: HSEFRST (Bit 1)                             */
#define SCU_RSSR_HSEFRST_Msk              (0x2UL)                   /*!< SCU RSSR: HSEFRST (Bitfield-Mask: 0x01)               */
#define SCU_RSSR_LVDRST_Pos               (0UL)                     /*!< SCU RSSR: LVDRST (Bit 0)                              */
#define SCU_RSSR_LVDRST_Msk               (0x1UL)                   /*!< SCU RSSR: LVDRST (Bitfield-Mask: 0x01)                */
/* =========================================================  PRER1  ========================================================= */
#define SCU_PRER1_WT_Pos                  (31UL)                    /*!< SCU PRER1: WT (Bit 31)                                */
#define SCU_PRER1_WT_Msk                  (0x80000000UL)            /*!< SCU PRER1: WT (Bitfield-Mask: 0x01)                   */
#define SCU_PRER1_TIMER21_Pos             (26UL)                    /*!< SCU PRER1: TIMER21 (Bit 26)                           */
#define SCU_PRER1_TIMER21_Msk             (0x4000000UL)             /*!< SCU PRER1: TIMER21 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER20_Pos             (25UL)                    /*!< SCU PRER1: TIMER20 (Bit 25)                           */
#define SCU_PRER1_TIMER20_Msk             (0x2000000UL)             /*!< SCU PRER1: TIMER20 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER30_Pos             (24UL)                    /*!< SCU PRER1: TIMER30 (Bit 24)                           */
#define SCU_PRER1_TIMER30_Msk             (0x1000000UL)             /*!< SCU PRER1: TIMER30 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER16_Pos             (22UL)                    /*!< SCU PRER1: TIMER16 (Bit 22)                           */
#define SCU_PRER1_TIMER16_Msk             (0x400000UL)              /*!< SCU PRER1: TIMER16 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER15_Pos             (21UL)                    /*!< SCU PRER1: TIMER15 (Bit 21)                           */
#define SCU_PRER1_TIMER15_Msk             (0x200000UL)              /*!< SCU PRER1: TIMER15 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER14_Pos             (20UL)                    /*!< SCU PRER1: TIMER14 (Bit 20)                           */
#define SCU_PRER1_TIMER14_Msk             (0x100000UL)              /*!< SCU PRER1: TIMER14 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER13_Pos             (19UL)                    /*!< SCU PRER1: TIMER13 (Bit 19)                           */
#define SCU_PRER1_TIMER13_Msk             (0x80000UL)               /*!< SCU PRER1: TIMER13 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER12_Pos             (18UL)                    /*!< SCU PRER1: TIMER12 (Bit 18)                           */
#define SCU_PRER1_TIMER12_Msk             (0x40000UL)               /*!< SCU PRER1: TIMER12 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER11_Pos             (17UL)                    /*!< SCU PRER1: TIMER11 (Bit 17)                           */
#define SCU_PRER1_TIMER11_Msk             (0x20000UL)               /*!< SCU PRER1: TIMER11 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_TIMER10_Pos             (16UL)                    /*!< SCU PRER1: TIMER10 (Bit 16)                           */
#define SCU_PRER1_TIMER10_Msk             (0x10000UL)               /*!< SCU PRER1: TIMER10 (Bitfield-Mask: 0x01)              */
#define SCU_PRER1_GPIOF_Pos               (13UL)                    /*!< SCU PRER1: GPIOF (Bit 13)                             */
#define SCU_PRER1_GPIOF_Msk               (0x2000UL)                /*!< SCU PRER1: GPIOF (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_GPIOE_Pos               (12UL)                    /*!< SCU PRER1: GPIOE (Bit 12)                             */
#define SCU_PRER1_GPIOE_Msk               (0x1000UL)                /*!< SCU PRER1: GPIOE (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_GPIOD_Pos               (11UL)                    /*!< SCU PRER1: GPIOD (Bit 11)                             */
#define SCU_PRER1_GPIOD_Msk               (0x800UL)                 /*!< SCU PRER1: GPIOD (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_GPIOC_Pos               (10UL)                    /*!< SCU PRER1: GPIOC (Bit 10)                             */
#define SCU_PRER1_GPIOC_Msk               (0x400UL)                 /*!< SCU PRER1: GPIOC (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_GPIOB_Pos               (9UL)                     /*!< SCU PRER1: GPIOB (Bit 9)                              */
#define SCU_PRER1_GPIOB_Msk               (0x200UL)                 /*!< SCU PRER1: GPIOB (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_GPIOA_Pos               (8UL)                     /*!< SCU PRER1: GPIOA (Bit 8)                              */
#define SCU_PRER1_GPIOA_Msk               (0x100UL)                 /*!< SCU PRER1: GPIOA (Bitfield-Mask: 0x01)                */
#define SCU_PRER1_DMA_Pos                 (4UL)                     /*!< SCU PRER1: DMA (Bit 4)                                */
#define SCU_PRER1_DMA_Msk                 (0x10UL)                  /*!< SCU PRER1: DMA (Bitfield-Mask: 0x01)                  */
#define SCU_PRER1_PCU_Pos                 (3UL)                     /*!< SCU PRER1: PCU (Bit 3)                                */
#define SCU_PRER1_PCU_Msk                 (0x8UL)                   /*!< SCU PRER1: PCU (Bitfield-Mask: 0x01)                  */
#define SCU_PRER1_WDT_Pos                 (2UL)                     /*!< SCU PRER1: WDT (Bit 2)                                */
#define SCU_PRER1_WDT_Msk                 (0x4UL)                   /*!< SCU PRER1: WDT (Bitfield-Mask: 0x01)                  */
#define SCU_PRER1_FMC_Pos                 (1UL)                     /*!< SCU PRER1: FMC (Bit 1)                                */
#define SCU_PRER1_FMC_Msk                 (0x2UL)                   /*!< SCU PRER1: FMC (Bitfield-Mask: 0x01)                  */
#define SCU_PRER1_SCU_Pos                 (0UL)                     /*!< SCU PRER1: SCU (Bit 0)                                */
#define SCU_PRER1_SCU_Msk                 (0x1UL)                   /*!< SCU PRER1: SCU (Bitfield-Mask: 0x01)                  */
/* =========================================================  PRER2  ========================================================= */
#define SCU_PRER2_CRC_Pos                 (31UL)                    /*!< SCU PRER2: CRC (Bit 31)                               */
#define SCU_PRER2_CRC_Msk                 (0x80000000UL)            /*!< SCU PRER2: CRC (Bitfield-Mask: 0x01)                  */
#define SCU_PRER2_LCD_Pos                 (28UL)                    /*!< SCU PRER2: LCD (Bit 28)                               */
#define SCU_PRER2_LCD_Msk                 (0x10000000UL)            /*!< SCU PRER2: LCD (Bitfield-Mask: 0x01)                  */
#define SCU_PRER2_TS_Pos                  (27UL)                    /*!< SCU PRER2: TS (Bit 27)                                */
#define SCU_PRER2_TS_Msk                  (0x8000000UL)             /*!< SCU PRER2: TS (Bitfield-Mask: 0x01)                   */
#define SCU_PRER2_CMP_Pos                 (23UL)                    /*!< SCU PRER2: CMP (Bit 23)                               */
#define SCU_PRER2_CMP_Msk                 (0x800000UL)              /*!< SCU PRER2: CMP (Bitfield-Mask: 0x01)                  */
#define SCU_PRER2_DAC_Pos                 (22UL)                    /*!< SCU PRER2: DAC (Bit 22)                               */
#define SCU_PRER2_DAC_Msk                 (0x400000UL)              /*!< SCU PRER2: DAC (Bitfield-Mask: 0x01)                  */
#define SCU_PRER2_ADC_Pos                 (20UL)                    /*!< SCU PRER2: ADC (Bit 20)                               */
#define SCU_PRER2_ADC_Msk                 (0x100000UL)              /*!< SCU PRER2: ADC (Bitfield-Mask: 0x01)                  */
#define SCU_PRER2_SPI21_Pos               (15UL)                    /*!< SCU PRER2: SPI21 (Bit 15)                             */
#define SCU_PRER2_SPI21_Msk               (0x8000UL)                /*!< SCU PRER2: SPI21 (Bitfield-Mask: 0x01)                */
#define SCU_PRER2_SPI20_Pos               (14UL)                    /*!< SCU PRER2: SPI20 (Bit 14)                             */
#define SCU_PRER2_SPI20_Msk               (0x4000UL)                /*!< SCU PRER2: SPI20 (Bitfield-Mask: 0x01)                */
#define SCU_PRER2_UART1_Pos               (13UL)                    /*!< SCU PRER2: UART1 (Bit 13)                             */
#define SCU_PRER2_UART1_Msk               (0x2000UL)                /*!< SCU PRER2: UART1 (Bitfield-Mask: 0x01)                */
#define SCU_PRER2_UART0_Pos               (12UL)                    /*!< SCU PRER2: UART0 (Bit 12)                             */
#define SCU_PRER2_UART0_Msk               (0x1000UL)                /*!< SCU PRER2: UART0 (Bitfield-Mask: 0x01)                */
#define SCU_PRER2_USART13_Pos             (11UL)                    /*!< SCU PRER2: USART13 (Bit 11)                           */
#define SCU_PRER2_USART13_Msk             (0x800UL)                 /*!< SCU PRER2: USART13 (Bitfield-Mask: 0x01)              */
#define SCU_PRER2_USART12_Pos             (10UL)                    /*!< SCU PRER2: USART12 (Bit 10)                           */
#define SCU_PRER2_USART12_Msk             (0x400UL)                 /*!< SCU PRER2: USART12 (Bitfield-Mask: 0x01)              */
#define SCU_PRER2_USART11_Pos             (9UL)                     /*!< SCU PRER2: USART11 (Bit 9)                            */
#define SCU_PRER2_USART11_Msk             (0x200UL)                 /*!< SCU PRER2: USART11 (Bitfield-Mask: 0x01)              */
#define SCU_PRER2_USART10_Pos             (8UL)                     /*!< SCU PRER2: USART10 (Bit 8)                            */
#define SCU_PRER2_USART10_Msk             (0x100UL)                 /*!< SCU PRER2: USART10 (Bitfield-Mask: 0x01)              */
#define SCU_PRER2_I2C2_Pos                (6UL)                     /*!< SCU PRER2: I2C2 (Bit 6)                               */
#define SCU_PRER2_I2C2_Msk                (0x40UL)                  /*!< SCU PRER2: I2C2 (Bitfield-Mask: 0x01)                 */
#define SCU_PRER2_I2C1_Pos                (5UL)                     /*!< SCU PRER2: I2C1 (Bit 5)                               */
#define SCU_PRER2_I2C1_Msk                (0x20UL)                  /*!< SCU PRER2: I2C1 (Bitfield-Mask: 0x01)                 */
#define SCU_PRER2_I2C0_Pos                (4UL)                     /*!< SCU PRER2: I2C0 (Bit 4)                               */
#define SCU_PRER2_I2C0_Msk                (0x10UL)                  /*!< SCU PRER2: I2C0 (Bitfield-Mask: 0x01)                 */
/* =========================================================  PER1  ========================================================== */
#define SCU_PER1_WT_Pos                   (31UL)                    /*!< SCU PER1: WT (Bit 31)                                 */
#define SCU_PER1_WT_Msk                   (0x80000000UL)            /*!< SCU PER1: WT (Bitfield-Mask: 0x01)                    */
#define SCU_PER1_TIMER21_Pos              (26UL)                    /*!< SCU PER1: TIMER21 (Bit 26)                            */
#define SCU_PER1_TIMER21_Msk              (0x4000000UL)             /*!< SCU PER1: TIMER21 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER20_Pos              (25UL)                    /*!< SCU PER1: TIMER20 (Bit 25)                            */
#define SCU_PER1_TIMER20_Msk              (0x2000000UL)             /*!< SCU PER1: TIMER20 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER30_Pos              (24UL)                    /*!< SCU PER1: TIMER30 (Bit 24)                            */
#define SCU_PER1_TIMER30_Msk              (0x1000000UL)             /*!< SCU PER1: TIMER30 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER16_Pos              (22UL)                    /*!< SCU PER1: TIMER16 (Bit 22)                            */
#define SCU_PER1_TIMER16_Msk              (0x400000UL)              /*!< SCU PER1: TIMER16 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER15_Pos              (21UL)                    /*!< SCU PER1: TIMER15 (Bit 21)                            */
#define SCU_PER1_TIMER15_Msk              (0x200000UL)              /*!< SCU PER1: TIMER15 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER14_Pos              (20UL)                    /*!< SCU PER1: TIMER14 (Bit 20)                            */
#define SCU_PER1_TIMER14_Msk              (0x100000UL)              /*!< SCU PER1: TIMER14 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER13_Pos              (19UL)                    /*!< SCU PER1: TIMER13 (Bit 19)                            */
#define SCU_PER1_TIMER13_Msk              (0x80000UL)               /*!< SCU PER1: TIMER13 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER12_Pos              (18UL)                    /*!< SCU PER1: TIMER12 (Bit 18)                            */
#define SCU_PER1_TIMER12_Msk              (0x40000UL)               /*!< SCU PER1: TIMER12 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER11_Pos              (17UL)                    /*!< SCU PER1: TIMER11 (Bit 17)                            */
#define SCU_PER1_TIMER11_Msk              (0x20000UL)               /*!< SCU PER1: TIMER11 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_TIMER10_Pos              (16UL)                    /*!< SCU PER1: TIMER10 (Bit 16)                            */
#define SCU_PER1_TIMER10_Msk              (0x10000UL)               /*!< SCU PER1: TIMER10 (Bitfield-Mask: 0x01)               */
#define SCU_PER1_GPIOF_Pos                (13UL)                    /*!< SCU PER1: GPIOF (Bit 13)                              */
#define SCU_PER1_GPIOF_Msk                (0x2000UL)                /*!< SCU PER1: GPIOF (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_GPIOE_Pos                (12UL)                    /*!< SCU PER1: GPIOE (Bit 12)                              */
#define SCU_PER1_GPIOE_Msk                (0x1000UL)                /*!< SCU PER1: GPIOE (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_GPIOD_Pos                (11UL)                    /*!< SCU PER1: GPIOD (Bit 11)                              */
#define SCU_PER1_GPIOD_Msk                (0x800UL)                 /*!< SCU PER1: GPIOD (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_GPIOC_Pos                (10UL)                    /*!< SCU PER1: GPIOC (Bit 10)                              */
#define SCU_PER1_GPIOC_Msk                (0x400UL)                 /*!< SCU PER1: GPIOC (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_GPIOB_Pos                (9UL)                     /*!< SCU PER1: GPIOB (Bit 9)                               */
#define SCU_PER1_GPIOB_Msk                (0x200UL)                 /*!< SCU PER1: GPIOB (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_GPIOA_Pos                (8UL)                     /*!< SCU PER1: GPIOA (Bit 8)                               */
#define SCU_PER1_GPIOA_Msk                (0x100UL)                 /*!< SCU PER1: GPIOA (Bitfield-Mask: 0x01)                 */
#define SCU_PER1_DMA_Pos                  (4UL)                     /*!< SCU PER1: DMA (Bit 4)                                 */
#define SCU_PER1_DMA_Msk                  (0x10UL)                  /*!< SCU PER1: DMA (Bitfield-Mask: 0x01)                   */
/* =========================================================  PER2  ========================================================== */
#define SCU_PER2_CRC_Pos                  (31UL)                    /*!< SCU PER2: CRC (Bit 31)                                */
#define SCU_PER2_CRC_Msk                  (0x80000000UL)            /*!< SCU PER2: CRC (Bitfield-Mask: 0x01)                   */
#define SCU_PER2_LCD_Pos                  (28UL)                    /*!< SCU PER2: LCD (Bit 28)                                */
#define SCU_PER2_LCD_Msk                  (0x10000000UL)            /*!< SCU PER2: LCD (Bitfield-Mask: 0x01)                   */
#define SCU_PER2_TS_Pos                   (27UL)                    /*!< SCU PER2: TS (Bit 27)                                 */
#define SCU_PER2_TS_Msk                   (0x8000000UL)             /*!< SCU PER2: TS (Bitfield-Mask: 0x01)                    */
#define SCU_PER2_CMP_Pos                  (23UL)                    /*!< SCU PER2: CMP (Bit 23)                                */
#define SCU_PER2_CMP_Msk                  (0x800000UL)              /*!< SCU PER2: CMP (Bitfield-Mask: 0x01)                   */
#define SCU_PER2_DAC_Pos                  (22UL)                    /*!< SCU PER2: DAC (Bit 22)                                */
#define SCU_PER2_DAC_Msk                  (0x400000UL)              /*!< SCU PER2: DAC (Bitfield-Mask: 0x01)                   */
#define SCU_PER2_ADC_Pos                  (20UL)                    /*!< SCU PER2: ADC (Bit 20)                                */
#define SCU_PER2_ADC_Msk                  (0x100000UL)              /*!< SCU PER2: ADC (Bitfield-Mask: 0x01)                   */
#define SCU_PER2_SPI21_Pos                (15UL)                    /*!< SCU PER2: SPI21 (Bit 15)                              */
#define SCU_PER2_SPI21_Msk                (0x8000UL)                /*!< SCU PER2: SPI21 (Bitfield-Mask: 0x01)                 */
#define SCU_PER2_SPI20_Pos                (14UL)                    /*!< SCU PER2: SPI20 (Bit 14)                              */
#define SCU_PER2_SPI20_Msk                (0x4000UL)                /*!< SCU PER2: SPI20 (Bitfield-Mask: 0x01)                 */
#define SCU_PER2_UART1_Pos                (13UL)                    /*!< SCU PER2: UART1 (Bit 13)                              */
#define SCU_PER2_UART1_Msk                (0x2000UL)                /*!< SCU PER2: UART1 (Bitfield-Mask: 0x01)                 */
#define SCU_PER2_UART0_Pos                (12UL)                    /*!< SCU PER2: UART0 (Bit 12)                              */
#define SCU_PER2_UART0_Msk                (0x1000UL)                /*!< SCU PER2: UART0 (Bitfield-Mask: 0x01)                 */
#define SCU_PER2_USART13_Pos              (11UL)                    /*!< SCU PER2: USART13 (Bit 11)                            */
#define SCU_PER2_USART13_Msk              (0x800UL)                 /*!< SCU PER2: USART13 (Bitfield-Mask: 0x01)               */
#define SCU_PER2_USART12_Pos              (10UL)                    /*!< SCU PER2: USART12 (Bit 10)                            */
#define SCU_PER2_USART12_Msk              (0x400UL)                 /*!< SCU PER2: USART12 (Bitfield-Mask: 0x01)               */
#define SCU_PER2_USART11_Pos              (9UL)                     /*!< SCU PER2: USART11 (Bit 9)                             */
#define SCU_PER2_USART11_Msk              (0x200UL)                 /*!< SCU PER2: USART11 (Bitfield-Mask: 0x01)               */
#define SCU_PER2_USART10_Pos              (8UL)                     /*!< SCU PER2: USART10 (Bit 8)                             */
#define SCU_PER2_USART10_Msk              (0x100UL)                 /*!< SCU PER2: USART10 (Bitfield-Mask: 0x01)               */
#define SCU_PER2_I2C2_Pos                 (6UL)                     /*!< SCU PER2: I2C2 (Bit 6)                                */
#define SCU_PER2_I2C2_Msk                 (0x40UL)                  /*!< SCU PER2: I2C2 (Bitfield-Mask: 0x01)                  */
#define SCU_PER2_I2C1_Pos                 (5UL)                     /*!< SCU PER2: I2C1 (Bit 5)                                */
#define SCU_PER2_I2C1_Msk                 (0x20UL)                  /*!< SCU PER2: I2C1 (Bitfield-Mask: 0x01)                  */
#define SCU_PER2_I2C0_Pos                 (4UL)                     /*!< SCU PER2: I2C0 (Bit 4)                                */
#define SCU_PER2_I2C0_Msk                 (0x10UL)                  /*!< SCU PER2: I2C0 (Bitfield-Mask: 0x01)                  */
/* =========================================================  PCER1  ========================================================= */
#define SCU_PCER1_WT_Pos                  (31UL)                    /*!< SCU PCER1: WT (Bit 31)                                */
#define SCU_PCER1_WT_Msk                  (0x80000000UL)            /*!< SCU PCER1: WT (Bitfield-Mask: 0x01)                   */
#define SCU_PCER1_TIMER21_Pos             (26UL)                    /*!< SCU PCER1: TIMER21 (Bit 26)                           */
#define SCU_PCER1_TIMER21_Msk             (0x4000000UL)             /*!< SCU PCER1: TIMER21 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER20_Pos             (25UL)                    /*!< SCU PCER1: TIMER20 (Bit 25)                           */
#define SCU_PCER1_TIMER20_Msk             (0x2000000UL)             /*!< SCU PCER1: TIMER20 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER30_Pos             (24UL)                    /*!< SCU PCER1: TIMER30 (Bit 24)                           */
#define SCU_PCER1_TIMER30_Msk             (0x1000000UL)             /*!< SCU PCER1: TIMER30 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER16_Pos             (22UL)                    /*!< SCU PCER1: TIMER16 (Bit 22)                           */
#define SCU_PCER1_TIMER16_Msk             (0x400000UL)              /*!< SCU PCER1: TIMER16 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER15_Pos             (21UL)                    /*!< SCU PCER1: TIMER15 (Bit 21)                           */
#define SCU_PCER1_TIMER15_Msk             (0x200000UL)              /*!< SCU PCER1: TIMER15 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER14_Pos             (20UL)                    /*!< SCU PCER1: TIMER14 (Bit 20)                           */
#define SCU_PCER1_TIMER14_Msk             (0x100000UL)              /*!< SCU PCER1: TIMER14 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER13_Pos             (19UL)                    /*!< SCU PCER1: TIMER13 (Bit 19)                           */
#define SCU_PCER1_TIMER13_Msk             (0x80000UL)               /*!< SCU PCER1: TIMER13 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER12_Pos             (18UL)                    /*!< SCU PCER1: TIMER12 (Bit 18)                           */
#define SCU_PCER1_TIMER12_Msk             (0x40000UL)               /*!< SCU PCER1: TIMER12 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER11_Pos             (17UL)                    /*!< SCU PCER1: TIMER11 (Bit 17)                           */
#define SCU_PCER1_TIMER11_Msk             (0x20000UL)               /*!< SCU PCER1: TIMER11 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_TIMER10_Pos             (16UL)                    /*!< SCU PCER1: TIMER10 (Bit 16)                           */
#define SCU_PCER1_TIMER10_Msk             (0x10000UL)               /*!< SCU PCER1: TIMER10 (Bitfield-Mask: 0x01)              */
#define SCU_PCER1_GPIOF_Pos               (13UL)                    /*!< SCU PCER1: GPIOF (Bit 13)                             */
#define SCU_PCER1_GPIOF_Msk               (0x2000UL)                /*!< SCU PCER1: GPIOF (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_GPIOE_Pos               (12UL)                    /*!< SCU PCER1: GPIOE (Bit 12)                             */
#define SCU_PCER1_GPIOE_Msk               (0x1000UL)                /*!< SCU PCER1: GPIOE (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_GPIOD_Pos               (11UL)                    /*!< SCU PCER1: GPIOD (Bit 11)                             */
#define SCU_PCER1_GPIOD_Msk               (0x800UL)                 /*!< SCU PCER1: GPIOD (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_GPIOC_Pos               (10UL)                    /*!< SCU PCER1: GPIOC (Bit 10)                             */
#define SCU_PCER1_GPIOC_Msk               (0x400UL)                 /*!< SCU PCER1: GPIOC (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_GPIOB_Pos               (9UL)                     /*!< SCU PCER1: GPIOB (Bit 9)                              */
#define SCU_PCER1_GPIOB_Msk               (0x200UL)                 /*!< SCU PCER1: GPIOB (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_GPIOA_Pos               (8UL)                     /*!< SCU PCER1: GPIOA (Bit 8)                              */
#define SCU_PCER1_GPIOA_Msk               (0x100UL)                 /*!< SCU PCER1: GPIOA (Bitfield-Mask: 0x01)                */
#define SCU_PCER1_DMA_Pos                 (4UL)                     /*!< SCU PCER1: DMA (Bit 4)                                */
#define SCU_PCER1_DMA_Msk                 (0x10UL)                  /*!< SCU PCER1: DMA (Bitfield-Mask: 0x01)                  */
/* =========================================================  PCER2  ========================================================= */
#define SCU_PCER2_CRC_Pos                 (31UL)                    /*!< SCU PCER2: CRC (Bit 31)                               */
#define SCU_PCER2_CRC_Msk                 (0x80000000UL)            /*!< SCU PCER2: CRC (Bitfield-Mask: 0x01)                  */
#define SCU_PCER2_LCD_Pos                 (28UL)                    /*!< SCU PCER2: LCD (Bit 28)                               */
#define SCU_PCER2_LCD_Msk                 (0x10000000UL)            /*!< SCU PCER2: LCD (Bitfield-Mask: 0x01)                  */
#define SCU_PCER2_TS_Pos                  (27UL)                    /*!< SCU PCER2: TS (Bit 27)                                */
#define SCU_PCER2_TS_Msk                  (0x8000000UL)             /*!< SCU PCER2: TS (Bitfield-Mask: 0x01)                   */
#define SCU_PCER2_CMP_Pos                 (23UL)                    /*!< SCU PCER2: CMP (Bit 23)                               */
#define SCU_PCER2_CMP_Msk                 (0x800000UL)              /*!< SCU PCER2: CMP (Bitfield-Mask: 0x01)                  */
#define SCU_PCER2_DAC_Pos                 (22UL)                    /*!< SCU PCER2: DAC (Bit 22)                               */
#define SCU_PCER2_DAC_Msk                 (0x400000UL)              /*!< SCU PCER2: DAC (Bitfield-Mask: 0x01)                  */
#define SCU_PCER2_ADC_Pos                 (20UL)                    /*!< SCU PCER2: ADC (Bit 20)                               */
#define SCU_PCER2_ADC_Msk                 (0x100000UL)              /*!< SCU PCER2: ADC (Bitfield-Mask: 0x01)                  */
#define SCU_PCER2_SPI21_Pos               (15UL)                    /*!< SCU PCER2: SPI21 (Bit 15)                             */
#define SCU_PCER2_SPI21_Msk               (0x8000UL)                /*!< SCU PCER2: SPI21 (Bitfield-Mask: 0x01)                */
#define SCU_PCER2_SPI20_Pos               (14UL)                    /*!< SCU PCER2: SPI20 (Bit 14)                             */
#define SCU_PCER2_SPI20_Msk               (0x4000UL)                /*!< SCU PCER2: SPI20 (Bitfield-Mask: 0x01)                */
#define SCU_PCER2_UART1_Pos               (13UL)                    /*!< SCU PCER2: UART1 (Bit 13)                             */
#define SCU_PCER2_UART1_Msk               (0x2000UL)                /*!< SCU PCER2: UART1 (Bitfield-Mask: 0x01)                */
#define SCU_PCER2_UART0_Pos               (12UL)                    /*!< SCU PCER2: UART0 (Bit 12)                             */
#define SCU_PCER2_UART0_Msk               (0x1000UL)                /*!< SCU PCER2: UART0 (Bitfield-Mask: 0x01)                */
#define SCU_PCER2_USART13_Pos             (11UL)                    /*!< SCU PCER2: USART13 (Bit 11)                           */
#define SCU_PCER2_USART13_Msk             (0x800UL)                 /*!< SCU PCER2: USART13 (Bitfield-Mask: 0x01)              */
#define SCU_PCER2_USART12_Pos             (10UL)                    /*!< SCU PCER2: USART12 (Bit 10)                           */
#define SCU_PCER2_USART12_Msk             (0x400UL)                 /*!< SCU PCER2: USART12 (Bitfield-Mask: 0x01)              */
#define SCU_PCER2_USART11_Pos             (9UL)                     /*!< SCU PCER2: USART11 (Bit 9)                            */
#define SCU_PCER2_USART11_Msk             (0x200UL)                 /*!< SCU PCER2: USART11 (Bitfield-Mask: 0x01)              */
#define SCU_PCER2_USART10_Pos             (8UL)                     /*!< SCU PCER2: USART10 (Bit 8)                            */
#define SCU_PCER2_USART10_Msk             (0x100UL)                 /*!< SCU PCER2: USART10 (Bitfield-Mask: 0x01)              */
#define SCU_PCER2_I2C2_Pos                (6UL)                     /*!< SCU PCER2: I2C2 (Bit 6)                               */
#define SCU_PCER2_I2C2_Msk                (0x40UL)                  /*!< SCU PCER2: I2C2 (Bitfield-Mask: 0x01)                 */
#define SCU_PCER2_I2C1_Pos                (5UL)                     /*!< SCU PCER2: I2C1 (Bit 5)                               */
#define SCU_PCER2_I2C1_Msk                (0x20UL)                  /*!< SCU PCER2: I2C1 (Bitfield-Mask: 0x01)                 */
#define SCU_PCER2_I2C0_Pos                (4UL)                     /*!< SCU PCER2: I2C0 (Bit 4)                               */
#define SCU_PCER2_I2C0_Msk                (0x10UL)                  /*!< SCU PCER2: I2C0 (Bitfield-Mask: 0x01)                 */
/* ========================================================  PPCLKSR  ======================================================== */
#define SCU_PPCLKSR_T1xCLK_Pos            (22UL)                    /*!< SCU PPCLKSR: T1xCLK (Bit 22)                          */
#define SCU_PPCLKSR_T1xCLK_Msk            (0x400000UL)              /*!< SCU PPCLKSR: T1xCLK (Bitfield-Mask: 0x01)             */
#define SCU_PPCLKSR_T20CLK_Pos            (20UL)                    /*!< SCU PPCLKSR: T20CLK (Bit 20)                          */
#define SCU_PPCLKSR_T20CLK_Msk            (0x100000UL)              /*!< SCU PPCLKSR: T20CLK (Bitfield-Mask: 0x01)             */
#define SCU_PPCLKSR_T30CLK_Pos            (17UL)                    /*!< SCU PPCLKSR: T30CLK (Bit 17)                          */
#define SCU_PPCLKSR_T30CLK_Msk            (0x20000UL)               /*!< SCU PPCLKSR: T30CLK (Bitfield-Mask: 0x01)             */
#define SCU_PPCLKSR_LCDCLK_Pos            (6UL)                     /*!< SCU PPCLKSR: LCDCLK (Bit 6)                           */
#define SCU_PPCLKSR_LCDCLK_Msk            (0xc0UL)                  /*!< SCU PPCLKSR: LCDCLK (Bitfield-Mask: 0x03)             */
#define SCU_PPCLKSR_WTCLK_Pos             (3UL)                     /*!< SCU PPCLKSR: WTCLK (Bit 3)                            */
#define SCU_PPCLKSR_WTCLK_Msk             (0x18UL)                  /*!< SCU PPCLKSR: WTCLK (Bitfield-Mask: 0x03)              */
#define SCU_PPCLKSR_WDTCLK_Pos            (0UL)                     /*!< SCU PPCLKSR: WDTCLK (Bit 0)                           */
#define SCU_PPCLKSR_WDTCLK_Msk            (0x1UL)                   /*!< SCU PPCLKSR: WDTCLK (Bitfield-Mask: 0x01)             */
/* =========================================================  CSCR  ========================================================== */
#define SCU_CSCR_WTIDKY_Pos               (16UL)                    /*!< SCU CSCR: WTIDKY (Bit 16)                             */
#define SCU_CSCR_WTIDKY_Msk               (0xffff0000UL)            /*!< SCU CSCR: WTIDKY (Bitfield-Mask: 0xffff)              */
#define SCU_CSCR_LSECON_Pos               (12UL)                    /*!< SCU CSCR: LSECON (Bit 12)                             */
#define SCU_CSCR_LSECON_Msk               (0xf000UL)                /*!< SCU CSCR: LSECON (Bitfield-Mask: 0x0f)                */
#define SCU_CSCR_LSICON_Pos               (8UL)                     /*!< SCU CSCR: LSICON (Bit 8)                              */
#define SCU_CSCR_LSICON_Msk               (0xf00UL)                 /*!< SCU CSCR: LSICON (Bitfield-Mask: 0x0f)                */
#define SCU_CSCR_HSICON_Pos               (4UL)                     /*!< SCU CSCR: HSICON (Bit 4)                              */
#define SCU_CSCR_HSICON_Msk               (0xf0UL)                  /*!< SCU CSCR: HSICON (Bitfield-Mask: 0x0f)                */
#define SCU_CSCR_HSECON_Pos               (0UL)                     /*!< SCU CSCR: HSECON (Bit 0)                              */
#define SCU_CSCR_HSECON_Msk               (0xfUL)                   /*!< SCU CSCR: HSECON (Bitfield-Mask: 0x0f)                */
/* =========================================================  SCCR  ========================================================== */
#define SCU_SCCR_WTIDKY_Pos               (16UL)                    /*!< SCU SCCR: WTIDKY (Bit 16)                             */
#define SCU_SCCR_WTIDKY_Msk               (0xffff0000UL)            /*!< SCU SCCR: WTIDKY (Bitfield-Mask: 0xffff)              */
#define SCU_SCCR_PLLINCLKSEL_Pos          (2UL)                     /*!< SCU SCCR: PLLINCLKSEL (Bit 2)                         */
#define SCU_SCCR_PLLINCLKSEL_Msk          (0x4UL)                   /*!< SCU SCCR: PLLINCLKSEL (Bitfield-Mask: 0x01)           */
#define SCU_SCCR_MCLKSEL_Pos              (0UL)                     /*!< SCU SCCR: MCLKSEL (Bit 0)                             */
#define SCU_SCCR_MCLKSEL_Msk              (0x3UL)                   /*!< SCU SCCR: MCLKSEL (Bitfield-Mask: 0x03)               */
/* ==========================================================  CMR  ========================================================== */
#define SCU_CMR_MCLKREC_Pos               (15UL)                    /*!< SCU CMR: MCLKREC (Bit 15)                             */
#define SCU_CMR_MCLKREC_Msk               (0x8000UL)                /*!< SCU CMR: MCLKREC (Bitfield-Mask: 0x01)                */
#define SCU_CMR_LSEMNT_Pos                (11UL)                    /*!< SCU CMR: LSEMNT (Bit 11)                              */
#define SCU_CMR_LSEMNT_Msk                (0x800UL)                 /*!< SCU CMR: LSEMNT (Bitfield-Mask: 0x01)                 */
#define SCU_CMR_LSEIE_Pos                 (10UL)                    /*!< SCU CMR: LSEIE (Bit 10)                               */
#define SCU_CMR_LSEIE_Msk                 (0x400UL)                 /*!< SCU CMR: LSEIE (Bitfield-Mask: 0x01)                  */
#define SCU_CMR_LSEFAIL_Pos               (9UL)                     /*!< SCU CMR: LSEFAIL (Bit 9)                              */
#define SCU_CMR_LSEFAIL_Msk               (0x200UL)                 /*!< SCU CMR: LSEFAIL (Bitfield-Mask: 0x01)                */
#define SCU_CMR_LSESTS_Pos                (8UL)                     /*!< SCU CMR: LSESTS (Bit 8)                               */
#define SCU_CMR_LSESTS_Msk                (0x100UL)                 /*!< SCU CMR: LSESTS (Bitfield-Mask: 0x01)                 */
#define SCU_CMR_MCLKMNT_Pos               (7UL)                     /*!< SCU CMR: MCLKMNT (Bit 7)                              */
#define SCU_CMR_MCLKMNT_Msk               (0x80UL)                  /*!< SCU CMR: MCLKMNT (Bitfield-Mask: 0x01)                */
#define SCU_CMR_MCLKIE_Pos                (6UL)                     /*!< SCU CMR: MCLKIE (Bit 6)                               */
#define SCU_CMR_MCLKIE_Msk                (0x40UL)                  /*!< SCU CMR: MCLKIE (Bitfield-Mask: 0x01)                 */
#define SCU_CMR_MCLKFAIL_Pos              (5UL)                     /*!< SCU CMR: MCLKFAIL (Bit 5)                             */
#define SCU_CMR_MCLKFAIL_Msk              (0x20UL)                  /*!< SCU CMR: MCLKFAIL (Bitfield-Mask: 0x01)               */
#define SCU_CMR_MCLKSTS_Pos               (4UL)                     /*!< SCU CMR: MCLKSTS (Bit 4)                              */
#define SCU_CMR_MCLKSTS_Msk               (0x10UL)                  /*!< SCU CMR: MCLKSTS (Bitfield-Mask: 0x01)                */
#define SCU_CMR_HSEMNT_Pos                (3UL)                     /*!< SCU CMR: HSEMNT (Bit 3)                               */
#define SCU_CMR_HSEMNT_Msk                (0x8UL)                   /*!< SCU CMR: HSEMNT (Bitfield-Mask: 0x01)                 */
#define SCU_CMR_HSEIE_Pos                 (2UL)                     /*!< SCU CMR: HSEIE (Bit 2)                                */
#define SCU_CMR_HSEIE_Msk                 (0x4UL)                   /*!< SCU CMR: HSEIE (Bitfield-Mask: 0x01)                  */
#define SCU_CMR_HSEFAIL_Pos               (1UL)                     /*!< SCU CMR: HSEFAIL (Bit 1)                              */
#define SCU_CMR_HSEFAIL_Msk               (0x2UL)                   /*!< SCU CMR: HSEFAIL (Bitfield-Mask: 0x01)                */
#define SCU_CMR_HSESTS_Pos                (0UL)                     /*!< SCU CMR: HSESTS (Bit 0)                               */
#define SCU_CMR_HSESTS_Msk                (0x1UL)                   /*!< SCU CMR: HSESTS (Bitfield-Mask: 0x01)                 */
/* =========================================================  NMIR  ========================================================== */
#define SCU_NMIR_ACCESSCODE_Pos           (16UL)                    /*!< SCU NMIR: ACCESSCODE (Bit 16)                         */
#define SCU_NMIR_ACCESSCODE_Msk           (0xffff0000UL)            /*!< SCU NMIR: ACCESSCODE (Bitfield-Mask: 0xffff)          */
#define SCU_NMIR_SWAPFAILSTS_Pos          (13UL)                    /*!< SCU NMIR: SWAPFAILSTS (Bit 13)                        */
#define SCU_NMIR_SWAPFAILSTS_Msk          (0x2000UL)                /*!< SCU NMIR: SWAPFAILSTS (Bitfield-Mask: 0x01)           */
#define SCU_NMIR_CMPINTSTS_Pos            (12UL)                    /*!< SCU NMIR: CMPINTSTS (Bit 12)                          */
#define SCU_NMIR_CMPINTSTS_Msk            (0x1000UL)                /*!< SCU NMIR: CMPINTSTS (Bitfield-Mask: 0x01)             */
#define SCU_NMIR_T30INTSTS_Pos            (11UL)                    /*!< SCU NMIR: T30INTSTS (Bit 11)                          */
#define SCU_NMIR_T30INTSTS_Msk            (0x800UL)                 /*!< SCU NMIR: T30INTSTS (Bitfield-Mask: 0x01)             */
#define SCU_NMIR_WDTINTSTS_Pos            (10UL)                    /*!< SCU NMIR: WDTINTSTS (Bit 10)                          */
#define SCU_NMIR_WDTINTSTS_Msk            (0x400UL)                 /*!< SCU NMIR: WDTINTSTS (Bitfield-Mask: 0x01)             */
#define SCU_NMIR_MCLKFAILSTS_Pos          (9UL)                     /*!< SCU NMIR: MCLKFAILSTS (Bit 9)                         */
#define SCU_NMIR_MCLKFAILSTS_Msk          (0x200UL)                 /*!< SCU NMIR: MCLKFAILSTS (Bitfield-Mask: 0x01)           */
#define SCU_NMIR_LVRSTS_Pos               (8UL)                     /*!< SCU NMIR: LVRSTS (Bit 8)                              */
#define SCU_NMIR_LVRSTS_Msk               (0x100UL)                 /*!< SCU NMIR: LVRSTS (Bitfield-Mask: 0x01)                */
#define SCU_NMIR_SWAPERRIEN_Pos           (5UL)                     /*!< SCU NMIR: SWAPERRIEN (Bit 5)                          */
#define SCU_NMIR_SWAPERRIEN_Msk           (0x20UL)                  /*!< SCU NMIR: SWAPERRIEN (Bitfield-Mask: 0x01)            */
#define SCU_NMIR_CMPINTEN_Pos             (4UL)                     /*!< SCU NMIR: CMPINTEN (Bit 4)                            */
#define SCU_NMIR_CMPINTEN_Msk             (0x10UL)                  /*!< SCU NMIR: CMPINTEN (Bitfield-Mask: 0x01)              */
#define SCU_NMIR_T30IEN_Pos               (3UL)                     /*!< SCU NMIR: T30IEN (Bit 3)                              */
#define SCU_NMIR_T30IEN_Msk               (0x8UL)                   /*!< SCU NMIR: T30IEN (Bitfield-Mask: 0x01)                */
#define SCU_NMIR_WDTINTEN_Pos             (2UL)                     /*!< SCU NMIR: WDTINTEN (Bit 2)                            */
#define SCU_NMIR_WDTINTEN_Msk             (0x4UL)                   /*!< SCU NMIR: WDTINTEN (Bitfield-Mask: 0x01)              */
#define SCU_NMIR_MCLKFAILEN_Pos           (1UL)                     /*!< SCU NMIR: MCLKFAILEN (Bit 1)                          */
#define SCU_NMIR_MCLKFAILEN_Msk           (0x2UL)                   /*!< SCU NMIR: MCLKFAILEN (Bitfield-Mask: 0x01)            */
#define SCU_NMIR_LVDEN_Pos                (0UL)                     /*!< SCU NMIR: LVDEN (Bit 0)                               */
#define SCU_NMIR_LVDEN_Msk                (0x1UL)                   /*!< SCU NMIR: LVDEN (Bitfield-Mask: 0x01)                 */
/* ==========================================================  COR  ========================================================== */
#define SCU_COR_CLKOEN_Pos                (4UL)                     /*!< SCU COR: CLKOEN (Bit 4)                               */
#define SCU_COR_CLKOEN_Msk                (0x10UL)                  /*!< SCU COR: CLKOEN (Bitfield-Mask: 0x01)                 */
#define SCU_COR_CLKODIV_Pos               (0UL)                     /*!< SCU COR: CLKODIV (Bit 0)                              */
#define SCU_COR_CLKODIV_Msk               (0xfUL)                   /*!< SCU COR: CLKODIV (Bitfield-Mask: 0x0f)                */
/* ========================================================  PLLCON  ========================================================= */
#define SCU_PLLCON_LOCK_Pos               (31UL)                    /*!< SCU PLLCON: LOCK (Bit 31)                             */
#define SCU_PLLCON_LOCK_Msk               (0x80000000UL)            /*!< SCU PLLCON: LOCK (Bitfield-Mask: 0x01)                */
#define SCU_PLLCON_PLLRSTB_Pos            (23UL)                    /*!< SCU PLLCON: PLLRSTB (Bit 23)                          */
#define SCU_PLLCON_PLLRSTB_Msk            (0x800000UL)              /*!< SCU PLLCON: PLLRSTB (Bitfield-Mask: 0x01)             */
#define SCU_PLLCON_PLLEN_Pos              (22UL)                    /*!< SCU PLLCON: PLLEN (Bit 22)                            */
#define SCU_PLLCON_PLLEN_Msk              (0x400000UL)              /*!< SCU PLLCON: PLLEN (Bitfield-Mask: 0x01)               */
#define SCU_PLLCON_BYPASSB_Pos            (21UL)                    /*!< SCU PLLCON: BYPASSB (Bit 21)                          */
#define SCU_PLLCON_BYPASSB_Msk            (0x200000UL)              /*!< SCU PLLCON: BYPASSB (Bitfield-Mask: 0x01)             */
#define SCU_PLLCON_PLLMODE_Pos            (20UL)                    /*!< SCU PLLCON: PLLMODE (Bit 20)                          */
#define SCU_PLLCON_PLLMODE_Msk            (0x100000UL)              /*!< SCU PLLCON: PLLMODE (Bitfield-Mask: 0x01)             */
#define SCU_PLLCON_PREDIV_Pos             (16UL)                    /*!< SCU PLLCON: PREDIV (Bit 16)                           */
#define SCU_PLLCON_PREDIV_Msk             (0x70000UL)               /*!< SCU PLLCON: PREDIV (Bitfield-Mask: 0x07)              */
#define SCU_PLLCON_POSTDIV1_Pos           (8UL)                     /*!< SCU PLLCON: POSTDIV1 (Bit 8)                          */
#define SCU_PLLCON_POSTDIV1_Msk           (0xff00UL)                /*!< SCU PLLCON: POSTDIV1 (Bitfield-Mask: 0xff)            */
#define SCU_PLLCON_POSTDIV2_Pos           (4UL)                     /*!< SCU PLLCON: POSTDIV2 (Bit 4)                          */
#define SCU_PLLCON_POSTDIV2_Msk           (0xf0UL)                  /*!< SCU PLLCON: POSTDIV2 (Bitfield-Mask: 0x0f)            */
#define SCU_PLLCON_OUTDIV_Pos             (0UL)                     /*!< SCU PLLCON: OUTDIV (Bit 0)                            */
#define SCU_PLLCON_OUTDIV_Msk             (0x7UL)                   /*!< SCU PLLCON: OUTDIV (Bitfield-Mask: 0x07)              */
/* ========================================================  VDCCON  ========================================================= */
#define SCU_VDCCON_VDC_WTIDKY_Pos         (20UL)                    /*!< SCU VDCCON: VDC_WTIDKY (Bit 20)                       */
#define SCU_VDCCON_VDC_WTIDKY_Msk         (0xf00000UL)              /*!< SCU VDCCON: VDC_WTIDKY (Bitfield-Mask: 0x0f)          */
#define SCU_VDCCON_VDC_PDBGR_Pos          (19UL)                    /*!< SCU VDCCON: VDC_PDBGR (Bit 19)                        */
#define SCU_VDCCON_VDC_PDBGR_Msk          (0x80000UL)               /*!< SCU VDCCON: VDC_PDBGR (Bitfield-Mask: 0x01)           */
#define SCU_VDCCON_VDC_STOP_Pos           (17UL)                    /*!< SCU VDCCON: VDC_STOP (Bit 17)                         */
#define SCU_VDCCON_VDC_STOP_Msk           (0x20000UL)               /*!< SCU VDCCON: VDC_STOP (Bitfield-Mask: 0x01)            */
#define SCU_VDCCON_VDC_IDLE_Pos           (16UL)                    /*!< SCU VDCCON: VDC_IDLE (Bit 16)                         */
#define SCU_VDCCON_VDC_IDLE_Msk           (0x10000UL)               /*!< SCU VDCCON: VDC_IDLE (Bitfield-Mask: 0x01)            */
#define SCU_VDCCON_VDC_LOCK_Pos           (15UL)                    /*!< SCU VDCCON: VDC_LOCK (Bit 15)                         */
#define SCU_VDCCON_VDC_LOCK_Msk           (0x8000UL)                /*!< SCU VDCCON: VDC_LOCK (Bitfield-Mask: 0x01)            */
#define SCU_VDCCON_VDCWDLY_WEN_Pos        (8UL)                     /*!< SCU VDCCON: VDCWDLY_WEN (Bit 8)                       */
#define SCU_VDCCON_VDCWDLY_WEN_Msk        (0x100UL)                 /*!< SCU VDCCON: VDCWDLY_WEN (Bitfield-Mask: 0x01)         */
#define SCU_VDCCON_VDCWDLY_Pos            (0UL)                     /*!< SCU VDCCON: VDCWDLY (Bit 0)                           */
#define SCU_VDCCON_VDCWDLY_Msk            (0xffUL)                  /*!< SCU VDCCON: VDCWDLY (Bitfield-Mask: 0xff)             */
/* ========================================================  LSICON  ========================================================= */
#define SCU_LSICON_SKIP_LS_Pos            (0UL)                     /*!< SCU LSICON: SKIP_LS (Bit 0)                           */
#define SCU_LSICON_SKIP_LS_Msk            (0x1UL)                   /*!< SCU LSICON: SKIP_LS (Bitfield-Mask: 0x01)             */
/* =========================================================  EOSCR  ========================================================= */
#define SCU_EOSCR_ESEN_Pos                (15UL)                    /*!< SCU EOSCR: ESEN (Bit 15)                              */
#define SCU_EOSCR_ESEN_Msk                (0x8000UL)                /*!< SCU EOSCR: ESEN (Bitfield-Mask: 0x01)                 */
#define SCU_EOSCR_ESISEL_Pos              (12UL)                    /*!< SCU EOSCR: ESISEL (Bit 12)                            */
#define SCU_EOSCR_ESISEL_Msk              (0x3000UL)                /*!< SCU EOSCR: ESISEL (Bitfield-Mask: 0x03)               */
#define SCU_EOSCR_ESNCBYPS_Pos            (8UL)                     /*!< SCU EOSCR: ESNCBYPS (Bit 8)                           */
#define SCU_EOSCR_ESNCBYPS_Msk            (0x100UL)                 /*!< SCU EOSCR: ESNCBYPS (Bitfield-Mask: 0x01)             */
#define SCU_EOSCR_EMEN_Pos                (7UL)                     /*!< SCU EOSCR: EMEN (Bit 7)                               */
#define SCU_EOSCR_EMEN_Msk                (0x80UL)                  /*!< SCU EOSCR: EMEN (Bitfield-Mask: 0x01)                 */
#define SCU_EOSCR_ISE_Pos                 (4UL)                     /*!< SCU EOSCR: ISE (Bit 4)                                */
#define SCU_EOSCR_ISE_Msk                 (0x30UL)                  /*!< SCU EOSCR: ISE (Bitfield-Mask: 0x03)                  */
#define SCU_EOSCR_NCOPT_Pos               (2UL)                     /*!< SCU EOSCR: NCOPT (Bit 2)                              */
#define SCU_EOSCR_NCOPT_Msk               (0xcUL)                   /*!< SCU EOSCR: NCOPT (Bitfield-Mask: 0x03)                */
#define SCU_EOSCR_NCSKIP_Pos              (0UL)                     /*!< SCU EOSCR: NCSKIP (Bit 0)                             */
#define SCU_EOSCR_NCSKIP_Msk              (0x1UL)                   /*!< SCU EOSCR: NCSKIP (Bitfield-Mask: 0x01)               */
/* =========================================================  EMODR  ========================================================= */
#define SCU_EMODR_BOOT_Pos                (0UL)                     /*!< SCU EMODR: BOOT (Bit 0)                               */
#define SCU_EMODR_BOOT_Msk                (0x1UL)                   /*!< SCU EMODR: BOOT (Bitfield-Mask: 0x01)                 */
/* ========================================================  RSTDBCR  ======================================================== */
#define SCU_RSTDBCR_WTIDKY_Pos            (16UL)                    /*!< SCU RSTDBCR: WTIDKY (Bit 16)                          */
#define SCU_RSTDBCR_WTIDKY_Msk            (0xffff0000UL)            /*!< SCU RSTDBCR: WTIDKY (Bitfield-Mask: 0xffff)           */
#define SCU_RSTDBCR_CLKCNT_Pos            (8UL)                     /*!< SCU RSTDBCR: CLKCNT (Bit 8)                           */
#define SCU_RSTDBCR_CLKCNT_Msk            (0x3f00UL)                /*!< SCU RSTDBCR: CLKCNT (Bitfield-Mask: 0x3f)             */
#define SCU_RSTDBCR_EN_Pos                (0UL)                     /*!< SCU RSTDBCR: EN (Bit 0)                               */
#define SCU_RSTDBCR_EN_Msk                (0x1UL)                   /*!< SCU RSTDBCR: EN (Bitfield-Mask: 0x01)                 */
/* =========================================================  MCCR1  ========================================================= */
#define SCU_MCCR1_TEXT1CSEL_Pos           (24UL)                    /*!< SCU MCCR1: TEXT1CSEL (Bit 24)                         */
#define SCU_MCCR1_TEXT1CSEL_Msk           (0x7000000UL)             /*!< SCU MCCR1: TEXT1CSEL (Bitfield-Mask: 0x07)            */
#define SCU_MCCR1_TEXT1DIV_Pos            (16UL)                    /*!< SCU MCCR1: TEXT1DIV (Bit 16)                          */
#define SCU_MCCR1_TEXT1DIV_Msk            (0xff0000UL)              /*!< SCU MCCR1: TEXT1DIV (Bitfield-Mask: 0xff)             */
#define SCU_MCCR1_STCSEL_Pos              (8UL)                     /*!< SCU MCCR1: STCSEL (Bit 8)                             */
#define SCU_MCCR1_STCSEL_Msk              (0x700UL)                 /*!< SCU MCCR1: STCSEL (Bitfield-Mask: 0x07)               */
#define SCU_MCCR1_STDIV_Pos               (0UL)                     /*!< SCU MCCR1: STDIV (Bit 0)                              */
#define SCU_MCCR1_STDIV_Msk               (0xffUL)                  /*!< SCU MCCR1: STDIV (Bitfield-Mask: 0xff)                */
/* =========================================================  MCCR2  ========================================================= */
#define SCU_MCCR2_TEXT3CSEL_Pos           (24UL)                    /*!< SCU MCCR2: TEXT3CSEL (Bit 24)                         */
#define SCU_MCCR2_TEXT3CSEL_Msk           (0x7000000UL)             /*!< SCU MCCR2: TEXT3CSEL (Bitfield-Mask: 0x07)            */
#define SCU_MCCR2_TEXT3DIV_Pos            (16UL)                    /*!< SCU MCCR2: TEXT3DIV (Bit 16)                          */
#define SCU_MCCR2_TEXT3DIV_Msk            (0xff0000UL)              /*!< SCU MCCR2: TEXT3DIV (Bitfield-Mask: 0xff)             */
#define SCU_MCCR2_TEXT2CSEL_Pos           (8UL)                     /*!< SCU MCCR2: TEXT2CSEL (Bit 8)                          */
#define SCU_MCCR2_TEXT2CSEL_Msk           (0x700UL)                 /*!< SCU MCCR2: TEXT2CSEL (Bitfield-Mask: 0x07)            */
#define SCU_MCCR2_TEXT2DIV_Pos            (0UL)                     /*!< SCU MCCR2: TEXT2DIV (Bit 0)                           */
#define SCU_MCCR2_TEXT2DIV_Msk            (0xffUL)                  /*!< SCU MCCR2: TEXT2DIV (Bitfield-Mask: 0xff)             */
/* =========================================================  MCCR3  ========================================================= */
#define SCU_MCCR3_WTEXTCSEL_Pos           (24UL)                    /*!< SCU MCCR3: WTEXTCSEL (Bit 24)                         */
#define SCU_MCCR3_WTEXTCSEL_Msk           (0x7000000UL)             /*!< SCU MCCR3: WTEXTCSEL (Bitfield-Mask: 0x07)            */
#define SCU_MCCR3_WTEXTCDIV_Pos           (16UL)                    /*!< SCU MCCR3: WTEXTCDIV (Bit 16)                         */
#define SCU_MCCR3_WTEXTCDIV_Msk           (0xff0000UL)              /*!< SCU MCCR3: WTEXTCDIV (Bitfield-Mask: 0xff)            */
#define SCU_MCCR3_WDTCSEL_Pos             (8UL)                     /*!< SCU MCCR3: WDTCSEL (Bit 8)                            */
#define SCU_MCCR3_WDTCSEL_Msk             (0x700UL)                 /*!< SCU MCCR3: WDTCSEL (Bitfield-Mask: 0x07)              */
#define SCU_MCCR3_WDTDIV_Pos              (0UL)                     /*!< SCU MCCR3: WDTDIV (Bit 0)                             */
#define SCU_MCCR3_WDTDIV_Msk              (0xffUL)                  /*!< SCU MCCR3: WDTDIV (Bitfield-Mask: 0xff)               */
/* =========================================================  MCCR4  ========================================================= */
#define SCU_MCCR4_PD1CSEL_Pos             (24UL)                    /*!< SCU MCCR4: PD1CSEL (Bit 24)                           */
#define SCU_MCCR4_PD1CSEL_Msk             (0x7000000UL)             /*!< SCU MCCR4: PD1CSEL (Bitfield-Mask: 0x07)              */
#define SCU_MCCR4_PD1DIV_Pos              (16UL)                    /*!< SCU MCCR4: PD1DIV (Bit 16)                            */
#define SCU_MCCR4_PD1DIV_Msk              (0xff0000UL)              /*!< SCU MCCR4: PD1DIV (Bitfield-Mask: 0xff)               */
#define SCU_MCCR4_PD0CSEL_Pos             (8UL)                     /*!< SCU MCCR4: PD0CSEL (Bit 8)                            */
#define SCU_MCCR4_PD0CSEL_Msk             (0x700UL)                 /*!< SCU MCCR4: PD0CSEL (Bitfield-Mask: 0x07)              */
#define SCU_MCCR4_PD0DIV_Pos              (0UL)                     /*!< SCU MCCR4: PD0DIV (Bit 0)                             */
#define SCU_MCCR4_PD0DIV_Msk              (0xffUL)                  /*!< SCU MCCR4: PD0DIV (Bitfield-Mask: 0xff)               */
/* =========================================================  MCCR5  ========================================================= */
#define SCU_MCCR5_LCDCSEL_Pos             (24UL)                    /*!< SCU MCCR5: LCDCSEL (Bit 24)                           */
#define SCU_MCCR5_LCDCSEL_Msk             (0x7000000UL)             /*!< SCU MCCR5: LCDCSEL (Bitfield-Mask: 0x07)              */
#define SCU_MCCR5_LCDDIV_Pos              (16UL)                    /*!< SCU MCCR5: LCDDIV (Bit 16)                            */
#define SCU_MCCR5_LCDDIV_Msk              (0xff0000UL)              /*!< SCU MCCR5: LCDDIV (Bitfield-Mask: 0xff)               */
#define SCU_MCCR5_TSRCSEL_Pos             (14UL)                    /*!< SCU MCCR5: TSRCSEL (Bit 14)                           */
#define SCU_MCCR5_TSRCSEL_Msk             (0xc000UL)                /*!< SCU MCCR5: TSRCSEL (Bitfield-Mask: 0x03)              */
#define SCU_MCCR5_TSSCSEL_Pos             (12UL)                    /*!< SCU MCCR5: TSSCSEL (Bit 12)                           */
#define SCU_MCCR5_TSSCSEL_Msk             (0x3000UL)                /*!< SCU MCCR5: TSSCSEL (Bitfield-Mask: 0x03)              */
#define SCU_MCCR5_TSSLSITSEN_Pos          (11UL)                    /*!< SCU MCCR5: TSSLSITSEN (Bit 11)                        */
#define SCU_MCCR5_TSSLSITSEN_Msk          (0x800UL)                 /*!< SCU MCCR5: TSSLSITSEN (Bitfield-Mask: 0x01)           */
/* =========================================================  MCCR6  ========================================================= */
/* =========================================================  MCCR7  ========================================================= */
#define SCU_MCCR7_ADCCSEL_Pos             (24UL)                    /*!< SCU MCCR7: ADCCSEL (Bit 24)                           */
#define SCU_MCCR7_ADCCSEL_Msk             (0x7000000UL)             /*!< SCU MCCR7: ADCCSEL (Bitfield-Mask: 0x07)              */
#define SCU_MCCR7_ADCCDIV_Pos             (16UL)                    /*!< SCU MCCR7: ADCCDIV (Bit 16)                           */
#define SCU_MCCR7_ADCCDIV_Msk             (0xff0000UL)              /*!< SCU MCCR7: ADCCDIV (Bitfield-Mask: 0xff)              */


/* =========================================================================================================================== */
/* ================                                           SCULV                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  LVICR  ========================================================= */
#define SCULV_LVICR_LVIFLAG_Pos           (8UL)                     /*!< SCULV LVICR: LVIFLAG (Bit 8)                          */
#define SCULV_LVICR_LVIFLAG_Msk           (0x100UL)                 /*!< SCULV LVICR: LVIFLAG (Bitfield-Mask: 0x01)            */
#define SCULV_LVICR_LVIEN_Pos             (7UL)                     /*!< SCULV LVICR: LVIEN (Bit 7)                            */
#define SCULV_LVICR_LVIEN_Msk             (0x80UL)                  /*!< SCULV LVICR: LVIEN (Bitfield-Mask: 0x01)              */
#define SCULV_LVICR_LVINTEN_Pos           (5UL)                     /*!< SCULV LVICR: LVINTEN (Bit 5)                          */
#define SCULV_LVICR_LVINTEN_Msk           (0x20UL)                  /*!< SCULV LVICR: LVINTEN (Bitfield-Mask: 0x01)            */
#define SCULV_LVICR_LVIST_Pos             (4UL)                     /*!< SCULV LVICR: LVIST (Bit 4)                            */
#define SCULV_LVICR_LVIST_Msk             (0x10UL)                  /*!< SCULV LVICR: LVIST (Bitfield-Mask: 0x01)              */
#define SCULV_LVICR_LVIVS_Pos             (0UL)                     /*!< SCULV LVICR: LVIVS (Bit 0)                            */
#define SCULV_LVICR_LVIVS_Msk             (0xfUL)                   /*!< SCULV LVICR: LVIVS (Bitfield-Mask: 0x0f)              */
/* =========================================================  LVRCR  ========================================================= */
#define SCULV_LVRCR_LVREN_Pos             (0UL)                     /*!< SCULV LVRCR: LVREN (Bit 0)                            */
#define SCULV_LVRCR_LVREN_Msk             (0xffUL)                  /*!< SCULV LVRCR: LVREN (Bitfield-Mask: 0xff)              */
/* =======================================================  LVRCNFIG  ======================================================== */
#define SCULV_LVRCNFIG_WTIDKY_Pos         (16UL)                    /*!< SCULV LVRCNFIG: WTIDKY (Bit 16)                       */
#define SCULV_LVRCNFIG_WTIDKY_Msk         (0xffff0000UL)            /*!< SCULV LVRCNFIG: WTIDKY (Bitfield-Mask: 0xffff)        */
#define SCULV_LVRCNFIG_LVRENM_Pos         (8UL)                     /*!< SCULV LVRCNFIG: LVRENM (Bit 8)                        */
#define SCULV_LVRCNFIG_LVRENM_Msk         (0xff00UL)                /*!< SCULV LVRCNFIG: LVRENM (Bitfield-Mask: 0xff)          */
#define SCULV_LVRCNFIG_LVRVS_Pos          (0UL)                     /*!< SCULV LVRCNFIG: LVRVS (Bit 0)                         */
#define SCULV_LVRCNFIG_LVRVS_Msk          (0xfUL)                   /*!< SCULV LVRCNFIG: LVRVS (Bitfield-Mask: 0x0f)           */


/* =========================================================================================================================== */
/* ================                                           PORT                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  MOD  ========================================================== */
#define PORT_MOD_MODE15_Pos               (30UL)                    /*!< PORT MOD: MODE15 (Bit 30)                             */
#define PORT_MOD_MODE15_Msk               (0xc0000000UL)            /*!< PORT MOD: MODE15 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE14_Pos               (28UL)                    /*!< PORT MOD: MODE14 (Bit 28)                             */
#define PORT_MOD_MODE14_Msk               (0x30000000UL)            /*!< PORT MOD: MODE14 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE13_Pos               (26UL)                    /*!< PORT MOD: MODE13 (Bit 26)                             */
#define PORT_MOD_MODE13_Msk               (0xc000000UL)             /*!< PORT MOD: MODE13 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE12_Pos               (24UL)                    /*!< PORT MOD: MODE12 (Bit 24)                             */
#define PORT_MOD_MODE12_Msk               (0x3000000UL)             /*!< PORT MOD: MODE12 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE11_Pos               (22UL)                    /*!< PORT MOD: MODE11 (Bit 22)                             */
#define PORT_MOD_MODE11_Msk               (0xc00000UL)              /*!< PORT MOD: MODE11 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE10_Pos               (20UL)                    /*!< PORT MOD: MODE10 (Bit 20)                             */
#define PORT_MOD_MODE10_Msk               (0x300000UL)              /*!< PORT MOD: MODE10 (Bitfield-Mask: 0x03)                */
#define PORT_MOD_MODE9_Pos                (18UL)                    /*!< PORT MOD: MODE9 (Bit 18)                              */
#define PORT_MOD_MODE9_Msk                (0xc0000UL)               /*!< PORT MOD: MODE9 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE8_Pos                (16UL)                    /*!< PORT MOD: MODE8 (Bit 16)                              */
#define PORT_MOD_MODE8_Msk                (0x30000UL)               /*!< PORT MOD: MODE8 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE7_Pos                (14UL)                    /*!< PORT MOD: MODE7 (Bit 14)                              */
#define PORT_MOD_MODE7_Msk                (0xc000UL)                /*!< PORT MOD: MODE7 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE6_Pos                (12UL)                    /*!< PORT MOD: MODE6 (Bit 12)                              */
#define PORT_MOD_MODE6_Msk                (0x3000UL)                /*!< PORT MOD: MODE6 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE5_Pos                (10UL)                    /*!< PORT MOD: MODE5 (Bit 10)                              */
#define PORT_MOD_MODE5_Msk                (0xc00UL)                 /*!< PORT MOD: MODE5 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE4_Pos                (8UL)                     /*!< PORT MOD: MODE4 (Bit 8)                               */
#define PORT_MOD_MODE4_Msk                (0x300UL)                 /*!< PORT MOD: MODE4 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE3_Pos                (6UL)                     /*!< PORT MOD: MODE3 (Bit 6)                               */
#define PORT_MOD_MODE3_Msk                (0xc0UL)                  /*!< PORT MOD: MODE3 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE2_Pos                (4UL)                     /*!< PORT MOD: MODE2 (Bit 4)                               */
#define PORT_MOD_MODE2_Msk                (0x30UL)                  /*!< PORT MOD: MODE2 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE1_Pos                (2UL)                     /*!< PORT MOD: MODE1 (Bit 2)                               */
#define PORT_MOD_MODE1_Msk                (0xcUL)                   /*!< PORT MOD: MODE1 (Bitfield-Mask: 0x03)                 */
#define PORT_MOD_MODE0_Pos                (0UL)                     /*!< PORT MOD: MODE0 (Bit 0)                               */
#define PORT_MOD_MODE0_Msk                (0x3UL)                   /*!< PORT MOD: MODE0 (Bitfield-Mask: 0x03)                 */
/* ==========================================================  TYP  ========================================================== */
#define PORT_TYP_TYP15_Pos                (15UL)                    /*!< PORT TYP: TYP15 (Bit 15)                              */
#define PORT_TYP_TYP15_Msk                (0x8000UL)                /*!< PORT TYP: TYP15 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP14_Pos                (14UL)                    /*!< PORT TYP: TYP14 (Bit 14)                              */
#define PORT_TYP_TYP14_Msk                (0x4000UL)                /*!< PORT TYP: TYP14 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP13_Pos                (13UL)                    /*!< PORT TYP: TYP13 (Bit 13)                              */
#define PORT_TYP_TYP13_Msk                (0x2000UL)                /*!< PORT TYP: TYP13 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP12_Pos                (12UL)                    /*!< PORT TYP: TYP12 (Bit 12)                              */
#define PORT_TYP_TYP12_Msk                (0x1000UL)                /*!< PORT TYP: TYP12 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP11_Pos                (11UL)                    /*!< PORT TYP: TYP11 (Bit 11)                              */
#define PORT_TYP_TYP11_Msk                (0x800UL)                 /*!< PORT TYP: TYP11 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP10_Pos                (10UL)                    /*!< PORT TYP: TYP10 (Bit 10)                              */
#define PORT_TYP_TYP10_Msk                (0x400UL)                 /*!< PORT TYP: TYP10 (Bitfield-Mask: 0x01)                 */
#define PORT_TYP_TYP9_Pos                 (9UL)                     /*!< PORT TYP: TYP9 (Bit 9)                                */
#define PORT_TYP_TYP9_Msk                 (0x200UL)                 /*!< PORT TYP: TYP9 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP8_Pos                 (8UL)                     /*!< PORT TYP: TYP8 (Bit 8)                                */
#define PORT_TYP_TYP8_Msk                 (0x100UL)                 /*!< PORT TYP: TYP8 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP7_Pos                 (7UL)                     /*!< PORT TYP: TYP7 (Bit 7)                                */
#define PORT_TYP_TYP7_Msk                 (0x80UL)                  /*!< PORT TYP: TYP7 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP6_Pos                 (6UL)                     /*!< PORT TYP: TYP6 (Bit 6)                                */
#define PORT_TYP_TYP6_Msk                 (0x40UL)                  /*!< PORT TYP: TYP6 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP5_Pos                 (5UL)                     /*!< PORT TYP: TYP5 (Bit 5)                                */
#define PORT_TYP_TYP5_Msk                 (0x20UL)                  /*!< PORT TYP: TYP5 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP4_Pos                 (4UL)                     /*!< PORT TYP: TYP4 (Bit 4)                                */
#define PORT_TYP_TYP4_Msk                 (0x10UL)                  /*!< PORT TYP: TYP4 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP3_Pos                 (3UL)                     /*!< PORT TYP: TYP3 (Bit 3)                                */
#define PORT_TYP_TYP3_Msk                 (0x8UL)                   /*!< PORT TYP: TYP3 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP2_Pos                 (2UL)                     /*!< PORT TYP: TYP2 (Bit 2)                                */
#define PORT_TYP_TYP2_Msk                 (0x4UL)                   /*!< PORT TYP: TYP2 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP1_Pos                 (1UL)                     /*!< PORT TYP: TYP1 (Bit 1)                                */
#define PORT_TYP_TYP1_Msk                 (0x2UL)                   /*!< PORT TYP: TYP1 (Bitfield-Mask: 0x01)                  */
#define PORT_TYP_TYP0_Pos                 (0UL)                     /*!< PORT TYP: TYP0 (Bit 0)                                */
#define PORT_TYP_TYP0_Msk                 (0x1UL)                   /*!< PORT TYP: TYP0 (Bitfield-Mask: 0x01)                  */
/* =========================================================  AFSR1  ========================================================= */
#define PORT_AFSR1_AFSR7_Pos              (28UL)                    /*!< PORT AFSR1: AFSR7 (Bit 28)                            */
#define PORT_AFSR1_AFSR7_Msk              (0xf0000000UL)            /*!< PORT AFSR1: AFSR7 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR6_Pos              (24UL)                    /*!< PORT AFSR1: AFSR6 (Bit 24)                            */
#define PORT_AFSR1_AFSR6_Msk              (0xf000000UL)             /*!< PORT AFSR1: AFSR6 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR5_Pos              (20UL)                    /*!< PORT AFSR1: AFSR5 (Bit 20)                            */
#define PORT_AFSR1_AFSR5_Msk              (0xf00000UL)              /*!< PORT AFSR1: AFSR5 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR4_Pos              (16UL)                    /*!< PORT AFSR1: AFSR4 (Bit 16)                            */
#define PORT_AFSR1_AFSR4_Msk              (0xf0000UL)               /*!< PORT AFSR1: AFSR4 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR3_Pos              (12UL)                    /*!< PORT AFSR1: AFSR3 (Bit 12)                            */
#define PORT_AFSR1_AFSR3_Msk              (0xf000UL)                /*!< PORT AFSR1: AFSR3 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR2_Pos              (8UL)                     /*!< PORT AFSR1: AFSR2 (Bit 8)                             */
#define PORT_AFSR1_AFSR2_Msk              (0xf00UL)                 /*!< PORT AFSR1: AFSR2 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR1_Pos              (4UL)                     /*!< PORT AFSR1: AFSR1 (Bit 4)                             */
#define PORT_AFSR1_AFSR1_Msk              (0xf0UL)                  /*!< PORT AFSR1: AFSR1 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR1_AFSR0_Pos              (0UL)                     /*!< PORT AFSR1: AFSR0 (Bit 0)                             */
#define PORT_AFSR1_AFSR0_Msk              (0xfUL)                   /*!< PORT AFSR1: AFSR0 (Bitfield-Mask: 0x0f)               */
/* =========================================================  AFSR2  ========================================================= */
#define PORT_AFSR2_AFSR15_Pos             (28UL)                    /*!< PORT AFSR2: AFSR15 (Bit 28)                           */
#define PORT_AFSR2_AFSR15_Msk             (0xf0000000UL)            /*!< PORT AFSR2: AFSR15 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR14_Pos             (24UL)                    /*!< PORT AFSR2: AFSR14 (Bit 24)                           */
#define PORT_AFSR2_AFSR14_Msk             (0xf000000UL)             /*!< PORT AFSR2: AFSR14 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR13_Pos             (20UL)                    /*!< PORT AFSR2: AFSR13 (Bit 20)                           */
#define PORT_AFSR2_AFSR13_Msk             (0xf00000UL)              /*!< PORT AFSR2: AFSR13 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR12_Pos             (16UL)                    /*!< PORT AFSR2: AFSR12 (Bit 16)                           */
#define PORT_AFSR2_AFSR12_Msk             (0xf0000UL)               /*!< PORT AFSR2: AFSR12 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR11_Pos             (12UL)                    /*!< PORT AFSR2: AFSR11 (Bit 12)                           */
#define PORT_AFSR2_AFSR11_Msk             (0xf000UL)                /*!< PORT AFSR2: AFSR11 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR10_Pos             (8UL)                     /*!< PORT AFSR2: AFSR10 (Bit 8)                            */
#define PORT_AFSR2_AFSR10_Msk             (0xf00UL)                 /*!< PORT AFSR2: AFSR10 (Bitfield-Mask: 0x0f)              */
#define PORT_AFSR2_AFSR9_Pos              (4UL)                     /*!< PORT AFSR2: AFSR9 (Bit 4)                             */
#define PORT_AFSR2_AFSR9_Msk              (0xf0UL)                  /*!< PORT AFSR2: AFSR9 (Bitfield-Mask: 0x0f)               */
#define PORT_AFSR2_AFSR8_Pos              (0UL)                     /*!< PORT AFSR2: AFSR8 (Bit 0)                             */
#define PORT_AFSR2_AFSR8_Msk              (0xfUL)                   /*!< PORT AFSR2: AFSR8 (Bitfield-Mask: 0x0f)               */
/* =========================================================  PUPD  ========================================================== */
#define PORT_PUPD_PUPD15_Pos              (30UL)                    /*!< PORT PUPD: PUPD15 (Bit 30)                            */
#define PORT_PUPD_PUPD15_Msk              (0xc0000000UL)            /*!< PORT PUPD: PUPD15 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD14_Pos              (28UL)                    /*!< PORT PUPD: PUPD14 (Bit 28)                            */
#define PORT_PUPD_PUPD14_Msk              (0x30000000UL)            /*!< PORT PUPD: PUPD14 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD13_Pos              (26UL)                    /*!< PORT PUPD: PUPD13 (Bit 26)                            */
#define PORT_PUPD_PUPD13_Msk              (0xc000000UL)             /*!< PORT PUPD: PUPD13 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD12_Pos              (24UL)                    /*!< PORT PUPD: PUPD12 (Bit 24)                            */
#define PORT_PUPD_PUPD12_Msk              (0x3000000UL)             /*!< PORT PUPD: PUPD12 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD11_Pos              (22UL)                    /*!< PORT PUPD: PUPD11 (Bit 22)                            */
#define PORT_PUPD_PUPD11_Msk              (0xc00000UL)              /*!< PORT PUPD: PUPD11 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD10_Pos              (20UL)                    /*!< PORT PUPD: PUPD10 (Bit 20)                            */
#define PORT_PUPD_PUPD10_Msk              (0x300000UL)              /*!< PORT PUPD: PUPD10 (Bitfield-Mask: 0x03)               */
#define PORT_PUPD_PUPD9_Pos               (18UL)                    /*!< PORT PUPD: PUPD9 (Bit 18)                             */
#define PORT_PUPD_PUPD9_Msk               (0xc0000UL)               /*!< PORT PUPD: PUPD9 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD8_Pos               (16UL)                    /*!< PORT PUPD: PUPD8 (Bit 16)                             */
#define PORT_PUPD_PUPD8_Msk               (0x30000UL)               /*!< PORT PUPD: PUPD8 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD7_Pos               (14UL)                    /*!< PORT PUPD: PUPD7 (Bit 14)                             */
#define PORT_PUPD_PUPD7_Msk               (0xc000UL)                /*!< PORT PUPD: PUPD7 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD6_Pos               (12UL)                    /*!< PORT PUPD: PUPD6 (Bit 12)                             */
#define PORT_PUPD_PUPD6_Msk               (0x3000UL)                /*!< PORT PUPD: PUPD6 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD5_Pos               (10UL)                    /*!< PORT PUPD: PUPD5 (Bit 10)                             */
#define PORT_PUPD_PUPD5_Msk               (0xc00UL)                 /*!< PORT PUPD: PUPD5 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD4_Pos               (8UL)                     /*!< PORT PUPD: PUPD4 (Bit 8)                              */
#define PORT_PUPD_PUPD4_Msk               (0x300UL)                 /*!< PORT PUPD: PUPD4 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD3_Pos               (6UL)                     /*!< PORT PUPD: PUPD3 (Bit 6)                              */
#define PORT_PUPD_PUPD3_Msk               (0xc0UL)                  /*!< PORT PUPD: PUPD3 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD2_Pos               (4UL)                     /*!< PORT PUPD: PUPD2 (Bit 4)                              */
#define PORT_PUPD_PUPD2_Msk               (0x30UL)                  /*!< PORT PUPD: PUPD2 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD1_Pos               (2UL)                     /*!< PORT PUPD: PUPD1 (Bit 2)                              */
#define PORT_PUPD_PUPD1_Msk               (0xcUL)                   /*!< PORT PUPD: PUPD1 (Bitfield-Mask: 0x03)                */
#define PORT_PUPD_PUPD0_Pos               (0UL)                     /*!< PORT PUPD: PUPD0 (Bit 0)                              */
#define PORT_PUPD_PUPD0_Msk               (0x3UL)                   /*!< PORT PUPD: PUPD0 (Bitfield-Mask: 0x03)                */
/* =========================================================  INDR  ========================================================== */
#define PORT_INDR_INDR15_Pos              (15UL)                    /*!< PORT INDR: INDR15 (Bit 15)                            */
#define PORT_INDR_INDR15_Msk              (0x8000UL)                /*!< PORT INDR: INDR15 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR14_Pos              (14UL)                    /*!< PORT INDR: INDR14 (Bit 14)                            */
#define PORT_INDR_INDR14_Msk              (0x4000UL)                /*!< PORT INDR: INDR14 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR13_Pos              (13UL)                    /*!< PORT INDR: INDR13 (Bit 13)                            */
#define PORT_INDR_INDR13_Msk              (0x2000UL)                /*!< PORT INDR: INDR13 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR12_Pos              (12UL)                    /*!< PORT INDR: INDR12 (Bit 12)                            */
#define PORT_INDR_INDR12_Msk              (0x1000UL)                /*!< PORT INDR: INDR12 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR11_Pos              (11UL)                    /*!< PORT INDR: INDR11 (Bit 11)                            */
#define PORT_INDR_INDR11_Msk              (0x800UL)                 /*!< PORT INDR: INDR11 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR10_Pos              (10UL)                    /*!< PORT INDR: INDR10 (Bit 10)                            */
#define PORT_INDR_INDR10_Msk              (0x400UL)                 /*!< PORT INDR: INDR10 (Bitfield-Mask: 0x01)               */
#define PORT_INDR_INDR9_Pos               (9UL)                     /*!< PORT INDR: INDR9 (Bit 9)                              */
#define PORT_INDR_INDR9_Msk               (0x200UL)                 /*!< PORT INDR: INDR9 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR8_Pos               (8UL)                     /*!< PORT INDR: INDR8 (Bit 8)                              */
#define PORT_INDR_INDR8_Msk               (0x100UL)                 /*!< PORT INDR: INDR8 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR7_Pos               (7UL)                     /*!< PORT INDR: INDR7 (Bit 7)                              */
#define PORT_INDR_INDR7_Msk               (0x80UL)                  /*!< PORT INDR: INDR7 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR6_Pos               (6UL)                     /*!< PORT INDR: INDR6 (Bit 6)                              */
#define PORT_INDR_INDR6_Msk               (0x40UL)                  /*!< PORT INDR: INDR6 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR5_Pos               (5UL)                     /*!< PORT INDR: INDR5 (Bit 5)                              */
#define PORT_INDR_INDR5_Msk               (0x20UL)                  /*!< PORT INDR: INDR5 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR4_Pos               (4UL)                     /*!< PORT INDR: INDR4 (Bit 4)                              */
#define PORT_INDR_INDR4_Msk               (0x10UL)                  /*!< PORT INDR: INDR4 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR3_Pos               (3UL)                     /*!< PORT INDR: INDR3 (Bit 3)                              */
#define PORT_INDR_INDR3_Msk               (0x8UL)                   /*!< PORT INDR: INDR3 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR2_Pos               (2UL)                     /*!< PORT INDR: INDR2 (Bit 2)                              */
#define PORT_INDR_INDR2_Msk               (0x4UL)                   /*!< PORT INDR: INDR2 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR1_Pos               (1UL)                     /*!< PORT INDR: INDR1 (Bit 1)                              */
#define PORT_INDR_INDR1_Msk               (0x2UL)                   /*!< PORT INDR: INDR1 (Bitfield-Mask: 0x01)                */
#define PORT_INDR_INDR0_Pos               (0UL)                     /*!< PORT INDR: INDR0 (Bit 0)                              */
#define PORT_INDR_INDR0_Msk               (0x1UL)                   /*!< PORT INDR: INDR0 (Bitfield-Mask: 0x01)                */
/* =========================================================  OUTDR  ========================================================= */
#define PORT_OUTDR_OUTDR15_Pos            (15UL)                    /*!< PORT OUTDR: OUTDR15 (Bit 15)                          */
#define PORT_OUTDR_OUTDR15_Msk            (0x8000UL)                /*!< PORT OUTDR: OUTDR15 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR14_Pos            (14UL)                    /*!< PORT OUTDR: OUTDR14 (Bit 14)                          */
#define PORT_OUTDR_OUTDR14_Msk            (0x4000UL)                /*!< PORT OUTDR: OUTDR14 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR13_Pos            (13UL)                    /*!< PORT OUTDR: OUTDR13 (Bit 13)                          */
#define PORT_OUTDR_OUTDR13_Msk            (0x2000UL)                /*!< PORT OUTDR: OUTDR13 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR12_Pos            (12UL)                    /*!< PORT OUTDR: OUTDR12 (Bit 12)                          */
#define PORT_OUTDR_OUTDR12_Msk            (0x1000UL)                /*!< PORT OUTDR: OUTDR12 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR11_Pos            (11UL)                    /*!< PORT OUTDR: OUTDR11 (Bit 11)                          */
#define PORT_OUTDR_OUTDR11_Msk            (0x800UL)                 /*!< PORT OUTDR: OUTDR11 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR10_Pos            (10UL)                    /*!< PORT OUTDR: OUTDR10 (Bit 10)                          */
#define PORT_OUTDR_OUTDR10_Msk            (0x400UL)                 /*!< PORT OUTDR: OUTDR10 (Bitfield-Mask: 0x01)             */
#define PORT_OUTDR_OUTDR9_Pos             (9UL)                     /*!< PORT OUTDR: OUTDR9 (Bit 9)                            */
#define PORT_OUTDR_OUTDR9_Msk             (0x200UL)                 /*!< PORT OUTDR: OUTDR9 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR8_Pos             (8UL)                     /*!< PORT OUTDR: OUTDR8 (Bit 8)                            */
#define PORT_OUTDR_OUTDR8_Msk             (0x100UL)                 /*!< PORT OUTDR: OUTDR8 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR7_Pos             (7UL)                     /*!< PORT OUTDR: OUTDR7 (Bit 7)                            */
#define PORT_OUTDR_OUTDR7_Msk             (0x80UL)                  /*!< PORT OUTDR: OUTDR7 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR6_Pos             (6UL)                     /*!< PORT OUTDR: OUTDR6 (Bit 6)                            */
#define PORT_OUTDR_OUTDR6_Msk             (0x40UL)                  /*!< PORT OUTDR: OUTDR6 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR5_Pos             (5UL)                     /*!< PORT OUTDR: OUTDR5 (Bit 5)                            */
#define PORT_OUTDR_OUTDR5_Msk             (0x20UL)                  /*!< PORT OUTDR: OUTDR5 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR4_Pos             (4UL)                     /*!< PORT OUTDR: OUTDR4 (Bit 4)                            */
#define PORT_OUTDR_OUTDR4_Msk             (0x10UL)                  /*!< PORT OUTDR: OUTDR4 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR3_Pos             (3UL)                     /*!< PORT OUTDR: OUTDR3 (Bit 3)                            */
#define PORT_OUTDR_OUTDR3_Msk             (0x8UL)                   /*!< PORT OUTDR: OUTDR3 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR2_Pos             (2UL)                     /*!< PORT OUTDR: OUTDR2 (Bit 2)                            */
#define PORT_OUTDR_OUTDR2_Msk             (0x4UL)                   /*!< PORT OUTDR: OUTDR2 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR1_Pos             (1UL)                     /*!< PORT OUTDR: OUTDR1 (Bit 1)                            */
#define PORT_OUTDR_OUTDR1_Msk             (0x2UL)                   /*!< PORT OUTDR: OUTDR1 (Bitfield-Mask: 0x01)              */
#define PORT_OUTDR_OUTDR0_Pos             (0UL)                     /*!< PORT OUTDR: OUTDR0 (Bit 0)                            */
#define PORT_OUTDR_OUTDR0_Msk             (0x1UL)                   /*!< PORT OUTDR: OUTDR0 (Bitfield-Mask: 0x01)              */
/* ==========================================================  BSR  ========================================================== */
#define PORT_BSR_BSR15_Pos                (15UL)                    /*!< PORT BSR: BSR15 (Bit 15)                              */
#define PORT_BSR_BSR15_Msk                (0x8000UL)                /*!< PORT BSR: BSR15 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR14_Pos                (14UL)                    /*!< PORT BSR: BSR14 (Bit 14)                              */
#define PORT_BSR_BSR14_Msk                (0x4000UL)                /*!< PORT BSR: BSR14 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR13_Pos                (13UL)                    /*!< PORT BSR: BSR13 (Bit 13)                              */
#define PORT_BSR_BSR13_Msk                (0x2000UL)                /*!< PORT BSR: BSR13 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR12_Pos                (12UL)                    /*!< PORT BSR: BSR12 (Bit 12)                              */
#define PORT_BSR_BSR12_Msk                (0x1000UL)                /*!< PORT BSR: BSR12 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR11_Pos                (11UL)                    /*!< PORT BSR: BSR11 (Bit 11)                              */
#define PORT_BSR_BSR11_Msk                (0x800UL)                 /*!< PORT BSR: BSR11 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR10_Pos                (10UL)                    /*!< PORT BSR: BSR10 (Bit 10)                              */
#define PORT_BSR_BSR10_Msk                (0x400UL)                 /*!< PORT BSR: BSR10 (Bitfield-Mask: 0x01)                 */
#define PORT_BSR_BSR9_Pos                 (9UL)                     /*!< PORT BSR: BSR9 (Bit 9)                                */
#define PORT_BSR_BSR9_Msk                 (0x200UL)                 /*!< PORT BSR: BSR9 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR8_Pos                 (8UL)                     /*!< PORT BSR: BSR8 (Bit 8)                                */
#define PORT_BSR_BSR8_Msk                 (0x100UL)                 /*!< PORT BSR: BSR8 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR7_Pos                 (7UL)                     /*!< PORT BSR: BSR7 (Bit 7)                                */
#define PORT_BSR_BSR7_Msk                 (0x80UL)                  /*!< PORT BSR: BSR7 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR6_Pos                 (6UL)                     /*!< PORT BSR: BSR6 (Bit 6)                                */
#define PORT_BSR_BSR6_Msk                 (0x40UL)                  /*!< PORT BSR: BSR6 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR5_Pos                 (5UL)                     /*!< PORT BSR: BSR5 (Bit 5)                                */
#define PORT_BSR_BSR5_Msk                 (0x20UL)                  /*!< PORT BSR: BSR5 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR4_Pos                 (4UL)                     /*!< PORT BSR: BSR4 (Bit 4)                                */
#define PORT_BSR_BSR4_Msk                 (0x10UL)                  /*!< PORT BSR: BSR4 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR3_Pos                 (3UL)                     /*!< PORT BSR: BSR3 (Bit 3)                                */
#define PORT_BSR_BSR3_Msk                 (0x8UL)                   /*!< PORT BSR: BSR3 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR2_Pos                 (2UL)                     /*!< PORT BSR: BSR2 (Bit 2)                                */
#define PORT_BSR_BSR2_Msk                 (0x4UL)                   /*!< PORT BSR: BSR2 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR1_Pos                 (1UL)                     /*!< PORT BSR: BSR1 (Bit 1)                                */
#define PORT_BSR_BSR1_Msk                 (0x2UL)                   /*!< PORT BSR: BSR1 (Bitfield-Mask: 0x01)                  */
#define PORT_BSR_BSR0_Pos                 (0UL)                     /*!< PORT BSR: BSR0 (Bit 0)                                */
#define PORT_BSR_BSR0_Msk                 (0x1UL)                   /*!< PORT BSR: BSR0 (Bitfield-Mask: 0x01)                  */
/* ==========================================================  BCR  ========================================================== */
#define PORT_BCR_BCR15_Pos                (15UL)                    /*!< PORT BCR: BCR15 (Bit 15)                              */
#define PORT_BCR_BCR15_Msk                (0x8000UL)                /*!< PORT BCR: BCR15 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR14_Pos                (14UL)                    /*!< PORT BCR: BCR14 (Bit 14)                              */
#define PORT_BCR_BCR14_Msk                (0x4000UL)                /*!< PORT BCR: BCR14 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR13_Pos                (13UL)                    /*!< PORT BCR: BCR13 (Bit 13)                              */
#define PORT_BCR_BCR13_Msk                (0x2000UL)                /*!< PORT BCR: BCR13 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR12_Pos                (12UL)                    /*!< PORT BCR: BCR12 (Bit 12)                              */
#define PORT_BCR_BCR12_Msk                (0x1000UL)                /*!< PORT BCR: BCR12 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR11_Pos                (11UL)                    /*!< PORT BCR: BCR11 (Bit 11)                              */
#define PORT_BCR_BCR11_Msk                (0x800UL)                 /*!< PORT BCR: BCR11 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR10_Pos                (10UL)                    /*!< PORT BCR: BCR10 (Bit 10)                              */
#define PORT_BCR_BCR10_Msk                (0x400UL)                 /*!< PORT BCR: BCR10 (Bitfield-Mask: 0x01)                 */
#define PORT_BCR_BCR9_Pos                 (9UL)                     /*!< PORT BCR: BCR9 (Bit 9)                                */
#define PORT_BCR_BCR9_Msk                 (0x200UL)                 /*!< PORT BCR: BCR9 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR8_Pos                 (8UL)                     /*!< PORT BCR: BCR8 (Bit 8)                                */
#define PORT_BCR_BCR8_Msk                 (0x100UL)                 /*!< PORT BCR: BCR8 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR7_Pos                 (7UL)                     /*!< PORT BCR: BCR7 (Bit 7)                                */
#define PORT_BCR_BCR7_Msk                 (0x80UL)                  /*!< PORT BCR: BCR7 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR6_Pos                 (6UL)                     /*!< PORT BCR: BCR6 (Bit 6)                                */
#define PORT_BCR_BCR6_Msk                 (0x40UL)                  /*!< PORT BCR: BCR6 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR5_Pos                 (5UL)                     /*!< PORT BCR: BCR5 (Bit 5)                                */
#define PORT_BCR_BCR5_Msk                 (0x20UL)                  /*!< PORT BCR: BCR5 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR4_Pos                 (4UL)                     /*!< PORT BCR: BCR4 (Bit 4)                                */
#define PORT_BCR_BCR4_Msk                 (0x10UL)                  /*!< PORT BCR: BCR4 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR3_Pos                 (3UL)                     /*!< PORT BCR: BCR3 (Bit 3)                                */
#define PORT_BCR_BCR3_Msk                 (0x8UL)                   /*!< PORT BCR: BCR3 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR2_Pos                 (2UL)                     /*!< PORT BCR: BCR2 (Bit 2)                                */
#define PORT_BCR_BCR2_Msk                 (0x4UL)                   /*!< PORT BCR: BCR2 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR1_Pos                 (1UL)                     /*!< PORT BCR: BCR1 (Bit 1)                                */
#define PORT_BCR_BCR1_Msk                 (0x2UL)                   /*!< PORT BCR: BCR1 (Bitfield-Mask: 0x01)                  */
#define PORT_BCR_BCR0_Pos                 (0UL)                     /*!< PORT BCR: BCR0 (Bit 0)                                */
#define PORT_BCR_BCR0_Msk                 (0x1UL)                   /*!< PORT BCR: BCR0 (Bitfield-Mask: 0x01)                  */
/* ========================================================  OUTDMSK  ======================================================== */
#define PORT_OUTDMSK_OUTDMSK15_Pos        (15UL)                    /*!< PORT OUTDMSK: OUTDMSK15 (Bit 15)                      */
#define PORT_OUTDMSK_OUTDMSK15_Msk        (0x8000UL)                /*!< PORT OUTDMSK: OUTDMSK15 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK14_Pos        (14UL)                    /*!< PORT OUTDMSK: OUTDMSK14 (Bit 14)                      */
#define PORT_OUTDMSK_OUTDMSK14_Msk        (0x4000UL)                /*!< PORT OUTDMSK: OUTDMSK14 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK13_Pos        (13UL)                    /*!< PORT OUTDMSK: OUTDMSK13 (Bit 13)                      */
#define PORT_OUTDMSK_OUTDMSK13_Msk        (0x2000UL)                /*!< PORT OUTDMSK: OUTDMSK13 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK12_Pos        (12UL)                    /*!< PORT OUTDMSK: OUTDMSK12 (Bit 12)                      */
#define PORT_OUTDMSK_OUTDMSK12_Msk        (0x1000UL)                /*!< PORT OUTDMSK: OUTDMSK12 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK11_Pos        (11UL)                    /*!< PORT OUTDMSK: OUTDMSK11 (Bit 11)                      */
#define PORT_OUTDMSK_OUTDMSK11_Msk        (0x800UL)                 /*!< PORT OUTDMSK: OUTDMSK11 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK10_Pos        (10UL)                    /*!< PORT OUTDMSK: OUTDMSK10 (Bit 10)                      */
#define PORT_OUTDMSK_OUTDMSK10_Msk        (0x400UL)                 /*!< PORT OUTDMSK: OUTDMSK10 (Bitfield-Mask: 0x01)         */
#define PORT_OUTDMSK_OUTDMSK9_Pos         (9UL)                     /*!< PORT OUTDMSK: OUTDMSK9 (Bit 9)                        */
#define PORT_OUTDMSK_OUTDMSK9_Msk         (0x200UL)                 /*!< PORT OUTDMSK: OUTDMSK9 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK8_Pos         (8UL)                     /*!< PORT OUTDMSK: OUTDMSK8 (Bit 8)                        */
#define PORT_OUTDMSK_OUTDMSK8_Msk         (0x100UL)                 /*!< PORT OUTDMSK: OUTDMSK8 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK7_Pos         (7UL)                     /*!< PORT OUTDMSK: OUTDMSK7 (Bit 7)                        */
#define PORT_OUTDMSK_OUTDMSK7_Msk         (0x80UL)                  /*!< PORT OUTDMSK: OUTDMSK7 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK6_Pos         (6UL)                     /*!< PORT OUTDMSK: OUTDMSK6 (Bit 6)                        */
#define PORT_OUTDMSK_OUTDMSK6_Msk         (0x40UL)                  /*!< PORT OUTDMSK: OUTDMSK6 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK5_Pos         (5UL)                     /*!< PORT OUTDMSK: OUTDMSK5 (Bit 5)                        */
#define PORT_OUTDMSK_OUTDMSK5_Msk         (0x20UL)                  /*!< PORT OUTDMSK: OUTDMSK5 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK4_Pos         (4UL)                     /*!< PORT OUTDMSK: OUTDMSK4 (Bit 4)                        */
#define PORT_OUTDMSK_OUTDMSK4_Msk         (0x10UL)                  /*!< PORT OUTDMSK: OUTDMSK4 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK3_Pos         (3UL)                     /*!< PORT OUTDMSK: OUTDMSK3 (Bit 3)                        */
#define PORT_OUTDMSK_OUTDMSK3_Msk         (0x8UL)                   /*!< PORT OUTDMSK: OUTDMSK3 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK2_Pos         (2UL)                     /*!< PORT OUTDMSK: OUTDMSK2 (Bit 2)                        */
#define PORT_OUTDMSK_OUTDMSK2_Msk         (0x4UL)                   /*!< PORT OUTDMSK: OUTDMSK2 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK1_Pos         (1UL)                     /*!< PORT OUTDMSK: OUTDMSK1 (Bit 1)                        */
#define PORT_OUTDMSK_OUTDMSK1_Msk         (0x2UL)                   /*!< PORT OUTDMSK: OUTDMSK1 (Bitfield-Mask: 0x01)          */
#define PORT_OUTDMSK_OUTDMSK0_Pos         (0UL)                     /*!< PORT OUTDMSK: OUTDMSK0 (Bit 0)                        */
#define PORT_OUTDMSK_OUTDMSK0_Msk         (0x1UL)                   /*!< PORT OUTDMSK: OUTDMSK0 (Bitfield-Mask: 0x01)          */
/* =========================================================  DBCR  ========================================================== */
#define PORT_DBCR_DBEN15_Pos              (15UL)                    /*!< PORT DBCR: DBEN15 (Bit 15)                            */
#define PORT_DBCR_DBEN15_Msk              (0x8000UL)                /*!< PORT DBCR: DBEN15 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN14_Pos              (14UL)                    /*!< PORT DBCR: DBEN14 (Bit 14)                            */
#define PORT_DBCR_DBEN14_Msk              (0x4000UL)                /*!< PORT DBCR: DBEN14 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN13_Pos              (13UL)                    /*!< PORT DBCR: DBEN13 (Bit 13)                            */
#define PORT_DBCR_DBEN13_Msk              (0x2000UL)                /*!< PORT DBCR: DBEN13 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN12_Pos              (12UL)                    /*!< PORT DBCR: DBEN12 (Bit 12)                            */
#define PORT_DBCR_DBEN12_Msk              (0x1000UL)                /*!< PORT DBCR: DBEN12 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN11_Pos              (11UL)                    /*!< PORT DBCR: DBEN11 (Bit 11)                            */
#define PORT_DBCR_DBEN11_Msk              (0x800UL)                 /*!< PORT DBCR: DBEN11 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN10_Pos              (10UL)                    /*!< PORT DBCR: DBEN10 (Bit 10)                            */
#define PORT_DBCR_DBEN10_Msk              (0x400UL)                 /*!< PORT DBCR: DBEN10 (Bitfield-Mask: 0x01)               */
#define PORT_DBCR_DBEN9_Pos               (9UL)                     /*!< PORT DBCR: DBEN9 (Bit 9)                              */
#define PORT_DBCR_DBEN9_Msk               (0x200UL)                 /*!< PORT DBCR: DBEN9 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN8_Pos               (8UL)                     /*!< PORT DBCR: DBEN8 (Bit 8)                              */
#define PORT_DBCR_DBEN8_Msk               (0x100UL)                 /*!< PORT DBCR: DBEN8 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN7_Pos               (7UL)                     /*!< PORT DBCR: DBEN7 (Bit 7)                              */
#define PORT_DBCR_DBEN7_Msk               (0x80UL)                  /*!< PORT DBCR: DBEN7 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN6_Pos               (6UL)                     /*!< PORT DBCR: DBEN6 (Bit 6)                              */
#define PORT_DBCR_DBEN6_Msk               (0x40UL)                  /*!< PORT DBCR: DBEN6 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN5_Pos               (5UL)                     /*!< PORT DBCR: DBEN5 (Bit 5)                              */
#define PORT_DBCR_DBEN5_Msk               (0x20UL)                  /*!< PORT DBCR: DBEN5 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN4_Pos               (4UL)                     /*!< PORT DBCR: DBEN4 (Bit 4)                              */
#define PORT_DBCR_DBEN4_Msk               (0x10UL)                  /*!< PORT DBCR: DBEN4 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN3_Pos               (3UL)                     /*!< PORT DBCR: DBEN3 (Bit 3)                              */
#define PORT_DBCR_DBEN3_Msk               (0x8UL)                   /*!< PORT DBCR: DBEN3 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN2_Pos               (2UL)                     /*!< PORT DBCR: DBEN2 (Bit 2)                              */
#define PORT_DBCR_DBEN2_Msk               (0x4UL)                   /*!< PORT DBCR: DBEN2 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN1_Pos               (1UL)                     /*!< PORT DBCR: DBEN1 (Bit 1)                              */
#define PORT_DBCR_DBEN1_Msk               (0x2UL)                   /*!< PORT DBCR: DBEN1 (Bitfield-Mask: 0x01)                */
#define PORT_DBCR_DBEN0_Pos               (0UL)                     /*!< PORT DBCR: DBEN0 (Bit 0)                              */
#define PORT_DBCR_DBEN0_Msk               (0x1UL)                   /*!< PORT DBCR: DBEN0 (Bitfield-Mask: 0x01)                */
/* ==========================================================  IER  ========================================================== */
#define PORT_IER_P15_Pos                  (30UL)                    /*!< PORT IER: P15 (Bit 30)                                */
#define PORT_IER_P15_Msk                  (0xc0000000UL)            /*!< PORT IER: P15 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P14_Pos                  (28UL)                    /*!< PORT IER: P14 (Bit 28)                                */
#define PORT_IER_P14_Msk                  (0x30000000UL)            /*!< PORT IER: P14 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P13_Pos                  (26UL)                    /*!< PORT IER: P13 (Bit 26)                                */
#define PORT_IER_P13_Msk                  (0xc000000UL)             /*!< PORT IER: P13 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P12_Pos                  (24UL)                    /*!< PORT IER: P12 (Bit 24)                                */
#define PORT_IER_P12_Msk                  (0x3000000UL)             /*!< PORT IER: P12 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P11_Pos                  (22UL)                    /*!< PORT IER: P11 (Bit 22)                                */
#define PORT_IER_P11_Msk                  (0xc00000UL)              /*!< PORT IER: P11 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P10_Pos                  (20UL)                    /*!< PORT IER: P10 (Bit 20)                                */
#define PORT_IER_P10_Msk                  (0x300000UL)              /*!< PORT IER: P10 (Bitfield-Mask: 0x03)                   */
#define PORT_IER_P9_Pos                   (18UL)                    /*!< PORT IER: P9 (Bit 18)                                 */
#define PORT_IER_P9_Msk                   (0xc0000UL)               /*!< PORT IER: P9 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P8_Pos                   (16UL)                    /*!< PORT IER: P8 (Bit 16)                                 */
#define PORT_IER_P8_Msk                   (0x30000UL)               /*!< PORT IER: P8 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P7_Pos                   (14UL)                    /*!< PORT IER: P7 (Bit 14)                                 */
#define PORT_IER_P7_Msk                   (0xc000UL)                /*!< PORT IER: P7 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P6_Pos                   (12UL)                    /*!< PORT IER: P6 (Bit 12)                                 */
#define PORT_IER_P6_Msk                   (0x3000UL)                /*!< PORT IER: P6 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P5_Pos                   (10UL)                    /*!< PORT IER: P5 (Bit 10)                                 */
#define PORT_IER_P5_Msk                   (0xc00UL)                 /*!< PORT IER: P5 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P4_Pos                   (8UL)                     /*!< PORT IER: P4 (Bit 8)                                  */
#define PORT_IER_P4_Msk                   (0x300UL)                 /*!< PORT IER: P4 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P3_Pos                   (6UL)                     /*!< PORT IER: P3 (Bit 6)                                  */
#define PORT_IER_P3_Msk                   (0xc0UL)                  /*!< PORT IER: P3 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P2_Pos                   (4UL)                     /*!< PORT IER: P2 (Bit 4)                                  */
#define PORT_IER_P2_Msk                   (0x30UL)                  /*!< PORT IER: P2 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P1_Pos                   (2UL)                     /*!< PORT IER: P1 (Bit 2)                                  */
#define PORT_IER_P1_Msk                   (0xcUL)                   /*!< PORT IER: P1 (Bitfield-Mask: 0x03)                    */
#define PORT_IER_P0_Pos                   (0UL)                     /*!< PORT IER: P0 (Bit 0)                                  */
#define PORT_IER_P0_Msk                   (0x3UL)                   /*!< PORT IER: P0 (Bitfield-Mask: 0x03)                    */
/* ==========================================================  ISR  ========================================================== */
#define PORT_ISR_P15_Pos                  (30UL)                    /*!< PORT ISR: P15 (Bit 30)                                */
#define PORT_ISR_P15_Msk                  (0xc0000000UL)            /*!< PORT ISR: P15 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P14_Pos                  (28UL)                    /*!< PORT ISR: P14 (Bit 28)                                */
#define PORT_ISR_P14_Msk                  (0x30000000UL)            /*!< PORT ISR: P14 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P13_Pos                  (26UL)                    /*!< PORT ISR: P13 (Bit 26)                                */
#define PORT_ISR_P13_Msk                  (0xc000000UL)             /*!< PORT ISR: P13 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P12_Pos                  (24UL)                    /*!< PORT ISR: P12 (Bit 24)                                */
#define PORT_ISR_P12_Msk                  (0x3000000UL)             /*!< PORT ISR: P12 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P11_Pos                  (22UL)                    /*!< PORT ISR: P11 (Bit 22)                                */
#define PORT_ISR_P11_Msk                  (0xc00000UL)              /*!< PORT ISR: P11 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P10_Pos                  (20UL)                    /*!< PORT ISR: P10 (Bit 20)                                */
#define PORT_ISR_P10_Msk                  (0x300000UL)              /*!< PORT ISR: P10 (Bitfield-Mask: 0x03)                   */
#define PORT_ISR_P9_Pos                   (18UL)                    /*!< PORT ISR: P9 (Bit 18)                                 */
#define PORT_ISR_P9_Msk                   (0xc0000UL)               /*!< PORT ISR: P9 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P8_Pos                   (16UL)                    /*!< PORT ISR: P8 (Bit 16)                                 */
#define PORT_ISR_P8_Msk                   (0x30000UL)               /*!< PORT ISR: P8 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P7_Pos                   (14UL)                    /*!< PORT ISR: P7 (Bit 14)                                 */
#define PORT_ISR_P7_Msk                   (0xc000UL)                /*!< PORT ISR: P7 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P6_Pos                   (12UL)                    /*!< PORT ISR: P6 (Bit 12)                                 */
#define PORT_ISR_P6_Msk                   (0x3000UL)                /*!< PORT ISR: P6 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P5_Pos                   (10UL)                    /*!< PORT ISR: P5 (Bit 10)                                 */
#define PORT_ISR_P5_Msk                   (0xc00UL)                 /*!< PORT ISR: P5 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P4_Pos                   (8UL)                     /*!< PORT ISR: P4 (Bit 8)                                  */
#define PORT_ISR_P4_Msk                   (0x300UL)                 /*!< PORT ISR: P4 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P3_Pos                   (6UL)                     /*!< PORT ISR: P3 (Bit 6)                                  */
#define PORT_ISR_P3_Msk                   (0xc0UL)                  /*!< PORT ISR: P3 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P2_Pos                   (4UL)                     /*!< PORT ISR: P2 (Bit 4)                                  */
#define PORT_ISR_P2_Msk                   (0x30UL)                  /*!< PORT ISR: P2 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P1_Pos                   (2UL)                     /*!< PORT ISR: P1 (Bit 2)                                  */
#define PORT_ISR_P1_Msk                   (0xcUL)                   /*!< PORT ISR: P1 (Bitfield-Mask: 0x03)                    */
#define PORT_ISR_P0_Pos                   (0UL)                     /*!< PORT ISR: P0 (Bit 0)                                  */
#define PORT_ISR_P0_Msk                   (0x3UL)                   /*!< PORT ISR: P0 (Bitfield-Mask: 0x03)                    */
/* ==========================================================  ICR  ========================================================== */
#define PORT_ICR_P15_Pos                  (30UL)                    /*!< PORT ICR: P15 (Bit 30)                                */
#define PORT_ICR_P15_Msk                  (0xc0000000UL)            /*!< PORT ICR: P15 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P14_Pos                  (28UL)                    /*!< PORT ICR: P14 (Bit 28)                                */
#define PORT_ICR_P14_Msk                  (0x30000000UL)            /*!< PORT ICR: P14 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P13_Pos                  (26UL)                    /*!< PORT ICR: P13 (Bit 26)                                */
#define PORT_ICR_P13_Msk                  (0xc000000UL)             /*!< PORT ICR: P13 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P12_Pos                  (24UL)                    /*!< PORT ICR: P12 (Bit 24)                                */
#define PORT_ICR_P12_Msk                  (0x3000000UL)             /*!< PORT ICR: P12 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P11_Pos                  (22UL)                    /*!< PORT ICR: P11 (Bit 22)                                */
#define PORT_ICR_P11_Msk                  (0xc00000UL)              /*!< PORT ICR: P11 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P10_Pos                  (20UL)                    /*!< PORT ICR: P10 (Bit 20)                                */
#define PORT_ICR_P10_Msk                  (0x300000UL)              /*!< PORT ICR: P10 (Bitfield-Mask: 0x03)                   */
#define PORT_ICR_P9_Pos                   (18UL)                    /*!< PORT ICR: P9 (Bit 18)                                 */
#define PORT_ICR_P9_Msk                   (0xc0000UL)               /*!< PORT ICR: P9 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P8_Pos                   (16UL)                    /*!< PORT ICR: P8 (Bit 16)                                 */
#define PORT_ICR_P8_Msk                   (0x30000UL)               /*!< PORT ICR: P8 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P7_Pos                   (14UL)                    /*!< PORT ICR: P7 (Bit 14)                                 */
#define PORT_ICR_P7_Msk                   (0xc000UL)                /*!< PORT ICR: P7 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P6_Pos                   (12UL)                    /*!< PORT ICR: P6 (Bit 12)                                 */
#define PORT_ICR_P6_Msk                   (0x3000UL)                /*!< PORT ICR: P6 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P5_Pos                   (10UL)                    /*!< PORT ICR: P5 (Bit 10)                                 */
#define PORT_ICR_P5_Msk                   (0xc00UL)                 /*!< PORT ICR: P5 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P4_Pos                   (8UL)                     /*!< PORT ICR: P4 (Bit 8)                                  */
#define PORT_ICR_P4_Msk                   (0x300UL)                 /*!< PORT ICR: P4 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P3_Pos                   (6UL)                     /*!< PORT ICR: P3 (Bit 6)                                  */
#define PORT_ICR_P3_Msk                   (0xc0UL)                  /*!< PORT ICR: P3 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P2_Pos                   (4UL)                     /*!< PORT ICR: P2 (Bit 4)                                  */
#define PORT_ICR_P2_Msk                   (0x30UL)                  /*!< PORT ICR: P2 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P1_Pos                   (2UL)                     /*!< PORT ICR: P1 (Bit 2)                                  */
#define PORT_ICR_P1_Msk                   (0xcUL)                   /*!< PORT ICR: P1 (Bitfield-Mask: 0x03)                    */
#define PORT_ICR_P0_Pos                   (0UL)                     /*!< PORT ICR: P0 (Bit 0)                                  */
#define PORT_ICR_P0_Msk                   (0x3UL)                   /*!< PORT ICR: P0 (Bitfield-Mask: 0x03)                    */
/* ==========================================================  STR  ========================================================== */
#define PORT_STR_P4_Pos                   (8UL)                     /*!< PORT STR: P4 (Bit 8)                                  */
#define PORT_STR_P4_Msk                   (0x300UL)                 /*!< PORT STR: P4 (Bitfield-Mask: 0x03)                    */
#define PORT_STR_P3_Pos                   (6UL)                     /*!< PORT STR: P3 (Bit 6)                                  */
#define PORT_STR_P3_Msk                   (0xc0UL)                  /*!< PORT STR: P3 (Bitfield-Mask: 0x03)                    */
#define PORT_STR_P2_Pos                   (4UL)                     /*!< PORT STR: P2 (Bit 4)                                  */
#define PORT_STR_P2_Msk                   (0x30UL)                  /*!< PORT STR: P2 (Bitfield-Mask: 0x03)                    */
#define PORT_STR_P1_Pos                   (2UL)                     /*!< PORT STR: P1 (Bit 2)                                  */
#define PORT_STR_P1_Msk                   (0xcUL)                   /*!< PORT STR: P1 (Bitfield-Mask: 0x03)                    */
#define PORT_STR_P0_Pos                   (0UL)                     /*!< PORT STR: P0 (Bit 0)                                  */
#define PORT_STR_P0_Msk                   (0x3UL)                   /*!< PORT STR: P0 (Bitfield-Mask: 0x03)                    */


/* =========================================================================================================================== */
/* ================                                           PORTF                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  MOD  ========================================================== */
#define PORTF_MOD_MODE15_Pos              (30UL)                    /*!< PORTF MOD: MODE15 (Bit 30)                            */
#define PORTF_MOD_MODE15_Msk              (0xc0000000UL)            /*!< PORTF MOD: MODE15 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE14_Pos              (28UL)                    /*!< PORTF MOD: MODE14 (Bit 28)                            */
#define PORTF_MOD_MODE14_Msk              (0x30000000UL)            /*!< PORTF MOD: MODE14 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE13_Pos              (26UL)                    /*!< PORTF MOD: MODE13 (Bit 26)                            */
#define PORTF_MOD_MODE13_Msk              (0xc000000UL)             /*!< PORTF MOD: MODE13 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE12_Pos              (24UL)                    /*!< PORTF MOD: MODE12 (Bit 24)                            */
#define PORTF_MOD_MODE12_Msk              (0x3000000UL)             /*!< PORTF MOD: MODE12 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE11_Pos              (22UL)                    /*!< PORTF MOD: MODE11 (Bit 22)                            */
#define PORTF_MOD_MODE11_Msk              (0xc00000UL)              /*!< PORTF MOD: MODE11 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE10_Pos              (20UL)                    /*!< PORTF MOD: MODE10 (Bit 20)                            */
#define PORTF_MOD_MODE10_Msk              (0x300000UL)              /*!< PORTF MOD: MODE10 (Bitfield-Mask: 0x03)               */
#define PORTF_MOD_MODE9_Pos               (18UL)                    /*!< PORTF MOD: MODE9 (Bit 18)                             */
#define PORTF_MOD_MODE9_Msk               (0xc0000UL)               /*!< PORTF MOD: MODE9 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE8_Pos               (16UL)                    /*!< PORTF MOD: MODE8 (Bit 16)                             */
#define PORTF_MOD_MODE8_Msk               (0x30000UL)               /*!< PORTF MOD: MODE8 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE7_Pos               (14UL)                    /*!< PORTF MOD: MODE7 (Bit 14)                             */
#define PORTF_MOD_MODE7_Msk               (0xc000UL)                /*!< PORTF MOD: MODE7 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE6_Pos               (12UL)                    /*!< PORTF MOD: MODE6 (Bit 12)                             */
#define PORTF_MOD_MODE6_Msk               (0x3000UL)                /*!< PORTF MOD: MODE6 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE5_Pos               (10UL)                    /*!< PORTF MOD: MODE5 (Bit 10)                             */
#define PORTF_MOD_MODE5_Msk               (0xc00UL)                 /*!< PORTF MOD: MODE5 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE4_Pos               (8UL)                     /*!< PORTF MOD: MODE4 (Bit 8)                              */
#define PORTF_MOD_MODE4_Msk               (0x300UL)                 /*!< PORTF MOD: MODE4 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE3_Pos               (6UL)                     /*!< PORTF MOD: MODE3 (Bit 6)                              */
#define PORTF_MOD_MODE3_Msk               (0xc0UL)                  /*!< PORTF MOD: MODE3 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE2_Pos               (4UL)                     /*!< PORTF MOD: MODE2 (Bit 4)                              */
#define PORTF_MOD_MODE2_Msk               (0x30UL)                  /*!< PORTF MOD: MODE2 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE1_Pos               (2UL)                     /*!< PORTF MOD: MODE1 (Bit 2)                              */
#define PORTF_MOD_MODE1_Msk               (0xcUL)                   /*!< PORTF MOD: MODE1 (Bitfield-Mask: 0x03)                */
#define PORTF_MOD_MODE0_Pos               (0UL)                     /*!< PORTF MOD: MODE0 (Bit 0)                              */
#define PORTF_MOD_MODE0_Msk               (0x3UL)                   /*!< PORTF MOD: MODE0 (Bitfield-Mask: 0x03)                */
/* ==========================================================  TYP  ========================================================== */
#define PORTF_TYP_TYP15_Pos               (15UL)                    /*!< PORTF TYP: TYP15 (Bit 15)                             */
#define PORTF_TYP_TYP15_Msk               (0x8000UL)                /*!< PORTF TYP: TYP15 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP14_Pos               (14UL)                    /*!< PORTF TYP: TYP14 (Bit 14)                             */
#define PORTF_TYP_TYP14_Msk               (0x4000UL)                /*!< PORTF TYP: TYP14 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP13_Pos               (13UL)                    /*!< PORTF TYP: TYP13 (Bit 13)                             */
#define PORTF_TYP_TYP13_Msk               (0x2000UL)                /*!< PORTF TYP: TYP13 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP12_Pos               (12UL)                    /*!< PORTF TYP: TYP12 (Bit 12)                             */
#define PORTF_TYP_TYP12_Msk               (0x1000UL)                /*!< PORTF TYP: TYP12 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP11_Pos               (11UL)                    /*!< PORTF TYP: TYP11 (Bit 11)                             */
#define PORTF_TYP_TYP11_Msk               (0x800UL)                 /*!< PORTF TYP: TYP11 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP10_Pos               (10UL)                    /*!< PORTF TYP: TYP10 (Bit 10)                             */
#define PORTF_TYP_TYP10_Msk               (0x400UL)                 /*!< PORTF TYP: TYP10 (Bitfield-Mask: 0x01)                */
#define PORTF_TYP_TYP9_Pos                (9UL)                     /*!< PORTF TYP: TYP9 (Bit 9)                               */
#define PORTF_TYP_TYP9_Msk                (0x200UL)                 /*!< PORTF TYP: TYP9 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP8_Pos                (8UL)                     /*!< PORTF TYP: TYP8 (Bit 8)                               */
#define PORTF_TYP_TYP8_Msk                (0x100UL)                 /*!< PORTF TYP: TYP8 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP7_Pos                (7UL)                     /*!< PORTF TYP: TYP7 (Bit 7)                               */
#define PORTF_TYP_TYP7_Msk                (0x80UL)                  /*!< PORTF TYP: TYP7 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP6_Pos                (6UL)                     /*!< PORTF TYP: TYP6 (Bit 6)                               */
#define PORTF_TYP_TYP6_Msk                (0x40UL)                  /*!< PORTF TYP: TYP6 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP5_Pos                (5UL)                     /*!< PORTF TYP: TYP5 (Bit 5)                               */
#define PORTF_TYP_TYP5_Msk                (0x20UL)                  /*!< PORTF TYP: TYP5 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP4_Pos                (4UL)                     /*!< PORTF TYP: TYP4 (Bit 4)                               */
#define PORTF_TYP_TYP4_Msk                (0x10UL)                  /*!< PORTF TYP: TYP4 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP3_Pos                (3UL)                     /*!< PORTF TYP: TYP3 (Bit 3)                               */
#define PORTF_TYP_TYP3_Msk                (0x8UL)                   /*!< PORTF TYP: TYP3 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP2_Pos                (2UL)                     /*!< PORTF TYP: TYP2 (Bit 2)                               */
#define PORTF_TYP_TYP2_Msk                (0x4UL)                   /*!< PORTF TYP: TYP2 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP1_Pos                (1UL)                     /*!< PORTF TYP: TYP1 (Bit 1)                               */
#define PORTF_TYP_TYP1_Msk                (0x2UL)                   /*!< PORTF TYP: TYP1 (Bitfield-Mask: 0x01)                 */
#define PORTF_TYP_TYP0_Pos                (0UL)                     /*!< PORTF TYP: TYP0 (Bit 0)                               */
#define PORTF_TYP_TYP0_Msk                (0x1UL)                   /*!< PORTF TYP: TYP0 (Bitfield-Mask: 0x01)                 */
/* =========================================================  AFSR1  ========================================================= */
#define PORTF_AFSR1_AFSR7_Pos             (28UL)                    /*!< PORTF AFSR1: AFSR7 (Bit 28)                           */
#define PORTF_AFSR1_AFSR7_Msk             (0xf0000000UL)            /*!< PORTF AFSR1: AFSR7 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR6_Pos             (24UL)                    /*!< PORTF AFSR1: AFSR6 (Bit 24)                           */
#define PORTF_AFSR1_AFSR6_Msk             (0xf000000UL)             /*!< PORTF AFSR1: AFSR6 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR5_Pos             (20UL)                    /*!< PORTF AFSR1: AFSR5 (Bit 20)                           */
#define PORTF_AFSR1_AFSR5_Msk             (0xf00000UL)              /*!< PORTF AFSR1: AFSR5 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR4_Pos             (16UL)                    /*!< PORTF AFSR1: AFSR4 (Bit 16)                           */
#define PORTF_AFSR1_AFSR4_Msk             (0xf0000UL)               /*!< PORTF AFSR1: AFSR4 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR3_Pos             (12UL)                    /*!< PORTF AFSR1: AFSR3 (Bit 12)                           */
#define PORTF_AFSR1_AFSR3_Msk             (0xf000UL)                /*!< PORTF AFSR1: AFSR3 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR2_Pos             (8UL)                     /*!< PORTF AFSR1: AFSR2 (Bit 8)                            */
#define PORTF_AFSR1_AFSR2_Msk             (0xf00UL)                 /*!< PORTF AFSR1: AFSR2 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR1_Pos             (4UL)                     /*!< PORTF AFSR1: AFSR1 (Bit 4)                            */
#define PORTF_AFSR1_AFSR1_Msk             (0xf0UL)                  /*!< PORTF AFSR1: AFSR1 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR1_AFSR0_Pos             (0UL)                     /*!< PORTF AFSR1: AFSR0 (Bit 0)                            */
#define PORTF_AFSR1_AFSR0_Msk             (0xfUL)                   /*!< PORTF AFSR1: AFSR0 (Bitfield-Mask: 0x0f)              */
/* =========================================================  AFSR2  ========================================================= */
#define PORTF_AFSR2_AFSR15_Pos            (28UL)                    /*!< PORTF AFSR2: AFSR15 (Bit 28)                          */
#define PORTF_AFSR2_AFSR15_Msk            (0xf0000000UL)            /*!< PORTF AFSR2: AFSR15 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR14_Pos            (24UL)                    /*!< PORTF AFSR2: AFSR14 (Bit 24)                          */
#define PORTF_AFSR2_AFSR14_Msk            (0xf000000UL)             /*!< PORTF AFSR2: AFSR14 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR13_Pos            (20UL)                    /*!< PORTF AFSR2: AFSR13 (Bit 20)                          */
#define PORTF_AFSR2_AFSR13_Msk            (0xf00000UL)              /*!< PORTF AFSR2: AFSR13 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR12_Pos            (16UL)                    /*!< PORTF AFSR2: AFSR12 (Bit 16)                          */
#define PORTF_AFSR2_AFSR12_Msk            (0xf0000UL)               /*!< PORTF AFSR2: AFSR12 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR11_Pos            (12UL)                    /*!< PORTF AFSR2: AFSR11 (Bit 12)                          */
#define PORTF_AFSR2_AFSR11_Msk            (0xf000UL)                /*!< PORTF AFSR2: AFSR11 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR10_Pos            (8UL)                     /*!< PORTF AFSR2: AFSR10 (Bit 8)                           */
#define PORTF_AFSR2_AFSR10_Msk            (0xf00UL)                 /*!< PORTF AFSR2: AFSR10 (Bitfield-Mask: 0x0f)             */
#define PORTF_AFSR2_AFSR9_Pos             (4UL)                     /*!< PORTF AFSR2: AFSR9 (Bit 4)                            */
#define PORTF_AFSR2_AFSR9_Msk             (0xf0UL)                  /*!< PORTF AFSR2: AFSR9 (Bitfield-Mask: 0x0f)              */
#define PORTF_AFSR2_AFSR8_Pos             (0UL)                     /*!< PORTF AFSR2: AFSR8 (Bit 0)                            */
#define PORTF_AFSR2_AFSR8_Msk             (0xfUL)                   /*!< PORTF AFSR2: AFSR8 (Bitfield-Mask: 0x0f)              */
/* =========================================================  PUPD  ========================================================== */
#define PORTF_PUPD_PUPD15_Pos             (30UL)                    /*!< PORTF PUPD: PUPD15 (Bit 30)                           */
#define PORTF_PUPD_PUPD15_Msk             (0xc0000000UL)            /*!< PORTF PUPD: PUPD15 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD14_Pos             (28UL)                    /*!< PORTF PUPD: PUPD14 (Bit 28)                           */
#define PORTF_PUPD_PUPD14_Msk             (0x30000000UL)            /*!< PORTF PUPD: PUPD14 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD13_Pos             (26UL)                    /*!< PORTF PUPD: PUPD13 (Bit 26)                           */
#define PORTF_PUPD_PUPD13_Msk             (0xc000000UL)             /*!< PORTF PUPD: PUPD13 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD12_Pos             (24UL)                    /*!< PORTF PUPD: PUPD12 (Bit 24)                           */
#define PORTF_PUPD_PUPD12_Msk             (0x3000000UL)             /*!< PORTF PUPD: PUPD12 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD11_Pos             (22UL)                    /*!< PORTF PUPD: PUPD11 (Bit 22)                           */
#define PORTF_PUPD_PUPD11_Msk             (0xc00000UL)              /*!< PORTF PUPD: PUPD11 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD10_Pos             (20UL)                    /*!< PORTF PUPD: PUPD10 (Bit 20)                           */
#define PORTF_PUPD_PUPD10_Msk             (0x300000UL)              /*!< PORTF PUPD: PUPD10 (Bitfield-Mask: 0x03)              */
#define PORTF_PUPD_PUPD9_Pos              (18UL)                    /*!< PORTF PUPD: PUPD9 (Bit 18)                            */
#define PORTF_PUPD_PUPD9_Msk              (0xc0000UL)               /*!< PORTF PUPD: PUPD9 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD8_Pos              (16UL)                    /*!< PORTF PUPD: PUPD8 (Bit 16)                            */
#define PORTF_PUPD_PUPD8_Msk              (0x30000UL)               /*!< PORTF PUPD: PUPD8 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD7_Pos              (14UL)                    /*!< PORTF PUPD: PUPD7 (Bit 14)                            */
#define PORTF_PUPD_PUPD7_Msk              (0xc000UL)                /*!< PORTF PUPD: PUPD7 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD6_Pos              (12UL)                    /*!< PORTF PUPD: PUPD6 (Bit 12)                            */
#define PORTF_PUPD_PUPD6_Msk              (0x3000UL)                /*!< PORTF PUPD: PUPD6 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD5_Pos              (10UL)                    /*!< PORTF PUPD: PUPD5 (Bit 10)                            */
#define PORTF_PUPD_PUPD5_Msk              (0xc00UL)                 /*!< PORTF PUPD: PUPD5 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD4_Pos              (8UL)                     /*!< PORTF PUPD: PUPD4 (Bit 8)                             */
#define PORTF_PUPD_PUPD4_Msk              (0x300UL)                 /*!< PORTF PUPD: PUPD4 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD3_Pos              (6UL)                     /*!< PORTF PUPD: PUPD3 (Bit 6)                             */
#define PORTF_PUPD_PUPD3_Msk              (0xc0UL)                  /*!< PORTF PUPD: PUPD3 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD2_Pos              (4UL)                     /*!< PORTF PUPD: PUPD2 (Bit 4)                             */
#define PORTF_PUPD_PUPD2_Msk              (0x30UL)                  /*!< PORTF PUPD: PUPD2 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD1_Pos              (2UL)                     /*!< PORTF PUPD: PUPD1 (Bit 2)                             */
#define PORTF_PUPD_PUPD1_Msk              (0xcUL)                   /*!< PORTF PUPD: PUPD1 (Bitfield-Mask: 0x03)               */
#define PORTF_PUPD_PUPD0_Pos              (0UL)                     /*!< PORTF PUPD: PUPD0 (Bit 0)                             */
#define PORTF_PUPD_PUPD0_Msk              (0x3UL)                   /*!< PORTF PUPD: PUPD0 (Bitfield-Mask: 0x03)               */
/* =========================================================  INDR  ========================================================== */
#define PORTF_INDR_INDR15_Pos             (15UL)                    /*!< PORTF INDR: INDR15 (Bit 15)                           */
#define PORTF_INDR_INDR15_Msk             (0x8000UL)                /*!< PORTF INDR: INDR15 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR14_Pos             (14UL)                    /*!< PORTF INDR: INDR14 (Bit 14)                           */
#define PORTF_INDR_INDR14_Msk             (0x4000UL)                /*!< PORTF INDR: INDR14 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR13_Pos             (13UL)                    /*!< PORTF INDR: INDR13 (Bit 13)                           */
#define PORTF_INDR_INDR13_Msk             (0x2000UL)                /*!< PORTF INDR: INDR13 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR12_Pos             (12UL)                    /*!< PORTF INDR: INDR12 (Bit 12)                           */
#define PORTF_INDR_INDR12_Msk             (0x1000UL)                /*!< PORTF INDR: INDR12 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR11_Pos             (11UL)                    /*!< PORTF INDR: INDR11 (Bit 11)                           */
#define PORTF_INDR_INDR11_Msk             (0x800UL)                 /*!< PORTF INDR: INDR11 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR10_Pos             (10UL)                    /*!< PORTF INDR: INDR10 (Bit 10)                           */
#define PORTF_INDR_INDR10_Msk             (0x400UL)                 /*!< PORTF INDR: INDR10 (Bitfield-Mask: 0x01)              */
#define PORTF_INDR_INDR9_Pos              (9UL)                     /*!< PORTF INDR: INDR9 (Bit 9)                             */
#define PORTF_INDR_INDR9_Msk              (0x200UL)                 /*!< PORTF INDR: INDR9 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR8_Pos              (8UL)                     /*!< PORTF INDR: INDR8 (Bit 8)                             */
#define PORTF_INDR_INDR8_Msk              (0x100UL)                 /*!< PORTF INDR: INDR8 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR7_Pos              (7UL)                     /*!< PORTF INDR: INDR7 (Bit 7)                             */
#define PORTF_INDR_INDR7_Msk              (0x80UL)                  /*!< PORTF INDR: INDR7 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR6_Pos              (6UL)                     /*!< PORTF INDR: INDR6 (Bit 6)                             */
#define PORTF_INDR_INDR6_Msk              (0x40UL)                  /*!< PORTF INDR: INDR6 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR5_Pos              (5UL)                     /*!< PORTF INDR: INDR5 (Bit 5)                             */
#define PORTF_INDR_INDR5_Msk              (0x20UL)                  /*!< PORTF INDR: INDR5 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR4_Pos              (4UL)                     /*!< PORTF INDR: INDR4 (Bit 4)                             */
#define PORTF_INDR_INDR4_Msk              (0x10UL)                  /*!< PORTF INDR: INDR4 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR3_Pos              (3UL)                     /*!< PORTF INDR: INDR3 (Bit 3)                             */
#define PORTF_INDR_INDR3_Msk              (0x8UL)                   /*!< PORTF INDR: INDR3 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR2_Pos              (2UL)                     /*!< PORTF INDR: INDR2 (Bit 2)                             */
#define PORTF_INDR_INDR2_Msk              (0x4UL)                   /*!< PORTF INDR: INDR2 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR1_Pos              (1UL)                     /*!< PORTF INDR: INDR1 (Bit 1)                             */
#define PORTF_INDR_INDR1_Msk              (0x2UL)                   /*!< PORTF INDR: INDR1 (Bitfield-Mask: 0x01)               */
#define PORTF_INDR_INDR0_Pos              (0UL)                     /*!< PORTF INDR: INDR0 (Bit 0)                             */
#define PORTF_INDR_INDR0_Msk              (0x1UL)                   /*!< PORTF INDR: INDR0 (Bitfield-Mask: 0x01)               */
/* =========================================================  OUTDR  ========================================================= */
#define PORTF_OUTDR_OUTDR15_Pos           (15UL)                    /*!< PORTF OUTDR: OUTDR15 (Bit 15)                         */
#define PORTF_OUTDR_OUTDR15_Msk           (0x8000UL)                /*!< PORTF OUTDR: OUTDR15 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR14_Pos           (14UL)                    /*!< PORTF OUTDR: OUTDR14 (Bit 14)                         */
#define PORTF_OUTDR_OUTDR14_Msk           (0x4000UL)                /*!< PORTF OUTDR: OUTDR14 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR13_Pos           (13UL)                    /*!< PORTF OUTDR: OUTDR13 (Bit 13)                         */
#define PORTF_OUTDR_OUTDR13_Msk           (0x2000UL)                /*!< PORTF OUTDR: OUTDR13 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR12_Pos           (12UL)                    /*!< PORTF OUTDR: OUTDR12 (Bit 12)                         */
#define PORTF_OUTDR_OUTDR12_Msk           (0x1000UL)                /*!< PORTF OUTDR: OUTDR12 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR11_Pos           (11UL)                    /*!< PORTF OUTDR: OUTDR11 (Bit 11)                         */
#define PORTF_OUTDR_OUTDR11_Msk           (0x800UL)                 /*!< PORTF OUTDR: OUTDR11 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR10_Pos           (10UL)                    /*!< PORTF OUTDR: OUTDR10 (Bit 10)                         */
#define PORTF_OUTDR_OUTDR10_Msk           (0x400UL)                 /*!< PORTF OUTDR: OUTDR10 (Bitfield-Mask: 0x01)            */
#define PORTF_OUTDR_OUTDR9_Pos            (9UL)                     /*!< PORTF OUTDR: OUTDR9 (Bit 9)                           */
#define PORTF_OUTDR_OUTDR9_Msk            (0x200UL)                 /*!< PORTF OUTDR: OUTDR9 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR8_Pos            (8UL)                     /*!< PORTF OUTDR: OUTDR8 (Bit 8)                           */
#define PORTF_OUTDR_OUTDR8_Msk            (0x100UL)                 /*!< PORTF OUTDR: OUTDR8 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR7_Pos            (7UL)                     /*!< PORTF OUTDR: OUTDR7 (Bit 7)                           */
#define PORTF_OUTDR_OUTDR7_Msk            (0x80UL)                  /*!< PORTF OUTDR: OUTDR7 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR6_Pos            (6UL)                     /*!< PORTF OUTDR: OUTDR6 (Bit 6)                           */
#define PORTF_OUTDR_OUTDR6_Msk            (0x40UL)                  /*!< PORTF OUTDR: OUTDR6 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR5_Pos            (5UL)                     /*!< PORTF OUTDR: OUTDR5 (Bit 5)                           */
#define PORTF_OUTDR_OUTDR5_Msk            (0x20UL)                  /*!< PORTF OUTDR: OUTDR5 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR4_Pos            (4UL)                     /*!< PORTF OUTDR: OUTDR4 (Bit 4)                           */
#define PORTF_OUTDR_OUTDR4_Msk            (0x10UL)                  /*!< PORTF OUTDR: OUTDR4 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR3_Pos            (3UL)                     /*!< PORTF OUTDR: OUTDR3 (Bit 3)                           */
#define PORTF_OUTDR_OUTDR3_Msk            (0x8UL)                   /*!< PORTF OUTDR: OUTDR3 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR2_Pos            (2UL)                     /*!< PORTF OUTDR: OUTDR2 (Bit 2)                           */
#define PORTF_OUTDR_OUTDR2_Msk            (0x4UL)                   /*!< PORTF OUTDR: OUTDR2 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR1_Pos            (1UL)                     /*!< PORTF OUTDR: OUTDR1 (Bit 1)                           */
#define PORTF_OUTDR_OUTDR1_Msk            (0x2UL)                   /*!< PORTF OUTDR: OUTDR1 (Bitfield-Mask: 0x01)             */
#define PORTF_OUTDR_OUTDR0_Pos            (0UL)                     /*!< PORTF OUTDR: OUTDR0 (Bit 0)                           */
#define PORTF_OUTDR_OUTDR0_Msk            (0x1UL)                   /*!< PORTF OUTDR: OUTDR0 (Bitfield-Mask: 0x01)             */
/* ==========================================================  BSR  ========================================================== */
#define PORTF_BSR_BSR15_Pos               (15UL)                    /*!< PORTF BSR: BSR15 (Bit 15)                             */
#define PORTF_BSR_BSR15_Msk               (0x8000UL)                /*!< PORTF BSR: BSR15 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR14_Pos               (14UL)                    /*!< PORTF BSR: BSR14 (Bit 14)                             */
#define PORTF_BSR_BSR14_Msk               (0x4000UL)                /*!< PORTF BSR: BSR14 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR13_Pos               (13UL)                    /*!< PORTF BSR: BSR13 (Bit 13)                             */
#define PORTF_BSR_BSR13_Msk               (0x2000UL)                /*!< PORTF BSR: BSR13 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR12_Pos               (12UL)                    /*!< PORTF BSR: BSR12 (Bit 12)                             */
#define PORTF_BSR_BSR12_Msk               (0x1000UL)                /*!< PORTF BSR: BSR12 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR11_Pos               (11UL)                    /*!< PORTF BSR: BSR11 (Bit 11)                             */
#define PORTF_BSR_BSR11_Msk               (0x800UL)                 /*!< PORTF BSR: BSR11 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR10_Pos               (10UL)                    /*!< PORTF BSR: BSR10 (Bit 10)                             */
#define PORTF_BSR_BSR10_Msk               (0x400UL)                 /*!< PORTF BSR: BSR10 (Bitfield-Mask: 0x01)                */
#define PORTF_BSR_BSR9_Pos                (9UL)                     /*!< PORTF BSR: BSR9 (Bit 9)                               */
#define PORTF_BSR_BSR9_Msk                (0x200UL)                 /*!< PORTF BSR: BSR9 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR8_Pos                (8UL)                     /*!< PORTF BSR: BSR8 (Bit 8)                               */
#define PORTF_BSR_BSR8_Msk                (0x100UL)                 /*!< PORTF BSR: BSR8 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR7_Pos                (7UL)                     /*!< PORTF BSR: BSR7 (Bit 7)                               */
#define PORTF_BSR_BSR7_Msk                (0x80UL)                  /*!< PORTF BSR: BSR7 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR6_Pos                (6UL)                     /*!< PORTF BSR: BSR6 (Bit 6)                               */
#define PORTF_BSR_BSR6_Msk                (0x40UL)                  /*!< PORTF BSR: BSR6 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR5_Pos                (5UL)                     /*!< PORTF BSR: BSR5 (Bit 5)                               */
#define PORTF_BSR_BSR5_Msk                (0x20UL)                  /*!< PORTF BSR: BSR5 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR4_Pos                (4UL)                     /*!< PORTF BSR: BSR4 (Bit 4)                               */
#define PORTF_BSR_BSR4_Msk                (0x10UL)                  /*!< PORTF BSR: BSR4 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR3_Pos                (3UL)                     /*!< PORTF BSR: BSR3 (Bit 3)                               */
#define PORTF_BSR_BSR3_Msk                (0x8UL)                   /*!< PORTF BSR: BSR3 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR2_Pos                (2UL)                     /*!< PORTF BSR: BSR2 (Bit 2)                               */
#define PORTF_BSR_BSR2_Msk                (0x4UL)                   /*!< PORTF BSR: BSR2 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR1_Pos                (1UL)                     /*!< PORTF BSR: BSR1 (Bit 1)                               */
#define PORTF_BSR_BSR1_Msk                (0x2UL)                   /*!< PORTF BSR: BSR1 (Bitfield-Mask: 0x01)                 */
#define PORTF_BSR_BSR0_Pos                (0UL)                     /*!< PORTF BSR: BSR0 (Bit 0)                               */
#define PORTF_BSR_BSR0_Msk                (0x1UL)                   /*!< PORTF BSR: BSR0 (Bitfield-Mask: 0x01)                 */
/* ==========================================================  BCR  ========================================================== */
#define PORTF_BCR_BCR15_Pos               (15UL)                    /*!< PORTF BCR: BCR15 (Bit 15)                             */
#define PORTF_BCR_BCR15_Msk               (0x8000UL)                /*!< PORTF BCR: BCR15 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR14_Pos               (14UL)                    /*!< PORTF BCR: BCR14 (Bit 14)                             */
#define PORTF_BCR_BCR14_Msk               (0x4000UL)                /*!< PORTF BCR: BCR14 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR13_Pos               (13UL)                    /*!< PORTF BCR: BCR13 (Bit 13)                             */
#define PORTF_BCR_BCR13_Msk               (0x2000UL)                /*!< PORTF BCR: BCR13 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR12_Pos               (12UL)                    /*!< PORTF BCR: BCR12 (Bit 12)                             */
#define PORTF_BCR_BCR12_Msk               (0x1000UL)                /*!< PORTF BCR: BCR12 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR11_Pos               (11UL)                    /*!< PORTF BCR: BCR11 (Bit 11)                             */
#define PORTF_BCR_BCR11_Msk               (0x800UL)                 /*!< PORTF BCR: BCR11 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR10_Pos               (10UL)                    /*!< PORTF BCR: BCR10 (Bit 10)                             */
#define PORTF_BCR_BCR10_Msk               (0x400UL)                 /*!< PORTF BCR: BCR10 (Bitfield-Mask: 0x01)                */
#define PORTF_BCR_BCR9_Pos                (9UL)                     /*!< PORTF BCR: BCR9 (Bit 9)                               */
#define PORTF_BCR_BCR9_Msk                (0x200UL)                 /*!< PORTF BCR: BCR9 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR8_Pos                (8UL)                     /*!< PORTF BCR: BCR8 (Bit 8)                               */
#define PORTF_BCR_BCR8_Msk                (0x100UL)                 /*!< PORTF BCR: BCR8 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR7_Pos                (7UL)                     /*!< PORTF BCR: BCR7 (Bit 7)                               */
#define PORTF_BCR_BCR7_Msk                (0x80UL)                  /*!< PORTF BCR: BCR7 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR6_Pos                (6UL)                     /*!< PORTF BCR: BCR6 (Bit 6)                               */
#define PORTF_BCR_BCR6_Msk                (0x40UL)                  /*!< PORTF BCR: BCR6 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR5_Pos                (5UL)                     /*!< PORTF BCR: BCR5 (Bit 5)                               */
#define PORTF_BCR_BCR5_Msk                (0x20UL)                  /*!< PORTF BCR: BCR5 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR4_Pos                (4UL)                     /*!< PORTF BCR: BCR4 (Bit 4)                               */
#define PORTF_BCR_BCR4_Msk                (0x10UL)                  /*!< PORTF BCR: BCR4 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR3_Pos                (3UL)                     /*!< PORTF BCR: BCR3 (Bit 3)                               */
#define PORTF_BCR_BCR3_Msk                (0x8UL)                   /*!< PORTF BCR: BCR3 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR2_Pos                (2UL)                     /*!< PORTF BCR: BCR2 (Bit 2)                               */
#define PORTF_BCR_BCR2_Msk                (0x4UL)                   /*!< PORTF BCR: BCR2 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR1_Pos                (1UL)                     /*!< PORTF BCR: BCR1 (Bit 1)                               */
#define PORTF_BCR_BCR1_Msk                (0x2UL)                   /*!< PORTF BCR: BCR1 (Bitfield-Mask: 0x01)                 */
#define PORTF_BCR_BCR0_Pos                (0UL)                     /*!< PORTF BCR: BCR0 (Bit 0)                               */
#define PORTF_BCR_BCR0_Msk                (0x1UL)                   /*!< PORTF BCR: BCR0 (Bitfield-Mask: 0x01)                 */
/* ========================================================  OUTDMSK  ======================================================== */
#define PORTF_OUTDMSK_OUTDMSK15_Pos       (15UL)                    /*!< PORTF OUTDMSK: OUTDMSK15 (Bit 15)                     */
#define PORTF_OUTDMSK_OUTDMSK15_Msk       (0x8000UL)                /*!< PORTF OUTDMSK: OUTDMSK15 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK14_Pos       (14UL)                    /*!< PORTF OUTDMSK: OUTDMSK14 (Bit 14)                     */
#define PORTF_OUTDMSK_OUTDMSK14_Msk       (0x4000UL)                /*!< PORTF OUTDMSK: OUTDMSK14 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK13_Pos       (13UL)                    /*!< PORTF OUTDMSK: OUTDMSK13 (Bit 13)                     */
#define PORTF_OUTDMSK_OUTDMSK13_Msk       (0x2000UL)                /*!< PORTF OUTDMSK: OUTDMSK13 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK12_Pos       (12UL)                    /*!< PORTF OUTDMSK: OUTDMSK12 (Bit 12)                     */
#define PORTF_OUTDMSK_OUTDMSK12_Msk       (0x1000UL)                /*!< PORTF OUTDMSK: OUTDMSK12 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK11_Pos       (11UL)                    /*!< PORTF OUTDMSK: OUTDMSK11 (Bit 11)                     */
#define PORTF_OUTDMSK_OUTDMSK11_Msk       (0x800UL)                 /*!< PORTF OUTDMSK: OUTDMSK11 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK10_Pos       (10UL)                    /*!< PORTF OUTDMSK: OUTDMSK10 (Bit 10)                     */
#define PORTF_OUTDMSK_OUTDMSK10_Msk       (0x400UL)                 /*!< PORTF OUTDMSK: OUTDMSK10 (Bitfield-Mask: 0x01)        */
#define PORTF_OUTDMSK_OUTDMSK9_Pos        (9UL)                     /*!< PORTF OUTDMSK: OUTDMSK9 (Bit 9)                       */
#define PORTF_OUTDMSK_OUTDMSK9_Msk        (0x200UL)                 /*!< PORTF OUTDMSK: OUTDMSK9 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK8_Pos        (8UL)                     /*!< PORTF OUTDMSK: OUTDMSK8 (Bit 8)                       */
#define PORTF_OUTDMSK_OUTDMSK8_Msk        (0x100UL)                 /*!< PORTF OUTDMSK: OUTDMSK8 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK7_Pos        (7UL)                     /*!< PORTF OUTDMSK: OUTDMSK7 (Bit 7)                       */
#define PORTF_OUTDMSK_OUTDMSK7_Msk        (0x80UL)                  /*!< PORTF OUTDMSK: OUTDMSK7 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK6_Pos        (6UL)                     /*!< PORTF OUTDMSK: OUTDMSK6 (Bit 6)                       */
#define PORTF_OUTDMSK_OUTDMSK6_Msk        (0x40UL)                  /*!< PORTF OUTDMSK: OUTDMSK6 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK5_Pos        (5UL)                     /*!< PORTF OUTDMSK: OUTDMSK5 (Bit 5)                       */
#define PORTF_OUTDMSK_OUTDMSK5_Msk        (0x20UL)                  /*!< PORTF OUTDMSK: OUTDMSK5 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK4_Pos        (4UL)                     /*!< PORTF OUTDMSK: OUTDMSK4 (Bit 4)                       */
#define PORTF_OUTDMSK_OUTDMSK4_Msk        (0x10UL)                  /*!< PORTF OUTDMSK: OUTDMSK4 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK3_Pos        (3UL)                     /*!< PORTF OUTDMSK: OUTDMSK3 (Bit 3)                       */
#define PORTF_OUTDMSK_OUTDMSK3_Msk        (0x8UL)                   /*!< PORTF OUTDMSK: OUTDMSK3 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK2_Pos        (2UL)                     /*!< PORTF OUTDMSK: OUTDMSK2 (Bit 2)                       */
#define PORTF_OUTDMSK_OUTDMSK2_Msk        (0x4UL)                   /*!< PORTF OUTDMSK: OUTDMSK2 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK1_Pos        (1UL)                     /*!< PORTF OUTDMSK: OUTDMSK1 (Bit 1)                       */
#define PORTF_OUTDMSK_OUTDMSK1_Msk        (0x2UL)                   /*!< PORTF OUTDMSK: OUTDMSK1 (Bitfield-Mask: 0x01)         */
#define PORTF_OUTDMSK_OUTDMSK0_Pos        (0UL)                     /*!< PORTF OUTDMSK: OUTDMSK0 (Bit 0)                       */
#define PORTF_OUTDMSK_OUTDMSK0_Msk        (0x1UL)                   /*!< PORTF OUTDMSK: OUTDMSK0 (Bitfield-Mask: 0x01)         */
/* =========================================================  DBCR  ========================================================== */
#define PORTF_DBCR_DBEN15_Pos             (15UL)                    /*!< PORTF DBCR: DBEN15 (Bit 15)                           */
#define PORTF_DBCR_DBEN15_Msk             (0x8000UL)                /*!< PORTF DBCR: DBEN15 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN14_Pos             (14UL)                    /*!< PORTF DBCR: DBEN14 (Bit 14)                           */
#define PORTF_DBCR_DBEN14_Msk             (0x4000UL)                /*!< PORTF DBCR: DBEN14 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN13_Pos             (13UL)                    /*!< PORTF DBCR: DBEN13 (Bit 13)                           */
#define PORTF_DBCR_DBEN13_Msk             (0x2000UL)                /*!< PORTF DBCR: DBEN13 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN12_Pos             (12UL)                    /*!< PORTF DBCR: DBEN12 (Bit 12)                           */
#define PORTF_DBCR_DBEN12_Msk             (0x1000UL)                /*!< PORTF DBCR: DBEN12 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN11_Pos             (11UL)                    /*!< PORTF DBCR: DBEN11 (Bit 11)                           */
#define PORTF_DBCR_DBEN11_Msk             (0x800UL)                 /*!< PORTF DBCR: DBEN11 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN10_Pos             (10UL)                    /*!< PORTF DBCR: DBEN10 (Bit 10)                           */
#define PORTF_DBCR_DBEN10_Msk             (0x400UL)                 /*!< PORTF DBCR: DBEN10 (Bitfield-Mask: 0x01)              */
#define PORTF_DBCR_DBEN9_Pos              (9UL)                     /*!< PORTF DBCR: DBEN9 (Bit 9)                             */
#define PORTF_DBCR_DBEN9_Msk              (0x200UL)                 /*!< PORTF DBCR: DBEN9 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN8_Pos              (8UL)                     /*!< PORTF DBCR: DBEN8 (Bit 8)                             */
#define PORTF_DBCR_DBEN8_Msk              (0x100UL)                 /*!< PORTF DBCR: DBEN8 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN7_Pos              (7UL)                     /*!< PORTF DBCR: DBEN7 (Bit 7)                             */
#define PORTF_DBCR_DBEN7_Msk              (0x80UL)                  /*!< PORTF DBCR: DBEN7 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN6_Pos              (6UL)                     /*!< PORTF DBCR: DBEN6 (Bit 6)                             */
#define PORTF_DBCR_DBEN6_Msk              (0x40UL)                  /*!< PORTF DBCR: DBEN6 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN5_Pos              (5UL)                     /*!< PORTF DBCR: DBEN5 (Bit 5)                             */
#define PORTF_DBCR_DBEN5_Msk              (0x20UL)                  /*!< PORTF DBCR: DBEN5 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN4_Pos              (4UL)                     /*!< PORTF DBCR: DBEN4 (Bit 4)                             */
#define PORTF_DBCR_DBEN4_Msk              (0x10UL)                  /*!< PORTF DBCR: DBEN4 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN3_Pos              (3UL)                     /*!< PORTF DBCR: DBEN3 (Bit 3)                             */
#define PORTF_DBCR_DBEN3_Msk              (0x8UL)                   /*!< PORTF DBCR: DBEN3 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN2_Pos              (2UL)                     /*!< PORTF DBCR: DBEN2 (Bit 2)                             */
#define PORTF_DBCR_DBEN2_Msk              (0x4UL)                   /*!< PORTF DBCR: DBEN2 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN1_Pos              (1UL)                     /*!< PORTF DBCR: DBEN1 (Bit 1)                             */
#define PORTF_DBCR_DBEN1_Msk              (0x2UL)                   /*!< PORTF DBCR: DBEN1 (Bitfield-Mask: 0x01)               */
#define PORTF_DBCR_DBEN0_Pos              (0UL)                     /*!< PORTF DBCR: DBEN0 (Bit 0)                             */
#define PORTF_DBCR_DBEN0_Msk              (0x1UL)                   /*!< PORTF DBCR: DBEN0 (Bitfield-Mask: 0x01)               */
/* ==========================================================  IER  ========================================================== */
#define PORTF_IER_P15_Pos                 (30UL)                    /*!< PORTF IER: P15 (Bit 30)                               */
#define PORTF_IER_P15_Msk                 (0xc0000000UL)            /*!< PORTF IER: P15 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P14_Pos                 (28UL)                    /*!< PORTF IER: P14 (Bit 28)                               */
#define PORTF_IER_P14_Msk                 (0x30000000UL)            /*!< PORTF IER: P14 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P13_Pos                 (26UL)                    /*!< PORTF IER: P13 (Bit 26)                               */
#define PORTF_IER_P13_Msk                 (0xc000000UL)             /*!< PORTF IER: P13 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P12_Pos                 (24UL)                    /*!< PORTF IER: P12 (Bit 24)                               */
#define PORTF_IER_P12_Msk                 (0x3000000UL)             /*!< PORTF IER: P12 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P11_Pos                 (22UL)                    /*!< PORTF IER: P11 (Bit 22)                               */
#define PORTF_IER_P11_Msk                 (0xc00000UL)              /*!< PORTF IER: P11 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P10_Pos                 (20UL)                    /*!< PORTF IER: P10 (Bit 20)                               */
#define PORTF_IER_P10_Msk                 (0x300000UL)              /*!< PORTF IER: P10 (Bitfield-Mask: 0x03)                  */
#define PORTF_IER_P9_Pos                  (18UL)                    /*!< PORTF IER: P9 (Bit 18)                                */
#define PORTF_IER_P9_Msk                  (0xc0000UL)               /*!< PORTF IER: P9 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P8_Pos                  (16UL)                    /*!< PORTF IER: P8 (Bit 16)                                */
#define PORTF_IER_P8_Msk                  (0x30000UL)               /*!< PORTF IER: P8 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P7_Pos                  (14UL)                    /*!< PORTF IER: P7 (Bit 14)                                */
#define PORTF_IER_P7_Msk                  (0xc000UL)                /*!< PORTF IER: P7 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P6_Pos                  (12UL)                    /*!< PORTF IER: P6 (Bit 12)                                */
#define PORTF_IER_P6_Msk                  (0x3000UL)                /*!< PORTF IER: P6 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P5_Pos                  (10UL)                    /*!< PORTF IER: P5 (Bit 10)                                */
#define PORTF_IER_P5_Msk                  (0xc00UL)                 /*!< PORTF IER: P5 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P4_Pos                  (8UL)                     /*!< PORTF IER: P4 (Bit 8)                                 */
#define PORTF_IER_P4_Msk                  (0x300UL)                 /*!< PORTF IER: P4 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P3_Pos                  (6UL)                     /*!< PORTF IER: P3 (Bit 6)                                 */
#define PORTF_IER_P3_Msk                  (0xc0UL)                  /*!< PORTF IER: P3 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P2_Pos                  (4UL)                     /*!< PORTF IER: P2 (Bit 4)                                 */
#define PORTF_IER_P2_Msk                  (0x30UL)                  /*!< PORTF IER: P2 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P1_Pos                  (2UL)                     /*!< PORTF IER: P1 (Bit 2)                                 */
#define PORTF_IER_P1_Msk                  (0xcUL)                   /*!< PORTF IER: P1 (Bitfield-Mask: 0x03)                   */
#define PORTF_IER_P0_Pos                  (0UL)                     /*!< PORTF IER: P0 (Bit 0)                                 */
#define PORTF_IER_P0_Msk                  (0x3UL)                   /*!< PORTF IER: P0 (Bitfield-Mask: 0x03)                   */
/* ==========================================================  ISR  ========================================================== */
#define PORTF_ISR_P15_Pos                 (30UL)                    /*!< PORTF ISR: P15 (Bit 30)                               */
#define PORTF_ISR_P15_Msk                 (0xc0000000UL)            /*!< PORTF ISR: P15 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P14_Pos                 (28UL)                    /*!< PORTF ISR: P14 (Bit 28)                               */
#define PORTF_ISR_P14_Msk                 (0x30000000UL)            /*!< PORTF ISR: P14 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P13_Pos                 (26UL)                    /*!< PORTF ISR: P13 (Bit 26)                               */
#define PORTF_ISR_P13_Msk                 (0xc000000UL)             /*!< PORTF ISR: P13 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P12_Pos                 (24UL)                    /*!< PORTF ISR: P12 (Bit 24)                               */
#define PORTF_ISR_P12_Msk                 (0x3000000UL)             /*!< PORTF ISR: P12 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P11_Pos                 (22UL)                    /*!< PORTF ISR: P11 (Bit 22)                               */
#define PORTF_ISR_P11_Msk                 (0xc00000UL)              /*!< PORTF ISR: P11 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P10_Pos                 (20UL)                    /*!< PORTF ISR: P10 (Bit 20)                               */
#define PORTF_ISR_P10_Msk                 (0x300000UL)              /*!< PORTF ISR: P10 (Bitfield-Mask: 0x03)                  */
#define PORTF_ISR_P9_Pos                  (18UL)                    /*!< PORTF ISR: P9 (Bit 18)                                */
#define PORTF_ISR_P9_Msk                  (0xc0000UL)               /*!< PORTF ISR: P9 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P8_Pos                  (16UL)                    /*!< PORTF ISR: P8 (Bit 16)                                */
#define PORTF_ISR_P8_Msk                  (0x30000UL)               /*!< PORTF ISR: P8 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P7_Pos                  (14UL)                    /*!< PORTF ISR: P7 (Bit 14)                                */
#define PORTF_ISR_P7_Msk                  (0xc000UL)                /*!< PORTF ISR: P7 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P6_Pos                  (12UL)                    /*!< PORTF ISR: P6 (Bit 12)                                */
#define PORTF_ISR_P6_Msk                  (0x3000UL)                /*!< PORTF ISR: P6 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P5_Pos                  (10UL)                    /*!< PORTF ISR: P5 (Bit 10)                                */
#define PORTF_ISR_P5_Msk                  (0xc00UL)                 /*!< PORTF ISR: P5 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P4_Pos                  (8UL)                     /*!< PORTF ISR: P4 (Bit 8)                                 */
#define PORTF_ISR_P4_Msk                  (0x300UL)                 /*!< PORTF ISR: P4 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P3_Pos                  (6UL)                     /*!< PORTF ISR: P3 (Bit 6)                                 */
#define PORTF_ISR_P3_Msk                  (0xc0UL)                  /*!< PORTF ISR: P3 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P2_Pos                  (4UL)                     /*!< PORTF ISR: P2 (Bit 4)                                 */
#define PORTF_ISR_P2_Msk                  (0x30UL)                  /*!< PORTF ISR: P2 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P1_Pos                  (2UL)                     /*!< PORTF ISR: P1 (Bit 2)                                 */
#define PORTF_ISR_P1_Msk                  (0xcUL)                   /*!< PORTF ISR: P1 (Bitfield-Mask: 0x03)                   */
#define PORTF_ISR_P0_Pos                  (0UL)                     /*!< PORTF ISR: P0 (Bit 0)                                 */
#define PORTF_ISR_P0_Msk                  (0x3UL)                   /*!< PORTF ISR: P0 (Bitfield-Mask: 0x03)                   */
/* ==========================================================  ICR  ========================================================== */
#define PORTF_ICR_P15_Pos                 (30UL)                    /*!< PORTF ICR: P15 (Bit 30)                               */
#define PORTF_ICR_P15_Msk                 (0xc0000000UL)            /*!< PORTF ICR: P15 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P14_Pos                 (28UL)                    /*!< PORTF ICR: P14 (Bit 28)                               */
#define PORTF_ICR_P14_Msk                 (0x30000000UL)            /*!< PORTF ICR: P14 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P13_Pos                 (26UL)                    /*!< PORTF ICR: P13 (Bit 26)                               */
#define PORTF_ICR_P13_Msk                 (0xc000000UL)             /*!< PORTF ICR: P13 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P12_Pos                 (24UL)                    /*!< PORTF ICR: P12 (Bit 24)                               */
#define PORTF_ICR_P12_Msk                 (0x3000000UL)             /*!< PORTF ICR: P12 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P11_Pos                 (22UL)                    /*!< PORTF ICR: P11 (Bit 22)                               */
#define PORTF_ICR_P11_Msk                 (0xc00000UL)              /*!< PORTF ICR: P11 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P10_Pos                 (20UL)                    /*!< PORTF ICR: P10 (Bit 20)                               */
#define PORTF_ICR_P10_Msk                 (0x300000UL)              /*!< PORTF ICR: P10 (Bitfield-Mask: 0x03)                  */
#define PORTF_ICR_P9_Pos                  (18UL)                    /*!< PORTF ICR: P9 (Bit 18)                                */
#define PORTF_ICR_P9_Msk                  (0xc0000UL)               /*!< PORTF ICR: P9 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P8_Pos                  (16UL)                    /*!< PORTF ICR: P8 (Bit 16)                                */
#define PORTF_ICR_P8_Msk                  (0x30000UL)               /*!< PORTF ICR: P8 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P7_Pos                  (14UL)                    /*!< PORTF ICR: P7 (Bit 14)                                */
#define PORTF_ICR_P7_Msk                  (0xc000UL)                /*!< PORTF ICR: P7 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P6_Pos                  (12UL)                    /*!< PORTF ICR: P6 (Bit 12)                                */
#define PORTF_ICR_P6_Msk                  (0x3000UL)                /*!< PORTF ICR: P6 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P5_Pos                  (10UL)                    /*!< PORTF ICR: P5 (Bit 10)                                */
#define PORTF_ICR_P5_Msk                  (0xc00UL)                 /*!< PORTF ICR: P5 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P4_Pos                  (8UL)                     /*!< PORTF ICR: P4 (Bit 8)                                 */
#define PORTF_ICR_P4_Msk                  (0x300UL)                 /*!< PORTF ICR: P4 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P3_Pos                  (6UL)                     /*!< PORTF ICR: P3 (Bit 6)                                 */
#define PORTF_ICR_P3_Msk                  (0xc0UL)                  /*!< PORTF ICR: P3 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P2_Pos                  (4UL)                     /*!< PORTF ICR: P2 (Bit 4)                                 */
#define PORTF_ICR_P2_Msk                  (0x30UL)                  /*!< PORTF ICR: P2 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P1_Pos                  (2UL)                     /*!< PORTF ICR: P1 (Bit 2)                                 */
#define PORTF_ICR_P1_Msk                  (0xcUL)                   /*!< PORTF ICR: P1 (Bitfield-Mask: 0x03)                   */
#define PORTF_ICR_P0_Pos                  (0UL)                     /*!< PORTF ICR: P0 (Bit 0)                                 */
#define PORTF_ICR_P0_Msk                  (0x3UL)                   /*!< PORTF ICR: P0 (Bitfield-Mask: 0x03)                   */
/* ==========================================================  STR  ========================================================== */
#define PORTF_STR_P4_Pos                  (8UL)                     /*!< PORTF STR: P4 (Bit 8)                                 */
#define PORTF_STR_P4_Msk                  (0x300UL)                 /*!< PORTF STR: P4 (Bitfield-Mask: 0x03)                   */
#define PORTF_STR_P3_Pos                  (6UL)                     /*!< PORTF STR: P3 (Bit 6)                                 */
#define PORTF_STR_P3_Msk                  (0xc0UL)                  /*!< PORTF STR: P3 (Bitfield-Mask: 0x03)                   */
#define PORTF_STR_P2_Pos                  (4UL)                     /*!< PORTF STR: P2 (Bit 4)                                 */
#define PORTF_STR_P2_Msk                  (0x30UL)                  /*!< PORTF STR: P2 (Bitfield-Mask: 0x03)                   */
#define PORTF_STR_P1_Pos                  (2UL)                     /*!< PORTF STR: P1 (Bit 2)                                 */
#define PORTF_STR_P1_Msk                  (0xcUL)                   /*!< PORTF STR: P1 (Bitfield-Mask: 0x03)                   */
#define PORTF_STR_P0_Pos                  (0UL)                     /*!< PORTF STR: P0 (Bit 0)                                 */
#define PORTF_STR_P0_Msk                  (0x3UL)                   /*!< PORTF STR: P0 (Bitfield-Mask: 0x03)                   */
/* =========================================================  PLSR  ========================================================== */
#define PORTF_PLSR_PF7LSB_Pos             (2UL)                     /*!< PORTF PLSR: PF7LSB (Bit 2)                            */
#define PORTF_PLSR_PF7LSB_Msk             (0x4UL)                   /*!< PORTF PLSR: PF7LSB (Bitfield-Mask: 0x01)              */
#define PORTF_PLSR_PF6LSB_Pos             (1UL)                     /*!< PORTF PLSR: PF6LSB (Bit 1)                            */
#define PORTF_PLSR_PF6LSB_Msk             (0x2UL)                   /*!< PORTF PLSR: PF6LSB (Bitfield-Mask: 0x01)              */
#define PORTF_PLSR_PF5LSB_Pos             (0UL)                     /*!< PORTF PLSR: PF5LSB (Bit 0)                            */
#define PORTF_PLSR_PF5LSB_Msk             (0x1UL)                   /*!< PORTF PLSR: PF5LSB (Bitfield-Mask: 0x01)              */


/* =========================================================================================================================== */
/* ================                                           PCU1                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  SPI2PMR  ======================================================== */
#define PCU1_SPI2PMR_SPI21_PRM_Pos        (1UL)                     /*!< PCU1 SPI2PMR: SPI21_PRM (Bit 1)                       */
#define PCU1_SPI2PMR_SPI21_PRM_Msk        (0x2UL)                   /*!< PCU1 SPI2PMR: SPI21_PRM (Bitfield-Mask: 0x01)         */
#define PCU1_SPI2PMR_SPI20_PRM_Pos        (0UL)                     /*!< PCU1 SPI2PMR: SPI20_PRM (Bit 0)                       */
#define PCU1_SPI2PMR_SPI20_PRM_Msk        (0x1UL)                   /*!< PCU1 SPI2PMR: SPI20_PRM (Bitfield-Mask: 0x01)         */


/* =========================================================================================================================== */
/* ================                                           PCU2                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  ISEGPEN  ======================================================== */
#define PCU2_ISEGPEN_ISEGENKEY_Pos        (0UL)                     /*!< PCU2 ISEGPEN: ISEGENKEY (Bit 0)                       */
#define PCU2_ISEGPEN_ISEGENKEY_Msk        (0xffffUL)                /*!< PCU2 ISEGPEN: ISEGENKEY (Bitfield-Mask: 0xffff)       */
/* =========================================================  ISEGR  ========================================================= */
#define PCU2_ISEGR_ISEG9_Pos              (9UL)                     /*!< PCU2 ISEGR: ISEG9 (Bit 9)                             */
#define PCU2_ISEGR_ISEG9_Msk              (0x200UL)                 /*!< PCU2 ISEGR: ISEG9 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG8_Pos              (8UL)                     /*!< PCU2 ISEGR: ISEG8 (Bit 8)                             */
#define PCU2_ISEGR_ISEG8_Msk              (0x100UL)                 /*!< PCU2 ISEGR: ISEG8 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG7_Pos              (7UL)                     /*!< PCU2 ISEGR: ISEG7 (Bit 7)                             */
#define PCU2_ISEGR_ISEG7_Msk              (0x80UL)                  /*!< PCU2 ISEGR: ISEG7 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG6_Pos              (6UL)                     /*!< PCU2 ISEGR: ISEG6 (Bit 6)                             */
#define PCU2_ISEGR_ISEG6_Msk              (0x40UL)                  /*!< PCU2 ISEGR: ISEG6 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG5_Pos              (5UL)                     /*!< PCU2 ISEGR: ISEG5 (Bit 5)                             */
#define PCU2_ISEGR_ISEG5_Msk              (0x20UL)                  /*!< PCU2 ISEGR: ISEG5 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG4_Pos              (4UL)                     /*!< PCU2 ISEGR: ISEG4 (Bit 4)                             */
#define PCU2_ISEGR_ISEG4_Msk              (0x10UL)                  /*!< PCU2 ISEGR: ISEG4 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG3_Pos              (3UL)                     /*!< PCU2 ISEGR: ISEG3 (Bit 3)                             */
#define PCU2_ISEGR_ISEG3_Msk              (0x8UL)                   /*!< PCU2 ISEGR: ISEG3 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG2_Pos              (2UL)                     /*!< PCU2 ISEGR: ISEG2 (Bit 2)                             */
#define PCU2_ISEGR_ISEG2_Msk              (0x4UL)                   /*!< PCU2 ISEGR: ISEG2 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG1_Pos              (1UL)                     /*!< PCU2 ISEGR: ISEG1 (Bit 1)                             */
#define PCU2_ISEGR_ISEG1_Msk              (0x2UL)                   /*!< PCU2 ISEGR: ISEG1 (Bitfield-Mask: 0x01)               */
#define PCU2_ISEGR_ISEG0_Pos              (0UL)                     /*!< PCU2 ISEGR: ISEG0 (Bit 0)                             */
#define PCU2_ISEGR_ISEG0_Msk              (0x1UL)                   /*!< PCU2 ISEGR: ISEG0 (Bitfield-Mask: 0x01)               */
/* ========================================================  ISEGIR  ========================================================= */
#define PCU2_ISEGIR_ISEG9_INV_Pos         (9UL)                     /*!< PCU2 ISEGIR: ISEG9_INV (Bit 9)                        */
#define PCU2_ISEGIR_ISEG9_INV_Msk         (0x200UL)                 /*!< PCU2 ISEGIR: ISEG9_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG8_INV_Pos         (8UL)                     /*!< PCU2 ISEGIR: ISEG8_INV (Bit 8)                        */
#define PCU2_ISEGIR_ISEG8_INV_Msk         (0x100UL)                 /*!< PCU2 ISEGIR: ISEG8_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG7_INV_Pos         (7UL)                     /*!< PCU2 ISEGIR: ISEG7_INV (Bit 7)                        */
#define PCU2_ISEGIR_ISEG7_INV_Msk         (0x80UL)                  /*!< PCU2 ISEGIR: ISEG7_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG6_INV_Pos         (6UL)                     /*!< PCU2 ISEGIR: ISEG6_INV (Bit 6)                        */
#define PCU2_ISEGIR_ISEG6_INV_Msk         (0x40UL)                  /*!< PCU2 ISEGIR: ISEG6_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG5_INV_Pos         (5UL)                     /*!< PCU2 ISEGIR: ISEG5_INV (Bit 5)                        */
#define PCU2_ISEGIR_ISEG5_INV_Msk         (0x20UL)                  /*!< PCU2 ISEGIR: ISEG5_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG4_INV_Pos         (4UL)                     /*!< PCU2 ISEGIR: ISEG4_INV (Bit 4)                        */
#define PCU2_ISEGIR_ISEG4_INV_Msk         (0x10UL)                  /*!< PCU2 ISEGIR: ISEG4_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG3_INV_Pos         (3UL)                     /*!< PCU2 ISEGIR: ISEG3_INV (Bit 3)                        */
#define PCU2_ISEGIR_ISEG3_INV_Msk         (0x8UL)                   /*!< PCU2 ISEGIR: ISEG3_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG2_INV_Pos         (2UL)                     /*!< PCU2 ISEGIR: ISEG2_INV (Bit 2)                        */
#define PCU2_ISEGIR_ISEG2_INV_Msk         (0x4UL)                   /*!< PCU2 ISEGIR: ISEG2_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG1_INV_Pos         (1UL)                     /*!< PCU2 ISEGIR: ISEG1_INV (Bit 1)                        */
#define PCU2_ISEGIR_ISEG1_INV_Msk         (0x2UL)                   /*!< PCU2 ISEGIR: ISEG1_INV (Bitfield-Mask: 0x01)          */
#define PCU2_ISEGIR_ISEG0_INV_Pos         (0UL)                     /*!< PCU2 ISEGIR: ISEG0_INV (Bit 0)                        */
#define PCU2_ISEGIR_ISEG0_INV_Msk         (0x1UL)                   /*!< PCU2 ISEGIR: ISEG0_INV (Bitfield-Mask: 0x01)          */
/* ========================================================  PORTEN  ========================================================= */
#define PCU2_PORTEN_PORTEN_Pos            (0UL)                     /*!< PCU2 PORTEN: PORTEN (Bit 0)                           */
#define PCU2_PORTEN_PORTEN_Msk            (0xffUL)                  /*!< PCU2 PORTEN: PORTEN (Bitfield-Mask: 0xff)             */


/* =========================================================================================================================== */
/* ================                                           CFMC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  MR  =========================================================== */
#define CFMC_MR_ACODE_Pos                 (0UL)                     /*!< CFMC MR: ACODE (Bit 0)                                */
#define CFMC_MR_ACODE_Msk                 (0x7fUL)                  /*!< CFMC MR: ACODE (Bitfield-Mask: 0x7f)                  */
/* ==========================================================  CR  =========================================================== */
#define CFMC_CR_BSAEN_Pos                 (25UL)                    /*!< CFMC CR: BSAEN (Bit 25)                               */
#define CFMC_CR_BSAEN_Msk                 (0x2000000UL)             /*!< CFMC CR: BSAEN (Bitfield-Mask: 0x01)                  */
#define CFMC_CR_RPAEN_Pos                 (24UL)                    /*!< CFMC CR: RPAEN (Bit 24)                               */
#define CFMC_CR_RPAEN_Msk                 (0x1000000UL)             /*!< CFMC CR: RPAEN (Bitfield-Mask: 0x01)                  */
#define CFMC_CR_SELFPGM_Pos               (23UL)                    /*!< CFMC CR: SELFPGM (Bit 23)                             */
#define CFMC_CR_SELFPGM_Msk               (0x800000UL)              /*!< CFMC CR: SELFPGM (Bitfield-Mask: 0x01)                */
#define CFMC_CR_IFAEN_Pos                 (12UL)                    /*!< CFMC CR: IFAEN (Bit 12)                               */
#define CFMC_CR_IFAEN_Msk                 (0x1000UL)                /*!< CFMC CR: IFAEN (Bitfield-Mask: 0x01)                  */
#define CFMC_CR_MAS_Pos                   (7UL)                     /*!< CFMC CR: MAS (Bit 7)                                  */
#define CFMC_CR_MAS_Msk                   (0x80UL)                  /*!< CFMC CR: MAS (Bitfield-Mask: 0x01)                    */
#define CFMC_CR_SECT4K_Pos                (6UL)                     /*!< CFMC CR: SECT4K (Bit 6)                               */
#define CFMC_CR_SECT4K_Msk                (0x40UL)                  /*!< CFMC CR: SECT4K (Bitfield-Mask: 0x01)                 */
#define CFMC_CR_SECT1K_Pos                (5UL)                     /*!< CFMC CR: SECT1K (Bit 5)                               */
#define CFMC_CR_SECT1K_Msk                (0x20UL)                  /*!< CFMC CR: SECT1K (Bitfield-Mask: 0x01)                 */
#define CFMC_CR_PMODE_Pos                 (4UL)                     /*!< CFMC CR: PMODE (Bit 4)                                */
#define CFMC_CR_PMODE_Msk                 (0x10UL)                  /*!< CFMC CR: PMODE (Bitfield-Mask: 0x01)                  */
#define CFMC_CR_WADCK_Pos                 (3UL)                     /*!< CFMC CR: WADCK (Bit 3)                                */
#define CFMC_CR_WADCK_Msk                 (0x8UL)                   /*!< CFMC CR: WADCK (Bitfield-Mask: 0x01)                  */
#define CFMC_CR_PGM_Pos                   (2UL)                     /*!< CFMC CR: PGM (Bit 2)                                  */
#define CFMC_CR_PGM_Msk                   (0x4UL)                   /*!< CFMC CR: PGM (Bitfield-Mask: 0x01)                    */
#define CFMC_CR_ERS_Pos                   (1UL)                     /*!< CFMC CR: ERS (Bit 1)                                  */
#define CFMC_CR_ERS_Msk                   (0x2UL)                   /*!< CFMC CR: ERS (Bitfield-Mask: 0x01)                    */
#define CFMC_CR_HVEN_Pos                  (0UL)                     /*!< CFMC CR: HVEN (Bit 0)                                 */
#define CFMC_CR_HVEN_Msk                  (0x1UL)                   /*!< CFMC CR: HVEN (Bitfield-Mask: 0x01)                   */
/* ==========================================================  AR  =========================================================== */
#define CFMC_AR_FADDR_Pos                 (0UL)                     /*!< CFMC AR: FADDR (Bit 0)                                */
#define CFMC_AR_FADDR_Msk                 (0xffffUL)                /*!< CFMC AR: FADDR (Bitfield-Mask: 0xffff)                */
/* ==========================================================  DR  =========================================================== */
#define CFMC_DR_FDATA_Pos                 (0UL)                     /*!< CFMC DR: FDATA (Bit 0)                                */
#define CFMC_DR_FDATA_Msk                 (0xffffffffUL)            /*!< CFMC DR: FDATA (Bitfield-Mask: 0xffffffff)            */
/* =========================================================  BUSY  ========================================================== */
#define CFMC_BUSY_WRBUSY_Pos              (0UL)                     /*!< CFMC BUSY: WRBUSY (Bit 0)                             */
#define CFMC_BUSY_WRBUSY_Msk              (0x1UL)                   /*!< CFMC BUSY: WRBUSY (Bitfield-Mask: 0x01)               */
/* =======================================================  CRCCCITT  ======================================================== */
#define CFMC_CRCCCITT_CRC_Pos             (0UL)                     /*!< CFMC CRCCCITT: CRC (Bit 0)                            */
#define CFMC_CRCCCITT_CRC_Msk             (0xffffUL)                /*!< CFMC CRCCCITT: CRC (Bitfield-Mask: 0xffff)            */
/* ==========================================================  CFG  ========================================================== */
#define CFMC_CFG_WTIDKY_Pos               (16UL)                    /*!< CFMC CFG: WTIDKY (Bit 16)                             */
#define CFMC_CFG_WTIDKY_Msk               (0xffff0000UL)            /*!< CFMC CFG: WTIDKY (Bitfield-Mask: 0xffff)              */
#define CFMC_CFG_WAIT_Pos                 (8UL)                     /*!< CFMC CFG: WAIT (Bit 8)                                */
#define CFMC_CFG_WAIT_Msk                 (0x700UL)                 /*!< CFMC CFG: WAIT (Bitfield-Mask: 0x07)                  */
#define CFMC_CFG_CRCINIT_Pos              (7UL)                     /*!< CFMC CFG: CRCINIT (Bit 7)                             */
#define CFMC_CFG_CRCINIT_Msk              (0x80UL)                  /*!< CFMC CFG: CRCINIT (Bitfield-Mask: 0x01)               */
#define CFMC_CFG_CRCEN_Pos                (6UL)                     /*!< CFMC CFG: CRCEN (Bit 6)                               */
#define CFMC_CFG_CRCEN_Msk                (0x40UL)                  /*!< CFMC CFG: CRCEN (Bitfield-Mask: 0x01)                 */
/* =========================================================  WPROT  ========================================================= */
#define CFMC_WPROT_WPROT_Pos              (0UL)                     /*!< CFMC WPROT: WPROT (Bit 0)                             */
#define CFMC_WPROT_WPROT_Msk              (0xffffUL)                /*!< CFMC WPROT: WPROT (Bitfield-Mask: 0xffff)             */
/* =========================================================  RPROT  ========================================================= */
#define CFMC_RPROT_DBGMOD_Pos             (31UL)                    /*!< CFMC RPROT: DBGMOD (Bit 31)                           */
#define CFMC_RPROT_DBGMOD_Msk             (0x80000000UL)            /*!< CFMC RPROT: DBGMOD (Bitfield-Mask: 0x01)              */
#define CFMC_RPROT_SRBOOT_Pos             (30UL)                    /*!< CFMC RPROT: SRBOOT (Bit 30)                           */
#define CFMC_RPROT_SRBOOT_Msk             (0x40000000UL)            /*!< CFMC RPROT: SRBOOT (Bitfield-Mask: 0x01)              */
#define CFMC_RPROT_PWMATCH_Pos            (26UL)                    /*!< CFMC RPROT: PWMATCH (Bit 26)                          */
#define CFMC_RPROT_PWMATCH_Msk            (0x4000000UL)             /*!< CFMC RPROT: PWMATCH (Bitfield-Mask: 0x01)             */
#define CFMC_RPROT_RPBERSD_Pos            (25UL)                    /*!< CFMC RPROT: RPBERSD (Bit 25)                          */
#define CFMC_RPROT_RPBERSD_Msk            (0x2000000UL)             /*!< CFMC RPROT: RPBERSD (Bitfield-Mask: 0x01)             */
#define CFMC_RPROT_CERSD_Pos              (24UL)                    /*!< CFMC RPROT: CERSD (Bit 24)                            */
#define CFMC_RPROT_CERSD_Msk              (0x1000000UL)             /*!< CFMC RPROT: CERSD (Bitfield-Mask: 0x01)               */
#define CFMC_RPROT_LVL2_STS_Pos           (17UL)                    /*!< CFMC RPROT: LVL2_STS (Bit 17)                         */
#define CFMC_RPROT_LVL2_STS_Msk           (0x20000UL)               /*!< CFMC RPROT: LVL2_STS (Bitfield-Mask: 0x01)            */
#define CFMC_RPROT_LVL1_STS_Pos           (16UL)                    /*!< CFMC RPROT: LVL1_STS (Bit 16)                         */
#define CFMC_RPROT_LVL1_STS_Msk           (0x10000UL)               /*!< CFMC RPROT: LVL1_STS (Bitfield-Mask: 0x01)            */
#define CFMC_RPROT_LVL2_EN_Pos            (9UL)                     /*!< CFMC RPROT: LVL2_EN (Bit 9)                           */
#define CFMC_RPROT_LVL2_EN_Msk            (0x200UL)                 /*!< CFMC RPROT: LVL2_EN (Bitfield-Mask: 0x01)             */
#define CFMC_RPROT_LVL1_EN_Pos            (8UL)                     /*!< CFMC RPROT: LVL1_EN (Bit 8)                           */
#define CFMC_RPROT_LVL1_EN_Msk            (0x100UL)                 /*!< CFMC RPROT: LVL1_EN (Bitfield-Mask: 0x01)             */
#define CFMC_RPROT_RPROT_Pos              (0UL)                     /*!< CFMC RPROT: RPROT (Bit 0)                             */
#define CFMC_RPROT_RPROT_Msk              (0xffUL)                  /*!< CFMC RPROT: RPROT (Bitfield-Mask: 0xff)               */
/* =========================================================  PWIN  ========================================================== */
#define CFMC_PWIN_PWIN_Pos                (0UL)                     /*!< CFMC PWIN: PWIN (Bit 0)                               */
#define CFMC_PWIN_PWIN_Msk                (0xffffffffUL)            /*!< CFMC PWIN: PWIN (Bitfield-Mask: 0xffffffff)           */
/* ========================================================  PWPRST  ========================================================= */
#define CFMC_PWPRST_PWPRST_Pos            (0UL)                     /*!< CFMC PWPRST: PWPRST (Bit 0)                           */
#define CFMC_PWPRST_PWPRST_Msk            (0xffffffffUL)            /*!< CFMC PWPRST: PWPRST (Bitfield-Mask: 0xffffffff)       */
/* ==========================================================  BCR  ========================================================== */
#define CFMC_BCR_WTIDKY_Pos               (16UL)                    /*!< CFMC BCR: WTIDKY (Bit 16)                             */
#define CFMC_BCR_WTIDKY_Msk               (0xffff0000UL)            /*!< CFMC BCR: WTIDKY (Bitfield-Mask: 0xffff)              */
#define CFMC_BCR_BSE_Pos                  (4UL)                     /*!< CFMC BCR: BSE (Bit 4)                                 */
#define CFMC_BCR_BSE_Msk                  (0x10UL)                  /*!< CFMC BCR: BSE (Bitfield-Mask: 0x01)                   */
#define CFMC_BCR_BSW_Pos                  (0UL)                     /*!< CFMC BCR: BSW (Bit 0)                                 */
#define CFMC_BCR_BSW_Msk                  (0x1UL)                   /*!< CFMC BCR: BSW (Bitfield-Mask: 0x01)                   */
/* ==========================================================  BSR  ========================================================== */
#define CFMC_BSR_BSERR_Pos                (12UL)                    /*!< CFMC BSR: BSERR (Bit 12)                              */
#define CFMC_BSR_BSERR_Msk                (0x1000UL)                /*!< CFMC BSR: BSERR (Bitfield-Mask: 0x01)                 */
#define CFMC_BSR_CBF_Pos                  (8UL)                     /*!< CFMC BSR: CBF (Bit 8)                                 */
#define CFMC_BSR_CBF_Msk                  (0x100UL)                 /*!< CFMC BSR: CBF (Bitfield-Mask: 0x01)                   */
#define CFMC_BSR_BSST_Pos                 (4UL)                     /*!< CFMC BSR: BSST (Bit 4)                                */
#define CFMC_BSR_BSST_Msk                 (0x10UL)                  /*!< CFMC BSR: BSST (Bitfield-Mask: 0x01)                  */
#define CFMC_BSR_BSWST_Pos                (0UL)                     /*!< CFMC BSR: BSWST (Bit 0)                               */
#define CFMC_BSR_BSWST_Msk                (0x1UL)                   /*!< CFMC BSR: BSWST (Bitfield-Mask: 0x01)                 */
/* ========================================================  ABWPROT  ======================================================== */
#define CFMC_ABWPROT_AB_KEY_Pos           (20UL)                    /*!< CFMC ABWPROT: AB_KEY (Bit 20)                         */
#define CFMC_ABWPROT_AB_KEY_Msk           (0xfff00000UL)            /*!< CFMC ABWPROT: AB_KEY (Bitfield-Mask: 0xfff)           */
#define CFMC_ABWPROT_AB_WPROT_Pos         (0UL)                     /*!< CFMC ABWPROT: AB_WPROT (Bit 0)                        */
#define CFMC_ABWPROT_AB_WPROT_Msk         (0xffffUL)                /*!< CFMC ABWPROT: AB_WPROT (Bitfield-Mask: 0xffff)        */
/* ========================================================  NBWPROT  ======================================================== */
#define CFMC_NBWPROT_NB_KEY_Pos           (20UL)                    /*!< CFMC NBWPROT: NB_KEY (Bit 20)                         */
#define CFMC_NBWPROT_NB_KEY_Msk           (0xfff00000UL)            /*!< CFMC NBWPROT: NB_KEY (Bitfield-Mask: 0xfff)           */
#define CFMC_NBWPROT_NB_WPROT_Pos         (0UL)                     /*!< CFMC NBWPROT: NB_WPROT (Bit 0)                        */
#define CFMC_NBWPROT_NB_WPROT_Msk         (0xffffUL)                /*!< CFMC NBWPROT: NB_WPROT (Bitfield-Mask: 0xffff)        */


/* =========================================================================================================================== */
/* ================                                           DFMC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  MR  =========================================================== */
#define DFMC_MR_ACODE_Pos                 (0UL)                     /*!< DFMC MR: ACODE (Bit 0)                                */
#define DFMC_MR_ACODE_Msk                 (0x7fUL)                  /*!< DFMC MR: ACODE (Bitfield-Mask: 0x7f)                  */
/* ==========================================================  CR  =========================================================== */
#define DFMC_CR_RPAEN_Pos                 (24UL)                    /*!< DFMC CR: RPAEN (Bit 24)                               */
#define DFMC_CR_RPAEN_Msk                 (0x1000000UL)             /*!< DFMC CR: RPAEN (Bitfield-Mask: 0x01)                  */
#define DFMC_CR_WPGMEN_Pos                (16UL)                    /*!< DFMC CR: WPGMEN (Bit 16)                              */
#define DFMC_CR_WPGMEN_Msk                (0x10000UL)               /*!< DFMC CR: WPGMEN (Bitfield-Mask: 0x01)                 */
#define DFMC_CR_MAS_Pos                   (7UL)                     /*!< DFMC CR: MAS (Bit 7)                                  */
#define DFMC_CR_MAS_Msk                   (0x80UL)                  /*!< DFMC CR: MAS (Bitfield-Mask: 0x01)                    */
#define DFMC_CR_SECT4K_Pos                (6UL)                     /*!< DFMC CR: SECT4K (Bit 6)                               */
#define DFMC_CR_SECT4K_Msk                (0x40UL)                  /*!< DFMC CR: SECT4K (Bitfield-Mask: 0x01)                 */
#define DFMC_CR_SECT1K_Pos                (5UL)                     /*!< DFMC CR: SECT1K (Bit 5)                               */
#define DFMC_CR_SECT1K_Msk                (0x20UL)                  /*!< DFMC CR: SECT1K (Bitfield-Mask: 0x01)                 */
#define DFMC_CR_PMODE_Pos                 (4UL)                     /*!< DFMC CR: PMODE (Bit 4)                                */
#define DFMC_CR_PMODE_Msk                 (0x10UL)                  /*!< DFMC CR: PMODE (Bitfield-Mask: 0x01)                  */
#define DFMC_CR_WADCK_Pos                 (3UL)                     /*!< DFMC CR: WADCK (Bit 3)                                */
#define DFMC_CR_WADCK_Msk                 (0x8UL)                   /*!< DFMC CR: WADCK (Bitfield-Mask: 0x01)                  */
#define DFMC_CR_PGM_Pos                   (2UL)                     /*!< DFMC CR: PGM (Bit 2)                                  */
#define DFMC_CR_PGM_Msk                   (0x4UL)                   /*!< DFMC CR: PGM (Bitfield-Mask: 0x01)                    */
#define DFMC_CR_ERS_Pos                   (1UL)                     /*!< DFMC CR: ERS (Bit 1)                                  */
#define DFMC_CR_ERS_Msk                   (0x2UL)                   /*!< DFMC CR: ERS (Bitfield-Mask: 0x01)                    */
#define DFMC_CR_HVEN_Pos                  (0UL)                     /*!< DFMC CR: HVEN (Bit 0)                                 */
#define DFMC_CR_HVEN_Msk                  (0x1UL)                   /*!< DFMC CR: HVEN (Bitfield-Mask: 0x01)                   */
/* ==========================================================  AR  =========================================================== */
#define DFMC_AR_FADDR_Pos                 (0UL)                     /*!< DFMC AR: FADDR (Bit 0)                                */
#define DFMC_AR_FADDR_Msk                 (0xffffUL)                /*!< DFMC AR: FADDR (Bitfield-Mask: 0xffff)                */
/* ==========================================================  DR  =========================================================== */
#define DFMC_DR_FDATA_Pos                 (0UL)                     /*!< DFMC DR: FDATA (Bit 0)                                */
#define DFMC_DR_FDATA_Msk                 (0xffffffffUL)            /*!< DFMC DR: FDATA (Bitfield-Mask: 0xffffffff)            */
/* =========================================================  BUSY  ========================================================== */
#define DFMC_BUSY_WRBUSY_Pos              (0UL)                     /*!< DFMC BUSY: WRBUSY (Bit 0)                             */
#define DFMC_BUSY_WRBUSY_Msk              (0x1UL)                   /*!< DFMC BUSY: WRBUSY (Bitfield-Mask: 0x01)               */
/* =======================================================  CRCCCITT  ======================================================== */
#define DFMC_CRCCCITT_CRC_Pos             (0UL)                     /*!< DFMC CRCCCITT: CRC (Bit 0)                            */
#define DFMC_CRCCCITT_CRC_Msk             (0xffffUL)                /*!< DFMC CRCCCITT: CRC (Bitfield-Mask: 0xffff)            */
/* ==========================================================  CFG  ========================================================== */
#define DFMC_CFG_WTIDKY_Pos               (16UL)                    /*!< DFMC CFG: WTIDKY (Bit 16)                             */
#define DFMC_CFG_WTIDKY_Msk               (0xffff0000UL)            /*!< DFMC CFG: WTIDKY (Bitfield-Mask: 0xffff)              */
#define DFMC_CFG_WAIT_Pos                 (8UL)                     /*!< DFMC CFG: WAIT (Bit 8)                                */
#define DFMC_CFG_WAIT_Msk                 (0x700UL)                 /*!< DFMC CFG: WAIT (Bitfield-Mask: 0x07)                  */
#define DFMC_CFG_CRCINIT_Pos              (7UL)                     /*!< DFMC CFG: CRCINIT (Bit 7)                             */
#define DFMC_CFG_CRCINIT_Msk              (0x80UL)                  /*!< DFMC CFG: CRCINIT (Bitfield-Mask: 0x01)               */
#define DFMC_CFG_CRCEN_Pos                (6UL)                     /*!< DFMC CFG: CRCEN (Bit 6)                               */
#define DFMC_CFG_CRCEN_Msk                (0x40UL)                  /*!< DFMC CFG: CRCEN (Bitfield-Mask: 0x01)                 */
/* =========================================================  WPROT  ========================================================= */
#define DFMC_WPROT_WPROT_Pos              (0UL)                     /*!< DFMC WPROT: WPROT (Bit 0)                             */
#define DFMC_WPROT_WPROT_Msk              (0xffffffffUL)            /*!< DFMC WPROT: WPROT (Bitfield-Mask: 0xffffffff)         */
/* =========================================================  RPROT  ========================================================= */
#define DFMC_RPROT_DBGMOD_Pos             (31UL)                    /*!< DFMC RPROT: DBGMOD (Bit 31)                           */
#define DFMC_RPROT_DBGMOD_Msk             (0x80000000UL)            /*!< DFMC RPROT: DBGMOD (Bitfield-Mask: 0x01)              */
#define DFMC_RPROT_SRBOOT_Pos             (30UL)                    /*!< DFMC RPROT: SRBOOT (Bit 30)                           */
#define DFMC_RPROT_SRBOOT_Msk             (0x40000000UL)            /*!< DFMC RPROT: SRBOOT (Bitfield-Mask: 0x01)              */
#define DFMC_RPROT_PWMATCH_Pos            (26UL)                    /*!< DFMC RPROT: PWMATCH (Bit 26)                          */
#define DFMC_RPROT_PWMATCH_Msk            (0x4000000UL)             /*!< DFMC RPROT: PWMATCH (Bitfield-Mask: 0x01)             */
#define DFMC_RPROT_RPBERSD_Pos            (25UL)                    /*!< DFMC RPROT: RPBERSD (Bit 25)                          */
#define DFMC_RPROT_RPBERSD_Msk            (0x2000000UL)             /*!< DFMC RPROT: RPBERSD (Bitfield-Mask: 0x01)             */
#define DFMC_RPROT_CERSD_Pos              (24UL)                    /*!< DFMC RPROT: CERSD (Bit 24)                            */
#define DFMC_RPROT_CERSD_Msk              (0x1000000UL)             /*!< DFMC RPROT: CERSD (Bitfield-Mask: 0x01)               */
#define DFMC_RPROT_RPROT_STS_Pos          (16UL)                    /*!< DFMC RPROT: RPROT_STS (Bit 16)                        */
#define DFMC_RPROT_RPROT_STS_Msk          (0x10000UL)               /*!< DFMC RPROT: RPROT_STS (Bitfield-Mask: 0x01)           */
#define DFMC_RPROT_RPROT_EN_Pos           (8UL)                     /*!< DFMC RPROT: RPROT_EN (Bit 8)                          */
#define DFMC_RPROT_RPROT_EN_Msk           (0x100UL)                 /*!< DFMC RPROT: RPROT_EN (Bitfield-Mask: 0x01)            */
#define DFMC_RPROT_RPROT_Pos              (0UL)                     /*!< DFMC RPROT: RPROT (Bit 0)                             */
#define DFMC_RPROT_RPROT_Msk              (0xffUL)                  /*!< DFMC RPROT: RPROT (Bitfield-Mask: 0xff)               */
/* =========================================================  PWIN  ========================================================== */
#define DFMC_PWIN_PWIN_Pos                (0UL)                     /*!< DFMC PWIN: PWIN (Bit 0)                               */
#define DFMC_PWIN_PWIN_Msk                (0xffffffffUL)            /*!< DFMC PWIN: PWIN (Bitfield-Mask: 0xffffffff)           */
/* ========================================================  PWPRST  ========================================================= */
#define DFMC_PWPRST_PWPRST_Pos            (0UL)                     /*!< DFMC PWPRST: PWPRST (Bit 0)                           */
#define DFMC_PWPRST_PWPRST_Msk            (0xffffffffUL)            /*!< DFMC PWPRST: PWPRST (Bitfield-Mask: 0xffffffff)       */


/* =========================================================================================================================== */
/* ================                                           DMAC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define DMAC_CR_TRANSCNT_Pos              (16UL)                    /*!< DMAC CR: TRANSCNT (Bit 16)                            */
#define DMAC_CR_TRANSCNT_Msk              (0xfff0000UL)             /*!< DMAC CR: TRANSCNT (Bitfield-Mask: 0xfff)              */
#define DMAC_CR_PERISEL_Pos               (8UL)                     /*!< DMAC CR: PERISEL (Bit 8)                              */
#define DMAC_CR_PERISEL_Msk               (0x1f00UL)                /*!< DMAC CR: PERISEL (Bitfield-Mask: 0x1f)                */
#define DMAC_CR_SIZE_Pos                  (2UL)                     /*!< DMAC CR: SIZE (Bit 2)                                 */
#define DMAC_CR_SIZE_Msk                  (0xcUL)                   /*!< DMAC CR: SIZE (Bitfield-Mask: 0x03)                   */
#define DMAC_CR_DIR_Pos                   (1UL)                     /*!< DMAC CR: DIR (Bit 1)                                  */
#define DMAC_CR_DIR_Msk                   (0x2UL)                   /*!< DMAC CR: DIR (Bitfield-Mask: 0x01)                    */
/* ==========================================================  SR  =========================================================== */
#define DMAC_SR_EOT_Pos                   (7UL)                     /*!< DMAC SR: EOT (Bit 7)                                  */
#define DMAC_SR_EOT_Msk                   (0x80UL)                  /*!< DMAC SR: EOT (Bitfield-Mask: 0x01)                    */
#define DMAC_SR_DMARC_Pos                 (4UL)                     /*!< DMAC SR: DMARC (Bit 4)                                */
#define DMAC_SR_DMARC_Msk                 (0x10UL)                  /*!< DMAC SR: DMARC (Bitfield-Mask: 0x01)                  */
#define DMAC_SR_DMAEN_Pos                 (0UL)                     /*!< DMAC SR: DMAEN (Bit 0)                                */
#define DMAC_SR_DMAEN_Msk                 (0x1UL)                   /*!< DMAC SR: DMAEN (Bitfield-Mask: 0x01)                  */
/* ==========================================================  PAR  ========================================================== */
#define DMAC_PAR_PAR_Pos                  (0UL)                     /*!< DMAC PAR: PAR (Bit 0)                                 */
#define DMAC_PAR_PAR_Msk                  (0xffffUL)                /*!< DMAC PAR: PAR (Bitfield-Mask: 0xffff)                 */
/* ==========================================================  MAR  ========================================================== */
#define DMAC_MAR_OFFSET_Pos               (29UL)                    /*!< DMAC MAR: OFFSET (Bit 29)                             */
#define DMAC_MAR_OFFSET_Msk               (0x60000000UL)            /*!< DMAC MAR: OFFSET (Bitfield-Mask: 0x03)                */
#define DMAC_MAR_MAR_Pos                  (0UL)                     /*!< DMAC MAR: MAR (Bit 0)                                 */
#define DMAC_MAR_MAR_Msk                  (0xffffUL)                /*!< DMAC MAR: MAR (Bitfield-Mask: 0xffff)                 */


/* =========================================================================================================================== */
/* ================                                            WDT                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define WDT_CR_WTIDKY_Pos                 (16UL)                    /*!< WDT CR: WTIDKY (Bit 16)                               */
#define WDT_CR_WTIDKY_Msk                 (0xffff0000UL)            /*!< WDT CR: WTIDKY (Bitfield-Mask: 0xffff)                */
#define WDT_CR_RSTEN_Pos                  (10UL)                    /*!< WDT CR: RSTEN (Bit 10)                                */
#define WDT_CR_RSTEN_Msk                  (0xfc00UL)                /*!< WDT CR: RSTEN (Bitfield-Mask: 0x3f)                   */
#define WDT_CR_CNTEN_Pos                  (4UL)                     /*!< WDT CR: CNTEN (Bit 4)                                 */
#define WDT_CR_CNTEN_Msk                  (0x3f0UL)                 /*!< WDT CR: CNTEN (Bitfield-Mask: 0x3f)                   */
#define WDT_CR_WINMIEN_Pos                (3UL)                     /*!< WDT CR: WINMIEN (Bit 3)                               */
#define WDT_CR_WINMIEN_Msk                (0x8UL)                   /*!< WDT CR: WINMIEN (Bitfield-Mask: 0x01)                 */
#define WDT_CR_UNFIEN_Pos                 (2UL)                     /*!< WDT CR: UNFIEN (Bit 2)                                */
#define WDT_CR_UNFIEN_Msk                 (0x4UL)                   /*!< WDT CR: UNFIEN (Bitfield-Mask: 0x01)                  */
#define WDT_CR_CLKDIV_Pos                 (0UL)                     /*!< WDT CR: CLKDIV (Bit 0)                                */
#define WDT_CR_CLKDIV_Msk                 (0x3UL)                   /*!< WDT CR: CLKDIV (Bitfield-Mask: 0x03)                  */
/* ==========================================================  SR  =========================================================== */
#define WDT_SR_DBGCNTEN_Pos               (7UL)                     /*!< WDT SR: DBGCNTEN (Bit 7)                              */
#define WDT_SR_DBGCNTEN_Msk               (0x80UL)                  /*!< WDT SR: DBGCNTEN (Bitfield-Mask: 0x01)                */
#define WDT_SR_WINMIFLAG_Pos              (1UL)                     /*!< WDT SR: WINMIFLAG (Bit 1)                             */
#define WDT_SR_WINMIFLAG_Msk              (0x2UL)                   /*!< WDT SR: WINMIFLAG (Bitfield-Mask: 0x01)               */
#define WDT_SR_UNFIFLAG_Pos               (0UL)                     /*!< WDT SR: UNFIFLAG (Bit 0)                              */
#define WDT_SR_UNFIFLAG_Msk               (0x1UL)                   /*!< WDT SR: UNFIFLAG (Bitfield-Mask: 0x01)                */
/* ==========================================================  DR  =========================================================== */
#define WDT_DR_DATA_Pos                   (0UL)                     /*!< WDT DR: DATA (Bit 0)                                  */
#define WDT_DR_DATA_Msk                   (0xffffffUL)              /*!< WDT DR: DATA (Bitfield-Mask: 0xffffff)                */
/* ==========================================================  CNT  ========================================================== */
#define WDT_CNT_CNT_Pos                   (0UL)                     /*!< WDT CNT: CNT (Bit 0)                                  */
#define WDT_CNT_CNT_Msk                   (0xffffffUL)              /*!< WDT CNT: CNT (Bitfield-Mask: 0xffffff)                */
/* =========================================================  WINDR  ========================================================= */
#define WDT_WINDR_WDATA_Pos               (0UL)                     /*!< WDT WINDR: WDATA (Bit 0)                              */
#define WDT_WINDR_WDATA_Msk               (0xffffffUL)              /*!< WDT WINDR: WDATA (Bitfield-Mask: 0xffffff)            */
/* =========================================================  CNTR  ========================================================== */
#define WDT_CNTR_CNTR_Pos                 (0UL)                     /*!< WDT CNTR: CNTR (Bit 0)                                */
#define WDT_CNTR_CNTR_Msk                 (0xffUL)                  /*!< WDT CNTR: CNTR (Bitfield-Mask: 0xff)                  */


/* =========================================================================================================================== */
/* ================                                            WT                                             ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define WT_CR_WTEN_Pos                    (7UL)                     /*!< WT CR: WTEN (Bit 7)                                   */
#define WT_CR_WTEN_Msk                    (0x80UL)                  /*!< WT CR: WTEN (Bitfield-Mask: 0x01)                     */
#define WT_CR_WTINTV_Pos                  (4UL)                     /*!< WT CR: WTINTV (Bit 4)                                 */
#define WT_CR_WTINTV_Msk                  (0x30UL)                  /*!< WT CR: WTINTV (Bitfield-Mask: 0x03)                   */
#define WT_CR_WTIEN_Pos                   (3UL)                     /*!< WT CR: WTIEN (Bit 3)                                  */
#define WT_CR_WTIEN_Msk                   (0x8UL)                   /*!< WT CR: WTIEN (Bitfield-Mask: 0x01)                    */
#define WT_CR_WTIFLAG_Pos                 (1UL)                     /*!< WT CR: WTIFLAG (Bit 1)                                */
#define WT_CR_WTIFLAG_Msk                 (0x2UL)                   /*!< WT CR: WTIFLAG (Bitfield-Mask: 0x01)                  */
#define WT_CR_WTCLR_Pos                   (0UL)                     /*!< WT CR: WTCLR (Bit 0)                                  */
#define WT_CR_WTCLR_Msk                   (0x1UL)                   /*!< WT CR: WTCLR (Bitfield-Mask: 0x01)                    */
/* ==========================================================  DR  =========================================================== */
#define WT_DR_WTDATA_Pos                  (0UL)                     /*!< WT DR: WTDATA (Bit 0)                                 */
#define WT_DR_WTDATA_Msk                  (0xfffUL)                 /*!< WT DR: WTDATA (Bitfield-Mask: 0xfff)                  */
/* ==========================================================  CNT  ========================================================== */
#define WT_CNT_CNT_Pos                    (0UL)                     /*!< WT CNT: CNT (Bit 0)                                   */
#define WT_CNT_CNT_Msk                    (0xfffUL)                 /*!< WT CNT: CNT (Bitfield-Mask: 0xfff)                    */


/* =========================================================================================================================== */
/* ================                                          TIMER1n                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define TIMER1n_CR_SSYNC_Pos              (31UL)                    /*!< TIMER1n CR: SSYNC (Bit 31)                            */
#define TIMER1n_CR_SSYNC_Msk              (0x80000000UL)            /*!< TIMER1n CR: SSYNC (Bitfield-Mask: 0x01)               */
#define TIMER1n_CR_CSYNC_Pos              (30UL)                    /*!< TIMER1n CR: CSYNC (Bit 30)                            */
#define TIMER1n_CR_CSYNC_Msk              (0x40000000UL)            /*!< TIMER1n CR: CSYNC (Bitfield-Mask: 0x01)               */
#define TIMER1n_CR_EN_Pos                 (15UL)                    /*!< TIMER1n CR: EN (Bit 15)                               */
#define TIMER1n_CR_EN_Msk                 (0x8000UL)                /*!< TIMER1n CR: EN (Bitfield-Mask: 0x01)                  */
#define TIMER1n_CR_CLK_Pos                (14UL)                    /*!< TIMER1n CR: CLK (Bit 14)                              */
#define TIMER1n_CR_CLK_Msk                (0x4000UL)                /*!< TIMER1n CR: CLK (Bitfield-Mask: 0x01)                 */
#define TIMER1n_CR_MS_Pos                 (12UL)                    /*!< TIMER1n CR: MS (Bit 12)                               */
#define TIMER1n_CR_MS_Msk                 (0x3000UL)                /*!< TIMER1n CR: MS (Bitfield-Mask: 0x03)                  */
#define TIMER1n_CR_ECE_Pos                (11UL)                    /*!< TIMER1n CR: ECE (Bit 11)                              */
#define TIMER1n_CR_ECE_Msk                (0x800UL)                 /*!< TIMER1n CR: ECE (Bitfield-Mask: 0x01)                 */
#define TIMER1n_CR_OPOL_Pos               (8UL)                     /*!< TIMER1n CR: OPOL (Bit 8)                              */
#define TIMER1n_CR_OPOL_Msk               (0x100UL)                 /*!< TIMER1n CR: OPOL (Bitfield-Mask: 0x01)                */
#define TIMER1n_CR_CPOL_Pos               (6UL)                     /*!< TIMER1n CR: CPOL (Bit 6)                              */
#define TIMER1n_CR_CPOL_Msk               (0xc0UL)                  /*!< TIMER1n CR: CPOL (Bitfield-Mask: 0x03)                */
#define TIMER1n_CR_MIEN_Pos               (5UL)                     /*!< TIMER1n CR: MIEN (Bit 5)                              */
#define TIMER1n_CR_MIEN_Msk               (0x20UL)                  /*!< TIMER1n CR: MIEN (Bitfield-Mask: 0x01)                */
#define TIMER1n_CR_CIEN_Pos               (4UL)                     /*!< TIMER1n CR: CIEN (Bit 4)                              */
#define TIMER1n_CR_CIEN_Msk               (0x10UL)                  /*!< TIMER1n CR: CIEN (Bitfield-Mask: 0x01)                */
#define TIMER1n_CR_MIFLAG_Pos             (3UL)                     /*!< TIMER1n CR: MIFLAG (Bit 3)                            */
#define TIMER1n_CR_MIFLAG_Msk             (0x8UL)                   /*!< TIMER1n CR: MIFLAG (Bitfield-Mask: 0x01)              */
#define TIMER1n_CR_CIFLAG_Pos             (2UL)                     /*!< TIMER1n CR: CIFLAG (Bit 2)                            */
#define TIMER1n_CR_CIFLAG_Msk             (0x4UL)                   /*!< TIMER1n CR: CIFLAG (Bitfield-Mask: 0x01)              */
#define TIMER1n_CR_PAU_Pos                (1UL)                     /*!< TIMER1n CR: PAU (Bit 1)                               */
#define TIMER1n_CR_PAU_Msk                (0x2UL)                   /*!< TIMER1n CR: PAU (Bitfield-Mask: 0x01)                 */
#define TIMER1n_CR_CLR_Pos                (0UL)                     /*!< TIMER1n CR: CLR (Bit 0)                               */
#define TIMER1n_CR_CLR_Msk                (0x1UL)                   /*!< TIMER1n CR: CLR (Bitfield-Mask: 0x01)                 */
/* ==========================================================  ADR  ========================================================== */
#define TIMER1n_ADR_ADATA_Pos             (0UL)                     /*!< TIMER1n ADR: ADATA (Bit 0)                            */
#define TIMER1n_ADR_ADATA_Msk             (0xffffUL)                /*!< TIMER1n ADR: ADATA (Bitfield-Mask: 0xffff)            */
/* ==========================================================  BDR  ========================================================== */
#define TIMER1n_BDR_BDATA_Pos             (0UL)                     /*!< TIMER1n BDR: BDATA (Bit 0)                            */
#define TIMER1n_BDR_BDATA_Msk             (0xffffUL)                /*!< TIMER1n BDR: BDATA (Bitfield-Mask: 0xffff)            */
/* =========================================================  CAPDR  ========================================================= */
#define TIMER1n_CAPDR_CAPD_Pos            (0UL)                     /*!< TIMER1n CAPDR: CAPD (Bit 0)                           */
#define TIMER1n_CAPDR_CAPD_Msk            (0xffffUL)                /*!< TIMER1n CAPDR: CAPD (Bitfield-Mask: 0xffff)           */
/* =========================================================  PREDR  ========================================================= */
#define TIMER1n_PREDR_PRED_Pos            (0UL)                     /*!< TIMER1n PREDR: PRED (Bit 0)                           */
#define TIMER1n_PREDR_PRED_Msk            (0xfffUL)                 /*!< TIMER1n PREDR: PRED (Bitfield-Mask: 0xfff)            */
/* ==========================================================  CNT  ========================================================== */
#define TIMER1n_CNT_CNT_Pos               (0UL)                     /*!< TIMER1n CNT: CNT (Bit 0)                              */
#define TIMER1n_CNT_CNT_Msk               (0xffffUL)                /*!< TIMER1n CNT: CNT (Bitfield-Mask: 0xffff)              */


/* =========================================================================================================================== */
/* ================                                          TIMER2n                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define TIMER2n_CR_EN_Pos                 (15UL)                    /*!< TIMER2n CR: EN (Bit 15)                               */
#define TIMER2n_CR_EN_Msk                 (0x8000UL)                /*!< TIMER2n CR: EN (Bitfield-Mask: 0x01)                  */
#define TIMER2n_CR_CLK_Pos                (14UL)                    /*!< TIMER2n CR: CLK (Bit 14)                              */
#define TIMER2n_CR_CLK_Msk                (0x4000UL)                /*!< TIMER2n CR: CLK (Bitfield-Mask: 0x01)                 */
#define TIMER2n_CR_MS_Pos                 (12UL)                    /*!< TIMER2n CR: MS (Bit 12)                               */
#define TIMER2n_CR_MS_Msk                 (0x3000UL)                /*!< TIMER2n CR: MS (Bitfield-Mask: 0x03)                  */
#define TIMER2n_CR_ECE_Pos                (11UL)                    /*!< TIMER2n CR: ECE (Bit 11)                              */
#define TIMER2n_CR_ECE_Msk                (0x800UL)                 /*!< TIMER2n CR: ECE (Bitfield-Mask: 0x01)                 */
#define TIMER2n_CR_CAPSEL_Pos             (9UL)                     /*!< TIMER2n CR: CAPSEL (Bit 9)                            */
#define TIMER2n_CR_CAPSEL_Msk             (0x600UL)                 /*!< TIMER2n CR: CAPSEL (Bitfield-Mask: 0x03)              */
#define TIMER2n_CR_OPOL_Pos               (8UL)                     /*!< TIMER2n CR: OPOL (Bit 8)                              */
#define TIMER2n_CR_OPOL_Msk               (0x100UL)                 /*!< TIMER2n CR: OPOL (Bitfield-Mask: 0x01)                */
#define TIMER2n_CR_CPOL_Pos               (6UL)                     /*!< TIMER2n CR: CPOL (Bit 6)                              */
#define TIMER2n_CR_CPOL_Msk               (0xc0UL)                  /*!< TIMER2n CR: CPOL (Bitfield-Mask: 0x03)                */
#define TIMER2n_CR_MIEN_Pos               (5UL)                     /*!< TIMER2n CR: MIEN (Bit 5)                              */
#define TIMER2n_CR_MIEN_Msk               (0x20UL)                  /*!< TIMER2n CR: MIEN (Bitfield-Mask: 0x01)                */
#define TIMER2n_CR_CIEN_Pos               (4UL)                     /*!< TIMER2n CR: CIEN (Bit 4)                              */
#define TIMER2n_CR_CIEN_Msk               (0x10UL)                  /*!< TIMER2n CR: CIEN (Bitfield-Mask: 0x01)                */
#define TIMER2n_CR_MIFLAG_Pos             (3UL)                     /*!< TIMER2n CR: MIFLAG (Bit 3)                            */
#define TIMER2n_CR_MIFLAG_Msk             (0x8UL)                   /*!< TIMER2n CR: MIFLAG (Bitfield-Mask: 0x01)              */
#define TIMER2n_CR_CIFLAG_Pos             (2UL)                     /*!< TIMER2n CR: CIFLAG (Bit 2)                            */
#define TIMER2n_CR_CIFLAG_Msk             (0x4UL)                   /*!< TIMER2n CR: CIFLAG (Bitfield-Mask: 0x01)              */
#define TIMER2n_CR_PAU_Pos                (1UL)                     /*!< TIMER2n CR: PAU (Bit 1)                               */
#define TIMER2n_CR_PAU_Msk                (0x2UL)                   /*!< TIMER2n CR: PAU (Bitfield-Mask: 0x01)                 */
#define TIMER2n_CR_CLR_Pos                (0UL)                     /*!< TIMER2n CR: CLR (Bit 0)                               */
#define TIMER2n_CR_CLR_Msk                (0x1UL)                   /*!< TIMER2n CR: CLR (Bitfield-Mask: 0x01)                 */
/* ==========================================================  ADR  ========================================================== */
#define TIMER2n_ADR_ADATA_Pos             (0UL)                     /*!< TIMER2n ADR: ADATA (Bit 0)                            */
#define TIMER2n_ADR_ADATA_Msk             (0xffffffffUL)            /*!< TIMER2n ADR: ADATA (Bitfield-Mask: 0xffffffff)        */
/* ==========================================================  BDR  ========================================================== */
#define TIMER2n_BDR_BDATA_Pos             (0UL)                     /*!< TIMER2n BDR: BDATA (Bit 0)                            */
#define TIMER2n_BDR_BDATA_Msk             (0xffffffffUL)            /*!< TIMER2n BDR: BDATA (Bitfield-Mask: 0xffffffff)        */
/* =========================================================  CAPDR  ========================================================= */
#define TIMER2n_CAPDR_CAPD_Pos            (0UL)                     /*!< TIMER2n CAPDR: CAPD (Bit 0)                           */
#define TIMER2n_CAPDR_CAPD_Msk            (0xffffffffUL)            /*!< TIMER2n CAPDR: CAPD (Bitfield-Mask: 0xffffffff)       */
/* =========================================================  PREDR  ========================================================= */
#define TIMER2n_PREDR_PRED_Pos            (0UL)                     /*!< TIMER2n PREDR: PRED (Bit 0)                           */
#define TIMER2n_PREDR_PRED_Msk            (0xfffUL)                 /*!< TIMER2n PREDR: PRED (Bitfield-Mask: 0xfff)            */
/* ==========================================================  CNT  ========================================================== */
#define TIMER2n_CNT_CNT_Pos               (0UL)                     /*!< TIMER2n CNT: CNT (Bit 0)                              */
#define TIMER2n_CNT_CNT_Msk               (0xffffffffUL)            /*!< TIMER2n CNT: CNT (Bitfield-Mask: 0xffffffff)          */


/* =========================================================================================================================== */
/* ================                                          TIMER3n                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define TIMER3n_CR_EN_Pos                 (15UL)                    /*!< TIMER3n CR: EN (Bit 15)                               */
#define TIMER3n_CR_EN_Msk                 (0x8000UL)                /*!< TIMER3n CR: EN (Bitfield-Mask: 0x01)                  */
#define TIMER3n_CR_CLK_Pos                (14UL)                    /*!< TIMER3n CR: CLK (Bit 14)                              */
#define TIMER3n_CR_CLK_Msk                (0x4000UL)                /*!< TIMER3n CR: CLK (Bitfield-Mask: 0x01)                 */
#define TIMER3n_CR_MS_Pos                 (12UL)                    /*!< TIMER3n CR: MS (Bit 12)                               */
#define TIMER3n_CR_MS_Msk                 (0x3000UL)                /*!< TIMER3n CR: MS (Bitfield-Mask: 0x03)                  */
#define TIMER3n_CR_ECE_Pos                (11UL)                    /*!< TIMER3n CR: ECE (Bit 11)                              */
#define TIMER3n_CR_ECE_Msk                (0x800UL)                 /*!< TIMER3n CR: ECE (Bitfield-Mask: 0x01)                 */
#define TIMER3n_CR_FORCA_Pos              (10UL)                    /*!< TIMER3n CR: FORCA (Bit 10)                            */
#define TIMER3n_CR_FORCA_Msk              (0x400UL)                 /*!< TIMER3n CR: FORCA (Bitfield-Mask: 0x01)               */
#define TIMER3n_CR_DLYEN_Pos              (9UL)                     /*!< TIMER3n CR: DLYEN (Bit 9)                             */
#define TIMER3n_CR_DLYEN_Msk              (0x200UL)                 /*!< TIMER3n CR: DLYEN (Bitfield-Mask: 0x01)               */
#define TIMER3n_CR_DLYPOS_Pos             (8UL)                     /*!< TIMER3n CR: DLYPOS (Bit 8)                            */
#define TIMER3n_CR_DLYPOS_Msk             (0x100UL)                 /*!< TIMER3n CR: DLYPOS (Bitfield-Mask: 0x01)              */
#define TIMER3n_CR_CPOL_Pos               (6UL)                     /*!< TIMER3n CR: CPOL (Bit 6)                              */
#define TIMER3n_CR_CPOL_Msk               (0xc0UL)                  /*!< TIMER3n CR: CPOL (Bitfield-Mask: 0x03)                */
#define TIMER3n_CR_UPDT_Pos               (4UL)                     /*!< TIMER3n CR: UPDT (Bit 4)                              */
#define TIMER3n_CR_UPDT_Msk               (0x30UL)                  /*!< TIMER3n CR: UPDT (Bitfield-Mask: 0x03)                */
#define TIMER3n_CR_PMOC_Pos               (1UL)                     /*!< TIMER3n CR: PMOC (Bit 1)                              */
#define TIMER3n_CR_PMOC_Msk               (0xeUL)                   /*!< TIMER3n CR: PMOC (Bitfield-Mask: 0x07)                */
#define TIMER3n_CR_CLR_Pos                (0UL)                     /*!< TIMER3n CR: CLR (Bit 0)                               */
#define TIMER3n_CR_CLR_Msk                (0x1UL)                   /*!< TIMER3n CR: CLR (Bitfield-Mask: 0x01)                 */
/* ==========================================================  PDR  ========================================================== */
#define TIMER3n_PDR_PDATA_Pos             (0UL)                     /*!< TIMER3n PDR: PDATA (Bit 0)                            */
#define TIMER3n_PDR_PDATA_Msk             (0xffffUL)                /*!< TIMER3n PDR: PDATA (Bitfield-Mask: 0xffff)            */
/* ==========================================================  ADR  ========================================================== */
#define TIMER3n_ADR_ADATA_Pos             (0UL)                     /*!< TIMER3n ADR: ADATA (Bit 0)                            */
#define TIMER3n_ADR_ADATA_Msk             (0xffffUL)                /*!< TIMER3n ADR: ADATA (Bitfield-Mask: 0xffff)            */
/* ==========================================================  BDR  ========================================================== */
#define TIMER3n_BDR_BDATA_Pos             (0UL)                     /*!< TIMER3n BDR: BDATA (Bit 0)                            */
#define TIMER3n_BDR_BDATA_Msk             (0xffffUL)                /*!< TIMER3n BDR: BDATA (Bitfield-Mask: 0xffff)            */
/* ==========================================================  CDR  ========================================================== */
#define TIMER3n_CDR_CDATA_Pos             (0UL)                     /*!< TIMER3n CDR: CDATA (Bit 0)                            */
#define TIMER3n_CDR_CDATA_Msk             (0xffffUL)                /*!< TIMER3n CDR: CDATA (Bitfield-Mask: 0xffff)            */
/* =========================================================  CAPDR  ========================================================= */
#define TIMER3n_CAPDR_CAPD_Pos            (0UL)                     /*!< TIMER3n CAPDR: CAPD (Bit 0)                           */
#define TIMER3n_CAPDR_CAPD_Msk            (0xffffUL)                /*!< TIMER3n CAPDR: CAPD (Bitfield-Mask: 0xffff)           */
/* =========================================================  PREDR  ========================================================= */
#define TIMER3n_PREDR_PRED_Pos            (0UL)                     /*!< TIMER3n PREDR: PRED (Bit 0)                           */
#define TIMER3n_PREDR_PRED_Msk            (0xfffUL)                 /*!< TIMER3n PREDR: PRED (Bitfield-Mask: 0xfff)            */
/* ==========================================================  CNT  ========================================================== */
#define TIMER3n_CNT_CNT_Pos               (0UL)                     /*!< TIMER3n CNT: CNT (Bit 0)                              */
#define TIMER3n_CNT_CNT_Msk               (0xffffUL)                /*!< TIMER3n CNT: CNT (Bitfield-Mask: 0xffff)              */
/* =========================================================  OUTCR  ========================================================= */
#define TIMER3n_OUTCR_WTIDKY_Pos          (16UL)                    /*!< TIMER3n OUTCR: WTIDKY (Bit 16)                        */
#define TIMER3n_OUTCR_WTIDKY_Msk          (0xffff0000UL)            /*!< TIMER3n OUTCR: WTIDKY (Bitfield-Mask: 0xffff)         */
#define TIMER3n_OUTCR_POLB_Pos            (15UL)                    /*!< TIMER3n OUTCR: POLB (Bit 15)                          */
#define TIMER3n_OUTCR_POLB_Msk            (0x8000UL)                /*!< TIMER3n OUTCR: POLB (Bitfield-Mask: 0x01)             */
#define TIMER3n_OUTCR_POLA_Pos            (14UL)                    /*!< TIMER3n OUTCR: POLA (Bit 14)                          */
#define TIMER3n_OUTCR_POLA_Msk            (0x4000UL)                /*!< TIMER3n OUTCR: POLA (Bitfield-Mask: 0x01)             */
#define TIMER3n_OUTCR_PABOE_Pos           (13UL)                    /*!< TIMER3n OUTCR: PABOE (Bit 13)                         */
#define TIMER3n_OUTCR_PABOE_Msk           (0x2000UL)                /*!< TIMER3n OUTCR: PABOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_PBBOE_Pos           (12UL)                    /*!< TIMER3n OUTCR: PBBOE (Bit 12)                         */
#define TIMER3n_OUTCR_PBBOE_Msk           (0x1000UL)                /*!< TIMER3n OUTCR: PBBOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_PCBOE_Pos           (11UL)                    /*!< TIMER3n OUTCR: PCBOE (Bit 11)                         */
#define TIMER3n_OUTCR_PCBOE_Msk           (0x800UL)                 /*!< TIMER3n OUTCR: PCBOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_PAAOE_Pos           (10UL)                    /*!< TIMER3n OUTCR: PAAOE (Bit 10)                         */
#define TIMER3n_OUTCR_PAAOE_Msk           (0x400UL)                 /*!< TIMER3n OUTCR: PAAOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_PBAOE_Pos           (9UL)                     /*!< TIMER3n OUTCR: PBAOE (Bit 9)                          */
#define TIMER3n_OUTCR_PBAOE_Msk           (0x200UL)                 /*!< TIMER3n OUTCR: PBAOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_PCAOE_Pos           (8UL)                     /*!< TIMER3n OUTCR: PCAOE (Bit 8)                          */
#define TIMER3n_OUTCR_PCAOE_Msk           (0x100UL)                 /*!< TIMER3n OUTCR: PCAOE (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLAB_Pos           (6UL)                     /*!< TIMER3n OUTCR: LVLAB (Bit 6)                          */
#define TIMER3n_OUTCR_LVLAB_Msk           (0x40UL)                  /*!< TIMER3n OUTCR: LVLAB (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLBB_Pos           (5UL)                     /*!< TIMER3n OUTCR: LVLBB (Bit 5)                          */
#define TIMER3n_OUTCR_LVLBB_Msk           (0x20UL)                  /*!< TIMER3n OUTCR: LVLBB (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLCB_Pos           (4UL)                     /*!< TIMER3n OUTCR: LVLCB (Bit 4)                          */
#define TIMER3n_OUTCR_LVLCB_Msk           (0x10UL)                  /*!< TIMER3n OUTCR: LVLCB (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLAA_Pos           (2UL)                     /*!< TIMER3n OUTCR: LVLAA (Bit 2)                          */
#define TIMER3n_OUTCR_LVLAA_Msk           (0x4UL)                   /*!< TIMER3n OUTCR: LVLAA (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLBA_Pos           (1UL)                     /*!< TIMER3n OUTCR: LVLBA (Bit 1)                          */
#define TIMER3n_OUTCR_LVLBA_Msk           (0x2UL)                   /*!< TIMER3n OUTCR: LVLBA (Bitfield-Mask: 0x01)            */
#define TIMER3n_OUTCR_LVLCA_Pos           (0UL)                     /*!< TIMER3n OUTCR: LVLCA (Bit 0)                          */
#define TIMER3n_OUTCR_LVLCA_Msk           (0x1UL)                   /*!< TIMER3n OUTCR: LVLCA (Bitfield-Mask: 0x01)            */
/* ==========================================================  DLY  ========================================================== */
#define TIMER3n_DLY_DLY_Pos               (0UL)                     /*!< TIMER3n DLY: DLY (Bit 0)                              */
#define TIMER3n_DLY_DLY_Msk               (0x3ffUL)                 /*!< TIMER3n DLY: DLY (Bitfield-Mask: 0x3ff)               */
/* =========================================================  INTCR  ========================================================= */
#define TIMER3n_INTCR_HIZIEN_Pos          (6UL)                     /*!< TIMER3n INTCR: HIZIEN (Bit 6)                         */
#define TIMER3n_INTCR_HIZIEN_Msk          (0x40UL)                  /*!< TIMER3n INTCR: HIZIEN (Bitfield-Mask: 0x01)           */
#define TIMER3n_INTCR_CIEN_Pos            (5UL)                     /*!< TIMER3n INTCR: CIEN (Bit 5)                           */
#define TIMER3n_INTCR_CIEN_Msk            (0x20UL)                  /*!< TIMER3n INTCR: CIEN (Bitfield-Mask: 0x01)             */
#define TIMER3n_INTCR_BTIEN_Pos           (4UL)                     /*!< TIMER3n INTCR: BTIEN (Bit 4)                          */
#define TIMER3n_INTCR_BTIEN_Msk           (0x10UL)                  /*!< TIMER3n INTCR: BTIEN (Bitfield-Mask: 0x01)            */
#define TIMER3n_INTCR_PMIEN_Pos           (3UL)                     /*!< TIMER3n INTCR: PMIEN (Bit 3)                          */
#define TIMER3n_INTCR_PMIEN_Msk           (0x8UL)                   /*!< TIMER3n INTCR: PMIEN (Bitfield-Mask: 0x01)            */
#define TIMER3n_INTCR_AMIEN_Pos           (2UL)                     /*!< TIMER3n INTCR: AMIEN (Bit 2)                          */
#define TIMER3n_INTCR_AMIEN_Msk           (0x4UL)                   /*!< TIMER3n INTCR: AMIEN (Bitfield-Mask: 0x01)            */
#define TIMER3n_INTCR_BMIEN_Pos           (1UL)                     /*!< TIMER3n INTCR: BMIEN (Bit 1)                          */
#define TIMER3n_INTCR_BMIEN_Msk           (0x2UL)                   /*!< TIMER3n INTCR: BMIEN (Bitfield-Mask: 0x01)            */
#define TIMER3n_INTCR_CMIEN_Pos           (0UL)                     /*!< TIMER3n INTCR: CMIEN (Bit 0)                          */
#define TIMER3n_INTCR_CMIEN_Msk           (0x1UL)                   /*!< TIMER3n INTCR: CMIEN (Bitfield-Mask: 0x01)            */
/* ========================================================  INTFLAG  ======================================================== */
#define TIMER3n_INTFLAG_HIZIFLAG_Pos      (6UL)                     /*!< TIMER3n INTFLAG: HIZIFLAG (Bit 6)                     */
#define TIMER3n_INTFLAG_HIZIFLAG_Msk      (0x40UL)                  /*!< TIMER3n INTFLAG: HIZIFLAG (Bitfield-Mask: 0x01)       */
#define TIMER3n_INTFLAG_CIFLAG_Pos        (5UL)                     /*!< TIMER3n INTFLAG: CIFLAG (Bit 5)                       */
#define TIMER3n_INTFLAG_CIFLAG_Msk        (0x20UL)                  /*!< TIMER3n INTFLAG: CIFLAG (Bitfield-Mask: 0x01)         */
#define TIMER3n_INTFLAG_BTIFLAG_Pos       (4UL)                     /*!< TIMER3n INTFLAG: BTIFLAG (Bit 4)                      */
#define TIMER3n_INTFLAG_BTIFLAG_Msk       (0x10UL)                  /*!< TIMER3n INTFLAG: BTIFLAG (Bitfield-Mask: 0x01)        */
#define TIMER3n_INTFLAG_PMIFLAG_Pos       (3UL)                     /*!< TIMER3n INTFLAG: PMIFLAG (Bit 3)                      */
#define TIMER3n_INTFLAG_PMIFLAG_Msk       (0x8UL)                   /*!< TIMER3n INTFLAG: PMIFLAG (Bitfield-Mask: 0x01)        */
#define TIMER3n_INTFLAG_AMIFLAG_Pos       (2UL)                     /*!< TIMER3n INTFLAG: AMIFLAG (Bit 2)                      */
#define TIMER3n_INTFLAG_AMIFLAG_Msk       (0x4UL)                   /*!< TIMER3n INTFLAG: AMIFLAG (Bitfield-Mask: 0x01)        */
#define TIMER3n_INTFLAG_BMIFLAG_Pos       (1UL)                     /*!< TIMER3n INTFLAG: BMIFLAG (Bit 1)                      */
#define TIMER3n_INTFLAG_BMIFLAG_Msk       (0x2UL)                   /*!< TIMER3n INTFLAG: BMIFLAG (Bitfield-Mask: 0x01)        */
#define TIMER3n_INTFLAG_CMIFLAG_Pos       (0UL)                     /*!< TIMER3n INTFLAG: CMIFLAG (Bit 0)                      */
#define TIMER3n_INTFLAG_CMIFLAG_Msk       (0x1UL)                   /*!< TIMER3n INTFLAG: CMIFLAG (Bitfield-Mask: 0x01)        */
/* =========================================================  HIZCR  ========================================================= */
#define TIMER3n_HIZCR_HIZEN_Pos           (7UL)                     /*!< TIMER3n HIZCR: HIZEN (Bit 7)                          */
#define TIMER3n_HIZCR_HIZEN_Msk           (0x80UL)                  /*!< TIMER3n HIZCR: HIZEN (Bitfield-Mask: 0x01)            */
#define TIMER3n_HIZCR_HIZSW_Pos           (4UL)                     /*!< TIMER3n HIZCR: HIZSW (Bit 4)                          */
#define TIMER3n_HIZCR_HIZSW_Msk           (0x10UL)                  /*!< TIMER3n HIZCR: HIZSW (Bitfield-Mask: 0x01)            */
#define TIMER3n_HIZCR_HEDGE_Pos           (2UL)                     /*!< TIMER3n HIZCR: HEDGE (Bit 2)                          */
#define TIMER3n_HIZCR_HEDGE_Msk           (0x4UL)                   /*!< TIMER3n HIZCR: HEDGE (Bitfield-Mask: 0x01)            */
#define TIMER3n_HIZCR_HIZSTA_Pos          (1UL)                     /*!< TIMER3n HIZCR: HIZSTA (Bit 1)                         */
#define TIMER3n_HIZCR_HIZSTA_Msk          (0x2UL)                   /*!< TIMER3n HIZCR: HIZSTA (Bitfield-Mask: 0x01)           */
#define TIMER3n_HIZCR_HIZCLR_Pos          (0UL)                     /*!< TIMER3n HIZCR: HIZCLR (Bit 0)                         */
#define TIMER3n_HIZCR_HIZCLR_Msk          (0x1UL)                   /*!< TIMER3n HIZCR: HIZCLR (Bitfield-Mask: 0x01)           */
/* =========================================================  ADTCR  ========================================================= */
#define TIMER3n_ADTCR_BTTG_Pos            (4UL)                     /*!< TIMER3n ADTCR: BTTG (Bit 4)                           */
#define TIMER3n_ADTCR_BTTG_Msk            (0x10UL)                  /*!< TIMER3n ADTCR: BTTG (Bitfield-Mask: 0x01)             */
#define TIMER3n_ADTCR_PMTG_Pos            (3UL)                     /*!< TIMER3n ADTCR: PMTG (Bit 3)                           */
#define TIMER3n_ADTCR_PMTG_Msk            (0x8UL)                   /*!< TIMER3n ADTCR: PMTG (Bitfield-Mask: 0x01)             */
#define TIMER3n_ADTCR_AMTG_Pos            (2UL)                     /*!< TIMER3n ADTCR: AMTG (Bit 2)                           */
#define TIMER3n_ADTCR_AMTG_Msk            (0x4UL)                   /*!< TIMER3n ADTCR: AMTG (Bitfield-Mask: 0x01)             */
#define TIMER3n_ADTCR_BMTG_Pos            (1UL)                     /*!< TIMER3n ADTCR: BMTG (Bit 1)                           */
#define TIMER3n_ADTCR_BMTG_Msk            (0x2UL)                   /*!< TIMER3n ADTCR: BMTG (Bitfield-Mask: 0x01)             */
#define TIMER3n_ADTCR_CMTG_Pos            (0UL)                     /*!< TIMER3n ADTCR: CMTG (Bit 0)                           */
#define TIMER3n_ADTCR_CMTG_Msk            (0x1UL)                   /*!< TIMER3n ADTCR: CMTG (Bitfield-Mask: 0x01)             */
/* =========================================================  ADTDR  ========================================================= */
#define TIMER3n_ADTDR_ADTDATA_Pos         (0UL)                     /*!< TIMER3n ADTDR: ADTDATA (Bit 0)                        */
#define TIMER3n_ADTDR_ADTDATA_Msk         (0x3fffUL)                /*!< TIMER3n ADTDR: ADTDATA (Bitfield-Mask: 0x3fff)        */


/* =========================================================================================================================== */
/* ================                                           USART                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR1  ========================================================== */
#define USART_CR1_MS_Pos                  (14UL)                    /*!< USART CR1: MS (Bit 14)                                */
#define USART_CR1_MS_Msk                  (0xc000UL)                /*!< USART CR1: MS (Bitfield-Mask: 0x03)                   */
#define USART_CR1_PG_Pos                  (12UL)                    /*!< USART CR1: PG (Bit 12)                                */
#define USART_CR1_PG_Msk                  (0x3000UL)                /*!< USART CR1: PG (Bitfield-Mask: 0x03)                   */
#define USART_CR1_DLEN_Pos                (9UL)                     /*!< USART CR1: DLEN (Bit 9)                               */
#define USART_CR1_DLEN_Msk                (0xe00UL)                 /*!< USART CR1: DLEN (Bitfield-Mask: 0x07)                 */
#define USART_CR1_ORD_Pos                 (8UL)                     /*!< USART CR1: ORD (Bit 8)                                */
#define USART_CR1_ORD_Msk                 (0x100UL)                 /*!< USART CR1: ORD (Bitfield-Mask: 0x01)                  */
#define USART_CR1_CPOL_Pos                (7UL)                     /*!< USART CR1: CPOL (Bit 7)                               */
#define USART_CR1_CPOL_Msk                (0x80UL)                  /*!< USART CR1: CPOL (Bitfield-Mask: 0x01)                 */
#define USART_CR1_CPHA_Pos                (6UL)                     /*!< USART CR1: CPHA (Bit 6)                               */
#define USART_CR1_CPHA_Msk                (0x40UL)                  /*!< USART CR1: CPHA (Bitfield-Mask: 0x01)                 */
#define USART_CR1_DRIE_Pos                (5UL)                     /*!< USART CR1: DRIE (Bit 5)                               */
#define USART_CR1_DRIE_Msk                (0x20UL)                  /*!< USART CR1: DRIE (Bitfield-Mask: 0x01)                 */
#define USART_CR1_TXCIE_Pos               (4UL)                     /*!< USART CR1: TXCIE (Bit 4)                              */
#define USART_CR1_TXCIE_Msk               (0x10UL)                  /*!< USART CR1: TXCIE (Bitfield-Mask: 0x01)                */
#define USART_CR1_RXCIE_Pos               (3UL)                     /*!< USART CR1: RXCIE (Bit 3)                              */
#define USART_CR1_RXCIE_Msk               (0x8UL)                   /*!< USART CR1: RXCIE (Bitfield-Mask: 0x01)                */
#define USART_CR1_TXE_Pos                 (1UL)                     /*!< USART CR1: TXE (Bit 1)                                */
#define USART_CR1_TXE_Msk                 (0x2UL)                   /*!< USART CR1: TXE (Bitfield-Mask: 0x01)                  */
#define USART_CR1_RXE_Pos                 (0UL)                     /*!< USART CR1: RXE (Bit 0)                                */
#define USART_CR1_RXE_Msk                 (0x1UL)                   /*!< USART CR1: RXE (Bitfield-Mask: 0x01)                  */
/* ==========================================================  CR2  ========================================================== */
#define USART_CR2_DMATXIE_Pos             (14UL)                    /*!< USART CR2: DMATXIE (Bit 14)                           */
#define USART_CR2_DMATXIE_Msk             (0x4000UL)                /*!< USART CR2: DMATXIE (Bitfield-Mask: 0x01)              */
#define USART_CR2_DMARXIE_Pos             (13UL)                    /*!< USART CR2: DMARXIE (Bit 13)                           */
#define USART_CR2_DMARXIE_Msk             (0x2000UL)                /*!< USART CR2: DMARXIE (Bitfield-Mask: 0x01)              */
#define USART_CR2_RTOIE_Pos               (12UL)                    /*!< USART CR2: RTOIE (Bit 12)                             */
#define USART_CR2_RTOIE_Msk               (0x1000UL)                /*!< USART CR2: RTOIE (Bitfield-Mask: 0x01)                */
#define USART_CR2_RTOEN_Pos               (11UL)                    /*!< USART CR2: RTOEN (Bit 11)                             */
#define USART_CR2_RTOEN_Msk               (0x800UL)                 /*!< USART CR2: RTOEN (Bitfield-Mask: 0x01)                */
#define USART_CR2_BFREN_Pos               (10UL)                    /*!< USART CR2: BFREN (Bit 10)                             */
#define USART_CR2_BFREN_Msk               (0x400UL)                 /*!< USART CR2: BFREN (Bitfield-Mask: 0x01)                */
#define USART_CR2_EN_Pos                  (9UL)                     /*!< USART CR2: EN (Bit 9)                                 */
#define USART_CR2_EN_Msk                  (0x200UL)                 /*!< USART CR2: EN (Bitfield-Mask: 0x01)                   */
#define USART_CR2_DBLS_Pos                (8UL)                     /*!< USART CR2: DBLS (Bit 8)                               */
#define USART_CR2_DBLS_Msk                (0x100UL)                 /*!< USART CR2: DBLS (Bitfield-Mask: 0x01)                 */
#define USART_CR2_MASTER_Pos              (7UL)                     /*!< USART CR2: MASTER (Bit 7)                             */
#define USART_CR2_MASTER_Msk              (0x80UL)                  /*!< USART CR2: MASTER (Bitfield-Mask: 0x01)               */
#define USART_CR2_LOOPS_Pos               (6UL)                     /*!< USART CR2: LOOPS (Bit 6)                              */
#define USART_CR2_LOOPS_Msk               (0x40UL)                  /*!< USART CR2: LOOPS (Bitfield-Mask: 0x01)                */
#define USART_CR2_DISSCK_Pos              (5UL)                     /*!< USART CR2: DISSCK (Bit 5)                             */
#define USART_CR2_DISSCK_Msk              (0x20UL)                  /*!< USART CR2: DISSCK (Bitfield-Mask: 0x01)               */
#define USART_CR2_SSEN_Pos                (4UL)                     /*!< USART CR2: SSEN (Bit 4)                               */
#define USART_CR2_SSEN_Msk                (0x10UL)                  /*!< USART CR2: SSEN (Bitfield-Mask: 0x01)                 */
#define USART_CR2_FXCH_Pos                (3UL)                     /*!< USART CR2: FXCH (Bit 3)                               */
#define USART_CR2_FXCH_Msk                (0x8UL)                   /*!< USART CR2: FXCH (Bitfield-Mask: 0x01)                 */
#define USART_CR2_SB_Pos                  (2UL)                     /*!< USART CR2: SB (Bit 2)                                 */
#define USART_CR2_SB_Msk                  (0x4UL)                   /*!< USART CR2: SB (Bitfield-Mask: 0x01)                   */
#define USART_CR2_TX8_Pos                 (1UL)                     /*!< USART CR2: TX8 (Bit 1)                                */
#define USART_CR2_TX8_Msk                 (0x2UL)                   /*!< USART CR2: TX8 (Bitfield-Mask: 0x01)                  */
#define USART_CR2_RX8_Pos                 (0UL)                     /*!< USART CR2: RX8 (Bit 0)                                */
#define USART_CR2_RX8_Msk                 (0x1UL)                   /*!< USART CR2: RX8 (Bitfield-Mask: 0x01)                  */
/* ==========================================================  ST  =========================================================== */
#define USART_ST_DMATXF_Pos               (9UL)                     /*!< USART ST: DMATXF (Bit 9)                              */
#define USART_ST_DMATXF_Msk               (0x200UL)                 /*!< USART ST: DMATXF (Bitfield-Mask: 0x01)                */
#define USART_ST_DMARXF_Pos               (8UL)                     /*!< USART ST: DMARXF (Bit 8)                              */
#define USART_ST_DMARXF_Msk               (0x100UL)                 /*!< USART ST: DMARXF (Bitfield-Mask: 0x01)                */
#define USART_ST_DRE_Pos                  (7UL)                     /*!< USART ST: DRE (Bit 7)                                 */
#define USART_ST_DRE_Msk                  (0x80UL)                  /*!< USART ST: DRE (Bitfield-Mask: 0x01)                   */
#define USART_ST_TXC_Pos                  (6UL)                     /*!< USART ST: TXC (Bit 6)                                 */
#define USART_ST_TXC_Msk                  (0x40UL)                  /*!< USART ST: TXC (Bitfield-Mask: 0x01)                   */
#define USART_ST_RXC_Pos                  (5UL)                     /*!< USART ST: RXC (Bit 5)                                 */
#define USART_ST_RXC_Msk                  (0x20UL)                  /*!< USART ST: RXC (Bitfield-Mask: 0x01)                   */
#define USART_ST_RTOF_Pos                 (3UL)                     /*!< USART ST: RTOF (Bit 3)                                */
#define USART_ST_RTOF_Msk                 (0x8UL)                   /*!< USART ST: RTOF (Bitfield-Mask: 0x01)                  */
#define USART_ST_DOR_Pos                  (2UL)                     /*!< USART ST: DOR (Bit 2)                                 */
#define USART_ST_DOR_Msk                  (0x4UL)                   /*!< USART ST: DOR (Bitfield-Mask: 0x01)                   */
#define USART_ST_FE_Pos                   (1UL)                     /*!< USART ST: FE (Bit 1)                                  */
#define USART_ST_FE_Msk                   (0x2UL)                   /*!< USART ST: FE (Bitfield-Mask: 0x01)                    */
#define USART_ST_PE_Pos                   (0UL)                     /*!< USART ST: PE (Bit 0)                                  */
#define USART_ST_PE_Msk                   (0x1UL)                   /*!< USART ST: PE (Bitfield-Mask: 0x01)                    */
/* ==========================================================  BDR  ========================================================== */
#define USART_BDR_BDATA_Pos               (0UL)                     /*!< USART BDR: BDATA (Bit 0)                              */
#define USART_BDR_BDATA_Msk               (0xfffUL)                 /*!< USART BDR: BDATA (Bitfield-Mask: 0xfff)               */
/* ==========================================================  DR  =========================================================== */
#define USART_DR_DATA_Pos                 (0UL)                     /*!< USART DR: DATA (Bit 0)                                */
#define USART_DR_DATA_Msk                 (0xffUL)                  /*!< USART DR: DATA (Bitfield-Mask: 0xff)                  */
/* ==========================================================  BFR  ========================================================== */
#define USART_BFR_BFC_Pos                 (0UL)                     /*!< USART BFR: BFC (Bit 0)                                */
#define USART_BFR_BFC_Msk                 (0xffUL)                  /*!< USART BFR: BFC (Bitfield-Mask: 0xff)                  */
/* ==========================================================  RTO  ========================================================== */
#define USART_RTO_RTO_Pos                 (0UL)                     /*!< USART RTO: RTO (Bit 0)                                */
#define USART_RTO_RTO_Msk                 (0xffffffUL)              /*!< USART RTO: RTO (Bitfield-Mask: 0xffffff)              */


/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  RBR  ========================================================== */
#define UART_RBR_RBR_Pos                  (0UL)                     /*!< UART RBR: RBR (Bit 0)                                 */
#define UART_RBR_RBR_Msk                  (0xffUL)                  /*!< UART RBR: RBR (Bitfield-Mask: 0xff)                   */
/* ==========================================================  THR  ========================================================== */
#define UART_THR_THR_Pos                  (0UL)                     /*!< UART THR: THR (Bit 0)                                 */
#define UART_THR_THR_Msk                  (0xffUL)                  /*!< UART THR: THR (Bitfield-Mask: 0xff)                   */
/* ==========================================================  IER  ========================================================== */
#define UART_IER_DTXIEN_Pos               (5UL)                     /*!< UART IER: DTXIEN (Bit 5)                              */
#define UART_IER_DTXIEN_Msk               (0x20UL)                  /*!< UART IER: DTXIEN (Bitfield-Mask: 0x01)                */
#define UART_IER_DRXIEN_Pos               (4UL)                     /*!< UART IER: DRXIEN (Bit 4)                              */
#define UART_IER_DRXIEN_Msk               (0x10UL)                  /*!< UART IER: DRXIEN (Bitfield-Mask: 0x01)                */
#define UART_IER_TXEIE_Pos                (3UL)                     /*!< UART IER: TXEIE (Bit 3)                               */
#define UART_IER_TXEIE_Msk                (0x8UL)                   /*!< UART IER: TXEIE (Bitfield-Mask: 0x01)                 */
#define UART_IER_RLSIE_Pos                (2UL)                     /*!< UART IER: RLSIE (Bit 2)                               */
#define UART_IER_RLSIE_Msk                (0x4UL)                   /*!< UART IER: RLSIE (Bitfield-Mask: 0x01)                 */
#define UART_IER_THREIE_Pos               (1UL)                     /*!< UART IER: THREIE (Bit 1)                              */
#define UART_IER_THREIE_Msk               (0x2UL)                   /*!< UART IER: THREIE (Bitfield-Mask: 0x01)                */
#define UART_IER_DRIE_Pos                 (0UL)                     /*!< UART IER: DRIE (Bit 0)                                */
#define UART_IER_DRIE_Msk                 (0x1UL)                   /*!< UART IER: DRIE (Bitfield-Mask: 0x01)                  */
/* ==========================================================  IIR  ========================================================== */
#define UART_IIR_TXE_Pos                  (4UL)                     /*!< UART IIR: TXE (Bit 4)                                 */
#define UART_IIR_TXE_Msk                  (0x10UL)                  /*!< UART IIR: TXE (Bitfield-Mask: 0x01)                   */
#define UART_IIR_DMAF_Pos                 (3UL)                     /*!< UART IIR: DMAF (Bit 3)                                */
#define UART_IIR_DMAF_Msk                 (0x8UL)                   /*!< UART IIR: DMAF (Bitfield-Mask: 0x01)                  */
#define UART_IIR_IID_Pos                  (1UL)                     /*!< UART IIR: IID (Bit 1)                                 */
#define UART_IIR_IID_Msk                  (0x6UL)                   /*!< UART IIR: IID (Bitfield-Mask: 0x03)                   */
#define UART_IIR_IPEN_Pos                 (0UL)                     /*!< UART IIR: IPEN (Bit 0)                                */
#define UART_IIR_IPEN_Msk                 (0x1UL)                   /*!< UART IIR: IPEN (Bitfield-Mask: 0x01)                  */
/* ==========================================================  LCR  ========================================================== */
#define UART_LCR_BREAK_Pos                (6UL)                     /*!< UART LCR: BREAK (Bit 6)                               */
#define UART_LCR_BREAK_Msk                (0x40UL)                  /*!< UART LCR: BREAK (Bitfield-Mask: 0x01)                 */
#define UART_LCR_STICKP_Pos               (5UL)                     /*!< UART LCR: STICKP (Bit 5)                              */
#define UART_LCR_STICKP_Msk               (0x20UL)                  /*!< UART LCR: STICKP (Bitfield-Mask: 0x01)                */
#define UART_LCR_PARITY_Pos               (4UL)                     /*!< UART LCR: PARITY (Bit 4)                              */
#define UART_LCR_PARITY_Msk               (0x10UL)                  /*!< UART LCR: PARITY (Bitfield-Mask: 0x01)                */
#define UART_LCR_PEN_Pos                  (3UL)                     /*!< UART LCR: PEN (Bit 3)                                 */
#define UART_LCR_PEN_Msk                  (0x8UL)                   /*!< UART LCR: PEN (Bitfield-Mask: 0x01)                   */
#define UART_LCR_STOPBIT_Pos              (2UL)                     /*!< UART LCR: STOPBIT (Bit 2)                             */
#define UART_LCR_STOPBIT_Msk              (0x4UL)                   /*!< UART LCR: STOPBIT (Bitfield-Mask: 0x01)               */
#define UART_LCR_DLEN_Pos                 (0UL)                     /*!< UART LCR: DLEN (Bit 0)                                */
#define UART_LCR_DLEN_Msk                 (0x3UL)                   /*!< UART LCR: DLEN (Bitfield-Mask: 0x03)                  */
/* ==========================================================  DCR  ========================================================== */
#define UART_DCR_LBON_Pos                 (4UL)                     /*!< UART DCR: LBON (Bit 4)                                */
#define UART_DCR_LBON_Msk                 (0x10UL)                  /*!< UART DCR: LBON (Bitfield-Mask: 0x01)                  */
#define UART_DCR_RXINV_Pos                (3UL)                     /*!< UART DCR: RXINV (Bit 3)                               */
#define UART_DCR_RXINV_Msk                (0x8UL)                   /*!< UART DCR: RXINV (Bitfield-Mask: 0x01)                 */
#define UART_DCR_TXINV_Pos                (2UL)                     /*!< UART DCR: TXINV (Bit 2)                               */
#define UART_DCR_TXINV_Msk                (0x4UL)                   /*!< UART DCR: TXINV (Bitfield-Mask: 0x01)                 */
/* ==========================================================  LSR  ========================================================== */
#define UART_LSR_TEMT_Pos                 (6UL)                     /*!< UART LSR: TEMT (Bit 6)                                */
#define UART_LSR_TEMT_Msk                 (0x40UL)                  /*!< UART LSR: TEMT (Bitfield-Mask: 0x01)                  */
#define UART_LSR_THRE_Pos                 (5UL)                     /*!< UART LSR: THRE (Bit 5)                                */
#define UART_LSR_THRE_Msk                 (0x20UL)                  /*!< UART LSR: THRE (Bitfield-Mask: 0x01)                  */
#define UART_LSR_BI_Pos                   (4UL)                     /*!< UART LSR: BI (Bit 4)                                  */
#define UART_LSR_BI_Msk                   (0x10UL)                  /*!< UART LSR: BI (Bitfield-Mask: 0x01)                    */
#define UART_LSR_FE_Pos                   (3UL)                     /*!< UART LSR: FE (Bit 3)                                  */
#define UART_LSR_FE_Msk                   (0x8UL)                   /*!< UART LSR: FE (Bitfield-Mask: 0x01)                    */
#define UART_LSR_PE_Pos                   (2UL)                     /*!< UART LSR: PE (Bit 2)                                  */
#define UART_LSR_PE_Msk                   (0x4UL)                   /*!< UART LSR: PE (Bitfield-Mask: 0x01)                    */
#define UART_LSR_OE_Pos                   (1UL)                     /*!< UART LSR: OE (Bit 1)                                  */
#define UART_LSR_OE_Msk                   (0x2UL)                   /*!< UART LSR: OE (Bitfield-Mask: 0x01)                    */
#define UART_LSR_DR_Pos                   (0UL)                     /*!< UART LSR: DR (Bit 0)                                  */
#define UART_LSR_DR_Msk                   (0x1UL)                   /*!< UART LSR: DR (Bitfield-Mask: 0x01)                    */
/* ==========================================================  BDR  ========================================================== */
#define UART_BDR_BDR_Pos                  (0UL)                     /*!< UART BDR: BDR (Bit 0)                                 */
#define UART_BDR_BDR_Msk                  (0xffffUL)                /*!< UART BDR: BDR (Bitfield-Mask: 0xffff)                 */
/* ==========================================================  BFR  ========================================================== */
#define UART_BFR_BFR_Pos                  (0UL)                     /*!< UART BFR: BFR (Bit 0)                                 */
#define UART_BFR_BFR_Msk                  (0xffUL)                  /*!< UART BFR: BFR (Bitfield-Mask: 0xff)                   */
/* =========================================================  IDTR  ========================================================== */
#define UART_IDTR_SMS_Pos                 (7UL)                     /*!< UART IDTR: SMS (Bit 7)                                */
#define UART_IDTR_SMS_Msk                 (0x80UL)                  /*!< UART IDTR: SMS (Bitfield-Mask: 0x01)                  */
#define UART_IDTR_DMS_Pos                 (6UL)                     /*!< UART IDTR: DMS (Bit 6)                                */
#define UART_IDTR_DMS_Msk                 (0x40UL)                  /*!< UART IDTR: DMS (Bitfield-Mask: 0x01)                  */
#define UART_IDTR_WAITVAL_Pos             (0UL)                     /*!< UART IDTR: WAITVAL (Bit 0)                            */
#define UART_IDTR_WAITVAL_Msk             (0x7UL)                   /*!< UART IDTR: WAITVAL (Bitfield-Mask: 0x07)              */


/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  TDR  ========================================================== */
#define SPI_TDR_TDR_Pos                   (0UL)                     /*!< SPI TDR: TDR (Bit 0)                                  */
#define SPI_TDR_TDR_Msk                   (0x1ffffUL)               /*!< SPI TDR: TDR (Bitfield-Mask: 0x1ffff)                 */
/* ==========================================================  RDR  ========================================================== */
#define SPI_RDR_RDR_Pos                   (0UL)                     /*!< SPI RDR: RDR (Bit 0)                                  */
#define SPI_RDR_RDR_Msk                   (0x1ffffUL)               /*!< SPI RDR: RDR (Bitfield-Mask: 0x1ffff)                 */
/* ==========================================================  CR  =========================================================== */
#define SPI_CR_TXBC_Pos                   (20UL)                    /*!< SPI CR: TXBC (Bit 20)                                 */
#define SPI_CR_TXBC_Msk                   (0x100000UL)              /*!< SPI CR: TXBC (Bitfield-Mask: 0x01)                    */
#define SPI_CR_RXBC_Pos                   (19UL)                    /*!< SPI CR: RXBC (Bit 19)                                 */
#define SPI_CR_RXBC_Msk                   (0x80000UL)               /*!< SPI CR: RXBC (Bitfield-Mask: 0x01)                    */
#define SPI_CR_TXDIE_Pos                  (18UL)                    /*!< SPI CR: TXDIE (Bit 18)                                */
#define SPI_CR_TXDIE_Msk                  (0x40000UL)               /*!< SPI CR: TXDIE (Bitfield-Mask: 0x01)                   */
#define SPI_CR_RXDIE_Pos                  (17UL)                    /*!< SPI CR: RXDIE (Bit 17)                                */
#define SPI_CR_RXDIE_Msk                  (0x20000UL)               /*!< SPI CR: RXDIE (Bitfield-Mask: 0x01)                   */
#define SPI_CR_SSCIE_Pos                  (16UL)                    /*!< SPI CR: SSCIE (Bit 16)                                */
#define SPI_CR_SSCIE_Msk                  (0x10000UL)               /*!< SPI CR: SSCIE (Bitfield-Mask: 0x01)                   */
#define SPI_CR_TXIE_Pos                   (15UL)                    /*!< SPI CR: TXIE (Bit 15)                                 */
#define SPI_CR_TXIE_Msk                   (0x8000UL)                /*!< SPI CR: TXIE (Bitfield-Mask: 0x01)                    */
#define SPI_CR_RXIE_Pos                   (14UL)                    /*!< SPI CR: RXIE (Bit 14)                                 */
#define SPI_CR_RXIE_Msk                   (0x4000UL)                /*!< SPI CR: RXIE (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SSMOD_Pos                  (13UL)                    /*!< SPI CR: SSMOD (Bit 13)                                */
#define SPI_CR_SSMOD_Msk                  (0x2000UL)                /*!< SPI CR: SSMOD (Bitfield-Mask: 0x01)                   */
#define SPI_CR_SSOUT_Pos                  (12UL)                    /*!< SPI CR: SSOUT (Bit 12)                                */
#define SPI_CR_SSOUT_Msk                  (0x1000UL)                /*!< SPI CR: SSOUT (Bitfield-Mask: 0x01)                   */
#define SPI_CR_LBE_Pos                    (11UL)                    /*!< SPI CR: LBE (Bit 11)                                  */
#define SPI_CR_LBE_Msk                    (0x800UL)                 /*!< SPI CR: LBE (Bitfield-Mask: 0x01)                     */
#define SPI_CR_SSMASK_Pos                 (10UL)                    /*!< SPI CR: SSMASK (Bit 10)                               */
#define SPI_CR_SSMASK_Msk                 (0x400UL)                 /*!< SPI CR: SSMASK (Bitfield-Mask: 0x01)                  */
#define SPI_CR_SSMO_Pos                   (9UL)                     /*!< SPI CR: SSMO (Bit 9)                                  */
#define SPI_CR_SSMO_Msk                   (0x200UL)                 /*!< SPI CR: SSMO (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SSPOL_Pos                  (8UL)                     /*!< SPI CR: SSPOL (Bit 8)                                 */
#define SPI_CR_SSPOL_Msk                  (0x100UL)                 /*!< SPI CR: SSPOL (Bitfield-Mask: 0x01)                   */
#define SPI_CR_MS_Pos                     (5UL)                     /*!< SPI CR: MS (Bit 5)                                    */
#define SPI_CR_MS_Msk                     (0x20UL)                  /*!< SPI CR: MS (Bitfield-Mask: 0x01)                      */
#define SPI_CR_MSBF_Pos                   (4UL)                     /*!< SPI CR: MSBF (Bit 4)                                  */
#define SPI_CR_MSBF_Msk                   (0x10UL)                  /*!< SPI CR: MSBF (Bitfield-Mask: 0x01)                    */
#define SPI_CR_CPHA_Pos                   (3UL)                     /*!< SPI CR: CPHA (Bit 3)                                  */
#define SPI_CR_CPHA_Msk                   (0x8UL)                   /*!< SPI CR: CPHA (Bitfield-Mask: 0x01)                    */
#define SPI_CR_CPOL_Pos                   (2UL)                     /*!< SPI CR: CPOL (Bit 2)                                  */
#define SPI_CR_CPOL_Msk                   (0x4UL)                   /*!< SPI CR: CPOL (Bitfield-Mask: 0x01)                    */
#define SPI_CR_BITSZ_Pos                  (0UL)                     /*!< SPI CR: BITSZ (Bit 0)                                 */
#define SPI_CR_BITSZ_Msk                  (0x3UL)                   /*!< SPI CR: BITSZ (Bitfield-Mask: 0x03)                   */
/* ==========================================================  SR  =========================================================== */
#define SPI_SR_TXDMAF_Pos                 (9UL)                     /*!< SPI SR: TXDMAF (Bit 9)                                */
#define SPI_SR_TXDMAF_Msk                 (0x200UL)                 /*!< SPI SR: TXDMAF (Bitfield-Mask: 0x01)                  */
#define SPI_SR_RXDMAF_Pos                 (8UL)                     /*!< SPI SR: RXDMAF (Bit 8)                                */
#define SPI_SR_RXDMAF_Msk                 (0x100UL)                 /*!< SPI SR: RXDMAF (Bitfield-Mask: 0x01)                  */
#define SPI_SR_SBUSY_Pos                  (7UL)                     /*!< SPI SR: SBUSY (Bit 7)                                 */
#define SPI_SR_SBUSY_Msk                  (0x80UL)                  /*!< SPI SR: SBUSY (Bitfield-Mask: 0x01)                   */
#define SPI_SR_SSDET_Pos                  (6UL)                     /*!< SPI SR: SSDET (Bit 6)                                 */
#define SPI_SR_SSDET_Msk                  (0x40UL)                  /*!< SPI SR: SSDET (Bitfield-Mask: 0x01)                   */
#define SPI_SR_SSON_Pos                   (5UL)                     /*!< SPI SR: SSON (Bit 5)                                  */
#define SPI_SR_SSON_Msk                   (0x20UL)                  /*!< SPI SR: SSON (Bitfield-Mask: 0x01)                    */
#define SPI_SR_OVRF_Pos                   (4UL)                     /*!< SPI SR: OVRF (Bit 4)                                  */
#define SPI_SR_OVRF_Msk                   (0x10UL)                  /*!< SPI SR: OVRF (Bitfield-Mask: 0x01)                    */
#define SPI_SR_UDRF_Pos                   (3UL)                     /*!< SPI SR: UDRF (Bit 3)                                  */
#define SPI_SR_UDRF_Msk                   (0x8UL)                   /*!< SPI SR: UDRF (Bitfield-Mask: 0x01)                    */
#define SPI_SR_TXIDLE_Pos                 (2UL)                     /*!< SPI SR: TXIDLE (Bit 2)                                */
#define SPI_SR_TXIDLE_Msk                 (0x4UL)                   /*!< SPI SR: TXIDLE (Bitfield-Mask: 0x01)                  */
#define SPI_SR_TRDY_Pos                   (1UL)                     /*!< SPI SR: TRDY (Bit 1)                                  */
#define SPI_SR_TRDY_Msk                   (0x2UL)                   /*!< SPI SR: TRDY (Bitfield-Mask: 0x01)                    */
#define SPI_SR_RRDY_Pos                   (0UL)                     /*!< SPI SR: RRDY (Bit 0)                                  */
#define SPI_SR_RRDY_Msk                   (0x1UL)                   /*!< SPI SR: RRDY (Bitfield-Mask: 0x01)                    */
/* ==========================================================  BR  =========================================================== */
#define SPI_BR_BR_Pos                     (0UL)                     /*!< SPI BR: BR (Bit 0)                                    */
#define SPI_BR_BR_Msk                     (0xffffUL)                /*!< SPI BR: BR (Bitfield-Mask: 0xffff)                    */
/* ==========================================================  EN  =========================================================== */
#define SPI_EN_ENABLE_Pos                 (0UL)                     /*!< SPI EN: ENABLE (Bit 0)                                */
#define SPI_EN_ENABLE_Msk                 (0x1UL)                   /*!< SPI EN: ENABLE (Bitfield-Mask: 0x01)                  */
/* ==========================================================  LR  =========================================================== */
#define SPI_LR_SPL_Pos                    (16UL)                    /*!< SPI LR: SPL (Bit 16)                                  */
#define SPI_LR_SPL_Msk                    (0xff0000UL)              /*!< SPI LR: SPL (Bitfield-Mask: 0xff)                     */
#define SPI_LR_BTL_Pos                    (8UL)                     /*!< SPI LR: BTL (Bit 8)                                   */
#define SPI_LR_BTL_Msk                    (0xff00UL)                /*!< SPI LR: BTL (Bitfield-Mask: 0xff)                     */
#define SPI_LR_STL_Pos                    (0UL)                     /*!< SPI LR: STL (Bit 0)                                   */
#define SPI_LR_STL_Msk                    (0xffUL)                  /*!< SPI LR: STL (Bitfield-Mask: 0xff)                     */


/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define I2C_CR_EN_Pos                     (7UL)                     /*!< I2C CR: EN (Bit 7)                                    */
#define I2C_CR_EN_Msk                     (0x80UL)                  /*!< I2C CR: EN (Bitfield-Mask: 0x01)                      */
#define I2C_CR_TXDLYENB_Pos               (6UL)                     /*!< I2C CR: TXDLYENB (Bit 6)                              */
#define I2C_CR_TXDLYENB_Msk               (0x40UL)                  /*!< I2C CR: TXDLYENB (Bitfield-Mask: 0x01)                */
#define I2C_CR_IEN_Pos                    (5UL)                     /*!< I2C CR: IEN (Bit 5)                                   */
#define I2C_CR_IEN_Msk                    (0x20UL)                  /*!< I2C CR: IEN (Bitfield-Mask: 0x01)                     */
#define I2C_CR_IFLAG_Pos                  (4UL)                     /*!< I2C CR: IFLAG (Bit 4)                                 */
#define I2C_CR_IFLAG_Msk                  (0x10UL)                  /*!< I2C CR: IFLAG (Bitfield-Mask: 0x01)                   */
#define I2C_CR_ACKEN_Pos                  (3UL)                     /*!< I2C CR: ACKEN (Bit 3)                                 */
#define I2C_CR_ACKEN_Msk                  (0x8UL)                   /*!< I2C CR: ACKEN (Bitfield-Mask: 0x01)                   */
#define I2C_CR_IMASTER_Pos                (2UL)                     /*!< I2C CR: IMASTER (Bit 2)                               */
#define I2C_CR_IMASTER_Msk                (0x4UL)                   /*!< I2C CR: IMASTER (Bitfield-Mask: 0x01)                 */
#define I2C_CR_STOPC_Pos                  (1UL)                     /*!< I2C CR: STOPC (Bit 1)                                 */
#define I2C_CR_STOPC_Msk                  (0x2UL)                   /*!< I2C CR: STOPC (Bitfield-Mask: 0x01)                   */
#define I2C_CR_STARTC_Pos                 (0UL)                     /*!< I2C CR: STARTC (Bit 0)                                */
#define I2C_CR_STARTC_Msk                 (0x1UL)                   /*!< I2C CR: STARTC (Bitfield-Mask: 0x01)                  */
/* ==========================================================  ST  =========================================================== */
#define I2C_ST_SLT_Pos                    (31UL)                    /*!< I2C ST: SLT (Bit 31)                                  */
#define I2C_ST_SLT_Msk                    (0x80000000UL)            /*!< I2C ST: SLT (Bitfield-Mask: 0x01)                     */
#define I2C_ST_GCALL_Pos                  (7UL)                     /*!< I2C ST: GCALL (Bit 7)                                 */
#define I2C_ST_GCALL_Msk                  (0x80UL)                  /*!< I2C ST: GCALL (Bitfield-Mask: 0x01)                   */
#define I2C_ST_TEND_Pos                   (6UL)                     /*!< I2C ST: TEND (Bit 6)                                  */
#define I2C_ST_TEND_Msk                   (0x40UL)                  /*!< I2C ST: TEND (Bitfield-Mask: 0x01)                    */
#define I2C_ST_STOPD_Pos                  (5UL)                     /*!< I2C ST: STOPD (Bit 5)                                 */
#define I2C_ST_STOPD_Msk                  (0x20UL)                  /*!< I2C ST: STOPD (Bitfield-Mask: 0x01)                   */
#define I2C_ST_SSEL_Pos                   (4UL)                     /*!< I2C ST: SSEL (Bit 4)                                  */
#define I2C_ST_SSEL_Msk                   (0x10UL)                  /*!< I2C ST: SSEL (Bitfield-Mask: 0x01)                    */
#define I2C_ST_MLOST_Pos                  (3UL)                     /*!< I2C ST: MLOST (Bit 3)                                 */
#define I2C_ST_MLOST_Msk                  (0x8UL)                   /*!< I2C ST: MLOST (Bitfield-Mask: 0x01)                   */
#define I2C_ST_BUSY_Pos                   (2UL)                     /*!< I2C ST: BUSY (Bit 2)                                  */
#define I2C_ST_BUSY_Msk                   (0x4UL)                   /*!< I2C ST: BUSY (Bitfield-Mask: 0x01)                    */
#define I2C_ST_TMODE_Pos                  (1UL)                     /*!< I2C ST: TMODE (Bit 1)                                 */
#define I2C_ST_TMODE_Msk                  (0x2UL)                   /*!< I2C ST: TMODE (Bitfield-Mask: 0x01)                   */
#define I2C_ST_RXACK_Pos                  (0UL)                     /*!< I2C ST: RXACK (Bit 0)                                 */
#define I2C_ST_RXACK_Msk                  (0x1UL)                   /*!< I2C ST: RXACK (Bitfield-Mask: 0x01)                   */
/* =========================================================  SAR1  ========================================================== */
#define I2C_SAR1_SLA_Pos                  (1UL)                     /*!< I2C SAR1: SLA (Bit 1)                                 */
#define I2C_SAR1_SLA_Msk                  (0xfeUL)                  /*!< I2C SAR1: SLA (Bitfield-Mask: 0x7f)                   */
#define I2C_SAR1_GCALLEN_Pos              (0UL)                     /*!< I2C SAR1: GCALLEN (Bit 0)                             */
#define I2C_SAR1_GCALLEN_Msk              (0x1UL)                   /*!< I2C SAR1: GCALLEN (Bitfield-Mask: 0x01)               */
/* =========================================================  SAR2  ========================================================== */
#define I2C_SAR2_SLA_Pos                  (1UL)                     /*!< I2C SAR2: SLA (Bit 1)                                 */
#define I2C_SAR2_SLA_Msk                  (0xfeUL)                  /*!< I2C SAR2: SLA (Bitfield-Mask: 0x7f)                   */
#define I2C_SAR2_GCALLEN_Pos              (0UL)                     /*!< I2C SAR2: GCALLEN (Bit 0)                             */
#define I2C_SAR2_GCALLEN_Msk              (0x1UL)                   /*!< I2C SAR2: GCALLEN (Bitfield-Mask: 0x01)               */
/* ==========================================================  DR  =========================================================== */
#define I2C_DR_DATA_Pos                   (0UL)                     /*!< I2C DR: DATA (Bit 0)                                  */
#define I2C_DR_DATA_Msk                   (0xffUL)                  /*!< I2C DR: DATA (Bitfield-Mask: 0xff)                    */
/* =========================================================  SDHR  ========================================================== */
#define I2C_SDHR_HLDT_Pos                 (0UL)                     /*!< I2C SDHR: HLDT (Bit 0)                                */
#define I2C_SDHR_HLDT_Msk                 (0xfffUL)                 /*!< I2C SDHR: HLDT (Bitfield-Mask: 0xfff)                 */
/* =========================================================  SCLR  ========================================================== */
#define I2C_SCLR_SCLL_Pos                 (0UL)                     /*!< I2C SCLR: SCLL (Bit 0)                                */
#define I2C_SCLR_SCLL_Msk                 (0xfffUL)                 /*!< I2C SCLR: SCLL (Bitfield-Mask: 0xfff)                 */
/* =========================================================  SCHR  ========================================================== */
#define I2C_SCHR_SCLH_Pos                 (0UL)                     /*!< I2C SCHR: SCLH (Bit 0)                                */
#define I2C_SCHR_SCLH_Msk                 (0xfffUL)                 /*!< I2C SCHR: SCLH (Bitfield-Mask: 0xfff)                 */
/* =========================================================  SLTCR  ========================================================= */
#define I2C_SLTCR_SLTINT_Pos              (1UL)                     /*!< I2C SLTCR: SLTINT (Bit 1)                             */
#define I2C_SLTCR_SLTINT_Msk              (0x2UL)                   /*!< I2C SLTCR: SLTINT (Bitfield-Mask: 0x01)               */
#define I2C_SLTCR_SLTEN_Pos               (0UL)                     /*!< I2C SLTCR: SLTEN (Bit 0)                              */
#define I2C_SLTCR_SLTEN_Msk               (0x1UL)                   /*!< I2C SLTCR: SLTEN (Bitfield-Mask: 0x01)                */
/* ========================================================  SLTPDR  ========================================================= */
#define I2C_SLTPDR_PDATA_Pos              (0UL)                     /*!< I2C SLTPDR: PDATA (Bit 0)                             */
#define I2C_SLTPDR_PDATA_Msk              (0xffffffUL)              /*!< I2C SLTPDR: PDATA (Bitfield-Mask: 0xffffff)           */
/* =========================================================  MBCR  ========================================================== */
#define I2C_MBCR_SCLS_Pos                 (9UL)                     /*!< I2C MBCR: SCLS (Bit 9)                                */
#define I2C_MBCR_SCLS_Msk                 (0x200UL)                 /*!< I2C MBCR: SCLS (Bitfield-Mask: 0x01)                  */
#define I2C_MBCR_SDAS_Pos                 (8UL)                     /*!< I2C MBCR: SDAS (Bit 8)                                */
#define I2C_MBCR_SDAS_Msk                 (0x100UL)                 /*!< I2C MBCR: SDAS (Bitfield-Mask: 0x01)                  */
#define I2C_MBCR_SCLO_Pos                 (3UL)                     /*!< I2C MBCR: SCLO (Bit 3)                                */
#define I2C_MBCR_SCLO_Msk                 (0x8UL)                   /*!< I2C MBCR: SCLO (Bitfield-Mask: 0x01)                  */
#define I2C_MBCR_SDAO_Pos                 (2UL)                     /*!< I2C MBCR: SDAO (Bit 2)                                */
#define I2C_MBCR_SDAO_Msk                 (0x4UL)                   /*!< I2C MBCR: SDAO (Bitfield-Mask: 0x01)                  */
#define I2C_MBCR_SCLMCE_Pos               (1UL)                     /*!< I2C MBCR: SCLMCE (Bit 1)                              */
#define I2C_MBCR_SCLMCE_Msk               (0x2UL)                   /*!< I2C MBCR: SCLMCE (Bitfield-Mask: 0x01)                */
#define I2C_MBCR_SDAMCE_Pos               (0UL)                     /*!< I2C MBCR: SDAMCE (Bit 0)                              */
#define I2C_MBCR_SDAMCE_Msk               (0x1UL)                   /*!< I2C MBCR: SDAMCE (Bitfield-Mask: 0x01)                */


/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  MR  =========================================================== */
#define ADC_MR_TRGINFO_Pos                (21UL)                    /*!< ADC MR: TRGINFO (Bit 21)                              */
#define ADC_MR_TRGINFO_Msk                (0x200000UL)              /*!< ADC MR: TRGINFO (Bitfield-Mask: 0x01)                 */
#define ADC_MR_CHINFO_Pos                 (20UL)                    /*!< ADC MR: CHINFO (Bit 20)                               */
#define ADC_MR_CHINFO_Msk                 (0x100000UL)              /*!< ADC MR: CHINFO (Bitfield-Mask: 0x01)                  */
#define ADC_MR_DMAEN_Pos                  (17UL)                    /*!< ADC MR: DMAEN (Bit 17)                                */
#define ADC_MR_DMAEN_Msk                  (0x20000UL)               /*!< ADC MR: DMAEN (Bitfield-Mask: 0x01)                   */
#define ADC_MR_STSEL_Pos                  (12UL)                    /*!< ADC MR: STSEL (Bit 12)                                */
#define ADC_MR_STSEL_Msk                  (0x1f000UL)               /*!< ADC MR: STSEL (Bitfield-Mask: 0x1f)                   */
#define ADC_MR_SEQCNT_Pos                 (8UL)                     /*!< ADC MR: SEQCNT (Bit 8)                                */
#define ADC_MR_SEQCNT_Msk                 (0x700UL)                 /*!< ADC MR: SEQCNT (Bitfield-Mask: 0x07)                  */
#define ADC_MR_ADEN_Pos                   (7UL)                     /*!< ADC MR: ADEN (Bit 7)                                  */
#define ADC_MR_ADEN_Msk                   (0x80UL)                  /*!< ADC MR: ADEN (Bitfield-Mask: 0x01)                    */
#define ADC_MR_ARST_Pos                   (6UL)                     /*!< ADC MR: ARST (Bit 6)                                  */
#define ADC_MR_ARST_Msk                   (0x40UL)                  /*!< ADC MR: ARST (Bitfield-Mask: 0x01)                    */
#define ADC_MR_ADMOD_Pos                  (4UL)                     /*!< ADC MR: ADMOD (Bit 4)                                 */
#define ADC_MR_ADMOD_Msk                  (0x30UL)                  /*!< ADC MR: ADMOD (Bitfield-Mask: 0x03)                   */
#define ADC_MR_TRGSEL_Pos                 (0UL)                     /*!< ADC MR: TRGSEL (Bit 0)                                */
#define ADC_MR_TRGSEL_Msk                 (0x3UL)                   /*!< ADC MR: TRGSEL (Bitfield-Mask: 0x03)                  */
/* =========================================================  CSCR  ========================================================== */
#define ADC_CSCR_CSEQN_Pos                (8UL)                     /*!< ADC CSCR: CSEQN (Bit 8)                               */
#define ADC_CSCR_CSEQN_Msk                (0x700UL)                 /*!< ADC CSCR: CSEQN (Bitfield-Mask: 0x07)                 */
#define ADC_CSCR_CACH_Pos                 (0UL)                     /*!< ADC CSCR: CACH (Bit 0)                                */
#define ADC_CSCR_CACH_Msk                 (0x1fUL)                  /*!< ADC CSCR: CACH (Bitfield-Mask: 0x1f)                  */
/* ==========================================================  CCR  ========================================================== */
#define ADC_CCR_ADCPDA_Pos                (15UL)                    /*!< ADC CCR: ADCPDA (Bit 15)                              */
#define ADC_CCR_ADCPDA_Msk                (0x8000UL)                /*!< ADC CCR: ADCPDA (Bitfield-Mask: 0x01)                 */
#define ADC_CCR_CLKDIV_Pos                (8UL)                     /*!< ADC CCR: CLKDIV (Bit 8)                               */
#define ADC_CCR_CLKDIV_Msk                (0x7f00UL)                /*!< ADC CCR: CLKDIV (Bitfield-Mask: 0x7f)                 */
#define ADC_CCR_ADCPD_Pos                 (7UL)                     /*!< ADC CCR: ADCPD (Bit 7)                                */
#define ADC_CCR_ADCPD_Msk                 (0x80UL)                  /*!< ADC CCR: ADCPD (Bitfield-Mask: 0x01)                  */
#define ADC_CCR_EXTCLK_Pos                (6UL)                     /*!< ADC CCR: EXTCLK (Bit 6)                               */
#define ADC_CCR_EXTCLK_Msk                (0x40UL)                  /*!< ADC CCR: EXTCLK (Bitfield-Mask: 0x01)                 */
#define ADC_CCR_CLKINVT_Pos               (5UL)                     /*!< ADC CCR: CLKINVT (Bit 5)                              */
#define ADC_CCR_CLKINVT_Msk               (0x20UL)                  /*!< ADC CCR: CLKINVT (Bitfield-Mask: 0x01)                */
/* ==========================================================  TRG  ========================================================== */
#define ADC_TRG_SEQTRG7_Pos               (28UL)                    /*!< ADC TRG: SEQTRG7 (Bit 28)                             */
#define ADC_TRG_SEQTRG7_Msk               (0xf0000000UL)            /*!< ADC TRG: SEQTRG7 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG6_Pos               (24UL)                    /*!< ADC TRG: SEQTRG6 (Bit 24)                             */
#define ADC_TRG_SEQTRG6_Msk               (0xf000000UL)             /*!< ADC TRG: SEQTRG6 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG5_Pos               (20UL)                    /*!< ADC TRG: SEQTRG5 (Bit 20)                             */
#define ADC_TRG_SEQTRG5_Msk               (0xf00000UL)              /*!< ADC TRG: SEQTRG5 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG4_Pos               (16UL)                    /*!< ADC TRG: SEQTRG4 (Bit 16)                             */
#define ADC_TRG_SEQTRG4_Msk               (0xf0000UL)               /*!< ADC TRG: SEQTRG4 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG3_Pos               (12UL)                    /*!< ADC TRG: SEQTRG3 (Bit 12)                             */
#define ADC_TRG_SEQTRG3_Msk               (0xf000UL)                /*!< ADC TRG: SEQTRG3 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG2_Pos               (8UL)                     /*!< ADC TRG: SEQTRG2 (Bit 8)                              */
#define ADC_TRG_SEQTRG2_Msk               (0xf00UL)                 /*!< ADC TRG: SEQTRG2 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG1_Pos               (4UL)                     /*!< ADC TRG: SEQTRG1 (Bit 4)                              */
#define ADC_TRG_SEQTRG1_Msk               (0xf0UL)                  /*!< ADC TRG: SEQTRG1 (Bitfield-Mask: 0x0f)                */
#define ADC_TRG_SEQTRG0_BSTTRG_Pos        (0UL)                     /*!< ADC TRG: SEQTRG0_BSTTRG (Bit 0)                       */
#define ADC_TRG_SEQTRG0_BSTTRG_Msk        (0xfUL)                   /*!< ADC TRG: SEQTRG0_BSTTRG (Bitfield-Mask: 0x0f)         */
/* =========================================================  SCSR1  ========================================================= */
#define ADC_SCSR1_SEQ3CH_Pos              (24UL)                    /*!< ADC SCSR1: SEQ3CH (Bit 24)                            */
#define ADC_SCSR1_SEQ3CH_Msk              (0x1f000000UL)            /*!< ADC SCSR1: SEQ3CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR1_SEQ2CH_Pos              (16UL)                    /*!< ADC SCSR1: SEQ2CH (Bit 16)                            */
#define ADC_SCSR1_SEQ2CH_Msk              (0x1f0000UL)              /*!< ADC SCSR1: SEQ2CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR1_SEQ1CH_Pos              (8UL)                     /*!< ADC SCSR1: SEQ1CH (Bit 8)                             */
#define ADC_SCSR1_SEQ1CH_Msk              (0x1f00UL)                /*!< ADC SCSR1: SEQ1CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR1_SEQ0CH_Pos              (0UL)                     /*!< ADC SCSR1: SEQ0CH (Bit 0)                             */
#define ADC_SCSR1_SEQ0CH_Msk              (0x1fUL)                  /*!< ADC SCSR1: SEQ0CH (Bitfield-Mask: 0x1f)               */
/* =========================================================  SCSR2  ========================================================= */
#define ADC_SCSR2_SEQ7CH_Pos              (24UL)                    /*!< ADC SCSR2: SEQ7CH (Bit 24)                            */
#define ADC_SCSR2_SEQ7CH_Msk              (0x1f000000UL)            /*!< ADC SCSR2: SEQ7CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR2_SEQ6CH_Pos              (16UL)                    /*!< ADC SCSR2: SEQ6CH (Bit 16)                            */
#define ADC_SCSR2_SEQ6CH_Msk              (0x1f0000UL)              /*!< ADC SCSR2: SEQ6CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR2_SEQ5CH_Pos              (8UL)                     /*!< ADC SCSR2: SEQ5CH (Bit 8)                             */
#define ADC_SCSR2_SEQ5CH_Msk              (0x1f00UL)                /*!< ADC SCSR2: SEQ5CH (Bitfield-Mask: 0x1f)               */
#define ADC_SCSR2_SEQ4CH_Pos              (0UL)                     /*!< ADC SCSR2: SEQ4CH (Bit 0)                             */
#define ADC_SCSR2_SEQ4CH_Msk              (0x1fUL)                  /*!< ADC SCSR2: SEQ4CH (Bitfield-Mask: 0x1f)               */
/* ==========================================================  CR  =========================================================== */
#define ADC_CR_ASTOP_Pos                  (7UL)                     /*!< ADC CR: ASTOP (Bit 7)                                 */
#define ADC_CR_ASTOP_Msk                  (0x80UL)                  /*!< ADC CR: ASTOP (Bitfield-Mask: 0x01)                   */
#define ADC_CR_TRGCLR_Pos                 (1UL)                     /*!< ADC CR: TRGCLR (Bit 1)                                */
#define ADC_CR_TRGCLR_Msk                 (0x2UL)                   /*!< ADC CR: TRGCLR (Bitfield-Mask: 0x01)                  */
#define ADC_CR_ASTART_Pos                 (0UL)                     /*!< ADC CR: ASTART (Bit 0)                                */
#define ADC_CR_ASTART_Msk                 (0x1UL)                   /*!< ADC CR: ASTART (Bitfield-Mask: 0x01)                  */
/* ==========================================================  SR  =========================================================== */
#define ADC_SR_CMPIFLG_Pos                (8UL)                     /*!< ADC SR: CMPIFLG (Bit 8)                               */
#define ADC_SR_CMPIFLG_Msk                (0x100UL)                 /*!< ADC SR: CMPIFLG (Bitfield-Mask: 0x01)                 */
#define ADC_SR_DOVRUN_Pos                 (5UL)                     /*!< ADC SR: DOVRUN (Bit 5)                                */
#define ADC_SR_DOVRUN_Msk                 (0x20UL)                  /*!< ADC SR: DOVRUN (Bitfield-Mask: 0x01)                  */
#define ADC_SR_DMAIF_Pos                  (4UL)                     /*!< ADC SR: DMAIF (Bit 4)                                 */
#define ADC_SR_DMAIF_Msk                  (0x10UL)                  /*!< ADC SR: DMAIF (Bitfield-Mask: 0x01)                   */
#define ADC_SR_TRGIF_Pos                  (3UL)                     /*!< ADC SR: TRGIF (Bit 3)                                 */
#define ADC_SR_TRGIF_Msk                  (0x8UL)                   /*!< ADC SR: TRGIF (Bitfield-Mask: 0x01)                   */
#define ADC_SR_EOSIF_Pos                  (2UL)                     /*!< ADC SR: EOSIF (Bit 2)                                 */
#define ADC_SR_EOSIF_Msk                  (0x4UL)                   /*!< ADC SR: EOSIF (Bitfield-Mask: 0x01)                   */
#define ADC_SR_EOCIF_Pos                  (0UL)                     /*!< ADC SR: EOCIF (Bit 0)                                 */
#define ADC_SR_EOCIF_Msk                  (0x1UL)                   /*!< ADC SR: EOCIF (Bitfield-Mask: 0x01)                   */
/* ==========================================================  IER  ========================================================== */
#define ADC_IER_DMAIE_Pos                 (4UL)                     /*!< ADC IER: DMAIE (Bit 4)                                */
#define ADC_IER_DMAIE_Msk                 (0x10UL)                  /*!< ADC IER: DMAIE (Bitfield-Mask: 0x01)                  */
#define ADC_IER_TRGIE_Pos                 (3UL)                     /*!< ADC IER: TRGIE (Bit 3)                                */
#define ADC_IER_TRGIE_Msk                 (0x8UL)                   /*!< ADC IER: TRGIE (Bitfield-Mask: 0x01)                  */
#define ADC_IER_EOSIE_Pos                 (2UL)                     /*!< ADC IER: EOSIE (Bit 2)                                */
#define ADC_IER_EOSIE_Msk                 (0x4UL)                   /*!< ADC IER: EOSIE (Bitfield-Mask: 0x01)                  */
#define ADC_IER_EOCIE_Pos                 (0UL)                     /*!< ADC IER: EOCIE (Bit 0)                                */
#define ADC_IER_EOCIE_Msk                 (0x1UL)                   /*!< ADC IER: EOCIE (Bitfield-Mask: 0x01)                  */
/* ==========================================================  DDR  ========================================================== */
#define ADC_DDR_TRGINFO7_Pos              (31UL)                    /*!< ADC DDR: TRGINFO7 (Bit 31)                            */
#define ADC_DDR_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DDR: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO6_Pos              (30UL)                    /*!< ADC DDR: TRGINFO6 (Bit 30)                            */
#define ADC_DDR_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DDR: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO5_Pos              (29UL)                    /*!< ADC DDR: TRGINFO5 (Bit 29)                            */
#define ADC_DDR_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DDR: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO4_Pos              (28UL)                    /*!< ADC DDR: TRGINFO4 (Bit 28)                            */
#define ADC_DDR_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DDR: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO3_Pos              (27UL)                    /*!< ADC DDR: TRGINFO3 (Bit 27)                            */
#define ADC_DDR_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DDR: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO2_Pos              (26UL)                    /*!< ADC DDR: TRGINFO2 (Bit 26)                            */
#define ADC_DDR_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DDR: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO1_Pos              (25UL)                    /*!< ADC DDR: TRGINFO1 (Bit 25)                            */
#define ADC_DDR_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DDR: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_TRGINFO0_Pos              (24UL)                    /*!< ADC DDR: TRGINFO0 (Bit 24)                            */
#define ADC_DDR_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DDR: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DDR_ADMACH_Pos                (16UL)                    /*!< ADC DDR: ADMACH (Bit 16)                              */
#define ADC_DDR_ADMACH_Msk                (0x1f0000UL)              /*!< ADC DDR: ADMACH (Bitfield-Mask: 0x1f)                 */
#define ADC_DDR_ADDMAR_Pos                (4UL)                     /*!< ADC DDR: ADDMAR (Bit 4)                               */
#define ADC_DDR_ADDMAR_Msk                (0xfff0UL)                /*!< ADC DDR: ADDMAR (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR0  ========================================================== */
#define ADC_DR0_TRGINFO7_Pos              (31UL)                    /*!< ADC DR0: TRGINFO7 (Bit 31)                            */
#define ADC_DR0_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR0: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO6_Pos              (30UL)                    /*!< ADC DR0: TRGINFO6 (Bit 30)                            */
#define ADC_DR0_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR0: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO5_Pos              (29UL)                    /*!< ADC DR0: TRGINFO5 (Bit 29)                            */
#define ADC_DR0_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR0: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO4_Pos              (28UL)                    /*!< ADC DR0: TRGINFO4 (Bit 28)                            */
#define ADC_DR0_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR0: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO3_Pos              (27UL)                    /*!< ADC DR0: TRGINFO3 (Bit 27)                            */
#define ADC_DR0_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR0: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO2_Pos              (26UL)                    /*!< ADC DR0: TRGINFO2 (Bit 26)                            */
#define ADC_DR0_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR0: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO1_Pos              (25UL)                    /*!< ADC DR0: TRGINFO1 (Bit 25)                            */
#define ADC_DR0_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR0: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_TRGINFO0_Pos              (24UL)                    /*!< ADC DR0: TRGINFO0 (Bit 24)                            */
#define ADC_DR0_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR0: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR0_ACH_Pos                   (16UL)                    /*!< ADC DR0: ACH (Bit 16)                                 */
#define ADC_DR0_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR0: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR0_ADDATA_Pos                (4UL)                     /*!< ADC DR0: ADDATA (Bit 4)                               */
#define ADC_DR0_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR0: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR1  ========================================================== */
#define ADC_DR1_TRGINFO7_Pos              (31UL)                    /*!< ADC DR1: TRGINFO7 (Bit 31)                            */
#define ADC_DR1_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR1: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO6_Pos              (30UL)                    /*!< ADC DR1: TRGINFO6 (Bit 30)                            */
#define ADC_DR1_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR1: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO5_Pos              (29UL)                    /*!< ADC DR1: TRGINFO5 (Bit 29)                            */
#define ADC_DR1_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR1: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO4_Pos              (28UL)                    /*!< ADC DR1: TRGINFO4 (Bit 28)                            */
#define ADC_DR1_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR1: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO3_Pos              (27UL)                    /*!< ADC DR1: TRGINFO3 (Bit 27)                            */
#define ADC_DR1_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR1: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO2_Pos              (26UL)                    /*!< ADC DR1: TRGINFO2 (Bit 26)                            */
#define ADC_DR1_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR1: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO1_Pos              (25UL)                    /*!< ADC DR1: TRGINFO1 (Bit 25)                            */
#define ADC_DR1_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR1: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_TRGINFO0_Pos              (24UL)                    /*!< ADC DR1: TRGINFO0 (Bit 24)                            */
#define ADC_DR1_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR1: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR1_ACH_Pos                   (16UL)                    /*!< ADC DR1: ACH (Bit 16)                                 */
#define ADC_DR1_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR1: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR1_ADDATA_Pos                (4UL)                     /*!< ADC DR1: ADDATA (Bit 4)                               */
#define ADC_DR1_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR1: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR2  ========================================================== */
#define ADC_DR2_TRGINFO7_Pos              (31UL)                    /*!< ADC DR2: TRGINFO7 (Bit 31)                            */
#define ADC_DR2_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR2: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO6_Pos              (30UL)                    /*!< ADC DR2: TRGINFO6 (Bit 30)                            */
#define ADC_DR2_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR2: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO5_Pos              (29UL)                    /*!< ADC DR2: TRGINFO5 (Bit 29)                            */
#define ADC_DR2_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR2: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO4_Pos              (28UL)                    /*!< ADC DR2: TRGINFO4 (Bit 28)                            */
#define ADC_DR2_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR2: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO3_Pos              (27UL)                    /*!< ADC DR2: TRGINFO3 (Bit 27)                            */
#define ADC_DR2_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR2: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO2_Pos              (26UL)                    /*!< ADC DR2: TRGINFO2 (Bit 26)                            */
#define ADC_DR2_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR2: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO1_Pos              (25UL)                    /*!< ADC DR2: TRGINFO1 (Bit 25)                            */
#define ADC_DR2_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR2: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_TRGINFO0_Pos              (24UL)                    /*!< ADC DR2: TRGINFO0 (Bit 24)                            */
#define ADC_DR2_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR2: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR2_ACH_Pos                   (16UL)                    /*!< ADC DR2: ACH (Bit 16)                                 */
#define ADC_DR2_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR2: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR2_ADDATA_Pos                (4UL)                     /*!< ADC DR2: ADDATA (Bit 4)                               */
#define ADC_DR2_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR2: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR3  ========================================================== */
#define ADC_DR3_TRGINFO7_Pos              (31UL)                    /*!< ADC DR3: TRGINFO7 (Bit 31)                            */
#define ADC_DR3_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR3: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO6_Pos              (30UL)                    /*!< ADC DR3: TRGINFO6 (Bit 30)                            */
#define ADC_DR3_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR3: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO5_Pos              (29UL)                    /*!< ADC DR3: TRGINFO5 (Bit 29)                            */
#define ADC_DR3_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR3: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO4_Pos              (28UL)                    /*!< ADC DR3: TRGINFO4 (Bit 28)                            */
#define ADC_DR3_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR3: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO3_Pos              (27UL)                    /*!< ADC DR3: TRGINFO3 (Bit 27)                            */
#define ADC_DR3_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR3: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO2_Pos              (26UL)                    /*!< ADC DR3: TRGINFO2 (Bit 26)                            */
#define ADC_DR3_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR3: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO1_Pos              (25UL)                    /*!< ADC DR3: TRGINFO1 (Bit 25)                            */
#define ADC_DR3_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR3: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_TRGINFO0_Pos              (24UL)                    /*!< ADC DR3: TRGINFO0 (Bit 24)                            */
#define ADC_DR3_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR3: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR3_ACH_Pos                   (16UL)                    /*!< ADC DR3: ACH (Bit 16)                                 */
#define ADC_DR3_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR3: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR3_ADDATA_Pos                (4UL)                     /*!< ADC DR3: ADDATA (Bit 4)                               */
#define ADC_DR3_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR3: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR4  ========================================================== */
#define ADC_DR4_TRGINFO7_Pos              (31UL)                    /*!< ADC DR4: TRGINFO7 (Bit 31)                            */
#define ADC_DR4_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR4: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO6_Pos              (30UL)                    /*!< ADC DR4: TRGINFO6 (Bit 30)                            */
#define ADC_DR4_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR4: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO5_Pos              (29UL)                    /*!< ADC DR4: TRGINFO5 (Bit 29)                            */
#define ADC_DR4_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR4: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO4_Pos              (28UL)                    /*!< ADC DR4: TRGINFO4 (Bit 28)                            */
#define ADC_DR4_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR4: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO3_Pos              (27UL)                    /*!< ADC DR4: TRGINFO3 (Bit 27)                            */
#define ADC_DR4_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR4: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO2_Pos              (26UL)                    /*!< ADC DR4: TRGINFO2 (Bit 26)                            */
#define ADC_DR4_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR4: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO1_Pos              (25UL)                    /*!< ADC DR4: TRGINFO1 (Bit 25)                            */
#define ADC_DR4_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR4: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_TRGINFO0_Pos              (24UL)                    /*!< ADC DR4: TRGINFO0 (Bit 24)                            */
#define ADC_DR4_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR4: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR4_ACH_Pos                   (16UL)                    /*!< ADC DR4: ACH (Bit 16)                                 */
#define ADC_DR4_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR4: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR4_ADDATA_Pos                (4UL)                     /*!< ADC DR4: ADDATA (Bit 4)                               */
#define ADC_DR4_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR4: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR5  ========================================================== */
#define ADC_DR5_TRGINFO7_Pos              (31UL)                    /*!< ADC DR5: TRGINFO7 (Bit 31)                            */
#define ADC_DR5_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR5: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO6_Pos              (30UL)                    /*!< ADC DR5: TRGINFO6 (Bit 30)                            */
#define ADC_DR5_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR5: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO5_Pos              (29UL)                    /*!< ADC DR5: TRGINFO5 (Bit 29)                            */
#define ADC_DR5_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR5: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO4_Pos              (28UL)                    /*!< ADC DR5: TRGINFO4 (Bit 28)                            */
#define ADC_DR5_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR5: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO3_Pos              (27UL)                    /*!< ADC DR5: TRGINFO3 (Bit 27)                            */
#define ADC_DR5_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR5: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO2_Pos              (26UL)                    /*!< ADC DR5: TRGINFO2 (Bit 26)                            */
#define ADC_DR5_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR5: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO1_Pos              (25UL)                    /*!< ADC DR5: TRGINFO1 (Bit 25)                            */
#define ADC_DR5_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR5: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_TRGINFO0_Pos              (24UL)                    /*!< ADC DR5: TRGINFO0 (Bit 24)                            */
#define ADC_DR5_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR5: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR5_ACH_Pos                   (16UL)                    /*!< ADC DR5: ACH (Bit 16)                                 */
#define ADC_DR5_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR5: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR5_ADDATA_Pos                (4UL)                     /*!< ADC DR5: ADDATA (Bit 4)                               */
#define ADC_DR5_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR5: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR6  ========================================================== */
#define ADC_DR6_TRGINFO7_Pos              (31UL)                    /*!< ADC DR6: TRGINFO7 (Bit 31)                            */
#define ADC_DR6_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR6: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO6_Pos              (30UL)                    /*!< ADC DR6: TRGINFO6 (Bit 30)                            */
#define ADC_DR6_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR6: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO5_Pos              (29UL)                    /*!< ADC DR6: TRGINFO5 (Bit 29)                            */
#define ADC_DR6_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR6: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO4_Pos              (28UL)                    /*!< ADC DR6: TRGINFO4 (Bit 28)                            */
#define ADC_DR6_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR6: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO3_Pos              (27UL)                    /*!< ADC DR6: TRGINFO3 (Bit 27)                            */
#define ADC_DR6_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR6: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO2_Pos              (26UL)                    /*!< ADC DR6: TRGINFO2 (Bit 26)                            */
#define ADC_DR6_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR6: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO1_Pos              (25UL)                    /*!< ADC DR6: TRGINFO1 (Bit 25)                            */
#define ADC_DR6_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR6: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_TRGINFO0_Pos              (24UL)                    /*!< ADC DR6: TRGINFO0 (Bit 24)                            */
#define ADC_DR6_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR6: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR6_ACH_Pos                   (16UL)                    /*!< ADC DR6: ACH (Bit 16)                                 */
#define ADC_DR6_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR6: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR6_ADDATA_Pos                (4UL)                     /*!< ADC DR6: ADDATA (Bit 4)                               */
#define ADC_DR6_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR6: ADDATA (Bitfield-Mask: 0xfff)                */
/* ==========================================================  DR7  ========================================================== */
#define ADC_DR7_TRGINFO7_Pos              (31UL)                    /*!< ADC DR7: TRGINFO7 (Bit 31)                            */
#define ADC_DR7_TRGINFO7_Msk              (0x80000000UL)            /*!< ADC DR7: TRGINFO7 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO6_Pos              (30UL)                    /*!< ADC DR7: TRGINFO6 (Bit 30)                            */
#define ADC_DR7_TRGINFO6_Msk              (0x40000000UL)            /*!< ADC DR7: TRGINFO6 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO5_Pos              (29UL)                    /*!< ADC DR7: TRGINFO5 (Bit 29)                            */
#define ADC_DR7_TRGINFO5_Msk              (0x20000000UL)            /*!< ADC DR7: TRGINFO5 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO4_Pos              (28UL)                    /*!< ADC DR7: TRGINFO4 (Bit 28)                            */
#define ADC_DR7_TRGINFO4_Msk              (0x10000000UL)            /*!< ADC DR7: TRGINFO4 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO3_Pos              (27UL)                    /*!< ADC DR7: TRGINFO3 (Bit 27)                            */
#define ADC_DR7_TRGINFO3_Msk              (0x8000000UL)             /*!< ADC DR7: TRGINFO3 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO2_Pos              (26UL)                    /*!< ADC DR7: TRGINFO2 (Bit 26)                            */
#define ADC_DR7_TRGINFO2_Msk              (0x4000000UL)             /*!< ADC DR7: TRGINFO2 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO1_Pos              (25UL)                    /*!< ADC DR7: TRGINFO1 (Bit 25)                            */
#define ADC_DR7_TRGINFO1_Msk              (0x2000000UL)             /*!< ADC DR7: TRGINFO1 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_TRGINFO0_Pos              (24UL)                    /*!< ADC DR7: TRGINFO0 (Bit 24)                            */
#define ADC_DR7_TRGINFO0_Msk              (0x1000000UL)             /*!< ADC DR7: TRGINFO0 (Bitfield-Mask: 0x01)               */
#define ADC_DR7_ACH_Pos                   (16UL)                    /*!< ADC DR7: ACH (Bit 16)                                 */
#define ADC_DR7_ACH_Msk                   (0x1f0000UL)              /*!< ADC DR7: ACH (Bitfield-Mask: 0x1f)                    */
#define ADC_DR7_ADDATA_Pos                (4UL)                     /*!< ADC DR7: ADDATA (Bit 4)                               */
#define ADC_DR7_ADDATA_Msk                (0xfff0UL)                /*!< ADC DR7: ADDATA (Bitfield-Mask: 0xfff)                */
/* =========================================================  CMPR  ========================================================== */
#define ADC_CMPR_CMPIEN_Pos               (24UL)                    /*!< ADC CMPR: CMPIEN (Bit 24)                             */
#define ADC_CMPR_CMPIEN_Msk               (0x1000000UL)             /*!< ADC CMPR: CMPIEN (Bitfield-Mask: 0x01)                */
#define ADC_CMPR_CMPEN_Pos                (23UL)                    /*!< ADC CMPR: CMPEN (Bit 23)                              */
#define ADC_CMPR_CMPEN_Msk                (0x800000UL)              /*!< ADC CMPR: CMPEN (Bitfield-Mask: 0x01)                 */
#define ADC_CMPR_LTE_Pos                  (21UL)                    /*!< ADC CMPR: LTE (Bit 21)                                */
#define ADC_CMPR_LTE_Msk                  (0x200000UL)              /*!< ADC CMPR: LTE (Bitfield-Mask: 0x01)                   */
#define ADC_CMPR_CCH_Pos                  (16UL)                    /*!< ADC CMPR: CCH (Bit 16)                                */
#define ADC_CMPR_CCH_Msk                  (0x1f0000UL)              /*!< ADC CMPR: CCH (Bitfield-Mask: 0x1f)                   */
#define ADC_CMPR_CVAL_Pos                 (4UL)                     /*!< ADC CMPR: CVAL (Bit 4)                                */
#define ADC_CMPR_CVAL_Msk                 (0xfff0UL)                /*!< ADC CMPR: CVAL (Bitfield-Mask: 0xfff)                 */
/* ==========================================================  BCR  ========================================================== */
#define ADC_BCR_BYPSEL_Pos                (0UL)                     /*!< ADC BCR: BYPSEL (Bit 0)                               */
#define ADC_BCR_BYPSEL_Msk                (0x1UL)                   /*!< ADC BCR: BYPSEL (Bitfield-Mask: 0x01)                 */
#define ADC_BCR_BUFEN_Pos                 (1UL)                     /*!< ADC BCR: BUFEN (Bit 1)                                */
#define ADC_BCR_BUFEN_Msk                 (0x2UL)                   /*!< ADC BCR: BUFEN (Bitfield-Mask: 0x01)                  */
#define ADC_BCR_TBUFSEL_Pos               (4UL)                     /*!< ADC BCR: TBUFSEL (Bit 4)                              */
#define ADC_BCR_TBUFSEL_Msk               (0x70UL)                  /*!< ADC BCR: TBUFSEL (Bitfield-Mask: 0x07)                */


/* =========================================================================================================================== */
/* ================                                            DAC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  DR  =========================================================== */
#define DAC_DR_DACDR_Pos                  (0UL)                     /*!< DAC DR: DACDR (Bit 0)                                 */
#define DAC_DR_DACDR_Msk                  (0xffffUL)                /*!< DAC DR: DACDR (Bitfield-Mask: 0xffff)                 */
/* ==========================================================  BR  =========================================================== */
#define DAC_BR_DACBR_Pos                  (0UL)                     /*!< DAC BR: DACBR (Bit 0)                                 */
#define DAC_BR_DACBR_Msk                  (0xffffUL)                /*!< DAC BR: DACBR (Bitfield-Mask: 0xffff)                 */
/* ==========================================================  CR  =========================================================== */
#define DAC_CR_DAC_OUT_EN_Pos             (11UL)                    /*!< DAC CR: DAC_OUT_EN (Bit 11)                           */
#define DAC_CR_DAC_OUT_EN_Msk             (0x800UL)                 /*!< DAC CR: DAC_OUT_EN (Bitfield-Mask: 0x01)              */
#define DAC_CR_DAC_BUF_EN_Pos             (10UL)                    /*!< DAC CR: DAC_BUF_EN (Bit 10)                           */
#define DAC_CR_DAC_BUF_EN_Msk             (0x400UL)                 /*!< DAC CR: DAC_BUF_EN (Bitfield-Mask: 0x01)              */
#define DAC_CR_DACBC_Pos                  (4UL)                     /*!< DAC CR: DACBC (Bit 4)                                 */
#define DAC_CR_DACBC_Msk                  (0x10UL)                  /*!< DAC CR: DACBC (Bitfield-Mask: 0x01)                   */
#define DAC_CR_DACRLDS_Pos                (1UL)                     /*!< DAC CR: DACRLDS (Bit 1)                               */
#define DAC_CR_DACRLDS_Msk                (0x6UL)                   /*!< DAC CR: DACRLDS (Bitfield-Mask: 0x03)                 */
#define DAC_CR_DACEN_Pos                  (0UL)                     /*!< DAC CR: DACEN (Bit 0)                                 */
#define DAC_CR_DACEN_Msk                  (0x1UL)                   /*!< DAC CR: DACEN (Bitfield-Mask: 0x01)                   */
/* ==========================================================  ICR  ========================================================== */
#define DAC_ICR_DUDRUNF_Pos               (5UL)                     /*!< DAC ICR: DUDRUNF (Bit 5)                              */
#define DAC_ICR_DUDRUNF_Msk               (0x20UL)                  /*!< DAC ICR: DUDRUNF (Bitfield-Mask: 0x01)                */
#define DAC_ICR_DMAIF_Pos                 (4UL)                     /*!< DAC ICR: DMAIF (Bit 4)                                */
#define DAC_ICR_DMAIF_Msk                 (0x10UL)                  /*!< DAC ICR: DMAIF (Bitfield-Mask: 0x01)                  */
#define DAC_ICR_DUDRUNE_Pos               (1UL)                     /*!< DAC ICR: DUDRUNE (Bit 1)                              */
#define DAC_ICR_DUDRUNE_Msk               (0x2UL)                   /*!< DAC ICR: DUDRUNE (Bitfield-Mask: 0x01)                */
#define DAC_ICR_DAMIE_Pos                 (0UL)                     /*!< DAC ICR: DAMIE (Bit 0)                                */
#define DAC_ICR_DAMIE_Msk                 (0x1UL)                   /*!< DAC ICR: DAMIE (Bitfield-Mask: 0x01)                  */


/* =========================================================================================================================== */
/* ================                                            CMP                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CMP0CR  ========================================================= */
#define CMP_CMP0CR_C0HYSEN_Pos            (20UL)                    /*!< CMP CMP0CR: C0HYSEN (Bit 20)                          */
#define CMP_CMP0CR_C0HYSEN_Msk            (0x100000UL)              /*!< CMP CMP0CR: C0HYSEN (Bitfield-Mask: 0x01)             */
#define CMP_CMP0CR_C0HYSSEL_Pos           (16UL)                    /*!< CMP CMP0CR: C0HYSSEL (Bit 16)                         */
#define CMP_CMP0CR_C0HYSSEL_Msk           (0x10000UL)               /*!< CMP CMP0CR: C0HYSSEL (Bitfield-Mask: 0x01)            */
#define CMP_CMP0CR_C0EN_Pos               (12UL)                    /*!< CMP CMP0CR: C0EN (Bit 12)                             */
#define CMP_CMP0CR_C0EN_Msk               (0x1000UL)                /*!< CMP CMP0CR: C0EN (Bitfield-Mask: 0x01)                */
#define CMP_CMP0CR_C0INNSEL_Pos           (4UL)                     /*!< CMP CMP0CR: C0INNSEL (Bit 4)                          */
#define CMP_CMP0CR_C0INNSEL_Msk           (0x30UL)                  /*!< CMP CMP0CR: C0INNSEL (Bitfield-Mask: 0x03)            */
#define CMP_CMP0CR_C0INPSEL_Pos           (0UL)                     /*!< CMP CMP0CR: C0INPSEL (Bit 0)                          */
#define CMP_CMP0CR_C0INPSEL_Msk           (0x3UL)                   /*!< CMP CMP0CR: C0INPSEL (Bitfield-Mask: 0x03)            */
/* ========================================================  CMP1CR  ========================================================= */
#define CMP_CMP1CR_C1HYSEN_Pos            (20UL)                    /*!< CMP CMP1CR: C1HYSEN (Bit 20)                          */
#define CMP_CMP1CR_C1HYSEN_Msk            (0x100000UL)              /*!< CMP CMP1CR: C1HYSEN (Bitfield-Mask: 0x01)             */
#define CMP_CMP1CR_C1HYSSEL_Pos           (16UL)                    /*!< CMP CMP1CR: C1HYSSEL (Bit 16)                         */
#define CMP_CMP1CR_C1HYSSEL_Msk           (0x10000UL)               /*!< CMP CMP1CR: C1HYSSEL (Bitfield-Mask: 0x01)            */
#define CMP_CMP1CR_C1EN_Pos               (12UL)                    /*!< CMP CMP1CR: C1EN (Bit 12)                             */
#define CMP_CMP1CR_C1EN_Msk               (0x1000UL)                /*!< CMP CMP1CR: C1EN (Bitfield-Mask: 0x01)                */
#define CMP_CMP1CR_C1INNSEL_Pos           (4UL)                     /*!< CMP CMP1CR: C1INNSEL (Bit 4)                          */
#define CMP_CMP1CR_C1INNSEL_Msk           (0x30UL)                  /*!< CMP CMP1CR: C1INNSEL (Bitfield-Mask: 0x03)            */
#define CMP_CMP1CR_C1INPSEL_Pos           (0UL)                     /*!< CMP CMP1CR: C1INPSEL (Bit 0)                          */
#define CMP_CMP1CR_C1INPSEL_Msk           (0x3UL)                   /*!< CMP CMP1CR: C1INPSEL (Bitfield-Mask: 0x03)            */
/* =========================================================  DBNC  ========================================================== */
#define CMP_DBNC_DBNCTB_Pos               (16UL)                    /*!< CMP DBNC: DBNCTB (Bit 16)                             */
#define CMP_DBNC_DBNCTB_Msk               (0xffff0000UL)            /*!< CMP DBNC: DBNCTB (Bitfield-Mask: 0xffff)              */
#define CMP_DBNC_C1DBNC_Pos               (4UL)                     /*!< CMP DBNC: C1DBNC (Bit 4)                              */
#define CMP_DBNC_C1DBNC_Msk               (0xf0UL)                  /*!< CMP DBNC: C1DBNC (Bitfield-Mask: 0x0f)                */
#define CMP_DBNC_C0DBNC_Pos               (0UL)                     /*!< CMP DBNC: C0DBNC (Bit 0)                              */
#define CMP_DBNC_C0DBNC_Msk               (0xfUL)                   /*!< CMP DBNC: C0DBNC (Bitfield-Mask: 0x0f)                */
/* =========================================================  ICON  ========================================================== */
#define CMP_ICON_C1TPOL_Pos               (13UL)                    /*!< CMP ICON: C1TPOL (Bit 13)                             */
#define CMP_ICON_C1TPOL_Msk               (0x2000UL)                /*!< CMP ICON: C1TPOL (Bitfield-Mask: 0x01)                */
#define CMP_ICON_C0TPOL_Pos               (12UL)                    /*!< CMP ICON: C0TPOL (Bit 12)                             */
#define CMP_ICON_C0TPOL_Msk               (0x1000UL)                /*!< CMP ICON: C0TPOL (Bitfield-Mask: 0x01)                */
#define CMP_ICON_C1IPOL_Pos               (9UL)                     /*!< CMP ICON: C1IPOL (Bit 9)                              */
#define CMP_ICON_C1IPOL_Msk               (0x200UL)                 /*!< CMP ICON: C1IPOL (Bitfield-Mask: 0x01)                */
#define CMP_ICON_C0IPOL_Pos               (8UL)                     /*!< CMP ICON: C0IPOL (Bit 8)                              */
#define CMP_ICON_C0IPOL_Msk               (0x100UL)                 /*!< CMP ICON: C0IPOL (Bitfield-Mask: 0x01)                */
#define CMP_ICON_C1IMODE_Pos              (2UL)                     /*!< CMP ICON: C1IMODE (Bit 2)                             */
#define CMP_ICON_C1IMODE_Msk              (0xcUL)                   /*!< CMP ICON: C1IMODE (Bitfield-Mask: 0x03)               */
#define CMP_ICON_C0IMODE_Pos              (0UL)                     /*!< CMP ICON: C0IMODE (Bit 0)                             */
#define CMP_ICON_C0IMODE_Msk              (0x3UL)                   /*!< CMP ICON: C0IMODE (Bitfield-Mask: 0x03)               */
/* ==========================================================  IEN  ========================================================== */
#define CMP_IEN_COUTMON_Pos               (7UL)                     /*!< CMP IEN: COUTMON (Bit 7)                              */
#define CMP_IEN_COUTMON_Msk               (0x80UL)                  /*!< CMP IEN: COUTMON (Bitfield-Mask: 0x01)                */
#define CMP_IEN_C1IEN_Pos                 (1UL)                     /*!< CMP IEN: C1IEN (Bit 1)                                */
#define CMP_IEN_C1IEN_Msk                 (0x2UL)                   /*!< CMP IEN: C1IEN (Bitfield-Mask: 0x01)                  */
#define CMP_IEN_C0IEN_Pos                 (0UL)                     /*!< CMP IEN: C0IEN (Bit 0)                                */
#define CMP_IEN_C0IEN_Msk                 (0x1UL)                   /*!< CMP IEN: C0IEN (Bitfield-Mask: 0x01)                  */
/* ==========================================================  IST  ========================================================== */
#define CMP_IST_C1EPF_Pos                 (19UL)                    /*!< CMP IST: C1EPF (Bit 19)                               */
#define CMP_IST_C1EPF_Msk                 (0x80000UL)               /*!< CMP IST: C1EPF (Bitfield-Mask: 0x01)                  */
#define CMP_IST_C1EPR_Pos                 (18UL)                    /*!< CMP IST: C1EPR (Bit 18)                               */
#define CMP_IST_C1EPR_Msk                 (0x40000UL)               /*!< CMP IST: C1EPR (Bitfield-Mask: 0x01)                  */
#define CMP_IST_C0EPF_Pos                 (17UL)                    /*!< CMP IST: C0EPF (Bit 17)                               */
#define CMP_IST_C0EPF_Msk                 (0x20000UL)               /*!< CMP IST: C0EPF (Bitfield-Mask: 0x01)                  */
#define CMP_IST_C0EPR_Pos                 (16UL)                    /*!< CMP IST: C0EPR (Bit 16)                               */
#define CMP_IST_C0EPR_Msk                 (0x10000UL)               /*!< CMP IST: C0EPR (Bitfield-Mask: 0x01)                  */
#define CMP_IST_C1COUT_Pos                (13UL)                    /*!< CMP IST: C1COUT (Bit 13)                              */
#define CMP_IST_C1COUT_Msk                (0x2000UL)                /*!< CMP IST: C1COUT (Bitfield-Mask: 0x01)                 */
#define CMP_IST_C0COUT_Pos                (12UL)                    /*!< CMP IST: C0COUT (Bit 12)                              */
#define CMP_IST_C0COUT_Msk                (0x1000UL)                /*!< CMP IST: C0COUT (Bitfield-Mask: 0x01)                 */
#define CMP_IST_C1DO_Pos                  (9UL)                     /*!< CMP IST: C1DO (Bit 9)                                 */
#define CMP_IST_C1DO_Msk                  (0x200UL)                 /*!< CMP IST: C1DO (Bitfield-Mask: 0x01)                   */
#define CMP_IST_C0DO_Pos                  (8UL)                     /*!< CMP IST: C0DO (Bit 8)                                 */
#define CMP_IST_C0DO_Msk                  (0x100UL)                 /*!< CMP IST: C0DO (Bitfield-Mask: 0x01)                   */
#define CMP_IST_C1IRQ_Pos                 (1UL)                     /*!< CMP IST: C1IRQ (Bit 1)                                */
#define CMP_IST_C1IRQ_Msk                 (0x2UL)                   /*!< CMP IST: C1IRQ (Bitfield-Mask: 0x01)                  */
#define CMP_IST_C0IRQ_Pos                 (0UL)                     /*!< CMP IST: C0IRQ (Bit 0)                                */
#define CMP_IST_C0IRQ_Msk                 (0x1UL)                   /*!< CMP IST: C0IRQ (Bitfield-Mask: 0x01)                  */
/* =========================================================  ICLR  ========================================================== */
#define CMP_ICLR_C1EPFFC_Pos              (19UL)                    /*!< CMP ICLR: C1EPFFC (Bit 19)                            */
#define CMP_ICLR_C1EPFFC_Msk              (0x80000UL)               /*!< CMP ICLR: C1EPFFC (Bitfield-Mask: 0x01)               */
#define CMP_ICLR_C1EPRFC_Pos              (18UL)                    /*!< CMP ICLR: C1EPRFC (Bit 18)                            */
#define CMP_ICLR_C1EPRFC_Msk              (0x40000UL)               /*!< CMP ICLR: C1EPRFC (Bitfield-Mask: 0x01)               */
#define CMP_ICLR_C0EPFFC_Pos              (17UL)                    /*!< CMP ICLR: C0EPFFC (Bit 17)                            */
#define CMP_ICLR_C0EPFFC_Msk              (0x20000UL)               /*!< CMP ICLR: C0EPFFC (Bitfield-Mask: 0x01)               */
#define CMP_ICLR_C0EPRFC_Pos              (16UL)                    /*!< CMP ICLR: C0EPRFC (Bit 16)                            */
#define CMP_ICLR_C0EPRFC_Msk              (0x10000UL)               /*!< CMP ICLR: C0EPRFC (Bitfield-Mask: 0x01)               */
#define CMP_ICLR_C1ICLR_Pos               (1UL)                     /*!< CMP ICLR: C1ICLR (Bit 1)                              */
#define CMP_ICLR_C1ICLR_Msk               (0x2UL)                   /*!< CMP ICLR: C1ICLR (Bitfield-Mask: 0x01)                */
#define CMP_ICLR_C0ICLR_Pos               (0UL)                     /*!< CMP ICLR: C0ICLR (Bit 0)                              */
#define CMP_ICLR_C0ICLR_Msk               (0x1UL)                   /*!< CMP ICLR: C0ICLR (Bitfield-Mask: 0x01)                */


/* =========================================================================================================================== */
/* ================                                            LCD                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define LCD_CR_IRSEL_Pos                  (6UL)                     /*!< LCD CR: IRSEL (Bit 6)                                 */
#define LCD_CR_IRSEL_Msk                  (0xc0UL)                  /*!< LCD CR: IRSEL (Bitfield-Mask: 0x03)                   */
#define LCD_CR_DBS_Pos                    (3UL)                     /*!< LCD CR: DBS (Bit 3)                                   */
#define LCD_CR_DBS_Msk                    (0x38UL)                  /*!< LCD CR: DBS (Bitfield-Mask: 0x07)                     */
#define LCD_CR_LCLK_Pos                   (1UL)                     /*!< LCD CR: LCLK (Bit 1)                                  */
#define LCD_CR_LCLK_Msk                   (0x6UL)                   /*!< LCD CR: LCLK (Bitfield-Mask: 0x03)                    */
#define LCD_CR_DISP_Pos                   (0UL)                     /*!< LCD CR: DISP (Bit 0)                                  */
#define LCD_CR_DISP_Msk                   (0x1UL)                   /*!< LCD CR: DISP (Bitfield-Mask: 0x01)                    */
/* =========================================================  BCCR  ========================================================== */
#define LCD_BCCR_LCDABC_Pos               (12UL)                    /*!< LCD BCCR: LCDABC (Bit 12)                             */
#define LCD_BCCR_LCDABC_Msk               (0x1000UL)                /*!< LCD BCCR: LCDABC (Bitfield-Mask: 0x01)                */
#define LCD_BCCR_BMSEL_Pos                (8UL)                     /*!< LCD BCCR: BMSEL (Bit 8)                               */
#define LCD_BCCR_BMSEL_Msk                (0x700UL)                 /*!< LCD BCCR: BMSEL (Bitfield-Mask: 0x07)                 */
#define LCD_BCCR_LCTEN_Pos                (5UL)                     /*!< LCD BCCR: LCTEN (Bit 5)                               */
#define LCD_BCCR_LCTEN_Msk                (0x20UL)                  /*!< LCD BCCR: LCTEN (Bitfield-Mask: 0x01)                 */
#define LCD_BCCR_VLCD_Pos                 (0UL)                     /*!< LCD BCCR: VLCD (Bit 0)                                */
#define LCD_BCCR_VLCD_Msk                 (0xfUL)                   /*!< LCD BCCR: VLCD (Bitfield-Mask: 0x0f)                  */
/* =========================================================  BSSR  ========================================================== */
#define LCD_BSSR_VLE_EN_Pos               (11UL)                    /*!< LCD BSSR: VLE_EN (Bit 11)                             */
#define LCD_BSSR_VLE_EN_Msk               (0x800UL)                 /*!< LCD BSSR: VLE_EN (Bitfield-Mask: 0x01)                */
#define LCD_BSSR_LCDDR_Pos                (9UL)                     /*!< LCD BSSR: LCDDR (Bit 9)                               */
#define LCD_BSSR_LCDDR_Msk                (0x200UL)                 /*!< LCD BSSR: LCDDR (Bitfield-Mask: 0x01)                 */
#define LCD_BSSR_LCDEPEN_Pos              (8UL)                     /*!< LCD BSSR: LCDEPEN (Bit 8)                             */
#define LCD_BSSR_LCDEPEN_Msk              (0x100UL)                 /*!< LCD BSSR: LCDEPEN (Bitfield-Mask: 0x01)               */
#define LCD_BSSR_VLC3EN_Pos               (7UL)                     /*!< LCD BSSR: VLC3EN (Bit 7)                              */
#define LCD_BSSR_VLC3EN_Msk               (0x80UL)                  /*!< LCD BSSR: VLC3EN (Bitfield-Mask: 0x01)                */
#define LCD_BSSR_VLC2EN_Pos               (6UL)                     /*!< LCD BSSR: VLC2EN (Bit 6)                              */
#define LCD_BSSR_VLC2EN_Msk               (0x40UL)                  /*!< LCD BSSR: VLC2EN (Bitfield-Mask: 0x01)                */
#define LCD_BSSR_VLC1EN_Pos               (5UL)                     /*!< LCD BSSR: VLC1EN (Bit 5)                              */
#define LCD_BSSR_VLC1EN_Msk               (0x20UL)                  /*!< LCD BSSR: VLC1EN (Bitfield-Mask: 0x01)                */
#define LCD_BSSR_VLC0EN_Pos               (4UL)                     /*!< LCD BSSR: VLC0EN (Bit 4)                              */
#define LCD_BSSR_VLC0EN_Msk               (0x10UL)                  /*!< LCD BSSR: VLC0EN (Bitfield-Mask: 0x01)                */
/* ========================================================  LCDDR0  ========================================================= */
/* ========================================================  LCDDR1  ========================================================= */
/* ========================================================  LCDDR2  ========================================================= */
/* ========================================================  LCDDR3  ========================================================= */
/* ========================================================  LCDDR4  ========================================================= */
/* ========================================================  LCDDR5  ========================================================= */
/* ========================================================  LCDDR6  ========================================================= */
/* ========================================================  LCDDR7  ========================================================= */
/* ========================================================  LCDDR8  ========================================================= */
/* ========================================================  LCDDR9  ========================================================= */
/* ========================================================  LCDDR10  ======================================================== */
/* ========================================================  LCDDR11  ======================================================== */
/* ========================================================  LCDDR12  ======================================================== */
/* ========================================================  LCDDR13  ======================================================== */
/* ========================================================  LCDDR14  ======================================================== */
/* ========================================================  LCDDR15  ======================================================== */
/* ========================================================  LCDDR16  ======================================================== */
/* ========================================================  LCDDR17  ======================================================== */
/* ========================================================  LCDDR18  ======================================================== */
/* ========================================================  LCDDR19  ======================================================== */
/* ========================================================  LCDDR20  ======================================================== */
/* ========================================================  LCDDR21  ======================================================== */
/* ========================================================  LCDDR22  ======================================================== */
/* ========================================================  LCDDR23  ======================================================== */
/* ========================================================  LCDDR24  ======================================================== */
/* ========================================================  LCDDR25  ======================================================== */
/* ========================================================  LCDDR26  ======================================================== */
/* ========================================================  LCDDR27  ======================================================== */
/* ========================================================  LCDDR28  ======================================================== */
/* ========================================================  LCDDR29  ======================================================== */
/* ========================================================  LCDDR30  ======================================================== */
/* ========================================================  LCDDR31  ======================================================== */
/* ========================================================  LCDDR32  ======================================================== */
/* ========================================================  LCDDR33  ======================================================== */
/* ========================================================  LCDDR34  ======================================================== */
/* ========================================================  LCDDR35  ======================================================== */
/* ========================================================  LCDDR36  ======================================================== */
/* ========================================================  LCDDR37  ======================================================== */
/* ========================================================  LCDDR38  ======================================================== */
/* ========================================================  LCDDR39  ======================================================== */
/* ========================================================  LCDDR40  ======================================================== */
/* ========================================================  LCDDR41  ======================================================== */
/* ========================================================  LCDDR42  ======================================================== */
/* ========================================================  LCDDR43  ======================================================== */


/* =========================================================================================================================== */
/* ================                                            CRC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define CRC_CR_OUT_INV_Pos                (21UL)                    /*!< CRC CR: OUT_INV (Bit 21)                              */
#define CRC_CR_OUT_INV_Msk                (0x200000UL)              /*!< CRC CR: OUT_INV (Bitfield-Mask: 0x01)                 */
#define CRC_CR_OUT_REV_Pos                (20UL)                    /*!< CRC CR: OUT_REV (Bit 20)                              */
#define CRC_CR_OUT_REV_Msk                (0x100000UL)              /*!< CRC CR: OUT_REV (Bitfield-Mask: 0x01)                 */
#define CRC_CR_IN_REV_Pos                 (16UL)                    /*!< CRC CR: IN_REV (Bit 16)                               */
#define CRC_CR_IN_REV_Msk                 (0x10000UL)               /*!< CRC CR: IN_REV (Bitfield-Mask: 0x01)                  */
#define CRC_CR_DMADINT_Pos                (8UL)                     /*!< CRC CR: DMADINT (Bit 8)                               */
#define CRC_CR_DMADINT_Msk                (0x100UL)                 /*!< CRC CR: DMADINT (Bitfield-Mask: 0x01)                 */
#define CRC_CR_POLY_Pos                   (1UL)                     /*!< CRC CR: POLY (Bit 1)                                  */
#define CRC_CR_POLY_Msk                   (0x6UL)                   /*!< CRC CR: POLY (Bitfield-Mask: 0x03)                    */
#define CRC_CR_INIT_EN_Pos                (0UL)                     /*!< CRC CR: INIT_EN (Bit 0)                               */
#define CRC_CR_INIT_EN_Msk                (0x1UL)                   /*!< CRC CR: INIT_EN (Bitfield-Mask: 0x01)                 */
/* =========================================================  INIT  ========================================================== */
/* ==========================================================  IDR  ========================================================== */
#define CRC_IDR_INPUT_Pos                 (0UL)                     /*!< CRC IDR: INPUT (Bit 0)                                */
#define CRC_IDR_INPUT_Msk                 (0xffUL)                  /*!< CRC IDR: INPUT (Bitfield-Mask: 0xff)                  */
/* ==========================================================  ODR  ========================================================== */
#define CRC_ODR_OUTPUT_Pos                (0UL)                     /*!< CRC ODR: OUTPUT (Bit 0)                               */
#define CRC_ODR_OUTPUT_Msk                (0xffffffffUL)            /*!< CRC ODR: OUTPUT (Bitfield-Mask: 0xffffffff)           */
/* ==========================================================  SR  =========================================================== */
#define CRC_SR_DMADINT_Pos                (8UL)                     /*!< CRC SR: DMADINT (Bit 8)                               */
#define CRC_SR_DMADINT_Msk                (0x100UL)                 /*!< CRC SR: DMADINT (Bitfield-Mask: 0x01)                 */


/* =========================================================================================================================== */
/* ================                                            TS                                             ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define TS_CR_INTEN_Pos                   (8UL)                     /*!< TS CR: INTEN (Bit 8)                                  */
#define TS_CR_INTEN_Msk                   (0x100UL)                 /*!< TS CR: INTEN (Bitfield-Mask: 0x01)                    */
#define TS_CR_START_Pos                   (0UL)                     /*!< TS CR: START (Bit 0)                                  */
#define TS_CR_START_Msk                   (0x1UL)                   /*!< TS CR: START (Bitfield-Mask: 0x01)                    */
/* =========================================================  RCCNT  ========================================================= */
#define TS_RCCNT_RCCV_Pos                 (0UL)                     /*!< TS RCCNT: RCCV (Bit 0)                                */
#define TS_RCCNT_RCCV_Msk                 (0xffffffffUL)            /*!< TS RCCNT: RCCV (Bitfield-Mask: 0xffffffff)            */
/* =========================================================  SCCNT  ========================================================= */
#define TS_SCCNT_SCCV_Pos                 (0UL)                     /*!< TS SCCNT: SCCV (Bit 0)                                */
#define TS_SCCNT_SCCV_Msk                 (0xffffffffUL)            /*!< TS SCCNT: SCCV (Bitfield-Mask: 0xffffffff)            */
/* ==========================================================  SR  =========================================================== */
#define TS_SR_DONE_Pos                    (8UL)                     /*!< TS SR: DONE (Bit 8)                                   */
#define TS_SR_DONE_Msk                    (0x100UL)                 /*!< TS SR: DONE (Bitfield-Mask: 0x01)                     */
#define TS_SR_BUSY_Pos                    (0UL)                     /*!< TS SR: BUSY (Bit 0)                                   */
#define TS_SR_BUSY_Msk                    (0x1UL)                   /*!< TS SR: BUSY (Bitfield-Mask: 0x01)                     */

/** @} */ /* End of group PosMask_peripherals */


#ifdef __cplusplus
}
#endif

#endif /* A31G22X_H */


/** @} */ /* End of group A31G22x */

/** @} */ /* End of group ABOV Semiconductor Co., Ltd. */
