#include "scroll.h"
#include "delay.h"
#include "7219.h"
#include "ledmatrix.h"


void demo_ScrollBuff(uint8_t *pBuff, uint16_t ScrollLines, uint8_t RightToLeft)
{
  uint16_t ScrollIdx = (RightToLeft) ? 0 : ScrollLines - 1;

  fill_screenbuff(0x00);  
  
  for (uint16_t i = 0; i < ScrollLines + (MAX7219_NUM * 8); i++)
  {
    if (RightToLeft)    
    {
      ScrollLeft();

      if (i < ScrollLines)
        screenbuff[(MAX7219_NUM * 8) - 1] = pBuff[ScrollIdx++];
      else
        screenbuff[(MAX7219_NUM * 8) - 1] = 0;
    }
      
    update_from_buff();
      
    delay_ms(150);
  }
}
