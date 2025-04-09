/*
 * File:           A2B_Master_ADAU1452.h
 *
 * Created:        Tuesday, November 26, 2024 11:00:30 AM
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
/* Includes ------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#include "main_conf.h"
#ifdef ADAU1452_ENABLE
#include "i2c.h"
#include "ADAU1452_Init_Reg.h"

#define DEVICE_ADDR_ADAU1452		(0x38)

#ifdef MCU_EVK_FUNCTION_TEST //KMS241211_2
#define SIGMA_WRITE_REGISTER_BLOCK(deviceId, subAddr, dataSize, data) \
	I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_1, deviceId, subAddr, data, dataSize)
#else
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4 : I2C_0 Switch Control //PE0/Pin32(I2C_SW_CNTL) : Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. 
#define SIGMA_WRITE_REGISTER_BLOCK(deviceId, subAddr, dataSize, data) \
	I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_0_DSP, deviceId, subAddr, data, dataSize)
#else //ESTEC_2ND_BOARD_SUPPORT
#define SIGMA_WRITE_REGISTER_BLOCK(deviceId, subAddr, dataSize, data) \
	I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_0, deviceId, subAddr, data, dataSize)
#endif //ESTEC_2ND_BOARD_SUPPORT
#endif

//KMS241202_1 : To reduce RAM size, we need to modify original ADAU1452_init_Reg.h and ADAU1452.c like below.
//1. In ADAU1452_init_Reg.h, we have to change define like the following 
//	#define ADI_REG_TYPE       uint8_t --> #define ADI_REG_TYPE       const uint8_t
//2. In ADAU1452.c, we have to change from MODE_x_x to (uinit 8 *)MODE_x_x.
#ifdef MCU_EVK_FUNCTION_TEST
void ADAU1452_Download_Init_Value(void)
{
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF890, 2, (uint8_t *)MODE_1_0);			/* IC 1.SOFT_RESET */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF890, 2, (uint8_t *)MODE_1_1);			/* IC 1.SOFT_RESET */
  delay_ms(20);			/* IC 1.IC 1.Reset Delay */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_3);			/* IC 1.HIBERNATE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_4);			/* IC 1.HIBERNATE */
  delay_ms(20);			/* IC 1.IC 1.Hibernate Delay */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_6);			/* IC 1.KILL_CORE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_7);			/* IC 1.KILL_CORE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF003, 2, (uint8_t *)MODE_1_8);			/* IC 1.PLL_ENABLE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF000, 2, (uint8_t *)MODE_1_9);			/* IC 1.PLL_CTRL0 Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF001, 2, (uint8_t *)MODE_1_10);			/* IC 1.PLL_CTRL1 Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF002, 2, (uint8_t *)MODE_1_11);			/* IC 1.PLL_CLK_SRC Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF005, 2, (uint8_t *)MODE_1_12);			/* IC 1.MCLK_OUT Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF003, 2, (uint8_t *)MODE_1_13);			/* IC 1.PLL_ENABLE Register */
  delay_ms(20);			/* IC 1.IC 1.PLL Lock Delay */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF050, 2, (uint8_t *)MODE_1_15);			/* IC 1.POWER_ENABLE0 Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF051, 2, (uint8_t *)MODE_1_16);			/* IC 1.POWER_ENABLE1 Register */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF022, 2, (uint8_t *)MODE_1_17);			/* IC 1.CLK_GEN2_M */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF024, 2, (uint8_t *)MODE_1_18);			/* IC 1.CLK_GEN3_M */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF025, 2, (uint8_t *)MODE_1_19);			/* IC 1.CLK_GEN3_N */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF026, 2, (uint8_t *)MODE_1_20);			/* IC 1.CLK_GEN3_SRC */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF560, 2, (uint8_t *)MODE_1_21);			/* IC 1.DMIC_CTRL0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF561, 2, (uint8_t *)MODE_1_22);			/* IC 1.DMIC_CTRL1 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF511, 2, (uint8_t *)MODE_1_23);			/* IC 1.MP1_MODE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF51A, 2, (uint8_t *)MODE_1_24);			/* IC 1.MP10_MODE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF51D, 2, (uint8_t *)MODE_1_25);			/* IC 1.MP13_MODE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF52D, 2, (uint8_t *)MODE_1_26);			/* IC 1.MP13_WRITE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF798, 2, (uint8_t *)MODE_1_27);			/* IC 1.SPDIF_TX_PIN */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF100, 2, (uint8_t *)MODE_1_28);			/* IC 1.ASRC_INPUT0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF101, 2, (uint8_t *)MODE_1_29);			/* IC 1.ASRC_INPUT1 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF102, 2, (uint8_t *)MODE_1_30);			/* IC 1.ASRC_INPUT2 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF140, 2, (uint8_t *)MODE_1_31);			/* IC 1.ASRC_OUT_RATE0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF141, 2, (uint8_t *)MODE_1_32);			/* IC 1.ASRC_OUT_RATE1 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF142, 2, (uint8_t *)MODE_1_33);			/* IC 1.ASRC_OUT_RATE2 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF180, 2, (uint8_t *)MODE_1_34);			/* IC 1.SOUT_SOURCE0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF181, 2, (uint8_t *)MODE_1_35);			/* IC 1.SOUT_SOURCE1 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF182, 2, (uint8_t *)MODE_1_36);			/* IC 1.SOUT_SOURCE2 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF183, 2, (uint8_t *)MODE_1_37);			/* IC 1.SOUT_SOURCE3 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF184, 2, (uint8_t *)MODE_1_38);			/* IC 1.SOUT_SOURCE4 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF185, 2, (uint8_t *)MODE_1_39);			/* IC 1.SOUT_SOURCE5 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF186, 2, (uint8_t *)MODE_1_40);			/* IC 1.SOUT_SOURCE6 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF187, 2, (uint8_t *)MODE_1_41);			/* IC 1.SOUT_SOURCE7 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF188, 2, (uint8_t *)MODE_1_42);			/* IC 1.SOUT_SOURCE8 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF189, 2, (uint8_t *)MODE_1_43);			/* IC 1.SOUT_SOURCE9 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18A, 2, (uint8_t *)MODE_1_44);			/* IC 1.SOUT_SOURCE10 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18B, 2, (uint8_t *)MODE_1_45);			/* IC 1.SOUT_SOURCE11 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18C, 2, (uint8_t *)MODE_1_46);			/* IC 1.SOUT_SOURCE12 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18D, 2, (uint8_t *)MODE_1_47);			/* IC 1.SOUT_SOURCE13 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18E, 2, (uint8_t *)MODE_1_48);			/* IC 1.SOUT_SOURCE14 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18F, 2, (uint8_t *)MODE_1_49);			/* IC 1.SOUT_SOURCE15 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF190, 2, (uint8_t *)MODE_1_50);			/* IC 1.SOUT_SOURCE16 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF191, 2, (uint8_t *)MODE_1_51);			/* IC 1.SOUT_SOURCE17 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF192, 2, (uint8_t *)MODE_1_52);			/* IC 1.SOUT_SOURCE18 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF193, 2, (uint8_t *)MODE_1_53);			/* IC 1.SOUT_SOURCE19 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF194, 2, (uint8_t *)MODE_1_54);			/* IC 1.SOUT_SOURCE20 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF195, 2, (uint8_t *)MODE_1_55);			/* IC 1.SOUT_SOURCE21 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF196, 2, (uint8_t *)MODE_1_56);			/* IC 1.SOUT_SOURCE22 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF197, 2, (uint8_t *)MODE_1_57);			/* IC 1.SOUT_SOURCE23 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF1C0, 2, (uint8_t *)MODE_1_58);			/* IC 1.SPDIFTX_INPUT */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF200, 2, (uint8_t *)MODE_1_59);			/* IC 1.SERIAL_BYTE_0_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF204, 2, (uint8_t *)MODE_1_60);			/* IC 1.SERIAL_BYTE_1_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF208, 2, (uint8_t *)MODE_1_61);			/* IC 1.SERIAL_BYTE_2_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF20C, 2, (uint8_t *)MODE_1_62);			/* IC 1.SERIAL_BYTE_3_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF210, 2, (uint8_t *)MODE_1_63);			/* IC 1.SERIAL_BYTE_4_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF214, 2, (uint8_t *)MODE_1_64);			/* IC 1.SERIAL_BYTE_5_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF218, 2, (uint8_t *)MODE_1_65);			/* IC 1.SERIAL_BYTE_6_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF21C, 2, (uint8_t *)MODE_1_66);			/* IC 1.SERIAL_BYTE_7_0 */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF604, 2, (uint8_t *)MODE_1_67);			/* IC 1.SPDIF_RESTART */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF690, 2, (uint8_t *)MODE_1_68);			/* IC 1.SPDIF_TX_EN */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xC000, 3956, (uint8_t *)MODE_1_69);			/* Program Data */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0x0000, 1144, (uint8_t *)MODE_1_70);			/* DM0 Data */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0x6038, 832, (uint8_t *)MODE_1_71);			/* DM1 Data */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_72);			/* IC 1.KILL_CORE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF404, 2, (uint8_t *)MODE_1_73);			/* IC 1.START_ADDRESS */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF401, 2, (uint8_t *)MODE_1_74);			/* IC 1.START_PULSE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF402, 2, (uint8_t *)MODE_1_75);			/* IC 1.START_CORE */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF402, 2, (uint8_t *)MODE_1_76);			/* IC 1.START_CORE */
  delay_ms(20);			/* IC 1.IC 1.Start Delay */
  SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_78);			/* IC 1.HIBERNATE */
}

