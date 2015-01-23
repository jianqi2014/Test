enum { __FILE_NUM__= 0 };

#include <FreeRTOS.h>
#include <task.h>
#include <blueapi_types.h>
#include <ltplib.h>
#include <blueapi.h>
#include "patch_application.h"
#include "aci_if.h"
#include "btltp.h"
#include "core_cm0.h"
#include <trace_binary.h>
#include "otp.h"

void ltpTimerStart(TLTPTimerID TimerID, int TimerMS);

/****************************************************************************/
/* void BTLTPBufferCallback                                                 */
/* (                                                                        */
/*    THandle Handle                                                        */
/* )                                                                        */
/****************************************************************************/
void BTLTPBufferCallback(THandle Handle)
{
    PBTLtpAction         pAction    = (PBTLtpAction)Handle.lpHandle;
    TBTLtpActionCommand  thisAction = pAction->Action;

    pAction->Action = btltpActionNotUsed;

    switch (thisAction)
    {
    case btltpActionReset: /*---------------------------------------------*/
        BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                               "LTP: reset (wait for WD to kick in)"
                              );

        /* wait for last char of ResetRsp (buffercallback is executed on txempty, NOT on txcomplete) */
        vTaskDelay(portTICK_RATE_MS * 20);                       /* 20 ms delay */
        NVIC_SystemReset();   /* system reset */
        break;

#if 0
    case btltpActionSendDataConf: /*--------------------------------------*/
        {
            PBTLtpMDLContext pMDLContext = BTLTPFindMDLContext(P_BtLtp, pAction->p.MDL_ID);
            BOOL             ret;

            if (pMDLContext != NULL)
            {
                pMDLContext->pendingDataConfs++;
                while (pMDLContext->pendingDataConfs > 0)
                {
                    ret = blueAPI_DataConf(NULL,
                                           P_BtLtp->blueAPIHandle,
                                           pAction->p.MDL_ID,
                                           blueAPI_CauseSuccess
                                          );

                    /* if msg fails, keep number of failed dataConfs and retry later */
                    if (ret == FALSE)
                    {
                        BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                                               "!!LTP: failed to send [%d] COM_DataConf(s)",
                                               pMDLContext->pendingDataConfs
                                              );
                        break;
                    }
                    pMDLContext->pendingDataConfs--;
                }
            }
            LTPLibTriggerLTPProccess(P_BtLtp->.LTPLib);
        }
        break;
#endif
    default: /*-----------------------------------------------------------*/
        break;
    }
}

