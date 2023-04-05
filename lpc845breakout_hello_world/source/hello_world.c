/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "littleshell.h"

#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
#define START_TASK_PRIO        2
#define START_STK_SIZE         128
	TaskHandle_t StartTask_Handler;
	void start_task(void *pvParameters);
	
#define TASK1_TASK_PRIO        2
#define TASK1_STK_SIZE         128
	TaskHandle_t Task1Task_Handler;
	void start_task1(void *pvParameters);
	
#define SHELL_TASK_PRIO        2
#define SHELL_STK_SIZE         256
	TaskHandle_t ShellTask_Handler;


void start_task(void *pvParameters)
{
	while(1)
	{
		PRINTF("task1 .\r\n");
		vTaskDelay(500);
	}
}
	
	
void start_task1(void *pvParameters)
{
	while(1)
	{
		PRINTF("task2 .\r\n");
		vTaskDelay(1000);
	}
}


int main(void)
{
    char ch;

    /* Init board hardware. */
    /* Select the main clock as source clock of USART0 (debug console) */
    CLOCK_Select(BOARD_DEBUG_USART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_BootClockFRO30M();
    BOARD_InitDebugConsole();

    /* Turn on LED RED */
    LED_RED_INIT(LOGIC_LED_ON);

    PRINTF("hello world.\r\n");

    xTaskCreate((TaskFunction_t )start_task,
                (const char*    )"task1",
                (uint16_t       )START_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )START_TASK_PRIO,
                (TaskHandle_t*  )&StartTask_Handler);

    xTaskCreate((TaskFunction_t )start_task1,
                (const char*    )"task2",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_TASK_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);

    xTaskCreate((TaskFunction_t )littleshell_main_entry,
                (const char*    )"shell",
                (uint16_t       )SHELL_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )SHELL_TASK_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);
    vTaskStartScheduler();

}


unsigned int led(char argc,char ** argv)
{
    if(strcmp("on",argv[1]) == 0)
        LED_RED_ON();

    if(strcmp("off",argv[1]) == 0)
        LED_RED_OFF();
    return 1;
}
LTSH_FUNCTION_EXPORT(led,"test led on off");
