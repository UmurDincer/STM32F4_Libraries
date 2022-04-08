/*
 * 006spi_tx_testing.c
 *
 *  Created on: Feb 10, 2019
 *      Author: admin
 */

#include<string.h>
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000 ; i ++);
}

/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 -> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 */

/* SPI Slave Demo
 *
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select . Arduino SPI pins respond only if SS pulled low by the master
 *
 */
/*
 * main.c
 *
 *  Created on: 11 Şub 2022
 *      Author: umurd
 */
#include "stm32f407xx.h"
#include <string.h>
/*
 * PA4 --> SPI1_NSS
 * PA5 --> SPI1_SCK
 * PA6 --> SPI1_MISO
 * PA7 --> SPI1_MOSI
 * PORT --> AF5
 */

void my_delay(uint32_t value)
{
	for(uint32_t i = 0 ; i < value; ++i);
}

void GPIO_SPI_Init(void)
{
	GPIO_Handle_t spi_n;

	spi_n.pGPIOx = GPIOA;
	spi_n.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spi_n.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	spi_n.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spi_n.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	spi_n.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//NSS
	spi_n.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&spi_n);

	//SCK
	spi_n.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&spi_n);

	//MOSI
	spi_n.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&spi_n);
}

void SPI1_Init(void)
{
	SPI_Handle_t spi1;

	spi1.pSPIx = SPI1;

	spi1.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	spi1.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	spi1.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	spi1.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	spi1.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	spi1.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	spi1.SPIConfig.SPI_SSM = SPI_SSM_DI;  //Hardware slave management enabled for NSS pin

	SPI_Init(&spi1);
}

void GPIO_Button_and_Led(void)
{
	GPIO_Handle_t button;
	GPIO_Handle_t led;

	button.pGPIOx =GPIOA;
	button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0; // user button
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&button);

	led.pGPIOx =GPIOD;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&led);
}

int main()
{
	char my_data[] = "Ground Control to Major Tom";
	GPIO_Button_and_Led();

	GPIO_SPI_Init();
	SPI1_Init();


	SPI_SSOEConfig(SPI1, ENABLE); // activate the SS output for master mode

	while(1)
	{
	   while(! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

		my_delay(200000);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, SET);
		SPI_PeripheralControl(SPI1, ENABLE);

		uint8_t length = strlen(my_data);

		SPI_SendData(SPI1, &length, 1); // sent the length information

		SPI_SendData(SPI1, (uint8_t*)my_data , strlen(my_data));

		while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI1, DISABLE);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, RESET);

	   }



}



/*
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
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);


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
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; //Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);

}


int main(void)
{
	char user_data[] = "An Arduino Uno";
	GPIO_ButtonInit();

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	/*
	* making SSOE 1 does NSS output enable.
	* The NSS pin is automatically managed by the hardware.
	* i.e when SPE=1 , NSS will be pulled to low
	* and NSS pin will be high when SPE=0
	*/
/*	SPI_SSOEConfig(SPI2,ENABLE);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,ENABLE);

		//first send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2,&dataLen,1);

		//to send data
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

		//lets confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
	}

	return 0;

}
*/
