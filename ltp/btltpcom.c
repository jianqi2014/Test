enum { __FILE_NUM__= 0 };

/**********************************************************************!KA****
 *
 * $Header: /var/lib/cvs/sw/src/bt/app/btltp/btltpcom.c,v 1.74 2014/04/25 13:40:42 ka Exp $
 *
 * File:        $RCSfile: btltpcom.c,v $
 * Version:     $Name: P_SRP0007_U_KA_BLB1290_RC1 $
 *
 * Archive:     $Source: /var/lib/cvs/sw/src/bt/app/btltp/btltpcom.c,v $
 * Revision:    $Revision: 1.74 $
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
 *         COM message interface for LTP Application
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
 * $Log: btltpcom.c,v $
 * Revision 1.74  2014/04/25 13:40:42  ka
 * issue 0012122# Prepare SDK release candidate
 *
 * Revision 1.73  2014/03/28 10:12:22  pm
 * issue #0012269: BlueAPI: implement OBEX LTP interface
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
 * Revision 1.70  2013/09/24 14:18:11  ore
 * issue 0008066
 * BlueAPI: Support for max TX Power needed
 *
 * Revision 1.69  2013/09/24 14:08:54  ore
 * issue 0008067
 * BlueAPI: Support for Absolute RSSI needed
 *
 * Revision 1.68  2013/09/18 09:50:24  ore
 * issue 0008368
 * BlueAPI: Add configuration Interface for sniff mode
 *
 * Revision 1.67  2013/09/18 09:39:59  ore
 * issue 0010994
 * BlueAPI: add API for link policy configuration
 *
 * Revision 1.66  2013/08/28 13:36:17  ore
 * issue 0010851
 * remove btsec includes
 *
 * Revision 1.65  2013/08/28 09:06:38  ore
 * issue 0010843
 * BlueAPI: add pagescan- and linkpolicy configuration
 *
 * Revision 1.64  2013/08/21 13:37:06  ore
 * issue 0010803
 * BlueAPI: split up DeviceConfigSetReq
 *
 * Revision 1.63  2013/07/12 17:36:33  ore
 * issue 0009823
 * LE: add random resolvable address resolution / privacy mode
 *
 * Revision 1.62  2013/07/10 14:26:56  ore
 * issue 0009823
 * LE: add random resolvable address resolution / privacy mode
 *
 * Revision 1.61  2013/07/09 13:49:49  ore
 * issue 0010462
 * cleanup new trace calls
 *
 * Revision 1.60  2013/05/28 13:21:04  ore
 * issue 0009141
 * GATT: extended ATT_WRITE_COMMAND handling
 *
 * Revision 1.59  2013/03/12 10:53:10  ore
 * issue 0004550
 * Check maxTPDUSize / maxLTPSize calculation
 *
 * Revision 1.58  2013/02/27 18:08:55  ore
 * issue 0008926
 * fix VS2005 compiler warnings
 *
 * Revision 1.57  2013/02/26 11:03:21  ore
 * issue 0008354
 * fix ConnectMDLGATTRsp / GATT context handling
 *
 * Revision 1.56  2013/02/03 13:45:09  ore
 * issue 0008217
 * add GATTMtuSizeInfo
 *
 * Revision 1.55  2013/01/31 16:59:45  mj
 * issue #0008354
 * GATT: in some messages BlueAPI parameters have been overwritten,
 * fixed bug: buffer has been be released by L1 and LTP.
 *
 * Revision 1.54  2013/01/09 14:16:43  ore
 * issue 0008354
 * implement LTP BLE/GATT messages
 *
 * Revision 1.53  2012/11/02 14:49:13  ore
 * issue #7962
 * fix buffer handling
 *
 * Revision 1.52  2012/11/01 08:43:56  ore
 * issue #7952
 * move osif / hardware specific code
 *
 * Revision 1.51  2012/10/31 18:25:48  ore
 * issue #7949
 * fix VS2005 compiler warnings
 *
 * Revision 1.50  2012/07/23 15:22:11  ore
 * 0007663: LTP: do not start configurator if no configurator is present
 *
 * Revision 1.49  2012/07/04 09:39:30  ore
 * 0007585: BlueAPI: use C99 uintx_t and bool instead of BYTE, WORD etc.
 *
 * Revision 1.48  2012/05/31 11:58:39  odr
 * issue #0006776 Add DeviceConfiguration to message interface
 * Added DeviceConfigSetRsp and DeviceNameRsp
 *
 * Revision 1.47  2012/03/20 08:20:01  odr
 * Internal Change 7216: API renaming and cleaning
 * Contains changes from API_RENAMED branch
 * Cleaned function comments
 *
 * Revision 1.46.2.3  2012/03/19 14:03:43  odr
 * API renamed: Changed includes to fit new file names
 *
 * Revision 1.46.2.2  2012/03/08 09:37:35  odr
 * renamed blueAPI_Event_ to blueAPI_Event
 *
 * Revision 1.46.2.1  2012/03/06 15:55:51  odr
 * - adapted function calls and enums to new BlueAPI norm
 *
 * Revision 1.46  2012/01/02 15:48:09  ka
 * introduced flag 'BTMED_HDP_SUPPORT' to allow disabeling of HDP profile
 *
 * Revision 1.45  2011/12/09 13:40:10  odr
 * Fix 6828: Empty unsegmented packets returning credits interleave with packets of segmented data transfer
 *
 * Revision 1.44  2011/06/30 11:47:45  ore
 * function rename during ltplib cleanup
 *
 * Revision 1.43  2011/06/07 15:22:23  ore
 * fix 0006259: internalEventInfo message generated on LTP level for by dumped queued Tx data in case of connection lost
 *
 * Revision 1.42  2011/05/11 10:03:35  ore
 * move pMDLContext != NULL check
 *
 * Revision 1.40  2011/03/07 15:12:20  ore
 * cleanup previous commit
 *
 * Revision 1.39  2011/03/04 17:31:11  ka
 * 0005577: function of BTSEC feature request 0005576 shall be made available foe BlueHDP+ and LTP
 *
 * Revision 1.38  2011/02/18 10:19:52  ore
 * 0005857: LTP: remove unused return value from handler functions
 *
 * Revision 1.37  2010/12/30 13:38:31  ore
 * fix 0005580: Interrupted SPP connection in HW FLC mode freezes module
 *
 * Revision 1.36  2010/12/30 13:22:36  ore
 * fix 0005597: LTP pool switching not usable with multiple MDLs
 * - rename context
 *
 * Revision 1.35  2010/10/21 15:24:19  ore
 * fix 0005404: LTP credit context not reused for reconnect
 *
 * Revision 1.34  2010/08/26 13:56:38  ore
 * fix 0005061: LTP: use distinct pool for offline signaling
 *
 * Revision 1.33  2010/08/20 13:17:49  ka
 * implement: 0004990: rename 'HDPDevice' related messages to 'DIDDevice'
 *
 * Revision 1.32  2010/08/19 13:44:19  mj
 * #0004985: Renamed TBTMed_COM_DataReq/Ind.offset -> gap.
 *
 * Revision 1.31  2010/08/17 09:55:20  ore
 * fix 0004951: Remove traceoutput from LTP module
 *
 * Revision 1.30  2010/07/09 16:42:01  ore
 * fix 0004696: HDP+ offset definition in data exchange messages is misleading
 *
 * Revision 1.29  2010/07/09 16:19:36  ore
 * fix 0004411: [LTP]Ensure DataConf delivery
 *
 * Revision 1.28  2010/06/30 16:27:14  ore
 * fixes 0004413: [LTP]Do not reuse HDP_Ind buffers for LTP_Info messages
 * - add cause parameter to service discovery Confs
 *
 * Revision 1.27  2010/05/14 15:01:11  ka
 * - added ACL status info signalling for HDP and LTP
 * - added ACL and MDL status info filter compile flags
 *
 * Revision 1.26  2010/05/05 12:08:53  ka
 * - fixed asyncronus ResetReq with CRC
 * - fixed missing actInfo after configurator exit
 *
 * Revision 1.25  2010/04/28 13:23:13  ore
 * - add creditbased flowcontrol
 * - fix ConnectMDLInfo and ReconnectMDLReq
 * - remove tempBuffer
 *
 * Revision 1.24  2010/04/20 13:26:29  ore
 * add opt. parameters for Inquiry- and ServiceDiscovery messages
 *
 * Revision 1.23  2010/04/19 13:49:01  ore
 * - add LinkKey to AuthResultInd
 * - add InternalEventInfo message
 *
 * Revision 1.22  2010/04/15 16:06:09  ka
 * - bugfix for CRC check with additional optional parameters
 * - added max rx-msg as optional to actInfo msg
 *
 * Revision 1.21  2010/04/15 13:55:18  ore
 * add keytype to AuthResultInd and AuthListInfo Msg
 *
 * Revision 1.20  2010/04/15 12:45:09  ka
 * updated LTP module (add CRC, msg check)
 *
 * Revision 1.19  2010/03/29 09:59:53  ore
 * add local_BD to ActInfo
 *
 * Revision 1.18  2010/03/26 12:38:51  ore
 * - add BD to PasskeyNotificationInfo
 * - add BD to KeypressNotificationInfo
 * - add DisplayValue to UserConfRequestInd
 * - add cause/BD to UserConfRequestCnf
 *
 * Revision 1.17  2010/03/23 18:24:36  ka
 * interim version for LTP1.3 bootstrap (introduced auth result handling)
 *
 * Revision 1.16  2010/03/23 16:19:11  ore
 * fix BufferCallback Action for DataInd
 *
 * Revision 1.15  2010/03/22 15:25:52  ka
 * interim version for LTP1.3 bootstrap (add SetRadioMode handling)
 *
 * Revision 1.14  2010/03/22 15:21:16  ore
 * add missing SPPMDEPRsp
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
 * Revision 1.10  2010/03/16 17:57:31  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.9  2009/07/15 08:39:07  ka
 * addopted new COM features
 *
 * Revision 1.8  2008/10/24 14:38:08  ka
 * - introduced authentication via LTP
 * - removed VMOD
 * - introduced Multilink/Multimdl support
 * - bugfix for SDP and eL2CAP
 * - several other bugfixes
 *
 * Revision 1.7  2008/08/20 13:34:01  ka
 * - introduced LTP-Library
 * - bugfix for data-resp missing
 *
 * Revision 1.6  2008/08/13 11:07:07  ka
 * remocet btltpcmd dependencies
 *
 * Revision 1.5  2008/08/13 11:03:02  ka
 * added reconnect support
 *
 * Revision 1.4  2008/07/24 15:19:57  ka
 * - bugfix for createMDLInd->loc_MDEP_ID
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

#include <blueapi_types.h>
#include <blueapi.h>
#include "btltp.h"
#include <ltplib.h>
#include "patch_application.h"
#include <trace_binary.h>


#define LTP_SOURCE_FILE_ID 0x81

/****************************************************************************/
/* void LTPHandle_CreateMDLInd                                              */
/* (                                                                        */
/*    PBTLtp                  pBTLtp                                        */
/*    PBlueAPI_CreateMDLInd pCOM_CreateMDLInd                               */
/* )                                                                        */
/****************************************************************************/
void LTPHandle_CreateMDLInd(PBTLtp pBTLtp, PBlueAPI_CreateMDLInd pCOM_CreateMDLInd)
{
    BYTE pOpt[4];
    pOpt[0] = 4;     //blueAPI_LinkConfigGATT;   /* tifnan: for upper stack changes */
    pOpt[1] = 0x01;  //pCOM_CreateMDLInd->local_MDEP_ID;  /* tifnan: for upper stack changes */
    pOpt[2] = 0;  //pCOM_CreateMDLInd->remote_MDEP_ID;  /* tifnan: for upper stack changes */
    pOpt[3] = pCOM_CreateMDLInd->remote_BD_type;

    /* Allocate Context for this MDL */
    BTLTPAllocateMDLContext(pBTLtp,
                            (BYTE)pCOM_CreateMDLInd->local_MDL_ID,
                            //pCOM_CreateMDLInd->local_MDEP_ID
                            0x01                            /* tifnan: for upper stack changes  */
                            //blueAPI_LinkConfigGATT  deleted /* tifnan: for upper stack changes  */
                           );

    LTPLibSendCreateMDLInd(&pBTLtp->LTPLib,
                           (BTLTP_DEFAULT_COPMSK |
                            LTP_CREATE_MDL_IND_OPT_MASK_LINK_TYPE |
                            LTP_CREATE_MDL_IND_OPT_MASK_LOC_MDEP_ID |
                            LTP_CREATE_MDL_IND_OPT_MASK_REM_MDEP_ID |
                            LTP_CREATE_MDL_IND_OPT_MASK_BD_TYPE
                           ),
                           pOpt,
                           pCOM_CreateMDLInd->remote_BD,
                           (BYTE)pCOM_CreateMDLInd->local_MDL_ID
                          );
}

