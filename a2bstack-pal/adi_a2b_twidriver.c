/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************

   Name       : adi_a2b_twidriver.c
   
   Description: This file is responsible for handling all TWI related functions.        
                 
   Functions  : adi_a2b_TwiOpen()
                adi_a2b_TwiClose()
                adi_a2b_TwiRead8()
                adi_a2b_TwiGenericRead()
                adi_a2b_TwiGenericBlockRead()
                adi_a2b_TwiWrite8()
                adi_a2b_TwiGenericWrite()
                adi_a2b_TwiGenericBlockWrite()
               
                 
   Prepared &
   Reviewed by: Automotive Software and Systems team, 
                IPDC, Analog Devices,  Bangalore, India
                
   @version: $Revision: 3626 $
   @date: $Date: 2015-10-05 14:04:13 +0530 (Mon, 05 Oct 2015) $
               
******************************************************************************/
/*! \addtogroup Target_Dependent Target Dependent
 *  @{
 */

/** @defgroup TWI I2C / TWI
 *
 * This module handles all TWI/I2C transactions. It is used to configure A2B transceiver and the connected peripherals.
 * All the interface functions need to be re-implemented for different processor.
 
   \note I2C and TWI terms are used  interchangeably
 * 
 * 
 *
 */

/*! \addtogroup TWI I2C / TWI
 *  @{
 */


/*============= I N C L U D E S =============*/

#include "main_conf.h"
#ifndef ESTEC_A2B_STACK_PORTING
#include <string.h>
#include <cdefbf527.h>

#include "adi_a2b_datatypes.h"
#include "adi_a2b_framework.h"
#include "adi_a2b_externs.h"
#include "adi_a2b_twidriver.h"
#include "adi_a2b_timer.h"

#if A2B_PRINT_FOR_DEBUG
#include <stdio.h>
#endif

/*============= D E F I N E S =============*/

/*============= D A T A =============*/
#if A2B_DEBUG_STORE_CONFIG
/*! TWI debug buffer  */
A2B_PAL_L3_DATA
ADI_A2B_TWI_DATA_DEBUG_CONFIG aDebugDataTwi;
#endif

/*!\var adi_twi_hDevice
 TWI driver handle */
A2B_PAL_L3_DATA
static ADI_A2B_TWI_INFO goTWIInfo;

/*!\var nBufferProcessCount
 Number of processed buffers  */
A2B_PAL_L1_DATA
static volatile a2b_UInt8 nBufferProcessCount = 0;

/*!\var nExpectedCallbackCount
 Total number of expected callbacks */
A2B_PAL_L1_DATA
static a2b_UInt8 nExpectedCallbackCount = 0;


/*!\var oTWITimer
 Timer object for TWI
static ADI_A2B_TIMER_HANDLER *pTWITimer;
*/

/*============= C O D E =============*/
/*
** Function Prototype section
*/
static void adi_a2b_TWICallbackFunction(void* pCBParam, a2b_UInt32 Event, void* pArg);
static a2b_UInt8 adi_a2b_TwiReadComplete(a2b_UInt8 nTWIDeviceNo);
static a2b_UInt8 adi_a2b_TwiWriteComplete(a2b_UInt8 nTWIDeviceNo);
static a2b_UInt32 adi_a2b_HandleError(a2b_Handle A2bTwiHandle ,  a2b_UInt8 bComplete );
static void adi_a2b_TWITimeoutHandler(ADI_A2B_TIMER_HANDLER_PTR pTWITimerHandlePtr);

/*
** Function Definition section
*/


