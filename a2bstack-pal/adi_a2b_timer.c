/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************

   Name       : adi_a2b_timer.c
   
   Description: This file is responsible for handling timer related functions.        
                 
   Functions  :  adi_a2b_TimerOpen()
                 adi_a2b_TimerStart()
                 adi_a2b_TimerStop()
                 adi_a2b_TimerCallbackFunction()
                 adi_a2b_TimerClose()
                 void  adi_a2b_Delay()
                 

   Prepared &
   Reviewed by: Automotive Software and Systems team, 
                IPDC, Analog Devices,  Bangalore, India
                
   @version: $Revision: 3344 $
   @date: $Date: 2015-07-29 08:44:17 +0530 (Wed, 29 Jul 2015) $
               
******************************************************************************/
/*! \addtogroup Target_Dependent Target Dependent
 *  @{
 */

/** @defgroup Timer
 *
 * This module controls timer configuration.Framework uses timer during discovery, I2C transaction and error signal indication.
 * All the interface functions needs to be re-implemented for different processor.
 */

/*! \addtogroup Timer
 *  @{
 */


#include "main_conf.h"
#ifndef ESTEC_A2B_STACK_PORTING

/*============= I N C L U D E S =============*/

#include "adi_a2b_datatypes.h"
#include "adi_a2b_framework.h"
#include "adi_a2b_timer.h"
#include <services\tmr\adi_tmr.h>
#include <services\pwr\adi_pwr.h>

/*============= D E F I N E S =============*/

/*============= D A T A =============*/

/*! Timer handle */
static ADI_TMR_HANDLE   ghTimer[A2B_MAX_TIMERS];

/*============= C O D E =============*/
typedef void (*TIMER_INT_HANDLER_PTR)(void);
/*
** Function Prototype section
*/
static void adi_a2b_TimerCallbackFunction(void* DeviceHandle, a2b_UInt32 Event, void* pArg);

/******************************************************************************/
/*!
@brief  This function Initializes timer driver. 

@param [in] nTimerNo        Timer identification number.

@param [in] pUserArgument   User argument for call-back

@return         Return code
                - 0: Success
                - 1: Failure 

*/    
/******************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 adi_a2b_TimerOpen(a2b_UInt32 nTimerNo,void* pUserArgument)
{
    /* Return value - assume we're going to be successful */
    ADI_TMR_RESULT eTmrResult   =   ADI_TMR_SUCCESS;
    a2b_UInt16 nRegCtrlVal;
    /*! Memory required for opening the timer */
    static uint8_t TimerMemory[A2B_MAX_TIMERS][ADI_TMR_MEMORY_SIZE];

    eTmrResult = adi_tmr_Open (
    				nTimerNo,
                    TimerMemory[nTimerNo],
                    ADI_TMR_MEMORY_SIZE,
                    &(ghTimer[nTimerNo]),
                    (ADI_CALLBACK)&adi_a2b_TimerCallbackFunction,
                    pUserArgument
                    );

    eTmrResult = adi_tmr_SetMode(
                    ghTimer[nTimerNo],
                    ADI_TMR_MODE_PWM);
    
    eTmrResult = adi_tmr_SetClockSource(ghTimer[nTimerNo],ADI_TMR_CLKIN_SYSCLK);

    eTmrResult = adi_tmr_InterruptEnable(ghTimer[nTimerNo], TRUE );

    nRegCtrlVal = 0x55u;
    eTmrResult = adi_tmr_SetControlReg(ghTimer[nTimerNo],ADI_TMR_CONFIG_REG, nRegCtrlVal);

    return ((a2b_UInt32)eTmrResult);
}

