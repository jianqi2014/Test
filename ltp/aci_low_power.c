enum { __FILE_NUM__= 0 };
/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      aci_low_power.c
* @brief     low power handle when using ACI.
* @details   none.
* @author    Tifnan
* @date      2014-11-19
* @version   v0.1
*            v1.0 for git test
* *********************************************************************************************************
*/

#include "aci_low_power.h"
#include "btltp.h"
#include "hal_gpio.h"
#include "patch_application.h"
#include "dlps_platform.h"
#include "blueapi.h"

#define INT_LEVEL_ACTIVE_HIGH		0x01
#define INT_EDGE_ACTIVE_LOW			0x02

extern uint8_t CanEnterDlps;

/** @brief the current power state of bee */
uint8_t LtpPowerState = LTPLL_STATE_AWAKE;
/** @brief host power stste */
uint8_t HostPowerState = LTPLL_STATE_AWAKE;
/** @brief aci uart no transmit timer */
xTimerHandle LTPLL_InActiveTimeOut = NULL;

/* test interface */
uint8_t TestDlps = 0;
uint8_t EnAciLog = 0;

/* default aci gpio */
GPIOGroupDef BeeIndGpioGroup = GPIO_GROUP_C;
uint8_t BeeIndGpioIndex = 1;
GPIOGroupDef HostWakeGpioGroup = GPIO_GROUP_B;
uint8_t HostWakeGpioIndex = 2;


extern void LtpLowPowerQueueSend(void);

void LTPLL_PulseDelay(uint32_t delay)
{
	uint32_t i = 0;

	/* for different mcu */
    if(NULL != pPatch_Aci_PulseDelay)
    {
    	pPatch_Aci_PulseDelay();
    }
    
	for(i = 0; i < delay; i++);

	return;
}

void LTPLL_WakeUpNotifyHost(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_WakeUpNotifyHost\n", 0);
	
	/* 1. pull host input gpio high */
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 1);  /* high */
	
	/* 2. start a timer to wait for host ack */
	//xTimerStart(LTPLL_WaitForHostAckTimer, 0);
	
	/* 3. set status to LTPLL_STATE_W4_ACK */
	LTPLL_SetPowerStatus(LTPLL_STATE_W4_ACK);
}

/**
 * @brief when bee is to enter dlps, call this function to send dlps indication to host.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_SendSleepInd(void)
{
	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_SendSleepInd\n", 0);
	
	/* L -> H -> L*/
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 1);
	/* may need delay */
	LTPLL_PulseDelay(10);
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 0);
	LTPLL_SetPowerStatus(LTPLL_STATE_DLPS);
}

void LTPLL_SendLogicalSleepInd(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_SendLogicalSleepInd\n", 0);
	
	/* L -> H -> L*/
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 1);
	/* may need delay */
	LTPLL_PulseDelay(10);
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 0);
	
	LTPLL_SetPowerStatus(LTPLL_STATE_LOGICAL_SLEEP);
}

/**
 * @brief when host wakeup bee, call this function to send ack signal to host.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_SendAckToHost(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_SendAckToHost\n", 0);
	
	/* L -> H -> L*/
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 1);
	/* may need delay */
	LTPLL_PulseDelay(10);
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 0);
	
	LTPLL_SetPowerStatus(LTPLL_STATE_AWAKE);
}

/**
 * @brief wait for host ack timeout, notify host again.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_SendWakeUpIndRty(void)
{
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 0);  /* low */
	/* may need delay */
	LTPLL_PulseDelay(10);
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 1);  /* high */
}

void LTPLL_InActiveTimeout(xTimerHandle handle)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_InActiveTimeout", 0);
	
	//1. notify host to sleep
	LTPLL_SendLogicalSleepInd();
	
	//2. stop the timer
	if(pdFAIL == xTimerStop(LTPLL_InActiveTimeOut, 0))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_InActiveTimeout, stop inactive timer fail", 0);
	}
	
	//3. update the host power state
	LTPLL_SetHostPowerStatus(LTPLL_STATE_LOGICAL_SLEEP);
}

