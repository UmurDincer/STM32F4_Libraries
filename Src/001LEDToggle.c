/*
 * 001LEDToggle.c
 *
 *  Created on: 11 Oca 2022
 *      Author: umurdincer
 */


#include "stm32f407xx.h"

void myDelay(uint32_t value)
{
	for(uint32_t i = 0; i < value; ++i)
		;
}
//  Output OPEN-DRAIN MODE

int main(void)
{
	GPIO_Handle_t GpioLed;

		GpioLed.pGPIOx = GPIOD;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; //high internal resistance thats why led almost not seen. but it can be changed with no_pupd
																//then we can be use external resistor. resistor can be connected between PD12 and 5V supply of the board
																// so external pull up resistor will be connected.
		GPIO_PeriClockControl(GPIOD, ENABLE);
		GPIO_Init(&GpioLed);

		while(1){
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			myDelay(500000);
		}

}





//  Output PUSH-PULL MODE
/*
int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	while(1){
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		myDelay(500000);
	}



}
*/
