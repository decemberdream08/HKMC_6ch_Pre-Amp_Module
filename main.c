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
#ifdef DEEP_SLEEP_MODE_ENABLE
#include "A31G22x_hal_pwr.h"
#endif
#ifdef ESTEC_A2B_STACK_PORTING
#include "a2bapp.h"
#endif
#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT)
#include "timer21.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(ESTEC_A2B_STACK_PORTING) || defined(SYSTICK_TIMER_ENABLE)
uint32_t MilliSec = 0;
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
Bool B_Deep_Sleep = FALSE;
#endif
#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT) //KMS250228_3
Bool B_Mute_TimerOn = FALSE;
#endif
#ifdef ESTEC_A2B_STACK_PORTING
a2b_App_t gApp_Info;
#endif

#ifdef SYSTICK_TIMER_ENABLE
static uint32_t SysTick_1ms_count = 0, SysTick_100ms_count = 0, SysTick_500ms_count = 0, SysTick_1s_count = 0;
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT
#ifdef ESTEC_A2B_STACK_PORTING
a2b_UInt32 nResult = 0;
#endif
Bool B_A2B_Master_Support = FALSE; //KMS250227_2 : To enable A2B Master Mode
#endif

/* Private define ------------------------------------------------------------*/
typedef enum {
	INPUT_MODE_A2B,
	INPUT_MODE_AUX
} INPUT_MODE;

typedef enum {
	MUTE_OFF_STATE,
	MUTE_ON_STATE
} MUTE_STATE;

/* Private function prototypes -----------------------------------------------*/
void DEBUG_MenuPrint(void);
#ifdef MCU_EVK_FUNCTION_TEST
void MCU_EVK_Function_Test(void);
#endif
#ifdef GPIO_ENABLE
#ifdef ESTEC_2ND_BOARD_SUPPORT
Bool A2B_Direct_State(void); //KMS250227_2 : //PA6/Pin2(A2B_DIRECT) - High : A2B Master feature disable / Low : A2B Master feature enable
void Mute_Relay_Control(MUTE_STATE B_Mute_On); //KMS250228_3 : Mute On/Off function.
#endif
INPUT_MODE Input_Source_State(void); //KMS241213_2 : Added new function to check current input source whether A2B or Aux
void Input_Source_Control(INPUT_MODE B_A2B_Mode); //KMS241213_2 : To inform current mode(A2B or Aux) to DSP using PA3

Bool ACC_On_State(void); //KMS241129_1 : ACC ON/OFF status check functtion
void EXTI_PortA_Configure(void); //KMS24112_6 : External Interrupt Setting for PA0
void GPIO_Configure(void);
void Power_Control(void); //KMS241127_2 : ACC ON/OFF contorl functtion
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
void DEEP_SLEEP_EXIT_Configure(void);
#endif
#ifdef SYSTICK_TIMER_ENABLE
void SysTick_Configure(void);
#endif
#ifdef ESTEC_2ND_BOARD_SUPPORT
void Init_Board(void);
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
"\t - 2025/03/18 - PM \n\r"
"************************************************\n\r";
#endif

/* Public Function ------------------------------------------------------------*/
extern void Main_TestI2CMasterInterrupt(void);

#ifdef ESTEC_2ND_BOARD_SUPPORT
void Init_Board(void)
{
#ifdef GPIO_DEBUG_MSG
	cputs("\n\rACC_ON is detected on MCU restart");
#endif
	B_Need_ACC_On = TRUE;

	
#ifdef GPIO_ENABLE //KMS241219_1 : Need to move here because power should be supplied before DSP/Audio Codec init.
	Power_Control(); //KMS241127_2 : Power Control is executed here.
#endif
/*
	}
#endif */ //KMS250228_1 : During Power-On, we don't need to initialize all peripherals. So, this statement is moved below.
#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE) //KMS241224_1 : I2C I/F Init is moved after Power_Control() due to DSP Init problem and added delay 500ms.
	delay_ms(1000); //Tested with 3sec delay
	//NTA : MCLK SW CNTR Pin Control
#ifdef MCU_RESET_AFTER_WAKE_UP
	if(ACC_On_State() == TRUE)

#endif

	delay_ms(500); //KMS250106_1 : Changed timing from 100ms to 500ms due to ADAU1452 Init failure.
#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4		
	I2C_Configure(I2C_0_DSP, I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
	//I2C_Configure(I2C_1, I2C_SPEED_400K, SLAVE);
#else
	I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
#endif
#endif

#ifdef GPIO_ENABLE //KMS241213_2
	//KMS241213_3 : Just check one time upon power on if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is defined but it checks current status with intterrupt and upon Power On if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is not defined
	if(Input_Source_State() == INPUT_MODE_A2B)
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rInput Source is A2B Mode upon Power On !!!");
#endif
		Input_Source_Control(INPUT_MODE_A2B); //KMS241223_1 : Changed sending data state for DSP.
	}
	else
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rInput Source is Aux Mode upon Power On !!!");
#endif
		Input_Source_Control(INPUT_MODE_AUX); //KMS241223_1 : Changed sending data state for DSP.
	}
