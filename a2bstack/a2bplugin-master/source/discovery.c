/*=============================================================================
 *
 * Project: a2bstack
 *
 * Copyright (c) 2015 - 2023Analog Devices Inc. All Rights Reserved.
 * This software is subject to the terms and conditions of the license set 
 * forth in the project LICENSE file. Downloading, reproducing, distributing or 
 * otherwise using the software constitutes acceptance of the license. The 
 * software may not be used except as expressly authorized under the license.
 *
 *=============================================================================
 *
 * \file:   discovery.c
 * \brief:  The implementation of an A2B master plugin discovery process.
 *
 *=============================================================================
 */
/*! \addtogroup Network_Configuration
 *  @{
 */

/** @defgroup Discovery_and_Node_Configuration Discovery and Node Configuration
 *
 * This module discovers the node and configures the nodes based on the BDD configuration
 *
 */

/*! \addtogroup Discovery_and_Node_Configuration
 *  @{
 */

/*======================= I N C L U D E S =========================*/
#include "a2b\pluginapi.h"
#include "a2b\error.h"
#include "a2b\conf.h"
#include "a2b\defs.h"
#include "a2b\util.h"
#include "a2b\msg.h"
#include "a2b\msgrtr.h"
#include "a2b\trace.h"
#include "a2b\stack.h"
#include "a2b\regdefs.h"
#include "a2b\interrupt.h"
#include "a2b\stackctxmailbox.h"
#include "a2b\a2b_i2c.h"
#include "a2b\timer.h"
#include "a2b\seqchart.h"
#include "a2bplugin-master\plugin.h"
#include "discovery.h"
#include "periphcfg.h"
#include "override.h"
#include "a2b\audio.h"
#if defined _TESSY_INCLUDES_ || defined A2B_SS_STACK
#include "msg_priv.h"
#include "a2b\msgtypes.h"
#include "timer_priv.h"
#include "stackctx.h"
#include "stack_priv.h"
#endif	/* _TESSY_INCLUDES_ */


#ifdef A2B_STACK_CODE_FROM_ADI
/*======================= D E F I N E S ===========================*/

#define A2B_MASTER_NODEBDDIDX   (0u)

/** Delay (in msec) for a node discovery */
#define A2B_DISCOVERY_DELAY     (50u)

/** Delay (in msec) to wait after a software reset */
#define A2B_SW_RESET_DELAY      (25u)


#define A2B_DEINIT_DSCVREY_END  (1u)
#define A2B_DEINIT_START        (2u)

/** Define if a search for a plugin to manage a node should be done
 * AFTER the node itself has been completely initialized. If undefined
 * then a search for the managing plugin (including opening the plugin)
 * will occur immediately after the slave node has been discovered but
 * BEFORE the node itself has been initialized.
 */
#if 1
#define FIND_NODE_HANDLER_AFTER_NODE_INIT   (1u)
#else
#undef FIND_NODE_HANDLER_AFTER_NODE_INIT
#endif

#ifdef A2B_QAC
#pragma PRQA_NO_SIDE_EFFECTS a2b_isAd242xChip
#endif
/*======================= L O C A L  P R O T O T Y P E S  =========*/

typedef enum
{
    TIMER_DSCVRY,
    TIMER_RESET
} a2b_dscvryTimer;


/*======================= D A T A  ================================*/


/*======================= M A C R O S =============================*/

#define A2B_HAS_EEPROM( plugin, nodeAddr ) \
        ((a2b_UInt32)((plugin)->discovery.hasEeprom) & ((a2b_UInt32)1u << (a2b_UInt32)(nodeAddr)))

#define A2B_HAS_PLUGIN( plugin, nodeAddr ) \
        ((a2b_UInt32)((plugin)->discovery.hasPlugin) & ((a2b_UInt32)1u << (a2b_UInt32)(nodeAddr)))

#define A2B_NEEDS_PLUGIN_INIT( plugin, nodeAddr ) \
        ((a2b_UInt32)((plugin)->discovery.needsPluginInit) & ((a2b_UInt32)1u << (a2b_UInt32)(nodeAddr)))

#define A2B_HAS_SEARCHED_FOR_HANLDER(plugin, nodeAddr ) \
        ((a2b_UInt32)((plugin)->discovery.hasSearchedForHandler) & ((a2b_UInt32)1u << (a2b_UInt32)(nodeAddr)))

/* Maps slave node address to an internal slave array index */
#define A2B_MAP_SLAVE_ADDR_TO_INDEX(a)  ((a2b_UInt16)(a))
/* Maps slave array index to slave node address */
#define A2B_MAP_SLAVE_INDEX_TO_ADDR(i)  ((a2b_Int16)(i))

/*======================= C O D E =================================*/

static a2b_Int32 	a2b_dscvryNodeComplete(a2b_Plugin* plugin, a2b_Int16 nodeAddr, a2b_Bool bDoEepromCfg, a2b_UInt32* errCode);
static void 		a2b_dscvryNetComplete(a2b_Plugin* plugin);
static a2b_Bool 	a2b_dscvryPreMasterInit(a2b_Plugin* plugin);
static a2b_Bool 	a2b_dscvryPreSlaveInit(a2b_Plugin* plugin);
static a2b_Int32 	a2b_dscvryReset(a2b_Plugin* plugin);
static void 		a2b_dscvryFindNodeHandler(a2b_Plugin* plugin, a2b_UInt16 slaveNodeIdx);
static void 		a2b_dscvryInitTdmSettings(a2b_Plugin* plugin,a2b_Int16 nodeAddr);
static void 		a2b_dscvryDeinitPluginComplete( struct a2b_Msg* msg, a2b_Bool isCancelled);
static void 		a2b_dscvryInitPluginComplete_NoEeprom(struct a2b_Msg* msg, a2b_Bool  isCancelled);
static void 		a2b_dscvryInitPluginComplete_EepromComplete(struct a2b_Msg* msg, a2b_Bool isCancelled);
static void 		a2b_onDiscTimeout(struct a2b_Timer *timer, a2b_Handle userData);
static void 		a2b_onResetTimeout(struct a2b_Timer *timer, a2b_Handle userData);
static a2b_Bool 	a2b_dscvryStartTimer(a2b_Plugin* plugin, a2b_dscvryTimer type);
static a2b_Bool 	a2b_dscvryNodeInterruptInit(a2b_Plugin* plugin, a2b_Int16 nodeBddIdx);
static const a2b_NodeSignature* a2b_getNodeSignature(a2b_Plugin* plugin, a2b_Int16 nodeAddr);
static a2b_Bool 	a2b_SimpleModeChkNodeConfig(a2b_Plugin* plugin);
static void 		adi_a2b_ReConfigSlot(a2b_Plugin* plugin, a2b_Int16 nodeAddr);
static a2b_HResult 	a2b_FinalMasterSetup(a2b_Plugin* plugin, a2b_Int16 nodeAddr);
static a2b_Bool 	adi_a2b_ConfigureNodePeri(a2b_Plugin* plugin, a2b_Int16 dscNodeAddr);
static a2b_Bool		adi_a2b_ConfigNodeOptimizAdvancedMode(a2b_Plugin* plugin, a2b_Int16 dscNodeAddr);
static a2b_UInt32 	a2b_dscvryInitPlugin(a2b_Plugin* plugin, a2b_Int16  nodeAddr, a2b_MsgCallbackFunc completeCallback);
static void 		a2b_dscvryDeinitPlugin(a2b_Plugin* plugin, a2b_UInt32  mode);
static a2b_HResult 	a2b_ConfigSpreadSpectrum(a2b_Plugin* plugin, a2b_Int16 nodeAddr);
static a2b_Bool		a2b_isAd242xChip(a2b_UInt8 vendorId, a2b_UInt8 productId);
static a2b_Bool		a2b_isCrossTalkFixApply(a2b_UInt8 vendorId, a2b_UInt8 productId);
static a2b_Bool 	a2b_stackSupportedNode(a2b_UInt8 vendorId, a2b_UInt8 productId, a2b_UInt8 version);
static a2b_Bool 	a2b_dscvryCustomAuthFrmMem(a2b_Plugin* plugin, a2b_NodeSignature nodeSig);
static a2b_Bool 	a2b_dscvryCustomAuthFrmGpio(a2b_Plugin* plugin, a2b_NodeSignature nodeSig);
#ifdef A2B_FEATURE_COMM_CH
static a2b_Bool 	a2b_dscvryNodeMailboxInit (a2b_Plugin* plugin, a2b_Int16 nodeBddIdx);
static a2b_Bool 	a2b_dscvryPostAuthViaCommCh(a2b_Plugin* plugin);
static a2b_Bool 	a2b_dscvryStartCommChAuthTimer(a2b_Plugin* plugin, a2b_UInt16 delay);
static void 		a2b_onCommChAuthTimeout(struct a2b_Timer *timer, a2b_Handle userData);
static a2b_Bool 	a2b_dscvryCustomAuthFrmCommCh(a2b_Plugin* plugin, a2b_NodeSignature nodeSig);
#endif	/* A2B_FEATURE_COMM_CH */
static a2b_Bool 	sendNodeDscvryNotification(a2b_Plugin *plugin, a2b_UInt32 discCode, a2b_Int16 dscNodeIdx);
static void         a2b_I2CErrorReported(struct a2b_Msg* msg, a2b_Handle userData);
static void         a2b_ReportI2CError(a2b_Plugin *plugin, a2b_Int16 nodeAddr);
/*!****************************************************************************
*
*  \b              a2b_dscvryInitTdmSettings
*
*  Initialize the master plugins TDM Settings for a specific node.
*
*  \param          [in]    plugin
*  \param          [in]    nodeAddr
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryInitTdmSettings
    (
    a2b_Plugin*         plugin,
    a2b_Int16           nodeAddr
    )
{
    a2b_Int16           nodeBddIdx = nodeAddr+1;
    const bdd_Node      *bddNodeObj;
    a2b_TdmSettings*    tdmSettings;
    a2b_UInt32          reg;

    (void)a2b_memset( &plugin->pluginTdmSettings, 0, sizeof(a2b_TdmSettings) );

    if ( nodeBddIdx > (a2b_Int16)plugin->bdd->nodes_count- (a2b_Int16)1)
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\ra2b_dscvryInitTdmSettingsInvalid nodeAddr");
#else
        A2B_DSCVRY_ERROR0( plugin->ctx, "a2b_dscvryInitTdmSettings", 
                           "Invalid nodeAddr" );
#endif
        return;
    }

    bddNodeObj  = &plugin->bdd->nodes[nodeBddIdx];
    tdmSettings = &plugin->pluginTdmSettings;

    tdmSettings->networkSampleRate =
                                 ((a2b_UInt16)plugin->bdd->sampleRate & (a2b_UInt16)0xFFFF);

    if ( bddNodeObj->i2cI2sRegs.has_i2srate )
    {
        switch ( (bddNodeObj->i2cI2sRegs.i2srate & A2B_BITM_I2SRATE_I2SRATE) )
        {
        case A2B_ENUM_I2SRATE_1X_SFF:
            tdmSettings->sampleRateMultiplier = 1u;
            break;
        case A2B_ENUM_I2SRATE_2X_SFF:
            tdmSettings->sampleRateMultiplier = 2u;
            break;
        case A2B_ENUM_I2SRATE_4X_SFF:
            tdmSettings->sampleRateMultiplier = 4u;
            break;
        /* TODO: We need to handle the Reduced Rate (RRDIV) enumerated
         * rates introduced by the AD242X chips. This likely means we will
         * need to to enumerate the possible values and include the RRDIV
         * values itself.
         */
        case A2B_ENUM_I2SRATE_SFF_RRDIV:
            tdmSettings->sampleRateMultiplier = 3u;
            break;
        case A2B_ENUM_I2SRATE_SFF_DIV_4:
            tdmSettings->sampleRateMultiplier = 2u;
            break;
        case A2B_ENUM_I2SRATE_SFF_DIV_2:
            tdmSettings->sampleRateMultiplier = 1u;
            break;
        default:
            tdmSettings->sampleRateMultiplier = 1u;
            break;

        }
    }

    switch ( bddNodeObj->i2cI2sRegs.i2sgcfg & A2B_BITM_I2SGCFG_TDMMODE )
    {
    case A2B_ENUM_I2SGCFG_TDM2:
        tdmSettings->tdmMode = 2u;
        break;
    case A2B_ENUM_I2SGCFG_TDM4:
        tdmSettings->tdmMode = 4u;
        break;
    case A2B_ENUM_I2SGCFG_TDM8:
        tdmSettings->tdmMode = 8u;
        break;
    case A2B_ENUM_I2SGCFG_TDM16:
        tdmSettings->tdmMode = 16u;
        break;
    case A2B_ENUM_I2SGCFG_TDM32:
        tdmSettings->tdmMode = 32u;
        break;
    default:
        tdmSettings->tdmMode = 2u;
        break;
    }

    reg = bddNodeObj->i2cI2sRegs.i2sgcfg;
    tdmSettings->slotSize    = (reg & A2B_BITM_I2SGCFG_TDMSS ) ? 16u : 32u;
    tdmSettings->halfCycle   = (a2b_Bool)(( reg & A2B_BITM_I2SGCFG_ALT ) ==
                                  A2B_ENUM_I2SGCFG_ALT_EN );
    tdmSettings->prevCycle   = (a2b_Bool)(( reg & A2B_BITM_I2SGCFG_EARLY ) ==
                                  A2B_ENUM_I2SGCFG_EARLY_EN );
    tdmSettings->fallingEdge = (a2b_Bool)(( reg & A2B_BITM_I2SGCFG_INV ) ==
                                  A2B_ENUM_I2SGCFG_INV_EN );

    reg = bddNodeObj->i2cI2sRegs.i2scfg;
    tdmSettings->rx.invertBclk = (a2b_Bool)(( reg & A2B_BITM_I2SCFG_RXBCLKINV ) ==
                                    A2B_ENUM_I2SCFG_RXBCLKINV_EN );
    tdmSettings->rx.interleave = (a2b_Bool)(( reg & A2B_BITM_I2SCFG_RX2PINTL ) ==
                                    A2B_ENUM_I2SCFG_RX2PINTL_EN );
    tdmSettings->rx.pinEnabled = (a2b_UInt8)(( reg & (A2B_BITM_I2SCFG_RX0EN |
                               A2B_BITM_I2SCFG_RX1EN)) >> A2B_BITP_I2SCFG_RX0EN);
    
    if ( bddNodeObj->i2cI2sRegs.has_i2srxoffset )
    {
        switch ( bddNodeObj->i2cI2sRegs.i2srxoffset & 
                 A2B_BITM_I2SRXOFFSET_RXOFFSET )
        {
        case A2B_ENUM_I2SRXOFFSET_00:
            tdmSettings->rx.offset = 0u;
            break;
        case A2B_ENUM_I2SRXOFFSET_62:
            tdmSettings->rx.offset = 62u;
            break;
        case A2B_ENUM_I2SRXOFFSET_63:
            tdmSettings->rx.offset = 63u;
            break;
        default:
            tdmSettings->rx.offset = 0u;
            break;
        }
    }
    
    tdmSettings->tx.invertBclk = (a2b_Bool)(( reg & A2B_BITM_I2SCFG_TXBCLKINV ) ==
                                    A2B_ENUM_I2SCFG_TXBCLKINV_EN );
    tdmSettings->tx.interleave = (a2b_Bool)(( reg & A2B_BITM_I2SCFG_TX2PINTL ) ==
                                    A2B_ENUM_I2SCFG_TX2PINTL_EN );
    tdmSettings->tx.pinEnabled = (a2b_UInt8)((reg & (A2B_BITM_I2SCFG_TX0EN |
                              A2B_BITM_I2SCFG_TX1EN) ) >> A2B_BITP_I2SCFG_TX0EN);

    if ( bddNodeObj->i2cI2sRegs.has_i2stxoffset )
    {
        switch ( bddNodeObj->i2cI2sRegs.i2stxoffset & 
                 A2B_BITM_I2STXOFFSET_TXOFFSET )
        {
        case A2B_ENUM_I2STXOFFSET_TXOFFSET_00:
            tdmSettings->tx.offset = 0u;
            break;
        case A2B_ENUM_I2STXOFFSET_TXOFFSET_01:
            tdmSettings->tx.offset = 1u;
            break;
        case A2B_ENUM_I2STXOFFSET_TXOFFSET_62:
            tdmSettings->tx.offset = 62u;
            break;
        case A2B_ENUM_I2STXOFFSET_TXOFFSET_63:
            tdmSettings->tx.offset = 63u;
            break;
        default:
            tdmSettings->tx.offset = 0u;
            break;
        }

        tdmSettings->tx.triStateBefore = (a2b_Bool)(( bddNodeObj->i2cI2sRegs.i2stxoffset &
                                           A2B_BITM_I2STXOFFSET_TSBEFORE ) ==
                                           A2B_ENUM_I2STXOFFSET_TSBEFORE_EN );
        tdmSettings->tx.triStateAfter  = (a2b_Bool)(( bddNodeObj->i2cI2sRegs.i2stxoffset &
                                           A2B_BITM_I2STXOFFSET_TSAFTER ) ==
                                           A2B_ENUM_I2STXOFFSET_TSAFTER_EN );
    }
} /* a2b_dscvryInitTdmSettings */


/*!****************************************************************************
*
*  \b              a2b_dscvryDeinitPluginComplete
*
*  Callback when A2B_MSGREQ_PLUGIN_PERIPH_DEINIT has completed processing.
*  This can be called from the dscvryEnd or the Start routines, depends on TID.
*
*  \param          [in]    msg          The response to the de-init request.
*
*  \param          [in]    isCancelled  An indication of whether the request
*                                       was cancelled.
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryDeinitPluginComplete
    (
    struct a2b_Msg* msg,
    a2b_Bool        isCancelled
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)a2b_msgGetUserData( msg );

    A2B_UNUSED(isCancelled);

    if ( plugin )
    {
        /* One less pending de-initialization response. */
        plugin->discovery.pendingPluginDeinit--;

        if ( msg )
        {
            /* Whether the de-initialization of the node's peripherals failed
             * (or not) for this plugin we'll continue processing but at least
             * trace the result.
             */
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("%s DeinitPluginComplete(): node=%hd status=0x%lX",
                A2B_MPLUGIN_PLUGIN_NAME,
                &plugin->nodeSig.nodeAddr,
                &((a2b_PluginDeinit*)a2b_msgGetPayload(msg))->resp.status);
#else
            A2B_TRACE3( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
                "%s DeinitPluginComplete(): node=%hd status=0x%lX",
                A2B_MPLUGIN_PLUGIN_NAME,
                &plugin->nodeSig.nodeAddr,
                &((a2b_PluginDeinit*)a2b_msgGetPayload(msg))->resp.status) );
#endif
        }

        if ( plugin->discovery.pendingPluginDeinit == 0u )
        {
            if ( A2B_DEINIT_DSCVREY_END == a2b_msgGetTid( msg ) )
            {
                a2b_dscvryEnd( plugin, 
                               plugin->discovery.discoveryCompleteCode );
            }
            else
            {
                (void)a2b_dscvryReset( plugin );

                /* On A2B_EXEC_COMPLETE a2b_dscvryEnd already called and 
                 * when continuing we NOP here as well.
                 */
            }
        }
    }

} /* a2b_dscvryDeinitPluginComplete */


/*!****************************************************************************
*
*  \b              a2b_dscvryInitPluginComplete_NoEeprom
*
*  Callback when A2B_MSGREQ_PLUGIN_PERIPH_INIT has completed processing.
*  This is specific to the case when No EEPROM is detected or supported.
*
*  \param          [in]    msg          The response to the peripheral init
*                                       request.
*
*  \param          [in]    isCancelled  An indication of whether or not
*                                       the request was cancelled.
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryInitPluginComplete_NoEeprom
    (
    struct a2b_Msg* msg,
    a2b_Bool        isCancelled
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)a2b_msgGetUserData( msg );
    a2b_UInt32 nodeAddr = a2b_msgGetTid( msg );
    a2b_HResult status = A2B_MAKE_HRESULT(A2B_SEV_FAILURE,
                                        A2B_FAC_PLUGIN,
                                        A2B_EC_INTERNAL);
    bdd_DiscoveryMode eDscMode;
    a2b_UInt32 nDscvrdNode = 0u;

    a2b_UInt8 wBuf[4u];
    a2b_Bool  isXTalkFixApplicable;
    a2b_Int16 dscNodeBddIdx;
    struct a2b_StackContext* ctx;
    const bdd_Node* bddNodeObj;

    if (plugin == A2B_NULL)
    {
        return;
    }

    dscNodeBddIdx = (a2b_Int16)plugin->discovery.dscNumNodes;
    ctx = plugin->ctx;
    bddNodeObj = &plugin->bdd->nodes[dscNodeBddIdx];

     A2B_UNUSED(isCancelled);

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\ra2b_dscvryInitPluginComplete_NoEeprom" );
#else
     A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                           "a2b_dscvryInitPluginComplete_NoEeprom" );
#endif

	 eDscMode = a2b_ovrGetDiscMode(plugin);

    if ( msg )
    {
		if ( A2B_HAS_PLUGIN(plugin, nodeAddr) )
		{
			plugin->discovery.pendingPluginInit--;
		}
	    nDscvrdNode = (a2b_UInt32)plugin->discovery.dscNumNodes-(a2b_UInt32)1u;
		/* Get the result of the plugin peripheral initialization */
        status = ((a2b_PluginInit*)a2b_msgGetPayload(msg))->resp.status;
    }

    /* If the plugin peripheral initialization failed then ... */
    if ( A2B_FAILED(status) )
    {
        a2b_dscvryEnd(plugin, A2B_ERR_CODE(status));
    }
    else if ( bdd_DISCOVERY_MODE_MODIFIED == eDscMode )
    {
        (void)a2b_dscvryPreSlaveInit( plugin );

        /* Now we wait for INTTYPE.DSCDONE on success */
    }
    else if((bdd_DISCOVERY_MODE_OPTIMIZED == eDscMode) ||
    		(bdd_DISCOVERY_MODE_ADVANCED == eDscMode))
    {
    	 if(nDscvrdNode != nodeAddr)
    	 {
             if ((a2b_Int16)nDscvrdNode == A2B_NODEADDR_MASTER)
             {
                 a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_OK);
             }
             else
             {
                 (void)adi_a2b_ConfigNodeOptimizAdvancedMode(plugin, (a2b_Int16)nDscvrdNode);
             }
    	 }
    	 else 
    	 {
             if (bdd_DISCOVERY_MODE_ADVANCED == eDscMode)
             {
                 /******************************************************
                 * Reconfigure slots for all Nodes discovered till
                 * now and enable data flow.Note: If EEPROM is present
                 * A2B registers may yet  be written so delay this
                 * till EEPROM and slave plugin initialization is complete
                 * Note: 'hasEeprom' is assigned when node is discovered
                 *****************************************************/

                 /* Re-configure Down and Up slot values for this node */
                 adi_a2b_ReConfigSlot(plugin, (a2b_Int16)nodeAddr);
                 /* Enable Downstream and Upstream data flow */
                 (void)a2b_FinalMasterSetup(plugin, A2B_NODEADDR_MASTER);
             }

            if (nodeAddr >= ((a2b_UInt32)plugin->bdd->nodes_count - (a2b_UInt32)2u))
            {
                a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_OK);
            }
            else
            {             
                /*Workaround for Optimized Discovery Flow anomaly number(18-00-0068)
                * 
                * During a sub-node discovery, if host processor performs I2C transaction and the if node getting discovered responds with SRF(if we had written discovery and started node and peripheral initialization.), then
                * the I2C transaction initiated will get wrong acknowledgement or if it is a read operation we will get garbled data.
                * 
                * 
                * DISCVRY Register needs to be wriiten after node and Peripheral Initialization
                * in case of Optimized and advanced discovery */
                if (!a2b_dscvryStartTimer(plugin, TIMER_DSCVRY))
                {
                    a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
                    A2B_DSCVRY_SEQEND(plugin->ctx);
                    return;
                }

                /*NodeAdr should be set to last Discovered node before writing DISCVRY register*/
                wBuf[0u] = A2B_REG_NODEADR;
                wBuf[1u] = (a2b_UInt8)nDscvrdNode;
                status = a2b_i2cMasterWrite(plugin->ctx, 2u, &wBuf);

                isXTalkFixApplicable = a2b_isCrossTalkFixApply(bddNodeObj->nodeDescr.vendor, bddNodeObj->nodeDescr.product);
                wBuf[0] = A2B_REG_DISCVRY;
                /* Cross Talk fix is enable, then increase the response cycle */
                if ((plugin->bdd->policy.bCrossTalkFixApply == A2B_TRUE) && (isXTalkFixApplicable == A2B_TRUE))
                {
                    wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs + 2u;
                }
                else
                {
                    wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs;
                }

                status = a2b_i2cMasterWrite(ctx, 2u, &wBuf);

                if (A2B_FAILED(status))
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cputs("\n\ra2b_dscvryInitPluginComplete_NoEeprom Cannot discover next node");
#else                
                    A2B_DSCVRY_ERROR0(ctx, "a2b_dscvryInitPluginComplete_NoEeprom", "Cannot discover next node");
#endif
                    a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
                    A2B_DSCVRY_SEQEND(plugin->ctx);
                    return;
                }
            }

            
            
		 }
    }
    else
    {
        /* Completing the control statement */
    }

    A2B_DSCVRY_SEQEND(plugin->ctx);

} /* a2b_dscvryInitPluginComplete_NoEeprom */