/*****************************************************************************/
/*!
@brief  This API initializes the TWI module.TWI handles are initialized, preliminary device control
                    is established, and the TWI is reset and prepared for use.

@param [in]:nTWIDeviceNo  - TWI device number.
@param [in]:pUserArgument - User Argument for TWI open(Currently NULL is expected)
  
    
@return Return code
        -1: Failure
        -0: Success
        
\note I2C and TWI terms are used  interchangeably        
  
*/   
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_Handle adi_a2b_TwiOpen(A2B_ECB* ecb, void* pUserArgument)
{
    a2b_UInt32 nReturnValue = (a2b_UInt32)0;
    ADI_TWI_RESULT eTwiResult = ADI_TWI_SUCCESS;
    a2b_UInt32 nDummy;
    /*!< TWI driver memory */
    static a2b_UInt8 ganTwiDriverMemory[ADI_TWI_MEMORY_SIZE];

    /* SDP board specific */
    /* SET EBIU.D0 and D3 to enable TWI SEL_A*/
    *((unsigned short*)0x20200000u) = 0x0009u;

    /* open the TWI0 driver in master mode */
    eTwiResult = adi_twi_Open(ecb->palEcb.oTWIConfig.nTWIDeviceNo, ADI_TWI_MASTER, ganTwiDriverMemory, ADI_TWI_MEMORY_SIZE,
            &goTWIInfo.adi_twi_hDevice);

    /* Set bit rate of TWI0 to 100 kHz */
    if(ecb->palEcb.oTWIConfig.i2c_speed == A2B_I2C_BUS_SPEED_100KHZ)
    {
        eTwiResult = adi_twi_SetBitRate (goTWIInfo.adi_twi_hDevice, 100u);
    }
    else
    {
    	eTwiResult = adi_twi_SetBitRate (goTWIInfo.adi_twi_hDevice, 400u);
    }

    /* Set Duty cycle of TWI0 to 50 */
    eTwiResult = adi_twi_SetDutyCycle (goTWIInfo.adi_twi_hDevice, 50u);

    /* Set the pre-scaler for TWI0 to 10u */
    eTwiResult = adi_twi_SetPrescale (goTWIInfo.adi_twi_hDevice, 10u);

    eTwiResult = adi_twi_RegisterCallback(goTWIInfo.adi_twi_hDevice,(ADI_CALLBACK)&adi_a2b_TWICallbackFunction, (void*)0u);

    ecb->palEcb.oTWITimer.nTimerNo = TWI_TIMER;
    nDummy = (a2b_UInt32)&adi_a2b_TWITimeoutHandler;
    ecb->palEcb.oTWITimer.pCallbackhandle = (TIMER_CALL_BACK)nDummy;

    goTWIInfo.pEcb = ecb;
    nReturnValue = adi_a2b_TimerOpen(ecb->palEcb.oTWITimer.nTimerNo,(void *)&ecb->palEcb.oTWITimer);

    return (&goTWIInfo);

}

/*****************************************************************************/
/*!
@brief          This function closes the TWI device

@param [in]     nTWIDeviceNo    TWI device number

@return         Return code
                    - 0: Success
                    - 1: Failure
*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 adi_a2b_TwiClose(a2b_Handle hA2bTwiHandle)
{

    a2b_UInt32 nResult = 0u;
    ADI_TWI_RESULT eTwiResult = ADI_TWI_SUCCESS;
    a2b_UInt8 nTWIDeviceNo;

    ADI_A2B_TWI_INFO *pA2bTwiInfo =  (ADI_A2B_TWI_INFO *)hA2bTwiHandle;
    nTWIDeviceNo = pA2bTwiInfo->pEcb->palEcb.oTWIConfig.nTWIDeviceNo;
    /* SDP board specific */
    *((unsigned short*)0x20200000u) = 0x0000u; /* SET EBIU.D0 and D3 to enable TWI SEL_A*/

    nResult = adi_a2b_TimerClose(TWI_TIMER);
    eTwiResult = adi_twi_Close(pA2bTwiInfo->adi_twi_hDevice);


    return (a2b_UInt32)eTwiResult;
}