#endif //GPIO_ENABLE

//KMS241219_1
#ifdef ADAU1452_ENABLE
	ADAU1452_Init(); //DSP Init
#endif
#ifdef ADAU1761_ENABLE
	ADAU1761_Init(); //Audio Codec Init
#endif
#ifdef MCU_EVK_FUNCTION_TEST
	MCU_EVK_Function_Test();
#endif

#ifdef ESTEC_A2B_STACK_PORTING
	/* system/platform specific initialization */
	//nResult = adi_a2b_SystemInit();
	
	if(nResult != 0)
	{
		//assert(nResult == 0);
	}

	/* A2B Network Setup. Performs discovery and configuration of A2B nodes and its peripherals */
#ifndef A2B_SLAVE_EXTENSION_SUPPORT_TEST
#ifdef ESTEC_2ND_BOARD_SUPPORT
	if (A2B_Direct_State() == FALSE) //KMS250227_2 : //PA6/Pin2(A2B_DIRECT) - High : A2B Master feature disable / Low : A2B Master feature enable
	{
#ifdef _DEBUG_MSG
		cputs("\n\rA2B_Master_Support !!!");
#endif
		B_A2B_Master_Support = TRUE;
		nResult = a2b_setup(&gApp_Info);
	}
	else
	{
#ifdef _DEBUG_MSG
		cputs("\n\rA2B_Master_No_Support !!!");
#endif
		B_A2B_Master_Support = FALSE;
	}
#else //ESTEC_2ND_BOARD_SUPPORT
	nResult = a2b_setup(&gApp_Info);
#endif //ESTEC_2ND_BOARD_SUPPORT
#endif //A2B_SLAVE_EXTENSION_SUPPORT_TEST
	if (nResult)
	{
		/* failed to setup A2B network */
		//assert(nResult == 0);
	}
#endif

#ifdef _DEBUG_MSG
	cputs("\n\rInit Done !!!");
#endif
#if defined(ESTEC_2ND_BOARD_SUPPORT) && defined(TIMER21_ENABLE)
	TIMER21_Interrupt_Mode_Run(TRUE); //KMS250228_3 : Mute Off execution after 1 sec using timer.
#endif
}
#endif

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

#ifdef SYSTICK_TIMER_ENABLE
/**********************************************************************
 * @brief		SysTick handler sub-routine (1ms)
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SysTick_Handler_IT (void) 					
{
	/* SysTick Interrupt Handler @ 1000Hz*/
	MilliSec++;

	if(!(SysTick_1ms_count % 100))
	{
		if(!(SysTick_100ms_count%5))
		{
			if(SysTick_500ms_count%2)
			{
				SysTick_1s_count++;
#ifdef SYSTICK_DEBUG_MSG
				cprintf("\n\rSysTick_1s_count = %d\r\n",SysTick_1s_count);
#endif
			}

			SysTick_500ms_count++;
		}

		SysTick_100ms_count++;
	}
	
	SysTick_1ms_count++;
}

/**********************************************************************
 * @brief		SysTick_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void SysTick_Configure(void)
{
	/*1MilliSec interrupt */
	SysTick_Config(SystemCoreClock/1000);
	
}
#endif

