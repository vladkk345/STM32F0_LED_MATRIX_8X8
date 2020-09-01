#include "delay.h"

// Программная задержка ~1 мкс

void delay_us(unsigned int us)
{
  unsigned int tick = 0;
  
  while (us--)
  {
    while (tick < 6)
    {
      tick++;
    }
    tick = 0;
  }
}

// Программная задержка ~1 мс

void delay_ms(unsigned int ms)
{
  while (ms--)
  {
    delay_us(1000);
  }
}

