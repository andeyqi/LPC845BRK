   .text
    .thumb

/* Reset Handler */
    .thumb_func
    .align 2
    .globl   my_memset
    .type    my_memset, %function
my_memset:
    mov r2,r0
    ldr r0,=0x10003f00
    ldr r1,=0x10003fe0
1:
    strb r2,[r0]
    add r0,r0,#1
    cmp	r1, r0
    bne 1b

    bx lr

    .globl   asm_test_ror
    .type    asm_test_ror, %function

asm_test_ror:
    ldr r0,=0xaabbccdd
    ldr r1,=16
    ror r0,r1

    ldr r0,=0xaabbccdd
    ldr r2,=24
    ror r0,r2

    bx lr