/*!****************************************************************************
*
*  \b              a2b_dscvryInitPluginComplete_EepromComplete
*
*  Callback when A2B_MSGREQ_PLUGIN_PERIPH_INIT has completed processing.
*  This is specific to the case when an EEPROM is found and has been
*  processed to completion.
*
*  \param          [in]    msg          Response for EEPROM completion.
*
*  \param          [in]    isCancelled  Indication of whether the request
*                                       was cancelled.
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryInitPluginComplete_EepromComplete
    (
    struct a2b_Msg* msg,
    a2b_Bool        isCancelled
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)a2b_msgGetUserData( msg );
    a2b_UInt32 nodeAddr = a2b_msgGetTid( msg );
    a2b_UInt32 nDscvrdNode = 0u;
    a2b_HResult status = A2B_MAKE_HRESULT(A2B_SEV_FAILURE,
                                        A2B_FAC_PLUGIN,
                                        A2B_EC_INTERNAL);
    bdd_DiscoveryMode eDscMode;

    a2b_UInt8 wBuf[4u];
	a2b_Bool  isXTalkFixApplicable;
    a2b_Int16 dscNodeBddIdx;
    struct a2b_StackContext* ctx;
    const bdd_Node* bddNodeObj;

    if (plugin == A2B_NULL)
    {
        return;
    }

	dscNodeBddIdx = (a2b_Int16)plugin->discovery.dscNumNodes;
	ctx = plugin->ctx;
	
    A2B_UNUSED(isCancelled);

    bddNodeObj = &plugin->bdd->nodes[dscNodeBddIdx];

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\ra2b_dscvryInitPluginComplete_EepromComplete" );
#else
    A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                          "a2b_dscvryInitPluginComplete_EepromComplete" );
#endif

    eDscMode = a2b_ovrGetDiscMode(plugin);

    if ( msg )
    {

        if ( A2B_HAS_PLUGIN(plugin, nodeAddr) )
        {
            plugin->discovery.pendingPluginInit--;
        }
        nDscvrdNode = (a2b_UInt32)plugin->discovery.dscNumNodes-(a2b_UInt32)1u;
        /* Get the result of the plugin peripheral initialization */
        status = ((a2b_PluginInit*)a2b_msgGetPayload(msg))->resp.status;
    }

    /* If the plugin peripheral initialization failed then ... */
    if ( A2B_FAILED(status) )
    {
        a2b_dscvryEnd(plugin, A2B_ERR_CODE(status));
    }
    else if ( bdd_DISCOVERY_MODE_MODIFIED == a2b_ovrGetDiscMode(plugin) )
    {
        (void)a2b_dscvryPreSlaveInit( plugin );

        /* If returned true:
         * Now we wait for INTTYPE.DSCDONE on success 
         * Else:
         * Complete
         */
    }
    else if((bdd_DISCOVERY_MODE_OPTIMIZED == eDscMode) ||
       		(bdd_DISCOVERY_MODE_ADVANCED == eDscMode))
    {
    	if(bdd_DISCOVERY_MODE_ADVANCED == eDscMode)
		{
			/* Since EEPROM configuration done for current node,
			 * re-configure slots up until  this node
			 * and re-initialize data flow again
			 *  */
			adi_a2b_ReConfigSlot(plugin, (a2b_Int16)nodeAddr);
			(void)a2b_FinalMasterSetup(plugin, A2B_NODEADDR_MASTER);
		}

    	/**********************************************************************
    	 * Also for the new node that has been discovered configure node ,
    	 * re-configure slots and re-initialize data flow again
    	 **********************************************************************/
       	if(nDscvrdNode != nodeAddr)
       	{

            if ((a2b_Int16)nDscvrdNode == A2B_NODEADDR_MASTER)
            {
                a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_OK);
            }
            else
            {
                (void)adi_a2b_ConfigNodeOptimizAdvancedMode(plugin, (a2b_Int16)nDscvrdNode);
            }
       	}
       	else
       	{
       		if(nodeAddr == ((a2b_UInt32)plugin->bdd->nodes_count-(a2b_UInt32)2u))
       		{
				a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_OK );
       		}
       		else
				{
                /*Workaround for Optimized Discovery Flow anomaly number(18-00-0068)
                *
                * During a sub-node discovery, if host processor performs I2C transaction and the if node getting discovered responds with SRF(if we had written discovery and started node and peripheral initialization.), then
                * the I2C transaction initiated will get wrong acknowledgement or if it is a read operation we will get garbled data.
                *
                * DISCVRY Register needs to be wriiten after node and Peripheral Initialization
                * in case of Optimized and advanced discovery */
					if (!a2b_dscvryStartTimer(plugin, TIMER_DSCVRY))
					{
						a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
						A2B_DSCVRY_SEQEND(plugin->ctx);
						return;
					}

                    /*NodeAdr should be set to last Discovered node before writing DISCVRY register*/
					wBuf[0u] = A2B_REG_NODEADR;
					wBuf[1u] = (a2b_UInt8)nDscvrdNode;
					status = a2b_i2cMasterWrite(plugin->ctx, 2u, &wBuf);

					isXTalkFixApplicable = a2b_isCrossTalkFixApply(bddNodeObj->nodeDescr.vendor, bddNodeObj->nodeDescr.product);
					wBuf[0] = A2B_REG_DISCVRY;
					/* Cross Talk fix is enable, then increase the response cycle */
					if ((plugin->bdd->policy.bCrossTalkFixApply == A2B_TRUE) && (isXTalkFixApplicable == A2B_TRUE))
					{
						wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs + 2u;
					}
					else
					{
						wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs;
					}

					status = a2b_i2cMasterWrite(ctx, 2u, &wBuf);

					if (A2B_FAILED(status))
					{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
						cputs("\n\ra2b_dscvryInitPluginComplete_EepromComplete Cannot discover next node");
#else					
						A2B_DSCVRY_ERROR0(ctx, "a2b_dscvryInitPluginComplete_EepromComplete", "Cannot discover next node");
#endif
						a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
						A2B_DSCVRY_SEQEND(plugin->ctx);
						return;
					}
				}
       	}
    }
    else
    {
        /* This will either process the next node or 
         * complete the network processing 
         */

#if !defined(A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY) && \
    defined(A2B_FEATURE_EEPROM_OR_FILE_PROCESSING)
        /* This is to avoid wasted calls to a2b_dscvryNetComplete 
         * that waste cycles and confuse the UML output.
         */
        if ((( plugin->discovery.hasEeprom == 0u ) &&
             ( plugin->discovery.pendingPluginInit == 0u ) ) ||
            (( plugin->discovery.hasEeprom ) &&
             ( a2b_periphCfgUsingSync() ) &&
             ( plugin->discovery.pendingPluginInit == 0u ) ) )
#endif
        {
            a2b_dscvryNetComplete( plugin );
        }
    }

    A2B_DSCVRY_SEQEND(plugin->ctx);

} /* a2b_dscvryInitPluginComplete_EepromComplete */


/*!****************************************************************************
*
*  \b              a2b_dscvryDeinitPlugin
*
*  This is called to initiate A2B_MSGREQ_PLUGIN_PERIPH_DEINIT ALL slave plugins.
*
*  \param          [in]    plugin
*  \param          [in]    mode
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryDeinitPlugin
    (
    a2b_Plugin*         plugin,
    a2b_UInt32          mode
    )
{
    struct a2b_Msg* msg;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_Int16 nodeAddr;

    for ( nodeAddr = 0; 
          nodeAddr < (a2b_Int16)plugin->discovery.dscNumNodes;
          nodeAddr++ )
    {
        if ( A2B_HAS_PLUGIN(plugin, nodeAddr) )
        {
            msg = a2b_msgAlloc( plugin->ctx,
                                A2B_MSG_REQUEST,
                                A2B_MSGREQ_PLUGIN_PERIPH_DEINIT );
            if ( msg )
            {
                a2b_msgSetUserData( msg, (a2b_Handle)plugin, A2B_NULL );
                a2b_msgSetTid( msg, mode );
                /* Assume failure de-initializing the plugin's peripherals. */
                ((a2b_PluginDeinit*)a2b_msgGetPayload(msg))->resp.status =
                                            A2B_MAKE_HRESULT(A2B_SEV_FAILURE,
                                            A2B_FAC_PLUGIN,
                                            A2B_EC_INTERNAL);

                status = a2b_msgRtrSendRequest( msg, 
                                         nodeAddr,
                                         &a2b_dscvryDeinitPluginComplete );

                if ( A2B_SUCCEEDED(status) )
                {
                    plugin->discovery.pendingPluginDeinit++;
                }

                /* Job executor now owns the message, 
                 * or free on error 
                 */
                (void)a2b_msgUnref( msg );
            }
        }
    }

} /* a2b_dscvryDeinitPlugin */


/*!****************************************************************************
*
*  \b              a2b_dscvryInitPlugin
*
*  This is called to initiate A2B_MSGREQ_PLUGIN_PERIPH_INIT with a specific
*  slave plugin.
*
*  \param          [in]    plugin
*  \param          [in]    nodeAddr
*  \param          [in]    completeCallback
*
*  \pre            None
*
*  \post           None
*
*  \return         [add here]
*
******************************************************************************/
static a2b_UInt32
a2b_dscvryInitPlugin
    (
    a2b_Plugin*         plugin,
    a2b_Int16           nodeAddr,
    a2b_MsgCallbackFunc completeCallback
    )
{
    struct a2b_Msg* msg;
    struct a2b_MsgNotifier 	*notifyIrptI2CError;
    a2b_HResult     result;
    a2b_PluginInit* pluginInit;
    a2b_UInt32 status = A2B_EC_OK;

    if ( A2B_NEEDS_PLUGIN_INIT( plugin, nodeAddr ) )
    {
        /* clear the bit */
        plugin->discovery.needsPluginInit ^= ((a2b_UInt32)1 << (a2b_UInt32)nodeAddr);
    }
    
    if ( A2B_HAS_PLUGIN(plugin, nodeAddr) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rInitPlugin: %hd ", &nodeAddr);
#else
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_TRACE1),
                    "InitPlugin: %hd ", &nodeAddr ) );
#endif
    }
    else
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rNo Plugin, Direct Init: %hd ", &nodeAddr );
#else   
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_TRACE1),
                    "No Plugin, Direct Init: %hd ", &nodeAddr ) );
#endif
    }

    msg = a2b_msgAlloc( plugin->ctx,
                        A2B_MSG_REQUEST,
                        A2B_MSGREQ_PLUGIN_PERIPH_INIT );
    if ( A2B_NULL == msg )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\ra2b_dscvryInitPlugin Cannot allocate message" );
#else    
        A2B_DSCVRY_ERROR0( plugin->ctx, "a2b_dscvryInitPlugin", 
                           "Cannot allocate message" );
#endif
        return (a2b_UInt32)A2B_EC_RESOURCE_UNAVAIL;
    }

    a2b_msgSetUserData( msg, (a2b_Handle)plugin, A2B_NULL );
    a2b_msgSetTid( msg, (a2b_UInt32)nodeAddr );

    if ( !A2B_HAS_PLUGIN(plugin, (a2b_UInt32)nodeAddr) )
    {
        /* Without a plugin this call would fail, so 
         * we call the requested callback now.  This 
         * means the msg is somewhat incomplete and 
         * MUST be used carefully.
         */
        completeCallback( msg , A2B_FALSE /* not cancelled */);
        (void)a2b_msgUnref( msg );

        return (a2b_UInt32)A2B_EC_OK;
    }

    /* Build the INIT payload */
    a2b_dscvryInitTdmSettings( plugin, nodeAddr );
    pluginInit = (a2b_PluginInit*)a2b_msgGetPayload( msg );
    pluginInit->req.tdmSettings = &plugin->pluginTdmSettings;
    pluginInit->req.pNodePeriDeviceConfig = (const void *)plugin->periphCfg.pkgCfg;
    /* Assume peripheral initialization failure */
    pluginInit->resp.status = A2B_MAKE_HRESULT(A2B_SEV_FAILURE,
                                                A2B_FAC_PLUGIN,
                                                A2B_EC_INTERNAL);
    
    result = a2b_msgRtrSendRequest(msg, 
                                   nodeAddr, /* destNodeAddr */
                                   completeCallback);

    /* Job executor now owns the message, or free on error */
    (void)a2b_msgUnref( msg );

    if ( A2B_FAILED(result) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
 		cprintf("\n\ra2b_dscvryInitPlugin Cannot send message (%ld)", &result);
#else    
        A2B_DSCVRY_ERROR1( plugin->ctx, "a2b_dscvryInitPlugin", 
                           "Cannot send message (%ld)", &result );
#endif
        return (a2b_UInt32)A2B_EC_IO;
    }

	/* Register for notifications on I2C to I2C peripheral configuration done events */
    notifyIrptI2CError = a2b_msgRtrRegisterNotify(plugin->ctx, A2B_MSGREQ_PERIPH_I2C_ERROR , &a2b_I2CErrorReported, A2B_NULL, A2B_NULL);
	if(notifyIrptI2CError != A2B_NULL)
	{
        /* Do nothing */
	}
	else
	{
		status = A2B_MAKE_HRESULT(A2B_SEV_FAILURE, A2B_FAC_PLUGIN, A2B_EC_INTERNAL);
	}

    plugin->discovery.pendingPluginInit++;

    return status;

} /* a2b_dscvryInitPlugin */


/*!****************************************************************************
*
*  \b              a2b_dscvryEnd
*
*  Terminate/End the discovery process, and changed the scheduler
*  execution to A2B_EXEC_COMPLETE.  After this call the Job executor will
*  start processing jobs again for the master plugin.
*
*  \param          [in]    plugin   Master plugin record
*  \param          [in]    errCode  A2B_EC_xxx error code of the
*                                   discovery process
*
*  \pre            ONLY called when in a suspended mode on the job queue
*                  while processing discovery.
*
*  \post           Job executor will start processing jobs again for
*                  this master plugin.
*
*  \return         None
*
******************************************************************************/
void
a2b_dscvryEnd
    (
    a2b_Plugin* plugin,
    a2b_UInt32 errCode
    )
{
    a2b_UInt8  wBuf[4u];
    struct a2b_Msg* msg;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    bdd_DiscoveryMode eDscMode;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    a2b_Bool periphComplete = A2B_TRUE;
    a2b_UInt8 idx;
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

    /* Stop the previously running timer */
    a2b_timerStop( plugin->timer );

    eDscMode = a2b_ovrGetDiscMode(plugin);
    if ( ((a2b_UInt32)A2B_EC_OK == errCode) && (plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_OK))
    {
#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
        /* See if all peripheral config has completed */
        periphComplete = (a2b_Bool)(plugin->discovery.hasEeprom == 0u);
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */
    }
	/* For partial A2B bus operation */
	else if (	((a2b_UInt32)A2B_EC_DISCOVERY_PWR_FAULT		== errCode)	|| 
				((a2b_UInt32)A2B_EC_BUSY					== errCode)	||
				((a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH		== errCode)	||
				((a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_TIMEOUT	== errCode)	)
	{
		/* Only in SIMPLE mode discovery  and atleast one sub node discovered*/
		if ((bdd_DISCOVERY_MODE_SIMPLE == eDscMode) && (plugin->discovery.dscNumNodes > 0u))
		{
			if (plugin->discovery.discoveryComplete == A2B_FALSE)
			{
				plugin->discovery.discoveryCompleteCode = errCode;
				a2b_dscvryNetComplete(plugin);

				/* Immediately return from this function as a2b_dscvryEnd is again called from a2b_dscvryNetComplete function */
				return;
			}
		}
	}
    /* Discovery error */
    /* Check to make sure we have not already done this processing */
    else if ( plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_OK )
    {
        /* Setting these to prevent executing this code again */
        plugin->discovery.discoveryComplete = A2B_TRUE;
        plugin->discovery.discoveryCompleteCode = errCode;

        /* On an error we need to clear the hasEeprom tracking */
        plugin->discovery.hasEeprom = 0u;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
        /* Stop all potential peripheral processing */
        for ( idx = 0u; idx < (a2b_UInt8)A2B_ARRAY_SIZE(plugin->periph.node); idx++ )
        {
            if ( plugin->periph.node[idx].mboxHnd )
            {
                (void)a2b_stackCtxMailboxFlush( plugin->ctx,
                                          plugin->periph.node[idx].mboxHnd );

                (void)a2b_stackCtxMailboxFree( plugin->ctx,
                                         plugin->periph.node[idx].mboxHnd );
                plugin->periph.node[idx].mboxHnd = A2B_NULL;
            }
        }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

        /* Send the A2B_MSGREQ_PLUGIN_PERIPH_DEINIT to all 
         * discovered plugins.
         */
        a2b_dscvryDeinitPlugin( plugin, A2B_DEINIT_DSCVREY_END );

        if ( plugin->discovery.pendingPluginDeinit )
        {
            /* Wait until Plugin Deinit has been responded to */
            return;
        }
    }
    else
    {
        /* Completing the control statement */
    }

    /* Track that discovery has completed and what the error code is
     * so if the peripheral config is still running we can 
     */
    plugin->discovery.discoveryComplete = A2B_TRUE;

    /* Once an error, always an error.  We don't want to clear the 
     * final error on subsequent calls.
     */
    if ((a2b_UInt32)A2B_EC_OK == plugin->discovery.discoveryCompleteCode )
    {
        plugin->discovery.discoveryCompleteCode = errCode;
    }

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    /* Only complete this when the peripherals are done */
    if ( !periphComplete )
    {
        return;
    }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

    /* Are we waiting for plugin de/initialization? */
    if (( plugin->discovery.pendingPluginInit ) || 
        ( plugin->discovery.pendingPluginDeinit ))
    {
        return;
    }
	/* Power is already disabled in case of power faults */
	if(errCode != (a2b_UInt32)A2B_EC_DISCOVERY_PWR_FAULT)
	{
		/* Disable power on the B side of the node */
		wBuf[0] = A2B_REG_SWCTL;
		wBuf[1] = A2B_ENUM_SWCTL_ENSW_DIS;
		status = a2b_regWrite( plugin->ctx, ((a2b_Int16)plugin->discovery.dscNumNodes-(a2b_Int16)1),2u, wBuf );

	}

    if (( A2B_FAILED(status) ) && 
        ((a2b_UInt32)A2B_EC_OK == plugin->discovery.discoveryCompleteCode))
    {
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        return;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\rDiscovery End (err: 0x%lX)",&plugin->discovery.discoveryCompleteCode );
#else
    A2B_DSCVRY_SEQGROUP1( plugin->ctx,
                          "Discovery End (err: 0x%lX)",
                          &plugin->discovery.discoveryCompleteCode );
#endif

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    /* STOP ALL possible peripheral processing timers */
    for (idx = 0u; idx < A2B_ARRAY_SIZE(plugin->periph.node); idx++)
    {
        a2b_timerStop(plugin->periph.node[idx].timer);
        (void)a2b_timerUnref( plugin->periph.node[idx].timer );
        plugin->periph.node[idx].timer = A2B_NULL;

        if ( A2B_NULL != plugin->periph.node[idx].mboxHnd )
        {
            (void)a2b_stackCtxMailboxFree(plugin->ctx,
                                     plugin->periph.node[idx].mboxHnd );
        }
        plugin->periph.node[idx].mboxHnd = A2B_NULL;
    }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

    if ( (bdd_DISCOVERY_MODE_MODIFIED == eDscMode) ||
    		(bdd_DISCOVERY_MODE_OPTIMIZED == eDscMode) ||
			(bdd_DISCOVERY_MODE_ADVANCED == eDscMode))
    {
        /* Only after the peripherals have completed should we finalize
         * the master node and enable up/downstream audio transmission.
         */
        a2b_dscvryNetComplete( plugin );
    }

    wBuf[0] = A2B_REG_CONTROL;
    /* The AD242X (only) needs to be told it's a Master node BEFORE
     * the PLL locks on the SYNC pin. Once the PLL is locked, setting
     * the MSTR bit is ignored. We set it anyway so it's clear this is
     * the master node.
     */
    wBuf[1] = A2B_ENUM_CONTROL_END_DISCOVERY;
    if ( (plugin->nodeSig.hasSiliconInfo) &&
        ((a2b_isAd242xChip(plugin->nodeSig.siliconInfo.vendorId,
        plugin->nodeSig.siliconInfo.productId))) )
    {
        wBuf[1] |= (a2b_UInt8)A2B_ENUM_CONTROL_MSTR;
    }
	wBuf[1] |= (a2b_UInt8)(plugin->bdd->nodes[0].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
    (void)a2b_i2cMasterWrite( plugin->ctx, 2u, &wBuf );

    plugin->discovery.inDiscovery = A2B_FALSE;

    msg = a2b_msgRtrGetExecutingMsg( plugin->ctx, A2B_MSG_MAILBOX );
    if (msg)
    {
        a2b_NetDiscovery*   dscResp;
        dscResp = (a2b_NetDiscovery*)a2b_msgGetPayload( msg );

        status = A2B_RESULT_SUCCESS;
        if (plugin->discovery.discoveryCompleteCode)
        {
            /* Add the severity and facility */
            status = A2B_MAKE_HRESULT(A2B_SEV_FAILURE, A2B_FAC_PLUGIN, 
                                      plugin->discovery.discoveryCompleteCode);
        }

        dscResp->resp.status   = status;
        dscResp->resp.numNodes = plugin->discovery.dscNumNodes;
		dscResp->resp.oLastNodeInfo = plugin->slaveNodeSig[dscResp->resp.numNodes].siliconInfo;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rDiscoveryResp: status: 0x%08lX, numNodes: %ld", 
                &dscResp->resp.status, &dscResp->resp.numNodes);
#else    
        A2B_SEQ_CHART2( (plugin->ctx,
                A2B_NODE_ADDR_TO_CHART_PLUGIN_ENTITY(plugin->nodeSig.nodeAddr),
                A2B_SEQ_CHART_ENTITY_APP,
                A2B_SEQ_CHART_COMM_REPLY,
                A2B_SEQ_CHART_LEVEL_DISCOVERY,
                "DiscoveryResp: status: 0x%08lX, numNodes: %ld", 
                &dscResp->resp.status, &dscResp->resp.numNodes ));
#endif
    }

    a2b_msgRtrExecUpdate( plugin->ctx, A2B_MSG_MAILBOX, A2B_EXEC_COMPLETE );

    /*
     * Notify listeners that discovery is done
     */
    msg = a2b_msgAlloc( plugin->ctx,
                        A2B_MSG_NOTIFY,
                        A2B_MSGNOTIFY_DISCOVERY_DONE );
    if ( A2B_NULL == msg )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("%s a2b_dscvryEnd(): Failed to allocate DISCOVERY_DONE notification msg", A2B_MPLUGIN_PLUGIN_NAME);
#else   
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s a2b_dscvryEnd(): Failed to allocate DISCOVERY_DONE "
                    "notification msg", A2B_MPLUGIN_PLUGIN_NAME));
#endif
    }
    else
    {
        a2b_DiscoveryStatus* discStatus;

        discStatus = (a2b_DiscoveryStatus*)a2b_msgGetPayload(msg);
        discStatus->status = status;
        discStatus->numNodes = plugin->discovery.dscNumNodes;
        if ( A2B_FAILED(a2b_msgRtrNotify(msg)) )
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf( "%s a2b_dscvryEnd(): Failed to emit DISCOVERY_DONE notification",A2B_MPLUGIN_PLUGIN_NAME);
#else     
            A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                                "%s a2b_dscvryEnd(): Failed to emit "
                                "DISCOVERY_DONE notification",
                                A2B_MPLUGIN_PLUGIN_NAME));
#endif
        }
        /* We always unref the notification message on success or failure of
         * notification delivery
         */
        (void)a2b_msgUnref(msg);

    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rdscvryEnd== Discovery Ended ==" );
#else
    A2B_DSCVRY_RAWDEBUG0( plugin->ctx, "dscvryEnd",
                          "== Discovery Ended ==" );
#endif
    A2B_DSCVRY_SEQEND( plugin->ctx );

} /* a2b_dscvryEnd */


/*!****************************************************************************
*
*  \b              a2b_onDiscTimeout
*
*  Handle the discovery timeout.
*
*  \param          [in]    timer
*  \param          [in]    userData
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_onDiscTimeout
    (
    struct a2b_Timer *timer,
    a2b_Handle userData
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)userData;
    a2b_HResult ret;
    a2b_UInt8   dscNumNodes = plugin->discovery.dscNumNodes;
    a2b_Bool bNetConfigFlag = A2B_FALSE;

    A2B_UNUSED(timer);

    /* Check the interrupt status one more time in 
     * case of a timing race condition.
     */
    ret = a2b_intrQueryIrq( plugin->ctx );

    if (( A2B_SUCCEEDED(ret) ) && ( dscNumNodes != plugin->discovery.dscNumNodes ))
    {
        /* Discovery Done, no error, node already handled */
        return;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\ronDiscTimeout DISCOVERY TIMEOUT" );
#else
    A2B_DSCVRY_ERROR0( plugin->ctx, "onDiscTimeout", "DISCOVERY TIMEOUT" );
#endif

    bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);
    if((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
    {
    	plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_BUSY;
    	a2b_dscvryNetComplete(plugin);
    }
    else
    {
    a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_BUSY );
    }

} /* a2b_onDiscTimeout */


#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
/*!****************************************************************************
*
*  \b              a2b_dscvryPeripheralProcessingComplete
*
*  Handler when peripheral processing is complete.
*
*  \param          [in]    plugin
*  \param          [in]    nodeAddr
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
void 
a2b_dscvryPeripheralProcessingComplete
    ( 
    a2b_Plugin* plugin,
    a2b_Int16   nodeAddr
    )
{
    if (plugin)
    {
#ifdef FIND_NODE_HANDLER_AFTER_NODE_INIT
        a2b_dscvryFindNodeHandler(plugin,
                                A2B_MAP_SLAVE_ADDR_TO_INDEX(nodeAddr));
#endif
        (void)a2b_dscvryInitPlugin( plugin, 
                              nodeAddr,
                              &a2b_dscvryInitPluginComplete_EepromComplete );
    }

} /* a2b_dscvryPeripheralProcessingComplete */

#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */


/*!****************************************************************************
*
*  \b              a2b_onResetTimeout
*
*  Handle the reset timeout.
*
*  \param          [in]    timer
*  \param          [in]    userData
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_onResetTimeout
    (
    struct a2b_Timer *timer,
    a2b_Handle userData
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)userData;

    A2B_UNUSED(timer);

    if (plugin->discovery.inDiscovery)
    {
        /* Initialize the Master Node */
        if (a2b_dscvryPreMasterInit(plugin))
        {
            /* Discovery has started */
            return;
        }
    }

    /* Must be an error or in the wrong state, quit the complete command */
    a2b_msgRtrExecUpdate( plugin->ctx, A2B_MSG_MAILBOX, A2B_EXEC_COMPLETE );

} /* a2b_onResetTimeout */


/*!****************************************************************************
*
*  \b              a2b_dscvryStartTimer
*
*  Generate/Start the discovery timer.
*
*  \param          [in]    plugin
*  \param          [in]    type
*
*  \pre            None
*
*  \post           None
*
*  \return         [add here]
*
******************************************************************************/
static a2b_Bool
a2b_dscvryStartTimer
    (
    a2b_Plugin*     plugin,
    a2b_dscvryTimer type
    )
{
    /* Default is for the discovery timer */
    a2b_UInt32 delay = A2B_DISCOVERY_DELAY;
    a2b_TimerFunc timerFunc = &a2b_onDiscTimeout; 

    if ( TIMER_RESET == type )
    {
        /* Setup for the reset timer */
		delay = (plugin->bdd->policy.discoveryStartDelay > 0u ? plugin->bdd->policy.discoveryStartDelay : A2B_SW_RESET_DELAY);
        timerFunc = &a2b_onResetTimeout;
    }

    /* Stop the previously running timer */
    a2b_timerStop( plugin->timer );

    /* Single shot timer */
    a2b_timerSet( plugin->timer, delay, 0u );
    a2b_timerSetHandler(plugin->timer, timerFunc);
    a2b_timerSetData(plugin->timer, plugin);
    a2b_timerStart( plugin->timer );

    return A2B_TRUE;

} /* a2b_dscvryStartTimer */


/*!****************************************************************************
*
*  \b              a2b_dscvryNodeInterruptInit
*
*  Initialize a nodes interrupt registers
*
*  \param          [in]    plugin       plugin specific data
* 
*  \param          [in]    nodeBddIdx   0=master, 1=slave0, etc
*
*  \pre            None
*
*  \post           None
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool
a2b_dscvryNodeInterruptInit
    (
    a2b_Plugin* plugin,
    a2b_Int16   nodeBddIdx
    )
{
    a2b_Int16 nodeAddr = nodeBddIdx-1;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_UInt32 nRetVal;

    if ((nodeBddIdx < 0) || (nodeBddIdx >= (a2b_Int16)plugin->bdd->nodes_count))
    {
        return A2B_FALSE;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rInterrupt Registers");
#else
    A2B_DSCVRY_SEQGROUP0( plugin->ctx, 
                          "Interrupt Registers" );
#endif

    if (plugin->bdd->nodes[nodeBddIdx].has_intRegs)
    {
        a2b_UInt8 wBuf[4];
        a2b_UInt32 mask = 0u;

        if (plugin->bdd->nodes[nodeBddIdx].intRegs.has_intmsk0)
        {
            mask |= (plugin->bdd->nodes[nodeBddIdx].intRegs.intmsk0 <<
                     A2B_INTRMASK0_OFFSET);
        }
        if (plugin->bdd->nodes[nodeBddIdx].intRegs.has_intmsk1)
        {
            nRetVal = a2b_ovrApplyIntrActive(plugin, nodeBddIdx,
                    A2B_REG_INTMSK1) << A2B_INTRMASK1_OFFSET;
            mask |= nRetVal;
        }
        if (plugin->bdd->nodes[nodeBddIdx].intRegs.has_intmsk2)
        {
            nRetVal = a2b_ovrApplyIntrActive(plugin, nodeBddIdx,
                    A2B_REG_INTMSK2) << A2B_INTRMASK2_OFFSET;
            mask |= nRetVal;
        }

        /* The last node in the network should *not* have the power fault
         * interrupts enabled since it would always trigger. Since there is
         * no connection on the "B" side of the transceiver it will always
         * report an open-circuit condition.
         */
        if (nodeBddIdx + 1 >= (a2b_Int16)plugin->bdd->nodes_count)
        {
            mask &= (a2b_UInt32)(~((a2b_UInt32)A2B_BITM_INTPND0_PWRERR << (a2b_UInt32)A2B_INTRMASK0_OFFSET));
        }
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("%s NodeInterruptInit(): setIntrMask(0x%lX)",A2B_MPLUGIN_PLUGIN_NAME, &mask);
#else
        A2B_TRACE2( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_TRACE3),
                    "%s NodeInterruptInit(): setIntrMask(0x%lX)",
                    A2B_MPLUGIN_PLUGIN_NAME, &mask) );
#endif
        (void)a2b_intrSetMask( plugin->ctx, nodeAddr, mask );

        if (plugin->bdd->nodes[nodeBddIdx].intRegs.has_becctl)
        {
            wBuf[0] = A2B_REG_BECCTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeBddIdx].intRegs.becctl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            if ( A2B_FAILED(status) )
            {
                A2B_DSCVRY_SEQEND( plugin->ctx );
                return A2B_FALSE;
            }
        }
    }

    A2B_DSCVRY_SEQEND( plugin->ctx );

    return A2B_TRUE;

} /* a2b_dscvryNodeInterruptInit */


/*!****************************************************************************
*
*  \b              a2b_dscvryNodeComplete
*
*  Configuration of master/slave node after discovery
*
*  \param          [in]    plugin        plugin specific data
*  \param          [in]    nodeAddr      -1=master, 0=slave0, 1=slave1, etc
*  \param          [in]    bDoEepromCfg   Configure node from EEPROM
*  \param          [in]    errCode        Pointer to the Error code passed
*  										  from this function
**
*  \pre            Should call this routine only for the master node
*
*  \post           On failures the a2b_dscvryEnd() is expected to be called
*                  outside this function.
*
*  \return         status - sucess (0u)
*							failure (0xFFFFFFFFu)
******************************************************************************/
static a2b_Int32
a2b_dscvryNodeComplete
    (
    a2b_Plugin* plugin,
    a2b_Int16   nodeAddr,
    a2b_Bool    bDoEepromCfg,
    a2b_UInt32* errCode
    )
{
    a2b_UInt8 wBuf[4];
    a2b_Int16 nodeIdx = nodeAddr+1;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_UInt32 i2cCount = 0u;
    a2b_Int32 retCode;
    a2b_Bool bGroupLogged = A2B_FALSE;
    a2b_Bool isAd242x = A2B_FALSE;
    a2b_Bool isAd242xMaster = A2B_FALSE;
    a2b_Bool bRetVal;
    bdd_DiscoveryMode eDiscMode;

    eDiscMode = a2b_ovrGetDiscMode(plugin);

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\rNodeComplete for nodeAddr %hd", &nodeAddr );
#else
    A2B_DSCVRY_SEQGROUP1( plugin->ctx,
                          "NodeComplete for nodeAddr %hd", &nodeAddr );
#endif

    *errCode = (a2b_UInt32)A2B_EC_OK;

#ifndef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    A2B_UNUSED( bDoEepromCfg );
#endif

    if ((nodeAddr < A2B_NODEADDR_MASTER) || 
        (nodeIdx >= (a2b_Int16)plugin->bdd->nodes_count))
    {
        A2B_DSCVRY_SEQEND( plugin->ctx );
        *errCode = (a2b_UInt32)A2B_EC_INVALID_PARAMETER;
        return A2B_EXEC_COMPLETE_FAIL;
    }

    if ( plugin->nodeSig.hasSiliconInfo )
    {
        isAd242xMaster = a2b_isAd242xChip(
                                        plugin->nodeSig.siliconInfo.vendorId,
                                        plugin->nodeSig.siliconInfo.productId);
    }

    if ( A2B_NODEADDR_MASTER == nodeAddr )
    {
        isAd242x = isAd242xMaster;
    }
    else if ( plugin->slaveNodeSig[nodeAddr].hasSiliconInfo )
    {
        isAd242x = a2b_isAd242xChip(
                plugin->slaveNodeSig[nodeAddr].siliconInfo.vendorId,
                plugin->slaveNodeSig[nodeAddr].siliconInfo.productId) ||
                plugin->bdd->nodes[nodeIdx].nodeDescr.bIsAnalyzer;
    }
    else
    {
        /* Completing the control statement */
    }

    /*---------------------------------------------------*/
    /* Some simple setup prior to further initialization */
    /*---------------------------------------------------*/

    /* NOTE: A2B_REG_NODEADR managed by I2C, no need to set it */
    
    if ( (bdd_DISCOVERY_MODE_SIMPLE == eDiscMode) &&
        (A2B_NODEADDR_MASTER == nodeAddr) )
    {
        /*if ( A2B_SUCCEEDED(status) )*/
        {
            wBuf[0] = A2B_REG_SWCTL;
            wBuf[1] = A2B_BITM_SWCTL_ENSW;
            status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
            i2cCount++;
        }
    }

    /*-------------------*/
    /* Control Registers */
    /*-------------------*/
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rControl Registers");
#else
    A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                          "Control Registers" );
#endif

    if (( A2B_SUCCEEDED(status) ) && 
        (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_bcdnslots))
    {
        wBuf[0] = A2B_REG_BCDNSLOTS;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.bcdnslots;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if (( A2B_SUCCEEDED(status) ) && 
        (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_ldnslots))
    {
        wBuf[0] = A2B_REG_LDNSLOTS;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.ldnslots;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if (( A2B_SUCCEEDED(status) ) && 
        (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_lupslots))
    {
        wBuf[0] = A2B_REG_LUPSLOTS;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.lupslots;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if(((a2b_UInt32)nodeIdx < (a2b_UInt32)(plugin->bdd->nodes_count - (a2b_UInt32)1u)) &&
    		(bdd_DISCOVERY_MODE_ADVANCED != eDiscMode))
    {
		if ( A2B_SUCCEEDED(status) &&
			(plugin->bdd->nodes[nodeIdx].ctrlRegs.has_dnslots))
		{
			wBuf[0] = A2B_REG_DNSLOTS;
			wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.dnslots;
			status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
			i2cCount++;
		}

		if ( A2B_SUCCEEDED(status) &&
				(plugin->bdd->nodes[nodeIdx].ctrlRegs.has_upslots))
		{
			wBuf[0] = A2B_REG_UPSLOTS;
			wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.upslots;
			status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
			i2cCount++;
		}
    }
   
    A2B_DSCVRY_SEQEND( plugin->ctx );

    /*-------------------*/
    /* I2C/I2S Registers */
    /*-------------------*/

    bGroupLogged = A2B_FALSE;
    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2ccfg))
    {
        bGroupLogged = A2B_TRUE;
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rI2C/I2S Registers" );
#else		
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "I2C/I2S Registers" );
#endif

        wBuf[0] = A2B_REG_I2CCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2ccfg;
		status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

	if ((A2B_SUCCEEDED(status)) &&
		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_syncoffset))
	{
		wBuf[0] = A2B_REG_SYNCOFFSET;
		wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.syncoffset;
		status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
		i2cCount++;
	}
    if (( A2B_SUCCEEDED(status) ) &&
        (plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2stxoffset))
    {
        wBuf[0] = A2B_REG_I2STXOFFSET;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2stxoffset;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if (( A2B_SUCCEEDED(status) ) &&
        (plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2srxoffset))
    {
        wBuf[0] = A2B_REG_I2SRXOFFSET;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2srxoffset;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }
    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2sgcfg))
    {
        wBuf[0] = A2B_REG_I2SGCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2sgcfg;
		status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2scfg))
    {
        wBuf[0] = A2B_REG_I2SCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2scfg;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if (( A2B_SUCCEEDED(status) ) && 
        (plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2srate))
    {
        wBuf[0] = A2B_REG_I2SRATE;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2srate;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }
	
    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_pdmctl))
    {
        wBuf[0] = A2B_REG_PDMCTL;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.pdmctl;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }
	/* Chiron  - Start */
    if ( A2B_SUCCEEDED(status) &&
			(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_pdmctl2))
    {
        wBuf[0] = A2B_REG_PDMCTL2;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.pdmctl2;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

	/* chiron - End */
    if ( A2B_SUCCEEDED(status) && 
    		(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_errmgmt))
    {
        wBuf[0] = A2B_REG_ERRMGMT;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.errmgmt;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( bGroupLogged )
    {
        A2B_DSCVRY_SEQEND(plugin->ctx);
    }
    

    /*-------------------*/
    /* Pin I/O Registers */
    /*-------------------*/

    bGroupLogged = A2B_FALSE;
    if ( A2B_SUCCEEDED(status) )
    {
        bGroupLogged = A2B_TRUE;
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rPin I/O Registers" );
#else
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "Pin I/O Registers" );
#endif

        /* Only the AD24XX (e.g. older AD2410 chips) have a CLKCFG register */
        if ( (plugin->bdd->nodes[nodeIdx].pinIoRegs.has_clkcfg) && (!isAd242x) )
        {
            wBuf[0] = A2B_REG_CLKCFG;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.clkcfg;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_gpiodat) )
    {
        wBuf[0] = A2B_REG_GPIODAT;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.gpiodat;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_gpiooen))
    {
        wBuf[0] = A2B_REG_GPIOOEN;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.gpiooen;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_gpioien))
    {
        wBuf[0] = A2B_REG_GPIOIEN;
        wBuf[1] = (a2b_UInt8)a2b_ovrApplyIntrActive(plugin, nodeIdx, A2B_REG_GPIOIEN);
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_pinten) )
    {
        wBuf[0] = A2B_REG_PINTEN;
        wBuf[1] = (a2b_UInt8)a2b_ovrApplyIntrActive(plugin, nodeIdx, A2B_REG_PINTEN);
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_pintinv) )
    {
        wBuf[0] = A2B_REG_PINTINV;
        wBuf[1] = (a2b_UInt8)a2b_ovrApplyIntrActive(plugin, nodeIdx, A2B_REG_PINTINV);
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) &&
    		(plugin->bdd->nodes[nodeIdx].pinIoRegs.has_pincfg) )
    {
        wBuf[0] = A2B_REG_PINCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.pincfg;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }


    /*
     * Additional AD242X registers
     */

    /*--------------------------------------*/
    /* Clock Config Registers - AD242X only */
    /*--------------------------------------*/

    if ( (A2B_SUCCEEDED(status)) && (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].pinIoRegs.has_clk1cfg) )
    {
        wBuf[0] = A2B_REG_CLK1CFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.clk1cfg;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( (A2B_SUCCEEDED(status)) && (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].pinIoRegs.has_clk2cfg) )
    {
        wBuf[0] = A2B_REG_CLK2CFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].pinIoRegs.clk2cfg;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    if ( bGroupLogged )
    {
        A2B_DSCVRY_SEQEND(plugin->ctx);
    }

    /*------------------------------------------------------*/
    /* Slot Enhancement Registers (AD242x only, slave only) */
    /*------------------------------------------------------*/

    if ( (A2B_SUCCEEDED(status)) &&
        (isAd242x) &&
        (A2B_NODEADDR_MASTER != nodeAddr) &&
        (plugin->bdd->nodes[nodeIdx].has_slotEnh) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rSlot Enhancement Registers" );
#else    
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "Slot Enhancement Registers" );
#endif

        if ( /*(A2B_SUCCEEDED(status)) &&*/
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_upmask0))
        {
            wBuf[0] = A2B_REG_UPMASK0;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.upmask0;
            status = a2b_i2cSlaveWrite(plugin->ctx, nodeAddr, 2u, wBuf);
            i2cCount++;
        }

        if ((A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_upmask1))
        {
            wBuf[0] = A2B_REG_UPMASK1;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.upmask1;
            status = a2b_i2cSlaveWrite(plugin->ctx, nodeAddr, 2u, wBuf);
            i2cCount++;
        }

        if ((A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_upmask2))
        {
            wBuf[0] = A2B_REG_UPMASK2;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.upmask2;
            status = a2b_i2cSlaveWrite(plugin->ctx, nodeAddr, 2u, wBuf);
            i2cCount++;
        }

        if ((A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_upmask3))
        {
            wBuf[0] = A2B_REG_UPMASK3;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.upmask3;
            status = a2b_i2cSlaveWrite(plugin->ctx, nodeAddr, 2u, wBuf);
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_upoffset) )
        {
            wBuf[0] = A2B_REG_UPOFFSET;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.upoffset;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_dnmask0) )
        {
            wBuf[0] = A2B_REG_DNMASK0;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.dnmask0;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_dnmask1) )
        {
            wBuf[0] = A2B_REG_DNMASK1;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.dnmask1;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_dnmask2) )
        {
            wBuf[0] = A2B_REG_DNMASK2;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.dnmask2;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_dnmask3) )
        {
            wBuf[0] = A2B_REG_DNMASK3;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.dnmask3;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].slotEnh.has_dnoffset) )
        {
            wBuf[0] = A2B_REG_DNOFFSET;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].slotEnh.dnoffset;
            status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        A2B_DSCVRY_SEQEND(plugin->ctx);
    }


    /*--------------------------------------------*/
    /* GPIO over Distance Registers (AD242x only) */
    /*--------------------------------------------*/
    if ( (A2B_SUCCEEDED(status)) &&
        (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].has_gpioDist) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rGPIO Over Distance Registers" );
#else    
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "GPIO Over Distance Registers" );
#endif

        if ( /*(A2B_SUCCEEDED(status)) &&*/
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod0msk) )
        {
            wBuf[0] = A2B_REG_GPIOD0MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod0msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod1msk) )
        {
            wBuf[0] = A2B_REG_GPIOD1MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod1msk;
			status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod2msk) )
        {
            wBuf[0] = A2B_REG_GPIOD2MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod2msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod3msk) )
        {
            wBuf[0] = A2B_REG_GPIOD3MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod3msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod4msk) )
        {
            wBuf[0] = A2B_REG_GPIOD4MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod4msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod5msk) )
        {
            wBuf[0] = A2B_REG_GPIOD5MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod5msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod6msk) )
        {
            wBuf[0] = A2B_REG_GPIOD6MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod6msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiod7msk) )
        {
            wBuf[0] = A2B_REG_GPIOD7MSK;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiod7msk;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }
        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpioddat) )
        {
            wBuf[0] = A2B_REG_GPIODDAT;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpioddat;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpiodinv) )
        {
            wBuf[0] = A2B_REG_GPIODINV;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpiodinv;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if ( (A2B_SUCCEEDED(status)) &&
            (plugin->bdd->nodes[nodeIdx].gpioDist.has_gpioden) )
        {
            wBuf[0] = A2B_REG_GPIODEN;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].gpioDist.gpioden;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        A2B_DSCVRY_SEQEND(plugin->ctx);
    }

#ifdef A2B_FEATURE_COMM_CH
    if (plugin->bdd->nodes[nodeIdx].nodeDescr.oCustomNodeIdSettings.bReadFrmCommCh == A2B_FALSE)
    {
#endif	/* A2B_FEATURE_COMM_CH */
		/*---------------------------------------------*/
		/* Mailbox Registers (AD242x only, slave only) */
		/*---------------------------------------------*/

		if ( (A2B_SUCCEEDED(status)) &&
			(isAd242x) &&
			(plugin->bdd->nodes[nodeIdx].has_mbox) &&
			(A2B_NODEADDR_MASTER != nodeAddr) )
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rMailbox Registers" );
#else		
			A2B_DSCVRY_SEQGROUP0( plugin->ctx, "Mailbox Registers" );
#endif

			if (/* (A2B_SUCCEEDED(status)) && */
				(plugin->bdd->nodes[nodeIdx].mbox.has_mbox0ctl) )
			{
				wBuf[0] = A2B_REG_MBOX0CTL;
				wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].mbox.mbox0ctl;
				status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
				i2cCount++;
			}

			if ( (A2B_SUCCEEDED(status)) &&
				(plugin->bdd->nodes[nodeIdx].mbox.has_mbox1ctl) )
			{
				wBuf[0] = A2B_REG_MBOX1CTL;
				wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].mbox.mbox1ctl;
				status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
				i2cCount++;
			}

			A2B_DSCVRY_SEQEND(plugin->ctx);
		}
#ifdef A2B_FEATURE_COMM_CH
	}
#endif	/* A2B_FEATURE_COMM_CH */

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\r242x I2S Registers" );
#else
	A2B_DSCVRY_SEQGROUP0( plugin->ctx, "242x I2S Registers" );
#endif

    /* A2B_REG_SUSCFG - AD242X only for slave nodes */
    if ( (A2B_SUCCEEDED(status)) &&
        (A2B_NODEADDR_MASTER != nodeAddr) &&
        (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_suscfg ))
    {
        wBuf[0] = A2B_REG_SUSCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.suscfg;
        status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    /* A2B_REG_I2SRRSOFFS - AD242X only, slave only */
    if ( (A2B_SUCCEEDED(status)) &&
        ((A2B_NODEADDR_MASTER != nodeAddr)) &&
        (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2srrsoffs ))
    {
        wBuf[0] = A2B_REG_I2SRRSOFFS;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2srrsoffs;
        status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }

    /* A2B_REG_I2SRRCTL - AD242X only */
    if ( (A2B_SUCCEEDED(status)) && (isAd242x) &&
        (plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2srrctl) )
    {
        wBuf[0] = A2B_REG_I2SRRCTL;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2srrctl;
        status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
        i2cCount++;
    }
    A2B_DSCVRY_SEQEND(plugin->ctx);

    /*------------------*/
    /* Tuning Registers */
    /*------------------*/

    if (plugin->bdd->nodes[nodeIdx].has_tuningRegs)
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rTuning Registers" );
#else    
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "Tuning Registers" );
#endif

        if (( A2B_SUCCEEDED(status) ) && 
            (plugin->bdd->nodes[nodeIdx].tuningRegs.has_vregctl))
        {
            wBuf[0] = A2B_REG_VREGCTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].tuningRegs.vregctl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if (( A2B_SUCCEEDED(status) ) && 
            (plugin->bdd->nodes[nodeIdx].tuningRegs.has_txactl))
        {
            wBuf[0] = A2B_REG_TXACTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].tuningRegs.txactl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if (( A2B_SUCCEEDED(status) ) && 
            (plugin->bdd->nodes[nodeIdx].tuningRegs.has_rxactl))
        {
            wBuf[0] = A2B_REG_RXACTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].tuningRegs.rxactl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if (( A2B_SUCCEEDED(status) ) && 
            (plugin->bdd->nodes[nodeIdx].tuningRegs.has_txbctl))
        {
            wBuf[0] = A2B_REG_TXBCTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].tuningRegs.txbctl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }

        if (( A2B_SUCCEEDED(status) ) && 
            (plugin->bdd->nodes[nodeIdx].tuningRegs.has_rxbctl))
        {
            wBuf[0] = A2B_REG_RXBCTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].tuningRegs.rxbctl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );
            i2cCount++;
        }
        A2B_DSCVRY_SEQEND(plugin->ctx);
    }

    /*---------------------*/
    /* Interrupt Registers */
    /*---------------------*/

    bRetVal = a2b_dscvryNodeInterruptInit(plugin, nodeIdx);
    if (( A2B_SUCCEEDED(status) ) && (!bRetVal))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rnodeComplete Failed to set node interrupts" );
#else
        A2B_DSCVRY_ERROR0( plugin->ctx, "nodeComplete",
                           "Failed to set node interrupts" );
#endif
        A2B_DSCVRY_SEQEND( plugin->ctx );
        *errCode = (a2b_UInt32)A2B_EC_IO;
        return A2B_EXEC_COMPLETE_FAIL;
    }

    /*---------------------*/
    /* Final Master Setup  */
    /*---------------------*/

    if ( A2B_SUCCEEDED(status) )
    {
        if ((A2B_NODEADDR_MASTER != nodeAddr) &&
        		(bdd_DISCOVERY_MODE_SIMPLE == eDiscMode))
        {
		    /* Don't enable switch to last slave */
        	if(nodeAddr != (plugin->bdd->nodes_count - 2))
        	{
				wBuf[0] = A2B_REG_SWCTL;
				/* Disable the Switch for last discoverd sub node when faults in the bus*/
				if(nodeAddr == (plugin->discovery.dscNumNodes - 1u))
				{
					wBuf[1] = A2B_ENUM_SWCTL_ENSW_DIS;
				}
				else
				{
					wBuf[1] = A2B_BITM_SWCTL_ENSW;
				}

				status  = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
				i2cCount++;
        	}
        }
    }

    /*-----------------------*/
    /* Peripheral Processing */
    /*-----------------------*/
    retCode = A2B_EXEC_COMPLETE;
