/*
 * gpio_driver.c
 *
 *  Created on: Jun 10, 2026
 *      Author: lethi
 */

#include "gpio_driver.h"

#include <stdint.h>
#include <stdbool.h>

void
GPIO_init(GPIO_PORT port, PORT_TYPE type, uint8_t pin, PIN_DIR direction){
    (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + RCGCGPIO))) |= (1U << port);
    
    while (
        (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port) == 0
    );

    GPIO_TypeDef *gpio_port = NULL;


}