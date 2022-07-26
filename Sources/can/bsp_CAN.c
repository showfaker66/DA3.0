/**
  ******************************************************************************
  * 文件名程: bsp_CAN.c
  * 作    者: kian
  * 版    本: V1.0
  * 编写日期: 2020-10-26 16:49:18
  * 功    能: 板载CAN底层驱动程序：默认使用CAN0
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
#include "can/bsp_CAN.h"
#include "BoardDefines.h"
#include "S32K144.h"
#include "../print/printf.h"
#include <string.h>

#include "timers.h"
#include "userCode.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/

/* Set information about the data to be sent
 *  - Standard message ID
 *  - Bit rate switch enabled to use a different bitrate for the data segment
 *  - Flexible data rate enabled
 *  - Use zeros for FD padding
 */
can_buff_config_t buffCfg =  {
    .enableFD = true,
    .enableBRS = true,
    .fdPadding = 0U,
    .idType = CAN_MSG_ID_STD,
    .isRemote = false
};

can_buff_config_t ExbuffCfg =  {
    .enableFD = true,
    .enableBRS = true,
    .fdPadding = 0U,
    .idType = CAN_MSG_ID_EXT,/*!< Extended ID */
    .isRemote = false
};

can_message_t gCAN_RecvMsg;
can_message_t gCAN_sendMsg;

can_message_t EOL_recvMsg;
can_message_t EOL_sendMsg;

uint8_t EOL_RCV_Flag = 0;
uint8_t CAN_RCV_Flag = 0;

uint8_t rrm1_buf[8] = {0};
ptrRRM_1 rcv_rrm1_data = rrm1_buf;

uint8_t rrm2_buf[8] = {0};
ptrRRM_2 rcv_rrm2_data = rrm2_buf;

uint8_t rrm4_buf[8] = {0};
ptrRRM_4 rcv_rrm4_data = rrm4_buf;

uint8_t itm0_buf[6] = {0};
ptrITM_0 rcv_itm0_data = itm0_buf;


QueueHandle_t gCANMsgQueue = NULL;
/* The CAN send software timer.  */
static TimerHandle_t xCanSendTimers = NULL;

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/


/**
  * 函数功能: CAN初始化配置
  * 输入参数:
  * 返 回 值: 无
  * 说    明:
  */
void bspCAN_Init(void)
{
    /*********************************************************************
    CAN Initializes     START
    *********************************************************************/
    gCANMsgQueue = xQueueCreate( CAN_MSG_QUEUE_LENGTH, sizeof( can_message_t ) );

    // PINS_DRV_ClearPins(CAN_STB_GPIO,CAN_STB_PIN);

    CAN_Init(&can_pal1_instance, &can_pal1_Config0);
    /* Configure RX buffer with index RX_MAILBOX */
    CAN_ConfigRxBuff(&can_pal1_instance, RX_MAILBOX, &buffCfg, RX_MSG_ID);
    CAN_ConfigRxBuff(&can_pal1_instance, EOL_RX_MAILBOX, &buffCfg, RX_EOL_ID);

    CAN_SetRxFilter(&can_pal1_instance, CAN_MSG_ID_STD, RX_MAILBOX, RX_MSG_ID_MASK);
    CAN_SetRxFilter(&can_pal1_instance, CAN_MSG_ID_STD, EOL_RX_MAILBOX, RX_EOL_ID_MASK);


    CAN_ConfigTxBuff(&can_pal1_instance, TX_MAILBOX, &buffCfg);
    // CAN_ConfigTxBuff(&can_pal1_instance, exTX_MAILBOX, &ExbuffCfg);/* special for the extended fram */
    CAN_ConfigTxBuff(&can_pal1_instance, EOL_TX_MAILBOX, &buffCfg);

    CAN_InstallEventCallback(&can_pal1_instance, &CAN_ISR, (isr_t *)0);
    /* Start receiving data in RX_MAILBOX. */
    CAN_Receive(&can_pal1_instance, RX_MAILBOX, &gCAN_RecvMsg);
    CAN_Receive(&can_pal1_instance, EOL_RX_MAILBOX, &EOL_recvMsg);

    INT_SYS_SetPriority(CAN2_ORed_IRQn, (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1) );
    INT_SYS_SetPriority(CAN2_ORed_0_15_MB_IRQn, (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1) );
    // INT_SYS_SetPriority(CAN0_ORed_16_31_MB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
    
    /********  CAN   Initializes     END  *****************************/
}

/* CAN IRQ handler */
void CAN_ISR(uint32_t instance, can_event_t eventType, uint32_t objIdx, void *driverState)
{
    status_t status = STATUS_ERROR;
    uint8_t count;

    if(instance == can_pal1_instance.instIdx)
    {
        switch (objIdx)
        {
            case RX_MAILBOX:
                status = CAN_Receive(&can_pal1_instance, RX_MAILBOX, &gCAN_RecvMsg);
                xQueueSendFromISR( gCANMsgQueue, &gCAN_RecvMsg, queueSendDONT_BLOCK );
                break;

            case EOL_RX_MAILBOX:
                status = CAN_Receive(&can_pal1_instance, EOL_RX_MAILBOX, &EOL_recvMsg);
                xQueueSendFromISR( gCANMsgQueue, &EOL_recvMsg, queueSendDONT_BLOCK );
                break;
        }
    }
}




/*---应用函数体-----------------------------------------------------------------*/
void vCanSendPer100ms(void)
{
    can_message_t canSendMsg;
    static uint8_t count = 0;

    count++;
    canSendMsg.cs = 0;
    canSendMsg.id = 0x602;
    canSendMsg.length = 8;
    canSendMsg.data[0] = count;
    CAN_Send(&can_pal1_instance, TX_MAILBOX, &canSendMsg);

}


static void vCAN_Send_TimerCallback( TimerHandle_t xTimer )
{
	uint32_t ulTimerID;
    configASSERT(xTimer);
    /* 获取那个定时器时间到 */
    ulTimerID = (uint32_t)pvTimerGetTimerID(xTimer);
    /* 处理定时器 0 任务 */
    if(ulTimerID == 0)
    {
        vCanSendPer100ms();
    }
    /* 处理定时器 1 任务 */
    if(ulTimerID == 1)
    {
        ;
    }
}

void vCAN_Send_TimerCreat(void)
{
    uint8_t i = 0;
    /* Creat timers */
	const TickType_t xTimerPer[2] = {100, 500};         /* 创建一个定时器组，分别为100ms、500ms*/

    for(i=0; i<2; i++)
    {
        xCanSendTimers = xTimerCreate(	"CAN-T", 			/* 定时器名字 */
							        xTimerPer[i], 			/* 定时器周期,单位系统时钟节拍 */
							        pdTRUE, 			/* 周期性模式或者单次模式 */
							        (void *) i, 		/* 定时器 ID */
							        vCAN_Send_TimerCallback); 	/* 定时器回调函数 */
        if(xCanSendTimers == NULL)
        {
            /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
        }
        else
        {
            /* 启动定时器，系统启动后才开始工作 */
            if(xTimerStart(xCanSendTimers, 100) != pdPASS)
            {
                /* 定时器还没有进入激活状态 */
            }
        }
    }
}


/**
  * 函数功能: CAN 应答任务
  * 输入参数:
  * 返 回 值: 无
  * 说    明:
  */
void prvCAN_RespondTask(void *pvParameters )
{
    can_message_t canRecvMsg;
    can_message_t canSendMsg;
    static uint8_t count = 0;

	while(1)
	{
        // vTaskDelay(1000);

        /* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( gCANMsgQueue, &canRecvMsg, portMAX_DELAY );

        switch(canRecvMsg.id)
        {
            case RRM_1_ID:
                // printf("receive id :0x%x\r\n", canRecvMsg.id);
                memcpy(rcv_rrm1_data, canRecvMsg.data, 8);
            break;

            case RRM_2_ID: 
                memcpy(rcv_rrm2_data, canRecvMsg.data, 8);
            break;

            case RRM_4_ID: 
                memcpy(rcv_rrm4_data, canRecvMsg.data, 8);
            break;

            case ITM_0_ID:
                // printf("receive id :0x%x\r\n", canRecvMsg.id);
                memcpy(rcv_itm0_data, canRecvMsg.data, 8);
                EOL_RCV_Flag = 1;
            break;

            default:
                // printf("unknow id :%x\r\n", canRecvMsg.id);
            break;
        }
        
        vTaskDelay(1);
	}
}



/************************END OF FILE************************/