#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    if (( A2B_SUCCEEDED(status) ) && (bDoEepromCfg) &&
        ( A2B_HAS_EEPROM(plugin, nodeAddr) ) )
    {
        retCode = a2b_periphCfgInitProcessing( plugin, nodeAddr );
        if ( A2B_EXEC_COMPLETE_FAIL == retCode )
        {
            /* On an error we need to clear the hasEeprom tracking */
            plugin->discovery.hasEeprom = 0u;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rnodeComplete EEPROM Processing Failed" );
#else
            A2B_DSCVRY_ERROR0( plugin->ctx, "nodeComplete",
                               "EEPROM Processing Failed" );
#endif
            A2B_DSCVRY_SEQEND( plugin->ctx );
            *errCode = (a2b_UInt32)A2B_EC_IO;
            return A2B_EXEC_COMPLETE_FAIL;
        }
    }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */


    /*-------------------*/
    /* Status Processing */
    /*-------------------*/

    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rnodeComplete I2C failure at operation: %ld", &i2cCount );
#else    
        A2B_DSCVRY_ERROR1( plugin->ctx, "nodeComplete",
                           "I2C failure at operation: %ld", &i2cCount );
#endif
        A2B_DSCVRY_SEQEND( plugin->ctx );
        *errCode = (a2b_UInt32)A2B_EC_INTERNAL;
        return A2B_EXEC_COMPLETE_FAIL;
    }

    A2B_DSCVRY_SEQEND( plugin->ctx );

    return retCode;

} /* a2b_dscvryNodeComplete */

/*!****************************************************************************
*
*  \b              a2b_ReportI2CError
*
*  Creates an I2C error message for Application
*
*  \param          [in]    plugin           plugin specific data
*
*  \param          [in]    nodeAddr         NodeAddress -1(0xFF)=master
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void a2b_ReportI2CError(a2b_Plugin *plugin, a2b_Int16 nodeAddr)
{
	struct a2b_Msg* notification;
	a2b_I2CError* I2CError;
	a2b_HResult result = A2B_RESULT_SUCCESS;

    /* Allocate a notification message */
    notification = a2b_msgAlloc(plugin->ctx,
                                A2B_MSG_NOTIFY,
								A2B_MSGREQ_PERIPH_I2C_ERROR_APP);

    if ( A2B_NULL == notification )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("a2b_I2CErrorReported: failed to allocate notification");
#else   
        A2B_TRACE0((plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                "a2b_I2CErrorReported: "
                "failed to allocate notification"));
#endif
    }
    else
    {
    	I2CError = (a2b_I2CError*)a2b_msgGetPayload(notification);
    	I2CError->I2CAddr = (nodeAddr & 0xFF00) >> 8u;
		I2CError->nodeAddr = nodeAddr & 0xFF;
        /* Make best effort delivery of notification */
        result = a2b_msgRtrNotify(notification);
        if ( A2B_FAILED(result) )
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("a2b_I2CErrorReported: failed to report I2C Error: 0x%lX",&result);
#else        
            A2B_TRACE1((plugin->ctx,
                    (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "a2b_I2CErrorReported: "
                    "failed to report I2C Error: 0x%lX",
                    &result));
#endif
        }

        /* We no longer need this message */
        (void)a2b_msgUnref(notification);
    }
}

/*!****************************************************************************
*
*  \b              a2b_ReportI2CError
*
*  This serves as a notification callback function. This function is called when
*  I2C error is reported from slave plugin
*
*  \param          [in]    msg           A2B message instance
*
*  \param          [in]    userData      An opaque pointer to user defined data
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void a2b_I2CErrorReported(struct a2b_Msg* msg, a2b_Handle userData)
{
	a2b_Plugin	*plugin;
	a2b_Int16   nodeAddr=0;

	if(msg)
	{
		/* Getting master plugin handle from user data in notify message */
		plugin 		= (a2b_Plugin*)a2b_msgGetUserData(msg);

		/* Getting the current slave node address which emitted this notification */
		nodeAddr 	= (a2b_Int16)a2b_msgGetTid(msg);

		a2b_ReportI2CError(plugin, nodeAddr);
	}
}

/*!****************************************************************************
*
*  \b              a2b_FinalMasterSetup
*
*  Final setup of master node after discovery. This is called at the last for
*  all modes of discovery except Advanced Mode. In advanced mode, this function
*  is repeatedly called after reconfiguration of slots at each node.
*
*  \param          [in]    plugin           plugin specific data
*
*  \param          [in]    nodeAddr          NodeAddress -1=master
*
*  \pre            None
*
*  \post           None
*
*  \return         A2B_TRUE == NetConfiguration is to be done
*                  A2B_FALSE == NetConfiguration is not to be done
*
******************************************************************************/
static a2b_HResult
a2b_FinalMasterSetup(a2b_Plugin* plugin,
		a2b_Int16   nodeAddr)
{
	a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_Bool isAd242xMaster = A2B_FALSE;
    a2b_UInt32 i2cCount = 0u;
    a2b_UInt8 wBuf[4u];
    a2b_UInt8 rBuf[4u];
    a2b_Int16 nodeIdx = nodeAddr+1;
    a2b_Int16 node;
    bdd_DiscoveryMode eDscMode;


    if ((A2B_NODEADDR_MASTER == nodeAddr) && (plugin != A2B_NULL))
    {
		wBuf[0] = A2B_REG_NODEADR;
		wBuf[1] = 0x0u;
		status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );

        if ( plugin->nodeSig.hasSiliconInfo )
        {
            isAd242xMaster = a2b_isAd242xChip(
                                            plugin->nodeSig.siliconInfo.vendorId,
                                            plugin->nodeSig.siliconInfo.productId);
        }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rFinal Master Setup" );
#else
        A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                              "Final Master Setup" );
#endif
		
		/* Configuration of Spread spectrum - AD2428 onwards */
		(void)a2b_ConfigSpreadSpectrum(plugin, nodeAddr);

		wBuf[0] = A2B_REG_NODEADR;
		wBuf[1] = (a2b_UInt8)0;
		status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
		i2cCount++;

		if (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_slotfmt)
		{
			wBuf[0] = A2B_REG_SLOTFMT;
			wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.slotfmt;
			status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
			i2cCount++;
		}

		if ( A2B_SUCCEEDED(status) )
		{
			/* Enable the up and downstream slots */
			wBuf[0] = A2B_REG_DATCTL;

			if (plugin->bdd->nodes[nodeIdx].ctrlRegs.has_datctl) 
			{
				wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].ctrlRegs.datctl;
			}
			else 
			{
				wBuf[1] = A2B_BITM_DATCTL_UPS | A2B_BITM_DATCTL_DNS;
			}
			status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
			i2cCount++;
		}

		/* A2B_REG_I2SRRATE - AD242X only, Master node only */
		if ( (A2B_SUCCEEDED(status)) &&
			(isAd242xMaster) &&
			(plugin->bdd->nodes[nodeIdx].i2cI2sRegs.has_i2srrate ))
		{
			wBuf[0] = A2B_REG_I2SRRATE;
			wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.i2srrate;
			status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
			i2cCount++;
		}

		if ( A2B_SUCCEEDED(status) )
		{
			/* Push all shadowed/cached registers */
			wBuf[0] = A2B_REG_CONTROL;
			/* The AD242X (only) needs to be told it's a Master node
			 * BEFORE the PLL locks on the SYNC pin. Once the PLL is
			 * locked, setting the MSTR bit is ignored. We set it
			 * anyway so it's clear this is the master node.
			 */
			wBuf[1] = A2B_ENUM_CONTROL_START_NS;
			if ( isAd242xMaster )
			{
				wBuf[1] |= (a2b_UInt8)A2B_ENUM_CONTROL_MSTR;
			}
			/* Adding additional bit fields with AD2428 onwards */
			wBuf[1] |= (a2b_UInt8)(plugin->bdd->nodes[nodeIdx].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
			status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
			/*Apply delay for new structure to take effect*/
			a2b_ActiveDelay(plugin->ctx, 1u);
			i2cCount++;
		}

        eDscMode = a2b_ovrGetDiscMode(plugin);

        if ((bdd_DISCOVERY_MODE_ADVANCED == eDscMode) && ((a2b_Int16)(plugin->discovery.dscNumNodes) == plugin->bdd->nodes_count - 1u))
        {
            for (node = plugin->bdd->nodes_count - 2u; node >= 0; node--)
            {
                /* CLear BECNT for Sub node*/
                wBuf[0u] = A2B_REG_BECNT;
                wBuf[1] = 0U;
                status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)node), 2u, wBuf);
                if (A2B_FAILED(status))
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cputs("\n\rBECNT Register Write Failed");
#else                
                	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                        "BECNT Register Write Failed");
#endif
                }

                /* Enable BECCTL count for sub node*/
                wBuf[0u] = A2B_REG_BECCTL;
                wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].intRegs.becctl;
                status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)node), 2u, wBuf);
                if (A2B_FAILED(status))
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cputs("\n\rBECCTL Register Write Failed");
#else                
                	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                        "BECCTL Register Write Failed");
#endif
                }

                /* Enable BECOVF interrupt for sub Node*/
                wBuf[0u] = A2B_REG_INTMSK0;
                rBuf[0] = 0U;
                status = a2b_i2cSlaveWriteRead(plugin->ctx, ((a2b_Int16)node), 1, wBuf, 1, rBuf);

                if (A2B_FAILED(status))
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cputs("\n\rINTMASK0 Register Read Failed");
#else
                	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                        "INTMASK0 Register Read Failed");
#endif
                }
                else
                {
                    wBuf[1] = rBuf[0] | A2B_BITM_INTPND0_BECOVF;
                    status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)node), 2u, wBuf);
                    if (A2B_FAILED(status))
                    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
						cputs("\n\rINTMSK0 Register Write Failed");
#else
                    	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                            "INTMSK0 Register Write Failed");
#endif
                    }
                }
            }
            /* Clear BECNT for Main node */
            wBuf[0u] = A2B_REG_BECNT;
            wBuf[1] = 0U;
            status = a2b_i2cMasterWrite(plugin->ctx, 2u, wBuf);
            if (A2B_FAILED(status))
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rBECNT Register Write Failed");
#else            
            	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                    "BECNT Register Write Failed");
#endif
            }
            /* Enable BECCTL count for Main node*/
            wBuf[0u] = A2B_REG_BECCTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[0U].intRegs.becctl;
            status = a2b_i2cMasterWrite(plugin->ctx, 2u, wBuf);
            if (A2B_FAILED(status))
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rBECCTL Register Write Failed");
#else            
            	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                    "BECCTL Register Write Failed");
#endif

            }

            /* Enable BECOVF interrupt for Main Node*/
            wBuf[0u] = A2B_REG_INTMSK0;
            rBuf[0] = 0U;
            status = a2b_i2cMasterWriteRead(plugin->ctx, 1, wBuf, 1, rBuf);

            if (A2B_FAILED(status))
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
  				cputs("\n\rINTMSK0 Register Read Failed");
#else          
            	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                    "INTMSK0 Register Read Failed");
#endif
            }
            else
            {
                wBuf[1] = rBuf[0] | A2B_BITM_INTPND0_BECOVF;
                status = a2b_i2cMasterWrite(plugin->ctx, 2u, wBuf);
                if (A2B_FAILED(status))
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				  cputs("\n\rINTMSK0 Register Write Failed");
#else                
                	A2B_DSCVRY_ERROR0(plugin->ctx, a2b_FinalMasterSetup,
                        "INTMSK0 Register Write Failed");
#endif                        
                }
            }
        }
		A2B_DSCVRY_SEQEND( plugin->ctx );
    }
    return status;

} /* a2b_FinalMasterSetup */


/*!****************************************************************************
*
*  \b              a2b_ConfigSpreadSpectrum
*
*  Final setup of Spread Spectrum Configuration.
*
*  \param          [in]    plugin           plugin specific data
*
*  \param          [in]    nodeAddr          NodeAddress -1=master
*
*  \pre            None
*
*  \post           None
*
*  \return         A2B_TRUE == NetConfiguration is to be done
*                  A2B_FALSE == NetConfiguration is not to be done
*
******************************************************************************/
static a2b_HResult
a2b_ConfigSpreadSpectrum(a2b_Plugin* plugin,
		a2b_Int16   nodeAddr)
{
	a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_Bool isAd2428Master = A2B_FALSE;
    a2b_UInt8 wBuf[4u], nIndex;
    a2b_Int16 nodeIdx = nodeAddr+1;
	a2b_Int16 slvNodeAddr = 0;
	a2b_Int16 slvNodeIdx = 0;
	a2b_Bool commnSpreadSpectrum = A2B_FALSE;

    if ((A2B_NODEADDR_MASTER == nodeAddr) && (plugin != A2B_NULL))
    {
		commnSpreadSpectrum = (a2b_Bool)plugin->bdd->policy.has_common_SSSettings;

		wBuf[0] = A2B_REG_NODEADR;
		wBuf[1] = 0x0u;
		status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
        if ( plugin->nodeSig.hasSiliconInfo )
        {
            isAd2428Master = A2B_IS_AD2428X_CHIP(
                                            plugin->nodeSig.siliconInfo.vendorId,
                                            plugin->nodeSig.siliconInfo.productId);
        }
		if(isAd2428Master)
		{
			wBuf[0] = A2B_REG_PLLCTL;
			wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeIdx].i2cI2sRegs.pllctl;
			/* Check whether all nodes should have common spread spectrum settings */
			if(commnSpreadSpectrum)
			{
				status = a2b_i2cSlaveBroadcastWrite(plugin->ctx, 2u, wBuf);
			}
			else
			{
				status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
			}
		}
		if((plugin->discovery.dscNumNodes) && (commnSpreadSpectrum == A2B_FALSE))
		{
			/*If the every node has separate settings*/
			for(nIndex = 0u; nIndex < plugin->discovery.dscNumNodes; nIndex++)
			{
				slvNodeAddr = (a2b_Int16)nIndex;
				slvNodeIdx = slvNodeAddr + 1;
				if(plugin->bdd->nodes[slvNodeIdx].i2cI2sRegs.has_pllctl)
				{
					wBuf[0u] = A2B_REG_PLLCTL;
					wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[slvNodeIdx].i2cI2sRegs.pllctl;
					status = a2b_i2cSlaveWrite(plugin->ctx, slvNodeAddr , 2u, wBuf );
				}

			}
		}

    
    }
    return status;

} /* a2b_ConfigSpreadSpectrum */


/*!****************************************************************************
*
*  \b              a2b_dscvryNetComplete
*
*  Final cleanup steps of network discovery
*  (i.e. when all nodes have been found.)
* 
*  In the case of Simplified Discovery this method can be called more than once.
*
*  \param          [in]    plugin   plugin specific data
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryNetComplete
    (
    a2b_Plugin* plugin
    )
{
    a2b_UInt8 wBuf[4];
    a2b_Int16 nodeAddr;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_Bool initMaster = A2B_TRUE;
    a2b_UInt32 errCode = (a2b_UInt32)A2B_EC_OK;
    a2b_Int32 retCode;
    a2b_Bool bDoEepromCfg = A2B_TRUE;

#ifdef A2B_FEATURE_SEQ_CHART
    a2b_Bool bSeqGroupShown = A2B_FALSE;
#endif

#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
    a2b_Int16 nTempVar;
#if !defined(A2B_FEATURE_SEQ_CHART)
    A2B_UNUSED(nTempVar);
#endif
#endif

    if ( !plugin->discovery.inDiscovery )
    {
        return;
    }

    if ( bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin) )
    {
        a2b_Bool bContLoop;

#ifndef A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY
        /* When disabled using Simple discovery the node init will be
         * completed for all nodes, then all peripheral config is queued
         * and will execute cooperatively.  Whereas when enabled the node
         * init is completed followed by the nodes peripheral processing
         * followed by the next nodes int, and so on.
         */
        bDoEepromCfg = A2B_FALSE;
#endif /* A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY */

        /* Start from the latest to the first (per spec) */
        for ( nodeAddr = ((a2b_Int16)plugin->discovery.simpleNodeCount-(a2b_Int16)1);
              nodeAddr > A2B_NODEADDR_MASTER; 
              nodeAddr-- )
        {
#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
            nTempVar = nodeAddr;
#endif
            bContLoop = A2B_FALSE;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			  cputs("\n\rNetComplete");
#else
            A2B_DSCVRY_SEQGROUP0_COND( plugin->ctx, bSeqGroupShown,
                                       "NetComplete" );
#endif

            retCode = a2b_dscvryNodeComplete( plugin, nodeAddr, 
                                              bDoEepromCfg, &errCode );
            plugin->discovery.simpleNodeCount--;

            if ( A2B_EXEC_COMPLETE_FAIL == retCode )
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rFailed to complete node %hd init");
#else            
                A2B_DSCVRY_ERROR1( plugin->ctx, "NetComplete",
                                   "Failed to complete node %hd init", 
                                   &nTempVar );
#endif                                   
                a2b_dscvryEnd( plugin, errCode );
            }
            else if ( A2B_EXEC_COMPLETE == retCode )
            {
                /* a2b_dscvryInitPlugin() will also check for an
                 * available plugin, however, if no plugin is 
                 * available for a plugin it will call the callback 
                 * right away.  So to avoid a situation where few
                 * or no plugins are in our setup we could possibly 
                 * blow the stack on some systems.  So to avoid
                 * growing the stack unnecessarily we check here
                 * for a plugin and if not available we will loop
                 * to the next plugin.
                 */
#ifdef A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY

#ifdef FIND_NODE_HANDLER_AFTER_NODE_INIT
                a2b_dscvryFindNodeHandler(plugin,
                            A2B_MAP_SLAVE_ADDR_TO_INDEX(nodeAddr));
#endif
                if ( A2B_HAS_PLUGIN(plugin, nodeAddr) )
                {
#if !defined(A2B_BCF_FROM_SOC_EEPROM) && !defined(A2B_BCF_FROM_FILE_IO)
                    errCode = a2b_dscvryInitPlugin( plugin, nodeAddr,
                                  &a2b_dscvryInitPluginComplete_EepromComplete );

                    if ((a2b_UInt32)A2B_EC_OK != errCode )
                    {
                        a2b_dscvryEnd( plugin, errCode );
                    }
                    /* else, waiting for plugin message to process */
#endif
                }
                else
#endif /* A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY */
                {
                    /* Process the next plugin using this routine */
                    bContLoop = A2B_TRUE;
                }
            }
            else
            {
                /* Completing the control statement */
            }
            /* else, waiting for peripheral node processing to complete */

            if ( !bContLoop )
            {
                A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
                return;
            }
        }

#ifndef A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY
        for ( nodeAddr = plugin->discovery.dscNumNodes-1;
              nodeAddr > A2B_NODEADDR_MASTER; 
              nodeAddr-- )
        {
            retCode = A2B_EXEC_COMPLETE;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
            if ( A2B_HAS_EEPROM(plugin, nodeAddr) )
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
  				cputs("\n\rNetComplete" );
#else            
                A2B_DSCVRY_SEQGROUP0_COND( plugin->ctx, bSeqGroupShown,
                                           "NetComplete" );
#endif

                retCode = a2b_periphCfgInitProcessing( plugin, nodeAddr );
                if ( A2B_EXEC_COMPLETE_FAIL == retCode )
                {
                    /* On an error we need to clear the hasEeprom tracking */
                    plugin->discovery.hasEeprom = 0;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				  cputs("\n\rnodeComplete EEPROM Processing Failed" );
#else
                    A2B_DSCVRY_ERROR0( plugin->ctx, "nodeComplete",
                                       "EEPROM Processing Failed" );
#endif                                       
                    a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_IO );
                    A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
                    return;
                }
            }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

            if ( A2B_EXEC_COMPLETE == retCode )
            {
#ifdef FIND_NODE_HANDLER_AFTER_NODE_INIT
                a2b_dscvryFindNodeHandler(plugin,
                                        A2B_MAP_SLAVE_ADDR_TO_INDEX(nodeAddr));
#endif
                if ( A2B_HAS_PLUGIN(plugin, nodeAddr) &&
                     A2B_NEEDS_PLUGIN_INIT(plugin, nodeAddr) )
                {
                    /* This ensures we will only queue the message to
                     * the peripheral mailbox for this node.
                     */
                    errCode = a2b_dscvryInitPlugin( plugin, nodeAddr,
                              a2b_dscvryInitPluginComplete_EepromComplete );
                    if ( A2B_EC_OK != errCode )
                    {
                        a2b_dscvryEnd( plugin, errCode );
                        A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
                        return;
                    }
                    /* else, waiting for plugin message to process */
                }
            }
#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
            else if (( A2B_EXEC_SUSPEND == retCode ) &&
                     (a2b_periphCfgUsingSync()) )
            {
                /* MUST be waiting for a delay to complete 
                 * while synchronous cfg blocks processing
                 * is expected.
                 */
                A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
                return;
            }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */
        }

        if (( plugin->discovery.hasEeprom ) ||
            (plugin->discovery.pendingPluginInit ) )
        {
            initMaster = A2B_FALSE;
        }

#endif /* A2B_FEATURE_WAIT_ON_PERIPHERAL_CFG_DELAY */

    }
    else /* if ( bdd_DISCOVERY_MODE_MODIFIED == a2b_ovrGetDiscMode(plugin) )*/
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
  		cputs("\n\rNetComplete" );
#else    
        A2B_DSCVRY_SEQGROUP0_COND( plugin->ctx, bSeqGroupShown,
                                   "NetComplete" );
#endif

        /* If the nodeAddr we were trying to discover was Slave0 
         * then we skip this final step on the node.
         */
        if (plugin->discovery.dscNumNodes != 0u)
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rAdjust Node Power" );
#else        
            A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                                  "Adjust Node Power" );
#endif

            /* We need to adjust the power setting on the discovered nodes */
            for ( nodeAddr = ((a2b_Int16)plugin->discovery.dscNumNodes-(a2b_Int16)2);
                  nodeAddr > A2B_NODEADDR_MASTER; 
                  nodeAddr-- )
            {
#ifdef A2B_FEATURE_TRACE
                nTempVar = nodeAddr;
#endif
                wBuf[0] = A2B_REG_SWCTL;
                wBuf[1] = A2B_ENUM_SWCTL_ENSW_EN;
                status = a2b_i2cSlaveWrite( plugin->ctx, nodeAddr, 2u, wBuf );
                if ( A2B_FAILED(status) )
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cputs("\n\rCannot adjust power on nodeAddr: %hd");
#else
                    A2B_DSCVRY_ERROR1( plugin->ctx, "NetComplete",
                                       "Cannot adjust power on nodeAddr: %hd",
                                       &nTempVar );
#endif                                       
                    initMaster = A2B_FALSE;
                    break;
                }
            }

			wBuf[0] = A2B_REG_SWCTL;
            wBuf[1] = A2B_ENUM_SWCTL_ENSW_EN;
            status = a2b_i2cMasterWrite( plugin->ctx, 2u, wBuf );
            if ( A2B_FAILED(status) )
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rCannot adjust power on nodeAddr: %hd");
#else            
                A2B_DSCVRY_ERROR1( plugin->ctx, "NetComplete",
                                    "Cannot adjust power on nodeAddr: %hd",
                                    &nTempVar );
#endif                                    
                initMaster = A2B_FALSE;
            }

            A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
        }
    }

    if ( bdd_DISCOVERY_MODE_ADVANCED == a2b_ovrGetDiscMode(plugin) )
    {
    	initMaster = A2B_FALSE;
    }

    if ( initMaster )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rNetComplete" );
#else    
        A2B_DSCVRY_SEQGROUP0_COND( plugin->ctx, bSeqGroupShown,
                                   "NetComplete" );
#endif

        a2b_dscvryInitTdmSettings( plugin, A2B_NODEADDR_MASTER );
        status = a2b_audioConfig( plugin->ctx, &plugin->pluginTdmSettings );

        if ( A2B_FAILED(status) )
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rNetComplete Cannot config audio for nodeAddr: %hd",
                               &nodeAddr );
#else        
            A2B_DSCVRY_ERROR1( plugin->ctx, "NetComplete",
                               "Cannot config audio for nodeAddr: %hd",
                               &nodeAddr );
#endif                               
            a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_IO );
            A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
            return;
        }

        /* Do final setup of the master node and enable the up/downstream */
        if (a2b_dscvryNodeComplete( plugin, A2B_NODEADDR_MASTER, 
                                 A2B_TRUE, &errCode ) == A2B_EXEC_COMPLETE_FAIL)
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rNetComplete Failed to complete master node init" );
#else        
            A2B_DSCVRY_ERROR0( plugin->ctx, "NetComplete",
                               "Failed to complete master node init" );
#endif                               
        }
        else
        {
			status = a2b_FinalMasterSetup(plugin, A2B_NODEADDR_MASTER);
			if(status != A2B_RESULT_SUCCESS)
			{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rNetComplete Failed to complete master node init" );
#else			
				A2B_DSCVRY_ERROR0( plugin->ctx, "NetComplete",
								   "Failed to complete master node init" );
#endif								   
			}
        }

        if ( bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin) )
        {
            /* We only reach this is Simple discovery has completed */
        	if((plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_BUSY) ||
        	   (plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_PERMISSION) ||
			   (plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH) ||
			   (plugin->discovery.discoveryCompleteCode == (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE))
        	{
        		errCode = plugin->discovery.discoveryCompleteCode;
        	}
        	plugin->discovery.discoveryComplete = A2B_TRUE;
            a2b_dscvryEnd( plugin, errCode );
        }
    }

    A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );

} /* a2b_dscvryNetComplete */


