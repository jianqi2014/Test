enum { __FILE_NUM__= 0 };
/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      btltp_FreeRTOS.c
* @brief     aci iterface implementation.
* @details   none.
* @author    Tifnan
* @date      2014-10-17
* @version   v0.1                       
* *********************************************************************************************************
*/

#include <blueapi_types.h>
#include <blueapi_lib.h>
#include <blueapi.h>
#include "aci_if.h"
#include "btltp.h"
#include <trace_binary.h>
#include <trace_binary_mod.h>
#include "patch_application.h"
#include "auto_test.h"
#include "dlps_platform.h"
#include "otp.h"
#include "aci_low_power.h"
#include "aci_low_power_utils.h"

/* ltp task configuration */
#define LTP_PRIORITY             (tskIDLE_PRIORITY + 2)   /* Task priorities. */
#define LTP_STACK_SIZE           0x400

#define MAX_NUMBER_OF_RX_EVENT   0x20
#define MAX_NUMBER_OF_MESSAGE    0x20
#define LTP_RX_DISABLE_COUNT     0x400   /* Disable Rx */
#define LTP_RX_ENABLE_COUNT      0x300   /* Enable Rx */

/******************************** the define of events ltp used **********************************/

#define LTP_EVENT_UART_RX             0x01      /* data available */
#define LTP_EVENT_UART_TX             0x02      /* transmit request */
#define LTP_EVENT_UART_TX_COMPLETED   0x03      /* transmit completed */
#define LTP_EVENT_BLUEAPI_MESSAGE     0x04      /* BlueAPI message */

const uint8_t ltpEventUartRx          = LTP_EVENT_UART_RX;
const uint8_t ltpEventUartTx          = LTP_EVENT_UART_TX;
const uint8_t ltpEventUartTxCompleted = LTP_EVENT_UART_TX_COMPLETED;

/*************************************************************************************************/

static const char ltpTimer[] = "TIM_LTP";

PBTLtp  P_BtLtp SRAM_ON_BD_DATA_SECTION = NULL;

/* used to test dlps */
uint8_t EnableDlpsLog = 0;
uint8_t RxTriggerLevel = 14;

/* static function declarations */
void LtpStartDmaTransmit(IN void* pgdma_adapter);
void SpiPutBytesToTxFifo(uint8_t *p_buf, uint16_t len);

/**
 * @brief send event to ltp task.
 *
 * @param pEvent, pointer to the event to be sent.
 * @return send result.
 * @retval pdPASS--send successfully.
 *         errQUEUE_FULL-- queue is full.
*/
HAL_ROM_TEXT_SECTION
portBASE_TYPE ltpSendEvent(const unsigned char *pEvent)
{
    portBASE_TYPE ReturnValue;

    ReturnValue = xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleEvent, pEvent, 0);
    return (ReturnValue);
}

/**
 * @brief send event to ltp task in isr.
 *
 * @param pEvent, pointer to the event to b sent.
 * @return send result.
 * @retval pdPASS--send successfully.
 *         errQUEUE_FULL-- queue is full.
*/
HAL_ROM_TEXT_SECTION
portBASE_TYPE ltpSendEventFromISR(const unsigned char *pEvent)
{
    portBASE_TYPE ReturnValue;
    portBASE_TYPE TaskWoken = pdFALSE;

    ReturnValue = xQueueSendFromISR(P_BtLtp->p_aci_tcb->QueueHandleEvent, pEvent, &TaskWoken);
    portYIELD_FROM_ISR(TaskWoken);

    return (ReturnValue);
}

/****************************************************************************/
/* Send tx data event to P_BtLtp->p_aci_tcb->QueueHandleTxData                                               */
/****************************************************************************/
/**
 * @brief send in data uart isr, notify TxAssistTask to send continue.
 *
 * @param p_tx_data, pointer to the bytes buffer to be sent.
 * @return void.
*/
HAL_ROM_TEXT_SECTION
portBASE_TYPE ltpSendTxEventFromISR(TLTPData *p_tx_data)
{
    portBASE_TYPE ReturnValue;
    portBASE_TYPE TaskWoken = pdFALSE;

    ReturnValue = xQueueSendFromISR(P_BtLtp->p_aci_tcb->QueueHandleTxData, p_tx_data, &TaskWoken);
    portYIELD_FROM_ISR(TaskWoken);

    return (ReturnValue);
}

/****************************************************************************/
/**
 * @brief send to ltp task to release tx buffer space.
 *
 * @param p_tx_buf, pointer to the tx bufer to be released.
 * @return void.
*/
HAL_ROM_TEXT_SECTION
portBASE_TYPE ltpSendTxBufReleaseMsg(TLTPData *p_tx_buf)
{
    portBASE_TYPE ReturnValue;

    ReturnValue = xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleTxRel, p_tx_buf, 0);

    return (ReturnValue);
}

#if 0
/****************************************************************************/
/**
 * @brief send to ltp task to release tx buffer space in ISR.
 *
 * @param p_tx_buf, pointer to the tx bufer to be released.
 * @return void.
*/
HAL_ROM_TEXT_SECTION
static portBASE_TYPE ltpSendTxBufReleaseMsgFromISR(TLTPData *p_tx_buf)
{
    portBASE_TYPE ReturnValue;
    portBASE_TYPE TaskWoken = pdFALSE;

    ReturnValue = xQueueSendFromISR(P_BtLtp->p_aci_tcb->QueueHandleTxRel, p_tx_buf, &TaskWoken);
	portYIELD_FROM_ISR(TaskWoken);

    return (ReturnValue);
}
#endif

/**
 * @brief tx task, tx bytes in polling mode.
 *
 * @param pParameters, not used.
 * @return void.
*/
HAL_ROM_TEXT_SECTION
void TxAssistTask(void *pParameters)
{
	if(NULL != pPatch_Ltp_TxTask)
	{
		pPatch_Ltp_TxTask();
		return;
	}
	
    uint32_t i = 0;
    uint8_t *pBuffer = NULL;
    uint32_t len = 0;
	TLTPData data = {NULL, 0};
    
    if (LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface && LTP_POLLING_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode) /* uart polling mode */
    {
        while (true)
        {
            if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleTxData, &data, portMAX_DELAY) == pdPASS)
            {
                pBuffer = data.pBuffer;
                len = data.Length;
                for (i = 0; i < len; i++)
                {
                    while (1)
                    {
                        if ((UART_GetLineStatus(INDEX_DATA_UART) & TX_FIFO_SHIFT_EMPTY_BIT_MASK) == TX_FIFO_SHIFT_EMPTY)
                        {
                            break;
                        }
                    }
                    UART_Write(INDEX_DATA_UART, pBuffer++, 1);
                }
                if(pdFALSE == ltpSendEvent(&ltpEventUartTxCompleted))
                {
                	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendEvent fail", 0);
                }
                if(pdFALSE == ltpSendTxBufReleaseMsg(&data))
                {
                	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendTxBufReleaseMsg fail", 0);
                }
            }
        }
    }
    else if (LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface && LTP_INTERRUPT_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)  /* uart interrupt mode */
    {
        while (true)
        {
            if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleTxData, &P_BtLtp->p_aci_tcb->TxData, portMAX_DELAY) == pdPASS)
            {
                if (P_BtLtp->p_aci_tcb->TxData.pBuffer != (uint8_t)0)
                {
                    pBuffer = P_BtLtp->p_aci_tcb->TxData.pBuffer + P_BtLtp->p_aci_tcb->NumOfCharSent;
                    /* could be sent once */
                    if ((P_BtLtp->p_aci_tcb->TxData.Length - P_BtLtp->p_aci_tcb->NumOfCharSent) <= DATA_UART_FIFO_MAX_LENGTH)
                    {
                        UART_Write(INDEX_DATA_UART, pBuffer, P_BtLtp->p_aci_tcb->TxData.Length - P_BtLtp->p_aci_tcb->NumOfCharSent);
                        P_BtLtp->p_aci_tcb->NumOfCharSent += (P_BtLtp->p_aci_tcb->TxData.Length - P_BtLtp->p_aci_tcb->NumOfCharSent);
                    }
                    else    /* should be sent several times */
                    {
                        UART_Write(INDEX_DATA_UART, pBuffer, DATA_UART_FIFO_MAX_LENGTH);
                        P_BtLtp->p_aci_tcb->NumOfCharSent += DATA_UART_FIFO_MAX_LENGTH;
                    }
                    /* enable tx empty interrupt, wait tx completed */
                    UART_IntEnable(INDEX_DATA_UART, UART_TX_EMPTY_INT_EN);
                }
            }
        }
    }
}

