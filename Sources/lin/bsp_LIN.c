/**
  ******************************************************************************
  * 文件名程: bsp_LIN.c
  * 作    者: kian
  * 版    本: V1.0
  * 编写日期: 2020-10-28 16:10:58
  * 功    能: 板载LIN底层驱动程序：默认使用LPUART0
  ******************************************************************************
  * 说明：
  * 
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "queue.h"
#include "pin_mux.h"
#include "dmaController1.h"
#include "clockMan1.h"
#include "lin/bsp_LIN.h"
#include "BoardDefines.h"
#include "S32K144.h"
#include "stdbool.h"


LIN_MSG_Type id_0x3c = {
    .size = 8,
};
LIN_MSG_Type id_0x3d = {
    .size = 8,
};
LIN_MSG_Type id_0x11 = {
    .size = 8,
};
LIN_MSG_Type id_0x0a = {
    .size = 7,
};
LIN_MSG_Type id_0x0b = {
    .size = 2,
};
LIN_MSG_Type id_0x0d = {
    .size = 3,
};



/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
uint8_t lin_ClassicPID[] = {0x3C, 0x3D};
volatile bool wakeupSignalFlag = false;

/* Define for DATA buffer transmit */
/* Define for DATA buffer receiver */
uint8_t lin_rxBuff[DATA_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t lin_0x11_rxBuff[DATA_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t lin_0x21_rxBuff[DATA_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
linData8Bytes linSendBuff;
lin_node_state_t linNodeState = LIN_NODE_STATE_UNINIT;

/* 扩展变量 ------------------------------------------------------------------*/
uint16_t timerOverflowInterruptCount = 0U;
/* 私有函数原形 --------------------------------------------------------------*/
lin_callback_t lin_CallbackHandler(uint32_t instance, lin_state_t * lin1_State);
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: lin初始化配置
  * 输入参数:
  * 返 回 值: 无
  * 说    明:
  */
void bspLIN_Init(void)
{
    /* Wake up LIN transceiver */
    PINS_DRV_SetPins(LIN_EN_GPIO,LIN_EN_PIN);

    /* Initialize LIN network interface */
    LIN_DRV_Init(INST_LIN1, &lin1_InitConfig0, &lin1_State);

    /* Install callback function */
    LIN_DRV_InstallCallback(INST_LIN1, (lin_callback_t)lin_CallbackHandler);

    INT_SYS_SetPriority(LPUART1_RxTx_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
}


/*!
 * @brief Callback function to get time interval in nano seconds
 * @param[out] ns - number of nanoseconds passed since the last call of the function
 * @return dummy value
 */
uint32_t lin1TimerGetTimeIntervalCallback0(uint32_t *ns)
{
    static uint32_t previousCountValue = 0UL;
    uint32_t counterValue;

    counterValue = LPTMR_DRV_GetCounterValueByCount(INST_LPTMR1);
    *ns = ((uint32_t)(counterValue + timerOverflowInterruptCount * TIMER_COMPARE_VAL - previousCountValue)) * 1000U / TIMER_TICKS_1US;
    timerOverflowInterruptCount = 0UL;
    previousCountValue = counterValue;

    return 0UL;
}


/**
* Func:     lin_CallbackHandler()
* Desc:     Declare Callback handler function
*/
lin_callback_t lin_CallbackHandler(uint32_t instance, lin_state_t * lin1_State)
{
    lin_callback_t callbackCurrent;
    callbackCurrent = lin1_State->Callback;

    switch (lin1_State->currentEventId)
    {
        case LIN_PID_OK:

            /* Set timeout */
            LIN_DRV_SetTimeoutCounter(INST_LIN1, TIMEOUT);

            /* If PID is ID_0A_SLAVE_RECEIVE_DATA, salve node will receive data from master node */
            if(ID_3C_SLAVE_RECEIVE_DATA == lin1_State->currentId)
            {
                /* Call to Send Frame DATA Function */
                LIN_DRV_SendFrameData(INST_LIN1, id_0x3c.data.data, id_0x3c.size);
            }

            if(ID_0A_SLAVE_RECEIVE_DATA == lin1_State->currentId)
            {
                LIN_DRV_SendFrameData(INST_LIN1,id_0x0a.data.data, id_0x0a.size);
            }

            if(ID_0B_SLAVE_RECEIVE_DATA == lin1_State->currentId)
            {
                LIN_DRV_SendFrameData(INST_LIN1,id_0x0b.data.data, id_0x0b.size);
            }

            if(ID_0D_SLAVE_RECEIVE_DATA == lin1_State->currentId)
            {
                LIN_DRV_SendFrameData(INST_LIN1,id_0x0d.data.data, id_0x0d.size);
            }
            /* If PID is FRAME_MASTER_RECEIVE_DATA, master node will receive data */
            if(ID_3D_MASTER_RECEIVE_DATA == lin1_State->currentId)
            {
                /* Call to Receive Frame DATA Function */
                LIN_DRV_ReceiveFrameData(INST_LIN1, lin_rxBuff, sizeof(lin_rxBuff));
            }

            if(ID_11_MASTER_RECEIVE_DATA == lin1_State->currentId)
            {
                /* Call to Receive Frame DATA Function */
                LIN_DRV_ReceiveFrameData(INST_LIN1, lin_0x11_rxBuff, sizeof(lin_0x11_rxBuff));
            }
            
            if(ID_21_MASTER_RECEIVE_DATA == lin1_State->currentId)
            {
                /* Call to Receive Frame DATA Function */
                LIN_DRV_ReceiveFrameData(INST_LIN1, lin_0x21_rxBuff, sizeof(lin_0x21_rxBuff));
            }
            /* If PID is FRAME_GO_TO_SLEEP, salve node will go to sleep mode */
            if(FRAME_GO_TO_SLEEP == lin1_State->currentId)
            {
                /* Go to sleep mode */
                LIN_DRV_GoToSleepMode(INST_LIN1);
            }
            break;
        case LIN_PID_ERROR:
            /* Go to idle mode */
            //禁止计入休眠模式 LIN_DRV_GoToSleepMode(INST_LIN1);
            break;
        case LIN_TX_COMPLETED:
        case LIN_RX_COMPLETED:
            /* Go to idle mode */
            LIN_DRV_GotoIdleState(INST_LIN1);
            break;
        case LIN_CHECKSUM_ERROR:
        case LIN_READBACK_ERROR:
        case LIN_FRAME_ERROR:
        case LIN_RECV_BREAK_FIELD_OK:
            /* Set timeout */
            LIN_DRV_SetTimeoutCounter(INST_LIN1, TIMEOUT);
            break;
        case LIN_WAKEUP_SIGNAL:
            /* Set wakeup signal flag */
            wakeupSignalFlag = true;
            break;
        case LIN_SYNC_ERROR:
        case LIN_BAUDRATE_ADJUSTED:
        case LIN_NO_EVENT:
        case LIN_SYNC_OK:
        default:
        /* do nothing */
            break;
    }
    return callbackCurrent;
}

/**
  * 函数功能: LIN任务
  * 输入参数:
  * 返 回 值: 无
  * 说    明:
  */
void prvLIN_Task(void *pvParameters )
{
    uint8_t byteRemain = 1U;
    status_t status = STATUS_ERROR;
    static uint16_t  errorCount;

    bspLIN_Init();

    /* Infinite loop */
    while(1)
    {
        id_0x0d.data.data[0] = 0x01;
        id_0x0d.data.data[1] = 0x00;
        id_0x0d.data.data[2] = 0x00;

        status = LIN_DRV_MasterSendHeader(INST_LIN1, ID_0D_SLAVE_RECEIVE_DATA);
        if (status == STATUS_SUCCESS)
        {
            errorCount = 0;
            }
            else
            {
                errorCount++;
                if(errorCount>100)
                {
                    LIN_DRV_GotoIdleState(INST_LIN1);
                    errorCount = 0;
                }  
            }
    }
}


/************************END OF FILE************************/