#ifdef DEEP_SLEEP_MODE_ENABLE
/**********************************************************************
 * @brief		DEEP_SLEEP_EXIT_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void DEEP_SLEEP_EXIT_Configure(void)
{
#ifdef DEEP_SLEEP_LOWEST_POWER_CONSUMPTION
	uint32_t Reg = 0;
#endif

	HAL_GPIO_EXTI_Config(PA, 0, PCU_INTERRUPT_MODE_EDGE, PCU_INTERRUPT_CTRL_EDGE_RISING);
	
	HAL_SCU_SetResetSrc(RST_LVDRST, DISABLE); //Disable RESET source especially LVRRST = 0/Disable (Master). 1st action of LVD = OFF.

#ifdef DEEP_SLEEP_LOWEST_POWER_CONSUMPTION
    SCULV->LVRCR = 0x55; //Disable LVR Block(Disable Low Voltage Reset). 2nd action of LVD = OFF.
    Reg = SCULV->LVICR;
    SCULV->LVICR = Reg & (~SCULV_LVICR_LVIEN_ENABLE); //Disable LVI Block(Disable low voltage indicator). 3rd(the last) action of LVD = OFF.
#endif

	NVIC_SetPriority(GPIOAB_IRQn, 3);
	NVIC_EnableIRQ(GPIOAB_IRQn);	
	
	HAL_SCU_WakeUpSRCCmd(WAKEUP_GPIOA, ENABLE);

#ifdef DEEP_SLEEP_LOWEST_POWER_CONSUMPTION
	HAL_PWR_AlwaysOnLSIForDeepSleep(LSIAON_DISABLE, BGRAON_DISABLE, VDCAON_DISABLE);
#else
	HAL_PWR_AlwaysOnLSIForDeepSleep(LSIAON_ENABLE, BGRAON_ENABLE, VDCAON_ENABLE);
#endif
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

#ifdef MCU_RESET_AFTER_WAKE_UP	//RESET
	HAL_SCU_SetResetSrc(RST_SWRST, ENABLE);
	SCU->SCR |= (0x9EB30000|SCU_SCR_SWRST_Msk);
#else
	NVIC_ClearPendingIRQ(GPIOAB_IRQn);

	SystemClock_Config();

	EXTI_PortA_Configure(); //To return original external interrupt setting for PA0 when MCU wake-up in sleep mode.
#endif
#ifdef DEEP_SLEEP_MODE_DEBUG_MSG	
	cprintf("\n\rWaked Up from Deep Sleep");
#endif
}
#endif //DEEP_SLEEP_MODE_ENABLE

#ifdef GPIO_ENABLE

#ifdef ESTEC_2ND_BOARD_SUPPORT
/**********************************************************************
 * @brief		A2B_DIRECT_State
 * @Description   whether A2B Master feature is supportted(Low) or not(High)
 * @param[in]	None
 * @return 		TRUE : A2B Master feature disable
 *				FALSE : A2B Master feature enable
 **********************************************************************/
Bool A2B_Direct_State(void) //KMS250227_2 : //PA6/Pin2(A2B_DIRECT) - High : A2B Master feature disable / Low : A2B Master feature enable
{
	Bool B_A2B_Master_Feature_Enable;

	if(HAL_GPIO_ReadPin(PA) & _BIT(6)) //Check the state of PA6
		B_A2B_Master_Feature_Enable = TRUE; //A2B Master feature disable
	else
		B_A2B_Master_Feature_Enable = FALSE; // A2B Master feature enable

	return B_A2B_Master_Feature_Enable;
}
#endif

/**********************************************************************
 * @brief		Input_Source_State
 * @param[in]	None
 * @return 		TRUE : A2B Mode
 *				FALSE : Aux Mode
 **********************************************************************/
INPUT_MODE Input_Source_State(void) //KMS241213_2 : Added new function to check current input source whether A2B or Aux //PA4
{
	INPUT_MODE B_A2B_On;
	
	if(HAL_GPIO_ReadPin(PA) & _BIT(4)) //PA4
		B_A2B_On = INPUT_MODE_A2B; //TRUE; //A2B Mode
	else
		B_A2B_On = INPUT_MODE_AUX; //FALSE; //Aux Mode

	return B_A2B_On;
}

/**********************************************************************
 * @brief		Input_Source_Control
 * @param[in]	B_Aux_Mode
 * @return 		INPUT_MODE_AUX(TRUE) : Aux Mode
 *				INPUT_MODE_AUX(FALSE) : A2B Mode
 **********************************************************************/
void Input_Source_Control(INPUT_MODE B_Aux_Mode) //KMS241223_1 //KMS241213_2 : To inform current mode(A2B or Aux) to DSP using PA3
{
	if(B_Aux_Mode == INPUT_MODE_AUX) //TRUE
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rSet PA3 !!!");
#endif
		HAL_GPIO_SetPin(PA, _BIT(3)); //Made PA3 to High
	}
	else
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rClear PA3 !!!");
#endif
		HAL_GPIO_ClearPin(PA, _BIT(3)); //Made PA3 to Low
	}
}

