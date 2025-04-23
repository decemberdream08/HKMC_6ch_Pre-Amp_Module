/*******************************************************************************
Copyright (c) 2025 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
* @file: adi_a2b_busconfig.c
* @brief: This file contains A2B Schematic information
* @version: $Revision$
* @date: Tuesday, April 22, 2025-9:24:59 AM
* BCF Version - 1.0.0
* A2B DLL version- 19.4.3.0
* A2B Stack DLL version- 19.4.3.0
* SigmaStudio version- 4.07.000.1831
* Developed by: Automotive Software and Systems team, Bangalore, India
* THIS IS A SIGMASTUDIO GENERATED FILE AND SHALL NOT BE MODIFIED OUTSIDE OF SIGMASTUDIO
*****************************************************************************/

/*! \addtogroup Target_Independent
* @{
*/

/*! \addtogroup Bus_Configuration Bus Configuration
* @{
*/

#include "adi_a2b_datatypes.h"
#include "adi_a2b_graphdata.h"
#include "adi_a2b_busconfig.h"

#ifdef A2B_STACK_CODE_FROM_ADI
static ADI_A2B_COMPR_MASTER_SLAVE_CONFIG sChainConfig0;
static a2b_Byte  gA2bNetworkChain0[];
static ADI_A2B_NODE_PERICONFIG_DATA sChain0_Slave0PeriConfig;

ADI_A2B_MEM_BCF_CONST_DATA
 static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig0;

ADI_A2B_MEM_BCF_CONST_DATA
 static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig1;

ADI_A2B_MEM_BCF_CONST_DATA
 static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig2;

ADI_A2B_MEM_BCF_CONST_DATA
 static ADI_A2B_STREAM_SETTINGS sChain0MstrStreamCfg;

ADI_A2B_MEM_BCF_CONST_DATA
 static A2B_PERIPHERAL_DEVICE_CONFIG  sChain0_Slave0_PeriConfig0;
static ADI_A2B_PERI_CONFIG_UNIT  gaPeriCfg_0_6A_Unit[4];

ADI_A2B_MEM_BCF_CONST_DATA
 static ADI_A2B_STREAM_SETTINGS sChain0_Slave0StreamCfg;


ADI_A2B_MEM_BCF_DATA

/* BUS CONFIGURATION */ 
ADI_A2B_COMPR_BCD sCmprBusDescription = 
 { 
	/* Number of master nodes/daisy chains in the network */ 
	.nNumMasterNode  = 1u, 
 
	/* Array of Master-slave daisy chains */ 
 	.apNetworkconfig = {  &sChainConfig0 }, 

	/* Network control guidance */ 
	.sTargetProperties    = 
 	{ 
		/* Discovery Mode Selection */ 
		.eDiscoveryMode     = A2B_SIMPLE_DISCOVERY,

		/* PLL Lock Time (tPLK). Delay (in msec) to wait after a software reset and before starting discovery. */ 
		.nDiscoveryStartDelay     = 25,

		/*  Enable/Disable  Line diagnostics (Post discovery) */ 
		.bLineDiagnostics   = A2B_DISABLED,

		/*  Enable/Disable automatic discovery upon critical faults (during discovery process) */ 
		.bAutoDiscCriticalFault = A2B_DISABLED,

		/*  Number of automatic discovery attempts (during discovery process) */ 
		.nAttemptsCriticalFault = 0,

		/* Auto-rediscovery upon post discovery line fault */ 
		.bAutoRediscOnFault = A2B_DISABLED,

		/*! Interval (in milliseconds) between re-discovery attempt during line fault */ 
		.nRediscInterval = 100,

		/*! Enable Cross Talk Fix, applicable only for AD2425 series */ 
		.bCrossTalkFix = A2B_DISABLED,

		/*! Enable override bus self discovery */ 
		/*! Number of peripheral devices connected to Target */
		.nNumPeriDevice = 3,

		/*! Array of peripheral configuration pointers */
 		.apPeriConfig = { 	&Target_PeriConfig0, &Target_PeriConfig1, &Target_PeriConfig2 }
 	}, 

 };

 /************************************************* CHAIN 0 DESCRIPTION  ********************************************************************************/

 /* MASTER-SLAVE DAISY CHAIN0 */ 
 
