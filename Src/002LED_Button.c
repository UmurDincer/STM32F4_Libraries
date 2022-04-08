/*
 * 002LED_Button.c
 *
 *  Created on: 11 Oca 2022
 *      Author: umurd
 */

#include "stm32f407xx.h"

void myDelay(uint32_t value)
{
	for(uint32_t i = 0; i < value; ++i)
		;
}

void LedConfig(void)
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
}

void ButtonConfig(void)
{
	GPIO_Handle_t Button;

	Button.pGPIOx = GPIOA;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&Button);
}
int main(void)
{

	LedConfig();
	ButtonConfig();
	;

	while(1){
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			myDelay(500000);
		}
		else
			GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, SET);
	}

}

