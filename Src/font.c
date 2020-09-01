#include "font.h"
#include "font_6x8m.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Текущий шрифт для вывода текста

uint8_t FontID = FONTID_6X8M;

// Таблица с указателями на функции извлечения таблицы символа шрифта. Шрифт пока один

const t_font_getchar font_table_funcs[] = 
{
		f6x8m_GetCharTable
};


// Программа меняет шрифт

void ChangeFont(uint8_t NewFont)
{
		FontID = NewFont;
}

// Функция возвращает ширину символа Char в пикселях

uint8_t GetCharWidth(uint8_t Char)
{
		uint8_t *pCharTable = font_table_funcs[FontID](Char);
		return *pCharTable;  // Ширина символа
}

// Функция вывода символа Char в буфер из набора байт
// 1 байт буфера = 1 столбец монохромного индикатора
// Возвращает кол-во использованных столбцов, 0 - если не хватило длины буфера (BuffLen)

uint8_t DrawChar(uint8_t Char, uint8_t *pColumnBuff, uint16_t BuffLen)
{
		uint8_t *pCharTable = font_table_funcs[FontID](Char);
		uint8_t CharWidth = *(pCharTable++);  
		uint8_t CharHeight = *(pCharTable++);
  
		if (CharWidth > BuffLen)
			return 0;
  
		for (uint8_t col = 0; col < CharWidth; col++)
		{
			uint8_t ColBuff = 0;
    
		for (uint8_t row = 0; row < CharHeight; row++)
    {
      if (pCharTable[row] & (1 << (7 - col)))
        ColBuff |= (1 << row);
    }
    
    *pColumnBuff = ColBuff;
		pColumnBuff++;
  }
  
		return CharWidth;
}

// Функция вывода текста из строки Str в буфер из набора байт
// 1 байт буфера = 1 столбец монохромного индикатора
// Возвращает кол-во использованных столбцов, 0 - если не хватило длины буфера (BuffLen)

uint16_t DrawString(uint8_t *Str, uint8_t *pColumnBuff, uint16_t BuffLen)
{
		uint16_t BuffOffset = 0;
		uint8_t *StrTemp = Str;
    
  while (*StrTemp != '\0')
  {
    BuffOffset += GetCharWidth(*StrTemp);
    StrTemp++;

    if (BuffOffset > BuffLen) 
      return 0;
  }
  
  BuffOffset = 0;
  StrTemp = Str;
  

  while (*StrTemp != '\0')
  {
    
    uint8_t Width = DrawChar(*StrTemp, pColumnBuff, BuffLen - BuffOffset);
    BuffOffset += Width;
    pColumnBuff += Width;
    StrTemp++;
  }

  return BuffOffset;
}

// Функция форматированного вывода в буфер из набора байт
// 1 байт буфера = 1 столбец монохромного индикатора
// Возвращает кол-во использованных столбцов, 0 - если не хватило длины буфера (BuffLen)

uint16_t text_printf(uint8_t *pColumnBuff, uint16_t BuffLen, const char *args, ...)
{
  char font_Buff[40];
  
  va_list ap;
  va_start(ap, args);
  char len = vsnprintf(font_Buff, sizeof(font_Buff), args, ap);
  va_end(ap);

  return DrawString((uint8_t *)font_Buff, pColumnBuff, BuffLen);
}