/****************************************************************************/
/* void LTPHandle_ConnectMDLInfo                                            */
/* (                                                                        */
/*    PBTLtp                    pBTLtp                                      */
/*    PBlueAPI_ConnectMDLInfo pCOM_ConnectMDLInfo                           */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_ConnectMDLInfo(PBTLtp pBTLtp, PBlueAPI_ConnectMDLInfo pCOM_ConnectMDLInfo)
{
    BYTE              pOpt[3];
    PBTLtpMDLContext  pMDLContext;

    if (pBTLtp->LTP_PoolID != pCOM_ConnectMDLInfo->dsPoolID)
    {
        BLUEAPI_TRACE_PRINTF_2(BLUEAPI_TRACE_MASK_TRACE,
                               "LTP: ConnectMDLInfo MDL[%d] switch COM pool to [0x%X]",
                               pCOM_ConnectMDLInfo->local_MDL_ID,
                               pCOM_ConnectMDLInfo->dsPoolID
                              );

        pBTLtp->LTP_PoolID = pCOM_ConnectMDLInfo->dsPoolID;

    }

    /* check signalling for consistancy with owh configuration */
    if (pCOM_ConnectMDLInfo->dsDataOffset > BTLTP_US_BUFFER_OFFSET + LTP_DATA_MIN_HEADER_LENGTH)
    {
        BLUEAPI_TRACE_PRINTF_2(BLUEAPI_TRACE_MASK_TRACE,
                               "!!LTP: ConnectMDLInfo data offset not supported (%d>%d)",
                               pCOM_ConnectMDLInfo->dsDataOffset,
                               BTLTP_US_BUFFER_OFFSET + LTP_DATA_MIN_HEADER_LENGTH
                              );

        LTPLibSendInternalEventInfo(&pBTLtp->LTPLib, 0, NULL, LTP_CAUSE_RESOURCE_ERROR, LTP_INTERNAL_EVENT_INVALID_DATA_RECEIVED, LTP_GENERATE_EVENT_ID);
    }

    if (pCOM_ConnectMDLInfo->maxTPDUSize  > BTLTP_US_BUFFER_SIZE)
    {
        BLUEAPI_TRACE_PRINTF_2(BLUEAPI_TRACE_MASK_TRACE,
                               "!!LTP: ConnectMDLInfo TPDU size not supported (%d>%d)",
                               pCOM_ConnectMDLInfo->maxTPDUSize,
                               BTLTP_US_BUFFER_SIZE
                              );

        LTPLibSendInternalEventInfo(&pBTLtp->LTPLib, 0, NULL, LTP_CAUSE_RESOURCE_ERROR, LTP_INTERNAL_EVENT_INVALID_DATA_RECEIVED, LTP_GENERATE_EVENT_ID);
    }

    /* Update Context for this MDL */
    pMDLContext = BTLTPFindMDLContext(pBTLtp, (BYTE)pCOM_ConnectMDLInfo->local_MDL_ID);
    if (pMDLContext != NULL)
    {
        pMDLContext->flags             |= LTP_MDL_CONNECTED;
        //  pMDLContext->maxUsCredits       = pCOM_ConnectMDLInfo->maxTPDUusCredits; /* tifnan: for upper  stack changes */
        pMDLContext->collectedUsCredits = 0;
        pMDLContext->pendingDataConfs   = 0;
        pMDLContext->dsDataOffset = pCOM_ConnectMDLInfo->dsDataOffset;
		pMDLContext->dsPoolID = pCOM_ConnectMDLInfo->dsPoolID;
    }

    pOpt[0] = 4; //blueAPI_LinkConfigGATT;       /* tifnan: for upper stack changes */
    //pOpt[1] = pCOM_ConnectMDLInfo->maxTPDUusCredits;
    pOpt[1] = 27;     /* tifnan: for upper  stack changes */
    pOpt[2] = pCOM_ConnectMDLInfo->maxTPDUdsCredits;

    LTPLibSendConnectMDLInfo(&pBTLtp->LTPLib,
                             BTLTP_DEFAULT_COPMSK |
                             LTP_CONNECT_MDL_INFO_OPT_MASK_LINK_TYPE |
                             LTP_CONNECT_MDL_INFO_OPT_MASK_MAX_TPDU_US_CREDITS |
                             LTP_CONNECT_MDL_INFO_OPT_MASK_MAX_TPDU_DS_CREDITS,
                             pOpt,
                             (BYTE)pCOM_ConnectMDLInfo->local_MDL_ID,
                             pCOM_ConnectMDLInfo->maxTPDUSize + LTP_DATA_MIN_HEADER_LENGTH,
                             //31, /* tifnan: for upper  stack changes */
                             //pCOM_ConnectMDLInfo->maxAPDUSize
                             pCOM_ConnectMDLInfo->maxTPDUdsCredits
                             //23  /* tifnan: for upper  stack changes */
                            );
}

