enum { __FILE_NUM__= 0 };
/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      aci_gdma.c
* @brief     gdma interface ltp used.
* @details   none.
* @author    Tifnan
* @date      2014-11-14
* @version   v0.1                       
* *********************************************************************************************************
*/

#include "aci_if.h"
#include "patch_application.h"
#include "dlps_platform.h"
#include "otp.h"

extern void LtpGdma0Ch0IrqHandle(IN void *data);

/* static functions declaration */
void LtpGdmaIpEnable(void);
void LtpGdmaConfig(void* p_gdma_adapter);


/**
 * @brief enable data uart--gdma ip.
 * @param none.
 * @return none
 * @retval void.
*/
void LtpGdmaIpEnable(void)
{
    uint32_t reg_val;

    /* Clock */
    reg_val = HAL_READ32(PERI_ON_BASE, REG_PESOC_CLK_CTRL);
    reg_val = reg_val | BIT16 | BIT18;
    HAL_WRITE32(PERI_ON_BASE, REG_PESOC_CLK_CTRL, reg_val);

    /* Function Enable */
    reg_val = HAL_READ32(PERI_ON_BASE, REG_SOC_FUNC_EN);
    reg_val = reg_val | BIT13 | BIT14;
    HAL_WRITE32(PERI_ON_BASE, REG_SOC_FUNC_EN, reg_val);

    /* Handshake Interface Configuration */
    reg_val = HAL_READ32(PERI_ON_BASE, REG_PESOC_SOC_CTRL);
    reg_val &= ~(1 << 16);  /* uart 0 connect to gdma0 */
    HAL_WRITE32(PERI_ON_BASE, REG_PESOC_SOC_CTRL, reg_val);
}

/**
 * @brief config gdma registers.
 * @param p_init_data PGDMA_ADAPTER type.
 * @return none.
 * @retval void.
*/
void LtpGdmaConfig(void* pGdmaAdapter)
{
	PLTPGDMA_ADAPTER    p_gdma_adapter = (PLTPGDMA_ADAPTER)pGdmaAdapter;
	PHAL_GDMA_ADAPTER 	p_hal_gdma_adapter = p_gdma_adapter->pHalGdmaAdapter;
    PHAL_GDMA_OP      	p_hal_gdma_op = p_gdma_adapter->pHalGdmaOp;
    IRQ_HANDLE        	Gdma0IrqHandle_Tx;
    
    uint8_t *pSrc = NULL;
    uint8_t *pDst = NULL;

    HalGdmaOpInit((VOID*)p_hal_gdma_op);
    
    memset((void*)p_hal_gdma_adapter, 0, sizeof(HAL_GDMA_ADAPTER));

    /* for gdma test */
    /*pSrc = &Test1LtpGdma[0];
    for (data_index = 0; data_index < 100; data_index++)
    {
        Test1LtpGdma[data_index] = data_index;
    }*/
    
    if(LTP_DMA_MODE == otp_str_data.gEfuse_Ltp_s.ltp_tx_mode && LTP_IF_UART == otp_str_data.gEfuse_Ltp_s.ltp_interface)
    {
    	pDst = (uint8_t*) (DATA_UART_REG_BASE + DATA_UART_TRAN_HOLD_OFF);
    }
    
    /* gdma interrupt config */
    Gdma0IrqHandle_Tx.Data = (uint32_t) (p_gdma_adapter);
    Gdma0IrqHandle_Tx.IrqNum = GDMA0_CHANNEL0_IRQ;
    Gdma0IrqHandle_Tx.IrqFun = (IRQ_FUN)LtpGdma0Ch0IrqHandle;
    Gdma0IrqHandle_Tx.Priority = 1;
    
    InterruptUnRegister(&Gdma0IrqHandle_Tx);
    InterruptRegister(&Gdma0IrqHandle_Tx);
    InterruptEn(&Gdma0IrqHandle_Tx);

	/* gdma init parameters */
    p_hal_gdma_adapter->GdmaCtl.BlockSize = 0;
    p_hal_gdma_adapter->GdmaCtl.TtFc      = TTFCMemToPeri;
    p_hal_gdma_adapter->GdmaCfg.DestPer   = 0;
    p_hal_gdma_adapter->MuliBlockCunt     = 0;
    p_hal_gdma_adapter->ChSar = (UINT32)pSrc;
    p_hal_gdma_adapter->ChDar = (UINT32)pDst;
    p_hal_gdma_adapter->GdmaIndex   = 0;
    p_hal_gdma_adapter->ChNum       = 0;
    p_hal_gdma_adapter->ChEn        = GdmaCh0;
    p_hal_gdma_adapter->GdmaIsrType = (BlockType|TransferType|ErrType);
    p_hal_gdma_adapter->IsrCtrl     = ENABLE;
    p_hal_gdma_adapter->GdmaOnOff   = ON;
    p_hal_gdma_adapter->GdmaCtl.IntEn      = ENABLE;
    p_hal_gdma_adapter->GdmaCtl.SrcMsize   = MsizeOne;
    p_hal_gdma_adapter->GdmaCtl.DestMsize  = MsizeOne;
    p_hal_gdma_adapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
    p_hal_gdma_adapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
    p_hal_gdma_adapter->GdmaCtl.Dinc = NoChange;
    p_hal_gdma_adapter->GdmaCtl.Sinc = IncType;

	/* reset gdma parameters */
    if(NULL != pPatch_Ltp_Gdma_ReConfig)
    {
    	pPatch_Ltp_Gdma_ReConfig((void*)pGdmaAdapter);
    }
    
    /* gdma on */
    p_hal_gdma_op->HalGdmaOnOff((VOID*)(p_hal_gdma_adapter));
    /* gdma channel isr enable */
    p_hal_gdma_op->HalGdmaChIsrEnAndDis((VOID*)(p_hal_gdma_adapter));
    /* gdma channel setting */
    p_hal_gdma_op->HalGdmaChSeting((VOID*)(p_hal_gdma_adapter));
}


/**
 * @brief enable gdma channel.
 * @param p_init_data PGDMA_ADAPTER type.
 * @return none.
 * @retval void.
*/
void LtpGdmaChannelEnable(void* pGdmaAdapter)
{
	PLTPGDMA_ADAPTER  		p_gdma_adapter = (PLTPGDMA_ADAPTER)pGdmaAdapter;
	PHAL_GDMA_ADAPTER 	p_hal_gdma_adapter = p_gdma_adapter->pHalGdmaAdapter;
    PHAL_GDMA_OP      	p_hal_gdma_op = p_gdma_adapter->pHalGdmaOp;

    p_hal_gdma_op->HalGdmaChEn((void*)(p_hal_gdma_adapter));
}

/**
 * @brief disable gdma channel.
 * @param p_init_data PGDMA_ADAPTER type.
 * @return none.
 * @retval void.
*/
void LtpGdmaChannelDisable(void* pGdmaAdapter)
{
	PLTPGDMA_ADAPTER  		p_gdma_adapter = (PLTPGDMA_ADAPTER)pGdmaAdapter;
	PHAL_GDMA_ADAPTER 	p_hal_gdma_adapter = p_gdma_adapter->pHalGdmaAdapter;
    PHAL_GDMA_OP      	p_hal_gdma_op = p_gdma_adapter->pHalGdmaOp;

   	p_hal_gdma_op->HalGdmaChDis((void*)(p_hal_gdma_adapter));
}


/**
 * @brief init uart gdma of uart.
 * @param p_init_data PGDMA_ADAPTER type.
 * @return none.
 * @retval void.
*/
void LtpGdmaInit(void* p_gdma_adapter)
{
	/* enable gdma ip */
	LtpGdmaIpEnable();
	/* config gdma registers */
	LtpGdmaConfig(p_gdma_adapter);
	/* enable gdma channel */
	//LtpGdmaChannelEnable(p_gdma_adapter);
}


