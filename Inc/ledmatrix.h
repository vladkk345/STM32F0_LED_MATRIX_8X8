#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

#include "stm32f0xx.h"

extern uint8_t ledmatrix_screenbuff[];

void ledmatrix_init(void);
void ledmatrix_fill_screenbuff(uint8_t FillValue);
void ledmatrix_ScrollLeft(void);
void ledmatrix_update_from_buff(void);

#endif /* __LEDMATRIX_H__ */
