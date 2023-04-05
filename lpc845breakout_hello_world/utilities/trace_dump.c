#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fsl_debug_console.h"

#define TRACE_DISPLAY_WIDTH          16

#define __OUTPUT_STREAM(__TYPE, __ADDR, __SIZE, __FORMAT_STR, __BLANK)          \
    do {                                                                        \
        int8_t n = 0;                                                           \
        uint16_t line = 0;                                                      \
        uint16_t __Size = (__SIZE);                                             \
        __TYPE *pSrc = (__TYPE *)(__ADDR);                                      \
        uint8_t *pchSrc;                                                        \
                                                                                \
        PRINTF("         ");                                                    \
        for (n = 0; n < (TRACE_DISPLAY_WIDTH / sizeof(__TYPE)); n++) {          \
            PRINTF(__FORMAT_STR, (n*sizeof(__TYPE)));                           \
        }                                                                       \
        PRINTF("\r\n");                                                         \
        while(__Size >= (TRACE_DISPLAY_WIDTH / sizeof(__TYPE))) {               \
            PRINTF("%08x:",TRACE_DISPLAY_WIDTH*(line++));                       \
            for (n = 0; n < (TRACE_DISPLAY_WIDTH / sizeof(__TYPE)); n++) {      \
                PRINTF(__FORMAT_STR, pSrc[n]);                                  \
            }                                                                   \
                                                                                \
            PRINTF("\t");                                                       \
            pchSrc = (uint8_t *)pSrc;                                           \
                                                                                \
            for (n = 0; n < TRACE_DISPLAY_WIDTH; n++) {                         \
                char c = pchSrc[n];                                             \
                if (c >= 127 || c < 32) {                                       \
                    c = '.';                                                    \
                }                                                               \
                PRINTF("%c", c);                                                \
            }                                                                   \
                                                                                \
            PRINTF("\r\n");                                                     \
                                                                                \
            pSrc += (TRACE_DISPLAY_WIDTH / sizeof(__TYPE));                     \
            __Size -= (TRACE_DISPLAY_WIDTH / sizeof(__TYPE));                   \
        }                                                                       \
                                                                                \
        if (__Size > 0) {                                                       \
            PRINTF("%08x:",TRACE_DISPLAY_WIDTH*(line));                         \
            for (n = 0; n < __Size; n++) {                                      \
                PRINTF(__FORMAT_STR, pSrc[n]);                                  \
            }                                                                   \
            for (   n = 0;                                                      \
                    n < (TRACE_DISPLAY_WIDTH/sizeof(__TYPE) - __Size);          \
                    n++) {                                                      \
                PRINTF(__BLANK);                                                \
            }                                                                   \
            PRINTF("\t");                                                       \
            pchSrc = (uint8_t *)pSrc;                                           \
            for (n = 0; n < __Size * sizeof(__TYPE); n++) {                     \
                char c = pchSrc[n];                                             \
                if (c > 127 || c < 32) {                                        \
                    c = '.';                                                    \
                }                                                               \
                PRINTF("%c", c);                                                \
            }                                                                   \
                                                                                \
            PRINTF("\r\n");                                                     \
        }                                                                       \
    } while(0)


#define __OUTPUT_STREAM1(__HEAD,__TYPE, __BASE ,__ADDR, __SIZE, __FORMAT_STR, __BLANK)         \
    do {                                                                                       \
        int8_t n = 0;                                                                          \
        uint16_t line = 0;                                                                     \
        uint16_t __Size = (__SIZE);                                                            \
        __TYPE *pSrc = (__TYPE *)(__ADDR);                                                     \
        uint8_t *pchSrc;                                                                       \
                                                                                               \
        if(__HEAD)                                                                             \
        {                                                                                      \
            PRINTF("         ");                                                               \
            for (n = 0; n < (TRACE_DISPLAY_WIDTH / sizeof(__TYPE)); n++) {                     \
                PRINTF(__FORMAT_STR, (n*sizeof(__TYPE)));                                      \
            }                                                                                  \
            PRINTF("\r\n");                                                                    \
        }                                                                                      \
        while(__Size >= (TRACE_DISPLAY_WIDTH / sizeof(__TYPE))) {                              \
            PRINTF("%08x:",TRACE_DISPLAY_WIDTH*(line++)+(__BASE));                             \
            for (n = 0; n < (TRACE_DISPLAY_WIDTH / sizeof(__TYPE)); n++) {                     \
                PRINTF(__FORMAT_STR, pSrc[n]);                                                 \
            }                                                                                  \
                                                                                               \
            PRINTF("\t");                                                                      \
            pchSrc = (uint8_t *)pSrc;                                                          \
                                                                                               \
            for (n = 0; n < TRACE_DISPLAY_WIDTH; n++) {                                        \
                char c = pchSrc[n];                                                            \
                if (c >= 127 || c < 32) {                                                      \
                    c = '.';                                                                   \
                }                                                                              \
                PRINTF("%c", c);                                                               \
            }                                                                                  \
                                                                                               \
            PRINTF("\r\n");                                                                    \
                                                                                               \
            pSrc += (TRACE_DISPLAY_WIDTH / sizeof(__TYPE));                                    \
            __Size -= (TRACE_DISPLAY_WIDTH / sizeof(__TYPE));                                  \
        }                                                                                      \
                                                                                               \
        if (__Size > 0) {                                                                      \
            PRINTF("%08x:",TRACE_DISPLAY_WIDTH*(line)+(__BASE));                               \
            for (n = 0; n < __Size; n++) {                                                     \
                PRINTF(__FORMAT_STR, pSrc[n]);                                                 \
            }                                                                                  \
            for (   n = 0;                                                                     \
                    n < (TRACE_DISPLAY_WIDTH/sizeof(__TYPE) - __Size);                         \
                    n++) {                                                                     \
                PRINTF(__BLANK);                                                               \
            }                                                                                  \
            PRINTF("\t");                                                                      \
            pchSrc = (uint8_t *)pSrc;                                                          \
            for (n = 0; n < __Size * sizeof(__TYPE); n++) {                                    \
                char c = pchSrc[n];                                                            \
                if (c > 127 || c < 32) {                                                       \
                    c = '.';                                                                   \
                }                                                                              \
                PRINTF("%c", c);                                                               \
            }                                                                                  \
                                                                                               \
            PRINTF("\r\n");                                                                    \
        }                                                                                      \
    } while(0)


void trace_word_stream(uint32_t *pwStream, uint16_t hwSize)
{
    __OUTPUT_STREAM(uint32_t, pwStream, hwSize, "%08X ", "         ");
}

void trace_hword_stream(uint16_t *phwStream, uint16_t hwSize)
{
    __OUTPUT_STREAM(uint16_t, phwStream, hwSize, "%04X ", "     ");
}

void trace_byte_stream(uint8_t *pchStream, uint16_t hwSize)
{
    __OUTPUT_STREAM(uint8_t, pchStream, hwSize, "%02X ", "   ");
}

void trace_byte_stream1(uint32_t base,uint8_t *pchStream, uint16_t hwSize)
{
    __OUTPUT_STREAM1(0,uint8_t, base,pchStream, hwSize, "%02X ", "   ");
}