/*!****************************************************************************
*
*  \b              a2b_dscvryPreSlaveInit
*
*  Steps taken before finding the next slave node during discovery
*
*  \param          [in]    plugin       plugin specific data
*
*  \pre            None
*
*  \post           The following registers are altered:
*                  A2B_REG_SWCTL
*                  A2B_REG_DISCVRY
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool
a2b_dscvryPreSlaveInit
    (
    a2b_Plugin* plugin
    )
{
    a2b_UInt8 wBuf[4u];
	a2b_HResult status;
	a2b_UInt32 value;
	struct a2b_StackContext* ctx = plugin->ctx;
	a2b_Bool  isXTalkFixApplicable;
    bdd_DiscoveryMode  eDiscMode;
	const bdd_Node      *bddNodeObj;

	/* Discovered node information */
	a2b_Int16 dscNodeBddIdx = (a2b_Int16)plugin->discovery.dscNumNodes;
	a2b_Int16 dscNodeAddr = dscNodeBddIdx - 1;

    eDiscMode = a2b_ovrGetDiscMode(plugin);

	/* Must add one to account for the fact that the nodes_count
	 * also includes the master node.
	 */
	if (plugin->discovery.dscNumNodes + (a2b_UInt8)1 >= (a2b_UInt8)plugin->bdd->nodes_count)
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s PreSlaveInit(): No more BDD slave nodes",
			A2B_MPLUGIN_PLUGIN_NAME);
#else	
		A2B_TRACE1((ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
			"%s PreSlaveInit(): No more BDD slave nodes",
			A2B_MPLUGIN_PLUGIN_NAME));
#endif
		if (bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin))
		{
			/* For simple discovery we need to now complete the network
			 * and ensure the peripherals are complete before we call
			 * a2b_dscvryEnd.  If we have peripherals to work on an early
			 * call to a2b_dscvryEnd it will just exit.
			 */
			a2b_dscvryNetComplete(plugin);
		}
		else if (bdd_DISCOVERY_MODE_MODIFIED == a2b_ovrGetDiscMode(plugin)) /* bdd_DISCOVERY_MODE_MODIFIED */
		{
			/* We have completed the modified discovery.  We will call the
			 * a2b_dscvryEnd and it will check if the peripherals have
			 * finished processing
			 */
			a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_OK);
		}
		else
		{
			/* completing control statement */
		}

		return A2B_FALSE;
	}

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rPreSlaveInit");
#else
	A2B_DSCVRY_SEQGROUP0(plugin->ctx,
		"PreSlaveInit");
#endif

	if (plugin->bdd->nodes[dscNodeBddIdx].ctrlRegs.has_control)
	{
		/* Write to Control register to Set LVDS Polarity, applicable only after AD2428
		*/
		wBuf[0] = A2B_REG_CONTROL;
		wBuf[1] = (a2b_UInt8)(plugin->bdd->nodes[dscNodeBddIdx].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
		status = a2b_i2cSlaveWrite(ctx, dscNodeAddr, 2u, wBuf);

		if (A2B_FAILED(status))
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rPreSlaveInit Cannot write to CONTROL Reg nodeAddr: %hd",
				&dscNodeAddr);
#else		
			A2B_DSCVRY_ERROR1(ctx, "PreSlaveInit",
				"Cannot write to CONTROL Reg nodeAddr: %hd",
				&dscNodeAddr);
#endif				
			a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
			A2B_DSCVRY_SEQEND(plugin->ctx);
			return A2B_FALSE;
		}
    }

    /* We need to enable phantom power to the next node,
     * to do so we write to the just discovered node.
     */
    wBuf[0] = A2B_REG_SWCTL;
    wBuf[1] = A2B_ENUM_SWCTL_ENSW_EN;
    status = a2b_i2cSlaveWrite( ctx, dscNodeAddr, 2u, wBuf );

    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rPreSlaveInit Cannot enable phantom power on nodeAddr: %hd",
                           &dscNodeAddr );
#else    
        A2B_DSCVRY_ERROR1( ctx, "PreSlaveInit",
                           "Cannot enable phantom power on nodeAddr: %hd",
                           &dscNodeAddr );
#endif                           
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }

    /* Only listen for power fault interrupts if it's not the last node
     * in the network. It's likely the last node will always report an
     * open circuit power fault and therefore that interrupt is not enabled
     * on this node
     */

    /* Set up INTMSK0 so we can see power fault interrupts during discovery */
    value = a2b_intrGetMask( ctx, dscNodeAddr );
    if ( value == A2B_INTRMASK_READERR )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rPreSlaveInit Cannot read INTMSK0-2 on nodeAddr: %hd",
                           &dscNodeAddr );
#else    
        A2B_DSCVRY_ERROR1( ctx, "PreSlaveInit",
                           "Cannot read INTMSK0-2 on nodeAddr: %hd",
                           &dscNodeAddr );
#endif                           
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }
    else
    {
        /* Unmask all interrupts which might be helpful for diagnosing
         * discovery failures.
         */
        value |= (
               (a2b_UInt32)A2B_BITM_INTPND0_PWRERR
#if 0
             | A2B_BITM_INTPND0_SRFERR
             | A2B_BITM_INTPND0_BECOVF
             | A2B_BITM_INTPND0_DPERR
             | A2B_BITM_INTPND0_CRCERR
             | A2B_BITM_INTPND0_DDERR
             | A2B_BITM_INTPND0_HDCNTERR
#endif
             ) << (a2b_UInt32)A2B_INTRMASK0_OFFSET
             ;

        status = a2b_intrSetMask( ctx, dscNodeAddr, value );
        if ( A2B_FAILED(status) )
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rPreSlaveInit Cannot write to INTMSK0-2 on nodeAddr: %hd",
                               &dscNodeAddr );
#else        
            A2B_DSCVRY_ERROR1( ctx, "PreSlaveInit",
                               "Cannot write to INTMSK0-2 on nodeAddr: %hd",
                               &dscNodeAddr );
#endif

            A2B_DSCVRY_SEQEND( plugin->ctx );
            return A2B_FALSE;
        }
    }

    /* Setup/Start the discovery timer */
  


	/* Check whether the discovering node belongs to AD2425 series */
	bddNodeObj = &plugin->bdd->nodes[dscNodeBddIdx];
    isXTalkFixApplicable = a2b_isCrossTalkFixApply(bddNodeObj->nodeDescr.vendor, bddNodeObj->nodeDescr.product);

    if ((eDiscMode != bdd_DISCOVERY_MODE_OPTIMIZED) && (eDiscMode != bdd_DISCOVERY_MODE_ADVANCED))
    {        
        if (!a2b_dscvryStartTimer(plugin, TIMER_DSCVRY))
        {
            A2B_DSCVRY_SEQEND(plugin->ctx);
            return A2B_FALSE;
        }

        wBuf[0] = A2B_REG_DISCVRY;
        /* Cross Talk fix is enable, then increase the response cycle */
        if ((plugin->bdd->policy.bCrossTalkFixApply == A2B_TRUE) && (isXTalkFixApplicable == A2B_TRUE))
        {
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs + 2u;
        }
        else
        {
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[dscNodeBddIdx + 1].ctrlRegs.respcycs;
        }
        status = a2b_i2cMasterWrite(ctx, 2u, &wBuf);

        if (A2B_FAILED(status))
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rPreSlaveInit Cannot discover next node");
#else        
            A2B_DSCVRY_ERROR0(ctx, "PreSlaveInit", "Cannot discover next node");
#endif            
            a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
            A2B_DSCVRY_SEQEND(plugin->ctx);
            return A2B_FALSE;
        }
    }

    

    /* Now we wait for INTTYPE.DSCDONE */
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rdscvryPreSlaveInit...Waiting for INTTYPE.DSCDONE..." );
#else
    A2B_DSCVRY_RAWDEBUG0( plugin->ctx, "dscvryPreSlaveInit", 
                          "...Waiting for INTTYPE.DSCDONE..." );
#endif

    A2B_DSCVRY_SEQEND( plugin->ctx );

    return A2B_TRUE;

} /* a2b_dscvryPreSlaveInit */


/*!****************************************************************************
*
*  \b              a2b_dscvryPreMasterInit
*
*  Steps taken to init the master node before discovery
*
*  \param          [in]    plugin       plugin specific data
*
*  \pre            None
*
*  \post           The following registers are altered:
*                  A2B_REG_INTMSK0/1/2
*                  A2B_REG_INTPND2
*                  A2B_REG_RESPCYCS
*                  A2B_REG_CONTROL
*                  A2B_REG_PLLCTL
*                  A2B_REG_I2SGCFG
*                  A2B_REG_SWCTL
*                  A2B_REG_DISCVRY
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool
a2b_dscvryPreMasterInit
    (
    a2b_Plugin* plugin
    )
{
    a2b_UInt8 wBuf[4];
    a2b_UInt8 rBuf[3];
    a2b_Bool isAd242x = A2B_FALSE;
	a2b_Bool isAd2428 = A2B_FALSE;
    a2b_UInt8 masterBddIdx = A2B_MASTER_NODEBDDIDX;
    struct a2b_StackContext* ctx = plugin->ctx;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_UInt32 i2cCount = 0u;
    a2b_UInt32 errCode;
#ifdef A2B_FEATURE_SEQ_CHART
    a2b_Int32 nNodeAddr;
    a2b_Bool bSeqGroupShown = A2B_FALSE;
#endif
	const bdd_Node      *bddNodeObj;

	bddNodeObj = &plugin->bdd->nodes[0];

    /* The one node would be the master node only */
    if ( 1u == plugin->bdd->nodes_count )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rPreMasterInit No slave nodes" );
#else    
        A2B_DSCVRY_ERROR0( ctx, "PreMasterInit", "No slave nodes" );
#endif        
        return A2B_FALSE;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rPreMasterInit" );
#else
    A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                          "PreMasterInit" );
#endif

    /* Read the master node's VID/PID/Version */
    wBuf[0] = A2B_REG_VENDOR;
    status  = a2b_i2cMasterWriteRead( plugin->ctx, 1u, wBuf, 3u, rBuf );
    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rFailed to read vid/pid/version of the master node");
#else    
        A2B_SEQ_GENNOTE0( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
                          "Failed to read vid/pid/version of the master node" );
#endif                          
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }
    plugin->nodeSig.hasSiliconInfo = A2B_TRUE;
    plugin->nodeSig.siliconInfo.vendorId = rBuf[0u];
    plugin->nodeSig.siliconInfo.productId = rBuf[1u];
    plugin->nodeSig.siliconInfo.version = rBuf[2u];
    if(bddNodeObj->verifyNodeDescr)
	{
		if ((bddNodeObj->nodeDescr.product != plugin->nodeSig.siliconInfo.productId)||
				(bddNodeObj->nodeDescr.version != plugin->nodeSig.siliconInfo.version))
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rmaster pid violation");
#else		
			A2B_SEQ_GENNOTE0(plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
				"master pid violation");
#endif				
			A2B_DSCVRY_SEQEND(plugin->ctx);
			a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_INTERNAL);
			return A2B_FALSE;
		}
	}

    isAd242x = a2b_isAd242xChip(plugin->nodeSig.siliconInfo.vendorId,
                                  plugin->nodeSig.siliconInfo.productId);

	isAd2428 = A2B_IS_AD2428X_CHIP(plugin->nodeSig.siliconInfo.vendorId,
		plugin->nodeSig.siliconInfo.productId);
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\r %s Master Node: Silicon vid/pid/ver: %02bX/%02bX/%02bX",
                        A2B_MPLUGIN_PLUGIN_NAME,
                        &(plugin->nodeSig.siliconInfo.vendorId),
                        &(plugin->nodeSig.siliconInfo.productId),
                        &(plugin->nodeSig.siliconInfo.version));
	cprintf("\n\r Master Node Silicon: vid/pid/ver: %02bX/%02bX/%02bX",
                      &(plugin->nodeSig.siliconInfo.vendorId),
                      &(plugin->nodeSig.siliconInfo.productId),
                      &(plugin->nodeSig.siliconInfo.version));
#else
    A2B_TRACE4( (ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
                        "%s Master Node: Silicon vid/pid/ver: "
                        "%02bX/%02bX/%02bX",
                        A2B_MPLUGIN_PLUGIN_NAME,
                        &(plugin->nodeSig.siliconInfo.vendorId),
                        &(plugin->nodeSig.siliconInfo.productId),
                        &(plugin->nodeSig.siliconInfo.version) ));

    A2B_SEQ_GENNOTE3( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
                      "Master Node Silicon: vid/pid/ver: %02bX/%02bX/%02bX",
                      &(plugin->nodeSig.siliconInfo.vendorId),
                      &(plugin->nodeSig.siliconInfo.productId),
                      &(plugin->nodeSig.siliconInfo.version) );
#endif

    /* Initialize Interrupts */
    /*-----------------------*/
    if (!a2b_dscvryNodeInterruptInit(plugin, (a2b_Int16)masterBddIdx))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rFailed to init node interrupts" );
#else    
        A2B_SEQ_GENNOTE0( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY, 
                          "Failed to init node interrupts" );
#endif                          
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }

#ifdef A2B_FEATURE_COMM_CH
    /* Initialize Mailbox registers  */
    /*-----------------------*/
    if (!a2b_dscvryNodeMailboxInit(plugin, (a2b_Int16)masterBddIdx))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rFailed to init mailbox registers" );
#else    
        A2B_SEQ_GENNOTE0( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
                          "Failed to init mailbox registers" );
#endif                          
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }
#endif	/* A2B_FEATURE_COMM_CH */

    /* Clear the DSCDONE pending flag prior to starting discovery */
    wBuf[0] = A2B_REG_INTPND2;
    wBuf[1] = A2B_BITM_INTPND2_DSCDONE;
    status  = a2b_i2cMasterWrite(ctx, 2u, wBuf);
    i2cCount++;

    /* NOTE: A2B_REG_NODEADR managed by I2C, no need to set it */

    if ( A2B_SUCCEEDED(status) )
    {
        /* Set the response cycle timing */
        wBuf[0] = A2B_REG_RESPCYCS;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[masterBddIdx].ctrlRegs.respcycs;
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
        i2cCount++;
    }

	if (A2B_SUCCEEDED(status))
	{
		/* Push respcycs to appropriate nodes */
		wBuf[0] = A2B_REG_CONTROL;
		/* The AD242X (only) needs to be told it's a Master node BEFORE
		 * the PLL locks on the SYNC pin. Once the PLL is locked, setting
		 * the MSTR bit is ignored. We set it anyway so it's clear this is
		 * the master node.
		 */
		wBuf[1] = A2B_ENUM_CONTROL_START_NS;
		if (isAd242x)
		{
			wBuf[1] |= (a2b_UInt8)A2B_ENUM_CONTROL_MSTR;
		}
		if (isAd2428)
		{
			wBuf[1] |= (a2b_UInt8)(plugin->bdd->nodes[masterBddIdx].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
	    }
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
		/*Apply delay for new structure to take effect*/
		a2b_ActiveDelay(plugin->ctx, 1u);
        i2cCount++;
    }

    /* PLLCTL only exists on older AD24XX chips (e.g. 2410) */
    if ( (A2B_SUCCEEDED(status)) && (!isAd242x) )
    {
        /* PLL configuration */
        wBuf[0] = A2B_REG_PLLCTL;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[masterBddIdx].i2cI2sRegs.pllctl;
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) )
    {
        /* Rev1.0 requirement -- effects the PLL */
        wBuf[0] = A2B_REG_I2SGCFG;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[masterBddIdx].i2cI2sRegs.i2sgcfg;
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_SUCCEEDED(status) )
    {
        wBuf[0] = A2B_REG_SWCTL;
        wBuf[1] = A2B_BITM_SWCTL_ENSW;
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
        i2cCount++;
    }

    /* Setup/Start the discovery timer */
    if (!a2b_dscvryStartTimer( plugin, TIMER_DSCVRY ))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rFailed to init discovery timer" );
#else    
        A2B_SEQ_GENERROR0( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY, 
                           "Failed to init discovery timer" );
#endif                           
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }

    if ( A2B_SUCCEEDED(status) )
    {
        /* Start Discovery of Next Node */
        wBuf[0] = A2B_REG_DISCVRY;
        wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[masterBddIdx+(a2b_UInt8)1].ctrlRegs.respcycs;
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
        i2cCount++;
    }

    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rPreMasterInit I2C failure at operation: %ld", &i2cCount );
#else    
        A2B_DSCVRY_ERROR1( plugin->ctx, "PreMasterInit", 
                           "I2C failure at operation: %ld", &i2cCount );
#endif                           
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }

    if(bdd_DISCOVERY_MODE_ADVANCED == a2b_ovrGetDiscMode(plugin))
    {
		a2b_dscvryInitTdmSettings( plugin, A2B_NODEADDR_MASTER );
		status = a2b_audioConfig( plugin->ctx, &plugin->pluginTdmSettings );

		if ( A2B_FAILED(status) )
		{
#ifdef A2B_FEATURE_SEQ_CHART
			nNodeAddr = A2B_NODEADDR_MASTER;
#endif
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rAdvanced Discovery - Cannot config audio for nodeAddr ??");
#else
			A2B_DSCVRY_ERROR1( plugin->ctx, "dscvryPreMasterInit",
							   "Advanced Discovery - Cannot config audio for nodeAddr: %hd",
							   &nNodeAddr );
#endif							   
			a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_IO );
			A2B_DSCVRY_SEQEND_COND( plugin->ctx, bSeqGroupShown );
			return A2B_FALSE;
		}

		/* Do final setup of the master node and enable the up/downstream */
		if (a2b_dscvryNodeComplete( plugin, A2B_NODEADDR_MASTER,
								 A2B_TRUE, &errCode ) == A2B_EXEC_COMPLETE_FAIL)
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rdscvryPreMasterInit Advanced Discovery - Failed to complete master node init" );
#else		
			A2B_DSCVRY_ERROR0( plugin->ctx, "dscvryPreMasterInit",
							   "Advanced Discovery - Failed to complete master node init" );
#endif							   
		}
    }
    /* Now we wait for INTTYPE.DSCDONE */

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rdscvryPreMasterInit...Waiting for INTTYPE.DSCDONE..." );
#else
    A2B_DSCVRY_RAWDEBUG0( plugin->ctx, "dscvryPreMasterInit", 
                          "...Waiting for INTTYPE.DSCDONE..." );
#endif
    A2B_DSCVRY_SEQEND( plugin->ctx );

    return A2B_TRUE;

} /* a2b_dscvryPreMasterInit */

#ifdef A2B_FEATURE_COMM_CH
static a2b_Bool a2b_dscvryNodeMailboxInit (a2b_Plugin* plugin, a2b_Int16 nodeBddIdx)
{
    a2b_Int16 nodeAddr = nodeBddIdx-1;
    a2b_HResult status = A2B_RESULT_SUCCESS;

    if ((nodeBddIdx < 0) || (nodeBddIdx >= (a2b_Int16)plugin->bdd->nodes_count))
    {
        return A2B_FALSE;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rMailbox Registers" );
#else
    A2B_DSCVRY_SEQGROUP0( plugin->ctx,
                          "Mailbox Registers" );
#endif                          

    if (plugin->bdd->nodes[nodeBddIdx].has_mbox)
    {
        a2b_UInt8 wBuf[4];

        if (plugin->bdd->nodes[nodeBddIdx].mbox.has_mbox0ctl)
        {
            /* Program MBOX 0 register */
            wBuf[0] = A2B_REG_MBOX0CTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeBddIdx].mbox.mbox0ctl;
			status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );

            if ( A2B_FAILED(status) )
            {
                A2B_DSCVRY_SEQEND( plugin->ctx );
                return A2B_FALSE;
            }
        }

        if (plugin->bdd->nodes[nodeBddIdx].mbox.has_mbox1ctl)
        {
            /* Program MBOX 1 register */
            wBuf[0] = A2B_REG_MBOX1CTL;
            wBuf[1] = (a2b_UInt8)plugin->bdd->nodes[nodeBddIdx].mbox.mbox1ctl;
            status = a2b_regWrite( plugin->ctx, nodeAddr, 2u, wBuf );

            if ( A2B_FAILED(status) )
            {
                A2B_DSCVRY_SEQEND( plugin->ctx );
                return A2B_FALSE;
            }
        }
    }

    A2B_DSCVRY_SEQEND( plugin->ctx );

    return A2B_TRUE;

} /* a2b_dscvryNodeMailboxInit */
#endif	/* A2B_FEATURE_COMM_CH */

/*!****************************************************************************
*
*  \b               a2b_getNodeSignature
*
*  Returns the node signature information for the specified node address.
*
*  \param           [in]    plugin      The A2B master plugin instance.
*
*  \param           [in]    nodeAddr    The node address to retrieve its
*                                       signature. Slave node addresses are
*                                       in the range [0, N] while the master
*                                       node is A2B_NODEADDR_MASTER.
*
*  \pre             None
*
*  \post            None
*
*  \return          Returns a pointer to the constant node signature structure.
*                   The caller should **not** attempt to free this structure.
*
******************************************************************************/
static const a2b_NodeSignature*
a2b_getNodeSignature
    (
    a2b_Plugin* plugin,
    a2b_Int16   nodeAddr
    )
{
    const a2b_NodeSignature*    nodeSig;
    a2b_UInt32                  iter = 0u;

    /* Search for the node signature information for this slave node */
    do
    {
        nodeSig = a2b_msgRtrGetHandler(plugin->ctx, &iter);
        if ( (nodeSig != A2B_NULL) &&
            (nodeSig->nodeAddr == nodeAddr) )
        {
            break;
        }
    }
    while ( A2B_NULL != nodeSig );

    return nodeSig;
} /* a2b_getNodeSignature */


/*!****************************************************************************
*
*  \b              a2b_dscvryFindNodeHandler
*
*  If a search hasn't been done to find a handler (plugin) to manage this
*  node then try to find one. If this search has already been done then the
*  function returns immediately.
*
*  \param          [in]    plugin       The master plugin specific data.
*
*  \param          [in]    slaveNodeIdx Zero-based index into a slave node
*                                       array where index 0 is the first
*                                       slave, index 1 is second slave, etc...
*
*  \pre            None
*
*  \post           If a handler (e.g. plugin) has been found for this node
*                  then it is bound to this node.
*
*  \return         None
*
******************************************************************************/
static void
a2b_dscvryFindNodeHandler
    (
    a2b_Plugin* plugin,
    a2b_UInt16  slaveNodeIdx
    )
{
    a2b_HResult                 status;
    const a2b_NodeSignature*    nodeSig = &plugin->slaveNodeSig[slaveNodeIdx];

    /* For this use-case the slave node index is identical to the node
     * address.
     */
    a2b_Int16                   nodeAddr =
                                    A2B_MAP_SLAVE_INDEX_TO_ADDR(slaveNodeIdx);

    /* If we've already searched for a handler to manage this plugin
     * then ...
     */
    if ( A2B_HAS_SEARCHED_FOR_HANLDER(plugin, nodeAddr) )
    {
        /* No need to search again */
        return;
    }

    /* Look for a plugin to manage this node */
    status = a2b_stackFindHandler( plugin->ctx, nodeSig);

    /* Mark it as being searched - whether successful or not */
    plugin->discovery.hasSearchedForHandler |= ((a2b_UInt32)1 << (a2b_UInt32)nodeAddr);

    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s findNodeHandler(): No plugin for node: %hd",
                    A2B_MPLUGIN_PLUGIN_NAME, &nodeAddr );
#else    
        A2B_TRACE2( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_DEBUG),
                    "%s findNodeHandler(): No plugin for node: %hd",
                    A2B_MPLUGIN_PLUGIN_NAME, &nodeAddr ));
#endif
    }
    else
    {
        /* Track that a plugin exists and will manage this node */
        plugin->discovery.hasPlugin |= ((a2b_UInt32)1 << (a2b_UInt32)nodeAddr);
        plugin->discovery.needsPluginInit |= ((a2b_UInt32)1 << (a2b_UInt32)nodeAddr);

        /* Get the updated signature with the actual plugin name */
        nodeSig = a2b_getNodeSignature(plugin, nodeAddr);
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rPlugin '%s' opened to manage node: %hd",
                          nodeSig->pluginName, &nodeAddr);
#else		
        A2B_SEQ_GENNOTE2( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
                          "Plugin '%s' opened to manage node: %hd",
                          nodeSig->pluginName, &nodeAddr);
#endif                          
    }
}