#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT) //KMS250228_3 : Mute On/Off function.
/**********************************************************************
 * @brief		Mute_Relay_Control
 * @param[in]	B_Aux_Mode
 * @return 		MUTE_ON_STATE(TRUE) : Mute On
 *				MUTE_OFF_STATE(FALSE) : Mute Off
 **********************************************************************/
 void Mute_Relay_Control(MUTE_STATE B_Mute_On)
{
	if(B_Mute_On ==MUTE_ON_STATE)// TRUE
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rSet PF2/Mute On !!!");
#endif
		HAL_GPIO_ClearPin((PORT_Type *)PF, _BIT(2)); //Made PF2 to Low //Mute On
	}
	else
	{
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rClear PF2/Mute Off !!!");
#endif
		HAL_GPIO_SetPin((PORT_Type *)PF, _BIT(2)); //Made PF2 to High //Mute Off
	}
}
#endif

/**********************************************************************
 * @brief		ACC_On_State
 * @param[in]	None
 * @return 		TRUE : ACC-ON
 *				FALSE : ACC-OFF
 **********************************************************************/
Bool ACC_On_State(void) //KMS241129_2 : ACC ON/OFF status check functtion to inform ACC status to A2B Slave using
{
	Bool B_ACC_On;
	
	if(HAL_GPIO_ReadPin(PA) & _BIT(0)) //Check the state of PA0
		B_ACC_On = TRUE; //ACC ON
	else
		B_ACC_On = FALSE; //ACC OFF

	return B_ACC_On;
}

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
		
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rPower On ~~~ !!!");
#endif
		HAL_GPIO_SetPin(PA, _BIT(1)); //Made PA1 to High
		HAL_GPIO_SetPin(PA, _BIT(2)); //Made PA2 to High
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_1 : The PF3/Pin37(12V_CNTRL) is followed by LDO_CNTRL state.
		HAL_GPIO_SetPin((PORT_Type *)PF, _BIT(3)); //Made PF3 to High
#endif
	}
	else if(B_Need_ACC_Off) //Need to make PA1/PA2 to Low. But especially PA2 should be 1sec later.
	{		
		B_Need_ACC_Off = FALSE;

#ifdef GPIO_DEBUG_MSG
		cputs("\n\rPower Off ~~~ !!!");
#endif
#ifdef TIMER20_ENABLE
		TIMER20_Interrupt_Mode_Run(TRUE); //1sec Timer Start for PA2
#endif
		HAL_GPIO_ClearPin(PA, _BIT(1)); //Made PA1 to Low
#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT)
		Mute_Relay_Control(MUTE_ON_STATE); //KMS250228_3 : Mute On
#endif
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
		
		if(ACC_On_State() == TRUE) //PA0
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

#ifndef INTPUT_SOURCE_SELECTION_UPON_POWER_ON //KMS241213_3	
	if (status & 0x00000300) //KMS241213_2 : External Interrupt is only PA4. xx11 0000 0000
	{
		clear_bit = status & 0x00000300;
		HAL_GPIO_EXTI_ClearPin(PA, status&clear_bit);
		
		if(Input_Source_State() == INPUT_MODE_A2B) //PA4 - A2B Mode
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rPA4 GPIO High - Input source A2B");
#endif
			Input_Source_Control(INPUT_MODE_A2B); //FALSE //KMS241223_1 : Changed sending data state for DSP.
#ifdef ESTEC_2ND_BOARD_SUPPORT
			HAL_GPIO_ClearPin(PE, _BIT(1)); //KMS250227_3 : Made PE1 to Low(XTAL-IN of DSP is connected with A2B Tranceiver's MCLK(A2B Mode))
#endif
		}
		else //PA4 - Aux Mode
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rPA4 GPIO Low - Input source Aux");
#endif
			Input_Source_Control(INPUT_MODE_AUX); //TRUE //KMS241223_1 : Changed sending data state for DSP.
#ifdef ESTEC_2ND_BOARD_SUPPORT
			HAL_GPIO_SetPin(PE, _BIT(1)); //KMS250227_3 : Made PE1 to High(XTAL-IN of DSP is connected with X-TAL(Aux Mode))
#endif
		}
	}
#endif //INTPUT_SOURCE_SELECTION_UPON_POWER_ON
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
#ifndef INTPUT_SOURCE_SELECTION_UPON_POWER_ON
	HAL_GPIO_EXTI_Config(PA, 4, PCU_INTERRUPT_MODE_EDGE, PCU_INTERRUPT_CTRL_EDGE_BOTH); //KMS241213_2
