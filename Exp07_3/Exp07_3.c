/* ========================================================================== */
/*                      Exp07_3.c : 119 Ambulance Sound                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

int main(void)
{
  unsigned char i, glitch;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "   * SOUND *    ");        // display title
  LCD_string(0xC0, " 119 Ambulance  ");

  TCCR3A = 0x40;                               // CTC mode(12), use OC3A
  TCCR3B = 0x1A;                               // f(OC3A) = 16MHz/8/2/(1+N)
  TCCR3C = 0x00;
  TCNT3H = 0x00;                               // clear Timer/Counter3
  TCNT3L = 0x00;

  while (1) {
    for (i = 0; i < 5; i++) {
      TCCR3B = 0x1A;                           // speaker on
      do {
        glitch = TCNT3L;                       // protect glitch
        glitch = TCNT3H;
      } while (glitch >= (2082 >> 8));
      ICR3H = (2082 >> 8);                     // 480 Hz
      ICR3L = 2082 & 0xFF;
      Delay_ms(500);                           // delay for 500 ms

      do {
        glitch = TCNT3L;                       // protect glitch
        glitch = TCNT3H;
      } while (glitch >= (2777 >> 8));
      ICR3H = (2777 >> 8);                     // 360 Hz
      ICR3L = 2777 & 0xFF;
      Delay_ms(500);                           // delay for 500 ms
    }

    TCCR3B = 0x18;                             // speaker off
    Delay_ms(1000);                            // delay for 1 sec
  }
}
