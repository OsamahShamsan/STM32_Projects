#include "bsp_gpio.h"

void bsp_gpio_toggle(GPIO_TypeDef *port, uint16_t pin_mask)
{
    if (pin_mask != 0)
    {
        HAL_GPIO_TogglePin(port, pin_mask);
    }
}

void bsp_gpio_set(GPIO_TypeDef *port, uint16_t pin_mask)
{
    if (pin_mask != 0)
    {
        HAL_GPIO_WritePin(port, pin_mask, GPIO_PIN_SET);
    }
}

void bsp_gpio_clear(GPIO_TypeDef *port, uint16_t pin_mask)
{
    if (pin_mask != 0)
    {
        HAL_GPIO_WritePin(port, pin_mask, GPIO_PIN_RESET);
    }
}

uint8_t bsp_gpio_read(GPIO_TypeDef *port, uint16_t pin_mask)
{
    if (pin_mask != 0)
    {
        return (HAL_GPIO_ReadPin(port, pin_mask) == GPIO_PIN_SET) ? 1 : 0;
    }
    return 0;
}
