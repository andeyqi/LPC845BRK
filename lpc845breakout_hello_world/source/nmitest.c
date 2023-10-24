#include <stdlib.h>
#include <stdio.h>
#include "fsl_pint.h"
#include "littleshell.h"
#include "trace_dump.h"
#include "fsl_debug_console.h"

void pint_cb(pint_pin_int_t pintr, uint32_t pmatch_status)
{
	PRINTF("pint0 ISR\r\n");
}

void NMI_Handler(void)
{
	PRINTF("nmi isr\r\n");
	SYSCON->NMISRC =  ((SYSCON->NMISRC & (~SYSCON_NMISRC_NMIEN_MASK)));
}

unsigned int nmi(char argc,char ** argv)
{
    int cmd = 0;
    cmd = atoi(argv[1]);
    switch(cmd)
    {
    case 0:
        PINT_Init(PINT);
        PINT_PinInterruptConfig(PINT,kPINT_PatternMatchInp0Src,kPINT_PinIntEnableFallEdge,pint_cb);
        NVIC_EnableIRQ(PIN_INT0_IRQn);
    break;
    case 1:
    	NVIC_DisableIRQ(PIN_INT0_IRQn);
    	PINT_PinInterruptClrStatus(PINT,PIN_INT0_IRQn);
    break;
    case 2:
        SYSCON->NMISRC =  ((SYSCON->NMISRC & (~SYSCON_NMISRC_NMIEN_MASK)));

        SYSCON->NMISRC = ((SYSCON->NMISRC &
                               /* Mask bits to zero which are setting */
                               (~(SYSCON_NMISRC_IRQN_MASK)))

                              /* Pin number select for pin interrupt or pattern match engine input. (PIO0_0 to
                               * PIO0_31correspond to numbers 0 to 31 and PIO1_0 to PIO1_31 correspond to numbers 32 to
                               * 63).: 0x04u */
                              | SYSCON_NMISRC_IRQN(PIN_INT0_IRQn));

        SYSCON->NMISRC = ((SYSCON->NMISRC &
                               /* Mask bits to zero which are setting */
                               (~(SYSCON_NMISRC_NMIEN_MASK)))

                              /* Pin number select for pin interrupt or pattern match engine input. (PIO0_0 to
                               * PIO0_31correspond to numbers 0 to 31 and PIO1_0 to PIO1_31 correspond to numbers 32 to
                               * 63).: 0x04u */
                              | SYSCON_NMISRC_NMIEN(1u));

    	break;
    }

    return 0;
}

LTSH_FUNCTION_EXPORT(nmi,"nmi interrupt test");
