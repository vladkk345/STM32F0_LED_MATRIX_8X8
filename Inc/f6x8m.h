#ifndef _F6X8M_H
#define _F6X8M_H

#include "stm32f0xx.h"

#define f6x8_MONO_WIDTH         6
#define f6x8_MONO_HEIGHT        8
#define f6x8m_NOFCHARS           256

uint8_t *f6x8m_GetCharTable(uint8_t Char);

#endif /* __F6x8M_H__ */