/****************************************************************************/
/* BOOL BTLTPTgtHandleLTPMessage                                            */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/*    LPBYTE            pMsgBuffer: pointer to message buffer               */
/*    BYTE              cmd       : identifier for LTP-command to be handled*/
/*    BYTE              copmsk    : copmsk of LPT-command to be handled     */
/*    LPBYTE            pOpt      : pointer to optional parameters of LTP-  */
/*                                  command to be handled, or NULL in case  */
/*                                  of no optional parameters included      */
/*    WORD              lenPara   : length of mandatory parameters of LTP-  */
/*                                  command to be handled                   */
/*    LPBYTE            pPara     : pointer to mandatory parameters of LTP- */
/*                                  command to be handled, or NULL in case  */
/*                                  of no mandatory parameters included     */
/* )                                                                        */
/****************************************************************************/
BOOL BTLTPTgtHandleLTPMessage(LTP_TGT_APPHANDLE AppHandle, LPBYTE pMsgBuffer, BYTE cmd, BYTE copmsk, LPBYTE pOpt, WORD lenPara, LPBYTE pPara)
{
    PBTLtp pBTLtp      = (PBTLtp)AppHandle;
    BOOL   reUseBuffer = TRUE; /* reuse assembly buffer for next message */
    uint8_t command = cmd;
	uint8_t patch_return_type = 0; //0--nothing, 1--add more command, 2-- modify command

	/* handle more ltp message or change ltp message handle way here */
    if(NULL != pPatch_Ltp_HandleLtpMsg)
    {
    	pPatch_Ltp_HandleLtpMsg((void*)pBTLtp, copmsk, (void*)pOpt, lenPara, (void*)pPara,\
    		(void*)&reUseBuffer,(void*) &command, (void*)&patch_return_type);
    }
	
    switch (command)
    {
    case LTP_DATA_UNSEGMENTED: /*-----------------------------------------*/
    case LTP_DATA_START_SEGMENT: /*---------------------------------------*/
    case LTP_DATA_END_SEGMENT: /*-----------------------------------------*/
    case LTP_DATA_CONTINUE_SEGMENT: /*------------------------------------*/
    case LTP_CONFIG_TUNNEL_REQ: /*----------------------------------------*/
    case LTP_GATT_ATTRIBUTE_UPDATE_REQ: /*--------------------------------*/
    case LTP_GATT_ATTRIBUTE_READ_CNF: /*----------------------------------*/
    case LTP_GATT_ATTRIBUTE_WRITE_REQ: /*---------------------------------*/
        /* reuse assembly buffer as DS message */
        pBTLtp->pMsgBuffer = pMsgBuffer;
        break;

    default: /*-----------------------------------------------------------*/
        /* force copy in BTMOSPutMessage */
        pBTLtp->pMsgBuffer = NULL;
        break;
    }

    switch (command)
    {
    case LTP_REGISTER_STACK_REQ:
    	BTLTPHandleRegisterStackReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
    break;

    case LTP_CONFIG_DLPS_REQ:
    	BTLTPHandleConfigDlpsReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
    break;
    
    case LTP_CONNECT_MDL_REQ: /*------------------------------------------*/
        BTLTPHandleConnectMDLReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_CREATE_MDL_CNF: /*-------------------------------------------*/
        BTLTPHandleCreateMDLConf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_DISCONNECT_MDL_REQ: /*---------------------------------------*/
        BTLTPHandleDisconnectMDLReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_DISCONNECT_MDL_CNF: /*---------------------------------------*/
        BTLTPHandleDisconnectMDLConf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_EXIT_REQ: /*-------------------------------------------------*/
        BTLTPHandleExitReq(pBTLtp, copmsk, pOpt, pPara);
        break;
    case LTP_RESET_REQ: /*------------------------------------------------*/
        BTLTPHandleResetReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_PASSKEY_REQUEST_CNF: /*--------------------------------------*/
        BTLTPHandlePasskeyRequestCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_REMOTE_OOB_REQUEST_CNF: /*-----------------------------------*/
        BTLTPHandleOOBRequestCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_AUTH_RESULT_CNF: /*------------------------------------------*/
        BTLTPHandleAuthResultCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_AUTH_RESULT_EXT_CNF: /*--------------------------------------*/
        BTLTPHandleAuthResultExtCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
	case LTP_AUTH_RESULT_REQUEST_EXT_CNF: /*------------------------------*/
      	BTLTPHandleAuthResultRequestExtCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
      	break;
    case LTP_CONFIG_TUNNEL_REQ: /*----------------------------------------*/
        reUseBuffer = BTLTPHandleConfigTunnelReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_PAIRABLE_MODE_SET_REQ: /*------------------------------------*/
        BTLTPHandlePairableModeSetReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_PASSKEY_REQ_REPLY_REQ: /*------------------------------------*/
        BTLTPHandlePasskeyReqReplyReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    /* add for gatt auto test */
    case LTP_DEVICE_CONFIG_DEVICE_SET_REQ:
        BTLTPHandleDeviceNameReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_DEVICE_CONFIG_SECURITY_SET_REQ:
        BTLTPHandleDeviceConfigSecuritySetReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    /* add for gatt auto test end */

//#if (F_BT_GATT_SERVER)
    case LTP_GATT_SERVICE_REGISTER_REQ: /*--------------------------------*/
        BTLTPHandleGATTServiceRegisterReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_SERVICE_RELEASE_REQ: /*---------------------------------*/
        BTLTPHandleGATTServiceReleaseReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_UPDATE_REQ: /*--------------------------------*/
        reUseBuffer = BTLTPHandleGATTAttributeUpdateReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_UPDATE_STATUS_CNF: /*-------------------------*/
        BTLTPHandleGATTAttributeUpdateStatusCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_READ_CNF: /*----------------------------------*/
        reUseBuffer = BTLTPHandleGATTAttributeReadCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_WRITE_CNF: /*---------------------------------*/
        BTLTPHandleGATTAttributeWriteCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
//#endif /* (F_BT_GATT_SERVER) */
//#if (F_BT_GATT_SERVER) || (F_BT_LOW_ENERGY)
    case LTP_GATT_SERVER_STORE_CNF: /*------------------------------------*/
        BTLTPHandleGATTServerStoreCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
//#endif /* (F_BT_GATT_SERVER) || (F_BT_LOW_ENERGY) */
//#if (F_BT_GATT_CLIENT)
    case LTP_CONNECT_GATT_MDL_REQ: /*-------------------------------------*/
        BTLTPHandleConnectGATTMDLReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_DISCOVERY_REQ: /*---------------------------------------*/
        BTLTPHandleGATTDiscoveryReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_DISCOVERY_CNF: /*---------------------------------------*/
        BTLTPHandleGATTDiscoveryCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_READ_REQ: /*----------------------------------*/
        BTLTPHandleGATTAttributeReadReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_WRITE_REQ: /*---------------------------------*/
        reUseBuffer = BTLTPHandleGATTAttributeWriteReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_GATT_ATTRIBUTE_CNF: /*---------------------------------------*/
        BTLTPHandleGATTAttributeCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
//#endif /* (F_BT_GATT_CLIENT) */
//#if (F_BT_GATT_SERVER) || (F_BT_GATT_CLIENT)
    case LTP_GATT_SECURITY_REQ: /*----------------------------------------*/
        BTLTPHandleGATTSecurityReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
//#endif /* (F_BT_GATT_SERVER) || (F_BT_GATT_CLIENT) */
//#if (F_BT_LOW_ENERGY)
    case LTP_LE_ADVERTISE_REQ: /*-----------------------------------------*/
        BTLTPHandleLEAdvertiseReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_ADVERTISE_PARAMETER_SET_REQ: /*---------------------------*/
        BTLTPHandleLEAdvertiseParameterSetReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_ADVERTISE_DATA_SET_REQ: /*--------------------------------*/
        BTLTPHandleLEAdvertiseDataSetReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_SCAN_REQ: /*----------------------------------------------*/
        BTLTPHandleLEScanReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_MODIFY_WHITELIST_REQ: /*----------------------------------*/
        BTLTPHandleLEModifyWhitelistReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_CONNECTION_UPDATE_REQ: /*---------------------------------*/
        BTLTPHandleLEConnectionUpdateReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
    case LTP_LE_CONNECTION_UPDATE_CNF: /*---------------------------------*/
        BTLTPHandleLEConnectionUpdateCnf(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
#if (F_BT_LE_PRIVACY_MODE)
    case LTP_LE_PRIVACY_MODE_REQ: /*--------------------------------------*/
        BTLTPHandleLEPrivacyModeReq(pBTLtp, copmsk, pOpt, lenPara, pPara);
        break;
#endif /* (F_BT_LE_PRIVACY_MODE) */
//#endif /* (F_BT_LOW_ENERGY) */
    default: /*-----------------------------------------------------------*/
    	if(0 == patch_return_type)
    	{
    		LTPLibHandleUnkownCommand(&pBTLtp->LTPLib, cmd);
    	}
    	else
    	{
    		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "BTLTPTgtHandleLTPMessage, command = 0x%x", 1, command);
    	}
        break;
    }

    return reUseBuffer;
}