/*!****************************************************************************
*
*  \b              a2b_dscvryNodeDiscovered
*
*  Called after a node has been discovered.  This can be used to setup
*  the new node depending on the discovery process being used.
*
*  \param          [in]    plugin   plugin specific data
*
*  \pre            Called on DSCDONE
*
*  \post           The following registers are altered:
*                  A2B_REG_SWCTL 
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
a2b_Bool
a2b_dscvryNodeDiscovered
    (
    a2b_Plugin* plugin
    )
{
    a2b_Bool 	bRet = A2B_TRUE, bNetConfigFlag = A2B_FALSE;
    a2b_UInt8 	wBuf[4u];
    a2b_UInt8 	rBuf[8u];
    a2b_Int16	 idx;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_Int16 	dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 	dscNodeIdx = dscNodeAddr+1;
    struct a2b_StackContext* ctx = plugin->ctx;
    bdd_DiscoveryMode 	eDiscMode;
	a2b_UInt8 			mstrBit = 0u;
	a2b_NodeSignature   nodeSig;
	const bdd_Node      *bddNodeObj;
	const bdd_Node      *bddMstrNodeObj;
#ifndef A2B_SLAVE_DISCOVERY_WO_ID_VER	
	a2b_Bool 			verifyNodeDescr;
#endif
	a2b_Bool 			bContinueDisc;
	a2b_Bool 			isXTalkFixApplicable;

    eDiscMode = a2b_ovrGetDiscMode(plugin);
    if (!plugin->discovery.inDiscovery)
    {
        /* Ignore DSCDONE when we are NOT discovering */
        return A2B_FALSE;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\rNodeDiscovered nodeAddr %hd", &dscNodeAddr);
#else
    A2B_DSCVRY_SEQGROUP1( ctx, "NodeDiscovered nodeAddr %hd", &dscNodeAddr);
#endif    

    /* Stop the previously running timer */
    a2b_timerStop( plugin->timer );

	/*Check whether upstream node is AD2425 or AD2410 series */
	bddNodeObj = &plugin->bdd->nodes[dscNodeIdx - 1];
	bddMstrNodeObj = &plugin->bdd->nodes[0];
	A2B_UNUSED(bddMstrNodeObj);

	 isXTalkFixApplicable = a2b_isCrossTalkFixApply(bddNodeObj->nodeDescr.vendor, bddNodeObj->nodeDescr.product);

	if ((plugin->bdd->policy.bCrossTalkFixApply) && (dscNodeIdx != 1) && (isXTalkFixApplicable == A2B_TRUE))
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rA2B CrossTalk Fix");
#else	
		A2B_DSCVRY_SEQGROUP0(ctx,
			"A2B CrossTalk Fix");
#endif

		if (((plugin->nodeSig.hasSiliconInfo) &&
			(a2b_isAd242xChip(plugin->nodeSig.siliconInfo.vendorId,
				              plugin->nodeSig.siliconInfo.productId)))  ||
			plugin->bdd->nodes[dscNodeIdx].nodeDescr.bIsAnalyzer)
		{
			 mstrBit = (a2b_UInt8)A2B_ENUM_CONTROL_MSTR;
		}

		wBuf[0] = A2B_REG_RESPCYCS;
		wBuf[1] = plugin->bdd->nodes[0].ctrlRegs.respcycs + 1u;
		status = a2b_i2cMasterWrite(ctx, 2, wBuf);

		for (idx = 1u; idx <= dscNodeIdx; idx++)
		{
			wBuf[0] = A2B_REG_RESPCYCS;
			wBuf[1] = plugin->bdd->nodes[idx].ctrlRegs.respcycs + 1u;
			status = a2b_i2cSlaveWrite(ctx, (idx - 1), 2u, wBuf);
		}

		wBuf[0] = A2B_REG_CONTROL;
		wBuf[1] = A2B_ENUM_CONTROL_START_NS;
		wBuf[1] |= mstrBit;
		wBuf[1] |= (a2b_UInt8)(plugin->bdd->nodes[0].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
		status = a2b_i2cMasterWrite(ctx, 2, wBuf);
		a2b_ActiveDelay(ctx, 1u);

		wBuf[0] = A2B_REG_RESPCYCS;
		wBuf[1] = plugin->bdd->nodes[0].ctrlRegs.respcycs;
		status = a2b_i2cMasterWrite(ctx, 2, wBuf);

		for (idx = 1u; idx <= dscNodeIdx; idx++)
		{
			wBuf[0] = A2B_REG_RESPCYCS;
			wBuf[1] = plugin->bdd->nodes[idx].ctrlRegs.respcycs;
			status = a2b_i2cSlaveWrite(ctx, (idx - 1), 2, wBuf);
		}

		wBuf[0] = A2B_REG_CONTROL;
		wBuf[1] = A2B_ENUM_CONTROL_START_NS;
		wBuf[1] |= mstrBit;
		wBuf[1] |= (a2b_UInt8)(plugin->bdd->nodes[0].ctrlRegs.control & (A2B_ENUM_CONTROL_XCVRBINV | A2B_ENUM_CONTROL_SWBYP));
		status = a2b_i2cMasterWrite(ctx, 2, wBuf);
		a2b_ActiveDelay(ctx,1u);
		A2B_DSCVRY_SEQEND(plugin->ctx);
	}
    /* Enable phantom power with external switch mode
     *
     * NOTE: v3 ADI documentation shows the Simple Discovery flow  
     *       sending this only to the Master, which the documentation
     *       verbiage says to send it to the slave.  We will send it to
     *       the slave node. 
     */
    wBuf[0] = A2B_REG_SWCTL;
    wBuf[1] = A2B_BITM_SWCTL_ENSW | A2B_ENUM_SWCTL_MODE_VOLT_ON_VIN;
    if ( A2B_NODEADDR_MASTER == dscNodeAddr - 1 )
    {
        status = a2b_i2cMasterWrite( ctx, 2u, wBuf );
    }
    else
    {
        /* Alters the previously discovered nodes SWCTL */
        status = a2b_i2cSlaveWrite( ctx, dscNodeAddr - 1, 2u, wBuf );
    }

#ifdef A2B_SS_STACK
	if (plugin->ctx->stk->ecb->palEcb.oAppEcbPal.PreCustomNodeConfig != A2B_NULL)
	{
		plugin->ctx->stk->ecb->palEcb.oAppEcbPal.PreCustomNodeConfig(dscNodeAddr - 1);
	}
#endif

    /* NOTE: A2B_REG_NODEADR managed by I2C, no need to set it */
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rA2B VID/PID/VERSION/CAP" );
#else
    A2B_DSCVRY_SEQGROUP0( ctx,
                          "A2B VID/PID/VERSION/CAP" );
#endif                          

    /* Read the new nodes VID/PID/VERSION/CAP */
    wBuf[0] = A2B_REG_VENDOR;
    status  = a2b_i2cSlaveWriteRead( ctx, dscNodeAddr, 1u, wBuf, 4u, rBuf );

    A2B_DSCVRY_SEQEND( plugin->ctx );

    bddNodeObj = &plugin->bdd->nodes[dscNodeIdx];
	bddMstrNodeObj = &plugin->bdd->nodes[0];

    if ( A2B_SUCCEEDED(status) )
    {
#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
        a2b_UInt16          capability = rBuf[3u];
#endif

        A2B_INIT_SIGNATURE( &nodeSig, dscNodeAddr );

        /* Silicon VID/PID/VER */
        nodeSig.hasSiliconInfo         = A2B_TRUE;
        nodeSig.siliconInfo.vendorId   = rBuf[0u];
        nodeSig.siliconInfo.productId  = rBuf[1u];
        nodeSig.siliconInfo.version    = rBuf[2u];

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s nodeDiscovered(): Silicon node/vid/pid/ver/cap: %02hx/%02hx/%02hx/%02hx",
                    A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                    nodeSig.siliconInfo.vendorId,
                    nodeSig.siliconInfo.productId,
                    nodeSig.siliconInfo.version);
		cprintf("\n\rSilicon vid/pid/ver/cap: %02hx/%02hx/%02hx", 
                          nodeSig.siliconInfo.vendorId,
                          nodeSig.siliconInfo.productId,
                          nodeSig.siliconInfo.version);
#else
        A2B_TRACE6( (ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
                    "%s nodeDiscovered(): Silicon node/vid/pid/ver/cap: "
                    "%02hX/%02bX/%02bX/%02bX/%02bX",
                    A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                    &nodeSig.siliconInfo.vendorId,
                    &nodeSig.siliconInfo.productId,
                    &nodeSig.siliconInfo.version,
                    &capability ));
        A2B_SEQ_GENNOTE4( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY,
                          "Silicon vid/pid/ver/cap: %02bX/%02bX/%02bX/%02bX", 
                          &nodeSig.siliconInfo.vendorId,
                          &nodeSig.siliconInfo.productId,
                          &nodeSig.siliconInfo.version,
                          &capability );
#endif

        /* Verify the stack supports this node */
        if ( (!a2b_stackSupportedNode(nodeSig.siliconInfo.vendorId,
                                       nodeSig.siliconInfo.productId, 
                                       nodeSig.siliconInfo.version )) &&
        	  !plugin->bdd->nodes[dscNodeIdx].nodeDescr.bIsAnalyzer)
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rnodeDiscovered Incompatible node %hd (%02x/%02x/%02x/%02x)", 
                               dscNodeAddr,
                               nodeSig.siliconInfo.vendorId, 
                               nodeSig.siliconInfo.productId, 
                               nodeSig.siliconInfo.version);
#else        
            A2B_DSCVRY_ERROR5( ctx, "nodeDiscovered",
                               "Incompatible node %hd (%02bX/%02bX/%02bX/%02bX)", 
                               &dscNodeAddr,
                               &nodeSig.siliconInfo.vendorId, 
                               &nodeSig.siliconInfo.productId, 
                               &nodeSig.siliconInfo.version,
                               &capability );
#endif

            bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);
            if((bdd_DISCOVERY_MODE_SIMPLE == eDiscMode) && (bNetConfigFlag))
            {
            	plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE;
            	a2b_dscvryNetComplete(plugin);
            }
            else
            {
				a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE );
            }

            A2B_DSCVRY_SEQEND( plugin->ctx );
            return A2B_FALSE;
        }

#ifndef A2B_SLAVE_DISCOVERY_WO_ID_VER
		/* Mandatory checking for AD2420 & AD2429 */
		verifyNodeDescr = (a2b_Bool)bddNodeObj->verifyNodeDescr;

        /* Optionally validate the node descriptor info */
        if ((verifyNodeDescr) &&
            (( bddNodeObj->nodeDescr.product !=
                                   nodeSig.siliconInfo.productId ) ||
             ( bddNodeObj->nodeDescr.version !=
                                   nodeSig.siliconInfo.version )) && (!bddNodeObj->nodeDescr.bIsAnalyzer))
        {

			/* Copy the signature information to the plugin */
			plugin->slaveNodeSig[dscNodeAddr] = nodeSig;
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rnodeDiscovered Failed Authentication ",
                              &dscNodeAddr );
#else			
            A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered",
                              "Failed Authentication ",
                              &dscNodeAddr );
#endif                              

            bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);
            if((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
            {
            	plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE;
            	a2b_dscvryNetComplete(plugin);
            }
            else
            {
				a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE );
            }
            A2B_DSCVRY_SEQEND( plugin->ctx );
            return A2B_FALSE;
        }
#endif
        nodeSig.hasI2cCapability = (a2b_Bool)((rBuf[3u] & A2B_BITM_CAPABILITY_I2CAVAIL) != 0u);

		/* Custom Node Identification - Start */
		if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bCustomNodeIdAuth == A2B_TRUE)
		{
			/* Authenticate by reading from memory */
			if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bReadFrmMemory == A2B_TRUE)
			{
				bRet = a2b_dscvryCustomAuthFrmMem(plugin, nodeSig);
				if (bRet == A2B_FALSE)
				{
					return (A2B_FALSE);
				}
			}

			/* Authenticate by GPIO pins */
			if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bReadGpioPins == A2B_TRUE)
			{
				bRet = a2b_dscvryCustomAuthFrmGpio(plugin, nodeSig);
				if (bRet == A2B_FALSE)
				{
					return (A2B_FALSE);
				}
			}

#ifdef A2B_FEATURE_COMM_CH
			/* Authenticate by getting the authentication message via communication channel */
			if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bReadFrmCommCh == A2B_TRUE)
			{
				bRet = a2b_dscvryCustomAuthFrmCommCh(plugin, nodeSig);
				if (bRet == A2B_FALSE)
				{
					return (A2B_FALSE);
				}
			}
#endif	/* A2B_FEATURE_COMM_CH */
		}
		/* Custom Node Identification - End */

#ifdef A2B_FEATURE_COMM_CH
		/* Authenticate by getting the authentication message via communication channel */
		if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bReadFrmCommCh == A2B_FALSE)
		{
#endif	/* A2B_FEATURE_COMM_CH */
			/* Used only during simple discovery with sync periph processing */
			plugin->discovery.simpleNodeCount++;
			plugin->discovery.dscNumNodes++;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
        if ((( nodeSig.hasI2cCapability ) && ( !bddNodeObj->ignEeprom ) &&
             ( ( plugin->overrides[0u] & A2B_MPLUGIN_IGN_EEPROM ) == 0u )) ||
            ( plugin->periphCfg.nodeCfg[dscNodeAddr] ))
        {
#if !defined(A2B_BCF_FROM_SOC_EEPROM) && !defined(A2B_BCF_FROM_FILE_IO)
            A2B_DSCVRY_SEQGROUP0( ctx,
                                  "Look for EEPROM at 0x50" );

            /* Read the EEPROM header             */
            /* [Two byte internal EEPROM address] */
            wBuf[0] = 0u;
            wBuf[1] = 0u;
            status = a2b_periphCfgWriteRead( plugin,
                                             dscNodeAddr,
                                             2u,  wBuf,
                                             8u,  rBuf);

            if (( A2B_SUCCEEDED(status) ) &&
                ( rBuf[0] == A2B_MARKER_EEPROM_CONFIG ))
            {
                a2b_UInt8 crc8 = a2b_crc8(rBuf, 0u, 7u);

                if ( crc8 == rBuf[7] )
                {
                    /* EEPROM VID/PID/VER */
                    nodeSig.hasEepromInfo        = A2B_TRUE;
                    nodeSig.eepromInfo.vendorId  = rBuf[1];
                    nodeSig.eepromInfo.productId = rBuf[2];
                    nodeSig.eepromInfo.version   = rBuf[3];

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cprintf("\n\r%s nodeDiscovered(): EEPROM node/vid/pid/ver: %02hX/%02bX/%02bX/%02bX",
                                A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                                &nodeSig.eepromInfo.vendorId,
                                &nodeSig.eepromInfo.productId,
                                &nodeSig.eepromInfo.version);
					cprintf("\n\rEEPROM vid/pid/ver: %02bX/%02bX/%02bX", 
                                      &nodeSig.eepromInfo.vendorId,
                                      &nodeSig.eepromInfo.productId,
                                      &nodeSig.eepromInfo.version );
#else
                    A2B_TRACE5( (ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
                                "%s nodeDiscovered(): EEPROM node/vid/pid/ver: "
                                "%02hX/%02bX/%02bX/%02bX",
                                A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                                &nodeSig.eepromInfo.vendorId,
                                &nodeSig.eepromInfo.productId,
                                &nodeSig.eepromInfo.version ));
                    A2B_SEQ_GENNOTE3( plugin->ctx, 
                                      A2B_SEQ_CHART_LEVEL_DISCOVERY,
                                      "EEPROM vid/pid/ver: %02bX/%02bX/%02bX", 
                                      &nodeSig.eepromInfo.vendorId,
                                      &nodeSig.eepromInfo.productId,
                                      &nodeSig.eepromInfo.version );
#endif

                    /* When this override is set we will parse the version
                     * (which we did) but we will not indicate that there 
                     * was an EEPRROM so we will avoid peripheral processing
                     */
                    if (( plugin->overrides[0] & A2B_MPLUGIN_EEPROM_VER_ONLY ) == 0u )
                    {
                        /* See if we have an override for this specific node */
                        if (( plugin->overrides[1] & (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr)) == (a2b_UInt32)0u )
                        {
                            plugin->discovery.hasEeprom |= (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr);
                        }
                        else
                        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
							cprintf("\n\rnodeDiscovered Override Set, Ignoring node %hd EEPROM",
                                       &dscNodeAddr );
#else                        
                            A2B_DSCVRYNOTE_DEBUG1( plugin->ctx, 
                                       "nodeDiscovered",
                                       "Override Set, Ignoring node %hd EEPROM",
                                       &dscNodeAddr );
#endif                                       
                        }
                    }

                    /* Optionally validate the node descriptor info */
                    if (( bddNodeObj->verifyNodeDescr ) &&
                        (( bddNodeObj->nodeDescr.vendor != 
                                               nodeSig.eepromInfo.vendorId ) ||
                         ( bddNodeObj->nodeDescr.product != 
                                               nodeSig.eepromInfo.productId ) ||
                         ( bddNodeObj->nodeDescr.version != 
                                               nodeSig.eepromInfo.version )) )
                    {
                        /* clear the bit */
                        plugin->discovery.hasEeprom ^= (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr);

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
						cprintf("\n\rnodeDiscovered Node %hd EEPROM failed verification",
                                          &dscNodeAddr );
#else
                        A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered", 
                                          "Node %hd EEPROM failed verification",
                                          &dscNodeAddr );
#endif                                          

                        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE );
                        A2B_DSCVRY_SEQEND( plugin->ctx );
                        return A2B_FALSE;
                    }
                }
                else
                {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cprintf("\n\rnodeDiscovered Node %hd EEPROM header CRC incorrect",
                                       &dscNodeAddr );
#else                
                    A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered", 
                                       "Node %hd EEPROM header CRC incorrect",
                                       &dscNodeAddr );
#endif                                       
                }
            }
            else
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rnodeDiscovered Node %hd EEPROM not found",
                                       &dscNodeAddr );
#else            
                A2B_DSCVRYNOTE_DEBUG1( ctx, "nodeDiscovered", 
                                       "Node %hd EEPROM not found",
                                       &dscNodeAddr );
#endif
            }

            A2B_DSCVRY_SEQEND( plugin->ctx );
#else
            plugin->discovery.hasEeprom |= (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr);
#endif
        }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

        /* BDD VID/PID/VER */
        nodeSig.hasBddInfo        = A2B_TRUE;
        nodeSig.bddInfo.vendorId  = (a2b_UInt8)bddNodeObj->nodeDescr.vendor;
        nodeSig.bddInfo.productId = (a2b_UInt8)bddNodeObj->nodeDescr.product;
        nodeSig.bddInfo.version   = (a2b_UInt8)bddNodeObj->nodeDescr.version;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s nodeDiscovered(): BDD node/vid/pid/ver: %02hX/%02bX/%02bX/%02bX",
                    A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                    &nodeSig.bddInfo.vendorId,
                    &nodeSig.bddInfo.productId,
                    &nodeSig.bddInfo.version );
		cprintf("\n\rBDD vid/pid/ver: %02bX/%02bX/%02bX", 
                          &nodeSig.bddInfo.vendorId,
                          &nodeSig.bddInfo.productId,
                          &nodeSig.bddInfo.version );
#else
        A2B_TRACE5( (ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
                    "%s nodeDiscovered(): BDD node/vid/pid/ver: "
                    "%02hX/%02bX/%02bX/%02bX",
                    A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
                    &nodeSig.bddInfo.vendorId,
                    &nodeSig.bddInfo.productId,
                    &nodeSig.bddInfo.version ));
        A2B_SEQ_GENNOTE3( plugin->ctx, 
                          A2B_SEQ_CHART_LEVEL_DISCOVERY,
                          "BDD vid/pid/ver: %02bX/%02bX/%02bX", 
                          &nodeSig.bddInfo.vendorId,
                          &nodeSig.bddInfo.productId,
                          &nodeSig.bddInfo.version );
#endif

        /* Copy the signature information to the plugin */
        plugin->slaveNodeSig[dscNodeAddr] = nodeSig;

#ifndef FIND_NODE_HANDLER_AFTER_NODE_INIT
        /* We'll attempt to find and open a plugin that can manage the
         * slave node *before* completing the full initialization of the
         * node.
         */
        a2b_dscvryFindNodeHandler(plugin, dscNodeAddr);
#endif
#ifdef A2B_FEATURE_COMM_CH
		}	/* If bReadFrmCommCh == A2B_FALSE */
#endif	/* A2B_FEATURE_COMM_CH */

    }	/* Successful reading of VID, PID */
    else
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rnodeDiscovered Cannot read VID/PID/VER/CAP for node: %hd",
                           &dscNodeAddr );
#else    
        A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered",
                           "Cannot read VID/PID/VER/CAP for node: %hd",
                           &dscNodeAddr );
#endif                           
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_PERMISSION );
        A2B_DSCVRY_SEQEND( plugin->ctx );
        return A2B_FALSE;
    }
    A2B_DSCVRY_SEQEND( plugin->ctx );

#ifdef A2B_FEATURE_COMM_CH
	if(bddNodeObj->nodeDescr.oCustomNodeIdSettings.bReadFrmCommCh == A2B_FALSE)
	{
#endif	/* A2B_FEATURE_COMM_CH */
		if ( bdd_DISCOVERY_MODE_MODIFIED == eDiscMode )
		{
			bRet = adi_a2b_ConfigureNodePeri(plugin, dscNodeAddr);

		} /* end Modified processing */
		else if((bdd_DISCOVERY_MODE_OPTIMIZED == eDiscMode) ||
				(bdd_DISCOVERY_MODE_ADVANCED == eDiscMode))
		{
			if(plugin->discovery.pendingPluginInit == (a2b_UInt8)0)
			{
				bRet = adi_a2b_ConfigNodeOptimizAdvancedMode(plugin, dscNodeAddr);
			}
		}
		else
		{
			/* send notification to application */
			bContinueDisc = sendNodeDscvryNotification( plugin, plugin->discovery.discoveryCompleteCode, dscNodeIdx);
			if(bContinueDisc == A2B_TRUE)
			{
				bRet = a2b_dscvryPreSlaveInit( plugin );
			}
			else
			{
				a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_CANCELLED );
			}
		}
#ifdef A2B_FEATURE_COMM_CH
	}
#endif	/* A2B_FEATURE_COMM_CH */

    /* Now we wait for INTTYPE.DSCDONE on success */
    
    return bRet;

} /* a2b_dscvryNodeDiscovered */


/*!****************************************************************************
*
*  \b              a2b_dscvryCustomAuthFrmMem
*
*  Called after a node has been discovered.  This can be used to perform
*  custom node authentication by reading from memory.
*
*  \param          [in]    plugin   plugin specific data
*
*  \param          [in]    nodeSig  node signature data
*
*  \pre            Called on DSCDONE
*
*  \post           None
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool a2b_dscvryCustomAuthFrmMem(a2b_Plugin* plugin, a2b_NodeSignature nodeSig)
{
    a2b_Bool 	bNetConfigFlag = A2B_FALSE, nFlgSupIdMatch;
    a2b_UInt8 	wBuf[4u];
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_UInt16 	nWrite, nRead;
	a2b_UInt8 	nIdx, rBufCustomNodeId[50u];
    a2b_Int16 	dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 	dscNodeIdx = dscNodeAddr+1;
	a2b_Bool 	bContinueDisc;
	const bdd_Node					*bddNodeObj;
	a2b_CustomAuth					*pSlvNodeCustomAuth;
	const bdd_CustomNodeIdSettings 	*pCustomNodeIdSettings;
	A2B_UNUSED(nodeSig.nodeAddr);

	bddNodeObj 				= &plugin->bdd->nodes[dscNodeIdx];
	pSlvNodeCustomAuth 		= &plugin->customAuth[dscNodeAddr]; /* Using dscNodeAddr as it only has slave node count */
	pCustomNodeIdSettings 	= &bddNodeObj->nodeDescr.oCustomNodeIdSettings;

	switch(pCustomNodeIdSettings->nReadMemAddrWidth)
	{
	case 1U:
		wBuf[0U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr);
		break;
	case 2U:
		wBuf[0U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 8U);
		wBuf[1U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr  & 0xFFU);
		break;
	case 3U:
		wBuf[0U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 16U);
		wBuf[1U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 8U);
		wBuf[2U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr  & 0xFFU);
		break;
	case 4U:
		wBuf[0U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 24U);
		wBuf[1U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 16U);
		wBuf[2U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 8U);
		wBuf[3U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr  & 0xFFU);
		break;
	default:
		wBuf[0U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr >> 8u);
		wBuf[1U]  =  (a2b_UInt8)(pCustomNodeIdSettings->nReadMemAddr & 0xFFu);
		break;
	}

	nWrite = (a2b_UInt16)pCustomNodeIdSettings->nReadMemAddrWidth;
	nRead  = (a2b_UInt16)pCustomNodeIdSettings->nNodeIdLength;

	do
	{
		/* Read from peripheral memory */
		status = a2b_i2cPeriphWriteRead(plugin->ctx, dscNodeAddr, (a2b_UInt16)pCustomNodeIdSettings->nDeviceAddr, nWrite, wBuf, nRead, rBufCustomNodeId);

		if (A2B_SUCCEEDED(status))
		{
			for (nIdx = 0u; nIdx < nRead; nIdx++)
			{
				if (rBufCustomNodeId[nIdx] != (a2b_UInt8)(pCustomNodeIdSettings->nNodeId[nIdx]))
				{
					nFlgSupIdMatch = A2B_FALSE;
					break;
				}	
				else
				{
					nFlgSupIdMatch = A2B_TRUE;
				}
			}
		}
		else
		{
			/* If read from memory is failed set the nFlgSupIdMatch as false */
			nFlgSupIdMatch = A2B_FALSE;
		}

		/* Decrement the retry count */
		pSlvNodeCustomAuth->nRetryCnt--;

		if(nFlgSupIdMatch == A2B_FALSE)
		{
			/* Wait for 1 msec */
			a2b_ActiveDelay(plugin->ctx, 1u);
		}

	} while ((nFlgSupIdMatch == A2B_FALSE) && (pSlvNodeCustomAuth->nRetryCnt > 0));

	if (nFlgSupIdMatch == A2B_FALSE)
	{
		/* Set the discovery complete code */
		plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;

		/* send notification to application */
		bContinueDisc = sendNodeDscvryNotification( plugin, plugin->discovery.discoveryCompleteCode, dscNodeIdx);
		if(bContinueDisc == A2B_TRUE)
		{
			/* Reset the custom node id flag */
			nFlgSupIdMatch = A2B_TRUE;

			/* Reset the discovery complete code */
			plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_OK;
		}
	}

	if (nFlgSupIdMatch == A2B_FALSE)
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\ra2b_dscvryCustomAuthFrmMem Node %hd: Custom Node Id Authentication Failed via read from memory", &dscNodeAddr);
#else	
		A2B_DSCVRY_ERROR1(plugin->ctx, "a2b_dscvryCustomAuthFrmMem", "Node %hd: Custom Node Id Authentication Failed via read from memory", &dscNodeAddr);
