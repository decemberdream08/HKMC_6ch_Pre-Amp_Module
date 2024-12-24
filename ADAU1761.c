/**********************************************************************
* @file		ADAU1761.c
* @brief	
* @version	1.0
* @date		
* @author	MS Kim
*
* Copyright(C) , ESTec
* All rights reserved.
*
**********************************************************************/

#include "main_conf.h"
#ifdef ADAU1761_ENABLE
#include "i2c.h"
#include "ADAU1761_Init_Reg.h"

//KMS241213_1 //#define DEVICE_ADDR_		(0x39)

#define SIGMA_WRITE_REGISTER_BLOCK(deviceId, subAddr, dataSize, data) \
    I2C_Interrupt_Write_Data_16bit_SubAdd(I2C_1, deviceId, subAddr, data, dataSize) //KMS241211_2

//KMS241202_2 : To reduce RAM size, we need to modify original ADAU1761_init_Reg.h and ADAU1761.c like below.
//1. In ADAU1761_init_Reg.h, we have to change define like the following 
//	#define ADI_REG_TYPE       uint8_t --> #define ADI_REG_TYPE       const uint8_t
//2. In ADAU1761.c, we have to change from MODE_x_x to (uinit 8 *)MODE_x_x.

void ADAU1761_Download_Init_Value(uint8_t DEVICE_ADDR_) //KMS241213_1 : To share ADAU1761 init with each same devices which have jsut different Device Address.
{
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40EB, 1, (uint8_t *)MODE_0_0); 		/* IC 1.Sample Rate Setting */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F6, 1, (uint8_t *)MODE_0_1); 		/* IC 1.DSP Run Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4000, 1, (uint8_t *)MODE_0_2); 		/* IC 1.Clock Control Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4002, 6, (uint8_t *)MODE_0_3); 		/* IC 1.PLL Control Register */
	delay_ms(20);			/* IC 1.IC 1.Delay */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4015, 2, (uint8_t *)MODE_0_5); 		/* IC 1.Serial Port Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4011, 4, (uint8_t *)MODE_0_6); 		/* IC 1.ALC Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4008, 1, (uint8_t *)MODE_0_7); 		/* IC 1.Microphone Control Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4009, 8, (uint8_t *)MODE_0_8); 		/* IC 1.Record Input Signal Path Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4019, 3, (uint8_t *)MODE_0_9); 		/* IC 1.ADC Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x401C, 14, (uint8_t *)MODE_0_10);			/* IC 1.Playback Output Signal Path Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4017, 2, (uint8_t *)MODE_0_11);			/* IC 1.Converter Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x402A, 3, (uint8_t *)MODE_0_12);			/* IC 1.DAC Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x402D, 1, (uint8_t *)MODE_0_13);			/* IC 1.Serial Port Pad Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x402F, 2, (uint8_t *)MODE_0_14);			/* IC 1.Communication Port Pad Control Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4031, 1, (uint8_t *)MODE_0_15);			/* IC 1.Jack Detect Pad Control Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0800, 1020, (uint8_t *)MODE_0_16); 		/* Program Clear Block 0 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x08CC, 1020, (uint8_t *)MODE_0_17); 		/* Program Clear Block 1 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0998, 1020, (uint8_t *)MODE_0_18); 		/* Program Clear Block 2 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0A64, 1020, (uint8_t *)MODE_0_19); 		/* Program Clear Block 3 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0BFC, 15, (uint8_t *)MODE_0_20);			/* Program Clear Block 4 */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F5, 1, (uint8_t *)MODE_0_21);			/* IC 1.DSP ON Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40C0, 5, (uint8_t *)MODE_0_22);			/* IC 1.CRC Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40C6, 4, (uint8_t *)MODE_0_23);			/* IC 1.GPIO Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40E9, 2, (uint8_t *)MODE_0_24);			/* IC 1.Non Modulo Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40D0, 5, (uint8_t *)MODE_0_25);			/* IC 1.Watchdog Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40EB, 1, (uint8_t *)MODE_0_26);			/* IC 1.Sampling Rate Setting Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F2, 1, (uint8_t *)MODE_0_27);			/* IC 1.Routing Matrix Inputs Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F3, 1, (uint8_t *)MODE_0_28);			/* IC 1.Routing Matrix Outputs Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F4, 1, (uint8_t *)MODE_0_29);			/* IC 1.Serial Data Configuration Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F7, 1, (uint8_t *)MODE_0_30);			/* IC 1.DSP Slew Mode Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F8, 1, (uint8_t *)MODE_0_31);			/* IC 1.Serial Port Sample Rate Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F9, 2, (uint8_t *)MODE_0_32);			/* IC 1.Clock Enable Registers */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0800, 815, (uint8_t *)MODE_0_33);			/* Program Data */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x0000, 72, (uint8_t *)MODE_0_34);			/* Param */
//Read : SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4002, 6, (uint8_t *)MODE_0_35);			/* IC 1.PLLCrlRegister */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40EB, 1, (uint8_t *)MODE_0_36);			/* IC 1.Sample Rate Setting */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x40F6, 1, (uint8_t *)MODE_0_37);			/* IC 1.DSP Run Register */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4036, 1, (uint8_t *)MODE_0_38);			/* IC 1.Dejitter Register Control */
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_, 0x4036, 1, (uint8_t *)MODE_0_39);			/* IC 1.Dejitter Register Control */
}

void ADAU1761_Init(void)
{
#ifdef ADAU1761_DEBUG_ENABLE
	cputs("\n\rADAU1761_Init Start~~~");
#endif //ADAU1761_DEBUG_ENABLE

//KMS241213_1
#ifdef MCU_EVK_FUNCTION_TEST
	ADAU1761_Download_Init_Value(0x39);
#else
	ADAU1761_Download_Init_Value(0x38);
	ADAU1761_Download_Init_Value(0x39);
	ADAU1761_Download_Init_Value(0x3A);
	ADAU1761_Download_Init_Value(0x3B);
#endif

#ifdef ADAU1761_DEBUG_ENABLE
	cputs("\n\rADAU1761_Init Done !!!");
#endif //ADAU1761_DEBUG_ENABLE
}

#endif //ADAU1761_ENABLE
