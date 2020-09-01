#include "7219.h"
#include "SPI_TRANS.h"

extern SPI_HandleTypeDef hspi1;
char dg = 8;

#define CS_SET() 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define CS_RESET() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)


void Send_data (uint8_t rg, uint8_t dt)
{
		uint16_t Word = (uint16_t) rg << 8 | dt;
		CS_RESET();
    HAL_SPI_Transmit (&hspi1, (uint8_t*)&Word, 1, 5000);
		CS_SET();
}


void Clear_data (void)
{
		uint16_t i = dg;
		do
		{
			Send_data(i, 0x0);
		} while(--i);	
}

// Программа отправляет массив команд в max7219

void max7219_sendarray(uint16_t *pArray)
{
		CS_RESET();
    max7219_send16bit(*(pArray++));
		CS_SET();
}


// Программа отправляет 16-битное слово по SPI

void max7219_send16bit(uint16_t Word)
{
	 SPI_I2S_SendData16(SPI1,Word);
	 while (SPI_I2S_GetFlagStatus(SPI1, SPI_FLAG_BSY) == SET);
}
