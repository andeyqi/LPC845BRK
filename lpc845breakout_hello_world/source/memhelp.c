#include "littleshell.h"
#include "fsl_debug_console.h"


unsigned int memlayout(char argc,char ** argv)
{

    PRINTF("+--------------------------------------------------+ \r\n");
    PRINTF("|                   Memory space                   | \r\n");
    PRINTF("+------------------------+-------------------------+ \r\n");
    PRINTF("|      Memory type       |           Addr          | \r\n");
    PRINTF("+------------------------+-------------------------+ \r\n");
    PRINTF("|       (reserved)       | 0xE010 0000~0xFFFF FFFF | \r\n");
    PRINTF("| private peripheral bus | 0xE000 0000~0xE010 0000 | \r\n");
    PRINTF("|       (reserved)       | 0xA000 8000~0xE000 0000 | \r\n");
    PRINTF("|    GPIO interrupts     | 0xA000 4000~0xA000 8000 | \r\n");
    PRINTF("|          GPIO          | 0xA000 0000~0xA000 4000 | \r\n");
    PRINTF("|       (reserved)       | 0x5001 4000~0xA000 0000 | \r\n");
    PRINTF("|    AHB peripherals     | 0x5000 0000~0x5001 4000 | \r\n");
    PRINTF("|       (reserved)       | 0x4008 0000~0x5000 0000 | \r\n");
    PRINTF("|    APB peripherals     | 0x4000 0000~0x4000 8000 | \r\n");
    PRINTF("|       (reserved)       | 0x1000 4000~0x4000 0000 | \r\n");
    PRINTF("|          RAM1          | 0x1000 2000~0x1000 4000 | \r\n");
    PRINTF("|          RAM0          | 0x1000 0000~0x1000 2000 | \r\n");
    PRINTF("|       (reserved)       | 0x0F00 5000~0x1000 0000 | \r\n");
    PRINTF("|        Boot ROM        | 0x0F00 0000~0x0F00 4000 | \r\n");
    PRINTF("|       (reserved)       | 0x0001 0000~0x0F00 0000 | \r\n");
    PRINTF("|      Flash memory      | 0x0000 0000~0x0000 1000 | \r\n");
    PRINTF("+------------------------+-------------------------+ \r\n");

    PRINTF("+------------------------------------------+\r\n");
    PRINTF("|              AHB perpherals              |\r\n");
    PRINTF("+----------------+-------------------------+\r\n");
    PRINTF("| Perpheral type |           Addr          |\r\n");
    PRINTF("+----------------+-------------------------+\r\n");
    PRINTF("|  FAIM memory   | 0x5001 0000~0x5001 4000 |\r\n");
    PRINTF("| MTB registers  | 0x5000 C000~0x5001 0000 |\r\n");
    PRINTF("| DMA controller | 0x5000 8000~0x5000 C000 |\r\n");
    PRINTF("| SCTimer / PWM  | 0x5000 4000~0x5000 8000 |\r\n");
    PRINTF("|   CRC engine   | 0x5000 0000~0x5000 4000 |\r\n");
    PRINTF("+----------------+-------------------------+\r\n");

    PRINTF("+----------------------------------------------+\r\n");
    PRINTF("|                APB perpherals                |\r\n");
    PRINTF("+--------------------+-------------------------+\r\n");
    PRINTF("|   Perpheral type   |           Addr          |\r\n");
    PRINTF("+--------------------+-------------------------+\r\n");
    PRINTF("|     (reserved)     | 0x4007 8000~0x4008 0000 |\r\n");
    PRINTF("|       UART4        | 0x4007 4000~0x4007 8000 |\r\n");
    PRINTF("|       UART3        | 0x4007 0000~0x4007 4000 |\r\n");
    PRINTF("|       UART2        | 0x4006 C000~0x4007 0000 |\r\n");
    PRINTF("|       UART1        | 0x4006 8000~0x4006 C000 |\r\n");
    PRINTF("|       UART0        | 0x4006 4000~0x4006 8000 |\r\n");
    PRINTF("|      CapTouch      | 0x4006 0000~0x4006 4000 |\r\n");
    PRINTF("|        SPI1        | 0x4005 C000~0x4006 0000 |\r\n");
    PRINTF("|        SPI0        | 0x4005 8000~0x4005 C000 |\r\n");
    PRINTF("|        I2C1        | 0x4005 4000~0x4005 8000 |\r\n");
    PRINTF("|        I2C0        | 0x4005 0000~0x4005 4000 |\r\n");
    PRINTF("|     (reserved)     | 0x4004 C000~0x4005 0000 |\r\n");
    PRINTF("|       Syscon       | 0x4004 8000~0x4004 C000 |\r\n");
    PRINTF("|       IOCON        | 0x4004 4000~0x4004 8000 |\r\n");
    PRINTF("|  Flash controller  | 0x4004 0000~0x4004 4000 |\r\n");
    PRINTF("|     (reserved)     | 0x4003 C000~0x4004 0000 |\r\n");
    PRINTF("|      CTIMER 0      | 0x4003 8000~0x4003 C000 |\r\n");
    PRINTF("|        I2C3        | 0x4003 4000~0x4003 8000 |\r\n");
    PRINTF("|        I2C2        | 0x4003 0000~0x4003 4000 |\r\n");
    PRINTF("| Input Multiplexing | 0x4002 C000~0x4003 0000 |\r\n");
    PRINTF("|     (reserved)     | 0x4002 8000~0x4002 C000 |\r\n");
    PRINTF("| Analog Comparator  | 0x4002 4000~0x4002 8000 |\r\n");
    PRINTF("|        PMU         | 0x4002 0000~0x4002 4000 |\r\n");
    PRINTF("|        ADC         | 0x4001 C000~0x4002 0000 |\r\n");
    PRINTF("|        DAC1        | 0x4001 8000~0x4001 C000 |\r\n");
    PRINTF("|        DAC0        | 0x4001 4000~0x4001 8000 |\r\n");
    PRINTF("|  FAIM controller   | 0x4001 0000~0x4001 4000 |\r\n");
    PRINTF("|   Switch Matrix    | 0x4000 C000~0x4001 0000 |\r\n");
    PRINTF("|   Wake-up Timer    | 0x4000 8000~0x4000 C000 |\r\n");
    PRINTF("|  Multi-Rate Timer  | 0x4000 4000~0x4000 8000 |\r\n");
    PRINTF("|   Watchdog timer   | 0x4000 0000~0x4000 4000 |\r\n");
    PRINTF("+--------------------+-------------------------+\r\n");
    return 0;
}

LTSH_FUNCTION_EXPORT(memlayout,"print memory layout");