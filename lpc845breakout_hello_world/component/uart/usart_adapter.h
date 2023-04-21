#ifndef __USART_ADAPTER_H__
#define __USART_ADAPTER_H__

#include <stdint.h>
#include <stdlib.h>
#include "fsl_common.h"

status_t shell_uart_init(void);
uint8_t shell_uart_getchar(uint8_t * pdata);
int shell_uart_putchar(int pdata);
    
#endif