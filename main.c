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
#ifdef ADAU1761_ENABLE
#include "ADAU1761.h"
#endif
#ifdef ADAU1452_ENABLE
#include "ADAU1452.h"
#endif
#ifdef TIMER20_ENABLE
#include "timer20.h"
#endif
#ifdef TIMER21_ENABLE
#include "timer21.h"
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
#include "A31G22x_hal_pwr.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef DEEP_SLEEP_MODE_ENABLE
Bool B_Deep_Sleep = FALSE;
#endif

/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DEBUG_MenuPrint(void);
#ifdef MCU_EVK_FUNCTION_TEST
void MCU_EVK_Function_Test(void);
#endif
#ifdef GPIO_ENABLE
void EXTI_PortA_Configure(void); //KMS24112_6 : External Interrupt Setting for PA0
void GPIO_Configure(void);
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
void DEEP_SLEEP_EXIT_Configure(void);
#endif

void mainloop(void);
int main (void);

/* Private variables ---------------------------------------------------------*/
Bool B_Need_ACC_On = FALSE; //KMS241127_2 : To Update ACC ON state using PA1(Pin45) & PA2(Pin46)
Bool B_Need_ACC_Off = FALSE; //KMS241127_2 : To Update ACC OFF state using PA1(Pin45) & PA2(Pin46)


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

void delay_ms(uint32_t m_ms)
{
	uint32_t i, j;

	for (i=0; i<m_ms; i++)
	{
		for (j=0; j<2070; j++)
		{
			__nop();
		}
	}
}

#ifdef DEEP_SLEEP_MODE_ENABLE
/**********************************************************************
 * @brief		SysTick handler sub-routine (1ms)
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SysTick_Handler_IT (void) 					
{
	/* SysTick Interrupt Handler @ 1000Hz*/
	if(MilliSec)MilliSec--;
}

/**********************************************************************
 * @brief		DEEP_SLEEP_EXIT_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void DEEP_SLEEP_EXIT_Configure(void)
{
	HAL_GPIO_EXTI_Config(PA, 0, PCU_INTERRUPT_MODE_EDGE, PCU_INTERRUPT_CTRL_EDGE_RISING);
	
	HAL_SCU_SetResetSrc(RST_LVDRST, DISABLE);	// LVR Disable (Master)
	
	NVIC_SetPriority(GPIOAB_IRQn, 3);
	NVIC_EnableIRQ(GPIOAB_IRQn);	
	
	HAL_SCU_WakeUpSRCCmd(WAKEUP_GPIOA, ENABLE);
	
	HAL_PWR_AlwaysOnLSIForDeepSleep(LSIAON_ENABLE, BGRAON_ENABLE, VDCAON_ENABLE);
}

/**********************************************************************
 * @brief		PWR_DeepSleepRun
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void PWR_DeepSleepRun(void)
{    
	DEEP_SLEEP_EXIT_Configure();

#ifdef DEEP_SLEEP_MODE_DEBUG_MSG	
	cprintf("Enter Deep Sleep... Connect PA0 pin to High(ACC ON) to exit sleep mode!");
#endif
	// Change Clock to LSI
	HAL_SCU_SystemClockChange(SCCR_LSI);
	
	HAL_SCU_LSE_ClockConfig(DISABLE);
	HAL_SCU_HSI_ClockConfig(DISABLE);
	HAL_SCU_HSE_ClockConfig(DISABLE);
		
	HAL_PWR_EnterDeepSleep();

	//RESET
	//HAL_SCU_SetResetSrc(RST_SWRST, ENABLE);
	//SCU->SCR |= (0x9EB30000|SCU_SCR_SWRST_Msk);

	NVIC_ClearPendingIRQ(GPIOAB_IRQn);

	SystemClock_Config();

	EXTI_PortA_Configure(); //To return original external interrupt setting for PA0 when MCU wake-up in sleep mode.
#ifdef DEEP_SLEEP_MODE_DEBUG_MSG	
	cprintf("\n\rWaked Up from Deep Sleep");
#endif
}
#endif //DEEP_SLEEP_MODE_ENABLE

#ifdef GPIO_ENABLE
/**********************************************************************
 * @brief		Power_Control
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void Power_Control(void) //KMS241127_2 : ACC ON/OFF contorl functtion
{
	if(B_Need_ACC_On) //Need to make PA1/PA2 to High
	{
		B_Need_ACC_On = FALSE;

		HAL_GPIO_SetPin(PA, _BIT(1));
		HAL_GPIO_SetPin(PA, _BIT(2));
	}
	else if(B_Need_ACC_Off) //Need to make PA1/PA2 to Low. But especially PA2 should be 1sec later.
	{		
		B_Need_ACC_Off = FALSE;
#ifdef TIMER20_ENABLE
		TIMER20_Interrupt_Mode_Run(TRUE); //1sec Timer Start for PA2
#endif
		HAL_GPIO_ClearPin(PA, _BIT(1));
	}
	else
	{
		return;
	}
}

/**********************************************************************
 * @brief		GPIOAB_IRQHandler_IT
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void GPIOAB_IRQHandler_IT(void) //KMS24112_6 : External Interrupt Setting for PA0
{
	uint32_t status, clear_bit = 0;
#ifdef GPIO_DEBUG_MSG
	static uint32_t status_bk = 0;
#endif

	status = HAL_GPIO_EXTI_GetState(PA);
	
#ifdef GPIO_DEBUG_MSG
	if(status_bk != status)
	{
		status_bk = status;
		cputs("\n\rstatus : ");
	}
#endif

	if (status & 0x00000003) //External Interrupt is only PA0.
	{
		clear_bit = status & 0x00000003;
		HAL_GPIO_EXTI_ClearPin(PA, status&clear_bit);
		
		if(HAL_GPIO_ReadPin(PA) & _BIT(0)) //PA0
		{
			B_Need_ACC_On = TRUE; //ACC On
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rGPIO High");
#endif
		}
		else
		{
			B_Need_ACC_Off = TRUE; //ACC Off
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rGPIO Low");
#endif
		}
	}
}

/**********************************************************************
 * @brief		EXTI_PortA_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void EXTI_PortA_Configure(void) //KMS24112_6 : External Interrupt Setting for PA0
{	
  	/* external interrupt clock setting*/
	HAL_SCU_MiscClockConfig(4,PD0_TYPE,CLKSRC_LSI,100);

	HAL_GPIO_EXTI_Config(PA, 0, PCU_INTERRUPT_MODE_EDGE, PCU_INTERRUPT_CTRL_EDGE_BOTH);
	
	NVIC_SetPriority(GPIOAB_IRQn, 3);	
	NVIC_EnableIRQ(GPIOAB_IRQn);
}

