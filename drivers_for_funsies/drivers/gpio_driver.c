/*
 * gpio_driver.c
 *
 *  Created on: Jun 10, 2026
 *      Author: lethi
 */

#include "gpio_driver.h"

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

static inline GPIO_TypeDef* 
GET_GPIO_BASE(PORT_TYPE type, GPIO_PORT port){
    GPIO_TypeDef *base_addr = NULL;
    if (type == AHB){
        base_addr = AHB_TABLE[port];
    } else {
        base_addr = APB_TABLE[port];
    }
    return base_addr;
};

void
GPIO_init(GPIO_PORT port, PORT_TYPE type, uint8_t pin, PIN_DIR direction){
    (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + RCGCGPIO))) |= (1U << port);
   
    uint32_t PR_GPIO = NULL;
    do {
        PR_GPIO = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port);
    } while (PR_GPIO == 0);

    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(type, port);
    gpio_port->DEN |= (1U << pin);

    if (direction != OUTPUT){
        if (direction == INPUT){
            //Configure the pin as Input
            gpio_port->DIR &= ~(1U << pin); 
        } else {
            gpio_port->DIR &= ~(1U << pin);
            if (direction == INPUT_PULLUP){
                //Configure PULL_UP
                gpio_port -> PUR |= (1U << pin);
            } else if (direction == INPUT_PULLDOWN){
                //COnfigure PULL_DOWN
                gpio_port -> PDR |= (1U << pin);
            }
        }
    } else {
        // Configure the pin as Output
        gpio_port->DIR |= (1U << pin);
    }
    return;
}


void 
output_pin(GPIO_PORT port, uint8_t pin, uint8_t val){
    assert(port <= PORT_F   && "GPIO_PORT port input is out of range");
    assert(pin <= 7         && "pin value is out of range");

    volatile uint32_t port_PR = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port);
    assert(port_PR != 0     && "Check PORT Initialization");

    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    if (val == 0){
        gpio_port->DR[1U << pin] = 0x00;
    } else {
        gpio_port->DR[1U << pin] = 0xFF;
    }    
}

void 
output_port(GPIO_PORT port, uint8_t val){
    assert(port <= PORT_F       && "GPIO_PORT port input is out of range");
    volatile uint32_t port_PR = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port);
    assert(port_PR != 0         && "Check PORT Initialization");

    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    gpio_port->DR[255] = 0x00;
    gpio_port->DR[255] |= val;
}

void
output_field(GPIO_PORT port, uint8_t mask, uint8_t val){
    assert(port <= PORT_F       && "GPIO_PORT port input is out of range");
    volatile uint32_t port_PR = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port);
    assert(port_PR != 0         && "Check PORT Initialization");

    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    if (val == 0){
        gpio_port->DR[mask] = 0x00;
    } else {
        gpio_port->DR[mask] = 0xFF;
    }    
}


void GPIO_Interrupt_Init(){
    
}