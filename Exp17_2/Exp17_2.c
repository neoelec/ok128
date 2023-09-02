/* ========================================================================== */
/*                       Exp17_2.c : Watchdog Timer (1)                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/wdt.h>
#include "c:\AvrEdit\OK128c\OK128.h"

int main(void)
{
  unsigned char i;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  OK-128  V2.2  ");        // display title
  LCD_string(0xC0, " Watchdog Timer ");
  PORTE = 0x04;                                // buzzer on
  PORTB = 0x10;                                // LED1 on
  Delay_ms(200);
  PORTB = 0x20;                                // LED2 on
  Delay_ms(200);
  PORTB = 0x40;                                // LED3 on
  Delay_ms(200);
  PORTB = 0x80;                                // LED4 on
  Delay_ms(200);
  PORTB = 0x00;                                // all LED off
  PORTE = 0x00;                                // buzzer off
  Delay_ms(1000);

  wdt_enable(WDTO_1S);                         // enable Watchdog Timer
  // timeout = 0.9 sec

  LCD_string(0x80, "Press  SW4/SW1 !");        // display command
  LCD_string(0xC0, "                ");

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      LCD_string(0x80, "                ");    // SW1
      LCD_string(0xC0, "   Blink LED1   ");
      for (i = 0; i < 20; i++) {
        wdt_reset();
        PORTB ^= 0x10;
        Delay_ms(100);
      }
      LCD_string(0x80, "Press  SW4/SW1 !");
      LCD_string(0xC0, "                ");
      break;
    case 0x70:
      LCD_string(0x80, "                ");    // SW4
      LCD_string(0xC0, "   Blink LED4   ");
      for (i = 0; i < 10; i++) {
        wdt_reset();
        PORTB ^= 0x80;
        Delay_ms(500);
      }
      LCD_string(0x80, "Press  SW4/SW1 !");
      LCD_string(0xC0, "                ");
      break;
    default:
      wdt_reset();
      break;
    }
  }
}
