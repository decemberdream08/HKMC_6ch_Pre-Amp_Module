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

#ifndef __ADAU1761_INIT_REG_H__
#define __ADAU1761_INIT_REG_H__

#define ADI_REG_TYPE        uint8_t

ADI_REG_TYPE MODE_0_0[4] = {0x00, 0x00, 0x10, 0x00};
ADI_REG_TYPE MODE_0_1[1] = {0x7F};
ADI_REG_TYPE MODE_0_2[1] = {0x00};
ADI_REG_TYPE MODE_0_3[1] = {0x0F};
ADI_REG_TYPE MODE_0_4[6] = {0x00, 0x01, 0x00, 0x00, 0x20,
 0x03};
ADI_REG_TYPE MODE_0_5[2] = {0x00, 0x64};
ADI_REG_TYPE MODE_0_6[2] = {0x00, 0x00};
ADI_REG_TYPE MODE_0_7[4] = {0x00, 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_8[1] = {0x00};
ADI_REG_TYPE MODE_0_9[8] = {0x00, 0x01, 0x05, 0x01, 0x05,
 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_10[3] = {0x13, 0x00, 0x00};
ADI_REG_TYPE MODE_0_11[14] = {0x21, 0x00, 0x41, 0x00, 0x01,
 0x01, 0x01, 0xE6, 0xE7,
 0xE4, 0xE4, 0xE5, 0x08,
 0x03};
ADI_REG_TYPE MODE_0_12[2] = {0x00, 0x00};
ADI_REG_TYPE MODE_0_13[3] = {0x03, 0x00, 0x00};
ADI_REG_TYPE MODE_0_14[1] = {0xFF};
ADI_REG_TYPE MODE_0_15[2] = {0xA0, 0x00};
ADI_REG_TYPE MODE_0_16[1] = {0x08};
ADI_REG_TYPE MODE_0_17[1020] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_18[1020] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_19[1020] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_20[1020] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_21[15] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00};
ADI_REG_TYPE MODE_0_22[1] = {0x01};
ADI_REG_TYPE MODE_0_23[5] = {0x41, 0x7F, 0x06, 0x7F, 0x01
};
ADI_REG_TYPE MODE_0_24[4] = {0x00, 0x00, 0x00, 0x00};
ADI_REG_TYPE MODE_0_25[2] = {0x10, 0x00};
ADI_REG_TYPE MODE_0_26[5] = {0x00, 0x04, 0x00, 0x00, 0x00
};
ADI_REG_TYPE MODE_0_27[1] = {0x7F};
ADI_REG_TYPE MODE_0_28[1] = {0x00};
ADI_REG_TYPE MODE_0_29[1] = {0x00};
ADI_REG_TYPE MODE_0_30[1] = {0x00};
ADI_REG_TYPE MODE_0_31[1] = {0x00};
ADI_REG_TYPE MODE_0_32[1] = {0x00};
ADI_REG_TYPE MODE_0_33[2] = {0x7F, 0x03};
ADI_REG_TYPE MODE_0_34[1730] = {0x00, 0x00, 0x00, 0x00, 0x00,
 0xFE, 0xE0, 0x00, 0x00,
 0x00, 0xFF, 0x34, 0x00,
 0x00, 0x00, 0xFF, 0x2C,
 0x00, 0x00, 0x00, 0xFF,
 0x54, 0x00, 0x00, 0x00,
 0xFF, 0x5C, 0x00, 0x00,
 0x00, 0xFF, 0xF5, 0x08,
 0x20, 0x00, 0xFF, 0x38,
 0x00, 0x00, 0x00, 0xFF,
 0x80, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFE, 0xE8,
 0x0C, 0x00, 0x00, 0xFE,
 0x30, 0x00, 0xE2, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xE8,
 0x07, 0x20, 0x08, 0x00,
 0x00, 0x06, 0xA0, 0x00,
 0xFF, 0xE0, 0x00, 0xC0,
 0x00, 0xFF, 0x80, 0x07,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0x00,
 0xFE, 0xC0, 0x22, 0x00,
 0x27, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFE, 0xE8,
 0x1E, 0x00, 0x00, 0xFF,
 0xE8, 0x01, 0x20, 0x00,
 0xFF, 0xD8, 0x01, 0x03,
 0x00, 0x00, 0x07, 0xC6,
 0x00, 0x00, 0xFF, 0x08,
 0x00, 0x00, 0x00, 0xFF,
 0xF4, 0x00, 0x20, 0x00,
 0xFF, 0xD8, 0x07, 0x02,
 0x00, 0xFD, 0xA5, 0x08,
 0x20, 0x00, 0x00, 0x00,
 0x00, 0xE2, 0x00, 0xFD,
 0xAD, 0x08, 0x20, 0x00,
 0x00, 0x08, 0x00, 0xE2,
 0x00, 0xFD, 0x25, 0x08,
 0x20, 0x00, 0x00, 0x10,
 0x00, 0xE2, 0x00, 0xFD,
 0x2D, 0x08, 0x20, 0x00,
 0x00, 0x18, 0x00, 0xE2,
 0x00, 0xFF, 0xE8, 0x08,
 0x20, 0x00, 0x00, 0x20,
 0x00, 0xE2, 0x00, 0x00,
 0x45, 0x1F, 0x20, 0x00,
 0x00, 0x35, 0x08, 0x22,
 0x00, 0x00, 0x00, 0x0A,
 0xA0, 0x00, 0xFF, 0xE5,
 0x18, 0x22, 0x00, 0x00,
 0x00, 0x09, 0xA0, 0x00,
 0x00, 0x38, 0x00, 0xEA,
 0x00, 0x00, 0x48, 0x00,
 0xF2, 0x00, 0x00, 0x38,
 0x00, 0xC0, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0xFF, 0xEC, 0x01,
 0x21, 0x00, 0x00, 0x04,
 0x00, 0xA1, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0xFF, 0xE5, 0x08, 0x22,
 0x40, 0x00, 0x50, 0x00,
 0xE2, 0x00, 0x00, 0x48,
 0x00, 0xC0, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x57, 0xFF, 0x20,
 0x00, 0xFF, 0xE5, 0x08,
 0x22, 0x00, 0x00, 0x58,
 0x00, 0xE2, 0x00, 0x00,
 0x58, 0x0B, 0x20, 0x00,
 0x00, 0x28, 0x00, 0xE2,
 0x00, 0x00, 0x85, 0x1F,
 0x20, 0x00, 0x00, 0x75,
 0x08, 0x22, 0x00, 0x00,
 0x00, 0x0D, 0xA0, 0x00,
 0xFF, 0xE5, 0x18, 0x22,
 0x00, 0x00, 0x00, 0x0C,
 0xA0, 0x00, 0x00, 0x78,
 0x00, 0xEA, 0x00, 0x00,
 0x88, 0x00, 0xF2, 0x00,
 0x00, 0x78, 0x00, 0xC0,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xFF,
 0xEC, 0x01, 0x21, 0x00,
 0x00, 0x04, 0x00, 0xA1,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xE5,
 0x08, 0x22, 0x40, 0x00,
 0x50, 0x00, 0xE2, 0x00,
 0x00, 0x88, 0x00, 0xC0,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x57,
 0xFF, 0x20, 0x00, 0xFF,
 0xE5, 0x08, 0x22, 0x00,
 0x00, 0x58, 0x00, 0xE2,
 0x00, 0x00, 0x58, 0x0E,
 0x20, 0x00, 0x00, 0x68,
 0x00, 0xE2, 0x00, 0x00,
 0x25, 0x08, 0x20, 0x00,
 0xFF, 0xD8, 0x0F, 0x02,
 0x00, 0x00, 0x90, 0x00,
 0xE2, 0x00, 0xFF, 0xE8,
 0x10, 0x20, 0x00, 0x00,
 0xE0, 0x00, 0xE2, 0x00,
 0x00, 0x6D, 0x08, 0x20,
 0x00, 0x00, 0xA8, 0x00,
 0xE2, 0x00, 0x00, 0x6D,
 0x08, 0x20, 0x00, 0x00,
 0xC0, 0x00, 0xE2, 0x00,
 0x00, 0x05, 0x08, 0x20,
 0x00, 0x00, 0xB0, 0x00,
 0xE2, 0x00, 0x00, 0x0D,
 0x08, 0x20, 0x00, 0x00,
 0xC8, 0x00, 0xE2, 0x00,
 0x00, 0x15, 0x08, 0x20,
 0x00, 0x00, 0xB8, 0x00,
 0xE2, 0x00, 0x00, 0x1D,
 0x08, 0x20, 0x00, 0x00,
 0xD0, 0x00, 0xE2, 0x00,
 0xFF, 0xF5, 0x08, 0x20,
 0x00, 0x01, 0x38, 0x00,
 0xE2, 0x00, 0x00, 0xDD,
 0x08, 0x20, 0x00, 0x00,
 0xE5, 0x08, 0x22, 0x48,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0xFF, 0xED, 0x08,
 0x20, 0x26, 0x01, 0x38,
 0x00, 0xE2, 0x00, 0x00,
 0xFD, 0x08, 0x20, 0x00,
 0xFF, 0xED, 0x13, 0x22,
 0x48, 0x00, 0xDD, 0x08,
 0x20, 0x00, 0x01, 0x1D,
 0x08, 0x20, 0x25, 0x01,
 0x20, 0x00, 0xE2, 0x00,
 0x01, 0x0D, 0x08, 0x20,
 0x00, 0xFF, 0xED, 0x13,
 0x22, 0x48, 0x00, 0xDD,
 0x08, 0x20, 0x00, 0x01,
 0x2D, 0x08, 0x20, 0x25,
 0x01, 0x30, 0x00, 0xE2,
 0x00, 0x01, 0x45, 0x08,
 0x20, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x01,
 0x50, 0x00, 0xF0, 0x00,
 0x01, 0x55, 0x08, 0x20,
 0x00, 0xFF, 0xED, 0x13,
 0x22, 0x48, 0x01, 0x3D,
 0x08, 0x20, 0x00, 0xFF,
 0xF5, 0x08, 0x20, 0x25,
 0x01, 0x38, 0x00, 0xE2,
 0x00, 0x00, 0xDD, 0x08,
 0x20, 0x00, 0x00, 0xE0,
 0x00, 0xE2, 0x25, 0x00,
 0xED, 0x08, 0x20, 0x00,
 0x00, 0xFD, 0x08, 0x22,
 0x40, 0x01, 0x48, 0x00,
 0xE2, 0x00, 0x00, 0xFD,
 0x08, 0x20, 0x00, 0x01,
 0x4D, 0x14, 0x22, 0x00,
 0x01, 0x00, 0x00, 0xE2,
 0x00, 0x01, 0x20, 0x00,
 0xC0, 0x00, 0x00, 0x07,
 0xFF, 0xA0, 0x00, 0x01,
 0x00, 0x00, 0xC0, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xAF, 0xFF,
 0x20, 0x80, 0x00, 0x98,
 0x00, 0xE2, 0x00, 0x00,
 0xC7, 0xFF, 0x40, 0x80,
 0x00, 0xA0, 0x00, 0xE4,
 0x00, 0xFF, 0xED, 0x08,
 0x20, 0x00, 0xFF, 0xEF,
 0xFF, 0x22, 0x40, 0x01,
 0x10, 0x00, 0xE2, 0x00,
 0x01, 0x30, 0x00, 0xC0,
 0x00, 0x00, 0x07, 0xFF,
 0xA0, 0x00, 0x01, 0x10,
 0x00, 0xC0, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0xAF, 0xFF, 0x20,
 0x80, 0x00, 0x9D, 0x08,
 0x22, 0x00, 0x00, 0x98,
 0x00, 0xE2, 0x00, 0x00,
 0xC7, 0xFF, 0x40, 0x80,
 0x00, 0xA5, 0x08, 0x44,
 0x00, 0x00, 0xA0, 0x00,
 0xE4, 0x00, 0x00, 0xED,
 0x08, 0x20, 0x00, 0x01,
 0x3D, 0x08, 0x22, 0x40,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xF0, 0x00,
 0xF0, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x01,
 0x7D, 0x08, 0x20, 0x00,
 0xFF, 0xE8, 0x12, 0x34,
 0x00, 0x01, 0x6D, 0x08,
 0x22, 0x48, 0x01, 0x78,
 0x11, 0x20, 0x40, 0x01,
 0x68, 0x11, 0x34, 0x40,
 0x01, 0x78, 0x11, 0x20,
 0x25, 0x01, 0x68, 0x11,
 0x34, 0x25, 0x01, 0x90,
 0x00, 0xE2, 0x00, 0x01,
 0x88, 0x00, 0xF2, 0x00,
 0x01, 0x7D, 0x08, 0x20,
 0x00, 0x01, 0x8D, 0x08,
 0x22, 0x00, 0x01, 0x6D,
 0x08, 0x34, 0x00, 0x01,
 0x95, 0x08, 0x22, 0x00,
 0x01, 0x70, 0x00, 0xE2,
 0x00, 0x01, 0x80, 0x00,
 0xF2, 0x00, 0x01, 0x75,
 0x08, 0x20, 0x08, 0xFF,
 0xED, 0x1F, 0x20, 0x00,
 0x01, 0x75, 0x08, 0x20,
 0x25, 0x01, 0x70, 0x00,
 0xE2, 0x00, 0xFF, 0xED,
 0x1F, 0x22, 0x40, 0x01,
 0xA0, 0x00, 0xE2, 0x00,
 0x01, 0x75, 0x08, 0x20,
 0x00, 0xFF, 0xE8, 0x12,
 0x22, 0x40, 0x01, 0x70,
 0x11, 0x30, 0x48, 0x01,
 0xA5, 0x08, 0x20, 0x00,
 0xFF, 0xE8, 0x12, 0x20,
 0x27, 0x01, 0xA0, 0x00,
 0xE2, 0x00, 0x01, 0xA0,
 0x00, 0xC0, 0x00, 0x00,
 0x17, 0xFF, 0x20, 0x00,
 0x01, 0x58, 0x00, 0xE2,
 0x00, 0x00, 0x1F, 0xFF,
 0x20, 0x00, 0x01, 0x60,
 0x00, 0xE2, 0x00, 0xFF,
 0xE8, 0x13, 0x20, 0x00,
 0x01, 0xF0, 0x00, 0xE2,
 0x00, 0x00, 0x05, 0x08,
 0x20, 0x00, 0x01, 0xB8,
 0x00, 0xE2, 0x00, 0x00,
 0x0D, 0x08, 0x20, 0x00,
 0x01, 0xD0, 0x00, 0xE2,
 0x00, 0x01, 0x5D, 0x08,
 0x20, 0x00, 0x01, 0xC0,
 0x00, 0xE2, 0x00, 0x01,
 0x65, 0x08, 0x20, 0x00,
 0x01, 0xD8, 0x00, 0xE2,
 0x00, 0x00, 0x2D, 0x08,
 0x20, 0x00, 0x01, 0xC8,
 0x00, 0xE2, 0x00, 0x00,
 0x2D, 0x08, 0x20, 0x00,
 0x01, 0xE0, 0x00, 0xE2,
 0x00, 0xFF, 0xF5, 0x08,
 0x20, 0x00, 0x02, 0x48,
 0x00, 0xE2, 0x00, 0x01,
 0xED, 0x08, 0x20, 0x00,
 0x01, 0xF5, 0x08, 0x22,
 0x48, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xED,
 0x08, 0x20, 0x26, 0x02,
 0x48, 0x00, 0xE2, 0x00,
 0x02, 0x0D, 0x08, 0x20,
 0x00, 0xFF, 0xED, 0x13,
 0x22, 0x48, 0x01, 0xED,
 0x08, 0x20, 0x00, 0x02,
 0x2D, 0x08, 0x20, 0x25,
 0x02, 0x30, 0x00, 0xE2,
 0x00, 0x02, 0x1D, 0x08,
 0x20, 0x00, 0xFF, 0xED,
 0x13, 0x22, 0x48, 0x01,
 0xED, 0x08, 0x20, 0x00,
 0x02, 0x3D, 0x08, 0x20,
 0x25, 0x02, 0x40, 0x00,
 0xE2, 0x00, 0x02, 0x55,
 0x08, 0x20, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x02, 0x60, 0x00, 0xF0,
 0x00, 0x02, 0x65, 0x08,
 0x20, 0x00, 0xFF, 0xED,
 0x13, 0x22, 0x48, 0x02,
 0x4D, 0x08, 0x20, 0x00,
 0xFF, 0xF5, 0x08, 0x20,
 0x25, 0x02, 0x48, 0x00,
 0xE2, 0x00, 0x01, 0xED,
 0x08, 0x20, 0x00, 0x01,
 0xF0, 0x00, 0xE2, 0x25,
 0x01, 0xFD, 0x08, 0x20,
 0x00, 0x02, 0x0D, 0x08,
 0x22, 0x40, 0x02, 0x58,
 0x00, 0xE2, 0x00, 0x02,
 0x0D, 0x08, 0x20, 0x00,
 0x02, 0x5D, 0x14, 0x22,
 0x00, 0x02, 0x10, 0x00,
 0xE2, 0x00, 0x02, 0x30,
 0x00, 0xC0, 0x00, 0x00,
 0x07, 0xFF, 0xA0, 0x00,
 0x02, 0x10, 0x00, 0xC0,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x01, 0xBF,
 0xFF, 0x20, 0x80, 0x01,
 0xA8, 0x00, 0xE2, 0x00,
 0x01, 0xD7, 0xFF, 0x40,
 0x80, 0x01, 0xB0, 0x00,
 0xE4, 0x00, 0xFF, 0xED,
 0x08, 0x20, 0x00, 0xFF,
 0xEF, 0xFF, 0x22, 0x40,
 0x02, 0x20, 0x00, 0xE2,
 0x00, 0x02, 0x40, 0x00,
 0xC0, 0x00, 0x00, 0x07,
 0xFF, 0xA0, 0x00, 0x02,
 0x20, 0x00, 0xC0, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x01, 0xBF, 0xFF,
 0x20, 0x80, 0x01, 0xAD,
 0x08, 0x22, 0x00, 0x01,
 0xA8, 0x00, 0xE2, 0x00,
 0x01, 0xD7, 0xFF, 0x40,
 0x80, 0x01, 0xB5, 0x08,
 0x44, 0x00, 0x01, 0xB0,
 0x00, 0xE4, 0x00, 0x01,
 0xFD, 0x08, 0x20, 0x00,
 0x02, 0x4D, 0x08, 0x22,
 0x40, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x02, 0x00,
 0x00, 0xF0, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x02, 0x8D, 0x08, 0x20,
 0x00, 0xFF, 0xE8, 0x15,
 0x34, 0x00, 0x02, 0x7D,
 0x08, 0x22, 0x48, 0x02,
 0x88, 0x14, 0x20, 0x40,
 0x02, 0x78, 0x14, 0x34,
 0x40, 0x02, 0x88, 0x14,
 0x20, 0x25, 0x02, 0x78,
 0x14, 0x34, 0x25, 0x02,
 0xA0, 0x00, 0xE2, 0x00,
 0x02, 0x98, 0x00, 0xF2,
 0x00, 0x02, 0x8D, 0x08,
 0x20, 0x00, 0x02, 0x9D,
 0x08, 0x22, 0x00, 0x02,
 0x7D, 0x08, 0x34, 0x00,
 0x02, 0xA5, 0x08, 0x22,
 0x00, 0x02, 0x80, 0x00,
 0xE2, 0x00, 0x02, 0x90,
 0x00, 0xF2, 0x00, 0x02,
 0x85, 0x08, 0x20, 0x08,
 0xFF, 0xED, 0x1F, 0x20,
 0x00, 0x02, 0x85, 0x08,
 0x20, 0x25, 0x02, 0x80,
 0x00, 0xE2, 0x00, 0xFF,
 0xED, 0x1F, 0x22, 0x40,
 0x02, 0xB0, 0x00, 0xE2,
 0x00, 0x02, 0x85, 0x08,
 0x20, 0x00, 0xFF, 0xE8,
 0x15, 0x22, 0x40, 0x02,
 0x80, 0x14, 0x30, 0x48,
 0x02, 0xB5, 0x08, 0x20,
 0x00, 0xFF, 0xE8, 0x15,
 0x20, 0x27, 0x02, 0xB0,
 0x00, 0xE2, 0x00, 0x02,
 0xB0, 0x00, 0xC0, 0x00,
 0x00, 0x9F, 0xFF, 0x20,
 0x00, 0x02, 0x68, 0x00,
 0xE2, 0x00, 0x00, 0xA7,
 0xFF, 0x20, 0x00, 0x02,
 0x70, 0x00, 0xE2, 0x00,
 0x02, 0xDD, 0x08, 0x20,
 0x00, 0xFF, 0xE8, 0x17,
 0x34, 0x00, 0x02, 0xCD,
 0x08, 0x22, 0x48, 0x02,
 0xD8, 0x16, 0x20, 0x40,
 0x02, 0xC8, 0x16, 0x34,
 0x40, 0x02, 0xD8, 0x16,
 0x20, 0x25, 0x02, 0xC8,
 0x16, 0x34, 0x25, 0x02,
 0xF0, 0x00, 0xE2, 0x00,
 0x02, 0xE8, 0x00, 0xF2,
 0x00, 0x02, 0xDD, 0x08,
 0x20, 0x00, 0x02, 0xED,
 0x08, 0x22, 0x00, 0x02,
 0xCD, 0x08, 0x34, 0x00,
 0x02, 0xF5, 0x08, 0x22,
 0x00, 0x02, 0xD0, 0x00,
 0xE2, 0x00, 0x02, 0xE0,
 0x00, 0xF2, 0x00, 0x02,
 0xD5, 0x08, 0x20, 0x08,
 0xFF, 0xED, 0x1F, 0x20,
 0x00, 0x02, 0xD5, 0x08,
 0x20, 0x25, 0x02, 0xD0,
 0x00, 0xE2, 0x00, 0xFF,
 0xED, 0x1F, 0x22, 0x40,
 0x03, 0x00, 0x00, 0xE2,
 0x00, 0x02, 0xD5, 0x08,
 0x20, 0x00, 0xFF, 0xE8,
 0x17, 0x22, 0x40, 0x02,
 0xD0, 0x16, 0x30, 0x48,
 0x03, 0x05, 0x08, 0x20,
 0x00, 0xFF, 0xE8, 0x17,
 0x20, 0x27, 0x03, 0x00,
 0x00, 0xE2, 0x00, 0x03,
 0x00, 0x00, 0xC0, 0x00,
 0x01, 0xAF, 0xFF, 0x20,
 0x00, 0x02, 0xB8, 0x00,
 0xE2, 0x00, 0x01, 0xB7,
 0xFF, 0x20, 0x00, 0x02,
 0xC0, 0x00, 0xE2, 0x00,
 0x02, 0x6D, 0x08, 0x20,
 0x00, 0xFD, 0x60, 0x00,
 0xE2, 0x00, 0x02, 0x75,
 0x08, 0x20, 0x00, 0xFD,
 0x68, 0x00, 0xE2, 0x00,
 0x02, 0xC5, 0x08, 0x20,
 0x00, 0xFD, 0xB8, 0x00,
 0xE2, 0x00, 0x02, 0xBD,
 0x08, 0x20, 0x00, 0xFD,
 0xB0, 0x00, 0xE2, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0xFE, 0x30, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xFE,
 0xC0, 0x0F, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00};
ADI_REG_TYPE MODE_0_35[96] = {0x00, 0x00, 0x10, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x02,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0x00,
 0x02, 0x22, 0x26, 0x00,
 0x80, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0x00,
 0x02, 0x22, 0x26, 0x00,
 0x80, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x01, 0x00,
 0x00, 0x10, 0x00, 0x00,
 0x80, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x01, 0x00,
 0x00, 0x10, 0x00, 0x00,
 0x80, 0x00, 0x00, 0x00,
 0x00, 0x10, 0x00, 0x00,
 0x80, 0x00, 0x00};
ADI_REG_TYPE MODE_0_36[1] = {0x01};
ADI_REG_TYPE MODE_0_37[1] = {0x01};
ADI_REG_TYPE MODE_0_38[1] = {0x00};
ADI_REG_TYPE MODE_0_39[1] = {0x03};

#endif //__ADAU1761_INIT_REG_H__
