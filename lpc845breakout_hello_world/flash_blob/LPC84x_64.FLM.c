#include "flash_blob.h"

#define OPS_OFFSET ((uint32_t)&flash_code)

#define DEV_OFFSET ((uint32_t)&flash_dev)

#define RAM_OFFSET ((uint32_t)&rw_data)

static  uint32_t flash_code[] =
{
    0X47700A80,0X48474948,0X60084449,0X22004847,0X21016102,0X61426141,0X61816141,0X20024943,
    0X70083940,0X47704610,0X47702000,0X4C40B5F8,0X444C2032,0X25004621,0XC461263F,0X483C3114,
    0X44484F3C,0X91003C0C,0X696047B8,0XD10D2800,0XC4612034,0X44484834,0X60206800,0X3C0C4834,
    0X99004448,0X696047B8,0XD0002800,0XBDF82001,0X4D2FB5F8,0X20320A84,0XC511444D,0X310C4629,
    0X4E2C482B,0X460F602C,0X3D084448,0X696847B0,0XD10E2800,0XC5112034,0X602C4823,0X68004448,
    0X48236068,0X44484639,0X47B03D08,0X28006968,0X2001D000,0XB5F8BDF8,0X00064614,0XCC03D10E,
    0X18406862,0X18896821,0X68A11840,0X68E11840,0X69211840,0X42401840,0X3C086160,0X0AB04D14,
    0X2132444D,0X60296068,0X462960A8,0X4F113114,0X91004628,0X696847B8,0XD1112800,0X60AC2033,
    0X20FFC541,0X60683001,0X44484807,0X60A86800,0X3D084807,0X99004448,0X696847B8,0XD0002800,
    0XBDF82001,0X00002EE0,0X00000004,0X40048040,0X00000008,0X0F001FF1,0X00000000,0X00000000,
};

static const uint32_t flash_dev[] =
{
    0X504C0101,0X78343843,0X50414920,0X6B343620,0X6C462042,0X00687361,0X00000000,0X00000000,
    0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
    0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
    0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
    0X00010000,0X00000000,0X00010000,0X00000100,0X00000000,0X000000FF,0X0000012C,0X00000BB8,
    0X00000400,0X00000000,0XFFFFFFFF,0XFFFFFFFF,
};

static uint32_t rw_data[] =
{
    0X00000000,0X00000000,0X504C0101,0X78343843,0X50414920,0X6B343620,0X6C462042,0X00687361,
    0X00000000,0X00000000,
};

register int *pPrgDataBase __asm("r9");

//static flash_blob_device_t  flash_device =
//{
//    (void*)(OPS_OFFSET + 0X0005),  // Init
//    (void*)(OPS_OFFSET + 0X0029),  // UnInit
//    (void*)(OPS_OFFSET + 0X002D),  // EraseChip
//    (void*)(OPS_OFFSET + 0X0071),  // EraseSector
//    (void*)(OPS_OFFSET + 0X00B7),  // ProgramPage
//    (void*)(DEV_OFFSET),
//    (void*)(RAM_OFFSET),
//};

static flash_ops_t flash_device =
{
	.Init = (OPS_OFFSET + 0X0005),  // Init
	.UnInit = (OPS_OFFSET + 0X0029),  // UnInit
	.EraseChip = (OPS_OFFSET + 0X002D),  // EraseChip
	.EraseSector = (OPS_OFFSET + 0X0071),  // EraseSector
	.ProgramPage = (OPS_OFFSET + 0X00B7),  // ProgramPage
	.ptFlashDev = (DEV_OFFSET),
};

#include "littleshell.h"
#include <stdio.h>
#include <stdlib.h>
#include "trace_dump.h"
#include "fsl_debug_console.h"

unsigned int flash(char argc,char ** argv)
{
	int cmd = 0;
    cmd = atoi(argv[1]);

    pPrgDataBase =  rw_data;
    static uint32_t s_PageBuf[64/4];
    memset((void *)s_PageBuf,0xa5,64);

    switch(cmd)
    {
    case 0:/* init */
    	flash_device.Init(0x00,30000000,2);
    	flash_device.EraseSector(1023*64);
    	if(flash_device.ProgramPage(1023*64,64,(unsigned char *)s_PageBuf)!=0)
            PRINTF("FAILED\r\n");
    	break;
    case 1:/* erase sector */
        trace_byte_stream((uint8_t *)flash_dev,sizeof(flash_dev),0x00u);
    	break;
    case 2: /* pragramepase */
        flash_device.UnInit(0);
    	break;
    case 3: /* dump data */
        flash_device.ProgramPage(1023*64,64,(unsigned char *)s_PageBuf);
    	break;
    }
	return 0;
}

LTSH_FUNCTION_EXPORT(flash,"test iap api");
