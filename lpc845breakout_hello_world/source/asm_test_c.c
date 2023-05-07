#include "asm_test_c.h"

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


void my_memset_c_1(uint8_t ch)
{
	uint32_t start = 0x10003f00;
	uint32_t end = 0x10003fe0;

	asm volatile(
		  "1: \n"
		  "strb %0,[%1] \n"
		  "add %1,%1,#1 \n"
		  "cmp	%1, %2 \n"
		  "bne 1b \n"
		  ::"r"(ch),"r"(start),"r"(end)
		  :"cc","memory");
}

