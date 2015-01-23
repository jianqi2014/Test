enum { __FILE_NUM__= 0 };

/**********************************************************************!KA****
 *
 * $Header: /var/lib/cvs/sw/src/bt/app/btltp/btltpltp.c,v 1.75 2014/04/25 13:40:42 ka Exp $
 *
 * File:        $RCSfile: btltpltp.c,v $
 * Version:     $Name: P_SRP0007_U_KA_BLB1290_RC1 $
 *
 * Archive:     $Source: /var/lib/cvs/sw/src/bt/app/btltp/btltpltp.c,v $
 * Revision:    $Revision: 1.75 $
 * Date:        $Date: 2014/04/25 13:40:42 $
 * Author:      $Author: ka $
 *
 * ---------------------------------------------------------------------------
 * !MODULE      [  ]
 * ---------------------------------------------------------------------------
 * !FILE        [  ]
 * !PROGRAM     [  ]
 * !VERSION     [$Name: P_SRP0007_U_KA_BLB1290_RC1 $]
 * !GROUP       [  ]
 * !AUTHOR      [$Author: ka $]
 * ---------------------------------------------------------------------------
 *
 *          Copyright (c)           2008 Stollmann E+V GmbH
 *                                  Mendelssohnstr. 15
 *                                  22761 Hamburg
 *                                  Phone: 040/89088-0
 *          All Rights Reserved
 *
 * ---------------------------------------------------------------------------
 * !DESCRIPTION
 *
 *         LTP protocol handler
 * ---------------------------------------------------------------------------
 * !INDEX
 *  ...
 * ---------------------------------------------------------------------------
 * !CONTENTS
 * ---------------------------------------------------------------------------
 * !INCLUDE_REFERENCES
 * ---------------------------------------------------------------------------
 * !HISTORY
 *  Date      Author          Comment
 *  tt.mm.jj                  Initial revision
 *  tt.mm.jj
 * ---------------------------------------------------------------------------
 *
 * $Log: btltpltp.c,v $
 * Revision 1.75  2014/04/25 13:40:42  ka
 * issue 0012122# Prepare SDK release candidate
 *
 * Revision 1.74  2014/03/28 10:12:22  pm
 * issue #0012269: BlueAPI: implement OBEX LTP interface
 *
 * Revision 1.73  2014/03/26 10:46:54  pm
 * issue #0012004: Add HID device functionality and HID Demo App
 *   - changed message Interface according to BlueAPI specification
 *
 * Revision 1.72  2014/03/24 16:10:23  ka
 * issue 0012122#
 * Create Vendor Project with source base from PM Handover (P_BLB_U_PM_D_20140312)
 *
 * Revision 1.70.2.2  2014/03/12 08:03:37  pm
 * issue #0011680: BlueAPI: implement HID interface
 *
 * Revision 1.70.2.1  2013/10/18 09:32:05  mn
 * issue 0011138
 * Non OSIF.
 *
 * Revision 1.70  2013/09/25 14:33:50  ore
 * issue 0010651
 * BlueAPI: allow application to set SSP display value for LE authentication
 *
 * Revision 1.69  2013/09/24 14:18:11  ore
 * issue 0008066
 * BlueAPI: Support for max TX Power needed
 *
 * Revision 1.68  2013/09/24 14:08:54  ore
 * issue 0008067
 * BlueAPI: Support for Absolute RSSI needed
 *
 * Revision 1.67  2013/09/18 09:50:24  ore
 * issue 0008368
 * BlueAPI: Add configuration Interface for sniff mode
 *
 * Revision 1.66  2013/09/18 09:39:59  ore
 * issue 0010994
 * BlueAPI: add API for link policy configuration
 *
 * Revision 1.65  2013/08/28 13:36:17  ore
 * issue 0010851
 * remove btsec includes
 *
 * Revision 1.64  2013/08/28 09:06:38  ore
 * issue 0010843
 * BlueAPI: add pagescan- and linkpolicy configuration
 *
 * Revision 1.63  2013/08/21 13:37:06  ore
 * issue 0010803
 * BlueAPI: split up DeviceConfigSetReq
 *
 * Revision 1.62  2013/07/10 14:26:56  ore
 * issue 0009823
 * LE: add random resolvable address resolution / privacy mode
 *
 * Revision 1.61  2013/07/09 13:49:49  ore
 * issue 0010462
 * cleanup new trace calls
 *
 * Revision 1.60  2013/05/31 14:05:05  mj
 * issue #0010119
 * Remove GNU compiler warnings.
 *
 * Revision 1.59  2013/02/27 18:08:55  ore
 * issue 0008926
 * fix VS2005 compiler warnings
 *
 * Revision 1.58  2013/02/26 11:03:21  ore
 * issue 0008354
 * fix ConnectMDLGATTRsp / GATT context handling
 *
 * Revision 1.57  2013/02/12 13:20:29  ore
 * issue 0008354
 * change GATTSecurityReq requirements to WORD
 *
 * Revision 1.56  2013/02/03 15:31:01  ore
 * issue 0008536
 * LE: remove patching of advertising data with discoverable mode / device name
 *
 * Revision 1.55  2013/01/10 10:01:23  ore
 * issue 0007701
 * LTP: no error response when sending data to not existing MDL
 *
 * Revision 1.54  2013/01/09 14:16:43  ore
 * issue 0008354
 * implement LTP BLE/GATT messages
 *
 * Revision 1.53  2012/11/29 16:29:20  ore
 * issue #0008139
 * BlueAPI: Implement Inquiry Cancel
 *
 * Revision 1.52  2012/11/01 08:43:56  ore
 * issue #7952
 * move osif / hardware specific code
 *
 * Revision 1.51  2012/10/31 18:25:48  ore
 * issue #7949
 * fix VS2005 compiler warnings
 *
 * Revision 1.50  2012/09/10 13:01:43  ore
 * 0007786: BlueAPI: add BLE / GATT external storage interface
 *
 * Revision 1.49  2012/08/31 12:12:17  ore
 * 0007773: BlueAPI: add HDP/SPP prefix to LinkConfigTypes
 *
 * Revision 1.48  2012/08/16 16:37:09  ore
 * 0007652: BlueAPI: add limited discoverable mode support
 * 0007653: BlueAPI: add limited inquiry support
 *
 * Revision 1.47  2012/07/23 15:22:11  ore
 * 0007663: LTP: do not start configurator if no configurator is present
 *
 * Revision 1.46  2012/07/13 16:59:46  ore
 * 0007636: BlueAPI: move NULL checks to API functions
 *
 * Revision 1.45  2012/07/13 09:52:05  mj
 * 0007625: Harmonization with BlueAPI spec.
 *
 * Revision 1.44  2012/07/12 17:04:50  mj
 * 0007592: Replace blueAPI_GATTConnectReq() by distinct routines for each
 * profile (HDP,SPP,GATT)
 *
 * Revision 1.43  2012/07/04 09:39:30  ore
 * 0007585: BlueAPI: use C99 uintx_t and bool instead of BYTE, WORD etc.
 *
 * Revision 1.42  2012/05/31 11:59:25  odr
 * issue #0006776 Add DeviceConfiguration to message interface
 * Added DeviceConfigSetReq and DeviceNameReq
 *
 * Revision 1.41  2012/05/31 07:21:36  odr
 * issue #7460: Flag handler code where handlers are flagged in switch case
 *
 * Revision 1.40  2012/04/30 09:59:07  ore
 * fix previous commit (broke fix for #6294)
 *
 * Revision 1.39  2012/03/22 14:09:05  ore
 * cleanup ConfigTunnelReq
 *
 * Revision 1.38  2012/03/20 08:21:53  odr
 * Internal Change 7216: API renaming and cleaning
 * Contains changes from API_RENAMED branch
 *
 * Revision 1.37.2.2  2012/03/19 14:03:43  odr
 * API renamed: Changed includes to fit new file names
 *
 * Revision 1.37.2.1  2012/03/06 15:57:32  odr
 * - adapted function calls, enums and defines to new BlueAPI norm
 *
 * Revision 1.37  2012/01/02 15:48:09  ka
 * introduced flag 'BTMED_HDP_SUPPORT' to allow disabeling of HDP profile
 *
 * Revision 1.36  2011/07/28 16:19:50  odr
 * BTLTPHandleConfigTunnelReq() optimized for F_CONFIG_APP=0.
 *
 * Revision 1.35  2011/04/11 11:56:36  ore
 * fix 0006103: LTP: Change CreateMDLConf default linkconfigtype
 *
 * Revision 1.34  2011/03/07 15:12:20  ore
 * cleanup previous commit
 *
 * Revision 1.33  2011/03/04 17:31:11  ka
 * 0005577: function of BTSEC feature request 0005576 shall be made available foe BlueHDP+ and LTP
 *
 * Revision 1.32  2011/02/18 10:19:52  ore
 * 0005857: LTP: remove unused return value from handler functions
 *
 * Revision 1.31  2011/02/18 09:09:55  ore
 * fix 0003481: software watchdog is used to perform system reset on LTP_RESET_REQ
 * - fix reset in error path
 * - use LTPLibSendResetRsp
 *
 * Revision 1.30  2010/12/30 13:22:36  ore
 * fix 0005597: LTP pool switching not usable with multiple MDLs
 * - rename context
 *
 * Revision 1.29  2010/10/07 12:52:22  ore
 * fix 0005341: [LTP]Fragment ConfigTunnelInfo messages
 *
 * Revision 1.28  2010/09/29 13:46:13  ore
 * fix 0005265: [LTP]rename BTMED_* defines to BTLTP_*
 *
 * Revision 1.27  2010/08/30 12:52:34  ore
 * add DID discovery as optional parameter
 *
 * Revision 1.26  2010/08/27 14:04:25  ka
 * implement: 0005067: Add DID discovery option to SPPDiscoveryReq
 *
 * Revision 1.25  2010/08/17 09:55:20  ore
 * fix 0004951: Remove traceoutput from LTP module
 *
 * Revision 1.24  2010/07/23 07:31:21  ore
 * fix 0004795: Optional parameters of ReconnectMDLReq not parsed correctly
 *
 * Revision 1.23  2010/07/09 16:19:36  ore
 * fix 0004411: [LTP]Ensure DataConf delivery
 *
 * Revision 1.22  2010/07/06 15:13:21  ore
 * fix 0004648: Initiator echoes data back in legacy mode
 * - change local_mdep_id default
 * - only acceptor shall echo data back
 *
 * Revision 1.21  2010/06/08 14:12:01  ka
 * Fix: 0004380: [LTP] handling of "LTP_NotSupported" Confirmation messages
 *
 * Revision 1.20  2010/05/03 14:29:55  ka
 * - fixed tunnel request
 *
 * Revision 1.19  2010/04/28 13:23:13  ore
 * - add creditbased flowcontrol
 * - fix ConnectMDLInfo and ReconnectMDLReq
 * - remove tempBuffer
 *
 * Revision 1.18  2010/04/15 16:38:41  ore
 * implement missing BTLTPHandlePasskeyReqReplyReq
 *
 * Revision 1.17  2010/03/26 12:38:51  ore
 * - add BD to PasskeyNotificationInfo
 * - add BD to KeypressNotificationInfo
 * - add DisplayValue to UserConfRequestInd
 * - add cause/BD to UserConfRequestCnf
 *
 * Revision 1.16  2010/03/25 17:51:40  ore
 * CreateMDLConf: maxTPDUusCredits is a byte
 *
 * Revision 1.15  2010/03/25 16:48:49  ka
 * interim version for LTP1.3 bootstrap (fixed trace)
 *
 * Revision 1.14  2010/03/22 15:25:52  ka
 * interim version for LTP1.3 bootstrap (add SetRadioMode handling)
 *
 * Revision 1.13  2010/03/19 16:50:04  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.12  2010/03/19 12:31:11  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.11  2010/03/18 18:22:38  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.10  2010/03/18 12:39:40  ore
 * interim version
 *
 * Revision 1.9  2010/03/16 17:57:31  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.8  2009/07/15 08:39:07  ka
 * addopted new COM features
 *
 * Revision 1.7  2008/10/24 14:38:08  ka
 * - introduced authentication via LTP
 * - removed VMOD
 * - introduced Multilink/Multimdl support
 * - bugfix for SDP and eL2CAP
 * - several other bugfixes
 *
 * Revision 1.6  2008/08/20 13:34:01  ka
 * - introduced LTP-Library
 * - bugfix for data-resp missing
 *
 * Revision 1.5  2008/08/13 11:07:07  ka
 * remocet btltpcmd dependencies
 *
 * Revision 1.4  2008/08/13 11:03:02  ka
 * added reconnect support
 *
 * Revision 1.3  2008/07/23 17:34:16  ka
 * - added DeviceID Service Parameter to DB
 * - changed SDP record handling (use buffer)
 * - addopted to new Flags
 *
 * Revision 1.2  2008/07/22 16:16:59  ka
 * added Inquiry/ServiceDiscovery commands
 *
 * Revision 1.1  2008/07/03 12:10:53  ka
 * first VASC version
 *
 * Initial revision.
 *
 ************************************************************************!KA*/

//#include <basetype.h>
//#include <btglbdef.h>
#include <blueapi_types.h>
#include <blueapi.h>
#include "btltp.h"
#include "gatt.h"
#include <trace_binary.h>
#include "diag.h"
#include "efuse_config.h"
#include "otp.h"
#include "dlps_platform.h"

#define LTP_SOURCE_FILE_ID 0x82

/****************************************************************************/
/* void BTLTPHandleExitReq                                                  */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleExitReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, LPBYTE pPara)
{
    LPBYTE       pInsert = pBTLtp->pMsgBuffer;
    WORD         pos     = 0;

    BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                           "LTP: >>ExitReq"
                          );

    /* prepare confirmation                                                 */
    pInsert[pos++] = LTP_EXIT_RSP;
    pInsert[pos++] = 0x00;                                    /* copmsk     */
    NETSHORT2CHAR(&pInsert[pos], LTP_EXIT_RSP_LENGTH);
    pos += 2; /* msg length */
    pInsert[pos++] = LTP_CAUSE_NOT_SUPPORTED;
    /* send LTP messages                                                    */
    BTLTPTgtSendLTPMessage(pBTLtp, pBTLtp->pMsgBuffer, 0, pos);
}

/* handle register stack request */
void BTLTPHandleRegisterStackReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
	blueAPI_RegisterReq(P_BtLtp, (void *)ltpBlueAPICallback);
}

/* handle dlps conrol */
void BTLTPHandleConfigDlpsReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{	
	uint8_t is_invalid_param = 0;
	uint16_t pos     = 0;
    uint8_t* pBuffer = NULL;
	
	/* enable dlps mode */
	if(*pPara == 0x01) 
	{
		/* enable dlps log */
		if(*(pPara + 1) == 0x01)
		{
			EnableDlpsLog = 1;
		}
		DLPS_INTERRUPT_CONTROL_CB_REG(LTP_EnterDlps, DLPS_ENTER);
		DLPS_INTERRUPT_CONTROL_CB_REG(LTP_ExitDlps, DLPS_EXIT);
		LPS_MODE_Set(LPM_DLPS_MODE);
	}
	else if(*pPara == 0x02)	/* pause dpls mode */
	{
		LPS_MODE_Pause();
	}
	else if(*pPara == 0x03)	/* resume dpls mode */
	{
		LPS_MODE_Resume();
	}
	else
	{
		is_invalid_param = 1;
	}
    
	if(is_invalid_param)
	{
		LTPLibSendInternalEventInfo(&pBTLtp->LTPLib, 0, NULL, LTP_CAUSE_INVALID_PARAMETER, LTP_INTERNAL_EVENT_COMMUNICATION_OUT_OF_SYNC, LTP_GENERATE_EVENT_ID);
		return;
	}
	
	pBuffer = BTLTPTgtSendBufferAlloc(pBTLtp, LTP_CONFIG_DLPS_RSP_LENGTH + 1);

    if(pBuffer)
    {
    	pBuffer[pos++] = LTP_CONFIG_DLPS_RSP;
	    pBuffer[pos++] = BTLTP_DEFAULT_COPMSK;                              /* copmsk */
	    NETSHORT2CHAR(&pBuffer[pos], LTP_CONFIG_DLPS_RSP_LENGTH + 1);       /* msg length */
	    pos += 2; 													    
	    pBuffer[pos++] = BTLTPTgtDoCRC8(&pBTLtp->LTPLib, pBuffer, LTP_DATA_MIN_HEADER_LENGTH);  /* crc */
	    pBuffer[pos++] = LTP_CAUSE_SUCCESS;   /* cause */
	    pBuffer[pos++] = *pPara;
	    /* send LTP messages */
	    BTLTPTgtSendLTPMessage(pBTLtp, pBuffer, 0, pos);
	}
	else
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "BTLTPHandleConfigDlpsReq:malloc fail", 0);
	}
	
	return;
}


/****************************************************************************/
/* void BTLTPHandleConnectMDLReq                                            */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleConnectMDLReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD                 pos = 0;
    LPBYTE               rem_BD;                                /* mandatory */
    BYTE                 rem_MDEP_ID;                           /* mandatory */
    BYTE                 loc_MDEP_ID    = 0x01;                 /* default   */
    //TBlueAPI_LinkConfigType linkConfigType = blueAPI_LinkConfigHDPDontCare;/* default */
    BYTE linkConfigType  = 4; /* tifnan for upper stack changes, not used here */
#if (F_BLUE_API_HDP_SUPPORT)
    WORD                 rem_C_PSM;                             /* mandatory */
    WORD                 rem_D_PSM;                             /* mandatory */
#endif

    /* read mandatory parameters                                             */
    rem_BD = pPara;
    pos += 6;

    rem_MDEP_ID = pPara[pos++];
#if (F_BLUE_API_HDP_SUPPORT)
    rem_C_PSM   = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    rem_D_PSM   = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
#endif
    /* read optional parameters                                              */
    pos = 0;
    if (copmsk & LTP_CONNECT_MDL_REQ_OPT_MASK_LINK_TYPE)
    {
        //linkConfigType = (TBlueAPI_LinkConfigType)pOpt[pos++];
        linkConfigType  = 4; /* tifnan for upper stack changes */
    }

    if (copmsk & LTP_CONNECT_MDL_REQ_OPT_MASK_LOC_MDEP_ID)
    {
        loc_MDEP_ID = pOpt[pos++];
    }

    switch (linkConfigType)
    {
    default:
        {
            BYTE pOpt[2];

            pOpt[0] = 0x00; /* loc_MDL_ID */
            pOpt[1] = loc_MDEP_ID;

            LTPLibSendConnectMDLRsp(&pBTLtp->LTPLib,
                                    (BTLTP_DEFAULT_COPMSK |
                                     LTP_CONNECT_MDL_RSP_OPT_MASK_LOC_MDL_ID |
                                     LTP_CONNECT_MDL_RSP_OPT_MASK_LOC_MDEP_ID),
                                    pOpt,
                                    LTP_CAUSE_INVALID_PARAMETER,
                                    rem_BD,
                                    rem_MDEP_ID
                                   );
            break;
        }
    }
}

/****************************************************************************/
/* void BTLTPHandleCreateMDLConf                                            */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleCreateMDLConf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    //TBlueAPI_LinkConfigType linkConfigType   = blueAPI_LinkConfigHDPReliable;
    //BYTE linkConfigType = 4; /* tifnan: for upper stack changes, not used here */
    WORD                 pos              = 0;
    BYTE                 local_MDL_ID     = 0;                  /* mandatory */
    BYTE                 maxTPDUusCredits = 0;                  /* default   */
    BYTE                 cause;


    /* read mandatory parameters                                             */
    cause        = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        local_MDL_ID = pPara[pos++];
    }

    /* read optional parameters                                              */
    pos = 0;
    if (copmsk & LTP_CREATE_MDL_CNF_OPT_MASK_LINK_TYPE)
    {
        //linkConfigType = pOpt[pos++];
        //linkConfigType = 4; /* tifnan:  for upper stack changes */
    }
    if (copmsk & LTP_CREATE_MDL_CNF_OPT_MASK_MAX_TPDU_US_CREDITS)
    {
        maxTPDUusCredits = pOpt[pos++];
    }

    blueAPI_CreateMDLConf(//pBTLtp->pMsgBuffer,
                          //pBTLtp->blueAPIHandle,
                          local_MDL_ID,
                          maxTPDUusCredits,
                          BTLTPConvertLTPtoCOMcause(cause)
                         );
}

/****************************************************************************/
/* void BTLTPHandleDisconnectMDLConf                                        */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleDisconnectMDLConf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    BYTE          local_MDL_ID;
    WORD          pos          = 0;


    /* read mandatory parameters                                             */
    local_MDL_ID = pPara[pos++];


    /* read optional parameters                                              */

    blueAPI_DisconnectMDLConf(//pBTLtp->pMsgBuffer,
                              //pBTLtp->blueAPIHandle,
                              local_MDL_ID
                             );
}

/****************************************************************************/
/* void BTLTPHandleDisconnectMDLConf                                        */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleDisconnectMDLReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    BYTE          local_MDL_ID = 0;                             /* mandatory */
    WORD          pos          = 0;
    BYTE          cause;


    /* read mandatory parameters                                             */
    cause        = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        local_MDL_ID = pPara[pos++];
    }

    /* read optional parameters                                              */
    /* non */

    blueAPI_DisconnectMDLReq(//pBTLtp->pMsgBuffer,
                             //pBTLtp->blueAPIHandle,
                             local_MDL_ID,
                             BTLTPConvertLTPtoCOMcause(cause)
                            );
}

/****************************************************************************/
/* void BTLTPHandleResetReq                                                 */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleResetReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    BOOL result = FALSE;

    BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                           "LTP: >>ResetReq"
                          );
    

    pBTLtp->pBufferAction = BTLTPAllocateAction(pBTLtp);
    if (pBTLtp->pBufferAction)
    {
        pBTLtp->pBufferAction->Action = btltpActionReset;

        result = LTPLibSendResetRsp(&pBTLtp->LTPLib, BTLTP_DEFAULT_COPMSK, NULL, LTP_CAUSE_SUCCESS);

        if (!result)
        {
            pBTLtp->pBufferAction->Action = btltpActionNotUsed;
            pBTLtp->pBufferAction         = NULL;
        }
    }

	/* if enable free dynamically off area ram before entering dlps!!!! */
	if(1 == otp_str_data.gEfuse_Ltp_s.ltp_off_ram_save)
	{
		BTLTPTgtAssemblyBufferRelease(&pBTLtp->LTPLib, pBTLtp->LTPLib.pLTPMsg);
    	pBTLtp->LTPLib.pLTPMsg = NULL;
	} 

    if (!result)
    {
        THandle      handle;
        TBTLtpAction directAction;
        directAction.Action = btltpActionReset;

        handle.lpHandle = (LPVOID)&directAction;
        BTLTPBufferCallback(handle);
    }
}

/****************************************************************************/
/* void BTLTPHandlePasskeyRequestCnf                                        */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandlePasskeyRequestCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD   pos = 0;
    BYTE   cause;                                               /* mandatory */
    LPBYTE rem_BD = NULL;                                       /* mandatory */


    /* read mandatory parameters                                             */
    cause = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        rem_BD = &pPara[pos];
        pos += 6;
    }

    /* read optional parameters                                              */
    /* non */

    blueAPI_UserPasskeyReqConf(//pBTLtp->pMsgBuffer,
                               //pBTLtp->blueAPIHandle,
                               rem_BD,
                               BTLTPConvertLTPtoCOMcause(cause)
                              );
}

/****************************************************************************/
/* void BTLTPHandleOOBRequestCnf                                            */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleOOBRequestCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD   pos = 0;
    LPBYTE rem_BD = NULL;                                       /* mandatory */
    LPBYTE C      = NULL;                                       /* mandatory */
    BYTE   cause;                                               /* mandatory */


    /* read mandatory parameters                                             */
    cause = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        rem_BD = &pPara[pos];
        pos += 6;
        C      = &pPara[pos];
        pos += 16;
    }
    /* read optional parameters                                              */
    /* non */

    blueAPI_RemoteOOBDataReqConf(//pBTLtp->pMsgBuffer,
                                 //pBTLtp->blueAPIHandle,
                                 rem_BD,
                                 C,
                                 BTLTPConvertLTPtoCOMcause(cause)
                                );
}

/****************************************************************************/
/* void BTLTPHandleAuthResultCnf                                            */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleAuthResultCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD   pos = 0;
    LPBYTE rem_BD = NULL;                                       /* mandatory */
    //DWORD  AppData = 0x00000000;                                /* mandatory */
    BYTE   cause;                                               /* mandatory */


    /* read mandatory parameters                                             */
    cause   = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        rem_BD  = &pPara[pos];
        pos += 6;
        //AppData = NETCHAR2LONG(&pPara[pos]);
        pos += 4;
    }
    /* read optional parameters                                              */
    /* non */

    blueAPI_AuthResultConf(//pBTLtp->pMsgBuffer,
                           //pBTLtp->blueAPIHandle,
                           rem_BD,
                           blueAPI_RemoteBDTypeClassic,
                           BTLTPConvertLTPtoCOMcause(cause)
                          );
}


/****************************************************************************/
/* void BTLTPHandleAuthResultExtCnf                                         */
/****************************************************************************/
void BTLTPHandleAuthResultExtCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD   pos = 0;
    BYTE   cause;
    LPBYTE rem_BD      = NULL;
    BYTE   rem_BD_Type = blueAPI_RemoteBDTypeClassic;
    //DWORD  AppData     = 0x00000000;


    /* read mandatory parameters                                             */
    cause = pPara[pos++];

    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        rem_BD      = &pPara[pos];
        pos += 6;
        rem_BD_Type = pPara[pos++];
        //AppData     = NETCHAR2LONG(&pPara[pos]);
        pos += 4;
    }

    /* read optional parameters                                              */
    /* non */

    blueAPI_AuthResultConf(//pBTLtp->pMsgBuffer,
                           //pBTLtp->blueAPIHandle,
                           rem_BD,
                           (TBlueAPI_RemoteBDType)rem_BD_Type,
                           BTLTPConvertLTPtoCOMcause(cause)
                          );
} /* BTLTPHandleAuthResultExtCnf */

void BTLTPHandleAuthResultRequestExtCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
  WORD          pos            = 0;
  LPBYTE        rem_BD         = NULL;
  BYTE          rem_BD_Type    = blueAPI_RemoteBDTypeClassic;
  LPBYTE        linkKey        = NULL;
  BYTE          linkKeyLength  = 0;
  BYTE          keyType        = 0;
  BYTE          cause;
  WORD          restartHandle  = 0x0000;                      /* optional  */


  /* read mandatory parameters                                             */
  cause = pPara[pos++];

  if (cause != LTP_CAUSE_NOT_SUPPORTED)
  {
    rem_BD        = &pPara[pos]; pos += 6;
    rem_BD_Type   = pPara[pos++];
    keyType       = pPara[pos++];
    linkKeyLength = lenPara - pos;
    linkKey       = &pPara[pos]; pos += linkKeyLength;
  }

  /* read optional parameters                                              */
  pos=0;

  if (copmsk & LTP_AUTH_RESULT_REQUEST_EXT_CNF_OPT_MASK_RESTART_HANDLE)
  {
    restartHandle = NETCHAR2SHORT(&pOpt[pos]); pos+=2;
  }

  blueAPI_AuthResultRequestConf(
                                rem_BD,
                                (TBlueAPI_RemoteBDType)rem_BD_Type,
                                linkKeyLength,
                                linkKey,
                                (TBlueAPI_LinkKeyType)keyType,
                                restartHandle,
                                BTLTPConvertLTPtoCOMcause(cause)
                                );
} /* BTLTPHandleAuthResultRequestExtCnf */


