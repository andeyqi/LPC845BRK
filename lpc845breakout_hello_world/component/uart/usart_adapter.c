#include "ringbuffer.h"
#include "fsl_usart.h"
#include "fsl_common.h"
#include "clock_config.h"
#include "board.h"

static  RingBuffer uart_rx;

status_t shell_uart_init(void)
{
    status_t result;
    usart_config_t usartConfig;
    status_t status;

    /* init uart recive ring buffer */
    static uint8_t uart_rx_buff[128] = {0};
    RingBuffer_Init(&uart_rx,uart_rx_buff,128);

    /* Select the main clock as source clock of USART0 (debug console) */
    CLOCK_Select(BOARD_DEBUG_USART_CLK_ATTACH);
    RESET_PeripheralReset(BOARD_DEBUG_USART_RST);

    /* config usart struct */
    USART_GetDefaultConfig(&usartConfig);
    usartConfig.baudRate_Bps = BOARD_DEBUG_USART_BAUDRATE;
    usartConfig.parityMode = kUSART_ParityDisabled;
    usartConfig.stopBitCount = kUSART_OneStopBit;
    usartConfig.enableRx = true;
    usartConfig.enableTx = true;

    /* init usart */
    status = USART_Init(USART0, &usartConfig, BOARD_DEBUG_USART_CLK_FREQ);

    if (kStatus_Success != status)
    {
        return status;
    }

    /* enable usart rx interrupts */
    USART_EnableInterrupts(USART0, kUSART_RxReadyInterruptEnable | kUSART_RxNoiseInterruptEnable);
    NVIC_EnableIRQ(USART0_IRQn);

}


uint8_t shell_uart_getchar(uint8_t * pdata)
{
    return RingBuffer_Read(&uart_rx,pdata,1);
}


int shell_uart_putchar(int pdata)
{
    if(!USART_WriteBlocking(USART0,(uint8_t *)&pdata,1))
        return 1;
    else
        return 0;
}


void USART0_DriverIRQHandler(void)
{
    uint8_t data = 0;

    if(USART_GetStatusFlags(USART0)&kUSART_RxReady)
    {
        data = USART0->RXDAT;
        RingBuffer_Write(&uart_rx,&data,1);
    }
}

