#include "drv_gpio.h"
#include "fsl_device_registers.h"
#include <stdio.h>
#include <stdlib.h>
#include "fsl_iocon.h"
#include "fsl_gpio.h"

#define SCON_INDEX(offset) ((offset)/0x04u)

#define PIN_NUM(port, no) (((((port) & 0x1u) << 5) | ((no) & 0x1Fu)))


static const struct pin_index pins[] =
{
    LPC48X_PIN(0,0,0,SCON_INDEX(0x044u)), /* PIO0_0 */
    LPC48X_PIN(1,0,1,SCON_INDEX(0x02cu)),
    LPC48X_PIN(2,0,2,SCON_INDEX(0x018u)),
    LPC48X_PIN(3,0,3,SCON_INDEX(0x014u)),
    LPC48X_PIN(4,0,4,SCON_INDEX(0x010u)),
    LPC48X_PIN(5,0,5,SCON_INDEX(0x00cu)), 
    LPC48X_PIN(6,0,6,SCON_INDEX(0x040u)),
    LPC48X_PIN(7,0,7,SCON_INDEX(0x03cu)),
    LPC48X_PIN(8,0,8,SCON_INDEX(0x038u)), 
    LPC48X_PIN(9,0,9,SCON_INDEX(0x034u)),
    LPC48X_PIN(10,0,10,SCON_INDEX(0x020u)),
    LPC48X_PIN(11,0,11,SCON_INDEX(0x01cu)),
    LPC48X_PIN(12,0,12,SCON_INDEX(0x008u)),
    LPC48X_PIN(13,0,13,SCON_INDEX(0x004u)),
    LPC48X_PIN(14,0,14,SCON_INDEX(0x048u)),
    LPC48X_PIN(15,0,15,SCON_INDEX(0x028u)),
    LPC48X_PIN(16,0,16,SCON_INDEX(0x024u)),
    LPC48X_PIN(17,0,17,SCON_INDEX(0x000u)), 
    LPC48X_PIN(18,0,18,SCON_INDEX(0x078u)),
    LPC48X_PIN(19,0,19,SCON_INDEX(0x074u)),
    LPC48X_PIN(20,0,20,SCON_INDEX(0x070u)), 
    LPC48X_PIN(21,0,21,SCON_INDEX(0x06cu)),
    LPC48X_PIN(22,0,22,SCON_INDEX(0x068u)),
    LPC48X_PIN(23,0,23,SCON_INDEX(0x064u)),
    LPC48X_PIN(24,0,24,SCON_INDEX(0x060u)),
    LPC48X_PIN(25,0,25,SCON_INDEX(0x05cu)),
    LPC48X_PIN(26,0,26,SCON_INDEX(0x058u)), 
    LPC48X_PIN(27,0,27,SCON_INDEX(0x054u)),
    LPC48X_PIN(28,0,28,SCON_INDEX(0x050u)),
    LPC48X_PIN(29,0,29,SCON_INDEX(0x0c8u)), 
    LPC48X_PIN(30,0,30,SCON_INDEX(0x0ccu)),
    LPC48X_PIN(31,0,31,SCON_INDEX(0x08cu)),
    LPC48X_PIN(32,1,0,SCON_INDEX(0x090u)), 
    LPC48X_PIN(33,1,1,SCON_INDEX(0x094u)), 
    LPC48X_PIN(34,1,2,SCON_INDEX(0x098u)),
    LPC48X_PIN(35,1,3,SCON_INDEX(0x0a4u)),
    LPC48X_PIN(36,1,4,SCON_INDEX(0x0a8u)),
    LPC48X_PIN(37,1,5,SCON_INDEX(0x0acu)), 
    LPC48X_PIN(38,1,6,SCON_INDEX(0x0b8u)),
    LPC48X_PIN(39,1,7,SCON_INDEX(0x0c4u)),
    LPC48X_PIN(40,1,8,SCON_INDEX(0x07cu)),
    LPC48X_PIN(41,1,9,SCON_INDEX(0x080u))
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])


/**
  * @brief  pin get
  * @param  name P0.1
  * @retval pin number
  */
int lpc84x_pin_get(const char * name)
{
    int pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -1;
    }
    
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -1;
    }
    
    if ((name[1] >= '0') && (name[1] <= '1'))
    {
        hw_port_num = (int)(name[1] - '0');
    }
    else
    {
        return -1;
    }
    
    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);

    return pin;

}



/**
  * @brief  get pin
  * @param  pin
  * @retval None
  */
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
        index = NULL;
    }
    else
    {
        index = NULL;
    }

    return index;
}


/**
  * @brief  set pin mode
  * @param  pin, mode
  * @retval None
  */
void lpc84x_pin_mode(int32_t pin, int32_t mode)
{
    const struct pin_index *index = NULL;
    uint32_t pin_mode = 0;
    uint8_t modefunc = 0;

    index = get_pin(pin);
    if (index == NULL)
    {
        return;
    }

    switch(mode)
    {
    case PIN_MODE_OUTPUT:
        IOCON_PinMuxSet(IOCON,index->iocon,IOCON_MODE_PULLUP);
        GPIO_PinInit(GPIO, index->port, index->pin, &(gpio_pin_config_t){kGPIO_DigitalOutput, (0)});
        break;
    case PIN_MODE_OUTPUT_OD:
        IOCON_PinMuxSet(IOCON,index->iocon,IOCON_OPENDRAIN_EN);
        GPIO_PinInit(GPIO, index->port, index->pin, &(gpio_pin_config_t){kGPIO_DigitalOutput, (0)});
        break;
    case PIN_MODE_INPUT:
        GPIO_PinInit(GPIO, index->port, index->pin, &(gpio_pin_config_t){kGPIO_DigitalInput, (0)});
        break;
    case PIN_MODE_INPUT_PULLUP:
        IOCON_PinMuxSet(IOCON,index->iocon,IOCON_MODE_PULLUP);
        /* input setting: pull up. */
        GPIO_PinInit(GPIO, index->port, index->pin, &(gpio_pin_config_t){kGPIO_DigitalInput, (0)});
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        IOCON_PinMuxSet(IOCON,index->iocon,IOCON_MODE_PULLDOWN);
        /* input setting: pull down. */
        GPIO_PinInit(GPIO, index->port, index->pin, &(gpio_pin_config_t){kGPIO_DigitalInput, (0)});
        break;
    default:
        break;
    }
}


/**
  * @brief  pin write
  * @param   pin, valuie
  * @retval None
  */
void lpc84x_pin_write(int32_t pin, int32_t value)
{
    const struct pin_index *index = NULL;

    index = get_pin(pin);
    if (index == NULL)
    {
        return;
    }

    GPIO_PinWrite(GPIO,index->port,index->pin,(uint8_t)value);
}



/**
  * @brief  pin read
  * @param  dev, pin
  * @retval None
  */
int lpc84x_pin_read(int32_t pin)
{
    int value = PIN_LOW;
    const struct pin_index *index = NULL;

    index = get_pin(pin);
    if (index == NULL)
    {
        return value;
    }

    value = GPIO_PinRead(GPIO,index->port,index->pin);
    return value;
}

