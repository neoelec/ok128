/* ========================================================================== */
/*                           Exp02_4.c : Bit Access                           */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "c:\AvrEdit\OK128c\OK128.h"

int main(void)
{
  MCU_initialize();                            // initialize MCU

  while (1) {
    PORTB = (1 << 6) | (1 << 4);               // LED1, 3 on
    Delay_ms(500);
    PORTB = _BV(7) | _BV(5);                   // LED2, 4 on
    Delay_ms(500);
  }
}