#endif

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
	HAL_GPIO_ConfigPullup(PA, 0, PCU_PUPD_DISABLE); //KMS250228_2 : The PA0/Pin44(ACC_INT_MICOM) is input and no need internal pull-up.
	HAL_GPIO_SetDebouncePin(PA, 0, ENABLE);
	HAL_GPIO_ClearPin(PA, _BIT(0)); //Made PA0 to Low during initailizing

	//PA1/Pin45(ACC_OUT_MICOM) : Output : This pin is followed by PA0 state
	HAL_GPIO_ConfigOutput(PA, 1, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PA, 1, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PA, _BIT(1)); //Made PA1 to Low during initailizing

	//PA2/Pin46(LDO_CNTRL) : Output : This pin is followed by PA1 state but it should work after 1sec when PA1 pin state is changed.
	HAL_GPIO_ConfigOutput(PA, 2, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PA, 2, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PA, _BIT(2)); //Made PA2 to Low during initailizing

	//PA3/Pin47(INPUT_CNTRL_OUT) : Output : This pin is followed by PA4 below. - High : Input source A2B / Low : Input Source Aux
	HAL_GPIO_ConfigOutput(PA, 3, PCU_MODE_PUSH_PULL); //KMS241220_2 : Changed this pin to Push-pull
	HAL_GPIO_ConfigPullup(PA, 3, PCU_PUPD_PULL_UP);
	HAL_GPIO_ClearPin(PA, _BIT(3)); //Made PA3 to Low during initailizing

	//PA4/Pin48(INPUT_CNTRL) : Input : Just pass input signal to PA3 and check input just one time. - High : Input source A2B / Low : Input Source Aux
	HAL_GPIO_ConfigOutput(PA, 4, PCU_MODE_INPUT);
	HAL_GPIO_ConfigPullup(PA, 4, PCU_PUPD_DISABLE); //KMS250228_2 : PA4/Pin48(INPUT_CNTRL) is input and no need internal pull-up.
	HAL_GPIO_SetDebouncePin(PA, 4, ENABLE);
	HAL_GPIO_ClearPin(PA, _BIT(4)); //Made PA4 to Low during initailizing

	//KMS250109_1 : Added DSP RESET Control. SET Low
	//PA5/Pin1(DSP_RESET_CNTRL) : Output : - High : NORMAL / Low : DSP RESET
	HAL_GPIO_ConfigOutput(PA, 5, PCU_MODE_OPEN_DRAIN);
	HAL_GPIO_ConfigPullup(PA, 5, PCU_PUPD_DISABLE);
	HAL_GPIO_ClearPin(PA, _BIT(5)); //Made PA5 to Low during initailizing
	
