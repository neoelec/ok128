/* ========================================================================== */
/*                     Exp02_2.c : Key Input Program (2)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"

void LCD_8bin(unsigned char number)
{                                              /* display 8-bit binary number */
  LCD_data((number >> 7) + '0');
  LCD_data(((number >> 6) & 0x01) + '0');
  LCD_data(((number >> 5) & 0x01) + '0');
  LCD_data(((number >> 4) & 0x01) + '0');
  LCD_data(((number >> 3) & 0x01) + '0');
  LCD_data(((number >> 2) & 0x01) + '0');
  LCD_data(((number >> 1) & 0x01) + '0');
  LCD_data((number & 0x01) + '0');
}

int main(void)
{
  unsigned char key;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "   KEY INPUT    ");        // display title
  LCD_string(0xC0, "PORTF = 11110000");
  Beep();

  while (1) {
    key = Key_input();                         // key input
    switch (key) {
    case 0xE0:
      PORTB = key ^ 0xF0;
      LCD_command(0xC8);
      LCD_8bin(key);
      break;
    case 0xD0:
      PORTB = key ^ 0xF0;
      LCD_command(0xC8);
      LCD_8bin(key);
      break;
    case 0xB0:
      PORTB = key ^ 0xF0;
      LCD_command(0xC8);
      LCD_8bin(key);
      break;
    case 0x70:
      PORTB = key ^ 0xF0;
      LCD_command(0xC8);
      LCD_8bin(key);
      break;
    default:
      break;
    }
  }
}
