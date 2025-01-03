;/**
;*******************************************************************************
;* @file        startup_A31G22x.s
;* @author      ABOV R&D Division
;* @brief       Startup APIs for A31G22x
;*
;* Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
;*
;* This file is licensed under terms that are found in the LICENSE file
;* located at Document directory.
;* If this file is delivered or shared without applicable license terms,
;* the terms of the BSD-3-Clause license shall be applied.
;* Reference: https://opensource.org/licenses/BSD-3-Clause
;******************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                    ; Top of Stack
                DCD     Reset_Handler                   ; Reset Handler
                DCD     NMI_Handler                     ; NMI Handler
                DCD     HardFault_Handler               ; Hard Fault Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     SVC_Handler                     ; SVCall Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     PendSV_Handler                  ; PendSV Handler
                DCD     SysTick_Handler                 ; SysTick Handler

; External Interrupts
                DCD     LVI_IRQHandler                  ; IRQ0
                DCD     SYSCLKFAIL_IRQHandler           ; IRQ1
                DCD     WDT_IRQHandler                  ; IRQ2
                DCD     GPIOAB_IRQHandler               ; IRQ3
                DCD     GPIOCD_IRQHandler               ; IRQ4
                DCD     GPIOE_IRQHandler                ; IRQ5
                DCD     GPIOF_IRQHandler                ; IRQ6
                DCD     TIMER10_IRQHandler              ; IRQ7
                DCD     TIMER11_IRQHandler              ; IRQ8
                DCD     TIMER12_IRQHandler              ; IRQ9
                DCD     I2C0_IRQHandler                 ; IRQ10
                DCD     USART10_IRQHandler              ; IRQ11
                DCD     WT_IRQHandler                   ; IRQ12
                DCD     TIMER30_IRQHandler              ; IRQ13
                DCD     I2C1_IRQHandler                 ; IRQ14
                DCD     TIMER20_IRQHandler              ; IRQ15
                DCD     TIMER21_IRQHandler              ; IRQ16
                DCD     USART11_IRQHandler              ; IRQ17
                DCD     ADC_IRQHandler                  ; IRQ18
                DCD     UART0_IRQHandler                ; IRQ19
                DCD     UART1_IRQHandler                ; IRQ20
                DCD     TIMER13_IRQHandler              ; IRQ21
                DCD     TIMER14_IRQHandler              ; IRQ22
                DCD     TIMER15_IRQHandler              ; IRQ23
                DCD     TIMER16_IRQHandler              ; IRQ24
                DCD     I2C2_SPI20_IRQHandler           ; IRQ25
                DCD     USART12_13_SPI21_IRQHandler     ; IRQ26
                DCD     DAC_IRQHandler                  ; IRQ27
                DCD     TEMP_SENSOR_IRQHandler          ; IRQ28
                DCD     NULL_IRQHandler                 ; IRQ29
                DCD     NULL_IRQHandler                 ; IRQ30
                DCD     CMP_CRC_IRQHandler              ; IRQ31

                AREA    |.text|, CODE, READONLY

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler                   [WEAK]
                IMPORT  __main
                IMPORT  SystemInit

                LDR     R0, =SystemInit
                BLX     R0
                LDR		R0, =__main
                BX		R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler     PROC
                EXPORT  NMI_Handler                     [WEAK]
                B       .
                ENDP
HardFault_Handler PROC
                EXPORT  HardFault_Handler               [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                     [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                  [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                 [WEAK]
                B       .
                ENDP

; External Interrupt Handlers
NULL_IRQHandler PROC
                EXPORT  LVI_IRQHandler                  [WEAK]
                EXPORT  SYSCLKFAIL_IRQHandler           [WEAK]
                EXPORT  WDT_IRQHandler                  [WEAK]
                EXPORT  GPIOAB_IRQHandler               [WEAK]
                EXPORT  GPIOCD_IRQHandler               [WEAK]
                EXPORT  GPIOE_IRQHandler                [WEAK]
                EXPORT  GPIOF_IRQHandler                [WEAK]
                EXPORT  TIMER10_IRQHandler              [WEAK]
                EXPORT  TIMER11_IRQHandler              [WEAK]
                EXPORT  TIMER12_IRQHandler              [WEAK]
                EXPORT  I2C0_IRQHandler                 [WEAK]
                EXPORT  USART10_IRQHandler              [WEAK]
                EXPORT  WT_IRQHandler                   [WEAK]
                EXPORT  TIMER30_IRQHandler              [WEAK]
                EXPORT  I2C1_IRQHandler                 [WEAK]
                EXPORT  TIMER20_IRQHandler              [WEAK]
                EXPORT  TIMER21_IRQHandler              [WEAK]
                EXPORT  USART11_IRQHandler              [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  UART0_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  TIMER13_IRQHandler              [WEAK]
                EXPORT  TIMER14_IRQHandler              [WEAK]
                EXPORT  TIMER15_IRQHandler              [WEAK]
                EXPORT  TIMER16_IRQHandler              [WEAK]
                EXPORT  I2C2_SPI20_IRQHandler           [WEAK]
                EXPORT  USART12_13_SPI21_IRQHandler     [WEAK]
                EXPORT  DAC_IRQHandler                  [WEAK]
                EXPORT  TEMP_SENSOR_IRQHandler          [WEAK]
                EXPORT  CMP_CRC_IRQHandler              [WEAK]
LVI_IRQHandler                                          ; IRQ0
SYSCLKFAIL_IRQHandler                                   ; IRQ1
WDT_IRQHandler                                          ; IRQ2
GPIOAB_IRQHandler                                       ; IRQ3
GPIOCD_IRQHandler                                       ; IRQ4
GPIOE_IRQHandler                                        ; IRQ5
GPIOF_IRQHandler                                        ; IRQ6
TIMER10_IRQHandler                                      ; IRQ7
TIMER11_IRQHandler                                      ; IRQ8
TIMER12_IRQHandler                                      ; IRQ9
I2C0_IRQHandler                                         ; IRQ10
USART10_IRQHandler                                      ; IRQ11
WT_IRQHandler                                           ; IRQ12
TIMER30_IRQHandler                                      ; IRQ13
I2C1_IRQHandler                                         ; IRQ14
TIMER20_IRQHandler                                      ; IRQ15
TIMER21_IRQHandler                                      ; IRQ16
USART11_IRQHandler                                      ; IRQ17
ADC_IRQHandler                                          ; IRQ18
UART0_IRQHandler                                        ; IRQ19
UART1_IRQHandler                                        ; IRQ20
TIMER13_IRQHandler                                      ; IRQ21
TIMER14_IRQHandler                                      ; IRQ22
TIMER15_IRQHandler                                      ; IRQ23
TIMER16_IRQHandler                                      ; IRQ24
I2C2_SPI20_IRQHandler                                   ; IRQ25
USART12_13_SPI21_IRQHandler                             ; IRQ26
DAC_IRQHandler                                          ; IRQ27 
TEMP_SENSOR_IRQHandler                                  ; IRQ28
CMP_CRC_IRQHandler                                      ; IRQ31
                B       .
                ENDP

                ALIGN
; User Initial Stack & Heap
                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