/****************************************************************************/
/* void LTPHandle_DisconnectMDLInd                                          */
/* (                                                                        */
/*    PBTLtp                      pBTLtp                                    */
/*    PBlueAPI_DisconnectMDLInd pCOM_DisconnectMDLInd                       */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_DisconnectMDLInd(PBTLtp pBTLtp, PBlueAPI_DisconnectMDLInd pCOM_DisconnectMDLInd)
{
    PBTLtpMDLContext pMDLContext;

    /* Update Context for this MDL */
    pMDLContext = BTLTPFindMDLContext(pBTLtp, (BYTE)pCOM_DisconnectMDLInd->local_MDL_ID);
    if (pMDLContext != NULL)
    {
        pMDLContext->flags &= ~(LTP_MDL_CONNECTED);
    }

    if (BTLTPCountMDLConnected(pBTLtp) == 0)
    {
        BLUEAPI_TRACE_PRINTF_2(BLUEAPI_TRACE_MASK_TRACE,
                               "LTP: DisconnectMDL MDL[%d] switch COM pool to [0x%X]",
                               pCOM_DisconnectMDLInd->local_MDL_ID,
                               pBTLtp->LTP_US_OfflinePoolID
                              );

        pBTLtp->LTP_PoolID = pBTLtp->LTP_US_OfflinePoolID;
    }

    LTPLibSendDisconnectMDLInd(&pBTLtp->LTPLib,
                               BTLTP_DEFAULT_COPMSK,
                               NULL,
                               BTLTPConvertCOMtoLTPcause(pCOM_DisconnectMDLInd->cause),
                               (BYTE)pCOM_DisconnectMDLInd->local_MDL_ID
                              );
}

/****************************************************************************/
/* void LTPHandle_ConnectMDLRsp                                             */
/* (                                                                        */
/*    PBTLtp                   pBTLtp                                       */
/*    PBlueAPI_ConnectMDLRsp pCOM_ConnectMDLRsp                             */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_ConnectMDLRsp(PBTLtp pBTLtp, PBlueAPI_ConnectMDLRsp pCOM_ConnectMDLRsp)
{
    PBTLtpMDLContext pContext;

    if (pCOM_ConnectMDLRsp->local_MDL_ID != 0x00)
    {
        pContext = BTLTPFindMDLContext(pBTLtp, (BYTE)pCOM_ConnectMDLRsp->local_MDL_ID);
    }
    else
    {
        //pContext = BTLTPFindMDLContextByMDEPID(pBTLtp, pCOM_ConnectMDLRsp->local_MDEP_ID);
        pContext = BTLTPFindMDLContextByMDEPID(pBTLtp, 0x01);    /* tifnan: for upper stack changes */
    }

    if ((pContext != NULL) && (pContext->flags & LTP_MDL_GATT))
    {
        LTPLibSendConnectGATTMDLRsp(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    BTLTPConvertCOMtoLTPcause(pCOM_ConnectMDLRsp->cause),
                                    pCOM_ConnectMDLRsp->remote_BD,
                                    pCOM_ConnectMDLRsp->remote_BD_type,
                                    (BYTE)pCOM_ConnectMDLRsp->local_MDL_ID,
                                    //pCOM_ConnectMDLRsp->local_MDEP_ID
                                    0x01   /* for upper stack changes */
                                   );

        /* context was allocated in ConnectMDLReq and no CreateMDLInd was sent
         * -> no DeleteMDLInfo -> free context now */
        if (pCOM_ConnectMDLRsp->local_MDL_ID == 0x00)
        {
            pContext->flags = LTP_MDL_UNUSED;
        }
    }
    else
    {
        BYTE pOpt[2];

        pOpt[0] = (BYTE)pCOM_ConnectMDLRsp->local_MDL_ID;
        pOpt[1] = 0x01; //pCOM_ConnectMDLRsp->local_MDEP_ID;  /* tifnan:for upper stack changes */

        LTPLibSendConnectMDLRsp(&pBTLtp->LTPLib,
                                BTLTP_DEFAULT_COPMSK |                    \
                                LTP_CONNECT_MDL_RSP_OPT_MASK_LOC_MDL_ID | \
                                LTP_CONNECT_MDL_RSP_OPT_MASK_LOC_MDEP_ID,
                                pOpt,
                                BTLTPConvertCOMtoLTPcause(pCOM_ConnectMDLRsp->cause),
                                pCOM_ConnectMDLRsp->remote_BD,
                                //(BYTE)pCOM_ConnectMDLRsp->remote_MDEP_ID
                                55   /* tifnan:for upper stack changes */
                               );
    }
}

/****************************************************************************/
/* void LTPHandle_DisconnectMDLRsp                                          */
/* (                                                                        */
/*    PBTLtp                      pBTLtp                                    */
/*    PBlueAPI_DisconnectMDLRsp pCOM_DisconnectMDLRsp                       */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_DisconnectMDLRsp(PBTLtp pBTLtp, PBlueAPI_DisconnectMDLRsp pCOM_DisconnectMDLRsp)
{
    LTPLibSendDisconnectMDLRsp(&pBTLtp->LTPLib,
                               BTLTP_DEFAULT_COPMSK,
                               NULL,
                               BTLTPConvertCOMtoLTPcause(pCOM_DisconnectMDLRsp->cause),
                               (BYTE)pCOM_DisconnectMDLRsp->local_MDL_ID
                              );
}

/****************************************************************************/
/* void LTPHandle_DeleteMDLInfo                                             */
/* (                                                                        */
/*    PBTLtp                   pBTLtp                                       */
/*    PBlueAPI_DeleteMDLInfo pCOM_DeleteMDLInfo                             */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_DeleteMDLInfo(PBTLtp pBTLtp, PBlueAPI_DeleteMDLInfo pCOM_DeleteMDLInfo)
{
    PBTLtpMDLContext pMDLContext;

    /* remove Credit Context for this MDL */
    pMDLContext = BTLTPFindMDLContext(pBTLtp, (BYTE)pCOM_DeleteMDLInfo->local_MDL_ID);
    if (pMDLContext != NULL)
    {
        pMDLContext->flags = LTP_MDL_UNUSED;
    }

    LTPLibSendDeleteMDLInfo(&pBTLtp->LTPLib,
                            BTLTP_DEFAULT_COPMSK,
                            NULL,
                            (BYTE)pCOM_DeleteMDLInfo->local_MDL_ID
                           );
}

/****************************************************************************/
/* void LTPHandle_AuthResultRequestInd                                      */
/* (                                                                        */
/*    PBTLtp                          pBTLtp                                */
/*    PBlueAPI_AuthResultRequestInd pCOM_AuthResultRequestInd               */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_AuthResultRequestInd(PBTLtp pBTLtp, PBlueAPI_AuthResultRequestInd pCOM_AuthResultRequestInd)
{
    if (pCOM_AuthResultRequestInd->remote_BD_Type != blueAPI_RemoteBDTypeClassic)
    {
        BYTE pOpt[2];
        BYTE pos = 0;

        NETSHORT2CHAR(&pOpt[pos], pCOM_AuthResultRequestInd->restartHandle);
        pos += 2;

        LTPLibSendAuthResultRequestExtInd(&pBTLtp->LTPLib,
                                          (BTLTP_DEFAULT_COPMSK |
                                           LTP_AUTH_RESULT_REQUEST_EXT_IND_OPT_MASK_RESTART_HANDLE
                                          ),
                                          pOpt,
                                          pCOM_AuthResultRequestInd->remote_BD,
                                          pCOM_AuthResultRequestInd->remote_BD_Type,
                                          pCOM_AuthResultRequestInd->keyType
                                         );
    }
    else
    {
        LTPLibSendAuthResultRequestInd(&pBTLtp->LTPLib,
                                       BTLTP_DEFAULT_COPMSK,
                                       NULL,
                                       pCOM_AuthResultRequestInd->remote_BD
                                      );
    }
}

/****************************************************************************/
/* void LTPHandle_RegisterRsp                                               */
/* (                                                                        */
/*    PBTLtp                 pBTLtp                                         */
/*    PBlueAPI_RegisterRsp pCOM_RegisterRsp                                 */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_RegisterRsp(PBTLtp pBTLtp, PBlueAPI_RegisterRsp pCOM_RegisterRsp)
{
    if (pCOM_RegisterRsp->cause == blueAPI_CauseSuccess)
    {
        //pBTLtp->blueAPIHandle = pCOM_RegisterRsp->blueAPIHandle;  /* tifnan */
        BTLTPCheckForActInfo(pBTLtp);
    }
    else
    {
        pBTLtp->blueAPIHandle = NULL;
    }
}

/****************************************************************************/
/* void LTPHandle_PairableModeSetRsp                                        */
/* (                                                                        */
/*    PBTLtp                        pBTLtp                                  */
/*    PBlueAPI_PairableModeSetRsp pCOM_PairableModeSetRsp                   */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_PairableModeSetRsp(PBTLtp pBTLtp, PBlueAPI_PairableModeSetRsp pCOM_PairableModeSetRsp)
{
    LTPLibSendPairableModeSetRsp(&pBTLtp->LTPLib,
                                 BTLTP_DEFAULT_COPMSK,
                                 NULL,
                                 BTLTPConvertCOMtoLTPcause(pCOM_PairableModeSetRsp->cause)
                                );
}

