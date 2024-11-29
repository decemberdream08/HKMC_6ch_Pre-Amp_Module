/**********************************************************************
* @file		ir.c
* @brief	IR code
* @version	1.0
* @date		
* @author	MS Kim
*
* Copyright(C) , ESTec
* All rights reserved.
*
**********************************************************************/
#include "main_conf.h"

#ifdef TIMER21_ENABLE
#include "A31G22x_hal_timer2n.h"
#include "timer21.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
TIMER2n_CFG_Type TIMER21_Config;

static uint32_t timer20_100ms_count = 0, timer20_500ms_count = 0, timer20_1s_count = 0;


/* Private define ----------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
static void Main_TIMER21_IRQHandler(void);
static void TIMER21_Interrupt_Service_Routine( void );

void TIMER21_IRQHandler_Interrupt(void);


/*******************************************************************************
* @brief      Timer20 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void TIMER21_IRQHandler_Interrupt(void)
{
	Main_TIMER21_IRQHandler();
}


/**********************************************************************
 * @brief		Main_TIMER21_IRQHandler
 * @param[in]	None
 * @return 		None
 **********************************************************************/
static void Main_TIMER21_IRQHandler(void)
{
	if (HAL_TIMER2n_GetStatus(TIMER21) & TIMER2n_STATUS_MATCH_INT) //100ms timer
	{	
		HAL_TIMER2n_ClearStatus(TIMER21, TIMER2n_STATUS_MATCH_INT);

		TIMER21_Interrupt_Service_Routine();
	}
}

/**********************************************************************
 * @brief		TIMER21_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void TIMER21_Configure(void) //100ms Timer
{
	// Timer21 and clock source setting
	HAL_SCU_Timer20_ClockConfig(T1NCLK_PCLK);
	
	TIMER21_Config.ExtClock = DISABLE; // PCLK 48MHz
	TIMER21_Config.PrescalerData = 32-1; //32MHz = 1MHz -> 1us
	TIMER21_Config.OutputPolarity = TIMER2n_OUTPUT_POLARITY_LOW;
	TIMER21_Config.MatchInterrupt = ENABLE;
	TIMER21_Config.CaptureInterrupt = DISABLE;
	TIMER21_Config.AData = (100000); //100ms
	TIMER21_Config.Mode = TIMER2n_MODE_PERIODIC;

	/* No Need the following Settings */
	//TIMER21_Config.BData = 0;
	//TIMER21_Config.ExtClockEdge = TIMER2n_EXT_CLOCK_EDGE_FALLING; //Not used /*!< External clock edge selection */
	//TIMER21_Config.CaptureSignal = TIMER2n_CAPTURE_SIGNAL_LSE; /*!< Capture signal selection (only timer20)*/
	
	HAL_TIMER2n_Init(TIMER21, &TIMER21_Config);
	
	/* Enable Interrupt for TIMERx channel */
	NVIC_SetPriority(TIMER21_IRQn, 3);
	NVIC_EnableIRQ(TIMER21_IRQn); 

	HAL_TIMER2n_Start(TIMER21);

	//Stop condition
	//HAL_TIMER2n_Stop(TIMER21);
	//HAL_TIMER2n_DeInit(TIMER21);
}

static void TIMER21_Interrupt_Service_Routine( void )
{
	if(!(timer20_100ms_count%5))
	{
		if(timer20_500ms_count%2)
		{
			timer20_1s_count++;
#ifdef TIMER21_DEBUG_MSG
			cprintf("\n\rtimer20_1s_count = %d\r\n",timer20_1s_count);
#endif
		}

		timer20_500ms_count++;
	}

	timer20_100ms_count++;
}

#endif //TIMER20_CAPTURE_ENABLE


