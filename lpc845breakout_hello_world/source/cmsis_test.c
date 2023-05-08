#include <stdint.h>
#include <stdbool.h>
#if defined (__GNUC__)
#include <cmsis_gcc.h>
#elif defined (__ICCARM__)
#include <cmsis_iar.h>
#endif
#include "littleshell.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int cmsis(char argc,char ** argv)
{
    int cmd = 0;
    cmd = atoi(argv[1]);
    uint32_t u32_temp1,u32_temp2;
    uint16_t u16_temp1,u16_temp2;

    switch(cmd)
    {
    case 0:
        u32_temp1 = 0xaabbccdd;
        u32_temp2 = __REV(u32_temp1);
        PRINTF("0x%x __REV = 0x%x.\r\n",u32_temp1,u32_temp2);
        u32_temp1 = 0xaabbccdd;
        u32_temp2 = __REV16(u32_temp1);
        PRINTF("0x%x __REV16 = 0x%x.\r\n",u32_temp1,u32_temp2);
        u16_temp1 = 0xaabb;
        u16_temp2 = (uint16_t)__REVSH((int16_t)u16_temp1);
        PRINTF("0x%x __REVSH = 0x%x.\r\n",u16_temp1,u16_temp2);
        break;
    default:
        break;
    }
}
LTSH_FUNCTION_EXPORT(cmsis,"cmsis test");

