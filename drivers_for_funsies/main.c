#include <stdint.h>
#include <stdbool.h>

#include "drivers/gpio_driver.h"

int main(void)
{
	GPIO_Init(PORT_F, APB, 1, OUTPUT);
	GPIO_Init(PORT_F, APB, 2, OUTPUT);
	GPIO_Init(PORT_F, APB, 3, OUTPUT);
	while (1){
		output_field(PORT_F,0xE,1);
	}
	return 0;
}
