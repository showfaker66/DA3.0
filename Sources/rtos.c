/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* SDK includes. */
#include "interrupt_manager.h"
#include "clock_manager.h"
#include "clockMan1.h"
#include "pin_mux.h"

#include "BoardDefines.h"
#include "UserDefines.h"
#include "print/printf.h"
#include "can/bsp_CAN.h"
#include "lin/bsp_LIN.h"
#include "print/bsp_debug_usart.h"
#include "e351/e351.h"
#include "e351/mosCtrl.h"


/* Priorities at which the tasks are created. */
/* low number，low priority */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )	// 2
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )	// 1
#define	mainPRINT_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )	// 1
#define mainCAN_RECEIVE_TASK_PRIORITY		( configMAX_PRIORITIES - 1 ) // 4
#define mainCAN_SEND_TASK_PRIORITY			( configMAX_PRIORITIES - 2 ) // 3
#define mainE351_REFRESH_TASK_PRIORITY		( configMAX_PRIORITIES - 1 ) // 4
#define mainMOS_CTRL_TASK_PRIORITY 			( configMAX_PRIORITIES - 3) // 2

/* specified in milliseconds, and converted to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( 200 / portTICK_PERIOD_MS )

/* The LED will remain on until the button has not been pushed for a full 5000ms. */
#define mainBUTTON_LED_TIMER_PERIOD_MS		( 5000UL / portTICK_PERIOD_MS )

#define mainQUEUE_LENGTH					( 1 )

#define mainTASK_CONTROLLED_LED				( 1UL << 0UL )

#define mainTIMER_CONTROLLED_LED			( 1UL << 1UL )

#define mainDONT_BLOCK						( 0UL )

/*-----------------------------------------------------------*/

/*
 * Setup the NVIC, LED outputs, and button inputs.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

void rtos_start( void )
{
	/* Configure the NVIC, LED outputs and button inputs. */
	prvSetupHardware();
	
	/* Creat tasks */
	// xTaskCreate( prvPrintTask, "PRINT", 256, NULL, mainPRINT_TASK_PRIORITY, NULL );
	xTaskCreate( prvCAN_RespondTask, "CANResp", 256, NULL, mainCAN_SEND_TASK_PRIORITY, NULL );
	// xTaskCreate( prvLIN_Task, "LINtask", 256, NULL, mainCAN_SEND_TASK_PRIORITY, NULL );
	xTaskCreate( prvE351RefreshTask, "E351", 512, NULL, mainE351_REFRESH_TASK_PRIORITY, NULL );

	xTaskCreate( prvMosCtrlTask, "mosCtrl", 512, NULL, mainMOS_CTRL_TASK_PRIORITY, NULL);

	extern void vCAN_Send_TimerCreat(void);
	vCAN_Send_TimerCreat();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	// printf("tasks start failed!\r\n");;
	for( ;; );
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
    /* Initialize and configure clocks
     *  -   Setup system clocks, dividers
     *  -   see clock manager component for more details
     */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
					g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
    
    /* Initialize GPIO */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

	timer_init();//主要用于LIN超时计算
	bspDebugUART_Init();
	/* CAN inint */
    bspCAN_Init();
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    volatile size_t xFreeHeapSpace;

	/* This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeHeapSpace = xPortGetFreeHeapSize();

	if( xFreeHeapSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}

}
/*-----------------------------------------------------------*/

/* The Blinky build configuration does not include run time stats gathering,
however, the Full and Blinky build configurations share a FreeRTOSConfig.h
file.  Therefore, dummy run time stats functions need to be defined to keep the
linker happy. */
void vMainConfigureTimerForRunTimeStats( void ) {}
unsigned long ulMainGetRunTimeCounterValue( void ) { return 0UL; }

/* A tick hook is used by the "Full" build configuration.  The Full and blinky
build configurations share a FreeRTOSConfig.h header file, so this simple build
configuration also has to define a tick hook - even though it does not actually
use it for anything. */
void vApplicationTickHook( void ) {}

/*-----------------------------------------------------------*/
