/* ========================================================================== */
/*                       Exp17_3.c : Watchdog Timer (2)                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"

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

  WDTCR = 0x18;                                // enable Watchdog Timer
  WDTCR = 0x0C;                                // timeout = 0.22 sec

  LCD_string(0x80, "Press  SW4/SW1 !");        // display command
  LCD_string(0xC0, "(SW3/SW2=ON/OFF)");
  PORTB = 0x40;                                // LED3 on

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      LCD_string(0x80, "                ");    // SW1
      LCD_string(0xC0, "   Blink LED1   ");
      for (i = 0; i < 20; i++) {
        asm volatile (" WDR ");
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
        asm volatile (" WDR ");
        PORTB ^= 0x80;
        Delay_ms(500);
      }
      LCD_string(0x80, "Press  SW4/SW1 !");
      LCD_string(0xC0, "                ");
      break;
    case 0xD0:
      WDTCR = 0x18;                            // SW2
      WDTCR = 0x00;
      PORTB = 0x20;
      break;
    case 0xB0:
      WDTCR = 0x18;                            // SW3
      WDTCR = 0x0C;
      PORTB = 0x40;
      break;
    default:
      asm volatile (" WDR ");
      break;
    }
  }
}
