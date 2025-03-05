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

#if defined(TIMER21_ENABLE) && defined(ESTEC_2ND_BOARD_SUPPORT)
#include "A31G22x_hal_timer2n.h"
#include "timer21.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
TIMER2n_CFG_Type TIMER21_Config;

/* Private define ----------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
static void Main_TIMER21_IRQHandler(void);
static void TIMER21_Interrupt_Service_Routine(void);

void TIMER21_IRQHandler_Interrupt(void);


/*******************************************************************************
* @brief      Timer21 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void TIMER21_Interrupt_Mode_Run(Bool On)
{
#ifdef TIMER21_DEBUG_MSG
	cprintf("\n\rTimer21 On = %d\r\n",On);
#endif

	if(On)
	{
		HAL_TIMER2n_Start(TIMER21);
	}
	else
	{
		HAL_TIMER2n_Stop(TIMER21);
		HAL_TIMER2n_ClearCounter(TIMER21);
	}
}

/*******************************************************************************
* @brief      Timer20 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void TIMER21_IRQHandler_Interrupt(void)
{
#ifdef TIMER21_DEBUG_MSG
	cputs("\n\rTimer21 Interrupt\r\n");
#endif
	Main_TIMER21_IRQHandler();
}



/**********************************************************************
 * @brief		Main_TIMER21_IRQHandler
 * @param[in]	None
 * @return 		None
 **********************************************************************/
static void Main_TIMER21_IRQHandler(void)
{
#ifdef TIMER21_DEBUG_MSG
	cputs("\n\rMain_TIMER21_IRQHandler\r\n");
#endif

	if (HAL_TIMER2n_GetStatus(TIMER21) & TIMER2n_STATUS_MATCH_INT)
	{
		TIMER21_Interrupt_Service_Routine();
		
		HAL_TIMER2n_ClearStatus(TIMER21, TIMER2n_STATUS_MATCH_INT);
		HAL_TIMER2n_ClearCounter(TIMER21); //HAL_TIMER2n_ClearCounter() is called by TIMER2n_Configure() function, also.
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
	HAL_SCU_Timer20_ClockConfig(T20CLK_PCLK);
	
	TIMER21_Config.ExtClock = DISABLE; // PCLK 48MHz
	TIMER21_Config.PrescalerData = 32-1; //32MHz = 1MHz -> 1us
	TIMER21_Config.OutputPolarity = TIMER2n_OUTPUT_POLARITY_LOW;
	TIMER21_Config.MatchInterrupt = ENABLE;
	TIMER21_Config.CaptureInterrupt = DISABLE;
	TIMER21_Config.AData = (2500*400); //1sec //(2500*100); //250ms //TIMER21_Config.ADR = (2500*200); //500ms
	TIMER21_Config.Mode = TIMER2n_MODE_PERIODIC;

	/* No Need the following Settings */
	//TIMER21_Config.BData = 0;
	//TIMER21_Config.ExtClockEdge = TIMER2n_EXT_CLOCK_EDGE_FALLING; //Not used /*!< External clock edge selection */
	//TIMER21_Config.CaptureSignal = TIMER2n_CAPTURE_SIGNAL_LSE; /*!< Capture signal selection (only timer20)*/
	
	HAL_TIMER2n_Init(TIMER21, &TIMER21_Config);
	
	/* Enable Interrupt for TIMERx channel */
	NVIC_SetPriority(TIMER21_IRQn, 3);
	NVIC_EnableIRQ(TIMER21_IRQn); 
}

static void TIMER21_Interrupt_Service_Routine( void )
{
	TIMER21_Interrupt_Mode_Run(FALSE);
	
	B_Mute_TimerOn = TRUE;

}
#endif //TIMER21_ENABLE