ADI_A2B_MEM_BCF_DATA 
static ADI_A2B_COMPR_MASTER_SLAVE_CONFIG sChainConfig0= 
 { 
 	/*! Number of Slave nodes */ 
	.nNumSlaveNode = 1, 
 
	/*! Compressed network info */ 
	.pgA2bNetwork = gA2bNetworkChain0, 
 
	/*! Number of byte */ 
	.gA2bNetworkLen = 164, 
 
	/*! Array of node peripheral configuration pointers  */ 
	.apNodePericonfig = { &sChain0_Slave0PeriConfig}, 

	/*! Master node stream configuration  */ 
	.pMstrNodeStreamCfg = &sChain0MstrStreamCfg, 

	/*! Array of Slave node stream configuration  */ 
	.apSlvNodeStreamCfg = {&sChain0_Slave0StreamCfg}, 


 };

//KMS241230_1 : To use A2B Bus as Master, we need to check AD2428 version on Master node. current version is 1.0.
//Line 10 : Version is (0x01) on this line "0xAD, 0x01, 0x10, 0x28, 0x18, (0x01), 0x50, 0x00,". If you have to use version 0, you need to change (0x00).
//KMS250314_1 : To use A2B Bus as Master, we can define Master AD2428 I2C address with (0x68). Now it's 0x68.
//Line 2 : 0x00, 0x00, 0x00, 0x00, 0x10, (0x68), 0x1A, 0x0C, 
 static a2b_Byte  gA2bNetworkChain0[]  = {
0x0A, 0x0A, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x15, 
0x00, 0x00, 0x00, 0x00, 0x10, 0x68, 0x1A, 0x0C, 
0x08, 0x00, 0x10, 0x02, 0x18, 0x01, 0x20, 0x00, 
0x28, 0x01, 0x30, 0x19, 0x22, 0x40, 0x08, 0x01, 
0x12, 0x09, 0x20, 0x04, 0x30, 0x83, 0x01, 0x38, 
0x44, 0x48, 0x01, 0x1A, 0x06, 0x08, 0x77, 0x10, 
0x78, 0x18, 0x0F, 0x2A, 0x06, 0x18, 0x62, 0x20, 
0x19, 0x58, 0x00, 0x32, 0x05, 0x20, 0x80, 0x01, 
0x38, 0x00, 0x38, 0x01, 0x40, 0x00, 0x4A, 0x07, 
0x08, 0xAD, 0x01, 0x10, 0x28, 0x18, 0x01, 0x50, 
0x00, 0x5A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x60, 
0x00, 0x8A, 0x01, 0x02, 0x08, 0x01, 0x22, 0x42, 
0x08, 0x02, 0x12, 0x07, 0x08, 0x02, 0x10, 0x02, 
0x30, 0x83, 0x01, 0x1A, 0x07, 0x08, 0x77, 0x10, 
0x7F, 0x20, 0xEF, 0x01, 0x2A, 0x07, 0x18, 0x62, 
0x20, 0x91, 0x01, 0x48, 0x18, 0x32, 0x0A, 0x08, 
0x01, 0x18, 0xC0, 0x01, 0x38, 0x00, 0x50, 0xC1, 
0x01, 0x38, 0x01, 0x40, 0x00, 0x4A, 0x07, 0x08, 
0xAD, 0x01, 0x10, 0x28, 0x18, 0x00, 0x50, 0x02, 
0x60, 0x02, 0x82, 0x01, 0x02, 0x10, 0x00, 0x8A, 
0x01, 0x00, 0x28, 0x00};
/************************************************* END OF Chain 0 DESCRIPTION ********************************************************************************//* CHAIN0 SLAVE0 PERIPHERALS*/ 
 static ADI_A2B_NODE_PERICONFIG_DATA sChain0_Slave0PeriConfig = 
 { 
	 /*! Number of peripheral devices connected  */
	.nNumPeriDevice = 1,

	 /*! Array of peripheral configuration pointers */ 
	.apNodePeriDeviceConfig = {	 &sChain0_Slave0_PeriConfig0, 	},


};
/************************************************** START OF PERIPHERALS CONNECTED TO TARGET PROCESSOR  ********************************************************************************  */

/* Peripheral - 0*/

