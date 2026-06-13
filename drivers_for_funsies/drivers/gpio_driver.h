/*
 * gpio_drivers.h
 *
 *  Created on: Jun 10, 2026
 *      Author: lethi
 */

#ifndef DRIVERS_GPIO_DRIVER_H_
#define DRIVERS_GPIO_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>


#define SYS_CONTROL_BASE_ADDR   0x400FE000
#define RCGCGPIO                0x608
#define PRGPIO                  0xA08

#define GPIO_PORTAP_BASE_ADDR   0x40004000
#define GPIO_PORTAH_BASE_ADDR   0x40058000
#define GPIO_PORTBP_BASE_ADDR   0x40005000
#define GPIO_PORTBH_BASE_ADDR   0x40059000
#define GPIO_PORTCP_BASE_ADDR   0x40006000
#define GPIO_PORTCH_BASE_ADDR   0x4005A000
#define GPIO_PORTDP_BASE_ADDR   0x40007000
#define GPIO_PORTDH_BASE_ADDR   0x4005B000
#define GPIO_PORTEP_BASE_ADDR   0x40024000
#define GPIO_PORTEH_BASE_ADDR   0x4005C000
#define GPIO_PORTFP_BASE_ADDR   0x40025000
#define GPIO_PORTFH_BASE_ADDR   0x4005D000

static GPIO_TypeDef* const APB_TABLE[] = {
    [PORT_A] = GPIO_PORTAP_BASE_ADDR,
    [PORT_B] = GPIO_PORTBP_BASE_ADDR,
    [PORT_C] = GPIO_PORTCP_BASE_ADDR,
    [PORT_D] = GPIO_PORTDP_BASE_ADDR,
    [PORT_E] = GPIO_PORTEP_BASE_ADDR,
    [PORT_F] = GPIO_PORTFP_BASE_ADDR,
};


static GPIO_TypeDef* const AHB_TABLE[] = {
    [PORT_A] = GPIO_PORTAH_BASE_ADDR,
    [PORT_B] = GPIO_PORTBH_BASE_ADDR,
    [PORT_C] = GPIO_PORTCH_BASE_ADDR,
    [PORT_D] = GPIO_PORTDH_BASE_ADDR,
    [PORT_E] = GPIO_PORTEH_BASE_ADDR,
    [PORT_F] = GPIO_PORTFH_BASE_ADDR,
};

static inline GPIO_TypeDef* GET_GPIO_BASE(PORT_TYPE type, GPIO_PORT port);

typedef enum {
    APB,
    AHB
} PORT_TYPE;

typedef enum {
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3,
    PORT_E = 4,
    PORT_F = 5
} GPIO_PORT;

typedef enum {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN
}PIN_DIR;

typedef struct {
    volatile uint32_t DR[256];      //0x000 to 0x3FC
    volatile uint32_t DIR;          //0x400
    volatile uint32_t IS;           //0x404
    volatile uint32_t IBE;          //0x408
    volatile uint32_t IEV;          //0x40C
    volatile uint32_t IM;           //0x410
    volatile uint32_t RIS;          //0x414
    volatile uint32_t MIS;          //0x418
    volatile uint32_t ICR;          //0x41C
    volatile uint32_t AFSEL;        //0x420
    volatile uint32_t _reserved[55];//padding to 0x500
    volatile uint32_t DR2R;         //0x500
    volatile uint32_t DR4R;         //0x504
    volatile uint32_t DR8R;         //0x508
    volatile uint32_t ODR;          //0x50C
    volatile uint32_t PUR;          //0x510
    volatile uint32_t PDR;          //0x514
    volatile uint32_t SLR;          //0x518
    volatile uint32_t DEN;          //0x51C
    volatile uint32_t LOCK;         //0x520
    volatile uint32_t CR;           //0x524
    volatile uint32_t AMSEL;        //0x528
    volatile uint32_t PCTL;         //0x52C
    volatile uint32_t ADCCTL;       //0x530
    volatile uint32_t DMACTL;       //0x534
} GPIO_TypeDef;

void GPIO_Init(GPIO_PORT port, PORT_TYPE type, uint8_t pin, PIN_DIR direction);

// DEFAULT AHB PORTS
uint8_t read_pin    (GPIO_PORT port, uint8_t pin);

uint8_t read_field  (GPIO_PORT port, uint8_t mask);
uint8_t read_port   (GPIO_PORT port);

uint8_t read_pin_APB    (GPIO_PORT port, uint8_t pin);
uint8_t read_field_APB  (GPIO_PORT port, uint8_t mask);
uint8_t read_port_APB   (GPIO_PORT port);  


//DEFAULT AHB PORTS

//  output_pin: output 0 if val is 0, 1 if otherwise
void output_pin     (GPIO_PORT port, uint8_t pin, uint8_t val);
//output_field: mask to pick which pins being affected, 
//                 output 0 if val is 0, 1 if otherwise
void output_field   (GPIO_PORT port, uint8_t mask, uint8_t val);
//output_port: for funsies, no one will ever use this
//            This is prolly the most useless function of them all
void output_port    (GPIO_PORT port, uint8_t val);

//APB PORTS BECAUSE WHY NOT
void output_pin_APB     (GPIO_PORT port, uint8_t pin, uint8_t val);
void output_field_APB   (GPIO_PORT port, uint8_t mask, uint8_t val);
void output_port_APB    (GPIO_PORT port, uint8_t val);

void GPIO_Interrupt_Init();

#endif