#else //MCU_EVK_FUNCTION_TEST

//KMS241223_2 : the I2S_OUT2 of DSP has not output. So, we changed register setting again.
//KMS241225_1 : Finished Audio path Configuration including L/R position as our spec.
#ifdef ADAU1452_DUMP //KMS250113_1 : Added Dump code for ADAU1452 registers.
void ADAU1452_Register_All_Read(void)
{
	uint8_t Read[2];
	uint16_t sub_address;
	uint32_t i;

#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	I2C_Port_No num = I2C_0_DSP;
#else
	I2C_Port_No num = I2C_0;
#endif
	/* IC 1.SOFT_RESET */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF890+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	delay_ms(20);			/* IC 1.Reset Delay */

	/* IC 1.HIBERNATE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF400+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}

	delay_ms(20);			/* IC 1.Hibernate Delay */
	
	/* IC 1.KILL_CORE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF403+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.PLL_ENABLE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF003+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.PLL_CTRL0 Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF000+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.PLL_CTRL1 Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF001+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.PLL_CLK_SRC Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF002+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MCLK_OUT Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF005+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.PLL_ENABLE Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF003+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	delay_ms(20);			/* IC 1.PLL Lock Delay */
	
	/* IC 1.POWER_ENABLE0 Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF050+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.POWER_ENABLE1 Register */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF051+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.CLK_GEN2_M */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF022+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.CLK_GEN3_M */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF024+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.CLK_GEN3_N */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF025+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.CLK_GEN3_SRC */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF026+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.DMIC_CTRL0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF560+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.DMIC_CTRL1 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF561+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MP0_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF510+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MP1_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF511+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MP6_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF516+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MP7_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF517+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.MP9_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF519+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.MP13_MODE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF51D+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.SPDIF_TX_PIN */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF798+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.ASRC_INPUT0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF100+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.ASRC_INPUT1 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF101+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.ASRC_INPUT2 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF102+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.ASRC_OUT_RATE0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF140+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.ASRC_OUT_RATE1 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF141+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.ASRC_OUT_RATE2 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF142+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF180+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE1 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF181+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.SOUT_SOURCE2 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF182+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.SOUT_SOURCE3 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF183+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
		
	/* IC 1.SOUT_SOURCE4 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF184+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE5 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF185+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE6 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF186+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE7 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF187+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE8 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF188+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE9 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF189+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE10 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18A+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE11 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18B+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE12 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18C+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE13 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18D+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE14 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18E+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE15 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF18F+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE16 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF190+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE17 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF191+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE18 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF192+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE19 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF193+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE20 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF194+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE21 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF195+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE22 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF196+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SOUT_SOURCE23 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF197+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SPDIFTX_INPUT */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF1C0+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_0_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF200+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_1_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF204+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_2_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF208+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_3_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF20C+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_4_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF210+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_5_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF214+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_6_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF185+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SERIAL_BYTE_7_0 */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF21C+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SPDIF_RESTART */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF604+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.SPDIF_TX_EN */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF690+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* Program Data */
	for(i=0;i<310;i++)
	{
		sub_address = 0xC000+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* DM0 Data */
	for(i=0;i<86;i++)
	{
		sub_address = 0x0000+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* DM1 Data */
	for(i=0;i<8;i++)
	{
		sub_address = 0x6010+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.KILL_CORE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF403+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.START_ADDRESS */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF404+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.START_PULSE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF401+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	/* IC 1.START_CORE */
	for(i=0;i<1;i++)
	{
		sub_address = 0xF402+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
	
	delay_ms(20);			/* IC 1.Start Delay */
	
	for(i=0;i<1;i++)
	{
		sub_address = 0xF400+i;
		I2C_Interrupt_Read_Data_16bit_SubAdd(num, DEVICE_ADDR_ADAU1452, sub_address, Read, 2);
		cprintf("\n\rAddress 0x%04x = 0x%02x%02x",sub_address,Read[0],Read[1]);
	}
}
#endif //ADAU1452_DUMP

void ADAU1452_Download_Init_Value(void)
{
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF890, 2, (uint8_t *)MODE_1_0);			/* IC 1.SOFT_RESET */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF890, 2, (uint8_t *)MODE_1_1);			/* IC 1.SOFT_RESET */
	delay_ms(20);			/* IC 1.Reset Delay */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_3);			/* IC 1.HIBERNATE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_4);			/* IC 1.HIBERNATE */
	delay_ms(20);			/* IC 1.Hibernate Delay */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_6);			/* IC 1.KILL_CORE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_7);			/* IC 1.KILL_CORE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF003, 2, (uint8_t *)MODE_1_8);			/* IC 1.PLL_ENABLE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF000, 2, (uint8_t *)MODE_1_9);			/* IC 1.PLL_CTRL0 Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF001, 2, (uint8_t *)MODE_1_10);			/* IC 1.PLL_CTRL1 Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF002, 2, (uint8_t *)MODE_1_11);			/* IC 1.PLL_CLK_SRC Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF005, 2, (uint8_t *)MODE_1_12);			/* IC 1.MCLK_OUT Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF003, 2, (uint8_t *)MODE_1_13);			/* IC 1.PLL_ENABLE Register */
	delay_ms(20);			/* IC 1.PLL Lock Delay */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF050, 2, (uint8_t *)MODE_1_15);			/* IC 1.POWER_ENABLE0 Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF051, 2, (uint8_t *)MODE_1_16);			/* IC 1.POWER_ENABLE1 Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF022, 2, (uint8_t *)MODE_1_17);			/* IC 1.CLK_GEN2_M */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF024, 2, (uint8_t *)MODE_1_18);			/* IC 1.CLK_GEN3_M */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF025, 2, (uint8_t *)MODE_1_19);			/* IC 1.CLK_GEN3_N */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF026, 2, (uint8_t *)MODE_1_20);			/* IC 1.CLK_GEN3_SRC */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF560, 2, (uint8_t *)MODE_1_21);			/* IC 1.DMIC_CTRL0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF561, 2, (uint8_t *)MODE_1_22);			/* IC 1.DMIC_CTRL1 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF510, 2, (uint8_t *)MODE_1_23);			/* IC 1.MP0_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF511, 2, (uint8_t *)MODE_1_24);			/* IC 1.MP1_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF516, 2, (uint8_t *)MODE_1_25);			/* IC 1.MP6_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF517, 2, (uint8_t *)MODE_1_26);			/* IC 1.MP7_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF519, 2, (uint8_t *)MODE_1_27);			/* IC 1.MP9_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF51D, 2, (uint8_t *)MODE_1_28);			/* IC 1.MP13_MODE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF798, 2, (uint8_t *)MODE_1_29);			/* IC 1.SPDIF_TX_PIN */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF100, 2, (uint8_t *)MODE_1_30);			/* IC 1.ASRC_INPUT0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF101, 2, (uint8_t *)MODE_1_31);			/* IC 1.ASRC_INPUT1 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF102, 2, (uint8_t *)MODE_1_32);			/* IC 1.ASRC_INPUT2 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF140, 2, (uint8_t *)MODE_1_33);			/* IC 1.ASRC_OUT_RATE0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF141, 2, (uint8_t *)MODE_1_34);			/* IC 1.ASRC_OUT_RATE1 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF142, 2, (uint8_t *)MODE_1_35);			/* IC 1.ASRC_OUT_RATE2 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF180, 2, (uint8_t *)MODE_1_36);			/* IC 1.SOUT_SOURCE0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF181, 2, (uint8_t *)MODE_1_37);			/* IC 1.SOUT_SOURCE1 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF182, 2, (uint8_t *)MODE_1_38);			/* IC 1.SOUT_SOURCE2 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF183, 2, (uint8_t *)MODE_1_39);			/* IC 1.SOUT_SOURCE3 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF184, 2, (uint8_t *)MODE_1_40);			/* IC 1.SOUT_SOURCE4 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF185, 2, (uint8_t *)MODE_1_41);			/* IC 1.SOUT_SOURCE5 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF186, 2, (uint8_t *)MODE_1_42);			/* IC 1.SOUT_SOURCE6 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF187, 2, (uint8_t *)MODE_1_43);			/* IC 1.SOUT_SOURCE7 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF188, 2, (uint8_t *)MODE_1_44);			/* IC 1.SOUT_SOURCE8 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF189, 2, (uint8_t *)MODE_1_45);			/* IC 1.SOUT_SOURCE9 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18A, 2, (uint8_t *)MODE_1_46);			/* IC 1.SOUT_SOURCE10 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18B, 2, (uint8_t *)MODE_1_47);			/* IC 1.SOUT_SOURCE11 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18C, 2, (uint8_t *)MODE_1_48);			/* IC 1.SOUT_SOURCE12 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18D, 2, (uint8_t *)MODE_1_49);			/* IC 1.SOUT_SOURCE13 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18E, 2, (uint8_t *)MODE_1_50);			/* IC 1.SOUT_SOURCE14 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF18F, 2, (uint8_t *)MODE_1_51);			/* IC 1.SOUT_SOURCE15 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF190, 2, (uint8_t *)MODE_1_52);			/* IC 1.SOUT_SOURCE16 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF191, 2, (uint8_t *)MODE_1_53);			/* IC 1.SOUT_SOURCE17 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF192, 2, (uint8_t *)MODE_1_54);			/* IC 1.SOUT_SOURCE18 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF193, 2, (uint8_t *)MODE_1_55);			/* IC 1.SOUT_SOURCE19 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF194, 2, (uint8_t *)MODE_1_56);			/* IC 1.SOUT_SOURCE20 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF195, 2, (uint8_t *)MODE_1_57);			/* IC 1.SOUT_SOURCE21 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF196, 2, (uint8_t *)MODE_1_58);			/* IC 1.SOUT_SOURCE22 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF197, 2, (uint8_t *)MODE_1_59);			/* IC 1.SOUT_SOURCE23 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF1C0, 2, (uint8_t *)MODE_1_60);			/* IC 1.SPDIFTX_INPUT */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF200, 2, (uint8_t *)MODE_1_61);			/* IC 1.SERIAL_BYTE_0_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF204, 2, (uint8_t *)MODE_1_62);			/* IC 1.SERIAL_BYTE_1_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF208, 2, (uint8_t *)MODE_1_63);			/* IC 1.SERIAL_BYTE_2_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF20C, 2, (uint8_t *)MODE_1_64);			/* IC 1.SERIAL_BYTE_3_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF210, 2, (uint8_t *)MODE_1_65);			/* IC 1.SERIAL_BYTE_4_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF214, 2, (uint8_t *)MODE_1_66);			/* IC 1.SERIAL_BYTE_5_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF218, 2, (uint8_t *)MODE_1_67);			/* IC 1.SERIAL_BYTE_6_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF21C, 2, (uint8_t *)MODE_1_68);			/* IC 1.SERIAL_BYTE_7_0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF604, 2, (uint8_t *)MODE_1_69);			/* IC 1.SPDIF_RESTART */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF690, 2, (uint8_t *)MODE_1_70);			/* IC 1.SPDIF_TX_EN */
	//KMS250403_2 : Added HighPass Filter on Aux mode - 0xC000 ~ 0x6094
	//KMS250409_2 : Added Volume Up setting under A2B Mode - 0xC000 ~ 0x0000
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xC000, 3080, (uint8_t *)MODE_1_71);			/* Program Data */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0x0000, 804, (uint8_t *)MODE_1_72);			/* DM0 Data */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0x6094, 236, (uint8_t *)MODE_1_73);			/* DM1 Data */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF403, 2, (uint8_t *)MODE_1_74);			/* IC 1.KILL_CORE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF404, 2, (uint8_t *)MODE_1_75);			/* IC 1.START_ADDRESS */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF401, 2, (uint8_t *)MODE_1_76);			/* IC 1.START_PULSE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF402, 2, (uint8_t *)MODE_1_77);			/* IC 1.START_CORE */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF402, 2, (uint8_t *)MODE_1_78);			/* IC 1.START_CORE */
	delay_ms(20);			/* IC 1.Start Delay */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_ADAU1452, 0xF400, 2, (uint8_t *)MODE_1_80);			/* IC 1.HIBERNATE */
}

#endif //MCU_EVK_FUNCTION_TEST

void ADAU1452_Init(void)
{
#ifdef ADAU1452_DEBUG_ENABLE
	cputs("\n\rADAU1452_Init Start~~~");
#endif //ADAU1452_DEBUG_ENABLE

	//KMS250109_1 : Added ADAU1452 RESET before MCU Init
	HAL_GPIO_ClearPin(PA, _BIT(5)); //Made PA5 to Low
	delay_ms(1000);
	HAL_GPIO_SetPin(PA, _BIT(5)); //Made PA5 to High
	delay_ms(1000);
	ADAU1452_Download_Init_Value();

#ifdef ADAU1452_DEBUG_ENABLE
	cputs("\n\rADAU1452_Init Done !!!!");
#endif
}

#endif //ADAU1452_ENABLE