ADI_A2B_MEM_BCF_CONST_DATA
static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig0=
{
 /*! I2C interface status  */ 
	 .bI2CInterfaceUse = A2B_ENABLED, 

	/*7 bit I2C address */ 
	.nI2Caddr = 0x38, 

	/* Device type -audio source/sink/host  */ 
	.eDeviceType = A2B_AUDIO_HOST, 

	/* Tx0 Pin in use */
	.bUseTx0 = A2B_DISABLED, 

	/* Rx0 Pin in use */
	.bUseRx0 = A2B_DISABLED, 

	/* Tx1 Pin in use */
	.bUseTx1 = A2B_DISABLED, 

	/* Rx1 Pin in use */
	.bUseRx1 = A2B_DISABLED, 

	/* No of Tx0 channels  */ 
	.nChTx0 = 2, 

	/* No of Rx0 channels  */ 
	.nChRx0 = 0, 

	/* No of Tx1 channels  */ 
	.nChTx1 = 0, 

	/* No of Rx1 channels  */ 
	.nChRx1 = 0, 

	/* Number of configuration units  */ 
	.nNumPeriConfigUnit = 0, 

	.paPeriConfigUnit = NULL_PTR 
 };

/* Peripheral - 1*/

ADI_A2B_MEM_BCF_CONST_DATA
static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig1=
{
 /*! I2C interface status  */ 
	 .bI2CInterfaceUse = A2B_ENABLED, 

	/*7 bit I2C address */ 
	.nI2Caddr = 0x50, 

	/* Device type -audio source/sink/host  */ 
	.eDeviceType = A2B_GENERIC_I2C_DEVICE, 

	/* Tx0 Pin in use */
	.bUseTx0 = A2B_DISABLED, 

	/* Rx0 Pin in use */
	.bUseRx0 = A2B_DISABLED, 

	/* Tx1 Pin in use */
	.bUseTx1 = A2B_DISABLED, 

	/* Rx1 Pin in use */
	.bUseRx1 = A2B_DISABLED, 

	/* No of Tx0 channels  */ 
	.nChTx0 = 0, 

	/* No of Rx0 channels  */ 
	.nChRx0 = 0, 

	/* No of Tx1 channels  */ 
	.nChTx1 = 0, 

	/* No of Rx1 channels  */ 
	.nChRx1 = 0, 

	/* Number of configuration units  */ 
	.nNumPeriConfigUnit = 0, 

	.paPeriConfigUnit = NULL_PTR 
 };

/* Peripheral - 2*/

ADI_A2B_MEM_BCF_CONST_DATA
static A2B_PERIPHERAL_DEVICE_CONFIG  Target_PeriConfig2=
{
 /*! I2C interface status  */ 
	 .bI2CInterfaceUse = A2B_ENABLED, 

	/*7 bit I2C address */ 
	.nI2Caddr = 0x39, 

	/* Device type -audio source/sink/host  */ 
	.eDeviceType = A2B_GENERIC_I2C_DEVICE, 

	/* Tx0 Pin in use */
	.bUseTx0 = A2B_DISABLED, 

	/* Rx0 Pin in use */
	.bUseRx0 = A2B_DISABLED, 

	/* Tx1 Pin in use */
	.bUseTx1 = A2B_DISABLED, 

	/* Rx1 Pin in use */
	.bUseRx1 = A2B_DISABLED, 

	/* No of Tx0 channels  */ 
	.nChTx0 = 0, 

	/* No of Rx0 channels  */ 
	.nChRx0 = 0, 

	/* No of Tx1 channels  */ 
	.nChTx1 = 0, 

	/* No of Rx1 channels  */ 
	.nChRx1 = 0, 

	/* Number of configuration units  */ 
	.nNumPeriConfigUnit = 0, 

	.paPeriConfigUnit = NULL_PTR 
 };

/************************************************** END OF PERIPHERALS CONNECTED TO TARGET PROCESSOR  ********************************************************************************  */

/************************************************** START OF CHAIN 0 MASTER 0 STREAM DESCRIPTION ********************************************************************************  */


ADI_A2B_MEM_BCF_CONST_DATA
static ADI_A2B_STREAM_SETTINGS sChain0MstrStreamCfg =
 	{
		/*! No of Streams sourced (added) by the node */
		.nNumSrcStreams = 0x0u ,

		/*! Source Streams Info */
		.pSrcStreams = { 	0x0u	},

		/*! No of Streams sinked (used) by the node */
		.nNumSnkStreams = 0x0u ,

		/*! Sink Streams Info */
		.pSnkStreams = { 	0x0u	},


	};
/************************************************** END OF CHAIN 0 MASTER 0 STREAM DESCRIPTION ********************************************************************************  */

