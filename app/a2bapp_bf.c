/*******************************************************************************
Copyright (c) 2017 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************

   Name       : a2bapp_bf.c

   Description: This file is responsible for handling all the application level
                 functions

   Functions  : main()
                a2b_setup()
                a2b_monitor()


   Prepared &
   Reviewed by: Automotive Software and Systems team,
                IPDC, Analog Devices,  Bangalore, India

   @version: $Revision: 3626 $
   @date: $Date: 2016-11-027 14:04:13 +0530 $

******************************************************************************/
/*============= I N C L U D E S =============*/
#ifndef ESTEC_A2B_STACK_PORTING
//#include <sys/platform.h>
//#include "adi_initialize.h"

#include "a2bapp_bf.h"
#include "a2bapp.h"
#include "adi_a2b_externs.h"
#include "assert.h"
/*============= D E F I N E S =============*/
/*============= D A T A =============*/
/*============= C O D E =============*/


/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
#ifndef ESTEC_A2B_STACK_PORTING //Need to do !!!!
char __argv_string[] = "";
a2b_App_t gApp_Info;


void main(int argc, char *argv[])
{
	a2b_UInt32 nResult = 0;
	bool bRunFlag = true;

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* system/platform specific initialization */
	nResult = adi_a2b_SystemInit();
	if(nResult != 0)
	{
		assert(nResult == 0);
	}

	/* A2B Network Setup. Performs discovery and configuration of A2B nodes and its peripherals */
	nResult = a2b_setup(&gApp_Info);
    if (nResult)
    {
    	/* failed to setup A2B network */
    	assert(nResult == 0);
    }

    /*-----------------------------------------------------------*/
    /* Add your one time applications setup code here 			 */
    /*-----------------------------------------------------------*/


	while(1)
	{
		/* Monitor a2b network for faults and initiate re-discovery if enabled */
		nResult = a2b_fault_monitor(&gApp_Info);

		/*-----------------------------------------------------------*/
		/* Add your other continuous monitoring application code here */
		/*-----------------------------------------------------------*/

		/* condition to exit the program */
		if (nResult != 0)
		{
			bRunFlag = false;
		}

		/* tick keeps all process rolling.. so keep ticking */
		a2b_stackTick(gApp_Info.ctx);

	}

}
#endif
#endif //ESTEC_A2B_STACK_PORTING