/****************************************************************************/
/* BOOL BTLTPHandleConfigTunnelReq                                          */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
BOOL BTLTPHandleConfigTunnelReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    LTPLibSendConfigTunnelRsp(&pBTLtp->LTPLib, BTLTP_DEFAULT_COPMSK, NULL, LTP_CAUSE_NOT_SUPPORTED);
    return TRUE;
}

/****************************************************************************/
/* void BTLTPHandlePairableModeSetReq                                       */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandlePairableModeSetReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BOOL                   enablePairableMode;                  /* mandatory */
    TBlueAPI_AuthRequirements AuthRequirements;                    /* mandatory */
    TBlueAPI_IOCapabilities   IOCapabilities;                      /* mandatory */
    BOOL                   remoteOOBDataPresent;                /* mandatory */


    /* read mandatory parameters                                             */
    enablePairableMode   = (BOOL)pPara[pos++];
    pos++;	/* skip btmode para, not used now */
    AuthRequirements     = (TBlueAPI_AuthRequirements)pPara[pos++];
    IOCapabilities       = (TBlueAPI_IOCapabilities)pPara[pos++];
    remoteOOBDataPresent = (BOOL)pPara[pos++];

    /* read optional parameters                                              */
    /* non */

    blueAPI_PairableModeSetReq(//pBTLtp->pMsgBuffer,
                               //pBTLtp->blueAPIHandle,
                               enablePairableMode,
                               AuthRequirements,
                               IOCapabilities,
                               remoteOOBDataPresent
                              );
}

/****************************************************************************/
/* void BTLTPHandlePasskeyReqReplyReq                                       */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandlePasskeyReqReplyReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD              pos       = 0;
    TBlueAPI_Cause    cause;                                    /* mandatory */
    LPBYTE            rem_BD;                                   /* mandatory */
    DWORD             passKey;                                  /* mandatory */


    /* read mandatory parameters                                             */
    cause    = (TBlueAPI_Cause)pPara[pos++];
    rem_BD   = &pPara[pos];
    pos += 6;
    passKey  = NETCHAR2LONG(&pPara[pos]);
    pos += 4;

    /* read optional parameters                                              */
    /* non */

    blueAPI_UserPasskeyReqReplyReq(//pBTLtp->pMsgBuffer,
                                   //pBTLtp->blueAPIHandle,
                                   rem_BD,
                                   passKey,
                                   cause
                                  );
}

/****************************************************************************
 * BTLTPHandleGATTServiceRegisterReq
 ****************************************************************************/
void BTLTPHandleGATTServiceRegisterReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                       WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    //BYTE serviceID;
    WORD nbrOfAttrib;
    BYTE MDL_ID;
    //BYTE serviceChanged;

    /* read mandatory parameters                                             */
    //serviceID       = pPara[pos++];
    pos++;  //skip service id
    nbrOfAttrib     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    MDL_ID          = pPara[pos++];
    //serviceChanged  = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    /* TODO: service upload not implemented, prevent unused variable warning */
    MDL_ID = MDL_ID;

    /* tifnan: add for services app provided */
    //serviceID = 0;
    nbrOfAttrib = GattdFindMeProfileSize / sizeof(TAttribAppl);
    blueAPI_GATTServiceRegisterReq(//pBTLtp->pMsgBuffer,
                                   //pBTLtp->blueAPIHandle,
                                   //(TBlueAPI_GATTServiceID)serviceID,
                                   nbrOfAttrib,
                                   (void*)GattdFindMeProfile
                                  );
    /* tifnan add end */
    /*blueAPI_GATTServiceRegisterReq(pBTLtp->pMsgBuffer,
                                   pBTLtp->blueAPIHandle,
                                   (TBlueAPI_GATTServiceID)serviceID,
                                   nbrOfAttrib,
                                   NULL,
                                   serviceChanged
                                   );*/
} /* BTLTPHandleGATTServiceRegisterReq */


/****************************************************************************
 * BTLTPHandleGATTServiceReleaseReq
 ****************************************************************************/
void BTLTPHandleGATTServiceReleaseReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE serviceHandle;

    /* read mandatory parameters                                             */
    serviceHandle = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    /* TODO: not implemented, return not supported */
    LTPLibSendGATTServiceReleaseRsp(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    blueAPI_CauseNotSupported,
                                    0x0000,
                                    serviceHandle
                                   );
} /* BTLTPHandleGATTServiceReleaseReq */


/****************************************************************************
 * BTLTPHandleGATTAttributeUpdateReq
 ****************************************************************************/
BOOL BTLTPHandleGATTAttributeUpdateReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                       WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE serviceHandle;
    WORD attribIndex;
    union
    {
        DWORD   d;
        void   *p;
    } requestHandle;

    uint16_t wOffset = 0;
    uint16_t ds_pool_id = 0;
    uint8_t* pBuffer = NULL;

    /* read mandatory parameters                                             */
    serviceHandle   = pPara[pos++];
    requestHandle.d = pPara[pos++];
    attribIndex     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    /* read optional parameters                                              */
    /* none */
    PBTLtpMDLContext p_mdl_context = BTLTPFindAMDLConnected(pBTLtp);

    if(p_mdl_context)
    {
    	wOffset = p_mdl_context->dsDataOffset + 3;
		ds_pool_id = p_mdl_context->dsPoolID;
    }
    
    if(blueAPI_CauseSuccess == blueAPI_BufferGet(ds_pool_id,  lenPara - pos, wOffset, (void**)&pBuffer))
    {
    	memcpy(pBuffer + wOffset, pPara + pos, lenPara - pos);
    	if(!blueAPI_GATTAttributeUpdateReq(pBuffer,
                                   BTLTPLookupGATTServiceHandle(pBTLtp, serviceHandle),
                                   requestHandle.p,
                                   attribIndex,
                                   (lenPara - pos),
                        		   wOffset
                                  ))
        {
        	blueAPI_BufferRelease(pBuffer);
        }
    }
    else
    {
    	 DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "blueAPI_BufferGet failed!", 0);
    }

    return FALSE;
} /* BTLTPHandleGATTAttributeUpdateReq */


/****************************************************************************
 * BTLTPHandleGATTAttributeUpdateStatusCnf
 ****************************************************************************/
void BTLTPHandleGATTAttributeUpdateStatusCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
        WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    BYTE serviceHandle = 0x00;
    WORD attribIndex   = 0x00;
    union
    {
        DWORD   d;
        void   *p;
    } requestHandle;

    requestHandle.d = 0;

    /* read mandatory parameters                                             */
    cause           = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        serviceHandle   = pPara[pos++];
        requestHandle.d = pPara[pos++];
        attribIndex     = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTAttributeUpdateStatusConf(//pBTLtp->pMsgBuffer,
                                          //pBTLtp->blueAPIHandle,
                                          BTLTPLookupGATTServiceHandle(pBTLtp, serviceHandle),
                                          requestHandle.p,
                                          attribIndex
                                         );
} /* BTLTPHandleGATTAttributeUpdateStatusCnf */


