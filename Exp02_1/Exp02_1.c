/* ========================================================================== */
/*                     Exp02_1.c : Key Input Program (1)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "   KEY INPUT    ");        // display title
  LCD_string(0xC0, "Press SW1-SW4 ! ");
  Beep();

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;
      LCD_string(0xC0, "SW1 was pressed.");
      break;
    case 0xD0:
      PORTB = 0x20;
      LCD_string(0xC0, "SW2 was pressed.");
      break;
    case 0xB0:
      PORTB = 0x40;
      LCD_string(0xC0, "SW3 was pressed.");
      break;
    case 0x70:
      PORTB = 0x80;
      LCD_string(0xC0, "SW4 was pressed.");
      break;
    default:
      break;
    }
  }
}
