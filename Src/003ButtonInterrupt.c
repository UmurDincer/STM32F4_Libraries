/*
 * 003ButtonInterrupt.c
 *
 *  Created on: 12 Oca 2022
 *      Author: umurdincer
 */

#include<string.h>
#include "stm32f407xx.h"

void myDelay(uint32_t value)
{
	for(uint32_t i = 0; i < value; ++i)
		;
}


int main(void)
{
	// LED configuration

	GPIO_Handle_t GpioLed, Button;

	memset(&GpioLed, 0, sizeof(GpioLed));
	memset(&Button, 0, sizeof(Button));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	//Button configuration




	Button.pGPIOx = GPIOD;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&Button);

	GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);
	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);


 	while(1);


}



void EXTI9_5_IRQHandler(void)
{
	myDelay(50000);
	GPIO_IRQHandling(GPIO_PIN_NO_5); // clear pending event from EXTI line
	//GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, 1);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}

