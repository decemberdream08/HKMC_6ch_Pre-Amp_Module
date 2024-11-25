/**
 *******************************************************************************
 * @file        main.c
 * @author      ABOV R&D Division
 * @brief       I2C Master Interrupt Example Code tested on A31G22x StarterKit
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "main_conf.h"
#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
#include "i2c.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DEBUG_MenuPrint(void);
void mainloop(void);
int main (void);

/* Private variables ---------------------------------------------------------*/

#ifdef _DEBUG_MSG
static const char Menu[] =
"************************************************\n\r"
"\t - MCU: A31G22x \n\r"
"\t - Core: ARM Cortex-M0+ \n\r"
"\t - Communicate via: USART10 - 38400 bps \n\r"
"\t - I2C Master Interrupt Test \n\r"
"************************************************\n\r";
#endif

/* Public Function ------------------------------------------------------------*/
extern void Main_TestI2CMasterInterrupt(void);

/**********************************************************************
 * @brief		 menu Print
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DEBUG_MenuPrint(void)
{
	#ifdef _DEBUG_MSG
	_DBG(Menu);
	#endif
}

/**********************************************************************
 * @brief		Main loop
 * @param[in]	None
 * @return	None
 **********************************************************************/
void mainloop(void)
{
	uint8_t uData[2];
	
	/*Configure menu prinf*/
	DEBUG_MenuPrint();

	/*Configure port peripheral*/
	//GPIO_Configure(); //To Do List !!!

#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
	I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave
#endif
	/* Enable IRQ Interrupts */
	__enable_irq();

#if 0 //DDD...TES : I2C Test
	uData[0] = 0x12;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(0x31, 0x1a, &uData[0],1);
	uData[0] = 0x32;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(0x31, 0x1a, &uData[0],1);
	uData[0] = 0x2e;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(0x31, 0x03, &uData[0],1);
	uData[0]=0;
	I2C0_Interrupt_Read_Data_8bit_SubAdd(0x31, 0x03, &uData[0], 1);
	cprintf("\n\r read[0x03] = 0x%02x",uData[0]);
#endif
	while(1) {
		/*User Code start*/
	}
}

/**********************************************************************
 * @brief		Main program
 * @param[in]	None
 * @return	None
 **********************************************************************/
int main (void)
{
	 /* Initialize all port */
	Port_Init();  

	/* Configure the system clock to HSE 8 MHz */
	SystemClock_Config();
	
	/* Initialize Debug frame work through initializing UART port  */
    #ifdef _DEBUG_MSG    
    debug_frmwrk_init();
    #endif	
    
	/* Infinite loop */
	mainloop();

	return (0);
}

/* --------------------------------- End Of File ------------------------------ */
