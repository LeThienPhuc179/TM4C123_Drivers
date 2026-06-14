#include "gpio_driver.h"

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

static GPIO_TypeDef* const APB_TABLE[] = {
    [PORT_A] = (GPIO_TypeDef *)GPIO_PORTAP_BASE_ADDR,
    [PORT_B] = (GPIO_TypeDef *)GPIO_PORTBP_BASE_ADDR,
    [PORT_C] = (GPIO_TypeDef *)GPIO_PORTCP_BASE_ADDR,
    [PORT_D] = (GPIO_TypeDef *)GPIO_PORTDP_BASE_ADDR,
    [PORT_E] = (GPIO_TypeDef *)GPIO_PORTEP_BASE_ADDR,
    [PORT_F] = (GPIO_TypeDef *)GPIO_PORTFP_BASE_ADDR,
};


static GPIO_TypeDef* const AHB_TABLE[] = {
    [PORT_A] = (GPIO_TypeDef *)GPIO_PORTAH_BASE_ADDR,
    [PORT_B] = (GPIO_TypeDef *)GPIO_PORTBH_BASE_ADDR,
    [PORT_C] = (GPIO_TypeDef *)GPIO_PORTCH_BASE_ADDR,
    [PORT_D] = (GPIO_TypeDef *)GPIO_PORTDH_BASE_ADDR,
    [PORT_E] = (GPIO_TypeDef *)GPIO_PORTEH_BASE_ADDR,
    [PORT_F] = (GPIO_TypeDef *)GPIO_PORTFH_BASE_ADDR,
};


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
GPIO_Init(GPIO_PORT port, PORT_TYPE type, uint8_t pin, PIN_DIR direction){
    (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + RCGCGPIO))) |= (1U << port);
   
    uint32_t PR_GPIO = NULL;
    do {PR_GPIO = (*((volatile uint32_t *)(SYS_CONTROL_BASE_ADDR + PRGPIO))) & (1U << port); } while (PR_GPIO == 0);

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

//TODO
//
void GPIO_Interrupt_Init(GPIO_PORT port, uint8_t mask, INT_ATTR attr){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    gpio_port -> IM &= ~mask;
    gpio_port -> IS &= ~mask;
    if (attr == BOTH_EDGE){
        gpio_port -> IBE |= mask;
        
    } else {
        gpio_port -> IBE &= ~mask;
        if (attr == POS_EDGE){
            gpio_port -> IEV |= mask;
            
        } else {
            gpio_port -> IEV &= ~mask;
            
        }
    }
    gpio_port -> IM |= mask;

    if (port != PORT_F){ 
        (*((volatile uint32_t *)(CORE_PERIPH_BASE_ADDR + EN0))) |= (1U << port);
    } else {
        (*((volatile uint32_t *)(CORE_PERIPH_BASE_ADDR + EN0))) |= (1U << 30);
    }

}


//APB READ
uint8_t read_pin(GPIO_PORT port, uint8_t pin){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    return (uint8_t)(((gpio_port->DR[1U<<pin]) >> pin) & 0x1);
}

uint8_t read_port(GPIO_PORT port){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    return (uint8_t)(gpio_port->DR[255]);
}

uint8_t read_field(GPIO_PORT port, uint8_t mask){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    return (uint8_t)(gpio_port->DR[mask]);
}


//AHB READ
uint8_t read_pin_AHB(GPIO_PORT port, uint8_t pin){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    return (uint8_t)(((gpio_port->DR[1U<<pin]) >> pin) & 0x1);
}

uint8_t read_port_AHB(GPIO_PORT port){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    return (uint8_t)(gpio_port->DR[255]);
}

uint8_t read_field_AHB(GPIO_PORT port, uint8_t mask){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    return (uint8_t)(gpio_port->DR[mask]);
}




void 
output_pin(GPIO_PORT port, uint8_t pin, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    if (val == 0){
        gpio_port->DR[1U << pin] = 0x00;
    } else {
        gpio_port->DR[1U << pin] = 0xFF;
    }    
}


void 
output_port(GPIO_PORT port, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    gpio_port->DR[255] = 0x00;
    gpio_port->DR[255] |= val;
}


void
output_field(GPIO_PORT port, uint8_t mask, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(APB, port);
    if (val == 0){
        gpio_port->DR[mask] = 0x00;
    } else {
        gpio_port->DR[mask] = 0xFF;
    }    
}


void 
output_pin_AHB(GPIO_PORT port, uint8_t pin, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    if (val == 0){
        gpio_port->DR[1U << pin] = 0x00;
    } else {
        gpio_port->DR[1U << pin] = 0xFF;
    }    
}


void 
output_port_AHB(GPIO_PORT port, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    gpio_port->DR[255] = 0x00;
    gpio_port->DR[255] |= val;
}


void
output_field_AHB(GPIO_PORT port, uint8_t mask, uint8_t val){
    GPIO_TypeDef *gpio_port = GET_GPIO_BASE(AHB, port);
    if (val == 0){
        gpio_port->DR[mask] = 0x00;
    } else {
        gpio_port->DR[mask] = 0xFF;
    }    
}