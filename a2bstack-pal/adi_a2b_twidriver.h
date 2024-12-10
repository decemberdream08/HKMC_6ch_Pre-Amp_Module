/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
* @file: adi_a2b_twidriver.h
* @brief: This file contains declarations required by TWI driver file.
* @version: $Revision: 3873 $
* @date: $Date: 2016-01-04 18:36:44 +0530 (Mon, 04 Jan 2016) $
* Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/

/*! \addtogroup TWI I2C / TWI
* @{
*/

/*! \addtogroup TWI_Configuration TWI Configuration
* @{
*/

#ifndef _ADI_A2B_TWIDRIVER_H_
#define _ADI_A2B_TWIDRIVER_H_

/*============= I N C L U D E S =============*/
#ifndef ESTEC_A2B_STACK_PORTING
//#include "adi_twi_int.h"
//#include "a2b\pal.h"
#endif
/*============= D E F I N E S =============*/

/*! Wait period in microsecond seconds for TWI time-out*/
#define TWI_TIMEOUT_PERIOD                	(1600u)

/*! Timer ID used by the TWI */
#define TWI_TIMER                         	(0u) /* FIXED to 0*/

/*! Block size of twi write is limited by this macro  */
#define MAX_NUMBER_TWI_BYTES              	(ADI_A2B_MAX_PERI_CONFIG_UNIT_SIZE) 

/*! Number of TWI devices used */
#define NO_TWI_DEVICES                      (1)

/*! RX callback */
#define TWI_RX_CALLBACK                     (0)

/*! TX callback */
#define TWI_TX_CALLBACK                     (1)

/*! Enable TWI abort on timer expire */
#define TIME_OUT_ENABLE                     (1u)

/*! TWI interface clock rate in KHz */
#define A2B_TWI_RATE                        (400u)      /* Use only 100KHz in 1.0 silicon with one level branch.
                                                           For details refer silicon Anamoly list - ID 18000016  */
																													 
																													 /*! A device handle used in all API functions to identify the TWI device. */
#if 1 //ESTEC_A2B_STACK_PORTING
typedef void *ADI_TWI_HANDLE;

/*! The amount of application supplied memory required by the TWI driver. */
#define ADI_TWI_MEMORY_SIZE (230u)
#endif

/*============= D A T A T Y P E S=============*/

/*! \struct ADI_A2B_TWI_ADDR_CONFIG
    TWI Sub address(Register) configuration structure
*/

typedef struct
{
    /*! Register address length/width in bytes(0/1/2/4 sub-address) */
    a2b_UInt32 nRegAddrLen;

    /*! Register Value (sub-address)  */
    a2b_UInt32 nRegVal;

}ADI_A2B_TWI_ADDR_CONFIG;


/*! \struct ADI_A2B_TWI_DATA_CONFIG
    TWI data configuration structure
*/
typedef struct
{
    /*! Data width in bytes(0/1/2/4)  */
    a2b_UInt32 nDataLen;

    /*! Register address length */
    a2b_UInt32 nDataCount;

    /*! value  */
    a2b_UInt32* paConfigData;

}ADI_A2B_TWI_DATA_CONFIG;

/*! \struct ADI_A2B_TWI_INFO
    TWI data configuration structure
*/
typedef struct
{
    /*! Driver TWI handle  */
	ADI_TWI_HANDLE adi_twi_hDevice;

    /*! Pointer to ECB struct */
	A2B_ECB       *pEcb;

    /*! TWI Driver Mem  */
    a2b_UInt8 ganTwiDriverMemory[ADI_TWI_MEMORY_SIZE];

}ADI_A2B_TWI_INFO;


/*======= P U B L I C P R O T O T Y P E S ========*/

/* TWI / I2C */
a2b_Handle adi_a2b_TwiOpen(A2B_ECB* ecb, void* pUserArgument);
a2b_UInt32 adi_a2b_TwiClose(a2b_Handle hA2bTwiHandle);
a2b_UInt32 adi_a2b_TwiRead(a2b_Handle A2bTwiHandle, a2b_UInt16 nDeviceAddress, a2b_UInt16 nRead, a2b_UInt8* pData);
a2b_UInt32 adi_a2b_TwiWrite(a2b_Handle hA2bTwiHandle, a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf);
a2b_UInt32 adi_a2b_TwiWriteRead(a2b_Handle hA2bTwiHandle, a2b_UInt16 nDeviceAddress,
		a2b_UInt16 nWrite, a2b_UInt8* wBuf,
		a2b_UInt16 nRead, a2b_UInt8* rBuf);


/*============= D A T A =============*/


#endif /* _ADI_A2B_TWIDRIVER_H_ */

/**
 @}
*/

/**
 @}
*/

/*
*
* EOF: $URL$
*
*/


