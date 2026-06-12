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
    uint32_t PR_GPIO = NULL;

    do {
        PR_GPIO = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port);
    } while (PR_GPIO == 0);

    GPIO_TypeDef *gpio_port = NULL;

    switch (type){
        case APB:
            switch (port){
                case PORT_A:
                    gpio_port = GPIO_PORTAP_BASE_ADDR;
                    break;
                case PORT_B:
                    gpio_port = GPIO_PORTBP_BASE_ADDR;
                    break;
                case PORT_C:
                    gpio_port = GPIO_PORTCP_BASE_ADDR;
                    break;
                case PORT_D:
                    gpio_port = GPIO_PORTDP_BASE_ADDR;
                    break;
                case PORT_E:
                    gpio_port = GPIO_PORTEP_BASE_ADDR;
                    break;
                case PORT_F:
                    gpio_port = GPIO_PORTFP_BASE_ADDR;
                    break;
            }
            break;
        case AHB:
            switch (port){
                case PORT_A:
                    gpio_port = GPIO_PORTAH_BASE_ADDR;
                    break;
                case PORT_B:
                    gpio_port = GPIO_PORTBH_BASE_ADDR;
                    break;
                case PORT_C:
                    gpio_port = GPIO_PORTCH_BASE_ADDR;
                    break;
                case PORT_D:
                    gpio_port = GPIO_PORTDH_BASE_ADDR;
                    break;
                case PORT_E:
                    gpio_port = GPIO_PORTEH_BASE_ADDR;
                    break;
                case PORT_F:
                    gpio_port = GPIO_PORTFH_BASE_ADDR;
                    break;
            }
            break;
    }

    gpio_port->DEN |= (1U << pin);

    if (direction != OUTPUT){
        if (direction == INPUT){
            gpio_port->DIR &= ~(1U << pin); 
        } else {
            gpio_port->DIR &= ~(1U << pin);
            if (direction == INPUT_PULLUP){
                gpio_port -> PUR |= (1U << pin);
            } else if (direction == INPUT_PULLDOWN){
                gpio_port -> PDR |= (1U << pin);
            }
        }
    } else {
        gpio_port->DIR |= (1U << pin);
    }

    return;
}


void GPIO_Interrupt_Init(){
    
}