/**
 * @brief start tx dma to send bytes through data uart or spis.
 *
 * @param none.
 * @return void.
*/
HAL_ROM_TEXT_SECTION
void LtpStartDmaTransmit(IN void* pgdma_adapter)
{
	if(NULL != pPatch_Ltp_StartDmaTransmit)
	{
		pPatch_Ltp_StartDmaTransmit(pgdma_adapter);
		return;
	}
	
	PLTPGDMA_ADAPTER p_gdma_adapter = (PLTPGDMA_ADAPTER)pgdma_adapter;
	TLTPData tx_data = {0};

    if (LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface) /* gdma tx through uart */
    {
    	/* gdma is sending, wait.....*/
    	if(1 == P_BtLtp->p_aci_tcb->is_gdma_working)
		{
			return;
		}
		else
		{
			if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleTxData, &tx_data, 0) == pdPASS)
        	{
	            if (NULL != tx_data.pBuffer)
	            {
	            	P_BtLtp->p_aci_tcb->TxData = tx_data;
	                p_gdma_adapter->pHalGdmaAdapter->ChSar = (uint32_t)tx_data.pBuffer;
	                p_gdma_adapter->pHalGdmaAdapter->GdmaCtl.BlockSize = tx_data.Length;
	                p_gdma_adapter->pHalGdmaOp->HalGdmaChSeting((void*)p_gdma_adapter->pHalGdmaAdapter);
	                p_gdma_adapter->pHalGdmaOp->HalGdmaChEn((void*)p_gdma_adapter->pHalGdmaAdapter);
	                P_BtLtp->p_aci_tcb->is_gdma_working = 1;
	            }
        	}
		}    
    }
    else if (LTP_IF_SPI == otp_str_data.gEfuse_Ltp_s.ltp_interface) /* gdma tx through spi*/
    {
        SpiPutBytesToTxFifo(P_BtLtp->p_aci_tcb->TxData.pBuffer, P_BtLtp->p_aci_tcb->TxData.Length);
        GPIO_Write((GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_int_pin_group, (uint32_t)otp_str_data.gEfuse_Ltp_s.spi_int_pin_index, 0);  /* pull low to notify STM32 */
        /* enable tx fifo empty interrupt */
        HAL_SSI_WRITE32(P_BtLtp->p_aci_tcb->aci_spi_handler.Index, REG_DW_SSI_IMR, HAL_SSI_READ32(P_BtLtp->p_aci_tcb->aci_spi_handler.Index, REG_DW_SSI_IMR) | 0x01);
    }
}

/**
 * @brief handle gdma interrupt.
 *
 * @param pGdmaAdapte, gdma handle adapter pointer(PGDMA_ADAPTER).
 * @return none.
 * @retval void.
*/
HAL_ROM_TEXT_SECTION
void LtpGdma0Ch0IrqHandle(IN void* pGdmaAdapte)    /* register interrupt, then run over ....*/
{
    //uint8_t isr_type_map = 0;
    
    //PLTPGDMA_ADAPTER p_gdma_adapte = (PLTPGDMA_ADAPTER)pGdmaAdapte;
    //PHAL_GDMA_ADAPTER p_hal_gdma_adapter = p_gdma_adapte->pHalGdmaAdapter;

	/* disable gdma channel */
    //p_gdma_adapte->pHalGdmaOp->HalGdmaChDis((VOID*)p_hal_gdma_adapter);

    if (ltpSendEventFromISR(&ltpEventUartTxCompleted) == pdPASS)
    {
    	/* for releasing tx buffer */
        ltpSendTxBufReleaseMsg(&P_BtLtp->p_aci_tcb->TxData);
        P_BtLtp->p_aci_tcb->TxData.Length = 0;
        P_BtLtp->p_aci_tcb->TxData.pBuffer= NULL;
    }
    //else
    {
        // queue full
    }
    //isr_type_map = p_gdma_adapte->pHalGdmaOp->HalGdmaChIsrClean((VOID*)p_hal_gdma_adapter);
}

/**
 * @brief put bytes in spi tx fifo.
 *
 * @param none.
 * @return none.
 * @retval void.
*/
HAL_ROM_TEXT_SECTION
void SpiPutBytesToTxFifo(uint8_t *p_buf, uint16_t len)
{
	P_BtLtp->p_aci_tcb->aci_spi_handler.tx_buf = (uint16_t*)p_buf;
	P_BtLtp->p_aci_tcb->aci_spi_handler.tx_len = len;
	/* can not exceed spi tx fifo length!! */
    SPI_BurstWrite((void*)&P_BtLtp->p_aci_tcb->aci_spi_handler);
}

/**
 * @brief update rx data length when received data from uart or spi.
 *
 * @param none.
 * @return none.
 * @retval void.
*/

HAL_ROM_TEXT_SECTION
void LtpRxDataLengthUpdate(void)
{
    uint16_t RxOffset;
    uint16_t Length;

    RxOffset = P_BtLtp->p_aci_tcb->P_RxBuffer - &P_BtLtp->p_aci_tcb->p_rx_buf[0]; /* tifnan: num of char received */

    /* will not occur in our uart framework!!! */
    if (P_BtLtp->p_aci_tcb->RxOffset == RxOffset)
    {
        if (P_BtLtp->p_aci_tcb->RxDataLength == otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)  /* overrun */
        {
			DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LtpRxDataLengthUpdate: Rx overrun", 0);
            P_BtLtp->p_aci_tcb->RxDataLength = 0;
            Length = otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size;
        }
        else
        {
            return;       /* no data */
        }
    }
    else
    {
        /* [p_aci_tcb->RxOffset----RxBufferSize-1] + [P_BtLtp->p_aci_tcb->p_rx_buf[0]----RxOffset] */
        if (P_BtLtp->p_aci_tcb->RxOffset > RxOffset)
        {
            Length = otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - P_BtLtp->p_aci_tcb->RxOffset + RxOffset;
        }
        /* [p_aci_tcb->RxOffset ---- RxOffset] */
        else
        {
            Length = RxOffset - P_BtLtp->p_aci_tcb->RxOffset;
        }

        /* update new P_BtLtp->p_aci_tcb->RxOffset */
        P_BtLtp->p_aci_tcb->RxOffset = RxOffset;
    }

    if ((Length + P_BtLtp->p_aci_tcb->RxDataLength) > otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)   /* Rx overrun */
    {
        DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LtpRxDataLengthUpdate: Rx overrun (%d)", 1,\
        	Length + P_BtLtp->p_aci_tcb->RxDataLength);

        P_BtLtp->p_aci_tcb->RxDataLength  = otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size;
        P_BtLtp->p_aci_tcb->RxWriteIndex += Length;
        P_BtLtp->p_aci_tcb->RxWriteIndex &= (otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - 1);
        P_BtLtp->p_aci_tcb->RxReadIndex   = P_BtLtp->p_aci_tcb->RxWriteIndex;
    }
    else
    {
        P_BtLtp->p_aci_tcb->RxDataLength += Length;         /* update length */
        P_BtLtp->p_aci_tcb->RxWriteIndex += Length;
        P_BtLtp->p_aci_tcb->RxWriteIndex &= (otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - 1);
    }

    /* tifnan: bee use auto flow control */
    /*if (P_BtLtp->p_aci_tcb->RxDataLength >= LTP_RX_DISABLE_COUNT &&
        P_BtLtp->p_aci_tcb->RxDisabled == false)
    {
      ltpRxDisable();
    }*/
}

