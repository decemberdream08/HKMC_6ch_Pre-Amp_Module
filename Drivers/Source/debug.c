/**
 *******************************************************************************
 * @file        debug.c
 * @author      ABOV R&D Division
 * @brief       debug file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/
 
#include <stdint.h>
#include "debug_frmwrk.h"

char	var_a;
char	var_b;
int32_t	msec;
int32_t	count;

int	clear_variables(int32_t arg)
{
	cprintf("a = %d, b = %d\r\nmsec = %d, count = %d\r\n", var_a, var_b, msec, count);

	// clear variables
	var_a = 0;
	var_b = 0;
	msec = 0;
	count = 0;

	return 0;
}

DEBUG_VARIABLES dbg_variables[] = {
	{	1,	"a", (void*)&var_a,	0	},
	{	1,	"b", (void*)&var_a,	0	},
	{	4,	"msec", (void*)&msec,	0	},
	{	4,	"count", (void*)&count,	0	},
	{	0,	"clear", (void*)clear_variables, 0	},
	{	-1,	"",		(void*)NULL,	0	}
};

