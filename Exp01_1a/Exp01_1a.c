/* ========================================================================== */
/*                      Exp01_1a.c : Basic C Program (1)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "c:\AvrEdit\OK128c\OK128.h"

int main(void)
{
  MCU_initialize();                            // initialize MCU

  while (1) {
    PORTB = 0x50;                              // LED1, 3 on
    Delay_ms(500);
    PORTB = 0xA0;                              // LED2, 4 on
    Delay_ms(500);
  }
}
