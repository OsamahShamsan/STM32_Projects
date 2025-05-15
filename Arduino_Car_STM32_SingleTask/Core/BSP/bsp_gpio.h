#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include "stm32g4xx_hal.h"

// Toggles the given pin(s)
void bsp_gpio_toggle(GPIO_TypeDef *port, uint16_t pin_mask);

// Sets (high) the given pin(s)
void bsp_gpio_set(GPIO_TypeDef *port, uint16_t pin_mask);

// Clears (low) the given pin(s)
void bsp_gpio_clear(GPIO_TypeDef *port, uint16_t pin_mask);

// Reads the value of a pin (returns 0 or 1)
uint8_t bsp_gpio_read(GPIO_TypeDef *port, uint16_t pin_mask);

#endif // BSP_GPIO_H_
