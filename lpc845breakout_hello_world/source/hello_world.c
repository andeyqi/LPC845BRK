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
#include "fsl_iap.h"
#include "trace_dump.h"
#include "drv_gpio.h"
#include "cap_touch.h"
#include "fsl_power.h"
#include "usart_adapter.h"
#include "asm_test_s.h"

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

#define CAPT_TASK_PRIO        2
#define CAPT_STK_SIZE         256
        TaskHandle_t CaptTask_Handler;



void start_task(void *pvParameters)
{
    uint8_t out = 0;
    /* get pin by name */
    //int pin = lpc84x_pin_get("P1.0");

    //lpc84x_pin_mode(pin,PIN_MODE_OUTPUT);
    while(1)
    {
        //lpc84x_pin_write(pin,out);
        vTaskDelay(500);
        out = out ? 0 : 1;
    }
}


void start_task1(void *pvParameters)
{
    uint8_t new = 1,old = 1;

    /* get pin by name */
    int pin = lpc84x_pin_get("P0.4");

    lpc84x_pin_mode(pin,PIN_MODE_INPUT);

    while(1)
    {
        new = lpc84x_pin_read(pin);
        if(new != old)
        {
            old = new;
            PRINTF("K3 %s\r\n",(new ? "UP":"DOWN"));
        }
        vTaskDelay(100);
    }
}


int main(void)
{
    char ch;

    /* Initialize board hardware. */
    /* Attach main clock to CAPT */
    CLOCK_Select(kCAPT_Clk_From_Fro);
    POWER_DisablePD(kPDRUNCFG_PD_ACMP);

    /* Init board hardware. */
    /* Select the main clock as source clock of USART0 (debug console) */
    CLOCK_Select(BOARD_DEBUG_USART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    //BOARD_InitDebugConsole();
    shell_uart_init();

    capt_touch_init();

    PRINTF("\r\n");
    PRINTF("LPC845-BRK %s %s.\r\n",__DATE__,__TIME__);
    PRINTF("\r\n");


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
                (TaskHandle_t*  )&ShellTask_Handler);

    xTaskCreate((TaskFunction_t )capt_touch_main,
                (const char*    )"touch",
                (uint16_t       )CAPT_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )CAPT_TASK_PRIO,
                (TaskHandle_t*  )&CaptTask_Handler);


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


unsigned int add(char argc,char ** argv)
{
    int a,b;

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    PRINTF("%s + %s = %d \r\n",argv[1],argv[2],a+b);

    return 1;
}
LTSH_FUNCTION_EXPORT(add,"mul a& b");

unsigned int sub(char argc,char ** argv)
{
    int a,b;

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    PRINTF("%s - %s = %d \r\n",argv[1],argv[2],a-b);

    return 1;
}
LTSH_FUNCTION_EXPORT(sub,"mul a& b");



unsigned int iap(char argc,char ** argv)
{
    int cmd;
    uint32_t partID = 0u;
    uint32_t bootCodeVersion = 0u;
    uint32_t * paddr;
    status_t status;
    static uint32_t s_PageBuf[FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES/4];
    memset((void *)s_PageBuf,0x5a,FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES);

    cmd = atoi(argv[1]);

    switch(cmd)
    {
    case 1:
        IAP_ReadPartID(&partID);
        PRINTF("partID = %x.\r\n",partID);
        break;
    case 2:
        IAP_ReadBootCodeVersion(&bootCodeVersion);
        PRINTF("bootCodeVersion = %x.\r\n",bootCodeVersion);
        break;
    case 3:
        PRINTF("dump page data.\r\n");
        paddr =  (uint32_t *)(1023*FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES);
        trace_word_stream(paddr,16,0);
        break;
    case 4:
        PRINTF("erase page data.\r\n");
        /* Erase sector before writing */
        IAP_PrepareSectorForWrite(63, 63);
        IAP_EraseSector(63, 63, SystemCoreClock);
        status = IAP_BlankCheckSector(63, 63);
        if (status != kStatus_IAP_Success)
        {
            PRINTF("\r\nSector erase failed\r\n");
        }
        break;
    case 5:
        PRINTF("write page data.\r\n");
        /* First write a page */
        IAP_PrepareSectorForWrite(63, 63);
        IAP_CopyRamToFlash(1023 * FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES, &s_PageBuf[0],
                       FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES, SystemCoreClock);
        break;
    }

}
LTSH_FUNCTION_EXPORT(iap,"test iap api");

void my_memset1(void * s,uint8_t c,uint32_t count)
{
    char *xs = (char *)s;

    while (count--)
        *xs++ = c;
}

__attribute__((naked))
void my_memset_c(uint8_t ch)
{
	__asm("mov r2,r0 \n"
		  "ldr r0,=0x10003f00 \n"
		  "ldr r1,=0x10003fe0 \n"
		  "1: \n"
		  "strb r2,[r0] \n"
		  "add r0,r0,#1 \n"
		  "cmp	r1, r0 \n"
		  "bne 1b \n"
		  "bx lr \n");
}

unsigned int asmtest(char argc,char ** argv)
{
    int cmd = 0;
    cmd = atoi(argv[1]);
    uint8_t buff[20] = {0xff};
    uint8_t ch = 0x00;

    switch(cmd)
    {
    case 0:
        asm_test_ror();
        break;
    case 1:
        my_memset1((void *)buff,0x55,20);
        break;
    case 2:
        ch = atoi(argv[2]);
        my_memset(ch);
        break;
    case 3:
        ch = atoi(argv[2]);
        my_memset_c(ch);
        break;
    default:
        break;
    }
}
LTSH_FUNCTION_EXPORT(asmtest,"test led on off");