#endif		

		bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);
		if ((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
		{
			plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;
			a2b_dscvryNetComplete(plugin);
		}
		else
		{
			a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH);
		}
		A2B_DSCVRY_SEQEND(plugin->ctx);
	}

	return (nFlgSupIdMatch);
}

/*!****************************************************************************
*
*  \b              a2b_dscvryCustomAuthFrmGpio
*
*  Called after a node has been discovered.  This can be used to perform
*  custom node authentication by reading from GPIO.
*
*  \param          [in]    plugin   plugin specific data
*
*  \param          [in]    nodeSig  node signature data
*
*  \pre            Called on DSCDONE
*
*  \post           None
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool a2b_dscvryCustomAuthFrmGpio(a2b_Plugin* plugin, a2b_NodeSignature nodeSig)
{
	a2b_Bool 	bNetConfigFlag = A2B_FALSE, nFlgGpioMatch;
	a2b_UInt8 	wBuf[4u];
	a2b_HResult status = A2B_RESULT_SUCCESS;
	a2b_UInt8 	nIdx, rBufGpio[8u], nGpioVal;
    a2b_Int16 	dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 	dscNodeIdx = dscNodeAddr+1;
    a2b_Bool 	bContinueDisc;
	const bdd_Node					*bddNodeObj;
	a2b_CustomAuth					*pSlvNodeCustomAuth;
	const bdd_CustomNodeIdSettings 	*pCustomNodeIdSettings;
	A2B_UNUSED(nodeSig.nodeAddr);

	bddNodeObj 				= &plugin->bdd->nodes[dscNodeIdx];
	pSlvNodeCustomAuth 		= &plugin->customAuth[dscNodeAddr]; /* Using dscNodeAddr as it only has slave node count */
	pCustomNodeIdSettings 	= &bddNodeObj->nodeDescr.oCustomNodeIdSettings;

    /* GPIO Input Enable*/
    wBuf[0] = A2B_REG_GPIOIEN;
    wBuf[1] = ~(a2b_UInt8)(A2B_REG_GPIOIEN_RESET);
    status = a2b_regWrite(plugin->ctx, dscNodeAddr, 2u, wBuf);
	wBuf[0u]  =  A2B_REG_GPIOIN;

	do
	{
		/* Read from GPIO */
		status = a2b_i2cSlaveWriteRead(plugin->ctx, dscNodeAddr, 1u, wBuf, 8u, rBufGpio);

		if (A2B_SUCCEEDED(status))
		{
			for (nIdx = 0u; nIdx < 8u; nIdx++)
			{
				if (pCustomNodeIdSettings->aGpio[nIdx] != A2B_IGNORE)
				{
                    nGpioVal = ((rBufGpio[0] & (1u << nIdx)) >> nIdx);
					if (nGpioVal != pCustomNodeIdSettings->aGpio[nIdx])
					{
						nFlgGpioMatch = A2B_FALSE;
						break;
					}
					else
					{
						nFlgGpioMatch = A2B_TRUE;
					}
				}
				else
				{
					nFlgGpioMatch = A2B_TRUE;
				}
			}
		}
		else
		{
			/* If read from memory is failed set the nFlgGpioMatch as false */
			nFlgGpioMatch = A2B_FALSE;
		}

		/* Decrement the retry count */
		pSlvNodeCustomAuth->nRetryCnt--;

		if(nFlgGpioMatch == A2B_FALSE)
		{
			/* Wait for 1 msec */
			a2b_ActiveDelay(plugin->ctx, 1u);
		}

	} while ((nFlgGpioMatch == A2B_FALSE) && (pSlvNodeCustomAuth->nRetryCnt > 0));

	if (nFlgGpioMatch == A2B_FALSE)
	{
		/* Set the discovery complete code */
		plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;

		/* send notification to application */
		bContinueDisc = sendNodeDscvryNotification( plugin, plugin->discovery.discoveryCompleteCode, dscNodeIdx);
		if(bContinueDisc == A2B_TRUE)
		{
			/* Reset the custom node id flag */
			nFlgGpioMatch = A2B_TRUE;

			/* Reset the discovery complete code */
			plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_OK;
		}
	}

	if (nFlgGpioMatch == A2B_FALSE)
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\ra2b_dscvryCustomAuthFrmGpio Node %hd Custom Node Id Authentication via GPIO ", &dscNodeAddr);
#else	
		A2B_DSCVRY_ERROR1(plugin->ctx, "a2b_dscvryCustomAuthFrmGpio", "Node %hd Custom Node Id Authentication via GPIO ", &dscNodeAddr);
#endif		

		bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);
		if ((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
		{
			plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;
			a2b_dscvryNetComplete(plugin);
		}
		else
		{
			a2b_dscvryEnd(plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH);
		}
		A2B_DSCVRY_SEQEND(plugin->ctx);
	}

	return(nFlgGpioMatch);
}

/*!****************************************************************************
*
*  \b              sendNodeDscvryNotification
*
*  Trigger's a node level discovery notification if an application is registered
*
*  \param          [in]    plugin   	plugin specific data
*
*  \param          [in]    discCode  	Discovery success/failure indication
*
*  \param          [in]    dscNodeIdx	The A2B node address of the node that was just discovered.
*
*  \pre            Called on DSCDONE
*
*  \post           None
*
*  \return         FALSE = end discovery
*                  TRUE = continue discovery
*
******************************************************************************/
static a2b_Bool sendNodeDscvryNotification(a2b_Plugin *plugin, a2b_UInt32 discCode, a2b_Int16 dscNodeIdx)
{
	a2b_HResult result = A2B_RESULT_SUCCESS;
	struct a2b_Msg* notification;
	struct a2b_Nodedscvry* dscvrdNode;
	a2b_Bool bContinueDisc;

	/* Initializing the bContinueDisc with true if the discovery complete code is zero so as to continue with discovery */
	/* Initializing the bContinueDisc with false if the discovery complete code is non zero so as to end the discovery */
	bContinueDisc = (discCode == A2B_EC_OK) ? A2B_TRUE : A2B_FALSE ;

	/* Allocate a notification message */
	notification = a2b_msgAlloc(plugin->ctx, A2B_MSG_NOTIFY, A2B_MSGNOTIFY_NODE_DISCOVERY);

	if ( A2B_NULL == notification )
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rsendNodeDscvryNotification: failed to allocate notification");
#else	
		A2B_TRACE0((plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR), "sendNodeDscvryNotification: " "failed to allocate notification"));
#endif
	}
	else
	{

			dscvrdNode = (a2b_Nodedscvry*)a2b_msgGetPayload(notification);
			dscvrdNode->bddNetObj 				= (const void*)(plugin->bdd);
			dscvrdNode->nodeAddr 				= dscNodeIdx;
			dscvrdNode->discoveryCompleteCode 	= discCode;
			dscvrdNode->bContinueDisc 			= (discCode == A2B_EC_OK) ? A2B_TRUE : A2B_FALSE ;

			/* Make best effort delivery of notification */
			result = a2b_msgRtrNotify(notification);
			if ( A2B_FAILED(result) )
			{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rsendNodeDscvryNotification: failed to emit node discovery status notification: 0x%lX", &result);
#else		
				A2B_TRACE1((plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR), "sendNodeDscvryNotification: " "failed to emit node discovery status notification: 0x%lX", &result));
#endif
			}

			/* We no longer need this message */
			(void)a2b_msgUnref(notification);

			/* Get back the user input */
			bContinueDisc = dscvrdNode->bContinueDisc;
	}

	return (bContinueDisc);
}

#ifdef A2B_FEATURE_COMM_CH
/*!****************************************************************************
*
*  \b              adi_a2b_MstrPluginCommChStatusCb
*
*  Master plugin communication channel status callback function
*
*  \param          [in]    pPlugin         Pointer to master plugin specific data
*  \param          [in]    pMsg            Pointer to message
*  \param		   [in]	   eEventType      Enumeration of the event type
*  \param		   [in]	   nNodeAddr       Node address from which the msg is received
*
*  \pre            None
*
*  \post           None
*
*  \return          Returns a Boolean flag of whether the node was configured
*  					successfully.
******************************************************************************/
a2b_Bool adi_a2b_MstrPluginCommChStatusCb(void* pPlugin, a2b_CommChMsg *pMsg, A2B_COMMCH_EVENT eEventType, a2b_Int8 nNodeAddr)
{
	a2b_UInt32			nIdx;
	a2b_NodeSignature   nodeSig;
	a2b_Bool 			bRet = A2B_FALSE, nFlgSupIdMatch = A2B_TRUE, bNetConfigFlag = A2B_FALSE;
	a2b_Plugin* 		plugin 		= (a2b_Plugin*)pPlugin;
    a2b_Int16 			dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 			dscNodeIdx 	= dscNodeAddr+1;
    const bdd_Node		*bddNodeObj = &plugin->bdd->nodes[dscNodeIdx];
    a2b_Bool 			bContinueDisc;
    a2b_CustomAuth		*pSlvNodeCustomAuth;
    A2B_UNUSED(nNodeAddr);

    A2B_INIT_SIGNATURE( &nodeSig, dscNodeAddr );

	switch(eEventType)
	{
	case A2B_COMMCH_EVENT_RX_MSG:
		if(pMsg->nMsgId == A2B_COMMCH_MSG_RSP_SLV_NODE_SIGNATURE)
		{
			/* Stop authentication timeout timer */
			a2b_timerStop( plugin->timer );

			if (pMsg->nMsgLenInBytes == bddNodeObj->nodeDescr.oCustomNodeIdSettings.nNodeIdLength)
			{
				for (nIdx = 0u; nIdx < pMsg->nMsgLenInBytes; nIdx++)
				{
					if (pMsg->pMsgPayload[nIdx] != bddNodeObj->nodeDescr.oCustomNodeIdSettings.nNodeId[nIdx])
					{
						nFlgSupIdMatch = A2B_FALSE;
						break;
					}
				}
			}
			else
			{
				nFlgSupIdMatch = A2B_FALSE;
			}

			if (nFlgSupIdMatch == A2B_FALSE)
			{
				/* Set the discovery complete code */
				plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;

				/* send notification to application */
				bContinueDisc = sendNodeDscvryNotification( plugin, plugin->discovery.discoveryCompleteCode, dscNodeIdx);
				if(bContinueDisc == A2B_TRUE)
				{
					/* Reset the custom node id flag */
					nFlgSupIdMatch = A2B_TRUE;

					/* Reset the discovery complete code */
					plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_OK;
				}
			}

			if(nFlgSupIdMatch == A2B_FALSE)	/* End discovery */
			{
				/* Copy the signature information to the plugin */
				plugin->slaveNodeSig[dscNodeAddr] = nodeSig;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rnodeDiscovered Node %hd: Custom Node Id Authentication Failed while reading via communication channel", &dscNodeAddr );
#else
	            A2B_DSCVRY_ERROR1( plugin->ctx, "nodeDiscovered", "Node %hd: Custom Node Id Authentication Failed while reading via communication channel", &dscNodeAddr );
#endif	            

	            bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);

	            if((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
	            {
	            	plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH;
	            	a2b_dscvryNetComplete(plugin);
	            }
	            else
	            {
					a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH );
	            }

	            A2B_DSCVRY_SEQEND( plugin->ctx );
	            return (A2B_FALSE);
			}
			else
			{
				/* send notification to application */
				bContinueDisc = sendNodeDscvryNotification( plugin, plugin->discovery.discoveryCompleteCode, dscNodeIdx);
				if(bContinueDisc == A2B_TRUE)
				{
					bRet = a2b_dscvryPostAuthViaCommCh(plugin);
				}
				else
				{
					a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_AUTH );
				}
			}
		}
		break;
	case A2B_COMMCH_EVENT_TX_DONE:

		/* If request message is successfully transmitted start the timeout timer
		 * as per timeout specified in bdd
		 * */
		if(pMsg->nMsgId == A2B_COMMCH_MSG_REQ_SLV_NODE_SIGNATURE)
		{
			bRet = a2b_dscvryStartCommChAuthTimer(plugin, bddNodeObj->nodeDescr.oCustomNodeIdSettings.nTimeOut);
		}
		break;
	case A2B_COMMCH_EVENT_TX_TIMEOUT:
		/* If request message transmission has timed out
		 * then end discovery
		 * */
		pSlvNodeCustomAuth = &plugin->customAuth[dscNodeAddr]; /* Using dscNodeAddr as it only has slave node count */

		if(pMsg->nMsgId == A2B_COMMCH_MSG_REQ_SLV_NODE_SIGNATURE)
		{
			if(pSlvNodeCustomAuth->nRetryCnt > 0)
			{
				/* Decrement the retry count */
				pSlvNodeCustomAuth->nRetryCnt--;

				/* Re-issue the custom node auth message via mailbox  */
				bRet = a2b_dscvryCustomAuthFrmCommCh(plugin, plugin->slaveNodeSig[dscNodeAddr]);
			}
			else
			{
				/* Copy the signature information to the plugin */
				plugin->slaveNodeSig[dscNodeAddr] = nodeSig;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rnodeDiscovered Node %hd: Custom Node Id Authentication Failed : Transmission via communication channel timed out ", &dscNodeAddr );
#else
				A2B_DSCVRY_ERROR1( plugin->ctx, "nodeDiscovered", "Node %hd: Custom Node Id Authentication Failed : Transmission via communication channel timed out ", &dscNodeAddr );
#endif				

				bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);

				if((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
				{
					plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_TIMEOUT;
					a2b_dscvryNetComplete(plugin);
				}
				else
				{
					a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_TIMEOUT );
				}

				A2B_DSCVRY_SEQEND( plugin->ctx );
				return (A2B_FALSE);
			}
		}
		break;
	default :
		bRet = A2B_FALSE;
		break;
	}

	return bRet;
}

/*!****************************************************************************
*
*  \b              a2b_dscvryPostAuthViaCommCh
*
*  Function used to continue the discovery flow after the current discovered node
*  has been authorized via communication channel.This requires a separate flow
*  since authorization by communication channel requires a non-blocking communi-
*  cation between master and slave node spanning multiple ticks.
*
*  \param          [in]    plugin         Pointer to master plugin
*  \pre            None
*
*  \post           None
*
*  \return          Returns a Boolean flag of whether the node was configured
*  					successfully.
******************************************************************************/
static a2b_Bool a2b_dscvryPostAuthViaCommCh(a2b_Plugin* plugin)
{
    a2b_Bool 	bRet = A2B_TRUE;
    a2b_Int16 	dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 	dscNodeIdx = dscNodeAddr+1;
    bdd_DiscoveryMode 	eDiscMode;
    a2b_NodeSignature   nodeSig;
    const bdd_Node      *bddNodeObj = &plugin->bdd->nodes[dscNodeIdx];
#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    struct a2b_StackContext* ctx = plugin->ctx;
    a2b_UInt8 	wBuf[4u];
    a2b_UInt8 	rBuf[8u];
    a2b_HResult status = A2B_RESULT_SUCCESS;
#endif

    eDiscMode = a2b_ovrGetDiscMode(plugin);
	/* Used only during simple discovery with sync periph processing */
	plugin->discovery.simpleNodeCount++;
	plugin->discovery.dscNumNodes++;

    /* Copy the signature information from the plugin */
    nodeSig = plugin->slaveNodeSig[dscNodeAddr];

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
	if ((( nodeSig.hasI2cCapability ) && ( !bddNodeObj->ignEeprom ) &&
		 ( ( plugin->overrides[0u] & A2B_MPLUGIN_IGN_EEPROM ) == 0u )) ||
		( plugin->periphCfg.nodeCfg[dscNodeAddr] ))
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rLook for EEPROM at 0x50" );
#else	
		A2B_DSCVRY_SEQGROUP0( ctx,
							  "Look for EEPROM at 0x50" );
#endif							  

		/* Read the EEPROM header             */
		/* [Two byte internal EEPROM address] */
		wBuf[0] = 0u;
		wBuf[1] = 0u;
		status = a2b_periphCfgWriteRead( plugin,
										 dscNodeAddr,
										 2u,  wBuf,
										 8u,  rBuf);

		if (( A2B_SUCCEEDED(status) ) &&
			( rBuf[0] == A2B_MARKER_EEPROM_CONFIG ))
		{
			a2b_UInt8 crc8 = a2b_crc8(rBuf, 0u, 7u);

			if ( crc8 == rBuf[7] )
			{
				/* EEPROM VID/PID/VER */
				nodeSig.hasEepromInfo        = A2B_TRUE;
				nodeSig.eepromInfo.vendorId  = rBuf[1];
				nodeSig.eepromInfo.productId = rBuf[2];
				nodeSig.eepromInfo.version   = rBuf[3];

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\r%s nodeDiscovered(): EEPROM node/vid/pid/ver: %02hX/%02bX/%02bX/%02bX",
							A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
							&nodeSig.eepromInfo.vendorId,
							&nodeSig.eepromInfo.productId,
							&nodeSig.eepromInfo.version );
				cprintf("\n\rEEPROM vid/pid/ver: %02bX/%02bX/%02bX",
								  &nodeSig.eepromInfo.vendorId,
								  &nodeSig.eepromInfo.productId,
								  &nodeSig.eepromInfo.version );
#else
				A2B_TRACE5( (ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
							"%s nodeDiscovered(): EEPROM node/vid/pid/ver: "
							"%02hX/%02bX/%02bX/%02bX",
							A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
							&nodeSig.eepromInfo.vendorId,
							&nodeSig.eepromInfo.productId,
							&nodeSig.eepromInfo.version ));
				A2B_SEQ_GENNOTE3( plugin->ctx,
								  A2B_SEQ_CHART_LEVEL_DISCOVERY,
								  "EEPROM vid/pid/ver: %02bX/%02bX/%02bX",
								  &nodeSig.eepromInfo.vendorId,
								  &nodeSig.eepromInfo.productId,
								  &nodeSig.eepromInfo.version );
#endif

				/* When this override is set we will parse the version
				 * (which we did) but we will not indicate that there
				 * was an EEPRROM so we will avoid peripheral processing
				 */
				if (( plugin->overrides[0] & A2B_MPLUGIN_EEPROM_VER_ONLY ) == 0u )
				{
					/* See if we have an override for this specific node */
					if (( plugin->overrides[1] & (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr)) == (a2b_UInt32)0u )
					{
						plugin->discovery.hasEeprom |= (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr);
					}
					else
					{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
						cprintf("\n\rnodeDiscovered Override Set, Ignoring node %hd EEPROM",
								   &dscNodeAddr );
#else					
						A2B_DSCVRYNOTE_DEBUG1( plugin->ctx,
								   "nodeDiscovered",
								   "Override Set, Ignoring node %hd EEPROM",
								   &dscNodeAddr );
#endif								   
					}
				}

				/* Optionally validate the node descriptor info */
				if (( bddNodeObj->verifyNodeDescr ) &&
					(( bddNodeObj->nodeDescr.vendor !=
										   nodeSig.eepromInfo.vendorId ) ||
					 ( bddNodeObj->nodeDescr.product !=
										   nodeSig.eepromInfo.productId ) ||
					 ( bddNodeObj->nodeDescr.version !=
										   nodeSig.eepromInfo.version )) )
				{
					/* clear the bit */
					plugin->discovery.hasEeprom ^= (a2b_UInt32)((a2b_UInt32)1u << dscNodeAddr);

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
					cprintf("\n\rnodeDiscovered Node %hd EEPROM failed verification",
									  &dscNodeAddr );
#else
					A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered",
									  "Node %hd EEPROM failed verification",
									  &dscNodeAddr );
#endif									  

					a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_TRANSCEIVER_AUTH_FAILURE );
					A2B_DSCVRY_SEQEND( plugin->ctx );
					return A2B_FALSE;
				}
			}
			else
			{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rnodeDiscovered Node %hd EEPROM header CRC incorrect",
								   &dscNodeAddr );
#else			
				A2B_DSCVRY_ERROR1( ctx, "nodeDiscovered",
								   "Node %hd EEPROM header CRC incorrect",
								   &dscNodeAddr );
#endif								   
			}
		}
		else
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rnodeDiscovered Node %hd EEPROM not found",
								   &dscNodeAddr );
#else		
			A2B_DSCVRYNOTE_DEBUG1( ctx, "nodeDiscovered",
								   "Node %hd EEPROM not found",
								   &dscNodeAddr );
#endif								   
		}
		A2B_DSCVRY_SEQEND( plugin->ctx );
	}
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

	/* BDD VID/PID/VER */
	nodeSig.hasBddInfo        = A2B_TRUE;
	nodeSig.bddInfo.vendorId  = (a2b_UInt8)bddNodeObj->nodeDescr.vendor;
	nodeSig.bddInfo.productId = (a2b_UInt8)bddNodeObj->nodeDescr.product;
	nodeSig.bddInfo.version   = (a2b_UInt8)bddNodeObj->nodeDescr.version;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\r%s nodeDiscovered(): BDD node/vid/pid/ver: %02hX/%02bX/%02bX/%02bX",
				A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
				&nodeSig.bddInfo.vendorId,
				&nodeSig.bddInfo.productId,
				&nodeSig.bddInfo.version);
	cprintf("\n\rBDD vid/pid/ver: %02bX/%02bX/%02bX",
					  &nodeSig.bddInfo.vendorId,
					  &nodeSig.bddInfo.productId,
					  &nodeSig.bddInfo.version );
#else
	A2B_TRACE5( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_INFO),
				"%s nodeDiscovered(): BDD node/vid/pid/ver: "
				"%02hX/%02bX/%02bX/%02bX",
				A2B_MPLUGIN_PLUGIN_NAME, &dscNodeAddr,
				&nodeSig.bddInfo.vendorId,
				&nodeSig.bddInfo.productId,
				&nodeSig.bddInfo.version ));
	A2B_SEQ_GENNOTE3( plugin->ctx,
					  A2B_SEQ_CHART_LEVEL_DISCOVERY,
					  "BDD vid/pid/ver: %02bX/%02bX/%02bX",
					  &nodeSig.bddInfo.vendorId,
					  &nodeSig.bddInfo.productId,
					  &nodeSig.bddInfo.version );
#endif

	/* Copy the signature information to the plugin */
	plugin->slaveNodeSig[dscNodeAddr].bddInfo = nodeSig.bddInfo;

#ifndef FIND_NODE_HANDLER_AFTER_NODE_INIT
	/* We'll attempt to find and open a plugin that can manage the
	 * slave node *before* completing the full initialization of the
	 * node.
	 */
	a2b_dscvryFindNodeHandler(plugin, dscNodeAddr);
#endif

	if ( bdd_DISCOVERY_MODE_MODIFIED == eDiscMode )
	{
		(void)adi_a2b_ConfigureNodePeri(plugin, dscNodeAddr);

	} /* end Modified processing */
	else if((bdd_DISCOVERY_MODE_OPTIMIZED == eDiscMode) ||
			(bdd_DISCOVERY_MODE_ADVANCED == eDiscMode))
	{
		if(plugin->discovery.pendingPluginInit == (a2b_UInt8)0)
		{
			bRet = adi_a2b_ConfigNodeOptimizAdvancedMode(plugin, dscNodeAddr);
		}
	}
	else
	{
		bRet = a2b_dscvryPreSlaveInit( plugin );
	}

	return bRet;
}

/*!****************************************************************************
*
*  \b              a2b_dscvryStartCommChAuthTimer
*
*  Generate/Start the authorization timer for timeout on reception of slave node
*  id response upon initiation of a request from master plugin.
*  NOTE: This timer instance is shared for discovery timeout as well
*  since authorization happens after a node is discovered and since timer started
*  for discovery timeout is stopped at this moment, this sharing is possible
*  \param          [in]    plugin
*  \param          [in]    delay
*
*  \pre            None
*
*  \post           None
*
*  \return         [add here]
*
******************************************************************************/
static a2b_Bool
a2b_dscvryStartCommChAuthTimer
    (
    a2b_Plugin*     plugin,
	a2b_UInt16 delay
    )
{
    a2b_TimerFunc timerFunc = &a2b_onCommChAuthTimeout;

    /* Stop the previously running timer */
    a2b_timerStop( plugin->timer );

    /* Single shot timer */
    a2b_timerSet( plugin->timer, (a2b_UInt32)delay, 0u );
    a2b_timerSetHandler(plugin->timer, timerFunc);
    a2b_timerSetData(plugin->timer, plugin);
    a2b_timerStart( plugin->timer );

    return A2B_TRUE;

} /* a2b_dscvryStartCommChAuthTimer */