/****************************************************************************/
/* BOOL BTLTPTgtSendLTPMessage                                              */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/*    LPBYTE            pMsg      : pointer to of LTP msg buffer to be send */
/*    WORD              offset                                              */
/*    WORD              dataLen                                             */
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* FALSE in case the message could be send successfully,                    */
/* TRUE in case the message could not be send but was dumped                */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This function is used to send an LTP message to an Application with the  */
/* BT_LTP_Sendxxx functions of this library                                 */
/****************************************************************************/
BOOL BTLTPTgtSendLTPMessage(LTP_TGT_APPHANDLE AppHandle, LPBYTE pBuffer, WORD offset, WORD dataLen)
{
	if(NULL != pPatch_Ltp_BTLTPTgtSendLTPMessage)
	{
		return pPatch_Ltp_BTLTPTgtSendLTPMessage(AppHandle, pBuffer, offset, dataLen);
	}
	
    PBTLtp    pBTLtp   = (PBTLtp)AppHandle;
    THandle   Handle;


    if (pBTLtp->State == btltpStateIdle)
    {
        /* put real buffer address and buffer callback in front of message */
        //pBTLtp->p_send_buffer = pBuffer;    /* save tx buffer address */
        LtpWrite((LPBYTE)(pBuffer + offset), dataLen);
        return (TRUE);
    }
    else
    {
        /* KA: todo: just temporary, needs a better handling */
        //blueAPI_BufferRelease(P_BtLtp->blueAPIHandle, pBuffer);
        /* tifnan change ram release way */
        //vPortFree(pBuffer, RAM_TYPE_DATA_OFF);	//for buffeer tx!!!!!
        pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx = pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx = 0;

        if (pBTLtp->pBufferAction)
        {
            Handle.lpHandle       = (LPVOID)pBTLtp->pBufferAction;
            pBTLtp->pBufferAction = NULL;

            BTLTPBufferCallback(Handle);
        }

        BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                               "btLTP: did not send message (configurator active)"
                              );
        return TRUE;
    }
}