/****************************************************************************/
/* void LTPHandle_UserPasskeyReqInd                                         */
/* (                                                                        */
/*    PBTLtp                       pBTLtp                                   */
/*    PBlueAPI_UserPasskeyReqInd pCOM_UserPasskeyReqInd                     */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_UserPasskeyReqInd(PBTLtp pBTLtp, PBlueAPI_UserPasskeyReqInd pCOM_UserPasskeyReqInd)
{
    LTPLibSendPasskeyRequestInd(&pBTLtp->LTPLib,
                                BTLTP_DEFAULT_COPMSK,
                                NULL,
                                pCOM_UserPasskeyReqInd->remote_BD
                               );
}

/****************************************************************************/
/* void LTPHandle_UserPasskeyReqReplyRsp                                    */
/* (                                                                        */
/*    PBTLtp                            pBTLtp                              */
/*    PBlueAPI_UserPasskeyReqReplyRsp pCOM_UserPasskeyReqReplyRsp           */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_UserPasskeyReqReplyRsp(PBTLtp pBTLtp, PBlueAPI_UserPasskeyReqReplyRsp pCOM_UserPasskeyReqReplyRsp)
{

    LTPLibSendPasskeyReqReplyRsp(&pBTLtp->LTPLib,
                                 BTLTP_DEFAULT_COPMSK,
                                 NULL,
                                 BTLTPConvertCOMtoLTPcause(pCOM_UserPasskeyReqReplyRsp->cause)
                                );
}

/****************************************************************************/
/* void LTPHandle_UserPasskeyNotificationInfo                               */
/* (                                                                        */
/*    PBTLtp                                 pBTLtp                         */
/*    PBlueAPI_UserPasskeyNotificationInfo pCOM_UserPasskeyNotificationInfo */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_UserPasskeyNotificationInfo(PBTLtp pBTLtp, PBlueAPI_UserPasskeyNotificationInfo pCOM_UserPasskeyNotificationInfo)
{
    LTPLibSendPasskeyNotificationInfo(&pBTLtp->LTPLib,
                                      BTLTP_DEFAULT_COPMSK,
                                      NULL,
                                      pCOM_UserPasskeyNotificationInfo->remote_BD,
                                      pCOM_UserPasskeyNotificationInfo->displayValue
                                     );
}

/****************************************************************************/
/* void LTPHandle_RemoteOOBDataReqInd                                       */
/* (                                                                        */
/*    PBTLtp                         pBTLtp                                 */
/*    PBlueAPI_RemoteOOBDataReqInd pCOM_RemoteOOBDataReqInd                 */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_RemoteOOBDataReqInd(PBTLtp pBTLtp, PBlueAPI_RemoteOOBDataReqInd pCOM_RemoteOOBDataReqInd)
{
    LTPLibSendRemoteOOBRequestInd(&pBTLtp->LTPLib,
                                  BTLTP_DEFAULT_COPMSK,
                                  NULL,
                                  pCOM_RemoteOOBDataReqInd->remote_BD
                                 );
}

#if 0
/****************************************************************************/
/* void LTPHandle_LocalOOBDataRsp                                           */
/* (                                                                        */
/*    PBTLtp                     pBTLtp                                     */
/*    PBlueAPI_LocalOOBDataRsp pCOM_LocalOOBDataRsp                         */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_LocalOOBDataRsp(PBTLtp pBTLtp, PBlueAPI_LocalOOBDataRsp pCOM_LocalOOBDataRsp)
{
    LTPLibSendLocalOOBRsp(&pBTLtp->LTPLib,
                          BTLTP_DEFAULT_COPMSK,
                          NULL,
                          BTLTPConvertCOMtoLTPcause(pCOM_LocalOOBDataRsp->cause),
                          pCOM_LocalOOBDataRsp->C,
                          pCOM_LocalOOBDataRsp->R
                         );
}
#endif

/****************************************************************************/
/* void LTPHandle_AuthResultInd                                             */
/* (                                                                        */
/*    PBTLtp                   pBTLtp                                       */
/*    PBlueAPI_AuthResultInd pCOM_AuthResultInd                             */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_AuthResultInd(PBTLtp pBTLtp, PBlueAPI_AuthResultInd pCOM_AuthResultInd)
{
    if (pCOM_AuthResultInd->remote_BD_Type != blueAPI_RemoteBDTypeClassic)
    {
        LTPLibSendAuthResultExtInd(&pBTLtp->LTPLib,
                                   BTLTP_DEFAULT_COPMSK,
                                   NULL,
                                   BTLTPConvertCOMtoLTPcause((TBlueAPI_Cause)pCOM_AuthResultInd->cause),
                                   pCOM_AuthResultInd->remote_BD,
                                   pCOM_AuthResultInd->remote_BD_Type,
                                   pCOM_AuthResultInd->keyType,
                                   pCOM_AuthResultInd->linkKey,
                                   pCOM_AuthResultInd->linkKeyLength
                                  );
    }
    else
    {
        LTPLibSendAuthResultInd(&pBTLtp->LTPLib,
                                BTLTP_DEFAULT_COPMSK,
                                NULL,
                                BTLTPConvertCOMtoLTPcause((TBlueAPI_Cause)pCOM_AuthResultInd->cause),
                                pCOM_AuthResultInd->remote_BD,
                                pCOM_AuthResultInd->linkKey,
                                pCOM_AuthResultInd->keyType
                               );
    }
}

/****************************************************************************/
/* void LTPHandle_ActInfo                                                   */
/* (                                                                        */
/*    PBTLtp             pBTLtp                                             */
/*    PBlueAPI_ActInfo pCOM_ActInfo                                         */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_ActInfo(PBTLtp pBTLtp, PBlueAPI_ActInfo pCOM_ActInfo)
{

    memcpy(pBTLtp->ownBDAddress        , pCOM_ActInfo->local_BD, 6);
    memcpy(pBTLtp->ActInfoVersionString, pCOM_ActInfo->version, BLUE_API_VERSION_LENGTH);

    pBTLtp->ActInfoCause = (BYTE)BTLTPConvertCOMtoLTPcause(pCOM_ActInfo->cause);

    pBTLtp->ActInfoFlags |= LTP_ACT_INFO_FLAG_ACT_INFO;

    BTLTPCheckForActInfo(pBTLtp);
}

/****************************************************************************/
/* void LTPHandle_InternalEventInfo                                         */
/* (                                                                        */
/*    PBTLtp                       pBTLtp                                   */
/*    PBlueAPI_InternalEventInfo pCOM_InternalEventInfo                     */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_InternalEventInfo(PBTLtp pBTLtp, PBlueAPI_InternalEventInfo pCOM_InternalEventInfo)
{
    LTPLibSendInternalEventInfo(&pBTLtp->LTPLib,
                                BTLTP_DEFAULT_COPMSK,
                                NULL,
                                BTLTPConvertCOMtoLTPcause(pCOM_InternalEventInfo->cause),
                                pCOM_InternalEventInfo->eventType,
                                pCOM_InternalEventInfo->eventInfo
                               );
}

/****************************************************************************/
/* void LTPHandle_DeviceConfigSetRsp                                        */
/* (                                                                        */
/*    PBTLtp                        pBTLtp                                  */
/*    PBlueAPI_DeviceConfigSetRsp   pCOM_DeviceConfigSetRsp                 */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_DeviceConfigSetRsp(PBTLtp pBTLtp, PBlueAPI_DeviceConfigSetRsp pCOM_DeviceConfigSetRsp)
{
    switch (pCOM_DeviceConfigSetRsp->opCode)
    {
	case blueAPI_DeviceConfigStore: /*-----------------------------------*/
		LTPLibSendDeviceConfigSecuritySetRsp(&pBTLtp->LTPLib,
												 BTLTP_DEFAULT_COPMSK,
												 NULL,
												 pCOM_DeviceConfigSetRsp->cause
												);


    case blueAPI_DeviceConfigSecurity: /*-----------------------------------*/
        LTPLibSendDeviceConfigSecuritySetRsp(&pBTLtp->LTPLib,
                                             BTLTP_DEFAULT_COPMSK,
                                             NULL,
                                             pCOM_DeviceConfigSetRsp->cause
                                            );
        break;

    case blueAPI_DeviceConfigDeviceName:   /* tifnan: notify!!!!!, just for telling serial tester set successfully */
        LTPLibSendDeviceConfigDeviceSetRsp(&pBTLtp->LTPLib,
                                           BTLTP_DEFAULT_COPMSK,
                                           NULL,
                                           pCOM_DeviceConfigSetRsp->cause
                                          );

        break;

#if (F_BLUE_API_HDP_SUPPORT)
    case blueAPI_DeviceConfigHDP: /*----------------------------------------*/
        LTPLibSendDeviceConfigHDPSetRsp(&pBTLtp->LTPLib,
                                        BTLTP_DEFAULT_COPMSK,
                                        NULL,
                                        pCOM_DeviceConfigSetRsp->cause
                                       );
        break;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

    default: /*-------------------------------------------------------------*/
        break;
    }
}

