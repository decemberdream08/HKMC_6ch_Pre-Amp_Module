/**
 *******************************************************************************
 * @file        debug_frmwrk.h
 * @author      ABOV R&D Division
 * @brief       debug_frmwrk file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _DEBUG_FRMWRK_H_
#define _DEBUG_FRMWRK_H_

/* Includes ------------------------------------------------------------------- */
#include "A31G22x_hal_uartn.h"
#include "A31G22x_hal_usart1n.h"

#define     DEBUG_POLLING
//#define     DEBUG_INTERRUPT

#define DEBUG_PORT_NUMBER	1 //ESTEC_BOARD : To USE UART1 for debugg port

#if (DEBUG_PORT_NUMBER == 0)
#define DEBUG_PORT	UART0
#elif (DEBUG_PORT_NUMBER == 1)
#define DEBUG_PORT	UART1
#elif (DEBUG_PORT_NUMBER == 10)
#define DEBUG_PORT	USART10
#elif (DEBUG_PORT_NUMBER == 11)
#define DEBUG_PORT	USART11
#elif (DEBUG_PORT_NUMBER == 12)
#define DEBUG_PORT	USART12
#elif (DEBUG_PORT_NUMBER == 13)
#define DEBUG_PORT	USART13
#else
#define	DEBUG_PORT	(NULL)
#endif

extern uint8_t uart_mode;
extern uint8_t usart_mode;

int32_t	cgetc(void);
int32_t	cgetchar(void);
int32_t	cgets(char *strin, int32_t maxsize);
void	cputc(char ch);
int32_t	cputs(char *strin);
void	cflush(void);
int32_t	cwrite(void *p,int size);
int32_t	cread(void *p,int size);
int32_t	cprintf(const  char *format, ...);

void 	debug_frmwrk_init(void);
void	dbg_init(void);
int32_t	dbg_console_check(void);
void	_DBG(const char *msg);



typedef struct {
	int32_t		type;
	char		*name;
	void		*variable;
	int32_t		arguement;
} DEBUG_VARIABLES;


#endif /* _DEBUG_FRMWRK_H_ */

/* --------------------------------- End Of File ------------------------------ */