/****************************************************************************/
/* LPBYTE BTLTPTgtSendBfferAlloc                                            */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/*    WORD    len                 : size of buffer to be allocated (bytes)  */
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* pointer to allocated memory in case of success                           */
/* NULL pointer in case of an error                                         */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to allocate buffers for LTP        */
/* messages that are send to an Application with the BT_LTP_Sendxxx         */
/* functions of this library.                                               */
/****************************************************************************/
LPBYTE BTLTPTgtSendBufferAlloc(LTP_TGT_APPHANDLE AppHandle, WORD len)
{
	if(NULL != pPatch_Ltp_SendBufferAlloc)
    {
    	return pPatch_Ltp_SendBufferAlloc(AppHandle, len);
    }
    
    LPBYTE p_buf = NULL;
    PBTLtp    pBTLtp   = (PBTLtp)AppHandle;
	
	/* pBuffer = (LPBYTE)pvPortMalloc(len, RAM_TYPE_DATA_OFF);
    if (pBuffer == NULL)
        DebuggerBreak();   */
     
	if(NULL == pBTLtp->p_aci_tcb)
	{
		return NULL;
	}

	/* free index > tx index  */
	if((pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx >= pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx)
		&& (pBTLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size != pBTLtp->p_aci_tcb->tx_mem_tcb.free_size))
	{
		/* [A---tx_idx----free_idx----B], have enough serial ram in  [free_idx----B]  */
		if((pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx + len) <= otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size)
		{
			p_buf = pBTLtp->p_aci_tcb->p_tx_buf + pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx;
			pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx += len;
			pBTLtp->p_aci_tcb->tx_mem_tcb.free_size -= len;
			/* if reach tx buffer size, return to index 0 */
			pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx &= (otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size - 1);
		}
		/* [A---tx_idx----free_idx----B], have enough serial ram in  [A---tx_idx],
			discard [free_idx----B] */
		else if((pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx + len) > otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size
				&& pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx >= len)
		{
			p_buf = pBTLtp->p_aci_tcb->p_tx_buf;
			pBTLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size = 
					otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size - pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx;
			pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx = len;
			pBTLtp->p_aci_tcb->tx_mem_tcb.free_size -= len;
		}
		else
		{
			p_buf = NULL;	/* no enough free size */
			DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Have no serial ram,free index:0x%x, tx index:0x%x, unused size:0x%x, free size:0x%x",
					4, pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx, pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx,\
					pBTLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size, pBTLtp->p_aci_tcb->tx_mem_tcb.free_size);
		}
	}
	/* free index < tx index */
	else if(pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx < pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx)
	{
		/* [A---free_idx----tx_idx----B],  have enough ram in  [free_idx----tx_idx]  */
		if((pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx + len) < pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx)
		{
			p_buf = pBTLtp->p_aci_tcb->p_tx_buf + pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx;
			pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx += len;
			pBTLtp->p_aci_tcb->tx_mem_tcb.free_size -= len;
		}
		else
		{
			p_buf = NULL;	/* no enough free size */
			DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Have no serial ram,free index:0x%x, tx index:0x%x, unused size:0x%x, free size:0x%x",
					4, pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx, pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx,\
					pBTLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size, pBTLtp->p_aci_tcb->tx_mem_tcb.free_size);
		}
	}
	else	/* no possiable */
	{
		p_buf = NULL;	/* no enough free size */
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Have no serial ram", 0);
	}

	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "BufferAlloc:tx_idx == 0x%4x, free_idx = 0x%4x", 2, pBTLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx,\
		pBTLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx);
	
    return p_buf;
}

