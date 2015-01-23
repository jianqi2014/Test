enum { __FILE_NUM__= 0 };
/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      aci_low_power_utils.c
* @brief     util fucntions implementation used in ltp aci low power.
* @details   none.
* @author    Tifnan
* @date      2014-11-22
* @version   v0.1                       
* *********************************************************************************************************
*/

#include "aci_low_power_utils.h"
#include "st_queue.h"
#include "FreeRTOS.h"

QUEUE_T LTPLL_SaveTxMsgQueue;

/**
 * @brief save ltp buffer message to queue.
 * @param addr the buffer address.
 * @param size the buffer size.
 * @return the save result. 
 * @retval TRUE -- save the buffer message to the queue successfully.
 			FALSE -- save the buffer message to the queue failed.
*/
BOOL LTPLL_QueueSave(uint8_t* addr, uint32_t size)
{
	PLTPLL_BufMsg p_buf_msg = (PLTPLL_BufMsg)pvPortMalloc(sizeof(LTPLL_BufMsg), RAM_TYPE_BUFFER_ON);

	if(NULL == p_buf_msg)
	{
		return FALSE;
	}
	else
	{
		p_buf_msg->buf_addr = addr;
		p_buf_msg->size = size;
		QueueIn(&LTPLL_SaveTxMsgQueue, (void*)p_buf_msg);
		
		return TRUE;
	}
}

/**
 * @brief check the queue is empty or not.
 * @param none.
 * @return the queue is empty?
 * @retval TRUE -- the queue is empty.
 			FALSE -- the queue is not empty.
*/
BOOL LTPLL_QueueIsEmpty(void)
{
	return (LTPLL_SaveTxMsgQueue.Last == NULL);
}

/**
 * @brief get the element count of the queue.
 * @param none.
 * @return the element count in the queue.
*/
uint16_t LTPLL_GetQueueSize(void)
{
	return LTPLL_SaveTxMsgQueue.ElementCount;
}

/**
 * @brief pop a ltp buffer message out of the queue.
 * @param none.
 * @return the pointer of the ltp buffer message.
*/
PLTPLL_BufMsg LTPLL_QueueOut(void)
{
	PLTPLL_BufMsg p_buf_msg = NULL;

	if(LTPLL_QueueIsEmpty())
	{
		return NULL;
	}
	
	p_buf_msg = QueueOut(&LTPLL_SaveTxMsgQueue);

	return p_buf_msg;
}