/*****************************************************************************/
/*!
@brief             This API reads 8 bit data from 8 bit register for the given device

@param [in]           nTWIDeviceNo      TWI device number
@param [in]           nDeviceAddress    TWI device address(7 bit) 
@param [in]           nRegAddress       8 bit register address
@param [in]           pData             Pointer to the reading data

@return        Return code
                - 0: Success
                - 1: Failure  
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
a2b_UInt32 adi_a2b_TwiRead(a2b_Handle A2bTwiHandle, a2b_UInt16 nDeviceAddress, a2b_UInt16 nRead, a2b_UInt8* pData)
{
    a2b_UInt32 nReturnValue = (a2b_UInt32)0 ;
    ADI_TWI_RESULT eTwiResult = ADI_TWI_SUCCESS;
    a2b_UInt8 nTWIDeviceNo;

    ADI_A2B_TWI_INFO *pA2bTwiInfo =  (ADI_A2B_TWI_INFO *)A2bTwiHandle;
    nBufferProcessCount = 0u;
    nTWIDeviceNo = pA2bTwiInfo->pEcb->palEcb.oTWIConfig.nTWIDeviceNo;
    eTwiResult = adi_twi_SetHardwareAddress (pA2bTwiInfo->adi_twi_hDevice, nDeviceAddress);
    eTwiResult = adi_twi_SubmitRxBuffer(pA2bTwiInfo->adi_twi_hDevice, pData, nRead , FALSE );
    nExpectedCallbackCount  = 1u;
    eTwiResult = adi_twi_Enable(pA2bTwiInfo->adi_twi_hDevice);

    /* Start Timer */
    pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout = (a2b_UInt8)0;
	nReturnValue = adi_a2b_TimerStart(TWI_TIMER,(TWI_TIMEOUT_PERIOD * (nRead)));

    while ( (!adi_a2b_TwiReadComplete( nTWIDeviceNo)) &&
    		(!pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout) )
    {
        /* Wait till time out or read complete */
    }
    nReturnValue = adi_a2b_TimerStop(TWI_TIMER);
    nReturnValue = adi_a2b_HandleError(A2bTwiHandle , adi_a2b_TwiReadComplete(nTWIDeviceNo));

    
#if A2B_DEBUG_STORE_CONFIG
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].eOp = 1u;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nRegAddr = 0u;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nTwiAddr = nDeviceAddress;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nDatVal = *pData;
    aDebugDataTwi.nNum++;
#endif
          
    return(nReturnValue);        
}

/******************************************************************************/
/*!
@brief  This function writes 8-bit data to 8-bit register

@param [in]     nTWIDeviceNo    TWI device number
@param [in]     nDeviceAddress  TWI device address(7 bit)
@param [in]     nRegAddress     8 bit register address
@param [in]     nData           Register value

@return        Return code
                    - 0: Success
                    - 1: Failure
*/
/*****************************************************************************/
A2B_PAL_L1_CODE
a2b_UInt32 adi_a2b_TwiWrite(a2b_Handle hA2bTwiHandle, a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf)
{
    a2b_UInt32 nReturnValue = (a2b_UInt32)0;
    ADI_TWI_RESULT eTwiResult = ADI_TWI_SUCCESS;
    nReturnValue = ((a2b_UInt8)TRUE);
    a2b_UInt8 nTWIDeviceNo;

    ADI_A2B_TWI_INFO *pA2bTwiInfo =  (ADI_A2B_TWI_INFO *)hA2bTwiHandle;
    nTWIDeviceNo = pA2bTwiInfo->pEcb->palEcb.oTWIConfig.nTWIDeviceNo;
    nBufferProcessCount = 0u;

    /* Set address  */
    eTwiResult = adi_twi_SetHardwareAddress(pA2bTwiInfo->adi_twi_hDevice, nDeviceAddress);

    /********************Not applicable while port into custom platform****/

    eTwiResult = adi_twi_SubmitTxBuffer(pA2bTwiInfo->adi_twi_hDevice, wBuf, nWrite, FALSE);
    eTwiResult = adi_twi_Enable(pA2bTwiInfo->adi_twi_hDevice);

    /* Start Timer */
    pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout = (a2b_UInt8)0;
    nReturnValue = adi_a2b_TimerStart(TWI_TIMER,(TWI_TIMEOUT_PERIOD * (nWrite)));

    while ( (!adi_a2b_TwiWriteComplete(nTWIDeviceNo) ) && (!pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout) )
    {
        /* Wait till time out or write complete */
    }
    nReturnValue = adi_a2b_TimerStop(TWI_TIMER);

    nReturnValue = adi_a2b_HandleError(hA2bTwiHandle, adi_a2b_TwiWriteComplete(nTWIDeviceNo));

#if A2B_DEBUG_STORE_CONFIG
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].eOp = 0u;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nRegAddr = wBuf[0];
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nTwiAddr = nDeviceAddress;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nDatVal = wBuf[1];
    aDebugDataTwi.nNum++;