/****************************************************************************/
/* void BTLTPTgtReceiveBufferRelease                                        */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/*    LPBYTE            pBuffer   : pointer to receive buffer to be released*/
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* non                                                                      */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to released buffers for LTP        */
/* messages that are received and consumed by the 'LTPLibHandleReceiveData' */
/* function of this library.                                                */
/****************************************************************************/

void BTLTPTgtReceiveBufferRelease(LTP_TGT_APPHANDLE AppHandle, LPBYTE pBuffer)
{
    UNUSED_PARAMETER(AppHandle);

    LtpBufferRelease((void *)pBuffer);
}

/****************************************************************************/
/* LPBYTE BTLTPTgtAssemblyBufferAlloc                                       */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* pointer to allocated memory in case of success                           */
/* NULL pointer in case of an error                                         */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to allocate buffers for LTP-       */
/* message assembly that is processed by functions of this library.         */
/****************************************************************************/
LPBYTE BTLTPTgtAssemblyBufferAlloc(LTP_TGT_APPHANDLE AppHandle)
{
    PBTLtp pBTLtp  = (PBTLtp)AppHandle;
    //LPBYTE pBuffer = NULL;
    //TBlueAPI_Cause  cause;

    /* alloc 400 bytes for ltp to save rx bytes */
    //pBuffer = pvPortMalloc(400, RAM_TYPE_DATA_OFF);
    //DBG_DIRECT("->PT:%x", pBuffer);
    //pBuffer = Msg_Buf;
    /*if (pBuffer == NULL)
    {
    	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "ltp alloc failed!", 0);
    }*/
    return pBTLtp->p_aci_tcb->p_rx_handle_buf;

   // return pBuffer;
}

/****************************************************************************/
/* void BTLTPTgtAssemblyBufferRelease                                       */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/*    LPBYTE            pBuffer   : pointer to receive buffer to be released*/
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* non                                                                      */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to released buffers for LTP        */
/* messages that are received and consumed by the 'LTPLibHandleReceiveData' */
/* function of this library.                                                */
/****************************************************************************/
void BTLTPTgtAssemblyBufferRelease(LTP_TGT_APPHANDLE AppHandle, LPBYTE pBuffer)
{
	//do nothing now!!!!
    //DBG_DIRECT("->PF1:%x", pBuffer);
    //vPortFree(pBuffer, RAM_TYPE_DATA_OFF);
    DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "->PF2:%x", 1, pBuffer);
}

/****************************************************************************/
/* PLTPElement BTLTPTgtQueueElementAlloc                                    */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* pointer to allocated queue element in case of success                    */
/* NULL pointer in case of an error                                         */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to allocate queue elements for LTP-*/
/* message assembly that is processed by functions of this library.         */
/****************************************************************************/
PLTPElement BTLTPTgtQueueElementAlloc(LTP_TGT_APPHANDLE AppHandle)
{
    PBTLtp      pBTLtp   = (PBTLtp)AppHandle;
    PLTPElement pElement;

    pElement = ltpQueueOut(&pBTLtp->FreeElementQueue);

    if (!pElement)
    {
        BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                               "btLTP: no element in BTLTPTgtQueueElementAlloc"
                              );
    }

    return pElement;
}

/****************************************************************************/
/* void BTLTPTgtQueueElementRelease                                         */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identity Application Context  */
/* )                                                                        */
/* return:------------------------------------------------------------------*/
/* non                                                                      */
/*                                                                          */
/* Description:-------------------------------------------------------------*/
/* This target specific function is used to release queue elements for LTP- */
/* message assembly that is processed by functions of this library.         */
/****************************************************************************/
void BTLTPTgtQueueElementRelease(LTP_TGT_APPHANDLE AppHandle, PLTPElement pLTPElement)
{
    PBTLtp pBTLtp   = (PBTLtp)AppHandle;

    ltpQueueIn(&pBTLtp->FreeElementQueue, pLTPElement);
}

