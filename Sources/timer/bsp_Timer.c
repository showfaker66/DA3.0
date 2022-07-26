/**
  ******************************************************************************
  * 文件名程: bsp_Timer.c
  * 作    者: kian
  * 版    本: V1.0
  * 编写日期: 2020-10-29 10:33:54
  * 功    能: Timer：默认使用LPTMR0
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
#include "timer/bsp_Timer.h"
#include "BoardDefines.h"
#include "S32K144.h"
#include "stdbool.h"


/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/

/* 扩展变量 ------------------------------------------------------------------*/
extern uint16_t timerOverflowInterruptCount;
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/*!
 * @brief LPTMR Interrupt Service Routine
 * The ISR will call LIN timeout service every 500us
 */
void LPTMR_ISR(void)
{
    /* Timer Interrupt Handler */
    LIN_DRV_TimeoutService(INST_LIN1);
    /* Increment overflow count */
    timerOverflowInterruptCount++;
    /* Clear compare flag */
    LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
}

void timer_init(void)
{
    /* Initialize LPTMR */
    LPTMR_DRV_Init(INST_LPTMR1, &lpTmr1_config0, false);
    INT_SYS_InstallHandler(LPTMR0_IRQn, LPTMR_ISR, (isr_t *)NULL);
    INT_SYS_SetPriority(LPTMR0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
    INT_SYS_EnableIRQ(LPTMR0_IRQn);
    LPTMR_DRV_StartCounter(INST_LPTMR1);
}


/************************END OF FILE************************/