/****************************************************************************
 * BTLTPHandleGATTAttributeReadCnf
 ****************************************************************************/
BOOL BTLTPHandleGATTAttributeReadCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                     WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    WORD subCause       = 0x0000;
    BYTE loc_MDL_ID     = 0x00;
    BYTE serviceHandle  = 0x00;
    WORD attribIndex    = 0x00;

    /* read mandatory parameters                                             */
    cause           = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        subCause      = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
        loc_MDL_ID    = pPara[pos++];
        serviceHandle = pPara[pos++];
        attribIndex   = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTAttributeReadConf(pBTLtp->pMsgBuffer,
                                  //pBTLtp->blueAPIHandle,
                                  loc_MDL_ID,
                                  BTLTPLookupGATTServiceHandle(pBTLtp, serviceHandle),
                                  (TBlueAPI_Cause)cause,
                                  subCause,
                                  attribIndex,
                                  (lenPara - pos),
                                  (WORD)((pPara + pos) - pBTLtp->pMsgBuffer)
                                 );

    return FALSE;
} /* BTLTPHandleGATTAttributeReadCnf */


/****************************************************************************
 * BTLTPHandleGATTAttributeWriteCnf
 ****************************************************************************/
void BTLTPHandleGATTAttributeWriteCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    WORD subCause       = 0x0000;
    BYTE loc_MDL_ID     = 0x00;
    BYTE serviceHandle  = 0x00;
    WORD attribIndex    = 0x0000;

    /* read mandatory parameters                                             */
    cause           = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        subCause      = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
        loc_MDL_ID    = pPara[pos++];
        serviceHandle = pPara[pos++];
        attribIndex   = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTAttributeWriteConf(//pBTLtp->pMsgBuffer,
                                   //pBTLtp->blueAPIHandle,
                                   loc_MDL_ID,
                                   BTLTPLookupGATTServiceHandle(pBTLtp, serviceHandle),
                                   (TBlueAPI_Cause)cause,
                                   subCause,
                                   attribIndex
                                  );
} /* BTLTPHandleGATTAttributeWriteCnf */

/****************************************************************************
 * BTLTPHandleGATTServerStoreCnf
 ****************************************************************************/
void BTLTPHandleGATTServerStoreCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                   WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    BYTE opCode         = 0x00;
    LPBYTE rem_BD       = NULL;
    BYTE rem_BD_Type    = 0x00;
    WORD restartHandle  = 0x0000;

    /* read mandatory parameters                                             */
    cause           = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        opCode        = pPara[pos++];
        rem_BD        = &pPara[pos];
        pos += 6;
        rem_BD_Type   = pPara[pos++];
        restartHandle = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTServerStoreConf(//pBTLtp->pMsgBuffer,
                                //pBTLtp->blueAPIHandle,
                                (TBlueAPI_GATTStoreOpCode)opCode,
                                rem_BD,
                                (TBlueAPI_RemoteBDType)rem_BD_Type,
                                restartHandle,
                                (lenPara - pos),
                                (pPara + pos),
                                (TBlueAPI_Cause)cause
                               );
} /* BTLTPHandleGATTServerStoreCnf */

/****************************************************************************
 * BTLTPHandleConnectGATTMDLReq
 ****************************************************************************/
void BTLTPHandleConnectGATTMDLReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                  WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    LPBYTE rem_BD;
    BYTE rem_BD_Type;
    BYTE loc_MDEP_ID;
    WORD scanInterval;
    WORD scanWindow;
    WORD scanTimeout;
    WORD connIntervalMin;
    WORD connIntervalMax;
    WORD connLatency;
    WORD supervisionTimeout;

    /* read mandatory parameters                                             */
    rem_BD              = &pPara[pos];
    pos += 6;
    rem_BD_Type         = pPara[pos++];
    loc_MDEP_ID         = pPara[pos++];
    scanInterval        = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    scanWindow          = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    scanTimeout         = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    connIntervalMin     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    connIntervalMax     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    connLatency         = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    supervisionTimeout  = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    /* read optional parameters                                              */
    /* none */

    /* Allocate Context for this loc_MDEP_ID */
    BTLTPAllocateMDLContext(pBTLtp, 0x00, loc_MDEP_ID);

    blueAPI_ConnectGATTMDLReq(//pBTLtp->pMsgBuffer,
                              rem_BD,
                              (TBlueAPI_RemoteBDType)rem_BD_Type,
                              blueAPI_LocalBDTypeLEPublic,
                              //loc_MDEP_ID,  /* tifnan: fot upper stack changes */
                              scanInterval,
                              scanWindow,
                              scanTimeout,
                              connIntervalMin,
                              connIntervalMax,
                              connLatency,
                              supervisionTimeout,
                              2*connIntervalMin - 2
                             );
} /* BTLTPHandleConnectGATTMDLReq */


/****************************************************************************
 * BTLTPHandleGATTDiscoveryReq
 ****************************************************************************/
void BTLTPHandleGATTDiscoveryReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                 WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE loc_MDL_ID;
    BYTE discoveryType;
    WORD startHandle;
    WORD endHandle;
    WORD uuid16 = 0;
    LPBYTE pUUID128 = NULL;

    /* read mandatory parameters                                             */
    loc_MDL_ID    = pPara[pos++];
    discoveryType = pPara[pos++];
    startHandle   = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    endHandle     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    if (lenPara == (pos + 2))
    {
        uuid16      = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }
    else
    {
        pUUID128    = &pPara[pos];
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTDiscoveryReq(//pBTLtp->pMsgBuffer,
                             //pBTLtp->blueAPIHandle,
                             loc_MDL_ID,
                             (TBlueAPI_GATTDiscoveryType)discoveryType,
                             startHandle,
                             endHandle,
                             uuid16,
                             pUUID128
                            );
} /* BTLTPHandleGATTDiscoveryReq */


/****************************************************************************
 * BTLTPHandleGATTDiscoveryCnf
 ****************************************************************************/
void BTLTPHandleGATTDiscoveryCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                 WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    BYTE loc_MDL_ID     = 0x00;
    BYTE discoveryType  = 0x00;
    WORD startHandle    = 0x0000;
    WORD endHandle      = 0x0000;

    /* read mandatory parameters                                             */
    cause           = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        loc_MDL_ID    = pPara[pos++];
        discoveryType = pPara[pos++];
        startHandle   = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
        endHandle     = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTDiscoveryConf(//pBTLtp->pMsgBuffer,
                              //pBTLtp->blueAPIHandle,
                              loc_MDL_ID,
                              (TBlueAPI_GATTDiscoveryType)discoveryType,
                              startHandle,
                              endHandle
                             );
} /* BTLTPHandleGATTDiscoveryCnf */


/****************************************************************************
 * BTLTPHandleGATTAttributeReadReq
 ****************************************************************************/
void BTLTPHandleGATTAttributeReadReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                     WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE loc_MDL_ID;
    BYTE readType;
    WORD readOffset;
    WORD startHandle;
    WORD endHandle;
    WORD uuid16 = 0;
    LPBYTE pUUID128 = NULL;

    /* read mandatory parameters                                             */
    loc_MDL_ID  = pPara[pos++];
    readType    = pPara[pos++];
    readOffset  = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    startHandle = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    endHandle   = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    if (lenPara == (pos + 2))
    {
        uuid16    = NETCHAR2SHORT(&pPara[pos]);
        pos += 2;
    }
    else
    {
        pUUID128  = &pPara[pos];
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTAttributeReadReq(//pBTLtp->pMsgBuffer,
                                 //pBTLtp->blueAPIHandle,
                                 loc_MDL_ID,
                                 (TBlueAPI_GATTReadType)readType,
                                 readOffset,
                                 startHandle,
                                 endHandle,
                                 uuid16,
                                 pUUID128
                                );
} /* BTLTPHandleGATTAttributeReadReq */


/****************************************************************************
 * BTLTPHandleGATTAttributeWriteReq
 ****************************************************************************/
BOOL BTLTPHandleGATTAttributeWriteReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE loc_MDL_ID;
    BYTE writeType;
    WORD attribHandle;
    //WORD writeOffset;
    
    PBTLtpMDLContext pMDLContext = NULL;
    uint16_t wOffset = 0;
    void* pBuffer = NULL;
	uint16_t ds_pool_id = 0;

    /* read mandatory parameters                                             */
    loc_MDL_ID    = pPara[pos++];
    writeType     = pPara[pos++];
    attribHandle  = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    //writeOffset   = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    /*DBG_DIRECT("DML = %x, handle = %x, writetype = %x, writeOffset = %x, wOffset = %x, data = %x, lenPara = %x, pos = %x",\
		loc_MDL_ID, attribHandle, writeType, writeOffset, wOffset, pPara[pos], lenPara, pos);*/

    /* read optional parameters */
    pMDLContext = BTLTPFindMDLContext(pBTLtp, loc_MDL_ID); 
	//DBG_DIRECT("pMDLContext = %x", pMDLContext);
	
	
    if(NULL != pMDLContext)
   	{
   		wOffset = pMDLContext->dsDataOffset + 3;
		ds_pool_id = pMDLContext->dsPoolID;
		//DBG_DIRECT("wOffset = %x, dsPoolID = %x, P_BtLtp->LTP_PoolID = %x", wOffset, ds_pool_id, P_BtLtp->LTP_PoolID);
		
   	}
	
    /* none */
    if(blueAPI_CauseSuccess == blueAPI_BufferGet(ds_pool_id,  lenPara - pos, wOffset, (void**)&pBuffer))
    {
    	memcpy(((uint8_t *)pBuffer) + wOffset, pPara + pos, lenPara - pos);
    	if(!blueAPI_GATTAttributeWriteReq(pBuffer,
                                  //pBTLtp->blueAPIHandle,
                                  loc_MDL_ID,
                                  (TBlueAPI_GATTWriteType)writeType,
                                  attribHandle,
                                  (lenPara - pos),
                                  //writeOffset
                                  wOffset
                                 ))
        {
        	blueAPI_BufferRelease(pBuffer);
        }
    }
    else
    {
    	//DBG_DIRECT("blueAPI_BufferGet failed!");
    	 DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "blueAPI_BufferGet failed!", 0);
    }
   
    return FALSE;
} /* BTLTPHandleGATTAttributeWriteReq */


/****************************************************************************
 * BTLTPHandleGATTAttributeCnf
 ****************************************************************************/
void BTLTPHandleGATTAttributeCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                 WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    BYTE loc_MDL_ID = 0x00;

    /* read mandatory parameters                                             */
    cause         = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        loc_MDL_ID  = pPara[pos++];
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTAttributeConf(//pBTLtp->pMsgBuffer,
                              //pBTLtp->blueAPIHandle,
                              loc_MDL_ID
                             );
} /* BTLTPHandleGATTAttributeCnf */

/****************************************************************************
 * BTLTPHandleGATTSecurityReq
 ****************************************************************************/
void BTLTPHandleGATTSecurityReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE loc_MDL_ID;
    WORD requirements;
    BYTE minKeySize;

    /* read mandatory parameters                                             */
    loc_MDL_ID    = pPara[pos++];
    requirements  = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    minKeySize    = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    blueAPI_GATTSecurityReq(//pBTLtp->pMsgBuffer,
                            //pBTLtp->blueAPIHandle,
                            loc_MDL_ID,
                            requirements,
                            minKeySize
                           );
} /* BTLTPHandleGATTSecurityReq */

/****************************************************************************
 * BTLTPHandleLEAdvertiseReq
 ****************************************************************************/
void BTLTPHandleLEAdvertiseReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                               WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE advMode;
    LPBYTE rem_BD;
    BYTE rem_BD_Type;

    /* read mandatory parameters                                             */
    advMode     = pPara[pos++];
    rem_BD      = &pPara[pos];
    pos += 6;
    rem_BD_Type = pPara[pos++];

    /* read optional parameters                                              */
    /* none */
    if(advMode == 2)
    {
        blueAPI_LEAdvertiseParameterSetReq(blueAPI_LEAdvTypeDirectedHighDuty,
        								   (TBlueAPI_LEFilterPolicy)0, 
        								   (TBlueAPI_LEFilterPolicy)0,
			                               0,
			                               0,
			                               blueAPI_LocalBDTypeLEPublic,
			                               rem_BD,
                                           (TBlueAPI_RemoteBDType)rem_BD_Type);
    	blueAPI_LEAdvertiseReq(
                           (TBlueAPI_LEAdvMode)advMode
                          );
	}
	else
	{
		blueAPI_LEAdvertiseReq(
                           (TBlueAPI_LEAdvMode)advMode
                          );
	}
} /* BTLTPHandleLEAdvertiseReq */


/****************************************************************************
 * BTLTPHandleLEAdvertiseParameterSetReq
 ****************************************************************************/
void BTLTPHandleLEAdvertiseParameterSetReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
        WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE advType;
    BYTE filterScanReq;
    BYTE filterConnectReq;
    WORD minAdvInterval;
    WORD maxAdvInterval;

    /* read mandatory parameters                                             */
    advType           = pPara[pos++];
    filterScanReq     = pPara[pos++];
    filterConnectReq  = pPara[pos++];
    minAdvInterval    = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    maxAdvInterval    = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    /* read optional parameters                                              */
    /* none */

    blueAPI_LEAdvertiseParameterSetReq(//pBTLtp->pMsgBuffer,
                                       //pBTLtp->blueAPIHandle,
                                       (TBlueAPI_LEAdvType)advType,
                                       (TBlueAPI_LEFilterPolicy)filterScanReq,
                                       (TBlueAPI_LEFilterPolicy)filterConnectReq,
                                       minAdvInterval,
                                       maxAdvInterval,
                                       blueAPI_LocalBDTypeLEPublic,
                                       NULL,
                                       blueAPI_RemoteBDTypeLEPublic
                                      );
} /* BTLTPHandleLEAdvertiseParameterSetReq */