/**
 * @brief handle host wake up signal.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_HandleHostWakeUpSig(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "HostWakeUpSig\n", 0);
	//sned ack
	LTPLL_SendAckToHost();
}

/**
 * @brief handle host ack signal.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_HandleHostAckSig(void)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLL_HandleHostAckSig", 0);
	GPIO_Write(BeeIndGpioGroup, BeeIndGpioIndex, 0);
	LTPLL_SetPowerStatus(LTPLL_STATE_AWAKE);
}

/* restart LTPLL_InActiveTimeOut */
void RestartInActiveTimer(void)
{
	portBASE_TYPE TaskWoken = pdFALSE;

	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "RestartInActiveTimer:0x%x,0x%x,0x%x ", 3,\
	LTPLL_InActiveTimeOut, LTPLL_GetPowerStatus(), LTPLL_GetHostPowerStatus());
	
	if(LTPLL_InActiveTimeOut 
		&& LTPLL_STATE_AWAKE == LTPLL_GetPowerStatus()
		&& LTPLL_STATE_AWAKE == LTPLL_GetHostPowerStatus())
    {
    	xTimerResetFromISR(LTPLL_InActiveTimeOut, &TaskWoken);
    	portYIELD_FROM_ISR(TaskWoken);
   	}
}

/**
 * @brief goio interrupt handle ISR.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_HostGpioIsr(void)
{
	/* reinit aci gpio */
    if(NULL != pPatch_Aci_LTPLL_HostGpioIsr)
    {
    	pPatch_Aci_LTPLL_HostGpioIsr();
    	return;
    }

	/* host wake up from logical sleep state */
	if(LTPLL_STATE_LOGICAL_SLEEP == LTPLL_GetPowerStatus())
	{
		LTPLL_SendAckToHost();
		LTPLL_SetHostPowerStatus(LTPLL_STATE_AWAKE);
		RestartInActiveTimer();
	}
	/* host wake up bee */
	else if(LTPLL_STATE_WAKE_BY_HOST == LTPLL_GetPowerStatus())
	{
		LTPLL_SendAckToHost();
		LTPLL_SetHostPowerStatus(LTPLL_STATE_AWAKE);
		RestartInActiveTimer();
	}
	/* host ack */
	else if(LTPLL_STATE_W4_ACK == LTPLL_GetPowerStatus())
	{
		LTPLL_HandleHostAckSig();
		LTPLL_SetHostPowerStatus(LTPLL_STATE_AWAKE);

		/* if have stack message in queue, handle it */
		LtpLowPowerQueueSend();
		RestartInActiveTimer();
	}
	/* wrong interrupt sig */
	else
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLL_HostGpioIsr:wrong interrupt:0x%x", 1, LTPLL_GetPowerStatus());
	}

	GPIO_ClearInterrupt(HostWakeGpioGroup * 8 + HostWakeGpioIndex);
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLL_HostGpioIsr: gpio_int_sta = 0x%x", 1, GPIO_GetINTStatus());
}

#if 0
/*config input interrupt trigger type */
uint8_t LTPLL_ConfigIntType(uint8_t int_type)
{
	GPIO_Initialize_Param gpio_param;

	gpio_param.GPIOGroup = HOST_WAKE_GPIO_GROUP;
	gpio_param.GPIOIndex = HOST_WAKE_GPIO_INDEX;
	gpio_param.GPIOPull = GPIO_PULL_MODE_PULL_DOWN;
	gpio_param.GPIOMode  = GPIO_MODE_INT;
	gpio_param.INTConfiguration.INT_Enabler = GPIO_INT_ENABLE;
	gpio_param.INTConfiguration.INT_Debounce = GPIO_INT_DEBOUNCE_ENABLE;

	if(INT_LEVEL_ACTIVE_HIGH == int_type)
	{
		gpio_param.INTConfiguration.INT_Level = GPIO_INT_LEVEL_SENSITIVE;
		gpio_param.INTConfiguration.INT_Polarity = GPIO_INT_POLARITY_ACTIVE_HIGH;
		gpio_param.INTConfiguration.INT_Enable_System_Wakeup = TRUE;
	}

	if(INT_EDGE_ACTIVE_LOW == int_type)
	{	
		gpio_param.INTConfiguration.INT_Level = GPIO_INT_EDGE_SENSITIVE;
		gpio_param.INTConfiguration.INT_Polarity = GPIO_INT_POLARITY_ACTIVE_LOW;
		gpio_param.INTConfiguration.INT_Enable_System_Wakeup = FALSE;
	}

	if (STATUS_FAIL == GPIO_Initialize(&gpio_param))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "Change gpio interrupt type fail\n", 0);
		return 0;
	}

	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_ConfigIntType:INTPinIndex:%d\n", 1, gpio_param.INTPinIndex);
	
	return 1;
}
#endif

