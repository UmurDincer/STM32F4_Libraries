/*
 * 005spi_txonly_arduino.c
 *
 *  Created on: 15 Oca 2022
 *      Author: umurd
 */

// https://www.udemy.com/course/mastering-microcontroller-with-peripheral-driver-development/learn/lecture/24455956#overview


#include "stm32f407xx.h"
#include <string.h>

/* PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 --> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode: 5
 */

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);
	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);
	//MISO
//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&SPIPins);
	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; //generates sclk of 2MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // hardware slave management for NSS pin

	SPI_Init(&SPI2handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t Button;

	Button.pGPIOx = GPIOA;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&Button);
}

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; ++i);
}

int main(void)
{
	char user_data[] = "Hello World";
	// this function is used to initialize the GPIO Pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//this function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	GPIO_ButtonInit();
	/*
	 * making SSOE 1 does NSS output enable.
	 * The NSS pin is automatically managed by the hardware.
	 * i.e. whe SPE=1, NSS will be pulled to low
	 * and NSS pin will be high when SPE = 0
	 */
	 SPI_SSOEConfig(SPI2, ENABLE);
	 while(1){
		 //wait till button is pressed
		 while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));
		 //to avoid de-bouncing related issues 200ms of delay
		 delay();
		 //enable the SPI2 peripheral
		 SPI_PeripheralControl(SPI2, ENABLE);

		 //first send length information
		 uint8_t dataLen = strlen(user_data);
		 SPI_SendData(SPI2, &dataLen, 1);
		 //to send data
		 SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

		 //confirm SPI is not busy
		 while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		 //disable the SPI2 peripheral
		 SPI_PeripheralControl(SPI2, DISABLE);
	 }

}
