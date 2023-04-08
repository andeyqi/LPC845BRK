#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define PIN_MODE_OUTPUT         0x00
#define PIN_MODE_INPUT          0x01
#define PIN_MODE_INPUT_PULLUP   0x02
#define PIN_MODE_INPUT_PULLDOWN 0x03
#define PIN_MODE_OUTPUT_OD      0x04


#define LPC48X_PIN(index, port, pin,iocon) {index, port, pin, iocon}


struct pin_index
{
    uint8_t index;
    uint8_t port;
    uint8_t pin;
    uint8_t iocon;
};


void lpc84x_pin_mode(int32_t pin, int32_t mode);
void lpc84x_pin_write(int32_t pin, int32_t value);
int lpc84x_pin_read(int32_t pin);
int lpc84x_pin_get(const char * name);


#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */


