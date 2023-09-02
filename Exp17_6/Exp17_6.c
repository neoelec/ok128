/* ========================================================================== */
/*              Exp17_6.c : printf() Function to Text LCD Module              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <stdio.h>
#include "c:\AvrEdit\OK128c\OK128.h"

int LCD_putchar(char c)
{                                              /* print a character to LCD */
  if ((c < 0x20) | (c > 0x7E))                 // check from 0x20 to 0x7E
    return 0;

  LCD_data(c);
  return 0;
}

int main(void)
{
  unsigned char i = 1;
  double x = 0.001;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  use printf()  ");        // display title
  LCD_string(0xC0, "  to LCD module ");
  Beep();

  fdevopen(LCD_putchar, 0, 0);                 // stdout and stderr device open

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;                            // SW1 ?
      LCD_command(0x80);
      printf("SW1 was pressed.");
      LCD_command(0xC0);
      printf(" i=%03d  x=%5.3f ", i++, x);
      x += 0.001;
      break;
    case 0xD0:
      PORTB = 0x20;                            // SW2 ?
      LCD_command(0x80);
      printf("SW2 was pressed.");
      LCD_command(0xC0);
      printf(" i=%03d  x=%5.3f ", i++, x);
      x += 0.001;
      break;
    case 0xB0:
      PORTB = 0x40;                            // SW3 ?
      LCD_command(0x80);
      printf("SW3 was pressed.");
      LCD_command(0xC0);
      printf(" i=%03d  x=%5.3f ", i++, x);
      x += 0.001;
      break;
    case 0x70:
      PORTB = 0x80;                            // SW4 ?
      LCD_command(0x80);
      printf("SW4 was pressed.");
      LCD_command(0xC0);
      printf(" i=%03d  x=%5.3f ", i++, x);
      x += 0.001;
      break;
    default:
      break;
    }
  }
}