/**
 * @brief uart interrupt handle ISR.
 *
 * @param none.
 * @return none.
 * @retval void.
*/
HAL_ROM_TEXT_SECTION
void LtpDataUartIrqHandle(void)
{
    /* read interrupt status */
    UINT32 int_status;
    UINT32 int_en;
    TLTPData rx_data;
    uint16_t len = 0;
    //uint8_t i = 0;
    uint32_t reg_val = 0;

    /* get interrupt config value */
    int_en = UART_GetIntEnConfig(INDEX_DATA_UART);
    /* read interrupt id */
    int_status = UART_GetIntStatus(INDEX_DATA_UART);
    /* disable all uart interrupts */
    UART_IntDisable(INDEX_DATA_UART, UART_INT_ALL_DIS);

    switch (int_status & 0x0E)
    {
    /* tx fifo empty */
    case 0x02:
        if (LTP_INTERRUPT_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode && LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface)
        {
            /* send compeleted */
            if (P_BtLtp->p_aci_tcb->TxData.Length == P_BtLtp->p_aci_tcb->NumOfCharSent)
            {
                P_BtLtp->p_aci_tcb->NumOfCharSent = 0;
                if(pdFALSE == ltpSendEventFromISR(&ltpEventUartTxCompleted))
                {
                	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendEventFromISR fail", 0);
                }
                //ltpSendTxBufReleaseMsgFromISR(P_BtLtp->p_aci_tcb->TxData);	/* to be modify */
            }
            else
            {
                rx_data = P_BtLtp->p_aci_tcb->TxData;
                ltpSendTxEventFromISR(&rx_data);
            }
        }
        /* tx empty interrupt disable */
        UART_IntEnable(INDEX_DATA_UART, int_en & UART_TX_EMPTY_INT_DIS);
        break;

    /* rx data valiable */
    case 0x04:
        if((P_BtLtp->p_aci_tcb->P_RxBuffer - &P_BtLtp->p_aci_tcb->p_rx_buf[0] + RxTriggerLevel)\
            <= otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)
        {
            UART_Read(INDEX_DATA_UART, P_BtLtp->p_aci_tcb->P_RxBuffer, RxTriggerLevel);
#if 0	/* for debug */
            //DBG_DIRECT("P_BtLtp->p_aci_tcb->P_RxBuffer = 0x%8x\n", P_BtLtp->p_aci_tcb->P_RxBuffer);
            for(i = 0; i < 8; i++)
            {
            	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "receive data[rx avaiable][0x%8x] = 0x%2x\t", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i));
            	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "receive data[x%8x] = 0x%x\n", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i);
            	if(i == 7)
            	{
            		reg_val = UART_GetLineStatus(INDEX_DATA_UART);
        			DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Line status register: 0x%2x!!!\n", 1, reg_val);
            		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            		//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            	}
            }
#endif
            P_BtLtp->p_aci_tcb->P_RxBuffer += RxTriggerLevel;
        }
        else
        {
            len = otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - (P_BtLtp->p_aci_tcb->P_RxBuffer - &P_BtLtp->p_aci_tcb->p_rx_buf[0]);
            UART_Read(INDEX_DATA_UART, P_BtLtp->p_aci_tcb->P_RxBuffer, len);
#if 0	/* for debug */
            //DBG_DIRECT("P_BtLtp->p_aci_tcb->P_RxBuffer(part 1) = 0x%8x\n", P_BtLtp->p_aci_tcb->P_RxBuffer);
            for(i = 0; i < len; i++)
            {
            	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "receive data[rx avaiable][0x%8x] = 0x%2x\t", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i));
            	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "receive data[x%8x] = 0x%x\n", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i);
            	if(i == (len-1))
            	{
            	    reg_val = UART_GetLineStatus(INDEX_DATA_UART);
        			DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Line status register: 0x%2x!!!\n", 1, reg_val);
            		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            		//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            	}
            }
#endif  
			P_BtLtp->p_aci_tcb->P_RxBuffer = &P_BtLtp->p_aci_tcb->p_rx_buf[0];
            UART_Read(INDEX_DATA_UART, P_BtLtp->p_aci_tcb->P_RxBuffer, RxTriggerLevel - len);
#if 0	/* for debug */
			//DBG_DIRECT("P_BtLtp->p_aci_tcb->P_RxBuffer(part 1) = 0x%8x\n", P_BtLtp->p_aci_tcb->P_RxBuffer);
			for(i = 0; i < (8 - len); i++)
			{
				DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "receive data[0x%8x] = 0x%2x\t", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i));
				//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "receive data[x%8x] = 0x%x\n", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i);
				if(i == (8 - len -1))
            	{
            		reg_val = UART_GetLineStatus(INDEX_DATA_UART);
        			DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Line status register: 0x%2x!!!\n", 1, reg_val);
            		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            		//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
            	}
			}
#endif 
            P_BtLtp->p_aci_tcb->P_RxBuffer += (RxTriggerLevel - len); 
        }
        
        /* update rx data length */
        LtpRxDataLengthUpdate();
        /* notify ltp task */
        if(pdFALSE == ltpSendEventFromISR(&ltpEventUartRx))
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendEventFromISR fail", 0);
        }

        /* enable data uart interrupt again */
        UART_IntEnable(INDEX_DATA_UART, int_en);
        break;

    /* rx time out */
    case 0x0c:
        /* read out all bytes in fifo */
        while (UART_GetLineStatus(INDEX_DATA_UART) & 0x01)
        {
        	if(P_BtLtp->p_aci_tcb->P_RxBuffer - &P_BtLtp->p_aci_tcb->p_rx_buf[0] == otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)
        	{
        		P_BtLtp->p_aci_tcb->P_RxBuffer = &P_BtLtp->p_aci_tcb->p_rx_buf[0];
        	}
        	
            UART_Read(INDEX_DATA_UART, P_BtLtp->p_aci_tcb->P_RxBuffer, 1);
#if 0	/* for debug */
				DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "receive data[timeout][0x%8x] = 0x%2x\t", 2, P_BtLtp->p_aci_tcb->P_RxBuffer, *(P_BtLtp->p_aci_tcb->P_RxBuffer));
				reg_val = UART_GetLineStatus(INDEX_DATA_UART);
        		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Line status register: 0x%2x!!!\n", 1, reg_val);
				//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,	"receive data[x%8x] = 0x%x\n", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i);
#endif     
			P_BtLtp->p_aci_tcb->P_RxBuffer++;       
        }
        
        /* update rx data length */
        LtpRxDataLengthUpdate();
        /* notify ltp task */
        if(pdFALSE == ltpSendEventFromISR(&ltpEventUartRx))
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendEventFromISR fail", 0);
        }

        /* enable data uart interrupt again */
        UART_IntEnable(INDEX_DATA_UART, int_en);
        break;

    /* receive line status interrupt */
    case 0x06:
        reg_val = UART_GetLineStatus(INDEX_DATA_UART);
        DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Line status errorXXX: 0x%x!!!\n", 1, reg_val);
        UART_IntEnable(INDEX_DATA_UART, int_en);
        break;

    default:
        //UART_GetStatus(INDEX_DATA_UART);  /* no this register in dada uart*/
        UART_GetLineStatus(INDEX_DATA_UART);
        UART_IntEnable(INDEX_DATA_UART, int_en);
        break;
    }
}