/************************************************** START OF CHAIN 0 SLAVE0 PERIPHERAL DESCRIPTION ********************************************************************************  */

/* Peripheral - 0*/

ADI_A2B_MEM_BCF_CONST_DATA
static A2B_PERIPHERAL_DEVICE_CONFIG  sChain0_Slave0_PeriConfig0=
{
 /*! I2C interface status  */ 
	.bI2CInterfaceUse = A2B_ENABLED, 

	/*7 bit I2C address */ 
	.nI2Caddr = 0x6A, 

	/* Device type -audio source/sink/host  */ 
	.eDeviceType = A2B_AUDIO_SOURCE_SINK, 

	/* Tx0 Pin in use */
	.bUseTx0 = A2B_ENABLED, 

	/* Rx0 Pin in use */
	.bUseRx0 = A2B_ENABLED, 

	/* Tx1 Pin in use */
	.bUseTx1 = A2B_DISABLED, 

	/* Rx1 Pin in use */
	.bUseRx1 = A2B_DISABLED, 

	/* No of Tx0 channels  */ 
	.nChTx0 = 0, 

	/* No of Rx0 channels  */ 
	.nChRx0 = 2, 

	/* No of Tx1 channels  */ 
	.nChTx1 = 0, 

	/* No of Rx1 channels  */ 
	.nChRx1 = 0, 

	/* Number of configuration units  */ 
	.nNumPeriConfigUnit = 4, 

	/* Pointer to configuration units  */ 
	.paPeriConfigUnit =  &gaPeriCfg_0_6A_Unit[0] 
 };

/************************************************** END OF CHAIN 0 SLAVE0 PERIPHERAL DESCRIPTION ********************************************************************************  */

/************************************************** START OF CHAIN 0 SLAVE 0 STREAM DESCRIPTION ********************************************************************************  */


ADI_A2B_MEM_BCF_CONST_DATA
static ADI_A2B_STREAM_SETTINGS sChain0_Slave0StreamCfg =
 	{
		/*! No of Streams sourced (added) by the node */
		.nNumSrcStreams = 0x0u ,

		/*! Source Streams Info */
		.pSrcStreams = { 	0x0u	},

		/*! No of Streams sinked (used) by the node */
		.nNumSnkStreams = 0x0u ,

		/*! Sink Streams Info */
		.pSnkStreams = { 	0x0u	},

		/*! No of Streams passing through this node */
		.nNumPassThruStreams = 0x0u ,

		/*! Pass Through Streams Info */
		.pPassThruStreams = { 	0x0u	},


	};
/************************************************** END OF CHAIN 0 SLAVE 0 STREAM DESCRIPTION ********************************************************************************  */


 ADI_A2B_MEM_PERI_CONFIG_CONST_DATA 
static	uint8 gaPeriCfg_0_6A_0_Data[1] =
{
	0x10u	
};

 ADI_A2B_MEM_PERI_CONFIG_CONST_DATA 
static	uint8 gaPeriCfg_0_6A_1_Data[1] =
{
	0x44u	
};

 ADI_A2B_MEM_PERI_CONFIG_CONST_DATA 
static	uint8 gaPeriCfg_0_6A_2_Data[1] =
{
	0x0u	
};

 ADI_A2B_MEM_PERI_CONFIG_CONST_DATA 
static	uint8 gaPeriCfg_0_6A_3_Data[1] =
{
	0xFFu	
};



ADI_A2B_MEM_PERI_CONFIG_UNIT
static	ADI_A2B_PERI_CONFIG_UNIT gaPeriCfg_0_6A_Unit[4] =
{
	{A2B_WRITE_OP,	0x1u,	0x0u,	0x1u,	0x1u,	&gaPeriCfg_0_6A_0_Data[0],	0x0u },
	{A2B_WRITE_OP,	0x1u,	0x3u,	0x1u,	0x1u,	&gaPeriCfg_0_6A_1_Data[0],	0x0u },
	{A2B_WRITE_OP,	0x1u,	0x4u,	0x1u,	0x1u,	&gaPeriCfg_0_6A_2_Data[0],	0x0u },
	{A2B_WRITE_OP,	0x1u,	0x5u,	0x1u,	0x1u,	&gaPeriCfg_0_6A_3_Data[0],	0x0u }
};

#endif //#ifdef A2B_STACK_CODE_FROM_ADI
