/*
 * File:           Mode 0_Modes.h
 *
 * Created:        Monday, November 25, 2024 3:34:40 PM
 * Description:    adi_a2b_2NodeSampleDemoConfig_Test Sequence data definitions.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright (c) 2024 Analog Devices, Inc. All rights reserved.
 */

#ifndef __ADAU1452_H__
#define __ADAU1452_H__

/*******************************************************************************
* Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/
#define DEVICE_ADDR_ADAU1452		(0x38) //KMS250425_2

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
void ADAU1452_Init(void);
#ifdef ADAU1452_DUMP //KMS250113_1 : Added Dump code for ADAU1452 registers.
void ADAU1452_Register_All_Read(void); //KMS250107_1 : For Debugging
#endif
#endif //__ADAU1452_H__

