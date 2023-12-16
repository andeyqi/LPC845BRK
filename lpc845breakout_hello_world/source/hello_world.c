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
#include "asm_test_c.h"

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

uint32_t ostime = 0;

void english_mode(uint8_t value)
{
    const char * english[] =
    {
     "The ink is black.",
     "I like to eat jam.",
     "I see a nest.",
     "We play in the park.",
     "He has a robot.",
     "This is my mom.",
     "Q said _|, queen quite quiz.",
     "R said _|, robot rocket rabbit",
     "She is a queen.",
     "He has a rabbit.",
     "R said _|, robot rocket rabbit",
     "R said _|, robot rocket rabbit",
     "R said _|, robot rocket rabbit",
     "R said _|, robot rocket rabbit",
     "R said _|, robot rocket rabbit",
     "R said _|, robot rocket rabbit",
    };

    if(value)
    {
        PRINTF("%s.\r\n",english[ostime%(sizeof(english)/sizeof(english[0]))]);
    }
}


void mach_mode(uint8_t value)
{
    static uint8_t a = 0,b = 0,c = 0;

#define MACH_GEN_PROBLEM 0
#define MACH_SHOW_ANS    1

    static uint8_t mach_status =  MACH_GEN_PROBLEM;
    if(value)
    {
        switch(mach_status)
        {
        case MACH_GEN_PROBLEM:
            a = (ostime & 0x0f)%10;
            b = ((ostime >> 4) & 0xf0)%10;
            c = ((ostime >> 8) & 0xf0)%10;

            if(c < 5)
            {
                a = a < 5 ? a+8 : a;
                b = b < 5 ? b+3 : b;
                PRINTF("%d + %d = ? \r\n",a,b);
            }
            else
            {
                a = a > 5 ? a-4 : a;
                b = b > 5 ? b-3 : b;
                PRINTF("%d ¡Á %d = ? \r\n",a,b);
            }
            mach_status = MACH_SHOW_ANS;
            break;
        case MACH_SHOW_ANS:

            if(c < 5)
                PRINTF("%d + %d = %d \r\n",a,b,a+b);
            else
                PRINTF("%d ¡Á %d = %d \r\n",a,b,a*b);

            mach_status = MACH_GEN_PROBLEM;
            break;
        }
    }
}

typedef void (*stdudy_mode)(uint8_t);

stdudy_mode mode = mach_mode;

unsigned int stdudymode(char argc,char ** argv)
{
    if(strcmp("english",argv[1]) == 0)
        mode = english_mode;

    if(strcmp("math",argv[1]) == 0)
        mode = mach_mode;
    return 1;
}
LTSH_FUNCTION_EXPORT(stdudymode,"stdudy mode");

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

            if(!new)
            {
                if(mode)
                {
                    mode(1);
                }
            }
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


unsigned int resetsource(char argc,char ** argv)
{
    uint32_t sys_rst_status = 0;

    sys_rst_status = SYSCON->SYSRSTSTAT;

    PRINTF("SYSRSTSTAT %x \r\n",sys_rst_status);

    if(sys_rst_status & SYSCON_SYSRSTSTAT_POR_MASK)
        PRINTF("POR\r\n");
    if(sys_rst_status & SYSCON_SYSRSTSTAT_EXTRST_MASK)
        PRINTF("EXTRST\r\n");
    if(sys_rst_status & SYSCON_SYSRSTSTAT_WDT_MASK)
        PRINTF("WDT\r\n");
    if(sys_rst_status &SYSCON_SYSRSTSTAT_BOD_MASK)
        PRINTF("BOD\r\n");
    if(sys_rst_status & SYSCON_SYSRSTSTAT_SYSRST_MASK)
        PRINTF("SYSRST\r\n");

    SYSCON->SYSRSTSTAT = sys_rst_status;

    sys_rst_status = SYSCON->SYSRSTSTAT;

    PRINTF("SYSRSTSTAT %x \r\n",sys_rst_status);

    return 1;
}
LTSH_FUNCTION_EXPORT(resetsource,"show reset source");

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
    case 4:
        ch = atoi(argv[2]);
        my_memset_c_1(ch);
        break;
    default:
        break;
    }
}
LTSH_FUNCTION_EXPORT(asmtest,"test led on off");

#if defined (__GNUC__ )

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

unsigned int gccversion(char argc,char ** argv)
{
    PRINTF("GCC_VERSION  %d.\r\n",GCC_VERSION);
}
LTSH_FUNCTION_EXPORT(gccversion,"show gcc version");

unsigned int gccinit(char argc,char ** argv)
{
    uint8_t a[] = {1,2,3,4,5,6,7,8};
    trace_byte_stream(a,8,0);
    uint8_t b[50] = {[10] = 1,[30] = 2};
    trace_byte_stream(b,50,0);
    uint8_t c[50] = {[10 ... 20] = 1,[30 ... 40] = 2};
    trace_byte_stream(c,50,0);
    PRINTF("GCC_VERSION  %d.\r\n",GCC_VERSION);
}
LTSH_FUNCTION_EXPORT(gccinit,"test gcc init");

#endif