/**
 * @brief spi interrupt handle ISR.
 *
 * @param data, not used.
 * @return void. 
*/
HAL_ROM_TEXT_SECTION
void AciSpiIrqHandle(IN void *data)
{
    UINT32 int_status = 0;
    UINT16 count = 0;   /* the number of bytes in spi rx fifo */
    UINT32 reg_val = 0;
    UINT32 i = 0;

    int_status = SPI_GetInterruptStatus((VOID*)&P_BtLtp->p_aci_tcb->aci_spi_handler);

    /* Transmit FIFO Overflow Interrupt Status */
    if (int_status & BIT_ISR_TXOIS)
    {
        HAL_SSI_READ32(0, REG_DW_SSI_TXOICR);
    }
    /* Receive FIFO Underflow Interrupt Status, generated when read from an empty receive FIFO */
    if (int_status & BIT_ISR_RXUIS)
    {
        HAL_SSI_READ32(0, REG_DW_SSI_RXUICR);
    }
    /* Receive FIFO Overflow Interrupt Status */
    if (int_status & BIT_ISR_RXOIS)
    {
        HAL_SSI_READ32(0, REG_DW_SSI_RXOICR);
    }
    /* Transmit FIFO Empty Interrupt Status */
    if (int_status & BIT_ISR_TXEIS)
    {
        /* transfer done... */
        GPIO_Write((GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_int_pin_group, (uint32_t)otp_str_data.gEfuse_Ltp_s.spi_int_pin_index, 1);  /* pull high to notify STM32 */
        /* disable tx fifo empty interrupt */
        HAL_SSI_WRITE32(P_BtLtp->p_aci_tcb->aci_spi_handler.Index, REG_DW_SSI_IMR, HAL_SSI_READ32(P_BtLtp->p_aci_tcb->aci_spi_handler.Index, REG_DW_SSI_IMR) & 0xfe);
    }

    /* Multi-Master Contention Interrupt */
    if (int_status & BIT_ISR_MSTIS)
    {
        /* HAL_SSI_READ32(0, REG_DW_SSI_MSTICR); */
    }

    /* Receive FIFO Full Interrupt Status,
            generater when receive FIFO equal to or above its threshold value plus 1 */
    if ((int_status & BIT_ISR_RXFIS) )
    {
        /* RsvdMemForRx_Index_Local = RsvdMemForRx_Index; */
        reg_val = SPI_GetStatus((VOID*)&P_BtLtp->p_aci_tcb->aci_spi_handler) & BIT_SR_RFNE;    /* 1 ¡§C Receive FIFO is not empty */

        while (reg_val)
        {
            /* Rx Fifo Not Empty */
            count = SPI_Get_RX_FIFO_Len((VOID*)&P_BtLtp->p_aci_tcb->aci_spi_handler);
            if (count == 0)
            {
                return;
            }
            /* read all data out */
            for (i = 0; i < count; i++)
            {
                *P_BtLtp->p_aci_tcb->P_RxBuffer++ = SPI_Read((VOID*)&P_BtLtp->p_aci_tcb->aci_spi_handler, SPI_READ_SINGLE_BYTE); /* signal byte or two bytes? */
                if ((P_BtLtp->p_aci_tcb->P_RxBuffer - &P_BtLtp->p_aci_tcb->p_rx_buf[0]) == otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)
                {
                    P_BtLtp->p_aci_tcb->P_RxBuffer = &P_BtLtp->p_aci_tcb->p_rx_buf[0];
                }
            }
            reg_val = SPI_GetStatus((VOID*)&P_BtLtp->p_aci_tcb->aci_spi_handler) & BIT_SR_RFNE;    /* 1 ¡§C Receive FIFO is not empty */
        }
        /* update rx data length */
        LtpRxDataLengthUpdate();
        /* notify ltp task */
        if(pdFALSE == ltpSendEventFromISR(&ltpEventUartRx))
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "ltpSendEventFromISR fail", 0);
        }
    }

}