/**
 * @used to get tx ram space and tx bytes.
 * @param  handle -- tx handle.
 * @param  p_buf -- the bytes buffer to be sent.
 * @param  len -- the size of the buffer.
 * @return  tx result.
 * @retval LTP_TX_RESULT_SUCCED		      -- tx succed, 
 *             LTP_TX_RESULT_NO_MEMORY        -- no free space for tx.
 *		   LTP_TX_RESULT_FAILED		      -- tx failed.
 *		   LTP_TX_STATUS_INVALID_HANDLE  -- tx handle is invalid.
*/
uint8_t AutoTestMallocAndSendBytes(LtpTxHandle handle, uint8_t* p_buf, uint32_t len)
{
	uint8_t tx_res = (uint8_t)LTP_TX_STATUS_SUCCED;
	uint8_t* p = NULL;

	if(NULL == handle)
	{
		return (uint8_t)LTP_TX_STATUS_INVALID_HANDLE;
	}
	
	p = BTLTPTgtSendBufferAlloc(handle, len);
	
	if(NULL != p)
	{
		memcpy(p, p_buf, len);
		if(BTLTPTgtSendLTPMessage(handle, p, 0, len))
		{
			tx_res = (uint8_t)LTP_TX_STATUS_SUCCED;
		}
		else
		{
			tx_res = (uint8_t)LTP_TX_STATUS_FAILED;
		}
	}
	else
	{
		tx_res =  (uint8_t)LTP_TX_STATUS_NO_MEMORY;
	}

	return tx_res;
}

/**
 * @brief just tx, bytes are in tx buffer already.
 * @param  tx_handle -- tx handle.
 * @param  p_buf -- the bytes buffer to be sent.
 * @param  len -- the size of the buffer.
 * @return  tx result.
 * @retval LTP_TX_RESULT_SUCCED		      -- tx succed, 
 *             LTP_TX_RESULT_NO_MEMORY        -- no free space for tx.
 *		   LTP_TX_RESULT_FAILED		      -- tx failed.
 *		   LTP_TX_STATUS_INVALID_HANDLE  -- tx handle is invalid.
*/

uint8_t AutoTestSendBytes(LtpTxHandle tx_handle, uint8_t* p_buf, uint16_t len)
{   
	if(NULL == tx_handle)
	{
		return (uint8_t)LTP_TX_STATUS_INVALID_HANDLE;
	}
	
    LtpWrite(p_buf, len);

    return (uint8_t)LTP_TX_STATUS_SUCCED;
}

/**
 * @brief  wapper fucntion, call AutoTestRegisterFromFlash function actually.
 * @param  tx_handle     the handle used to tx through ltp.
 * @param  ltp_if_handle the ltp nterface.
 * @return none.
 * @retval void.
*/
void AutoTestRegisterWapper(void* tx_handle, void* ltp_if_handle)
{
	if(NULL != pPatch_Ltp_AutoTestRegister)
    {
    	pPatch_Ltp_AutoTestRegister(tx_handle, ltp_if_handle);
    }
    else
    {
    	return;
    }
}

#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
/****************************************************************************/
/* void BTLTPTgtTriggerTimer                                                */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identify application context  */
/*    TLTPTimerID       timerID   : ID to identify addressed timer          */
/*    WORD              timeout_ms: new timeout for addressed timer in ms   */
/* )                                                                        */
/****************************************************************************/
void BTLTPTgtTriggerTimer(LTP_TGT_APPHANDLE AppHandle, TLTPTimerID timerID, WORD timeout_ms)
{
    ltpTimerStart(timerID, timeout_ms);
}

/****************************************************************************/
/* void BTLTPTgtHandleAsyncLTP_RESET_REQ                                    */
/* (                                                                        */
/*    LTP_TGT_APPHANDLE AppHandle : Handle to identify application context  */
/* )                                                                        */
/****************************************************************************/
void BTLTPTgtHandleAsyncLTP_RESET_REQ(LTP_TGT_APPHANDLE AppHandle)
{
    PBTLtp pBTLtp  = (PBTLtp)AppHandle;

    BTLTPHandleResetReq(pBTLtp, 0x00, NULL, 0, NULL);
}
#endif /* F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT */

