/**
  ******************************************************************************
  * 文件名程: bsp_debug_usart.c
  * 作    者: kian
  * 版    本: V1.0
  * 编写日期: 2020-10-01 00:02:12
  * 功    能: 板载调试串口底层驱动程序：默认使用LPUART2
  ******************************************************************************
  * 说明：
  * 
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "pin_mux.h"
#include "dmaController1.h"
#include "clockMan1.h"
#include "lpuart1.h"
#include "bsp_debug_usart.h"
#include "printf.h"
#include <string.h>
#include "UserDefines.h"
/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 串口硬件初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void bspDebugUART_Init(void)
{
    /* Initialize UART1 */
    LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
    /* SET UART1 INTERRUPT Priority
     * The interrupt calls an interrupt safe API function - so its priority must
     * be equal to or lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.   */
    INT_SYS_SetPriority(LPUART1_RxTx_IRQn, (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+2) );

}

void _putchar(char character)
{
  //	uint8_t data = 0u;
  //	memcpy(&data, &character, 1);
  LPUART_DRV_SendDataBlocking(PRINT_INSTANCE,&character,1,100);
  //	LPUART_DRV_SendData(INST_LPUART1,&character,1);
}

void prvPrintTask(void *pvParameters )
{
  uint16_t n = 0;

  /* show version */
  printf("Version:%d.%d.%d build %s\r\n", SW_VERSION, SW_SUBVERSION, SW_REVISION, __DATE__);

  while (1)
  {
    n++;
    // printf("hello world!count :%d\r\n", n);
    //		LPUART_DRV_SendData(INST_LPUART1,"hello world\r\n",15);
    vTaskDelay(1000);
  }
}
/*-----------------------------------------------------------*/


/************************END OF FILE************************/
