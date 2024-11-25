/**
 *******************************************************************************
 * @file        A31G22x_hal_cfmc_SelfWriteErase.h
 * @author      ABOV R&D Division
 * @brief       Contains all macro definitions and function prototypes support
 *              for CFMC(Code Flash Main Controller) driver on A31G22x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _A31G22x_HAL_CFMC_SELFWRITEERASE_H_
#define _A31G22x_HAL_CFMC_SELFWRITEERASE_H_

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

/*******************************************************************************
* Exported Public Function
*******************************************************************************/


int HAL_CFMC_SelfWrite (unsigned long addr, unsigned long size, unsigned char *buf);
int HAL_CFMC_SelfErase (unsigned long addr, unsigned long size);

#ifdef __cplusplus
}
#endif

#endif /* _A31G22x_DFMC_H_ */
/* --------------------------------- End Of File ------------------------------ */
