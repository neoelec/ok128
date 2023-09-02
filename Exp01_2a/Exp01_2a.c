/* ========================================================================== */
/*                      Exp01_2a.c : Basic C Program (2)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "c:\AvrEdit\OK128c\OK128.h"

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  OK-128  V2.2  ");        // display logo

  while (1) {
    LCD_string(0xC0, " ATmega128-16AI ");      // display message 1
    Delay_ms(1000);
    LCD_string(0xC0, "   2005/03/01   ");      // display message 2
    Delay_ms(1000);
  }
}
