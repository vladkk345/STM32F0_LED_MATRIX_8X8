#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

#include "stm32f0xx.h"

extern uint8_t screenbuff[];

void init(void);
void fill_screenbuff(uint8_t FillValue);
void ScrollLeft(void);
void update_from_buff(void);

#endif /* __LEDMATRIX_H__ */