/*!****************************************************************************
*
*  \b              a2b_onCommChAuthTimeout
*
*  Handle the communication channel authorization timeout.
*
*  \param          [in]    timer
*  \param          [in]    userData
*
*  \pre            None
*
*  \post           None
*
*  \return         None
*
******************************************************************************/
static void
a2b_onCommChAuthTimeout
    (
    struct a2b_Timer *timer,
    a2b_Handle userData
    )
{
    a2b_Plugin* plugin = (a2b_Plugin*)userData;
    a2b_NodeSignature   nodeSig;
	a2b_Int16 			dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
	a2b_Bool bNetConfigFlag = A2B_FALSE;

	A2B_UNUSED(timer);
	A2B_INIT_SIGNATURE( &nodeSig, dscNodeAddr );

	/* Copy the signature information to the plugin */
	plugin->slaveNodeSig[dscNodeAddr] = nodeSig;

	/* End the discovery */
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\rnodeDiscovered Node %hd: Custom Node Id Authentication Failed : Timed out on response from slave via communication channel ", &dscNodeAddr );
#else	
	A2B_DSCVRY_ERROR1( plugin->ctx, "nodeDiscovered", "Node %hd: Custom Node Id Authentication Failed : Timed out on response from slave via communication channel ", &dscNodeAddr );
#endif

	bNetConfigFlag = a2b_SimpleModeChkNodeConfig(plugin);

	if((bdd_DISCOVERY_MODE_SIMPLE == a2b_ovrGetDiscMode(plugin)) && (bNetConfigFlag))
	{
		plugin->discovery.discoveryCompleteCode = (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_TIMEOUT;
		a2b_dscvryNetComplete(plugin);
	}
	else
	{
		a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_CUSTOM_NODE_ID_TIMEOUT );
	}

	A2B_DSCVRY_SEQEND( plugin->ctx );
}

/*!****************************************************************************
*
*  \b              a2b_dscvryCustomAuthFrmCommCh
*
*  Called after a node has been discovered.  This can be used to perform
*  custom node authentication by reading from mailbox.
*
*  \param          [in]    plugin   plugin specific data
*
*  \param          [in]    nodeSig  node signature data
*
*  \pre            Called on DSCDONE
*
*  \post           None
*
*  \return         FALSE=error
*                  TRUE=success
*
******************************************************************************/
static a2b_Bool a2b_dscvryCustomAuthFrmCommCh(a2b_Plugin* plugin, a2b_NodeSignature nodeSig)
{
	a2b_Bool 		bRet;
	a2b_CommChMsg	oCommChMsgGetCustNodeId;
	A2B_COMMCH_RET	bCommChRet;
	a2b_UInt16		nCommChInstNo;
    a2b_Int16 		dscNodeAddr = (a2b_Int16)plugin->discovery.dscNumNodes;
    a2b_Int16 		dscNodeIdx = dscNodeAddr+1;

	/* Program the mailbox registers so that we can exchange the authentication request and response messages over mailbox */
	bRet = a2b_dscvryNodeMailboxInit(plugin, dscNodeIdx);
	if(bRet == A2B_FALSE)
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rnodeDiscovered Node %hd authorization via Communication channel ," "Programming of Mailbox registers failed ", &dscNodeAddr );
#else	
		A2B_DSCVRY_ERROR1(plugin->ctx, "nodeDiscovered", "Node %hd authorization via Communication channel ," "Programming of Mailbox registers failed ", &dscNodeAddr );
#endif		
	}

	/* Copy the signature information to the plugin */
	plugin->slaveNodeSig[dscNodeAddr] = nodeSig;

	/* Prepare and send authentication message */
	oCommChMsgGetCustNodeId.nMsgId			= A2B_COMMCH_MSG_REQ_SLV_NODE_SIGNATURE;
	oCommChMsgGetCustNodeId.nMsgLenInBytes 	= 0u;
	oCommChMsgGetCustNodeId.pMsgPayload		= NULL;
	bRet = a2b_GetCommChInstIdForSlvNode(plugin, dscNodeAddr, &nCommChInstNo);
	if(bRet == A2B_TRUE)
	{
		bCommChRet = adi_a2b_CommChMstrTxMsg(plugin->commCh.commChHnd[nCommChInstNo], &oCommChMsgGetCustNodeId , (a2b_Int8)dscNodeAddr);
		if(bCommChRet == A2B_COMMCH_FAILED)
		{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cprintf("\n\rnodeDiscovered Node %hd authorization via Communication channel ," "Transmission of request Node id message failed ", &dscNodeAddr );
#else		
			A2B_DSCVRY_ERROR1(plugin->ctx, "nodeDiscovered", "Node %hd authorization via Communication channel ," "Transmission of request Node id message failed ", &dscNodeAddr );
#endif
		}
	}
	else
	{
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\rnodeDiscovered Node %hd authorization via Communication channel ," "Communication Channel Instance for slave node address not available ", &dscNodeAddr );
#else	
		A2B_DSCVRY_ERROR1(plugin->ctx, "nodeDiscovered", "Node %hd authorization via Communication channel ," "Communication Channel Instance for slave node address not available ", &dscNodeAddr );
#endif		
	}

	return (bRet);
}
#endif	/* A2B_FEATURE_COMM_CH */

/*!****************************************************************************
*
*  \b              adi_a2b_ConfigureNodePeri
*
*  Configure node and peripheral in modified and optimized modes of discovery
*
*  \param          [in]    plugin           plugin specific data
*  \param		   [in]	   dscNodeAddr      The address of the node that has
*      			   							to be configured
*
*  \pre            None
*
*  \post           None
*
*  \return          Returns a Boolean flag of whether the node was configured
*  					successfully.
******************************************************************************/
static a2b_Bool
adi_a2b_ConfigureNodePeri(a2b_Plugin* plugin, a2b_Int16 dscNodeAddr)
{

    a2b_UInt32 errCode;
    a2b_Bool	bRes;
    a2b_Int32 retCode = a2b_dscvryNodeComplete( plugin, dscNodeAddr,
                                                A2B_TRUE, &errCode );
    switch (retCode)
    {
        case A2B_EXEC_COMPLETE:
            /* No EEPROM Cfg (or done), so init the plugin now */
#ifdef FIND_NODE_HANDLER_AFTER_NODE_INIT
            a2b_dscvryFindNodeHandler(plugin, (a2b_UInt16)dscNodeAddr);
#endif
            if ( A2B_HAS_PLUGIN( plugin, dscNodeAddr ) )
            {
#if !defined(A2B_BCF_FROM_SOC_EEPROM) && !defined(A2B_BCF_FROM_FILE_IO)
                if ((a2b_UInt32)A2B_EC_OK != a2b_dscvryInitPlugin( plugin, dscNodeAddr,
                                    &a2b_dscvryInitPluginComplete_NoEeprom ))
                {
                	bRes = A2B_FALSE;
                	break;
                }
#endif
                bRes = A2B_TRUE;
                break;
            }
            bRes = A2B_FALSE;
            break;

        case A2B_EXEC_COMPLETE_FAIL:
            a2b_dscvryEnd( plugin, errCode );
            bRes = A2B_FALSE;
            break;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
        case A2B_EXEC_SCHEDULE:
        case A2B_EXEC_SUSPEND:
            if ( a2b_periphCfgUsingSync() )
            {
                /* Node peripheral processing has not completed,
                 * processing, will resume later--would be a delay
                 * cfg block or async processing.
                 */
            	bRes = A2B_TRUE;
            	break;
            }
            bRes = A2B_FALSE;
            break;
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */
        default:
        	bRes = A2B_FALSE;
        	break;
    }
    return (bRes);

} /* adi_a2b_ConfigureNodePeri */

/*!****************************************************************************
*
*  \b              adi_a2b_ConfigNodeOptimizAdvancedMode
*
*  Configure node and peripheral in optimized and advanced modes of discovery
*
*  \param          [in]    plugin           plugin specific data
*  \param          [in]    dscNodeAddr      Destination Node address
*
*  \pre            None
*
*  \post           None
*
*  \return         Returns the status of slave intialization for next node
*  				   discovery
*  				   FALSE=error
*                  TRUE=success
******************************************************************************/
static a2b_Bool
adi_a2b_ConfigNodeOptimizAdvancedMode(a2b_Plugin* plugin, a2b_Int16 dscNodeAddr)
{
    a2b_Bool bRet;

	bRet = a2b_dscvryPreSlaveInit( plugin );
	/* Configure Node registers and start plugin initialization */
	(void)adi_a2b_ConfigureNodePeri(plugin, dscNodeAddr);

	return bRet;
}

/*!****************************************************************************
*
*  \b              a2b_dscvryReset
*
*  Reset discovery (variables, A2B, etc)
* 
*  \param          [in]    plugin   plugin specific data
*
*  \pre            None
*
*  \post           None
*
*  \return         A2B_EXEC_COMPLETE == Execution is now complete
*                  A2B_EXEC_SCHEDULE == Execution is unfinished - schedule again
*                  A2B_EXEC_SUSPEND  == Execution is unfinished - suspend 
*                                       scheduling until a later event
*
******************************************************************************/
static a2b_Int32
a2b_dscvryReset
    (
    a2b_Plugin* plugin
    )
{
    a2b_UInt8 wBuf[4];
    a2b_UInt8 rBuf[4];
    a2b_HResult status;
#if defined(A2B_FEATURE_TRACE) && defined(A2B_FEATURE_EEPROM_OR_FILE_PROCESSING)
    a2b_UInt8 nTempVar;
#endif
#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
    a2b_Int32   mode = a2b_ovrGetDiscMode(plugin);
#endif

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
    (void)a2b_periphCfgPreparse( plugin );
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

    /* Unload any instantiated slave plugins */
    (void)a2b_stackFreeSlaveNodeHandler( plugin->ctx, A2B_NODEADDR_NOTUSED );

    /* Some discovery tracking variables need resetting */
    (void)a2b_memset( &plugin->discovery, 0, sizeof(a2b_PluginDiscovery) );
    plugin->discovery.inDiscovery = A2B_TRUE;

#ifdef A2B_FEATURE_EEPROM_OR_FILE_PROCESSING
#ifndef A2B_FEATURE_COMM_CH
    if ( a2b_stackCtxMailboxCount(plugin->ctx) !=
         A2B_ARRAY_SIZE(plugin->periph.node)+1u )
#else
	if (a2b_stackCtxMailboxCount(plugin->ctx) !=
		A2B_ARRAY_SIZE(plugin->periph.node) + 2u)
#endif
    {
        a2b_UInt8 idx;

        for ( idx = 0u; idx < A2B_ARRAY_SIZE(plugin->periph.node); idx++ )
        {
#ifdef A2B_FEATURE_TRACE
            nTempVar = idx;
#endif
            /* Init some static tracking needed for timers, etc */
            plugin->periph.node[idx].nodeAddr = (a2b_Int16)idx;
            plugin->periph.node[idx].plugin   = plugin;

            /* Create the mailbox for the master plugin 
             * discovery time EEPROM peripheral config 
             * handling/processing.  This allows use to
             * do peripheral config in parallel to the
             * discovery of other nodes.
             */
            plugin->periph.node[idx].mboxHnd = a2b_stackCtxMailboxAlloc(
                                                                plugin->ctx,
                                                                A2B_JOB_PRIO0 );
            if ( A2B_NULL == plugin->periph.node[idx].mboxHnd )
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cprintf("\n\rdscvryReset: failed to create peripheral mailbox %bd",
                         &nTempVar);
#else            
                A2B_TRACE1( (plugin->ctx, 
                         (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                         "dscvryReset: failed to create peripheral mailbox %bd",
                         &nTempVar));
#endif
            }
        }
    }
#endif /* A2B_FEATURE_EEPROM_OR_FILE_PROCESSING */

#if defined(A2B_FEATURE_SEQ_CHART)
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\r== Starting Discovery Mode %ld ==", 
                  &mode );
#else
    A2B_SEQ_RAW1( plugin->ctx, A2B_SEQ_CHART_LEVEL_DISCOVERY, 
                  "== Starting Discovery Mode %ld ==", 
                  &mode );
#endif                  
#endif

#if defined(A2B_FEATURE_TRACE)
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cprintf("\n\r%s dscvryReset(): Starting DiscoveryMode %ld", 
                A2B_MPLUGIN_PLUGIN_NAME, &mode);
#else
    A2B_TRACE2( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_DEBUG),
                "%s dscvryReset(): Starting DiscoveryMode %ld", 
                A2B_MPLUGIN_PLUGIN_NAME, &mode) );
#endif
#endif

    /* Read the master node's VID/PID */
    wBuf[0] = A2B_REG_VENDOR;
    status  = a2b_i2cMasterWriteRead( plugin->ctx, 1u, wBuf, 2u, rBuf );
    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryReset(): Cannot read master vid/pid",
                    A2B_MPLUGIN_PLUGIN_NAME) ;
#else  
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryReset(): Cannot read master vid/pid",
                    A2B_MPLUGIN_PLUGIN_NAME) );
#endif
        a2b_ReportI2CError(plugin, A2B_NODEADDR_MASTER);
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        return A2B_EXEC_COMPLETE;
    }

    /* Do a software reset on the A2B master node */
    wBuf[0] = A2B_REG_CONTROL;
    /* The AD242X (only) needs to be told it's a Master node BEFORE
     * the PLL locks on the SYNC pin. Once the PLL is locked, setting
     * the MSTR bit is ignored. We set it anyway so it's clear this is
     * the master node.
     */
    wBuf[1] = A2B_ENUM_CONTROL_RESET_PE;
    if ( a2b_isAd242xChip(rBuf[0u] /* vid */, rBuf[1u] /* pid */))
    {
        wBuf[1] |= (a2b_UInt8)A2B_ENUM_CONTROL_MSTR;
    }
    status  = a2b_i2cMasterWrite( plugin->ctx, 2u, &wBuf );

    if ( A2B_FAILED(status) )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryReset(): Cannot reset master", 
                    A2B_MPLUGIN_PLUGIN_NAME);
#else    
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryReset(): Cannot reset master", 
                    A2B_MPLUGIN_PLUGIN_NAME) );
#endif
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        return A2B_EXEC_COMPLETE;
    }

    if (!a2b_dscvryStartTimer( plugin, TIMER_RESET ))
    {
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INTERNAL );
        return A2B_EXEC_COMPLETE;
    }

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rdscvryReset...Reset Delay..." );
#else
    A2B_DSCVRY_RAWDEBUG0( plugin->ctx, "dscvryReset", "...Reset Delay..." );
#endif    

    return A2B_EXEC_SUSPEND;

} /* a2b_dscvryReset */


/*!****************************************************************************
*
*  \b              a2b_dscvryStart
*
*  Start the discovery process
* 
*  \param          [in]    plugin           plugin specific data
* 
*  \param          [in]    deinitFirst      deinit slave nodes prior
*                                           to discovery
*
*  \pre            None
*
*  \post           None
*
*  \return         A2B_EXEC_COMPLETE == Execution is now complete
*                  A2B_EXEC_SCHEDULE == Execution is unfinished - schedule again
*                  A2B_EXEC_SUSPEND  == Execution is unfinished - suspend 
*                                       scheduling until a later event
*
******************************************************************************/
a2b_Int32
a2b_dscvryStart
    (
    a2b_Plugin* plugin,
    a2b_Bool    deinitFirst
    )
{
	bdd_DiscoveryMode eDiscMode;
    if ( a2b_ovrGetDiscCfgMethod(plugin) == bdd_CONFIG_METHOD_AUTO )
    {
        /* Currently not supported at this time */
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryStart(): AUTO Config not supported", 
                     A2B_MPLUGIN_PLUGIN_NAME);
#else	
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryStart(): AUTO Config not supported", 
                     A2B_MPLUGIN_PLUGIN_NAME) );
#endif
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INVALID_PARAMETER );
        return A2B_EXEC_COMPLETE;
    }

    eDiscMode = a2b_ovrGetDiscMode(plugin);
    if ( (bdd_DISCOVERY_MODE_SIMPLE  != eDiscMode) &&
        (bdd_DISCOVERY_MODE_MODIFIED != eDiscMode) &&
		(bdd_DISCOVERY_MODE_OPTIMIZED  != eDiscMode) &&
		(bdd_DISCOVERY_MODE_ADVANCED  != eDiscMode))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryStart(): unsupported discovery mode", 
                     A2B_MPLUGIN_PLUGIN_NAME);
#else    
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryStart(): unsupported discovery mode", 
                     A2B_MPLUGIN_PLUGIN_NAME ));
#endif
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INVALID_PARAMETER );
        return A2B_EXEC_COMPLETE;
    }

    if ( plugin->discovery.inDiscovery )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryStart(): already in the process of discovery", 
                     A2B_MPLUGIN_PLUGIN_NAME);
#else
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryStart(): already in the process of discovery", 
                     A2B_MPLUGIN_PLUGIN_NAME ));
#endif
        a2b_dscvryEnd( plugin, (a2b_UInt32)A2B_EC_INVALID_STATE );
        return A2B_EXEC_COMPLETE;
    }

    if ( plugin->bdd->nodes_count == 1u )
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cprintf("\n\r%s dscvryStart(): No slave nodes",
                    A2B_MPLUGIN_PLUGIN_NAME);
#else    
        A2B_TRACE1( (plugin->ctx, (A2B_TRC_DOM_PLUGIN | A2B_TRC_LVL_ERROR),
                    "%s dscvryStart(): No slave nodes",
                    A2B_MPLUGIN_PLUGIN_NAME ));
#endif
        return A2B_EXEC_COMPLETE;
    }

    if ( deinitFirst )
    {
        a2b_dscvryDeinitPlugin( plugin, A2B_DEINIT_START );
        if ( plugin->discovery.pendingPluginDeinit )
        {
            /* Pending deinit messages so wait to reset and start */
            return A2B_EXEC_SUSPEND;
        }
    }

    return a2b_dscvryReset( plugin );

} /* a2b_dscvryStart */

/*!****************************************************************************
*
*  \b              a2b_SimpleModeChkNodeConfig
*
*  Check if previously discovered nodes are to be configured
*
*  \param          [in]    plugin           plugin specific data
*
*  \pre            None
*
*  \post           None
*
*  \return         A2B_TRUE == NetConfiguration is to be done
*                  A2B_FALSE == NetConfiguration is not to be done
*                  
******************************************************************************/
static a2b_Bool
a2b_SimpleModeChkNodeConfig(a2b_Plugin* plugin)
{
	a2b_Bool bIsConfigReqd = A2B_FALSE;
	if((plugin->discovery.dscNumNodes !=0u) &&
			((plugin->discovery.dscNumNodes != (plugin->bdd->nodes_count)-1u)))
		{
			bIsConfigReqd = A2B_TRUE;
		}
    return bIsConfigReqd;

} /* a2b_SimpleModeChkNodeConfig */

/*!****************************************************************************
*
*  \b              adi_a2b_ReConfigSlot
*
*  This function is responsible for (re)configuring  pass down-slots and
*  pass up-slots
*
*  \param          [in]    plugin           plugin specific data
*  \param		   [in]	   nodeAddr			Node address of the current node
*  				   							for which the slots has to be
*  				   							reconfigured.
*
*  \pre            None
*
*  \post           None
*
*
******************************************************************************/
static void
adi_a2b_ReConfigSlot(a2b_Plugin* plugin, a2b_Int16 nodeAddr)
{

    a2b_UInt8 wBuf[4];
    a2b_UInt8 rBuf[4];
    a2b_UInt16 nNodeIdx = (a2b_UInt16)((a2b_UInt32)nodeAddr + 1u);
    a2b_HResult status;

#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
	cputs("\n\rReconfig Slots Registers");   
#else
    A2B_DSCVRY_SEQGROUP0(plugin->ctx,
        "Reconfig Slots Registers");   
#endif        
    /* Clear BECCTL register for Sub node*/
    wBuf[0u] = A2B_REG_BECCTL;
    wBuf[1] = 0U;
    status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)nodeAddr), 2u, wBuf);
    if (A2B_FAILED(status))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rBECCTL Register Write Failed");
#else    
    	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
            "BECCTL Register Write Failed");
#endif            
    }

    /* Mask the BECOVF interrupt for Sub node*/
    wBuf[0u] = A2B_REG_INTMSK0;
    rBuf[0] = 0U;
    status = a2b_i2cSlaveWriteRead(plugin->ctx, ((a2b_Int16)nodeAddr), 1, wBuf, 1, rBuf);

    if (A2B_FAILED(status))
    {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
		cputs("\n\rINTMASK0 Register Read Failed");
#else    
    	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
            "INTMASK0 Register Read Failed");
#endif
    }
    else
    {
        wBuf[1] = rBuf[0] & (~A2B_BITM_INTPND0_BECOVF);
        status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)nodeAddr), 2u, wBuf);
        if (A2B_FAILED(status))
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rINTMSK0 Register Write Failed");
#else        
        	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
                "INTMSK0 Register Write Failed");
#endif                
        }
    }

    if (nodeAddr == 0)
    {
        /* Clear BECCTL register for Main node*/
        wBuf[0u] = A2B_REG_BECCTL;
        wBuf[1] = 0U;
        status = a2b_i2cMasterWrite(plugin->ctx, 2u, wBuf);
        if (A2B_FAILED(status))
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rBECCTL Register Write Failed");
#else        
        	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
                "BECCTL Register Write Failed");
#endif
        }

        /* Mask the BECOVF interrupt for Main node*/
        wBuf[0u] = A2B_REG_INTMSK0;
        rBuf[0] = 0U;
        status = a2b_i2cMasterWriteRead(plugin->ctx, 1, wBuf, 1, rBuf);

        if (A2B_FAILED(status))
        {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
			cputs("\n\rINTMASK0 Register Read Failed");
#else        
        	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
                "INTMASK0 Register Read Failed");
#endif                
        }
        else
        {
            wBuf[1] = rBuf[0] & (~A2B_BITM_INTPND0_BECOVF);
            status = a2b_i2cMasterWrite(plugin->ctx, 2u, wBuf);
            if (A2B_FAILED(status))
            {
#ifdef ESTEC_A2B_STACK_PORTING_DEBUG_ENABLE
				cputs("\n\rINTMSK0 Register Write Failed");
#else            
            	A2B_DSCVRY_ERROR0(plugin->ctx, adi_a2b_ReConfigSlot,
                    "INTMSK0 Register Write Failed");
#endif
            }
        }            
    }
      
    /* Write DN Slots for Sub node*/
    wBuf[0u] = A2B_REG_DNSLOTS;
    wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[nNodeIdx].ctrlRegs.dnslots;
    status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)nodeAddr), 2u, wBuf);
    /* Write Up Slots for Sub node */
    wBuf[0u] = A2B_REG_UPSLOTS;
    wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[nNodeIdx].ctrlRegs.upslots;
    status = a2b_i2cSlaveWrite(plugin->ctx, ((a2b_Int16)nodeAddr), 2u, wBuf);
   
    if (nodeAddr == 0u)
    {
        /* Write DN Slots for Main Node*/
        wBuf[0u] = A2B_REG_DNSLOTS;
        wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[0].ctrlRegs.dnslots;
        status = a2b_i2cMasterWrite(plugin->ctx, 2u, &wBuf);

        /*Write UP Slots for Main Node*/
        wBuf[0u] = A2B_REG_UPSLOTS;
        wBuf[1u] = (a2b_UInt8)plugin->bdd->nodes[0].ctrlRegs.upslots;
        status = a2b_i2cMasterWrite(plugin->ctx, 2u, &wBuf);
    }

	A2B_UNUSED(status);

	A2B_DSCVRY_SEQEND(plugin->ctx);
} /* adi_a2b_ReConfigSlot */

/*!****************************************************************************
*
*  \b              a2b_isAd242xChip
*
*  This function detects whether the A2B chip is a newer AD24XX
*  series chip.
*
*  \param          [in]    vendorId         Vendor Identifier
*  \param		   [in]	   productId		Product Identifier
*  \pre            None
*
*  \post           None
*
*
******************************************************************************/
static a2b_Bool a2b_isAd242xChip(a2b_UInt8 vendorId, a2b_UInt8 productId)
{
	return (A2B_IS_AD242X_CHIP(vendorId, productId));
}

/*!****************************************************************************
*
*  \b              a2b_isAd242xChip
*
*  This function detects whether the stack supportes the A2B chip.
*
*  \param          [in]    vendorId         Vendor Identifier
*  \param		   [in]	   productId		Product Identifier
*  \param		   [in]	   version			Version Number
*  \pre            None
*
*  \post           None
*
*
******************************************************************************/
static a2b_Bool a2b_stackSupportedNode(a2b_UInt8 vendorId, a2b_UInt8 productId, a2b_UInt8 version)
{
	A2B_UNUSED( version );
	return (A2B_STACK_SUPPORTED_NODE(vendorId, productId, version));
}

/*!****************************************************************************
*
*  \b              a2b_isCrossTalkFixApply
*
*  This function detects whether the A2B chip requires Cross talk fix or not
*
*  \param          [in]    vendorId         Vendor Identifier
*  \param		   [in]	   productId		Product Identifier
*  \pre            None
*
*  \post           None
*
*
******************************************************************************/
static a2b_Bool a2b_isCrossTalkFixApply(a2b_UInt8 vendorId, a2b_UInt8 productId)
{
	return (A2B_IS_AD2425X_CHIP(vendorId, productId) || A2B_IS_AD241X_CHIP(vendorId, productId));
}


/**
 @}
*/


/**
 @}
*/

#endif //#ifdef A2B_STACK_CODE_FROM_ADI
