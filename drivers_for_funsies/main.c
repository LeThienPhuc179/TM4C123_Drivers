#include <stdint.h>
#include <stdbool.h>

#include "drivers/gpio_driver.h"

int main(void)
{
	GPIO_Init(PORT_A, APB, 3, INPUT);
	return 0;
}