#ifdef ESTEC_2ND_BOARD_SUPPORT
	//PA6/Pin2(A2B_DIRECT) : Input : This means whether A2B Master feature is supportted(Low) or not(High). - High : A2B Master feature disable / Low : A2B Master feature enable
	HAL_GPIO_ConfigOutput(PA, 6, PCU_MODE_INPUT);
	HAL_GPIO_ConfigPullup(PA, 6, PCU_PUPD_PULL_UP);
	HAL_GPIO_SetDebouncePin(PA, 6, ENABLE);
	HAL_GPIO_ClearPin(PA, _BIT(6)); //Made PA6 to Low during initailizing

	//PF3/Pin37(12V_CNTRL) : Output : This pin is followed by LDO_CNTRL state.
	HAL_GPIO_ConfigOutput((PORT_Type *)PF, 3, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup((PORT_Type *)PF, 3, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin((PORT_Type *)PF, _BIT(3)); //Made PF3 to Low during initailizing

	//PF2/Pin38(OP_OUT_RELAY_CNTRL) : Output : This pin is followed by PA0 inverse state but it should work after 1sec(timer) when PA0 pin state is changed.
	//MUTE control using relay. - High : Mute / Low : Mute Off
	HAL_GPIO_ConfigOutput((PORT_Type *)PF, 2, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup((PORT_Type *)PF, 2, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin((PORT_Type *)PF, _BIT(2)); //KMS250307_1 : Made PF2 to Low(Mute) during initailizing

	//PE0/Pin32(I2C_SW_CNTL) : Output : I2C_0 Switch Control. - High : I2C_0 can use DSP & Ext.A2B(I2C_0_DSP)  / Low : I2C_0 can use ADC & DAC(I2C_0_CODEC). 
	HAL_GPIO_ConfigOutput(PE, 0, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PE, 0, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PE, _BIT(0)); //Made PE0 to Low during initailizing

	//PE1/Pin31(MCLK_SW_CNTR) : Output : Can choose XTAL-IN of DSP. - High : X-TAL(Aux Mode)  / Low : A2B Tranceiver's MCLK(A2B Mode) 
	HAL_GPIO_ConfigOutput(PE, 1, PCU_MODE_PUSH_PULL);
	HAL_GPIO_ConfigPullup(PE, 1, PCU_PUPD_PULL_UP); //The schematic doesn't have any external pull-up.
	HAL_GPIO_ClearPin(PE, _BIT(1)); //Made PE1 to Low during initailizing
#endif //ESTEC_2ND_BOARD_SUPPORT
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
	uint8_t uDeviceID = 0x6A;//0x31;
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_4
	I2C_Port_No num = I2C_0_DSP;
#else
	I2C_Port_No num = I2C_0;
#endif
#endif

#ifdef MCU_EVK_I2C_TEST //Using ESMT82584F
	uData[0] = 0x12;
	I2C_Interrupt_Write_Data_8bit_SubAdd(num, uDeviceID, 0x1a, &uData[0],1);
	uData[0] = 0x32;
	I2C_Interrupt_Write_Data_8bit_SubAdd(num, uDeviceID, 0x1a, &uData[0],1);
	uData[0] = 0x2e;
	I2C_Interrupt_Write_Data_8bit_SubAdd(num, uDeviceID, 0x03, &uData[0],1);
	uData[0]=0;
	I2C_Interrupt_Read_Data_8bit_SubAdd(num, uDeviceID, 0x1a, &uData[0], 1);
	cprintf("\n\r read[0x03] = 0x%02x",uData[0]);

#ifdef MCU_EVK_FUNCTION_TEST
#ifdef ADAU1452_ENABLE
	I2C_Interrupt_Read_Data_16bit_SubAdd(I2C_1, 0x38, 0xF218, uData, 2);
#endif
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
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250305_1
	Bool B_Need_Init_Board = FALSE;
	Bool B_A2B_COM_Complete = FALSE;
	//uint32_t SysTick_100ms_count_check = 0;
#else //ESTEC_2ND_BOARD_SUPPORT
#ifdef ESTEC_A2B_STACK_PORTING
	a2b_UInt32 nResult = 0;
#endif
#endif //ESTEC_2ND_BOARD_SUPPORT
#ifdef ADAU1452_DUMP //KMS250113_1 : Added Dump code for ADAU1452 registers.
	int32_t count = 0;
#endif

	/*Configure menu prinf*/
	DEBUG_MenuPrint();

	/*Configure port peripheral*/
#ifdef GPIO_ENABLE
	GPIO_Configure();
#endif

#if 0//defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE) //KMS241224_1 
	I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
#endif
#ifdef TIMER20_ENABLE
	TIMER20_Configure();
#endif
#if defined(ESTEC_2ND_BOARD_SUPPORT) && defined(TIMER21_ENABLE)
	TIMER21_Configure();
#endif
#ifdef GPIO_ENABLE
	EXTI_PortA_Configure();
#endif
#ifdef SYSTICK_TIMER_ENABLE
	/*Configure SysTick peripheral*/
	SysTick_Configure();
#endif

	/* Enable IRQ Interrupts */
	__enable_irq();

//KMS241219_1 : Need to move here because power should be supplied before DSP/Audio Codec init.
#ifdef MCU_RESET_AFTER_WAKE_UP//KMS241129_1 : After MCU reset from wake-up, it need to set ACC_ON status in here. 
	//Becuase MCU interrupt pin has internal pull-up that's why MCU can't detect ACC_ON status on MCU reset.

	delay_ms(100); //KMS250306_1 : Added delay due to GPIO read error.
	
	if(ACC_On_State() == TRUE)
	{
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250305_1
		if(Input_Source_State() == INPUT_MODE_AUX)
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rXTAL-IN of DSP is connected with X-TAL(AUX Mode)");
#endif
			HAL_GPIO_SetPin(PE, _BIT(1)); //KMS250305_1 : Made PE1 to High(XTAL-IN of DSP is connected with X-TAL(AUX Mode))
			Init_Board();
		}
		else //A2B Mode
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rXTAL-IN of DSP is connected with A2B Tranceiver's MCLK(A2B Mode)");
#endif
			HAL_GPIO_ClearPin(PE, _BIT(1)); //KMS250305_1 : Made PE1 to Low(XTAL-IN of DSP is connected with A2B Tranceiver's MCLK(A2B Mode))
			B_Need_Init_Board = TRUE;
			
			B_Need_ACC_On = TRUE; //KMS250305_2 : Under A2B Mode, Power should be supplied at first time.
			Power_Control(); //KMS250305_2
			
#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4		
			//I2C_Configure(I2C_0_DSP, I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
			I2C_Configure(I2C_1, I2C_SPEED_400K, SLAVE); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
#else
			I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
#endif
			//SysTick_100ms_count_check = SysTick_100ms_count;
		}
#else //ESTEC_2ND_BOARD_SUPPORT
#ifdef GPIO_DEBUG_MSG
		cputs("\n\rACC_ON is detected on MCU restart");
#endif
		B_Need_ACC_On = TRUE;

		
#ifdef GPIO_ENABLE //KMS241219_1 : Need to move here because power should be supplied before DSP/Audio Codec init.
		Power_Control(); //KMS241127_2 : Power Control is executed here.
#endif
	/*
		}
 */ //KMS250228_1 : During Power-On, we don't need to initialize all peripherals. So, this statement is moved below.
#if defined(I2C_0_ENABLE) || defined(I2C_1_ENABLE) //KMS241224_1 : I2C I/F Init is moved after Power_Control() due to DSP Init problem and added delay 500ms.
		delay_ms(1000); //Tested with 3sec delay
		//NTA : MCLK SW CNTR Pin Control
#ifdef MCU_RESET_AFTER_WAKE_UP
		if(ACC_On_State() == TRUE)

#endif

		delay_ms(500); //KMS250106_1 : Changed timing from 100ms to 500ms due to ADAU1452 Init failure.
#ifdef I2C_1_SLAVE_ENABLE //KMS250228_4		
		I2C_Configure(I2C_0_DSP, I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
		I2C_Configure(I2C_1, I2C_SPEED_400K, SLAVE);
#else
		I2C_Configure(I2C_SPEED_400K, MASTER); //Define I2C Speed and Master/Slave. //KMS241206_1 : A2B I2C speed is fixed 400K in A2B and MCU both sides.
#endif
#endif

#ifdef GPIO_ENABLE //KMS241213_2
		//KMS241213_3 : Just check one time upon power on if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is defined but it checks current status with intterrupt and upon Power On if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is not defined
		if(Input_Source_State() == INPUT_MODE_A2B)
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rInput Source is A2B Mode upon Power On !!!");
#endif
			Input_Source_Control(INPUT_MODE_A2B); //FALSE //KMS241223_1 : Changed sending data state for DSP.
		}
		else
		{
#ifdef GPIO_DEBUG_MSG
			cputs("\n\rInput Source is Aux Mode upon Power On !!!");
#endif
			Input_Source_Control(INPUT_MODE_AUX); //TRUE //KMS241223_1 : Changed sending data state for DSP.
		}
#endif //GPIO_ENABLE

#ifdef ADAU1452_ENABLE
		ADAU1452_Init(); //DSP Init
#endif
#ifdef ADAU1761_ENABLE
		ADAU1761_Init(); //Audio Codec Init
#endif
#ifdef MCU_EVK_FUNCTION_TEST
		MCU_EVK_Function_Test();
#endif

#ifdef ESTEC_A2B_STACK_PORTING
		/* system/platform specific initialization */
		//nResult = adi_a2b_SystemInit();
		
		if(nResult != 0)
		{
			//assert(nResult == 0);
		}

		/* A2B Network Setup. Performs discovery and configuration of A2B nodes and its peripherals */
#ifndef A2B_SLAVE_EXTENSION_SUPPORT_TEST
		nResult = a2b_setup(&gApp_Info);
#endif //A2B_SLAVE_EXTENSION_SUPPORT_TEST
		if (nResult)
		{
			/* failed to setup A2B network */
			//assert(nResult == 0);
		}
#endif //ESTEC_A2B_STACK_PORTING

#ifdef _DEBUG_MSG
		cputs("\n\rInit Done !!!");
#endif
#if defined(ESTEC_2ND_BOARD_SUPPORT) && defined(TIMER21_ENABLE)
		TIMER21_Interrupt_Mode_Run(TRUE); //KMS250228_3 : Mute Off execution after 1 sec using timer.
#endif
#endif //ESTEC_2ND_BOARD_SUPPORT
	}
	else
	{
#ifdef DEEP_SLEEP_MODE_ENABLE
		B_Deep_Sleep = TRUE;
#endif

#ifdef _DEBUG_MSG
		cputs("\n\rInit NOT Done !!! due to ACC Off !!!");
#endif
	}
#endif //KMS250228_1 : During Power-On, we don't need to initialize all peripherals. So, this statement is moved here.

	while(1) {
#ifdef ADAU1452_DUMP //KMS250113_1 : Added Dump code for ADAU1452 registers.
		count++;
		
		if(count == 1000)
		{				
			ADAU1452_Register_All_Read();
		}
#endif //ADAU1452_DUMP

#if defined(I2C_1_SLAVE_ENABLE) && defined(MCU_RESET_AFTER_WAKE_UP) //KMS250228_4 : Polling check for I2C Read
		if(ACC_On_State() == TRUE)
			B_A2B_COM_Complete = Slave_Read_Buffer_Not_Empty();
#endif

#ifdef ESTEC_2ND_BOARD_SUPPORT
		/*User Code start*/
		
		if(B_Need_Init_Board) //KMS250305_1 : Under A2B Mode, we need to init all peripheral after A2B recever complete A2B communication with A2B Master
		{
#ifdef HMC_A2B_MASTER_BOARD_SUPPORT
			if(B_A2B_COM_Complete)// || (((SysTick_100ms_count - SysTick_100ms_count_check) >= 200) && SysTick_100ms_count_check != 0xffffffff)) //10sec Wait and Init_Board
#endif			
			{
				if(B_A2B_COM_Complete)
				{
#ifdef _DEBUG_MSG
					cputs("\n\rForced Execution Init_Board() : After A2B communication is completed");
#endif
				}
				else
				{
#ifdef _DEBUG_MSG
					cputs("\n\rForced Execution Init_Board() : using X-TAL instead of A2B Receiver's MCLK");
#endif
					HAL_GPIO_SetPin(PE, _BIT(1)); //KMS250305_1 : Made PE1 to High(XTAL-IN of DSP is connected with X-TAL(AUX Mode))
				}
				
				B_Need_Init_Board = FALSE;
				B_A2B_COM_Complete = FALSE;

				//SysTick_100ms_count_check = 0xffffffff;
			
				Init_Board();
			}
		}
		else
		{
#endif
#ifdef GPIO_ENABLE
			Power_Control(); //KMS241127_2 : Power Control is executed here.
#endif
#if defined(TIMER21) && defined(ESTEC_2ND_BOARD_SUPPORT) //KMS250228_3 : Mute Off execution after 1 sec using timer.
			if(B_Mute_TimerOn == TRUE)
			{
				B_Mute_TimerOn = FALSE;

				Mute_Relay_Control(MUTE_OFF_STATE); //Mute Off
			}
#endif
#ifdef DEEP_SLEEP_MODE_ENABLE
			if(B_Deep_Sleep == TRUE)
			{
				B_Deep_Sleep = FALSE;

				if(ACC_On_State() == FALSE) //KMS241129_3 : Need to check whether ACC Off or ACC On again before MCU goes deep-sleep mode
				{
					HAL_GPIO_ClearPin(PA, _BIT(2)); //KMS241129_3 : Move to here from time20.c!!! //Made PF3 to Low
#ifdef ESTEC_2ND_BOARD_SUPPORT //KMS250227_1 : The PF3/Pin37(12V_CNTRL) is followed by LDO_CNTRL state.
					HAL_GPIO_ClearPin((PORT_Type *)PF, _BIT(3)); //Made PF3 to Low
#endif
					PWR_DeepSleepRun();
				}
			}
#endif
#ifdef ESTEC_A2B_STACK_PORTING
#ifdef ESTEC_2ND_BOARD_SUPPORT
			if (B_A2B_Master_Support == TRUE) //KMS250227_2 : //PA6/Pin2(A2B_DIRECT) - High : A2B Master feature disable / Low : A2B Master feature enable
			{
				/* Monitor a2b network for faults and initiate re-discovery if enabled */
				nResult = a2b_fault_monitor(&gApp_Info);

				/*-----------------------------------------------------------*/
				/* Add your other continuous monitoring application code here */
				/*-----------------------------------------------------------*/

				/* condition to exit the program */
				if (nResult != 0)
				{
#ifdef _DEBUG_MSG
					cprintf("\n\r A2B_Falut_monitor = 0x%02x",nResult);
#endif
				}

				/* tick keeps all process rolling.. so keep ticking */
				a2b_stackTick(gApp_Info.ctx);
			}
#else //ESTEC_2ND_BOARD_SUPPORT
			/* Monitor a2b network for faults and initiate re-discovery if enabled */
			nResult = a2b_fault_monitor(&gApp_Info);

			/*-----------------------------------------------------------*/
			/* Add your other continuous monitoring application code here */
			/*-----------------------------------------------------------*/

			/* condition to exit the program */
			if (nResult != 0)
			{
#ifdef _DEBUG_MSG
				cprintf("\n\r A2B_Falut_monitor = 0x%02x",nResult);
#endif
			}

			/* tick keeps all process rolling.. so keep ticking */
			a2b_stackTick(gApp_Info.ctx);
#endif //ESTEC_2ND_BOARD_SUPPORT
#endif //ESTEC_A2B_STACK_PORTING
#ifdef ESTEC_2ND_BOARD_SUPPORT
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
