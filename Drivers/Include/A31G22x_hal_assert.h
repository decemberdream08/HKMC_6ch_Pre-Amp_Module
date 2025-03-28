/**
 *******************************************************************************
 * @file        A31G22x_hal_assert.h
 * @author      ABOV R&D Division
 * @brief       A31G22x HAL assert file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __A31G22X_HAL_ASSERT_H
#define __A31G22X_HAL_ASSERT_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#ifdef  USE_FULL_ASSERT
/*******************************************************************************************
* @brief                The CHECK_PARAM macro is used for function's parameters check.
*                               It is used only if the library is compiled in DEBUG mode.
* @param	    		expr - If expr is false, it calls check_failed() function
*                       which reports the name of the source file and the source
*                       line number of the call that failed.
*                    - If expr is true, it returns no value.
* @return               None
*******************************************************************************************/
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr) ((void)0U)
#endif 

/****************************************************************************************
* Public Typedef
****************************************************************************************/
 
 
/*******************************************************************************
* Exported Public Function
*******************************************************************************/
#ifdef  USE_FULL_ASSERT
void check_failed(uint8_t *file, uint32_t line);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __A31G22X_HAL_ASSERT_H */


/* --------------------------------- End Of File ------------------------------ */