/**********************************************************************
 * @brief		GPIO_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void GPIO_Configure(void) //KMS241126_3 : Added GPIO configuration function.
{
	//PA0/Pin44(ACC_INT_MICOM) : Input(INT) : Just pass input signal to PA1. High - ACC ON/Low - ACC OFF.
	HAL_GPIO_ConfigOutput(PA, 0, PCU_MODE_INPUT);
	HAL_GPIO_ConfigPullup(PA, 0, PCU_PUPD_PULL_UP);
	HAL_GPIO_SetDebouncePin(PA, 0, ENABLE);
	HAL_GPIO_ClearPin(PA, _BIT(0));	

	//PA1/Pin45(ACC_OUT_MICOM) : Output : This pin is followed by PA0 state
	HAL_GPIO_ConfigOutput(PA, 1, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PB, 1, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PB, _BIT(1));

	//PA2/Pin46(LDO_CNTRL) : Output : This pin is followed by PA1 state but it should work after 1sec when PA1 pin state is changed.
	HAL_GPIO_ConfigOutput(PA, 2, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PB, 2, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PB, _BIT(2));

	//PA3/Pin47(INPUT_CNTRL_OUT) : Output : This pin is followed by PA4 below. - High : Input source A2B / Low : Input Source Aux	
	HAL_GPIO_ConfigOutput(PA, 3, PCU_MODE_OPEN_DRAIN); //Open-Drain
	HAL_GPIO_ConfigPullup(PB, 3, PCU_PUPD_DISABLE); //The schematic has external pull-up & pull-down.
	HAL_GPIO_ClearPin(PB, _BIT(3));

	//PA4/Pin48(INPUT_CNTRL) : Input : Just pass input signal to PA3 and check input just one time. - High : Input source A2B / Low : Input Source Aux
	HAL_GPIO_ConfigOutput(PA, 4, PCU_MODE_INPUT);
	HAL_GPIO_ConfigPullup(PA, 4, PCU_PUPD_PULL_UP);
	HAL_GPIO_SetDebouncePin(PA, 4, ENABLE);
	HAL_GPIO_ClearPin(PA, _BIT(4));
}
#endif

#ifdef MCU_EVK_FUNCTION_TEST
/**********************************************************************
 * @brief		Function Test
 * @param[in]	None
 * @return	None
 **********************************************************************/
 void MCU_EVK_Function_Test(void)
{
#ifdef MCU_EVK_I2C_TEST
	uint8_t uData[2];
#endif

#ifdef MCU_EVK_I2C_TEST //Using ESMT82584F
	uData[0] = 0x12;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(I2C_0, 0x31, 0x1a, &uData[0],1);
	uData[0] = 0x32;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(I2C_0, 0x31, 0x1a, &uData[0],1);
	uData[0] = 0x2e;
	I2C0_Interrupt_Write_Data_8bit_SubAdd(I2C_0, 0x31, 0x03, &uData[0],1);
	uData[0]=0;
	I2C0_Interrupt_Read_Data_8bit_SubAdd(I2C_0, 0x31, 0x1a, &uData[0], 1);
	cprintf("\n\r read[0x03] = 0x%02x",uData[0]);

#ifdef ADAU1452_ENABLE
	I2C1_Interrupt_Read_Data_16bit_SubAdd(0x38, 0xF218, uData, 2);
#endif
#endif //MCU_EVK_I2C_TEST
}
#endif //MCU_EVK_FUNCTION_TEST

/**********************************************************************
 * @brief		Main loop
 * @param[in]	None
 * @return	None
 **********************************************************************/
void mainloop(void)
{	
	/*Configure menu prinf*/
	DEBUG_MenuPrint();

	/*Configure port peripheral*/
#ifdef GPIO_ENABLE
	GPIO_Configure();
#endif

#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE)
	I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave
#endif
#ifdef TIMER20_ENABLE
	TIMER20_Configure();
#endif
#ifdef TIMER21_ENABLE
	TIMER21_Configure();
#endif	
#ifdef GPIO_ENABLE
	EXTI_PortA_Configure();
#endif

	/* Enable IRQ Interrupts */
	__enable_irq();

#ifdef ADAU1452_ENABLE
	ADAU1452_Init(); //DSP Init
#endif
#ifdef ADAU1761_ENABLE
	ADAU1761_Init(); //Audio Codec Init
#endif
#ifdef MCU_EVK_FUNCTION_TEST
	MCU_EVK_Function_Test();
#endif

	while(1) {
		/*User Code start*/
#ifdef GPIO_ENABLE
		Power_Control(); //KMS241127_2 : Power Control is executed here.
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
		if(B_Deep_Sleep == TRUE)
		{
			B_Deep_Sleep = FALSE;
			PWR_DeepSleepRun();
		}
#endif
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