/**
 * @brief init ltp peripheral, uart or spi.
 *
 * @param none.
 * @return none. 
 * @retal void
*/
HAL_ROM_TEXT_SECTION
void ltpPeripheralInit(void)
{
	/* uart */
	UartAdapter adp;
	/* spi */
	IRQ_HANDLE   SpiIrqHandle;
	GPIO_Initialize_Param gpio_param;
	DriverModule_SPI_Params spi_slave_Param;
	
    /* ACI via uart */
    if (LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface)
    {	
        adp.uart_index = INDEX_DATA_UART;
        adp.data_length = DATA_UART_DATA_LEN_8BIT;
        //adp.baud_rate = otp_str_data.gEfuse_Ltp_s.ltp_uart_baudrate;
        adp.baud_fix_params.div = otp_str_data.gEfuse_Ltp_s.uart_calibration_div;
        adp.baud_fix_params.ovsr = otp_str_data.gEfuse_Ltp_s.uart_calibration_ovsr;
        adp.baud_fix_params.ovsr_adj = otp_str_data.gEfuse_Ltp_s.uart_calibration_ovsr_adj;
        adp.int_control = UART_RX_DATA_INT_EN | UART_RX_LINE_INT_EN;
        adp.fifo_en = UART_FIFO_ENABLE;
        adp.rx_fifo_trigger_level = UART_RX_IT_TR_LEVEL_14BYTE;
        adp.parity = UART_PARITY_DISABLE;
        adp.stop_bits = DATA_UART_STOP_1BIT;
        
        if(otp_str_data.gEfuse_Ltp_s.ltp_uart_flow_control_en)
        {
        	adp.flow_control = AUTO_FLOW_ENABLE;
        }
        else
        {
        	adp.flow_control = AUTO_FLOW_DISABLE;
        }
        
        if(LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
        {
        	adp.dma_mode = DATA_UART_DMA_ENABLE;
        }
        else
        {
        	adp.dma_mode = DATA_UART_DMA_DISABLE;
        }

#ifdef CONFIG_NEW_PINMUX
		adp.tx_pinmux.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.uart_tx_pin_group;
		adp.tx_pinmux.gpio_pin_index  	= (uint8_t)otp_str_data.gEfuse_Ltp_s.uart_tx_pin_index;
		adp.rx_pinmux.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.uart_rx_pin_group;
		adp.rx_pinmux.gpio_pin_index  	= (uint8_t)otp_str_data.gEfuse_Ltp_s.uart_rx_pin_index;
		adp.cts_pinmux.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.uart_cts_pin_group;
		adp.cts_pinmux.gpio_pin_index  	= (uint8_t)otp_str_data.gEfuse_Ltp_s.uart_cts_pin_index;
		adp.rts_pinmux.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.uart_rts_pin_group;
		adp.rts_pinmux.gpio_pin_index  	= (uint8_t)otp_str_data.gEfuse_Ltp_s.uart_rts_pin_index;
#endif

		/* irq settings */
		adp.irq_handle.IrqNum = DATA_UART_IRQ;
        adp.irq_handle.IrqFun = (IRQ_FUN) LtpDataUartIrqHandle;
        adp.irq_handle.Priority = 0;	/* must highest priority */

		/* rx pin wake up settings */
		if(otp_str_data.gEfuse_Ltp_s.ltp_wake_up_pin_en)
        {
        	adp.en_rx_wakeup = ENABLE_USE_DATA_UART_RX_PIN_WAKEUP;
        }
        else
        {
        	adp.en_rx_wakeup = DISABLE_USE_DATA_UART_RX_PIN_WAKEUP;
        }
		
#if 0
	    DBG_DIRECT("ltpPeripheralInit, adp.baud_rate = 0x%x", adp.baud_rate);
	    DBG_DIRECT("ltpPeripheralInit, adp.data_length = 0x%x", adp.data_length);
	    DBG_DIRECT("ltpPeripheralInit, adp.stop_bits = 0x%x", adp.stop_bits);
	    DBG_DIRECT("ltpPeripheralInit, adp.parity = 0x%x", adp.parity);
	    DBG_DIRECT("ltpPeripheralInit, adp.fifo_en = 0x%x", adp.fifo_en);
	    DBG_DIRECT("ltpPeripheralInit, adp.rx_fifo_trigger_level = 0x%x", adp.rx_fifo_trigger_level);
	    DBG_DIRECT("ltpPeripheralInit, adp.dma_mode = 0x%x", adp.dma_mode);
	    DBG_DIRECT("ltpPeripheralInit, adp.flow_control = 0x%x", adp.flow_control);
	    DBG_DIRECT("ltpPeripheralInit, adp.int_control = 0x%x", adp.int_control);
	    DBG_DIRECT("ltpPeripheralInit, adp.irq_handle.IrqNum = 0x%x", adp.irq_handle.IrqNum);
	    DBG_DIRECT("ltpPeripheralInit, adp.irq_handle.Priority = 0x%x", adp.irq_handle.Priority);
#endif

        /* data uart init */
        if(!UART_Initialize((void*)&adp))
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Ltp uart init failed", 0);
        }
    }
    else if (LTP_IF_SPI == otp_str_data.gEfuse_Ltp_s.ltp_interface)  /* ACI via spi */
    {    
        /* init INT pin, pull low when having data to send */
        gpio_param.GPIOGroup = (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_int_pin_group;
        gpio_param.GPIOIndex = (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_int_pin_index;
        gpio_param.GPIOMode  = GPIO_PIN_STATUS_INITIALIZED_GPIO_OUT;
        GPIO_Initialize(&gpio_param);
        GPIO_Write((GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_int_pin_group,
        				(uint32_t)otp_str_data.gEfuse_Ltp_s.spi_int_pin_index, 1);  /* pull high firstly */

        /* spi slave parameters */
        spi_slave_Param.spi_index         = otp_str_data.gEfuse_Ltp_s.spi_select;
        spi_slave_Param.devicerole        = SSI_SLAVE;
        spi_slave_Param.spi_speed		  = 1000000;	/* 1M speed */
        spi_slave_Param.data_frame_size   = DFS_8_BITS;
        spi_slave_Param.data_frame_format = FRF_MOTOROLA_SPI;
        spi_slave_Param.data_transfermode = TMOD_TR;
        spi_slave_Param.sclk_pol          = SCPOL_INACTIVE_IS_HIGH;
        spi_slave_Param.sclk_phase        = SCPH_TOGGLES_IN_MIDDLE;
        spi_slave_Param.SlaveOutputEnable = SLV_TXD_ENABLE;
        spi_slave_Param.InterruptMask     = 0x3C;   /* tx fifo empty masked */
        spi_slave_Param.TxThresholdLevel  = 0;
        spi_slave_Param.RxThresholdLevel  = 0;
        spi_slave_Param.ControlFrameSize  = CFS_1_BIT;

        spi_slave_Param.pin_assignment_clk.gpio_group		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_clk_pin_group;
        spi_slave_Param.pin_assignment_clk.gpio_pin_index 	= (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_clk_pin_index;
        spi_slave_Param.pin_assignment_mosi.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_mosi_pin_group;
        spi_slave_Param.pin_assignment_mosi.gpio_pin_index 	= (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_mosi_pin_index;
        spi_slave_Param.pin_assignment_miso.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_miso_pin_group;
        spi_slave_Param.pin_assignment_miso.gpio_pin_index 	= (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_miso_pin_index;
        spi_slave_Param.pin_assignment_cs0.gpio_group 		= (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_cs_pin_group;
        spi_slave_Param.pin_assignment_cs0.gpio_pin_index 	= (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_cs_pin_index;

        SpiIrqHandle.IrqFun = (IRQ_FUN)AciSpiIrqHandle;
        SpiIrqHandle.Priority = 2;
        if(0 == spi_slave_Param.spi_index)
        {
        	SpiIrqHandle.IrqNum   = SPI0_IRQ;
        }
        else if(1 == spi_slave_Param.spi_index)
        {
        	SpiIrqHandle.IrqNum   = SPI1_IRQ;
        }
        else
        {
        	//wrong spi index
        }
        
        //InterruptRegister(&SsiIrqHandle_Slave);     /* must use, if have data to send to isr */
        InterruptEn(&SpiIrqHandle);

        SPI_Initialize(&spi_slave_Param, &P_BtLtp->p_aci_tcb->aci_spi_handler);

        /* enable cs pin for interrupt */
        gpio_param.GPIOGroup = (GPIOGroupDef)otp_str_data.gEfuse_Ltp_s.spi_cs_pin_group;
        gpio_param.GPIOIndex = (uint8_t)otp_str_data.gEfuse_Ltp_s.spi_cs_pin_index;
        gpio_param.GPIOMode  = GPIO_PIN_STATUS_INITIALIZED_INT;   /* only GPIOA can be interrupt pin */
        gpio_param.GPIOPull  = GPIO_PULL_MODE_PULL_UP;
        gpio_param.GPIOMode  = (GPIOPinStatus)GPIO_MODE_INT;
        gpio_param.INTConfiguration.INT_Enabler  = GPIO_INT_ENABLE;
        gpio_param.INTConfiguration.INT_Level    = GPIO_INT_EDGE_SENSITIVE;
        gpio_param.INTConfiguration.INT_Polarity = GPIO_INT_POLARITY_ACTIVE_LOW;    /* interrupt when low */
        gpio_param.INTConfiguration.INT_Debounce = GPIO_INT_DEBOUNCE_ENABLE;
        GPIO_Initialize(&gpio_param);
    }

    if(LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
	{
		LtpGdmaInit((void*)&P_BtLtp->p_aci_tcb->LtpGdmaAdapterTx);
	}

    if(NULL != pPatch_Ltp_ReInit_Peripheral)
    {
    	pPatch_Ltp_ReInit_Peripheral((void*)&adp, (void*)&SpiIrqHandle, (void*)&gpio_param, (void*)&spi_slave_Param);
    }
}

/**
 * @brief handle message from upper stack.
 *
 * @param pMsg --message pointer from upper stack.
 * @return none. 
 * @retal void
*/
HAL_ROM_TEXT_SECTION
void ltpHandleBlueAPIMessage(PBlueAPI_UsMessage pMsg)
{
    BOOL             release = FALSE;
    LPBYTE           pBuffer;
    PBlueAPI_UsMessage pOldMsg = (PBlueAPI_UsMessage)0;

    /* patch for ltpHandleBlueAPIMessage */
    if(NULL != pPatch_Ltp_HandleBlueAPIMessage)
    {
       pPatch_Ltp_HandleBlueAPIMessage(&pMsg, &pOldMsg, &pBuffer, &release);
       return;
    }

    switch (pMsg->Command)
    {
    case blueAPI_EventActInfo: /*-------------------------------------------*/
        P_BtLtp->LTP_US_OfflinePoolID = pMsg->p.ActInfo.systemPoolID;
        P_BtLtp->LTP_PoolID = pMsg->p.ActInfo.systemPoolID;
        break;
#if 0
    case blueAPI_EventGATTAttributeUpdateRsp: /*----------------------------*/
    case blueAPI_EventGATTAttributeWriteInd: /*-----------------------------*/
    case blueAPI_EventGATTDiscoveryInd: /*----------------------------------*/
    case blueAPI_EventGATTAttributeReadRsp: /*------------------------------*/
    case blueAPI_EventGATTAttributeInd: /*----------------------------------*/
    case blueAPI_EventGATTAttributeNotificationInfo: /*---------------------*/
    case blueAPI_EventGATTCCCDInfo: /*--------------------------------------*/
        /* these are OSIF buffers and must be released after use */
        /* rs232api doesn't know about OSIF */
        /* => malloc & copy here, free OSIF buffer now */
        //pBuffer = pvPortMalloc(pMsg->Length);
        pBuffer = pvPortMalloc(pMsg->Length, RAM_TYPE_DATA_OFF);	//needed here ??
        if (NULL == pBuffer)
        {
            DebuggerBreak();
        }
        release = TRUE;

        memcpy(pBuffer, pMsg, pMsg->Length);

        /* free osif buffer */
        blueAPI_BufferRelease(pMsg);

        pMsg = (PBlueAPI_UsMessage)pBuffer;
        
        break;
#endif
    default: /*-------------------------------------------------------------*/
        break;
    }

    release &= BTLTPHandleBLUE_API_MSG(P_BtLtp, (LPBYTE)pMsg, 0);

#if 0
    /* In case the DataInd / DataRsp were not transmitted via LTP, free them here */
    if (release)
    {
        //vPortFree(pBuffer);
        vPortFree(pBuffer, RAM_TYPE_DATA_OFF);  /* tifnan: new ram free function */
    }
#endif

    if (pOldMsg != (PBlueAPI_UsMessage)0)
    {
        pMsg = pOldMsg;
    }

    release = TRUE;
    
#if 0
    switch (pMsg->Command)
    {
    case blueAPI_EventGATTAttributeUpdateRsp:
    case blueAPI_EventGATTAttributeWriteInd:
    case blueAPI_EventGATTDiscoveryInd:
    case blueAPI_EventGATTAttributeReadRsp:
    case blueAPI_EventGATTAttributeInd:
    case blueAPI_EventGATTAttributeNotificationInfo:
    case blueAPI_EventGATTCCCDInfo:
        /* buffer must be freed by application (via blueAPI_BufferRelease) */
        release = FALSE;
        break;
    default: /*---------------------------------------------------------*/
        break;
    }
#endif
	
    if (release)
    {
        /* release messages that are allocated in blueAPI_TgtSendEvent */
        /* osBufferRelease((LPVOID)pMsg);                              */
        blueAPI_BufferRelease(pMsg);
    }
}


/**
 * @brief callback function, upper stack will call it to send message to ltp.
 *
 * @param pMsg --message pointer from upper stack.
 * @return none. 
 * @retal void
*/
HAL_ROM_TEXT_SECTION
void ltpBlueAPICallback(PBlueAPI_UsMessage pMsg)
{
    unsigned char Event = LTP_EVENT_BLUEAPI_MESSAGE;

    if (xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleMessage, &pMsg, 0) == errQUEUE_FULL)
    {
        BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                               "ltpBlueAPICallback: MessageQueue full");

        blueAPI_BufferRelease(pMsg);
    }
    else
    {
        if (ltpSendEvent(&Event) == errQUEUE_FULL)     /* signal event to GATTDEMO task */
        {
            BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                                   "ltpBlueAPICallback: EventQueue full");
        }
    }
}


/**
 * @brief time out routine, not used now .
 *
 * @param xTimer --time handle.
 * @return none. 
 * @retal void
*/
#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
HAL_ROM_TEXT_SECTION
void ltpTimeoutRoutine(xTimerHandle xTimer)
{
    P_BtLtp->p_aci_tcb->ltpTimerMS = 0;
    LTPLibHandleTimeout(&P_BtLtp->LTPLib, (TLTPTimerID)P_BtLtp->p_aci_tcb->ltpTimerID);
}
#endif

/****************************************************************************/
/* TASK                                                                     */
/****************************************************************************/
SRAM_ON_BD_DATA_SECTION
xTaskHandle LTPTaskHandle = NULL;
SRAM_ON_BD_DATA_SECTION
xTaskHandle LTPTxAssistHandle = NULL;

/**
 * @brief ltp task implementation .
 *
 * @param pParameters --task parameters, no used in ltp task.
 * @return none. 
 * @retal void
*/
HAL_ROM_TEXT_SECTION
void ltpTask(void *pParameters)
{
    int  loop;
    char Event;

	if(NULL != pPatch_Ltp_Task)
	{
		/* will not return */
		pPatch_Ltp_Task();
	}
    
    /* register auto test module, because user app is init after bee task init */
	AutoTestRegisterWapper((void*)P_BtLtp, (void*)P_BtLtp->p_aci_tcb);

	/* init uart or spi */
    ltpPeripheralInit();

    P_BtLtp->State = btltpStateInit;

    for (loop = 0; loop < BTLTP_QUEUE_ELEMENT_COUNT; loop++)
    {
        ltpQueueIn(&P_BtLtp->FreeElementQueue, &P_BtLtp->ElementPool[loop]);
    }

    for (loop = 0; loop < BTLTP_ACTION_POOL_SIZE; loop++)
    {
        P_BtLtp->ActionPool[loop].Action = btltpActionNotUsed;
    }

    P_BtLtp->pBufferAction = NULL; /* no action pending */

    LTPLibInitialize(&P_BtLtp->LTPLib,
                     (LTP_TGT_APPHANDLE)P_BtLtp,
                     //BTLTP_US_BUFFER_OFFSET,
                     0,   /* tifnan */
                     //BTLTP_US_BUFFER_SIZE + LTP_DATA_MIN_HEADER_LENGTH,
                     200, /* tifnan */
                     0
                    );

    /* do not register stack now in these two modes */
	if(!otp_str_data.gEfuse_Ltp_s.auto_test_app
		&& !otp_str_data.gEfuse_Ltp_s.aci_en)
	{
		blueAPI_RegisterReq(P_BtLtp, (void *)ltpBlueAPICallback);
	}
    
    P_BtLtp->State = btltpStateIdle; /* not use !!*/

    while (true)
    {
    	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Ltp is alive!!!!",0);
        if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleEvent, &Event, portMAX_DELAY) == pdPASS)
        {
            switch (Event)
            {
            case LTP_EVENT_UART_RX:          /* RxData available */
                {
                    uint32_t RxDataLength;
                    uint16_t RxReadIndex;

                    taskENTER_CRITICAL();
                    /* skip data filed in handling */
                    RxDataLength = P_BtLtp->p_aci_tcb->RxDataLength - P_BtLtp->p_aci_tcb->RxDataIndication;
                    taskEXIT_CRITICAL();
                    RxReadIndex  = P_BtLtp->p_aci_tcb->RxReadIndex + P_BtLtp->p_aci_tcb->RxDataIndication;
                    RxReadIndex &= (otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - 1);

                    while (RxDataLength)
                    {
                        TLTPData RxData;

                        /* exceed rx buffer tail */
                        if ((RxReadIndex + RxDataLength) > otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size)
                        {
                            RxData.Length = otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - RxReadIndex;
                        }
                        else
                        {
                            RxData.Length = RxDataLength;
                        }
                        RxData.pBuffer = &P_BtLtp->p_aci_tcb->p_rx_buf[RxReadIndex];
						/* DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTP_EVENT_UART_RX: RxData.pBuffer = [0x%8x], RxData.Length= 0x%4x\t",\
							2, RxData.pBuffer, RxData.Length); */
                        if (xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleRxData, &RxData, 0) == pdPASS)
                        {
                            P_BtLtp->p_aci_tcb->RxDataIndication += RxData.Length;
                            /* LTPLibHandleReceiveData return when all data in RxData has been copied */
                            if (!LTPLibHandleReceiveData(&P_BtLtp->LTPLib, RxData.pBuffer, RxData.Length, 0))
                            {
                                LtpBufferRelease(RxData.pBuffer);
                            }

                            RxDataLength -= RxData.Length;
                            RxReadIndex  += RxData.Length;
                            RxReadIndex  &= (otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - 1);
                        }
                        else
                        {
                        	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LTP_EVENT_UART_RX, xQueueSend fail", 0);
                            break;
                        }
                    }
                    break;
                }
            case LTP_EVENT_UART_TX:
                if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
                {
                	/* used only in dma mode */
                    LtpStartDmaTransmit((void*)&P_BtLtp->p_aci_tcb->LtpGdmaAdapterTx);
                }
                break;

            case LTP_EVENT_UART_TX_COMPLETED:          /* transmit completed */
                {
                    THandle Handle;
                    TLTPData data;

              		if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleTxRel, &data, 0) == pdPASS)
                    {
						P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx += data.Length;
						P_BtLtp->p_aci_tcb->tx_mem_tcb.free_size += data.Length;

						if(P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx > otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size)
						{
							//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Free1:tx idx = 0x%4x", 1, P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx);
							P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx = data.Length;
							P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size = 0;
						}
                        else if(P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx == otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size)
						{
							//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Free1:tx idx = 0x%4x", 1, P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx);
							P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx = 0;
							P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size = 0;
						} 
						
						DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Free2:tx idx = 0x%4x, free idx = 0x%4x\t, tx_un_used_size = 0x%4x\t", 3,\
                    		P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_blk_idx,\
                    		P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_free_blk_idx,\
                    		P_BtLtp->p_aci_tcb->tx_mem_tcb.tx_un_used_size);
                    }

                    /* reset */
                    if (P_BtLtp->pBufferAction->Action == btltpActionReset)
                    {
                        Handle.lpHandle       = (LPVOID)P_BtLtp->pBufferAction;
                        BTLTPBufferCallback(Handle);
                        P_BtLtp->pBufferAction->Action = btltpActionNotUsed;
                        P_BtLtp->pBufferAction = NULL;
                    }

                    if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
                    {
                    	/* gdma tx completed, can enter dlsp */
        				P_BtLtp->p_aci_tcb->is_gdma_working = 0;
        				/* transmit again */
                        LtpStartDmaTransmit((void*)&P_BtLtp->p_aci_tcb->LtpGdmaAdapterTx);
                    }
                    break;
                }
            case LTP_EVENT_BLUEAPI_MESSAGE:            /* BlueAPI */
                {
                    PBlueAPI_UsMessage pMsg;

                    while (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleMessage, &pMsg, 0) == pdPASS)
                    {
                        ltpHandleBlueAPIMessage(pMsg);
                    }
                    break;
                }
            
            default:
                BLUEAPI_TRACE_PRINTF_1(BLUEAPI_TRACE_MASK_TRACE,
                                       "ltpTask: Unknown event (%d)", Event);
                DebuggerBreak();
                break;
            }
        }
    }
}