#endif

    return(nReturnValue);

}

/*****************************************************************************/
/*!
@brief             This API reads 8 bit data from 8 bit register for the given device

@param [in]           nTWIDeviceNo      TWI device number
@param [in]           nDeviceAddress    TWI device address(7 bit)
@param [in]           nRegAddress       8 bit register address
@param [in]           pData             Pointer to the reading data

@return        Return code
                - 0: Success
                - 1: Failure
*/
/*****************************************************************************/
A2B_PAL_L1_CODE
uint32 adi_a2b_TwiWriteRead(a2b_Handle hA2bTwiHandle, a2b_UInt16 nDeviceAddress,
		a2b_UInt16 nWrite, a2b_UInt8* wBuf,
		a2b_UInt16 nRead, a2b_UInt8* rBuf)
{
    uint32 nReturnValue = (uint32)0 ;
    ADI_TWI_RESULT eTwiResult = ADI_TWI_SUCCESS;
    a2b_UInt8 nTWIDeviceNo;

    ADI_A2B_TWI_INFO *pA2bTwiInfo =  (ADI_A2B_TWI_INFO *)hA2bTwiHandle;
    nTWIDeviceNo = pA2bTwiInfo->pEcb->palEcb.oTWIConfig.nTWIDeviceNo;
    nBufferProcessCount = 0u;

    eTwiResult = adi_twi_SetHardwareAddress (pA2bTwiInfo->adi_twi_hDevice, nDeviceAddress);

    /********************Not applicable while port into custom platform****/

    eTwiResult = adi_twi_SubmitTxBuffer(pA2bTwiInfo->adi_twi_hDevice, wBuf, nWrite , TRUE );
    eTwiResult = adi_twi_SubmitRxBuffer(pA2bTwiInfo->adi_twi_hDevice, rBuf, nRead , FALSE );
    eTwiResult = adi_twi_Enable(pA2bTwiInfo->adi_twi_hDevice);
    nExpectedCallbackCount = 2u;
    /* Start Timer */
    pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout = (uint8)0;
	nReturnValue = adi_a2b_TimerStart(TWI_TIMER,(TWI_TIMEOUT_PERIOD * (nWrite+nRead)));

    while ( (!adi_a2b_TwiReadComplete(nTWIDeviceNo) ) && (!pA2bTwiInfo->pEcb->palEcb.oTWITimer.bTimeout) )
    {
        /* Wait till time out or read complete */
    }
    nReturnValue = adi_a2b_TimerStop(TWI_TIMER);
    nReturnValue = adi_a2b_HandleError(hA2bTwiHandle , adi_a2b_TwiReadComplete(nTWIDeviceNo));


#if A2B_DEBUG_STORE_CONFIG
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].eOp = 1u;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nRegAddr = wBuf[0];
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nTwiAddr = nDeviceAddress;
    aDebugDataTwi.aStoreDataVal[aDebugDataTwi.nNum].nDatVal = rBuf[0];
    aDebugDataTwi.nNum++;
#endif

    return(nReturnValue);
}

/*****************************************************************************/
/*!
@brief      This function returns TWI write completion status

@param [in]    nTWIDeviceNo    TWI device number
    
@return        Return code
                    - 1: Write is complete
                    - 0: Incomplete   
    
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
static a2b_UInt8 adi_a2b_TwiWriteComplete(a2b_UInt8 nTWIDeviceNo)
{
    a2b_UInt8 nReturnValue = 0u;

    if(nBufferProcessCount == 1u)
    {
    	nReturnValue = 1u;
    }

    return(nReturnValue);
}
 /****************************************************************************/
/*!
@brief  This function returns the TWI read completion status

@param [in]     nTWIDeviceNo  TWI device number
    
@return            Return code
                    - 1: Read is complete 
                    - 0: Incomplete   
    
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
static a2b_UInt8 adi_a2b_TwiReadComplete(a2b_UInt8 nTWIDeviceNo)
{
    a2b_UInt8 nReturnValue = 0u;

    if(nBufferProcessCount == nExpectedCallbackCount)
    {
    	nReturnValue = 1u;
    }
    return(nReturnValue);
}
 
/****************************************************************************/
/*!
    @brief          This function handles TWI timeout event. It sets 'Timeout' flag

    @param [in]     pTWITimerHandlePtr  Pointer to TWI Timer configuration structure

    @return         none    
*/                    
/*******************************************************************************/ 
A2B_PAL_L1_CODE
static void adi_a2b_TWITimeoutHandler(ADI_A2B_TIMER_HANDLER_PTR pTWITimerHandlePtr)
{
    a2b_UInt32 nRet = 0u;
    
#if TIME_OUT_ENABLE
    pTWITimerHandlePtr->bTimeout = 1u;
#endif    
    /* Reset timer0 */
    nRet= adi_a2b_TimerStop(pTWITimerHandlePtr->nTimerNo);
    
}
/*****************************************************************************/
/*!

@brief  Callback function for TWI events. It is invoked upon TWI events

@param [in]     pCBParam       TWI device handle
@param [in]     Event               TWI event
@param [in]     pArg                pointer to user argument
    
    
@return:
    void 
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
static void adi_a2b_TWICallbackFunction(void* pCBParam, a2b_UInt32 Event, void* pArg)
{
    a2b_UInt32 event = Event;

    switch (event) {
#if 1
        case ADI_TWI_EVENT_MSTRXMT_PROCESSED:
        	nBufferProcessCount++;
            break;
        case ADI_TWI_EVENT_MSTRRCV_PROCESSED:
        	nBufferProcessCount++;
            break;

#else
        case ADI_TWI_EVENT_BUFFER_PROCESSED:
    	nBufferProcessCount++;
        break;
#endif
            default:
        break;
    }


}
/*****************************************************************************/
/*!

@brief  This function handles TWI errors by re-opening the driver

@param [in]     nTWIDeviceNo        TWI device number 
@param [in]     bComplete           TWI operation completion flag
    
@return:
                Return code
                    - 1: TWI operation is failed 
                    - 0: TWI operation is complete and driver is re-opened
*/    
/*****************************************************************************/
A2B_PAL_L1_CODE
static a2b_UInt32 adi_a2b_HandleError(a2b_Handle A2bTwiHandle ,  a2b_UInt8 bComplete )
{
    a2b_UInt32 nRet = 0u , nReturnValue;
    nExpectedCallbackCount = 0u;
    nBufferProcessCount = 0u;
    ADI_A2B_TWI_INFO *pA2bTwiInfo =  (ADI_A2B_TWI_INFO *)A2bTwiHandle;

    if(bComplete == 0u)
    {
        nReturnValue = adi_a2b_TwiClose(A2bTwiHandle);
        (void)adi_a2b_TwiOpen(pA2bTwiInfo->pEcb, NULL);

#if A2B_PRINT_FOR_DEBUG            
        printf(" \n TWI Transaction Failure  ");
        printf(" \n ");
#endif 
        /* Return failure */ 
        nRet = 1u; 
        
    }
    
    return(nRet);
          
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

