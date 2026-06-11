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

typedef struct {
    volatile uint32_t DR[256];  //0x000 to 0x3FC
    volatile uint32_t DIR;      //0x400
    volatile uint32_t IS;       //0x404
    volatile uint32_t IBE;      //0x408
    volatile uint32_t IEV;      //0x40C
    volatile uint32_t IM;       //0x410
    volatile uint32_t RIS;      //0x414
    volatile uint32_t MIS;      //0x418
    volatile uint32_t ICR;      //0x41C
    volatile uint32_t AFSEL;    //0x420
    volatile uint32_t _reserved[55];//padding to 0x500
    volatile uint32_t DR2R;     //0x500
    volatile uint32_t DR4R;     //0x504
    volatile uint32_t DR8R;     //0x508
    volatile uint32_t ODR;      //0x50C
    volatile uint32_t PUR;      //0x510
    volatile uint32_t PDR;      //0x514
    volatile uint32_t SLR;      //0x518
    volatile uint32_t DEN;      //0x51C
    volatile uint32_t LOCK;     //0x520
    volatile uint32_t CR;       //0x524
    volatile uint32_t AMSEL;    //0x528
    volatile uint32_t PCTL;     //0x52C
    volatile uint32_t ADCCTL;   //0x530
    volatile uint32_t DMACTL;   //0x534
} GPIO_TypeDef;



void GPIO_Init();

#endif /* DRIVERS_GPIO_DRIVER_H_ */
