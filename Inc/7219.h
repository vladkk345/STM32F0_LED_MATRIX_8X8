#ifndef __7219_H__
#define __7219_H__

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

void Send_data (uint8_t rg, uint8_t dt);
void Clear_data (void);
void max7219_send16bit(uint16_t Word);
void max7219_sendarray(uint16_t *pArray);

#define MAX7219_NUM             1

#endif /* __7219_H__ */