/****************************************************************************/
/*!
@brief  This function starts specified timer channel.
        Timer period shall be in micro-seconds

@param [in] nTimerNo    Timer number
@param [in] nTime       Time period in micro-seconds

@return         Return code
                - 0: Success
                - 1: Failure 

*/    
/******************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 adi_a2b_TimerStart(a2b_UInt32 nTimerNo, a2b_UInt32 nTime)
{ 
    a2b_UInt32 nWidth = 0u,nPeriod = 0u, nReturnValue = 0u;
    a2b_UInt32 nSClk;
    ADI_TMR_RESULT eTmrResult   =   ADI_TMR_SUCCESS;
    
    /* Calculate  period and width  from system clock */
    nReturnValue = (a2b_UInt32)adi_pwr_GetSystemFreq (&nSClk);

    if(nReturnValue == 0u)
    {
        /*! In micro seconds  */
        nPeriod = ((nSClk)/1000000u)*nTime;
        nWidth  = (nPeriod/(a2b_UInt32)1u);
    }

    eTmrResult = adi_tmr_SetPeriod(
                    ghTimer[nTimerNo],
                    nPeriod);

    eTmrResult = adi_tmr_SetWidth(
                    ghTimer[nTimerNo],
                    nWidth);


    eTmrResult = adi_tmr_Enable(
                    ghTimer[nTimerNo],
                    true);

    return(nReturnValue);
    
}
/******************************************************************************/
/*!

@brief  This function stops the specified timer channel immediately.

@param [in] nTimerNo    Timer number

@return         Return code
                - 0: Success
                - 1: Failure 

*/ 
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 adi_a2b_TimerStop(a2b_UInt32 nTimerNo)
{

    /* Return value - Assume we're going to be successful */
    a2b_UInt32 nReturnValue = (a2b_UInt32)0u;
    a2b_UInt16 nRegCtrlVal;

    /* 'adi_tmr_Enable', 'adi_tmr_StopPWMOut' is buggy. Use direct MMR */
#if __CCESVERSION__ == 0x02010000
    ADI_TMR_RESULT eTmrResult   =   ADI_TMR_SUCCESS;
    eTmrResult = adi_tmr_Enable(
                    ghTimer[nTimerNo],
                    false);


    eTmrResult = adi_tmr_StopPWMOut(ghTimer[nTimerNo], 1 << (12 + nTimerNo), true );
#else
    *pTIMER_DISABLE = 1u << (uint8)nTimerNo;
    *pTIMER_STATUS = 1u << (uint8)(12+ nTimerNo);

#endif

    return(nReturnValue);
}

/****************************************************************************/
/*!

@brief      This function terminates timer service. Timer shall be reset

@param [in] nTimerNo    Timer number
    
@return         Return code
                - 0: Success
                - 1: Failure 
*/    
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 adi_a2b_TimerClose(a2b_UInt32 nTimerNo)
{
	/* Return value - assume we're going to be successful */
	ADI_TMR_RESULT eTmrResult   =   ADI_TMR_SUCCESS;

    eTmrResult = adi_tmr_Close(ghTimer[nTimerNo]);
    
    return((a2b_UInt32)eTmrResult);
}

/********************************************************************************/
/*!
@brief This function implements software delay.

@param [in] nTime Delay in Milli-seconds(ms)

@return    void 
    
*/
/***********************************************************************************/
A2B_PAL_L1_CODE
void  adi_a2b_Delay(a2b_UInt32 nTime)
{
    a2b_UInt32 nDelayInCycles;
    a2b_UInt32 nCClk;

    (void)adi_pwr_GetCoreFreq (&nCClk);
    /* nCount represents the number of execution cycle  */
    nDelayInCycles = (nCClk/(10000u))*nTime;
    
    /* Delay implementation */
    while(nDelayInCycles--)
    {
    }
}



/*! \addtogroup Timer_Internal_Functions Timer Internal Functions
 *  @{
 */
/******************************************************************************/
/*!
@brief  Timer call back function. It is invoked upon timer expire

@param [in] DeviceHandle     Timer  handle
@param [in] Event            Interrupt event
@param [in] pArg             user argument if any
    
@return     none
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
static void adi_a2b_TimerCallbackFunction(void* DeviceHandle, a2b_UInt32 Event, void* pArg)
{
    ADI_A2B_TIMER_HANDLER_PTR pTimerHandle = (ADI_A2B_TIMER_HANDLER_PTR)DeviceHandle ;
  
    /* Set time out */
    if(DeviceHandle != NULL)
    {
        (pTimerHandle->pCallbackhandle)(pTimerHandle);
    }

}

    



/**
 @}
*/

/**
 @}
*/


/*
**
** EOF: $URL$
**
*/
#endif //ESTEC_A2B_STACK_PORTING