/**
 * @brief dlps callback function, used when bee is to enter dlps .
 *
 * @param none.
 * @return the check result. 
 * @retal  TRUE -- can enter dlps.
 			FALSE --can not enter dlps.
*/
#ifdef CONFIG_DLPS_EN
/* for test */
uint8_t CanEnterDlps = 1;
BOOL LtpDlpsEnterCheck(void)
{
	if( NULL != pPatch_Ltp_DlpsEnterCheck)
	{
		return pPatch_Ltp_DlpsEnterCheck();
	}
	
	uint16_t heap_struct_size = ((sizeof(BlockLink_t) + ( portBYTE_ALIGNMENT - 1)) & ~portBYTE_ALIGNMENT_MASK);
	if(CanEnterDlps)
	{
		/* check all queues are all empty */
		if(32 != uxQueueSpacesAvailable(P_BtLtp->p_aci_tcb->QueueHandleEvent)
			&& 12 != uxQueueSpacesAvailable(P_BtLtp->p_aci_tcb->QueueHandleTxData)
			&& 12 != uxQueueSpacesAvailable(P_BtLtp->p_aci_tcb->QueueHandleRxData)
			&& 12 != uxQueueSpacesAvailable(P_BtLtp->p_aci_tcb->QueueHandleTxRel)
			&& MAX_NUMBER_OF_MESSAGE != uxQueueSpacesAvailable(P_BtLtp->p_aci_tcb->QueueHandleMessage))
		{
			DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Ltp queue is not empty!", 0);
			return FALSE;
		}
		
		/* gdma is working now */
		if(P_BtLtp->p_aci_tcb->is_gdma_working && LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
		{
			DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Ltp dma is working!", 0);
			return FALSE;
		}
		
		/* enable save dynamically allocated off area ram info, to be checked! */
		if(1 == otp_str_data.gEfuse_Ltp_s.ltp_off_ram_save)
		{
			if(NULL != P_BtLtp->p_aci_tcb->p_rx_buf)
			{
				if(!DLPS_BUFFER_REG(P_BtLtp->p_aci_tcb->p_rx_buf - heap_struct_size, heap_struct_size, TRUE))
				{
					return FALSE;
				}
			}
			
			if(NULL != P_BtLtp->p_aci_tcb->p_tx_buf)
			{
				if(!DLPS_BUFFER_REG(P_BtLtp->p_aci_tcb->p_tx_buf - heap_struct_size, heap_struct_size, TRUE))
				{
					return FALSE;
				}
			}
			
			if(NULL != P_BtLtp->LTPLib.pLTPMsg)
			{
				if(!DLPS_BUFFER_REG(P_BtLtp->LTPLib.pLTPMsg - heap_struct_size, heap_struct_size, TRUE))
				{
					return FALSE;
				}
			}
		}	
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#endif

/*void LTP_ExitDlps()
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTP_ExitDlps", 0);
	CanEnterDlps = 0;
}*/

/**
 * @brief init ltp module, call this function before calling other ltp functions .
 *
 * @param none.
 * @return the init result. 
 * @retal  0 -- init ltp failed.
 			1 -- init ltp successfully.
*/
HAL_ROM_TEXT_SECTION
uint8_t ltpInit(void)
{
	if( NULL != pPatch_Ltp_Init)
	{
		return pPatch_Ltp_Init();
	}
	
    xTaskCreate(ltpTask, "BTLTP", otp_str_data.gEfuse_Ltp_s.ltp_task_stack_size / sizeof(portSTACK_TYPE), NULL, LTP_PRIORITY, &LTPTaskHandle);

    /* tx assist task */
    if (LTP_DMA_MODE != otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
    {
        xTaskCreate(TxAssistTask, "TxAssist", otp_str_data.gEfuse_Ltp_s.ltp_tx_task_stack_size / sizeof(portSTACK_TYPE), NULL, LTP_PRIORITY, &LTPTxAssistHandle);
    }

    /* allocate TCB ram and rx buffer ram, do not free them */
    P_BtLtp = pvPortMalloc(sizeof(TBTLtp), RAM_TYPE_DATA_ON);
    /* memset */
    memset(P_BtLtp, 0, sizeof(TBTLtp));
    P_BtLtp->p_aci_tcb = pvPortMalloc(sizeof(ACI_TCB), RAM_TYPE_DATA_ON);					/* ltp control block */
    memset(P_BtLtp->p_aci_tcb, 0, sizeof(ACI_TCB));
    P_BtLtp->p_aci_tcb->p_rx_buf = pvPortMalloc(otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size, RAM_TYPE_DATA_OFF);	    /* ltp uart rx buffer */
    memset(P_BtLtp->p_aci_tcb->p_rx_buf, 0, otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size);
	P_BtLtp->p_aci_tcb->p_tx_buf = pvPortMalloc(otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size, RAM_TYPE_DATA_OFF);     	/* ltp tx buffer */
    memset(P_BtLtp->p_aci_tcb->p_tx_buf, 0, otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size);
	P_BtLtp->p_aci_tcb->p_rx_handle_buf = pvPortMalloc(400, RAM_TYPE_DATA_OFF);   /* ltp rx handle buffer */
	memset(P_BtLtp->p_aci_tcb->p_rx_handle_buf, 0, 400);
    
    /* allocate failed */
    if (NULL == P_BtLtp
    		||NULL == P_BtLtp->p_aci_tcb 
    		|| NULL == P_BtLtp->p_aci_tcb->p_rx_buf 
    		|| NULL == P_BtLtp->p_aci_tcb->p_tx_buf
    		|| NULL == P_BtLtp->p_aci_tcb->p_rx_handle_buf)
    {
    	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "Ltp ram allocated failed!", 0);
        return 0;
    }

	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Ltp ram allocated successfully!", 0);
    
	memset(&(P_BtLtp->p_aci_tcb->tx_mem_tcb), 0, sizeof(TxMemTCB));
	P_BtLtp->p_aci_tcb->tx_mem_tcb.free_size = otp_str_data.gEfuse_Ltp_s.ltp_tx_buffer_size;

	/* for gdma*/
	P_BtLtp->p_aci_tcb->LtpGdmaAdapterTx.pHalGdmaAdapter = &P_BtLtp->p_aci_tcb->LtpHalGdmaAdapter;
	P_BtLtp->p_aci_tcb->LtpGdmaAdapterTx.pHalGdmaOp = &P_BtLtp->p_aci_tcb->LtpHalGdmaOp;

	/* tasks and queues */
    P_BtLtp->p_aci_tcb->Handle = LTPTaskHandle;
    P_BtLtp->p_aci_tcb->P_RxBuffer = &P_BtLtp->p_aci_tcb->p_rx_buf[0];
    P_BtLtp->p_aci_tcb->QueueHandleEvent   = xQueueCreate(32, sizeof(unsigned char));
    P_BtLtp->p_aci_tcb->QueueHandleTxData  = xQueueCreate(12, sizeof(TLTPData));
    P_BtLtp->p_aci_tcb->QueueHandleRxData  = xQueueCreate(12, sizeof(TLTPData));
    P_BtLtp->p_aci_tcb->QueueHandleTxRel  = xQueueCreate(12, sizeof(TLTPData));	/* tx release */
    P_BtLtp->p_aci_tcb->QueueHandleMessage = xQueueCreate(MAX_NUMBER_OF_MESSAGE, sizeof(PBlueAPI_DsMessage));
#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
    P_BtLtp->p_aci_tcb->ltpTimerHandle = xTimerCreate(ltpTimer, (10 * portTICK_RATE_MS), pdFALSE, 0, ltpTimeoutRoutine);
#endif
	
#ifdef CONFIG_DLPS_EN
	/* register dlps check callback function */
	DLPS_ENTER_CHECK_CB_REG(LtpDlpsEnterCheck);
	/* for test dlps */
	//DLPS_INTERRUPT_CONTROL_CB_REG(LTP_ExitDlps, DLPS_EXIT);
#endif

	/* tifnan: for test dlps */
	//LPS_MODE_Set(LPM_DLPS_MODE);
	
    return 1;
}

void LTP_ExitDlps(void)
{
	if(EnableDlpsLog)
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LTP_ExitDlps", 0);
	}
	
	if( NULL != pPatch_LTP_ExitDlps)
	{
		return pPatch_LTP_ExitDlps();
	}
	
    ActiveTime_Restart(200);    /* 50msx200 = 10s */
}

void LTP_EnterDlps(void)
{
	if(EnableDlpsLog)
	{
		DBG_DIRECT("LTP_EnterDlps");
	}
	
	if( NULL != pPatch_LTP_EnterDlps)
	{
		return pPatch_LTP_EnterDlps();
	}
}

#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
/**
 * @brief start lp timer, not used in ltp now.
 *
 * @param TimerID time id.
 * @param TimerMS the time setting of this timer.
 * @return none. 
 * @retal 	void.
*/
HAL_ROM_TEXT_SECTION
void ltpTimerStart(TLTPTimerID TimerID, int TimerMS)        /* tifnan:not used now */
{
    if (P_BtLtp->p_aci_tcb->ltpTimerMS != 0)     /* timer started */
    {
        xTimerStop(P_BtLtp->p_aci_tcb->ltpTimerHandle, 0);
    }
    P_BtLtp->p_aci_tcb->ltpTimerID = TimerID;
    P_BtLtp->p_aci_tcb->ltpTimerMS = TimerMS;
    xTimerChangePeriod(P_BtLtp->p_aci_tcb->ltpTimerHandle, (TimerMS / portTICK_RATE_MS), 0);
    xTimerStart(P_BtLtp->p_aci_tcb->ltpTimerHandle, 0);

    return;
}
#endif

/**
 * @brief send the data in queue save when bee is waiting for host ack.
 *
 * @param p_buf pointer to the buffer start address.
 * @param buf_len the length of the buffer.
 * @return none. 
 * @retal 	void.
*/
void LtpLowPowerQueueSend(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LtpLowPowerQueueSend", 0);
	
	uint16_t i = 0;
	PLTPLL_BufMsg p_buf_msg = NULL;
	TLTPData tx_data = {NULL, 0};
	uint16_t queue_size = LTPLL_GetQueueSize();

	for(i = 0; i < queue_size; i++)
	{
		p_buf_msg = LTPLL_QueueOut();
		
		tx_data.pBuffer = p_buf_msg->buf_addr;

		tx_data.Length = p_buf_msg->size;

		if(NULL != p_buf_msg)
		{
			/* take care that exceed the size of QueueHandleTxData!!! */
			if(pdFALSE == xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleTxData, &tx_data, 0))
			{
				DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LtpLowPowerQueueSend:xQueueSend fail", 0);
			}

	    	/* notify ltp task to start gdma */
	    	if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
	    	{
	        	ltpSendEvent(&ltpEventUartTx);
	    	}

	    	/* free */
    		vPortFree(p_buf_msg, RAM_TYPE_BUFFER_ON);
		}
	}
}

/**
 * @brief call this fucntion will start to send data through ltp.
 * @param p_buf pointer to the buffer start address.
 * @param buf_len the length of the buffer.
 * @return none. 
 * @retal 	void.
*/
HAL_ROM_TEXT_SECTION
void LtpWrite(uint8_t *p_buf, uint32_t buf_len)
{
    TLTPData tx_data;
    tx_data.pBuffer       = p_buf;
    tx_data.Length        = buf_len;

    if(NULL != pPatch_Ltp_LtpWrite)
    {
    	pPatch_Ltp_LtpWrite(p_buf, buf_len);
    	return;
    }

    if(!otp_str_data.gEfuse_Ltp_s.aci_en)
    {
    	if(pdFALSE == xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleTxData, &tx_data, 0))
    	{
    		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LtpWrite:xQueueSend fail", 0);
    	}

		/* notify ltp task to start gdma */
		if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
		{
			ltpSendEvent(&ltpEventUartTx);
		}
    }
    /* enable aci mode */
    else
    {
    	/* uart is active, restart LTPLL_InActiveTimeOut */
    	if(LTPLL_InActiveTimeOut && LPM_DLPS_MODE == LPS_MODE_Get())
    	{
    		xTimerReset(LTPLL_InActiveTimeOut, 0);
    	}

    	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LtpWrite", 0);
    	
    	/* host may be in sleep state */
    	if(LTPLL_STATE_LOGICAL_SLEEP == LTPLL_GetPowerStatus())
    	{
    		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "host may be in logical sleep, queue data firstly", 0);
    		LTPLL_QueueSave(p_buf, buf_len);
    		/* wake up host firstly */
    		LTPLL_WakeUpNotifyHost();
    		return;
    	}
    	
    	/* is wait for host ack, can not send to host now */
    	if (LTPLL_STATE_W4_ACK == LTPLL_GetPowerStatus())
	    {
	    	LTPLL_QueueSave(p_buf, buf_len);
	    	return;
	    }

		/* bee is in wake state but queue is not empty */
	    if(LTPLL_STATE_AWAKE == LTPLL_GetPowerStatus() && !LTPLL_QueueIsEmpty())
	    {
	    	LTPLL_QueueSave(p_buf, buf_len);
	    	return;
	    }

		/* bee is in wake state and queue is empty */
	    if(LTPLL_STATE_AWAKE == LTPLL_GetPowerStatus() && LTPLL_QueueIsEmpty())
	    {
	    	xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleTxData, &tx_data, 0);

			/* notify ltp task to start gdma */
			if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
			{
    			ltpSendEvent(&ltpEventUartTx);
			}

			return;
	    }
	    