/****************************************************************************/
/* void LTPHandle_MCLStatusInfo                                             */
/* (                                                                        */
/*    PBTLtp                   pBTLtp                                       */
/*    PBlueAPI_MCLStatusInfo pCOM_MCLStatusInfo                             */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_MCLStatusInfo(PBTLtp pBTLtp, PBlueAPI_MCLStatusInfo pCOM_MCLStatusInfo)
{
    LTPLibSendMCLStatusInfo(&pBTLtp->LTPLib,
                            BTLTP_DEFAULT_COPMSK,
                            NULL,
                            pCOM_MCLStatusInfo->remote_BD,
                            (BYTE)pCOM_MCLStatusInfo->local_MCL_ID,
                            pCOM_MCLStatusInfo->status
                           );
}

/****************************************************************************/
/* void LTPHandle_ACLStatusInfo                                             */
/* (                                                                        */
/*    PBTLtp                   pBTLtp                                       */
/*    PBlueAPI_ACLStatusInfo pCOM_ACLStatusInfo                             */
/* )                                                                        */
/****************************************************************************/
STATIC void LTPHandle_ACLStatusInfo(PBTLtp pBTLtp, PBlueAPI_ACLStatusInfo pCOM_ACLStatusInfo)
{
    BYTE pOpt[3];
    BYTE pos = 0;
    BYTE copmsk = (BTLTP_DEFAULT_COPMSK | LTP_ACL_STATUS_INFO_OPT_MASK_BD_TYPE);

    pOpt[pos++] = pCOM_ACLStatusInfo->remote_BD_type;

    if (0)
    {}
#if (F_LTPLIB_LE_SUPPORT) && (F_LTPLIB_LE_PRIVACY_SUPPORT)
    else if (pCOM_ACLStatusInfo->status == blueAPI_ACLAddressResolved)
    {
        LTPLibSendACLBDResolvedInfo(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    pCOM_ACLStatusInfo->remote_BD,
                                    pCOM_ACLStatusInfo->remote_BD_type,
                                    pCOM_ACLStatusInfo->p.resolve.remote_BD,
                                    pCOM_ACLStatusInfo->p.resolve.remote_BD_type
                                   );
    }
#endif /* (F_LTPLIB_LE_SUPPORT) && (F_LTPLIB_LE_PRIVACY_SUPPORT) */
    else
    {
        switch (pCOM_ACLStatusInfo->status)
        {
        case blueAPI_ACLAuthenticationStarted: /*-------------------------------*/
        case blueAPI_ACLAuthenticationSuccess: /*-------------------------------*/
        case blueAPI_ACLAuthenticationFailure: /*-------------------------------*/
        case blueAPI_ACLConnectionEncrypted: /*---------------------------------*/
        case blueAPI_ACLConnectionNotEncrypted: /*------------------------------*/
            pOpt[pos++] = pCOM_ACLStatusInfo->p.auth.keyType;
            pOpt[pos++] = pCOM_ACLStatusInfo->p.auth.keySize;
            copmsk |= (LTP_ACL_STATUS_INFO_OPT_MASK_KEY_TYPE |
                       LTP_ACL_STATUS_INFO_OPT_MASK_KEY_SIZE);
            break;

        default: /*-------------------------------------------------------------*/
            break;
        }

        LTPLibSendACLStatusInfo(&pBTLtp->LTPLib,
                                copmsk,
                                pOpt,
                                pCOM_ACLStatusInfo->remote_BD,
                                pCOM_ACLStatusInfo->status
                               );
    }
}

/****************************************************************************
 * LTPHandle_GATTServiceRegisterRsp
 ****************************************************************************/
STATIC void LTPHandle_GATTServiceRegisterRsp(PBTLtp pBTLtp, PBlueAPI_GATTServiceRegisterRsp pServiceRegisterRsp)
{
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pServiceRegisterRsp->serviceHandle);

    LTPLibSendGATTServiceRegisterRsp(&pBTLtp->LTPLib,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     pServiceRegisterRsp->cause,
                                     pServiceRegisterRsp->subCause,
                                     serviceHandle
                                    );
} /* LTPHandle_GATTServiceRegisterRsp */


/****************************************************************************
 * LTPHandle_GATTAttributeUpdateRsp
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTAttributeUpdateRsp(PBTLtp pBTLtp, LPBYTE pBuffer,
        PBlueAPI_GATTAttributeUpdateRsp pAttributeUpdateRsp)
{
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pAttributeUpdateRsp->serviceHandle);

    WORD pos    = 0;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTAttributeUpdateRsp.list) + pAttributeUpdateRsp->gap;
    TBlueAPI_GATTAttributeUpdateRsp  attributeUpdateRsp = *pAttributeUpdateRsp;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     pAttributeUpdateRsp->count * (6 + 1),
                                     LTP_GATT_ATTRIBUTE_UPDATE_RSP,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = attributeUpdateRsp.cause;
        NETSHORT2CHAR(&pBuffer[pos], attributeUpdateRsp.subCause);
        pos += 2;
        pBuffer[pos++] = serviceHandle;
        pBuffer[pos++] = (BYTE)(uintptr_t)attributeUpdateRsp.requestHandle;
        NETSHORT2CHAR(&pBuffer[pos], attributeUpdateRsp.attribIndex);
        pos += 2;

        /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTAttributeUpdateRsp */


/****************************************************************************
 * LTPHandle_GATTAttributeUpdateStatusInd
 ****************************************************************************/
STATIC void LTPHandle_GATTAttributeUpdateStatusInd(PBTLtp pBTLtp, PBlueAPI_GATTAttributeUpdateStatusInd pAttributeUpdateStatusInd)
{
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pAttributeUpdateStatusInd->serviceHandle);

    LTPLibSendGATTAttributeUpdateStatusInd(&pBTLtp->LTPLib,
                                           BTLTP_DEFAULT_COPMSK,
                                           NULL,
                                           pAttributeUpdateStatusInd->cause,
                                           pAttributeUpdateStatusInd->subCause,
                                           serviceHandle,
                                           (BYTE)(uintptr_t)pAttributeUpdateStatusInd->requestHandle,
                                           pAttributeUpdateStatusInd->attribIndex,
                                           pAttributeUpdateStatusInd->remote_BD,
                                           pAttributeUpdateStatusInd->remote_BD_Type
                                          );
} /* LTPHandle_GATTAttributeUpdateStatusInd */


/****************************************************************************
 * LTPHandle_GATTAttributeReadInd
 ****************************************************************************/
STATIC void LTPHandle_GATTAttributeReadInd(PBTLtp pBTLtp, PBlueAPI_GATTAttributeReadInd pAttributeReadInd)
{
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pAttributeReadInd->serviceHandle);

    LTPLibSendGATTAttributeReadInd(&pBTLtp->LTPLib,
                                   BTLTP_DEFAULT_COPMSK,
                                   NULL,
                                   (BYTE)pAttributeReadInd->local_MDL_ID,
                                   serviceHandle,
                                   pAttributeReadInd->attribIndex,
                                   pAttributeReadInd->readOffset
                                  );
} /* LTPHandle_GATTAttributeReadInd */


/****************************************************************************
 * LTPHandle_GATTAttributeWriteInd
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTAttributeWriteInd(PBTLtp pBTLtp, LPBYTE pBuffer,
        TBlueAPI_Command command,
        PBlueAPI_GATTAttributeWriteInd pAttributeWriteInd)
{
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pAttributeWriteInd->serviceHandle);

    WORD pos    = 0;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTAttributeWriteInd.data) + pAttributeWriteInd->gap;
    WORD local_MDL_ID = pAttributeWriteInd->local_MDL_ID;
    WORD attribIndex  = pAttributeWriteInd->attribIndex;
    WORD writeOffset  = pAttributeWriteInd->writeOffset;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     pAttributeWriteInd->attribLength,
                                     (command == blueAPI_EventGATTAttributeWriteInd) ? LTP_GATT_ATTRIBUTE_WRITE_IND
                                     : LTP_GATT_ATTRIBUTE_WRITE_COMMAND_INFO,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = (BYTE)local_MDL_ID;
        pBuffer[pos++] = serviceHandle;
        NETSHORT2CHAR(&pBuffer[pos], attribIndex);
        pos += 2;
        NETSHORT2CHAR(&pBuffer[pos], writeOffset);
        pos += 2;

        /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTAttributeWriteInd */


/****************************************************************************
 * LTPHandle_GATTCCCDInfo
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTCCCDInfo(PBTLtp pBTLtp, LPBYTE pBuffer,
                                   PBlueAPI_GATTCCCDInfo pCCCDInfo)
{
    WORD local_MDL_ID  = pCCCDInfo->local_MDL_ID;
    BYTE serviceHandle = BTLTPAllocateFindGATTServiceHandle(pBTLtp, pCCCDInfo->serviceHandle);

    WORD pos    = 0;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTCCCDInfo.data) + pCCCDInfo->gap;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     (pCCCDInfo->count * 4),
                                     LTP_GATT_CCCD_INFO,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = (BYTE)local_MDL_ID;
        pBuffer[pos++] = serviceHandle;

        /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTCCCDInfo */

/****************************************************************************
 * LTPHandle_GATTDiscoveryRsp
 ****************************************************************************/
STATIC void LTPHandle_GATTDiscoveryRsp(PBTLtp pBTLtp, PBlueAPI_GATTDiscoveryRsp pDiscoveryRsp)
{
    LTPLibSendGATTDiscoveryRsp(&pBTLtp->LTPLib,
                               BTLTP_DEFAULT_COPMSK,
                               NULL,
                               pDiscoveryRsp->cause,
                               pDiscoveryRsp->subCause,
                               (BYTE)pDiscoveryRsp->local_MDL_ID,
                               pDiscoveryRsp->discoveryType
                              );
} /* LTPHandle_GATTDiscoveryRsp */


/****************************************************************************
 * LTPHandle_GATTDiscoveryInd
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTDiscoveryInd(PBTLtp pBTLtp, LPBYTE pBuffer,
                                       PBlueAPI_GATTDiscoveryInd pDiscoveryInd)
{
    WORD pos    = 0;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTDiscoveryInd.list) + pDiscoveryInd->gap;
    TBlueAPI_GATTDiscoveryInd discoveryInd = *pDiscoveryInd;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     (pDiscoveryInd->elementCount * pDiscoveryInd->elementLength),
                                     LTP_GATT_DISCOVERY_IND,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );
	 
    if (msgLen > 0)
    {
        pBuffer[pos++] = discoveryInd.cause;
        NETSHORT2CHAR(&pBuffer[pos], discoveryInd.subCause);
        pos += 2;
        pBuffer[pos++] = (BYTE)discoveryInd.local_MDL_ID;
        pBuffer[pos++] = discoveryInd.discoveryType;
        pBuffer[pos++] = (BYTE)discoveryInd.elementLength;

		/* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTDiscoveryInd */


/****************************************************************************
 * LTPHandle_GATTAttributeReadRsp
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTAttributeReadRsp(PBTLtp pBTLtp, LPBYTE pBuffer,
        PBlueAPI_GATTAttributeReadRsp pAttributeReadRsp)
{
    WORD pos    = 0;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTAttributeReadRsp.handlesData) + pAttributeReadRsp->gap;
    TBlueAPI_GATTAttributeReadRsp  attributeReadRsp = *pAttributeReadRsp;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     pAttributeReadRsp->totalLength,
                                     LTP_GATT_ATTRIBUTE_READ_RSP,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = attributeReadRsp.cause;
        NETSHORT2CHAR(&pBuffer[pos], attributeReadRsp.subCause);
        pos += 2;
        pBuffer[pos++] = (BYTE)attributeReadRsp.local_MDL_ID;
        pBuffer[pos++] = attributeReadRsp.readType;
        NETSHORT2CHAR(&pBuffer[pos], attributeReadRsp.readOffset);
        pos += 2;
        NETSHORT2CHAR(&pBuffer[pos], attributeReadRsp.attribLength);
        pos += 2;
        pBuffer[pos++] = (BYTE)attributeReadRsp.nbrOfHandles;

        /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTAttributeReadRsp */


/****************************************************************************
 * LTPHandle_GATTAttributeWriteRsp
 ****************************************************************************/
STATIC void LTPHandle_GATTAttributeWriteRsp(PBTLtp pBTLtp, PBlueAPI_GATTAttributeWriteRsp pAttributeWriteRsp)
{
    LTPLibSendGATTAttributeWriteRsp(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    pAttributeWriteRsp->cause,
                                    pAttributeWriteRsp->subCause,
                                    (BYTE)pAttributeWriteRsp->local_MDL_ID,
                                    pAttributeWriteRsp->writeType
                                   );
} /* LTPHandle_GATTAttributeWriteRsp */


/****************************************************************************
 * LTPHandle_GATTAttributeInd
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTAttributeInd(PBTLtp pBTLtp, LPBYTE pBuffer,
                                       PBlueAPI_GATTAttributeInd pAttributeInd)
{
    WORD pos    = 0;
    WORD local_MDL_ID = pAttributeInd->local_MDL_ID;
    WORD attribHandle = pAttributeInd->attribHandle;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTAttributeInd.data) + pAttributeInd->gap;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     pAttributeInd->attribLength,
                                     LTP_GATT_ATTRIBUTE_IND,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = (BYTE)local_MDL_ID;
        NETSHORT2CHAR(&pBuffer[pos], attribHandle);
        pos += 2;

        /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTAttributeInd */


/****************************************************************************
 * LTPHandle_GATTAttributeNotificationInfo
 ****************************************************************************/
STATIC BOOL LTPHandle_GATTAttributeNotificationInfo(PBTLtp pBTLtp, LPBYTE pBuffer,
        PBlueAPI_GATTAttributeNotificationInfo pAttributeNotificationInfo)
{
    WORD pos    = 0;
    WORD local_MDL_ID = pAttributeNotificationInfo->local_MDL_ID;
    WORD attribHandle = pAttributeNotificationInfo->attribHandle;
    WORD offset = offsetof(TBlueAPI_UsMessage, p.GATTAttributeNotificationInfo.data) + pAttributeNotificationInfo->gap;
    WORD msgLen = LTPLibInsertHeader(&pBTLtp->LTPLib,
                                     pBuffer, &offset,
                                     pAttributeNotificationInfo->attribLength,
                                     LTP_GATT_ATTRIBUTE_NOTIFICATION_INFO,
                                     BTLTP_DEFAULT_COPMSK,
                                     NULL,
                                     &pos
                                    );

    if (msgLen > 0)
    {
        pBuffer[pos++] = (BYTE)local_MDL_ID;
        NETSHORT2CHAR(&pBuffer[pos], attribHandle);
        pos += 2;

       /* memory copy to tx buffer */
		uint8_t* pTxBuffer = BTLTPTgtSendBufferAlloc(pBTLtp->LTPLib.AppHandle, msgLen);
		memcpy(pTxBuffer, pBuffer + offset, msgLen);
        BTLTPTgtSendLTPMessage(pBTLtp, pTxBuffer, 0, msgLen);
        return FALSE;
    }

    return TRUE;
} /* LTPHandle_GATTAttributeNotificationInfo */

/****************************************************************************
 * LTPHandle_GATTSecurityRsp
 ****************************************************************************/
STATIC void LTPHandle_GATTSecurityRsp(PBTLtp pBTLtp, PBlueAPI_GATTSecurityRsp pSecurityRsp)
{
    LTPLibSendGATTSecurityRsp(&pBTLtp->LTPLib,
                              BTLTP_DEFAULT_COPMSK,
                              NULL,
                              pSecurityRsp->cause,
                              (BYTE)pSecurityRsp->local_MDL_ID,
                              pSecurityRsp->keyType,
                              pSecurityRsp->keySize
                             );
} /* LTPHandle_GATTSecurityRsp */

/****************************************************************************
 * LTPHandle_GATTServerStoreInd
 ****************************************************************************/
STATIC void LTPHandle_GATTServerStoreInd(PBTLtp pBTLtp, PBlueAPI_GATTServerStoreInd pServerStoreInd)
{
    LTPLibSendGATTServerStoreInd(&pBTLtp->LTPLib,
                                 BTLTP_DEFAULT_COPMSK,
                                 NULL,
                                 pServerStoreInd->opCode,
                                 pServerStoreInd->remote_BD,
                                 pServerStoreInd->remote_BD_Type,
                                 pServerStoreInd->restartHandle,
                                 pServerStoreInd->data,
                                 pServerStoreInd->dataLength
                                );
} /* LTPHandle_GATTServerStoreInd */

/****************************************************************************
 * LTPHandle_GATTMtuSizeInfo
 ****************************************************************************/
STATIC void LTPHandle_GATTMtuSizeInfo(PBTLtp pBTLtp, PBlueAPI_GATTMtuSizeInfo pMtuSizeInfo)
{
    LTPLibSendGATTMtuSizeInfo(&pBTLtp->LTPLib,
                              BTLTP_DEFAULT_COPMSK,
                              NULL,
                              (BYTE)pMtuSizeInfo->local_MDL_ID,
                              pMtuSizeInfo->mtuSize
                             );
} /* LTPHandle_GATTMtuSizeInfo */

/****************************************************************************
 * LTPHandle_LEAdvertiseRsp
 ****************************************************************************/
STATIC void LTPHandle_LEAdvertiseRsp(PBTLtp pBTLtp, PBlueAPI_LEAdvertiseRsp pAdvertiseRsp)
{
    LTPLibSendLEAdvertiseRsp(&pBTLtp->LTPLib,
                             BTLTP_DEFAULT_COPMSK,
                             NULL,
                             pAdvertiseRsp->cause,
                             pAdvertiseRsp->advMode
                            );
} /* LTPHandle_LEAdvertiseRsp */


/****************************************************************************
 * LTPHandle_LEAdvertiseParameterSetRsp
 ****************************************************************************/
STATIC void LTPHandle_LEAdvertiseParameterSetRsp(PBTLtp pBTLtp, PBlueAPI_LEAdvertiseParameterSetRsp pAdvertiseParameterSetRsp)
{
    LTPLibSendLEAdvertiseParameterSetRsp(&pBTLtp->LTPLib,
                                         BTLTP_DEFAULT_COPMSK,
                                         NULL,
                                         pAdvertiseParameterSetRsp->cause
                                        );
} /* LTPHandle_LEAdvertiseParameterSetRsp */


