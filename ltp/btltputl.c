enum { __FILE_NUM__= 0 };

/**********************************************************************!KA****
 *
 * $Header: /var/lib/cvs/sw/src/bt/app/btltp/btltputl.c,v 1.23 2014/03/24 16:10:23 ka Exp $
 *
 * File:        $RCSfile: btltputl.c,v $
 * Version:     $Name: P_SRP0007_U_KA_BLB1290_RC1 $
 *
 * Archive:     $Source: /var/lib/cvs/sw/src/bt/app/btltp/btltputl.c,v $
 * Revision:    $Revision: 1.23 $
 * Date:        $Date: 2014/03/24 16:10:23 $
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
 *         LTP Application
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
 * $Log: btltputl.c,v $
 * Revision 1.23  2014/03/24 16:10:23  ka
 * issue 0012122#
 * Create Vendor Project with source base from PM Handover (P_BLB_U_PM_D_20140312)
 *
 * Revision 1.22.2.1  2013/09/03 08:39:23  mn
 * issue 0010755
 * Changed for using with FreeRTOS (BtStack test).
 *
 * Revision 1.22  2013/07/09 13:49:49  ore
 * issue 0010462
 * cleanup new trace calls
 *
 * Revision 1.21  2013/03/12 10:53:10  ore
 * issue 0004550
 * Check maxTPDUSize / maxLTPSize calculation
 *
 * Revision 1.20  2013/02/27 18:08:55  ore
 * issue 0008926
 * fix VS2005 compiler warnings
 *
 * Revision 1.19  2013/02/26 11:03:21  ore
 * issue 0008354
 * fix ConnectMDLGATTRsp / GATT context handling
 *
 * Revision 1.18  2013/01/09 14:16:43  ore
 * issue 0008354
 * implement LTP BLE/GATT messages
 *
 * Revision 1.17  2012/03/20 08:28:07  odr
 * Internal Change 7216: API renaming and cleaning
 * Contains changes from API_RENAMED branch
 *
 * Revision 1.16.2.2  2012/03/19 14:03:43  odr
 * API renamed: Changed includes to fit new file names
 *
 * Revision 1.16.2.1  2012/03/06 16:01:17  odr
 * - adapted function calls, enums and defines to new BlueAPI norm
 *
 * Revision 1.16  2011/04/08 13:54:28  ore
 * fix 0006083: ActInfo message needs optional parameter for max_Tx_LTP_Size
 *
 * Revision 1.15  2010/12/30 13:22:36  ore
 * fix 0005597: LTP pool switching not usable with multiple MDLs
 * - rename context
 *
 * Revision 1.14  2010/10/21 15:24:19  ore
 * fix 0005404: LTP credit context not reused for reconnect
 *
 * Revision 1.13  2010/09/29 13:46:13  ore
 * fix 0005265: [LTP]rename BTMED_* defines to BTLTP_*
 *
 * Revision 1.12  2010/06/08 14:12:01  ka
 * Fix: 0004380: [LTP] handling of "LTP_NotSupported" Confirmation messages
 *
 * Revision 1.11  2010/05/21 14:07:46  ore
 * on connect errors no CreditContext is allocated
 *
 * Revision 1.10  2010/05/11 15:33:37  ka
 * - added btsec device secirity handling
 * - moved OSIF functions out of btmed_api
 * - replaced Blueface prototype in btsec with own definition
 * - fixed several compilder warnings in btsec and HDP
 *
 * Revision 1.9  2010/05/05 12:08:53  ka
 * - fixed asyncronus ResetReq with CRC
 * - fixed missing actInfo after configurator exit
 *
 * Revision 1.8  2010/04/28 13:23:13  ore
 * - add creditbased flowcontrol
 * - fix ConnectMDLInfo and ReconnectMDLReq
 * - remove tempBuffer
 *
 * Revision 1.7  2010/03/19 12:31:11  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.6  2010/03/16 17:57:31  ka
 * interim version for LTP1.3 bootstrap
 *
 * Revision 1.5  2008/08/20 13:34:01  ka
 * - introduced LTP-Library
 * - bugfix for data-resp missing
 *
 * Revision 1.4  2008/07/22 16:16:59  ka
 * added Inquiry/ServiceDiscovery commands
 *
 * Revision 1.3  2008/07/03 12:10:53  ka
 * first VASC version
 *
 * Revision 1.2  2008/06/27 18:26:11  ka
 * - config enter + exit works
 *
 * Revision 1.1  2008/06/09 12:32:54  mn
 * Initial revision.
 *
 ************************************************************************!KA*/

#include <blueapi_types.h>
#include "btltp.h"
#include <trace_binary.h>

/****************************************************************************/
/* PBTLtpMDLContext BTLTPAllocateMDLContext                                 */
/****************************************************************************/
PBTLtpMDLContext BTLTPAllocateMDLContext(PBTLtp pBTLtp, BYTE local_MDL_ID, BYTE local_MDEP_ID)
{
    WORD loop;
    PBTLtpMDLContext pUnusedContext = NULL;

#if 0   /* tifnan:¡¡must be true */
    BOOL isGATT = (linkConfigType == blueAPI_LinkConfigGATT);
    if (!isGATT && (local_MDL_ID == 0))
    {
        return NULL;
    }
#endif

    for (loop = 0; loop < BLUE_API_MDL_COUNT; loop++)
    {
        PBTLtpMDLContext pContext = &pBTLtp->MDLContextPool[loop];
        if (pContext->flags & LTP_MDL_ALLOCATED)
        {
            if (//isGATT && /* tifnan:¡¡must be true */
                (pContext->flags & LTP_MDL_GATT) &&
                (pContext->local_MDL_ID == 0x00) &&
                (pContext->local_MDEP_ID == local_MDEP_ID)
            )
            {
                pContext->local_MDL_ID = local_MDL_ID;
                return pContext;
            }
            else if (pContext->local_MDL_ID == local_MDL_ID)
            {
                return pContext;
            }
        }
        else if (pUnusedContext == NULL)
        {
            pUnusedContext = pContext;
        }
    }

    if (pUnusedContext != NULL)
    {
        memset(pUnusedContext, 0, sizeof(TBTLtpMDLContext));
        pUnusedContext->flags           = LTP_MDL_ALLOCATED;
        pUnusedContext->local_MDL_ID    = local_MDL_ID;
        pUnusedContext->local_MDEP_ID   = local_MDEP_ID;

        //if (isGATT)  /* tifnan:¡¡must be true */
        {
            pUnusedContext->flags        |= LTP_MDL_GATT;
        }
        return pUnusedContext;
    }

    BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                           "!!!LTP: out of MDL context elements"
                          );
    return NULL;
}

/****************************************************************************/
/* PBTLtpMDLContext BTLTPFindMDLContext                                     */
/****************************************************************************/
PBTLtpMDLContext BTLTPFindMDLContext(PBTLtp pBTLtp, BYTE local_MDL_ID)
{
    WORD loop;

    for (loop = 0; loop < BLUE_API_MDL_COUNT; loop++)
    {
        PBTLtpMDLContext pContext = &pBTLtp->MDLContextPool[loop];
        if ((pContext->flags & LTP_MDL_ALLOCATED) &&
                (pContext->local_MDL_ID == local_MDL_ID)
           )
        {
            return pContext;
        }
    }

    BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                           "!!!LTP: no MDL context found for MDL %d",
                           local_MDL_ID
                          );
    return NULL;
}


/****************************************************************************/
/* PBTLtpMDLContext BTLTPFindMDLContextByMDEPID                              */
/****************************************************************************/
PBTLtpMDLContext BTLTPFindMDLContextByMDEPID(PBTLtp pBTLtp, BYTE local_MDEP_ID)
{
    WORD loop;

    for (loop = 0; loop < BLUE_API_MDL_COUNT; loop++)
    {
        PBTLtpMDLContext pContext = &pBTLtp->MDLContextPool[loop];
        if ((pContext->flags & LTP_MDL_ALLOCATED) &&
                (pContext->local_MDL_ID == 0x00) &&
                (pContext->local_MDEP_ID == local_MDEP_ID)
           )
        {
            return pContext;
        }
    }

    BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                           "!!!LTP: no MDL context found for MDEP %d",
                           local_MDEP_ID
                          );
    return NULL;
}

/****************************************************************************/
/* BYTE BTLTPCountMDLConnected                                              */
/****************************************************************************/
BYTE BTLTPCountMDLConnected(PBTLtp pBTLtp)
{
    WORD loop;
    BYTE count = 0;

    for (loop = 0; loop < BLUE_API_MDL_COUNT; loop++)
    {
        PBTLtpMDLContext pContext = &pBTLtp->MDLContextPool[loop];

        if ((pContext->flags & (LTP_MDL_ALLOCATED | LTP_MDL_CONNECTED)) == (LTP_MDL_ALLOCATED | LTP_MDL_CONNECTED))
        {
            count++;
        }
    }

    return count;
}

/* find a mdl connection */
PBTLtpMDLContext BTLTPFindAMDLConnected(PBTLtp pBTLtp)
{
    WORD loop;

    for (loop = 0; loop < BLUE_API_MDL_COUNT; loop++)
    {
        PBTLtpMDLContext pContext = &pBTLtp->MDLContextPool[loop];

        if ((pContext->flags & (LTP_MDL_ALLOCATED | LTP_MDL_CONNECTED)) == (LTP_MDL_ALLOCATED | LTP_MDL_CONNECTED))
        {
            return pContext;
        }
    }

	return NULL;
}



/****************************************************************************/
/* PBTLtpAction BTLTPAllocateAction                                         */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/* )                                                                        */
/****************************************************************************/
PBTLtpAction BTLTPAllocateAction(PBTLtp pBTLtp)
{
    WORD loop;

    for (loop = 0; loop < BTLTP_ACTION_POOL_SIZE; loop++)
    {
        if (pBTLtp->ActionPool[loop].Action == btltpActionNotUsed)
        {
            return &pBTLtp->ActionPool[loop];
        }
    }

    BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                           "!!!LTP: out of action queue elements"
                          );
    return NULL;
}

/****************************************************************************/
/* BYTE BTLTPConvertCOMtoLTPcause                                           */
/* (                                                                        */
/*    TBlueAPI_Cause cause                                                  */
/* )                                                                        */
/****************************************************************************/
BYTE BTLTPConvertCOMtoLTPcause(TBlueAPI_Cause cause)
{
    switch (cause)
    {
    case blueAPI_CauseUnspecified:
        return LTP_CAUSE_UNSPECIFIED;
    default:
        return (BYTE) cause;
    }
}

/****************************************************************************/
/* TBlueAPI_Cause BTLTPConvertLTPtoCOMcause                                 */
/* (                                                                        */
/*    BYTE cause                                                            */
/* )                                                                        */
/****************************************************************************/
TBlueAPI_Cause BTLTPConvertLTPtoCOMcause(BYTE cause)
{
    switch (cause)
    {
    case LTP_CAUSE_NOT_SUPPORTED:
        return blueAPI_CauseNotSupported;
    default:
        return (TBlueAPI_Cause)cause;
    }
}

/****************************************************************************/
/* void BTLTPCheckForActInfo                                                */
/* (                                                                        */
/*    PBTLtp pBTLtp                                                         */
/* )                                                                        */
/****************************************************************************/
void BTLTPCheckForActInfo(PBTLtp pBTLtp)
{
    BYTE pOpt[4];
    WORD pos = 0;


    if (pBTLtp->ActInfoFlags == LTP_ACT_INFO_FLAG_ALL)
    {
        NETSHORT2CHAR(&pOpt[pos], pBTLtp->LTPLib.ReceiveMaxLength);
        pos += 2;
        //NETSHORT2CHAR(&pOpt[pos],BT_US_PDU_L2C_BYTE_COUNT + BT_US_WRITE_OFFSET_COUNT); pos+=2;
        NETSHORT2CHAR(&pOpt[pos], 0 + BT_US_WRITE_OFFSET_COUNT);
        pos += 2;

        BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                               "LTP: send ActInfo cause(%d)",
                               pBTLtp->ActInfoCause
                              );

        LTPLibSendActInfo(&pBTLtp->LTPLib,
                          BTLTP_DEFAULT_COPMSK | \
                          LTP_ACT_INFO_OPT_MASK_MAX_RX_MESSAGE_LENGTH | \
                          LTP_ACT_INFO_OPT_MASK_MAX_TX_MESSAGE_LENGTH,
                          pOpt,
                          pBTLtp->ActInfoCause,
                          LTP_VERSION,
                          pBTLtp->ownBDAddress,
                          pBTLtp->ActInfoVersionString
                         );
    }
}

/****************************************************************************
 * BTLTPAllocateFindGATTServiceHandle
 ****************************************************************************/
BYTE BTLTPAllocateFindGATTServiceHandle(PBTLtp pBTLtp, void *serviceHandle)
{
    BYTE i;
    BYTE firstUnused = BT_GATT_SERVER_MAX_SERVICES_COUNT;

    for (i = 0; i < BT_GATT_SERVER_MAX_SERVICES_COUNT; i++)
    {
        if (pBTLtp->gattServiceHandle[i] == serviceHandle)
        {
            return i;
        }
        else if ((pBTLtp->gattServiceHandle[i] == NULL) &&
                 (firstUnused == BT_GATT_SERVER_MAX_SERVICES_COUNT)
                )
        {
            firstUnused = i;
        }
    }

    if (firstUnused != BT_GATT_SERVER_MAX_SERVICES_COUNT)
    {
        pBTLtp->gattServiceHandle[firstUnused] = serviceHandle;
    }

    return firstUnused;
} /* BTLTPAllocateFindGATTServiceHandle */


/****************************************************************************
 * BTLTPLookupGATTServiceHandle
 ****************************************************************************/
void * BTLTPLookupGATTServiceHandle(PBTLtp pBTLtp, BYTE shortServiceHandle)
{
    if (shortServiceHandle < BT_GATT_SERVER_MAX_SERVICES_COUNT)
    {
        return pBTLtp->gattServiceHandle[shortServiceHandle];
    }

    return NULL;
} /* BTLTPLookupGATTServiceHandle */