#if 0	    
	    else if(LTPLL_STATE_AWAKE == LTPLL_GetPowerStatus())
	    {
	    	if(LTPLL_QueueIsEmpty())
	    	{
	    		xQueueSend(P_BtLtp->p_aci_tcb->QueueHandleTxData, &tx_data, 0);

				/* notify ltp task to start gdma */
				if (LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode)
				{
	    			ltpSendEvent(&ltpEventUartTx);
				}
	    	}
	    	else
	    	{
	    		/* save this data to queue */ 
	    		LTPLL_QueueSave(p_buf, buf_len);
	    		LtpLowPowerQueueSend();
	    	}    	
	    }
#endif
    }
}


/**
 * @brief release ltp buffer when ltp command has executed completely.
 *
 * @param p_buf the buffer start address to release, not used now!!
 * @return none. 
 * @retal 	void.
*/
HAL_ROM_TEXT_SECTION
void LtpBufferRelease(void* p_buf)
{
    TLTPData RxData;

    if(NULL != pPatch_Ltp_LtpBufferRelease)
    {
    	pPatch_Ltp_LtpBufferRelease(p_buf);
    	return;
    }

    if (xQueueReceive(P_BtLtp->p_aci_tcb->QueueHandleRxData, &RxData, 0) == pdPASS)
    {
        if (RxData.pBuffer == &P_BtLtp->p_aci_tcb->p_rx_buf[P_BtLtp->p_aci_tcb->RxReadIndex])
        {
            uint32_t RxDataLength;

            taskDISABLE_INTERRUPTS();
            P_BtLtp->p_aci_tcb->RxDataLength -= RxData.Length;
            RxDataLength           = P_BtLtp->p_aci_tcb->RxDataLength;
            taskENABLE_INTERRUPTS();

            P_BtLtp->p_aci_tcb->RxReadIndex += RxData.Length;
            P_BtLtp->p_aci_tcb->RxReadIndex &= (otp_str_data.gEfuse_Ltp_s.ltp_rx_buffer_size - 1);
            //DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LtpBufferRelease: P_BtLtp->p_aci_tcb->RxReadIndex = %d", 1, P_BtLtp->p_aci_tcb->RxReadIndex);

            if (P_BtLtp->p_aci_tcb->RxDataIndication)   /* waiting for response */
            {
                P_BtLtp->p_aci_tcb->RxDataIndication -= RxData.Length;
            }

            if (P_BtLtp->p_aci_tcb->RxDataIndication == 0 &&   /* no response pending and */
                    RxDataLength != 0)                 		   /* still data available */
            {
                ltpSendEvent(&ltpEventUartRx);
            }

            /* tifnan: we use auto-flow control */
            /*if (P_BtLtp->p_aci_tcb->RxDisabled == true && RxDataLength <= LTP_RX_ENABLE_COUNT)
            {
              ltpRxEnable();
            }*/
        }
        else
        {
            BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                                   "LtpBufferRelease: Wrong buffer");
            DebuggerBreak();
        }
    }
    else
    {
        BLUEAPI_TRACE_PRINTF_0(BLUEAPI_TRACE_MASK_TRACE,
                               "LtpBufferRelease: No RxData");
        DebuggerBreak();
    }

    return;
}


