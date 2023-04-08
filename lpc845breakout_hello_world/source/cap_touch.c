/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"
#include "fsl_capt.h"
#include "fsl_debug_console.h"

#include <stdbool.h>
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drv_gpio.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_CAPT_BASE            CAPT
#define DEMO_CAPT_IRQn            CMP_CAPT_IRQn
#define DEMO_CAPT_IRQHandler      CMP_CAPT_IRQHandler
#define DEMO_CAPT_ENABLE_PINS     kCAPT_X0Pin
#define DEMO_CAPT_ENABLE_PINS_NUM 1
#define DEMO_CAPT_CLOCK_FREQ      CLOCK_GetFroFreq()

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint16_t g_captRawData[DEMO_CAPT_ENABLE_PINS_NUM];
volatile bool g_captPollDone;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief ISR for CAPT.
 */
void DEMO_CAPT_IRQHandler(void)
{
    uint32_t intStat;
    capt_touch_data_t s_captData;

    intStat = CAPT_GetInterruptStatusFlags(DEMO_CAPT_BASE);

    CAPT_ClearInterruptStatusFlags(DEMO_CAPT_BASE, intStat);

    /* If timeout happens, the board capt capacitor should be changed. */
    if (intStat &
        (kCAPT_InterruptOfYesTouchStatusFlag | kCAPT_InterruptOfNoTouchStatusFlag | kCAPT_InterruptOfTimeOutStatusFlag))
    {
        CAPT_GetTouchData(DEMO_CAPT_BASE, &s_captData);

        g_captRawData[s_captData.XpinsIndex] = s_captData.count;
    }

    if (intStat & kCAPT_InterruptOfPollDoneStatusFlag)
    {
        g_captPollDone = true;
    }
}

void capt_touch_init(void)
{
    capt_config_t captConfig;
    uint32_t captClockFreq;

    PRINTF("CAPT basic continuous example.\r\n");

    /* Initialize CAPT module. */
    CAPT_GetDefaultConfig(&captConfig);

    /* Calculate the clock divider to make sure CAPT work in 2Mhz fclk. */
    captClockFreq           = DEMO_CAPT_CLOCK_FREQ;
    captConfig.clockDivider = (captClockFreq / 2000000U - 1U);
    captConfig.enableXpins  = DEMO_CAPT_ENABLE_PINS;

    /* The CAPT FCLK is set to 2MHz, the delay period between two polling rounds
     * is pollCount * 2096, setting pollCount to 250, then the polling round
     * frequency is about 2Hz, user can change this value to smaller value to
     * for faster polling round.
     */
    captConfig.pollCount = 250;

    CAPT_Init(DEMO_CAPT_BASE, &captConfig);

    /* Enable the interrupts. */
    CAPT_EnableInterrupts(DEMO_CAPT_BASE, kCAPT_InterruptOfYesTouchEnable | kCAPT_InterruptOfNoTouchEnable |
                                              kCAPT_InterruptOfTimeOutEnable | kCAPT_InterruptOfPollDoneEnable);
    NVIC_EnableIRQ(DEMO_CAPT_IRQn);

    /* Set polling mode and start poll. */
    CAPT_SetPollMode(DEMO_CAPT_BASE, kCAPT_PollContinuousMode);    
}

/*!
 * @brief Main function
 */
int capt_touch_main(void *pvParameters)
{
    int pin = lpc84x_pin_get("P1.1");

    lpc84x_pin_mode(pin,PIN_MODE_OUTPUT);
    while (1)
    {
        while (!g_captPollDone)
        {
            vTaskDelay(1);
        }
        if(g_captRawData[0] > 60)
        {
            lpc84x_pin_write(pin,0);
        }
        else
        {
            lpc84x_pin_write(pin,1);
        }
        /* Output the captured data. */
        

        g_captPollDone = false;
    }
}

