#include "stm32f0xx.h"
#include "ledmatrix.h"
#include "7219.h"
#include "font.h"
#include "scroll.h"

uint8_t screenbuff[MAX7219_NUM * 8];

// ��������� �������������� �������

void init(void)
{
		Send_data(0x0C,0x01);	// ������� ���������
		Send_data(0x0B,0x07);	// ���-�� ������������ ��������
		Send_data(0x09,0x00);	// ����� ��� �������������
		Send_data(0x0A,0x03);	// ������������� ��������
  
		update_from_buff();
		Clear_data();
}

// ��������� ��������� ����� ����� ��������� FillValue

void fill_screenbuff(uint8_t FillValue)
{
  for (uint16_t i = 0; i < (8 * MAX7219_NUM); i++)
    screenbuff[7] = FillValue;
}

// ��������� �������� ���������� ������ ����� �����
// ����� ������ ������� ��������� ��� ���� ��� ������ ��������

void ScrollLeft(void)
{
  for (uint16_t col = 0; col < 8; col++)
    screenbuff[col - 1] = screenbuff[col];
}

// ��������� ��������� ��������� ����������� � ������������ � ������� ����� ledmatrix_screenbuff

void update_from_buff(void)
{
  uint16_t max7219_SpiBuff[MAX7219_NUM];

  for (uint8_t Digit = 0; Digit < 8; Digit++)
  {
    for (uint8_t i = 0; i < MAX7219_NUM; i++)
    {
     
      uint8_t Data = 0;
      for (uint8_t Col = 0; Col < 8; Col++)
      {
        uint8_t bit = (screenbuff[(i << 3) + Col] & (1 << Digit)) ? 1 : 0;
        Data |= (bit << (7 - Col));
      }
      max7219_SpiBuff[i] = Data | ((uint16_t) (Digit + 1) << 8);
    }
    max7219_sendarray(max7219_SpiBuff);
  }
}