/****************************************************************************
 * LTPHandle_LEAdvertiseDataSetRsp
 ****************************************************************************/
STATIC void LTPHandle_LEAdvertiseDataSetRsp(PBTLtp pBTLtp, PBlueAPI_LEAdvertiseDataSetRsp pAdvertiseDataSetRsp)
{
    LTPLibSendLEAdvertiseDataSetRsp(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    pAdvertiseDataSetRsp->cause,
                                    pAdvertiseDataSetRsp->dataType
                                   );
} /* LTPHandle_LEAdvertiseDataSetRsp */


/****************************************************************************
 * LTPHandle_LEScanRsp
 ****************************************************************************/
STATIC void LTPHandle_LEScanRsp(PBTLtp pBTLtp, PBlueAPI_LEScanRsp pScanRsp)
{
    LTPLibSendLEScanRsp(&pBTLtp->LTPLib,
                        BTLTP_DEFAULT_COPMSK,
                        NULL,
                        pScanRsp->cause
                       );
} /* LTPHandle_LEScanRsp */


/****************************************************************************
 * LTPHandle_LEScanInfo
 ****************************************************************************/
STATIC void LTPHandle_LEScanInfo(PBTLtp pBTLtp, PBlueAPI_LEScanInfo pScanInfo)
{
    LTPLibSendLEScanInfo(&pBTLtp->LTPLib,
                         BTLTP_DEFAULT_COPMSK,
                         NULL,
                         pScanInfo->remote_BD,
                         pScanInfo->remote_BD_type,
                         pScanInfo->advType,
                         pScanInfo->rssi,
                         pScanInfo->data,
                         pScanInfo->dataLength
                        );
} /* LTPHandle_LEScanInfo */


/****************************************************************************
 * LTPHandle_LEModifyWhitelistRsp
 ****************************************************************************/
STATIC void LTPHandle_LEModifyWhitelistRsp(PBTLtp pBTLtp, PBlueAPI_LEModifyWhitelistRsp pModifyWhitelistRsp)
{
    LTPLibSendLEModifyWhitelistRsp(&pBTLtp->LTPLib,
                                   BTLTP_DEFAULT_COPMSK,
                                   NULL,
                                   pModifyWhitelistRsp->cause,
                                   pModifyWhitelistRsp->operation
                                  );
} /* LTPHandle_LEModifyWhitelistRsp */


/****************************************************************************
 * LTPHandle_LEConnectionUpdateRsp
 ****************************************************************************/
STATIC void LTPHandle_LEConnectionUpdateRsp(PBTLtp pBTLtp, PBlueAPI_LEConnectionUpdateRsp pConnectionUpdateRsp)
{
    LTPLibSendLEConnectionUpdateRsp(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    pConnectionUpdateRsp->cause,
                                    (BYTE)pConnectionUpdateRsp->local_MDL_ID
                                   );
} /* LTPHandle_LEConnectionUpdateRsp */


/****************************************************************************
 * LTPHandle_LEConnectionUpdateInd
 ****************************************************************************/
STATIC void LTPHandle_LEConnectionUpdateInd(PBTLtp pBTLtp, PBlueAPI_LEConnectionUpdateInd pConnectionUpdateInd)
{
    LTPLibSendLEConnectionUpdateInd(&pBTLtp->LTPLib,
                                    BTLTP_DEFAULT_COPMSK,
                                    NULL,
                                    (BYTE)pConnectionUpdateInd->local_MDL_ID,
                                    pConnectionUpdateInd->connIntervalMin,
                                    pConnectionUpdateInd->connIntervalMax,
                                    pConnectionUpdateInd->connLatency,
                                    pConnectionUpdateInd->supervisionTimeout
                                   );
} /* LTPHandle_LEConnectionUpdateInd */


/****************************************************************************
 * LTPHandle_LEConnectionParameterInfo
 ****************************************************************************/
STATIC void LTPHandle_LEConnectionParameterInfo(PBTLtp pBTLtp, PBlueAPI_LEConnectionParameterInfo pConnectionParameterInfo)
{
    LTPLibSendLEConnectionParameterInfo(&pBTLtp->LTPLib,
                                        BTLTP_DEFAULT_COPMSK,
                                        NULL,
                                        (BYTE)pConnectionParameterInfo->local_MDL_ID,
                                        pConnectionParameterInfo->connInterval,
                                        pConnectionParameterInfo->connLatency,
                                        pConnectionParameterInfo->supervisionTimeout
                                       );
} /* LTPHandle_LEConnectionParameterInfo */

#if (F_BT_LE_PRIVACY_MODE)
/****************************************************************************
 * LTPHandle_LEPrivacyModeRsp
 ****************************************************************************/
STATIC void LTPHandle_LEPrivacyModeRsp(PBTLtp pBTLtp, PBlueAPI_LEPrivacyModeRsp pPrivacyModeRsp)
{
    LTPLibSendLEPrivacyModeRsp(&pBTLtp->LTPLib,
                               BTLTP_DEFAULT_COPMSK,
                               NULL,
                               pPrivacyModeRsp->cause,
                               pPrivacyModeRsp->local_BD,
                               pPrivacyModeRsp->local_BD_type
                              );
} /* LTPHandle_LEPrivacyModeRsp */
#endif /* (F_BT_LE_PRIVACY_MODE) */