/**
 * @brief when bee exit dlps, this function will be called.
 * @param none.
 * @return none. 
 * @retval void.
*/
void LTPLL_ExitDlpsRoutin(void)
{
	unsigned long io_level = 0;
	
	if(NULL != pPatch_Aci_LTPLL_ExitDlpsRoutin)
	{
		pPatch_Aci_LTPLL_ExitDlpsRoutin();
		return;
	}

	/* test interface */
	if(TestDlps)
	{
		CanEnterDlps = 0;
	}

	GPIO_ReadExtPinStatus(HostWakeGpioGroup, HostWakeGpioIndex, &io_level);

	/* wake up by host */
	if(1 == io_level)
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLL_STATE_WAKE_BY_HOST", 1, io_level);
		LTPLL_SetPowerStatus(LTPLL_STATE_WAKE_BY_HOST);
	}

	/* wake up itself, notify host */
	if(0 == io_level)
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLL_STATE_WAKE_SELF", 1, io_level);
		LTPLL_SetPowerStatus(LTPLL_STATE_WAKE_SELF);
		LTPLL_WakeUpNotifyHost();
	}
}

void LTPLL_EnterDlpsRoutin(void)
{
	//just for debug dlps
	if(EnAciLog)
	{
		DBG_DIRECT("LTPLL_EnterDlpsRutin");
	}
}


void LTPLL_ConfigPowerMode(uint8_t command, uint8_t* p_param)
{
	if(NULL != pPatch_Aci_LTPLL_ConfigPowerMode)
	{
		pPatch_Aci_LTPLL_ConfigPowerMode(command, p_param);
		return;
	}
	
	/* low power mode config */
	if(0x02 == command)
	{
		LPS_MODE_Set((LPS_MODE)*p_param);		
		if(LPM_DLPS_MODE == ((LPS_MODE)*p_param) && LTPLL_InActiveTimeOut)
		{
			xTimerStart(LTPLL_InActiveTimeOut, 0);
		}
		else
		{
			xTimerStop(LTPLL_InActiveTimeOut, 0);
		}
	}

	/* low power mode pause */
	if(0x03 == command)
	{
		LPS_MODE_Pause();
		xTimerStop(LTPLL_InActiveTimeOut, 0);
	}

	/* low power mode resume */
	if(0x04 == command)
	{
		LPS_MODE_Resume();
		if(LPM_DLPS_MODE == LPS_MODE_Get())
		{
			xTimerReset(LTPLL_InActiveTimeOut, 0);
		}	
	}
}

uint8_t LTPLL_InActiveTimeConfig(uint8_t* p_param)
{
	//200ms * (*pPara)
	LTPLL_InActiveTimeOut = xTimerCreate((const char*)"InactiveTimer", ((*p_param) * 200) / portTICK_RATE_MS, pdFALSE, NULL, LTPLL_InActiveTimeout);

	if(!LTPLL_InActiveTimeOut)
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR,  "Create LTPLL_InActiveTimeOut timer fail", 0);
		return 0;
	}

	return 1;
}

uint8_t LTPLL_HardwareInit(uint8_t* p_param)
{
	/* reinit aci gpio */
    if(NULL != pPatch_Aci_LTPLL_HardwareConfig)
    {
    	return pPatch_Aci_LTPLL_HardwareConfig();
    }

    BeeIndGpioGroup   = (GPIOGroupDef)(*p_param++);
    BeeIndGpioIndex   = *p_param++;
    HostWakeGpioGroup = (GPIOGroupDef)(*p_param++);
	HostWakeGpioIndex = *p_param++;
    
	GPIO_Initialize_Param gpio_param;	
	IRQ_HANDLE gpio_isr_handle;

	/* bee output */
	gpio_param.GPIOGroup = BeeIndGpioGroup;
	gpio_param.GPIOIndex = BeeIndGpioIndex;
	gpio_param.GPIOPull = GPIO_PULL_MODE_PULL_DOWN;		/* low level out */
	gpio_param.INTConfiguration.INT_Enabler = GPIO_INT_DISABLE;
	gpio_param.GPIOMode  = (GPIOPinStatus)GPIO_MODE_OUT;
	if(STATUS_SUCCESS != GPIO_Initialize(&gpio_param))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR, "LTPLL_HardwareInit: output gpio init failed", 0);
		return 0;
	}

	/* bee input */
	gpio_param.GPIOGroup = HostWakeGpioGroup;
	gpio_param.GPIOIndex = HostWakeGpioIndex;
	gpio_param.GPIOPull  = GPIO_PULL_MODE_PULL_DOWN;
	gpio_param.GPIOMode  = (GPIOPinStatus)GPIO_MODE_INT;	/* for keil warming */
	gpio_param.INTConfiguration.INT_Enabler = GPIO_INT_ENABLE;
	gpio_param.INTConfiguration.INT_Level = GPIO_INT_LEVEL_SENSITIVE;
	gpio_param.INTConfiguration.INT_Polarity = GPIO_INT_POLARITY_ACTIVE_HIGH;
	gpio_param.INTConfiguration.INT_Debounce = GPIO_INT_DEBOUNCE_ENABLE;
	gpio_param.INTConfiguration.INT_Enable_System_Wakeup = TRUE;

	if (STATUS_FAIL == GPIO_Initialize(&gpio_param))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR,  "LTPLL_HardwareInit: Aci input gpio init failed\n", 0);
		return 0;
	}

	/* Register ISR function */
    gpio_isr_handle.IrqNum   = GPIO_IRQ;
    gpio_isr_handle.IrqFun   = (IRQ_FUN)LTPLL_HostGpioIsr;
    gpio_isr_handle.Priority = 0;
	gpio_isr_handle.GPIO_Irq_Num = gpio_param.INTPinIndex;
    if (STATUS_FAIL == GPIO_RegisterIRQ(&gpio_isr_handle))
    {
    	DBG_BUFFER(MODULE_LTP, LEVEL_ERROR,  "LTPLL_HardwareInit: Aci interrupt register fail\n", 0);
		return 0;
    }

    return 1;
}

/**
 * @brief aic low power init.
 * @param none.
 * @return the init result. 
 * @retval 1 init successfully.
 *         0 ini failed.
*/
uint8_t LTPLL_Init(void* p_param)
{	
	uint8_t* p_config_param = (uint8_t*)p_param;

	DLPS_INTERRUPT_CONTROL_CB_REG(LTPLL_EnterDlpsRoutin, DLPS_ENTER);
	DLPS_INTERRUPT_CONTROL_CB_REG(LTPLL_ExitDlpsRoutin, DLPS_EXIT);

	if(!LTPLL_HardwareInit(p_config_param))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR,  "Aci hardware init fail", 0);
		return 0;
	}

	p_config_param+= 4;
	
	if(!LTPLL_InActiveTimeConfig(p_config_param))
	{
		DBG_BUFFER(MODULE_LTP, LEVEL_ERROR,  "Aci config inactive timer fail", 0);
		return 0;
	}

	/* register stack */
	blueAPI_RegisterReq(P_BtLtp, (void *)ltpBlueAPICallback);

	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "Aci init OK", 0);
	
	return 1;
}


/**
 * @brief aci handle host command, for test now.
 * @param p_msg the message data buffer.
 * @param cmd ltp protocol command.
 * @param copmsk ltp protocol compask.
 * @param pOpt pointer to the optional parameter field.
 * @param lenPara the size of parameters.
 * @param pPara pointer to the payload field.
 * @return if reuse ltp message buffer. 
 * @retval TRUE reuse mesage buffer.
 *         FALSE release message buffer.
*/
BOOL LTPLL_HandleLowPowerCmd(uint8_t* p_msg, uint8_t cmd, uint8_t copmsk, uint8_t* pOpt, uint16_t lenPara, uint8_t* pPara)
{
	DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "LTPLL_HandleLowPowerCmd", 0);

	uint8_t command = *pOpt;
	
	/* handle more aci command, modify aci command */
	if(NULL != pPatch_Aci_LTPLL_HandleLowPowerCmd)
	{
		pPatch_Aci_LTPLL_HandleLowPowerCmd(p_msg, cmd, copmsk, pOpt, lenPara, pPara, &command);
	}

	switch(command)
	{	
		/* config power mode */
		case 0x02:	/* set*/
		case 0x03:	/* pause */
		case 0x04:	/* resume */
			LTPLL_ConfigPowerMode(command, pPara);	// 3
		break;

		/* aci init */
		case 0x01:
			LTPLL_Init((void*)pPara);
		break;

		case 0x20:
			TestDlps = *pPara;
		break;

		case 0x21:
			EnAciLog = *pPara;
		break;
		
		/* dlps test interface */
		case 0x22:
			CanEnterDlps = *pPara;
		break;
	}
	
	return TRUE;
}