/****************************************************************************
 * BTLTPHandleLEAdvertiseDataSetReq
 ****************************************************************************/
void BTLTPHandleLEAdvertiseDataSetReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE dataType = 0;

    /* read mandatory parameters                                             */
    dataType = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    //*********************************************************//
    /*uint8_t i = 0;
    DBG_DIRECT("scan response data len = %d", lenPara);
    if( blueAPI_LEDataTypeScanResponseData == dataType)
    {
      for(i = 0; i < lenPara; i++)
      {
          DBG_DIRECT("scan response data[%d] = 0x%x", i, *pPara++);
      }
    }*/

    blueAPI_LEAdvertiseDataSetReq(//pBTLtp->pMsgBuffer,
                                  //pBTLtp->blueAPIHandle,
                                  (TBlueAPI_LEDataType)dataType,
                                  (lenPara - pos),
                                  (pPara + pos)
                                 );

} /* BTLTPHandleLEAdvertiseDataSetReq */


/****************************************************************************
 * BTLTPHandleLEScanReq
 ****************************************************************************/
void BTLTPHandleLEScanReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                          WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE scanMode;
    WORD scanInterval;
    WORD scanWindow;
    BYTE filterPolicy;
    BYTE filterDuplicates;

    /* read mandatory parameters                                             */
    scanMode          = pPara[pos++];
    scanInterval      = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    scanWindow        = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    filterPolicy      = pPara[pos++];
    filterDuplicates  = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    blueAPI_LEScanReq(//pBTLtp->pMsgBuffer,
                      //pBTLtp->blueAPIHandle,
                      (TBlueAPI_LEScanMode)scanMode,
                      scanInterval,
                      scanWindow,
                      (TBlueAPI_LEFilterPolicy)filterPolicy,
                      blueAPI_LocalBDTypeLEPublic,
                      filterDuplicates
                     );
} /* BTLTPHandleLEScanReq */


/****************************************************************************
 * BTLTPHandleLEModifyWhitelistReq
 ****************************************************************************/
void BTLTPHandleLEModifyWhitelistReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                     WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE whitelistOp;
    LPBYTE rem_BD;
    BYTE rem_BD_Type;

    /* read mandatory parameters                                             */
    whitelistOp = pPara[pos++];
    rem_BD      = &pPara[pos];
    pos += 6;
    rem_BD_Type = pPara[pos++];

    /* read optional parameters                                              */
    /* none */

    blueAPI_LEModifyWhitelistReq(//pBTLtp->pMsgBuffer,
                                 //pBTLtp->blueAPIHandle,
                                 (TBlueAPI_LEWhitelistOp)whitelistOp,
                                 rem_BD,
                                 (TBlueAPI_RemoteBDType)rem_BD_Type
                                );
} /* BTLTPHandleLEModifyWhitelistReq */


/****************************************************************************
 * BTLTPHandleLEConnectionUpdateReq
 ****************************************************************************/
void BTLTPHandleLEConnectionUpdateReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE loc_MDL_ID;
    WORD connIntervalMin;
    WORD connIntervalMax;
    WORD connLatency;
    WORD supervisionTimeout;

    /* read mandatory parameters                                             */
    loc_MDL_ID          = pPara[pos++];
    connIntervalMin     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    connIntervalMax     = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    connLatency         = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;
    supervisionTimeout  = NETCHAR2SHORT(&pPara[pos]);
    pos += 2;

    /* read optional parameters                                              */
    /* none */

    blueAPI_LEConnectionUpdateReq(//pBTLtp->pMsgBuffer,
                                  // pBTLtp->blueAPIHandle,
                                  loc_MDL_ID,
                                  connIntervalMin,
                                  connIntervalMax,
                                  connLatency,
                                  supervisionTimeout
                                 );
} /* BTLTPHandleLEConnectionUpdateReq */


/****************************************************************************
 * BTLTPHandleLEConnectionUpdateCnf
 ****************************************************************************/
void BTLTPHandleLEConnectionUpdateCnf(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                      WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE cause;
    BYTE loc_MDL_ID = 0x00;

    /* read mandatory parameters                                             */
    cause         = pPara[pos++];
    if (cause != LTP_CAUSE_NOT_SUPPORTED)
    {
        loc_MDL_ID  = pPara[pos++];
    }

    /* read optional parameters                                              */
    /* none */

    blueAPI_LEConnectionUpdateConf(//pBTLtp->pMsgBuffer,
                                   //pBTLtp->blueAPIHandle,
                                   loc_MDL_ID,
                                   (TBlueAPI_Cause)cause
                                  );
} /* BTLTPHandleLEConnectionUpdateCnf */

#if (F_BT_LE_PRIVACY_MODE)
/****************************************************************************
 * BTLTPHandleLEPrivacyModeReq
 ****************************************************************************/
void BTLTPHandleLEPrivacyModeReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt,
                                 WORD lenPara, LPBYTE pPara)
{
    WORD pos = 0;
    BYTE privacyMode;

    /* read mandatory parameters                                             */
    privacyMode = pPara[pos++];

    blueAPI_LEPrivacyModeReq(pBTLtp->pMsgBuffer,
                             //pBTLtp->blueAPIHandle,
                             (TBlueAPI_LEPrivacyMode)privacyMode
                            );
} /* BTLTPHandleLEPrivacyModeReq */
#endif /* (F_BT_LE_PRIVACY_MODE) */

/* tifnan: 20140918 for gatt auto test */
/****************************************************************************/
/* void BTLTPHandleDeviceNameReq                                            */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/*    BYTE   copmsk                                                         */
/*    LPBYTE pOpt                                                           */
/*    WORD   lenPara                                                        */
/*    LPBYTE pPara                                                          */
/* )                                                                        */
/****************************************************************************/
void BTLTPHandleDeviceNameReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD   pos = 0;
    //LPBYTE rem_BD;


    /* read mandatory parameters                                             */
    //rem_BD = &pPara[pos];
    pos += 6;

    /* read optional parameters                                              */
    /* non */
    uint8_t *dev_name = (uint8_t*)"RT_Bee";
    blueAPI_DeviceConfigDeviceNameSetReq( dev_name);
}

/****************************************************************************/
/* void BTLTPHandleDeviceConfigSecuritySetReq                               */
/****************************************************************************/
void BTLTPHandleDeviceConfigSecuritySetReq(PBTLtp pBTLtp, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    WORD                    pos = 0;
    TBlueAPI_StoreBondModes storeBondMode;
    BYTE                    storeBondSize;
    //DWORD                   leFixedDisplayValue;

    /* read mandatory parameters                                             */
    storeBondMode       = (TBlueAPI_StoreBondModes)pPara[pos++];
    storeBondSize       = pPara[pos++];
    //leFixedDisplayValue = NETCHAR2LONG(&pPara[pos]);
    pos += 4;

	blueAPI_DeviceConfigStoreSetReq(storeBondMode, storeBondSize);
}

