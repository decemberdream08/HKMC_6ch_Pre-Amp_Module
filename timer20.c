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

#ifdef TIMER20_ENABLE
#include "A31G22x_hal_timer2n.h"
#include "timer20.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
TIMER2n_CFG_Type TIMER20_Config;

/* Private define ----------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
static void Main_TIMER20_IRQHandler(void);
static void TIMER20_Interrupt_Service_Routine(void);
void TIMER20_IRQHandler_Interrupt(void);


/*******************************************************************************
* @brief      Timer20 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void TIMER20_Interrupt_Mode_Run(Bool On)
{
#ifdef TIMER20_DEBUG_MSG
	cprintf("\n\rTimer On = %d\r\n",On);
#endif

	if(On)
	{
		HAL_TIMER2n_Start(TIMER20);
	}
	else
	{
		HAL_TIMER2n_Stop(TIMER20);
		HAL_TIMER2n_ClearCounter(TIMER20);
	}
}

/*******************************************************************************
* @brief      Timer20 interrupt handler
* @param      None
* @return     None
*******************************************************************************/
void TIMER20_IRQHandler_Interrupt(void) 
{
#ifdef TIMER20_DEBUG_MSG
	cputs("\n\rTimer20 Interrupt\r\n");
#endif
	Main_TIMER20_IRQHandler();
}


/**********************************************************************
 * @brief		TIMER20_IRQHandler_IT
 * @param[in]	None
 * @return 		None
 **********************************************************************/
static void Main_TIMER20_IRQHandler(void)
{
	if (HAL_TIMER2n_GetStatus(TIMER20) & TIMER2n_STATUS_MATCH_INT)
	{
		TIMER20_Interrupt_Service_Routine();
		
		HAL_TIMER2n_ClearStatus(TIMER20, TIMER2n_STATUS_MATCH_INT);
		HAL_TIMER2n_ClearCounter(TIMER20); //HAL_TIMER2n_ClearCounter() is called by TIMER2n_Configure() function, also.
	}

}

/**********************************************************************
 * @brief		TIMER2n_Configure
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void TIMER20_Configure(void)
{
	/*Timer21 clock source from PCLK*/
	HAL_SCU_Timer20_ClockConfig(T20CLK_PCLK);
	
	TIMER20_Config.ExtClock = DISABLE; // PCLK 48MHz
	TIMER20_Config.PrescalerData = 32-1; //32MHz = 1MHz -> 1us
	TIMER20_Config.OutputPolarity = TIMER2n_OUTPUT_POLARITY_LOW;
	TIMER20_Config.MatchInterrupt = ENABLE;
	TIMER20_Config.CaptureInterrupt = DISABLE;
	TIMER20_Config.AData = (2500*400); //1sec //(2500*100); //250ms //TIMER21_Config.ADR = (2500*200); //500ms
	TIMER20_Config.Mode = TIMER2n_MODE_PERIODIC;

	/* No Need the following Settings */
	//TIMER20_Config.BData = 0;
    //TIMER20_Config.ExtClockEdge = TIMER2n_EXT_CLOCK_EDGE_FALLING; //Not used /*!< External clock edge selection */
    //TIMER20_Config.CaptureSignal = TIMER2n_CAPTURE_SIGNAL_LSE; /*!< Capture signal selection (only timer20)*/
	
	HAL_TIMER2n_Init(TIMER20, &TIMER20_Config);
	
	/* Enable Interrupt for TIMERx channel */
	NVIC_SetPriority(TIMER20_IRQn, 3);
	NVIC_EnableIRQ(TIMER20_IRQn); 
}

void TIMER20_Interrupt_Service_Routine( void )
{
	//HAL_GPIO_ClearPin(PA, _BIT(2)); //KMS241129_3 : Move to main.c
	TIMER20_Interrupt_Mode_Run(FALSE);

	B_Deep_Sleep = TRUE;
}

#endif //TIMER21_ENABLE