/****************************************************************************/
/* BOOL BTLTPHandleBLUE_API_MSG                                             */
/****************************************************************************/
BOOL BTLTPHandleBLUE_API_MSG(PBTLtp pBTLtp, LPBYTE pBuffer, WORD offset)
{
    PBlueAPI_UsMessage pCOMMsg       = (PBlueAPI_UsMessage)(pBuffer + offset);
    BOOL releaseBuffer = TRUE;
    uint8_t patch_return_type = 0;	//0--nothing, 1--add more messgae, 2-- modify message

    /* handle more command or modify command handle way */
	if(NULL != pPatch_Ltp_HandleBlueApiMsg)
	{
		pPatch_Ltp_HandleBlueApiMsg((void*)pBTLtp, (void*)pBuffer, offset,\
				(void*)pCOMMsg, (void*)&releaseBuffer, (void*)&patch_return_type);
	}

    switch (pCOMMsg->Command)
    {
    case blueAPI_EventRegisterRsp: /*-----------------------------------*/
        LTPHandle_RegisterRsp(pBTLtp, &pCOMMsg->p.RegisterRsp);
        break;
    case blueAPI_EventCreateMDLInd: /*----------------------------------*/
        LTPHandle_CreateMDLInd(pBTLtp, &pCOMMsg->p.CreateMDLInd);
        break;
    case blueAPI_EventConnectMDLInfo: /*--------------------------------*/
        LTPHandle_ConnectMDLInfo(pBTLtp, &pCOMMsg->p.ConnectMDLInfo);
        break;
    case blueAPI_EventDisconnectMDLInd: /*------------------------------*/
        LTPHandle_DisconnectMDLInd(pBTLtp, &pCOMMsg->p.DisconnectMDLInd);
        break;
    case blueAPI_EventConnectMDLRsp: /*---------------------------------*/
        LTPHandle_ConnectMDLRsp(pBTLtp, &pCOMMsg->p.ConnectMDLRsp);
        break;
    case blueAPI_EventDisconnectMDLRsp: /*------------------------------*/
        LTPHandle_DisconnectMDLRsp(pBTLtp, &pCOMMsg->p.DisconnectMDLRsp);
        break;
    case blueAPI_EventDeleteMDLInfo: /*---------------------------------*/
        LTPHandle_DeleteMDLInfo(pBTLtp, &pCOMMsg->p.DeleteMDLInfo);
        break;
    case blueAPI_EventMCLStatusInfo: /*---------------------------------*/
        LTPHandle_MCLStatusInfo(pBTLtp, &pCOMMsg->p.MCLStatusInfo);
        break;
    case blueAPI_EventACLStatusInfo: /*---------------------------------*/
        LTPHandle_ACLStatusInfo(pBTLtp, &pCOMMsg->p.ACLStatusInfo);
        break;
    case blueAPI_EventDeviceConfigSetRsp: /*----------------------------*/
        LTPHandle_DeviceConfigSetRsp(pBTLtp, &pCOMMsg->p.DeviceConfigSetRsp);
        break;
    /*case blueAPI_EventAuthListInfo:
       LTPHandle_AuthListInfo(pBTLtp,&pCOMMsg->p.AuthListInfo);
       break;
    case blueAPI_EventAuthListRsp:
       LTPHandle_AuthListRsp(pBTLtp,&pCOMMsg->p.AuthListRsp);
       break;
    case blueAPI_EventAuthDeleteRsp:
       LTPHandle_AuthDeleteRsp(pBTLtp,&pCOMMsg->p.AuthDeleteRsp);
       break;*/
    case blueAPI_EventPairableModeSetRsp: /*----------------------------*/
        LTPHandle_PairableModeSetRsp(pBTLtp, &pCOMMsg->p.PairableModeSetRsp);
        break;
    case blueAPI_EventUserPasskeyReqInd: /*-----------------------------*/
        LTPHandle_UserPasskeyReqInd(pBTLtp, &pCOMMsg->p.UserPasskeyReqInd);
        break;
    case blueAPI_EventUserPasskeyReqReplyRsp: /*------------------------*/
        LTPHandle_UserPasskeyReqReplyRsp(pBTLtp, &pCOMMsg->p.UserPasskeyReqReplyRsp);
        break;
    case blueAPI_EventUserPasskeyNotificationInfo: /*-------------------*/
        LTPHandle_UserPasskeyNotificationInfo(pBTLtp, &pCOMMsg->p.UserPasskeyNotificationInfo);
        break;
    case blueAPI_EventRemoteOOBDataReqInd: /*---------------------------*/
        LTPHandle_RemoteOOBDataReqInd(pBTLtp, &pCOMMsg->p.RemoteOOBDataReqInd);
        break;
    /*case blueAPI_EventLocalOOBDataRsp:
       LTPHandle_LocalOOBDataRsp(pBTLtp,&pCOMMsg->p.LocalOOBDataRsp);
       break;*/
    case blueAPI_EventAuthResultInd: /*---------------------------------*/
        LTPHandle_AuthResultInd(pBTLtp, &pCOMMsg->p.AuthResultInd);
        break;

    case blueAPI_EventAuthResultRequestInd: /*--------------------------*/
         LTPHandle_AuthResultRequestInd(pBTLtp,&pCOMMsg->p.AuthResultRequestInd);
         break;
    
    case blueAPI_EventActInfo: /*---------------------------------------*/
        LTPHandle_ActInfo(pBTLtp, &pCOMMsg->p.ActInfo);
        break;
    case blueAPI_EventInternalEventInfo: /*-----------------------------*/
        LTPHandle_InternalEventInfo(pBTLtp, &pCOMMsg->p.InternalEventInfo);
        break;
//#if (F_BT_GATT_SERVER)
    case blueAPI_EventGATTServiceRegisterRsp: /*------------------------*/
        LTPHandle_GATTServiceRegisterRsp(pBTLtp, &pCOMMsg->p.GATTServiceRegisterRsp);
        break;

    case blueAPI_EventGATTAttributeUpdateRsp: /*------------------------*/
        releaseBuffer = LTPHandle_GATTAttributeUpdateRsp(pBTLtp, pBuffer, &pCOMMsg->p.GATTAttributeUpdateRsp);
        break;
    case blueAPI_EventGATTAttributeUpdateStatusInd: /*------------------*/
        LTPHandle_GATTAttributeUpdateStatusInd(pBTLtp, &pCOMMsg->p.GATTAttributeUpdateStatusInd);
        break;
    case blueAPI_EventGATTAttributeReadInd: /*--------------------------*/
        LTPHandle_GATTAttributeReadInd(pBTLtp, &pCOMMsg->p.GATTAttributeReadInd);
        break;
    case blueAPI_EventGATTAttributeWriteInd: /*-------------------------*/
    case blueAPI_EventGATTAttributeWriteCommandInfo: /*-----------------*/
        releaseBuffer = LTPHandle_GATTAttributeWriteInd(pBTLtp, pBuffer, (TBlueAPI_Command)pCOMMsg->Command, (PBlueAPI_GATTAttributeWriteInd)&pCOMMsg->p.GATTAttributeWriteInd);
        break;
    case blueAPI_EventGATTCCCDInfo: /*----------------------------------*/
        releaseBuffer = LTPHandle_GATTCCCDInfo(pBTLtp, pBuffer, &pCOMMsg->p.GATTCCCDInfo);
        break;
//#endif /* (F_BT_GATT_SERVER) */
//#if (F_BT_GATT_CLIENT)
    case blueAPI_EventGATTDiscoveryRsp: /*------------------------------*/
        LTPHandle_GATTDiscoveryRsp(pBTLtp, &pCOMMsg->p.GATTDiscoveryRsp);
        break;
    case blueAPI_EventGATTDiscoveryInd: /*------------------------------*/
        releaseBuffer = LTPHandle_GATTDiscoveryInd(pBTLtp, pBuffer, &pCOMMsg->p.GATTDiscoveryInd);
        break;
    case blueAPI_EventGATTAttributeReadRsp: /*--------------------------*/
        releaseBuffer = LTPHandle_GATTAttributeReadRsp(pBTLtp, pBuffer, &pCOMMsg->p.GATTAttributeReadRsp);
        break;
    case blueAPI_EventGATTAttributeWriteRsp: /*-------------------------*/
        LTPHandle_GATTAttributeWriteRsp(pBTLtp, &pCOMMsg->p.GATTAttributeWriteRsp);
        break;
    case blueAPI_EventGATTAttributeInd: /*------------------------------*/
        releaseBuffer = LTPHandle_GATTAttributeInd(pBTLtp, pBuffer, &pCOMMsg->p.GATTAttributeInd);
        break;
    case blueAPI_EventGATTAttributeNotificationInfo: /*-----------------*/
        releaseBuffer = LTPHandle_GATTAttributeNotificationInfo(pBTLtp, pBuffer, &pCOMMsg->p.GATTAttributeNotificationInfo);
        break;
//#endif /* (F_BT_GATT_CLIENT) */
//#if (F_BT_GATT_SERVER) || (F_BT_GATT_CLIENT)
    case blueAPI_EventGATTSecurityRsp: /*-------------------------------*/
        LTPHandle_GATTSecurityRsp(pBTLtp, &pCOMMsg->p.GATTSecurityRsp);
        break;
//#endif /* (F_BT_GATT_SERVER) || (F_BT_GATT_CLIENT) */
//#if (F_BT_GATT_SERVER) || (F_BT_LOW_ENERGY)
    case blueAPI_EventGATTServerStoreInd: /*----------------------------*/
        LTPHandle_GATTServerStoreInd(pBTLtp, &pCOMMsg->p.GATTServerStoreInd);
        break;
//#endif /* (F_BT_GATT_SERVER) || (F_BT_LOW_ENERGY) */
//#if (F_BT_LOW_ENERGY)
//#if (F_BT_GATT)
    case blueAPI_EventGATTMtuSizeInfo: /*-------------------------------*/
        LTPHandle_GATTMtuSizeInfo(pBTLtp, &pCOMMsg->p.GATTMtuSizeInfo);
        break;
//#endif /* (F_BT_GATT) */
    case blueAPI_EventLEAdvertiseRsp: /*--------------------------------*/
        LTPHandle_LEAdvertiseRsp(pBTLtp, &pCOMMsg->p.LEAdvertiseRsp);
        break;
    case blueAPI_EventLEAdvertiseParameterSetRsp: /*--------------------*/
        LTPHandle_LEAdvertiseParameterSetRsp(pBTLtp, &pCOMMsg->p.LEAdvertiseParameterSetRsp);
        break;
    case blueAPI_EventLEAdvertiseDataSetRsp: /*-------------------------*/
        LTPHandle_LEAdvertiseDataSetRsp(pBTLtp, &pCOMMsg->p.LEAdvertiseDataSetRsp);
        break;
    case blueAPI_EventLEScanRsp: /*-------------------------------------*/
        LTPHandle_LEScanRsp(pBTLtp, &pCOMMsg->p.LEScanRsp);
        break;
    case blueAPI_EventLEScanInfo: /*------------------------------------*/
        LTPHandle_LEScanInfo(pBTLtp, &pCOMMsg->p.LEScanInfo);
        break;
    case blueAPI_EventLEModifyWhitelistRsp: /*--------------------------*/
        LTPHandle_LEModifyWhitelistRsp(pBTLtp, &pCOMMsg->p.LEModifyWhitelistRsp);
        break;
    case blueAPI_EventLEConnectionUpdateRsp: /*-------------------------*/
        LTPHandle_LEConnectionUpdateRsp(pBTLtp, &pCOMMsg->p.LEConnectionUpdateRsp);
        break;
    case blueAPI_EventLEConnectionUpdateInd: /*-------------------------*/
        LTPHandle_LEConnectionUpdateInd(pBTLtp, &pCOMMsg->p.LEConnectionUpdateInd);
        break;
    case blueAPI_EventLEConnectionParameterInfo: /*---------------------*/
        LTPHandle_LEConnectionParameterInfo(pBTLtp, &pCOMMsg->p.LEConnectionParameterInfo);
        break;
#if (F_BT_LE_PRIVACY_MODE)
    case blueAPI_EventLEPrivacyModeRsp: /*------------------------------*/
        LTPHandle_LEPrivacyModeRsp(pBTLtp, &pCOMMsg->p.LEPrivacyModeRsp);
        break;
#endif /* (F_BT_LE_PRIVACY_MODE) */
//#endif /* (F_BT_LOW_ENERGY) */
    default: /*---------------------------------------------------------*/
    	if(0 == patch_return_type)
    	{
        	BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                               "!!LTP: unknown COM msg cmd or patch command(0x%x)",
                               pCOMMsg->Command
                              );
        }
        else
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "BTLTPHandleBLUE_API_MSG, pCOMMsg->Command = 0x%x", 1, pCOMMsg->Command);
        }
        break;
    }

    return releaseBuffer;
}
