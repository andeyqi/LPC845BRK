#include "littleshell.h"
#include "utilities.h"
#include "trace_dump.h"


unsigned int hexdump1(char argc,char ** argv)
{
    int addr = 0,len = 0;

    if( 3 != argc)
        return 1;

    if((argv[1][0] == '0') && (argv[1][1] == 'x' || argv[1][1] == 'X'))
        addr = myatohex(&argv[1][2]);
    else
        addr = myatoi(argv[1]);

    if((argv[2][0] == '0') && (argv[2][1] == 'x' || argv[2][1] == 'X'))
        len = myatohex(&argv[2][2]);
    else
        len = myatoi(argv[2]);

    trace_byte_stream((uint8_t *)addr,len);

    return 0;
}
LTSH_FUNCTION_EXPORT(hexdump1,"dump data with start addr and len");


unsigned int hexdump2(char argc,char ** argv)
{
    int addr1 = 0,addr2 = 0;

    if( 3 != argc)
        return 1;

    if((argv[1][0] == '0') && (argv[1][1] == 'x' || argv[1][1] == 'X'))
        addr1 = myatohex(&argv[1][2]);
    else
        addr1 = myatoi(argv[1]);

    if((argv[2][0] == '0') && (argv[2][1] == 'x' || argv[2][1] == 'X'))
        addr2 = myatohex(&argv[2][2]);
    else
        addr2 = myatoi(argv[2]);

    trace_byte_stream((uint8_t *)addr1,addr2 - addr1 + 1);

    return 0;

}
LTSH_FUNCTION_EXPORT(hexdump2,"dump data with start addr and end addr");



