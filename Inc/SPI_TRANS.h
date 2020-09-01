#ifndef __SPI_TRANS_H__
#define __SPI_TRANS_H__

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

void SPI_I2S_SendData16(SPI_TypeDef* SPIx, uint16_t Data);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);

#endif /* __SPI_TRANS_H__ */
