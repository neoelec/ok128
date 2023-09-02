/* ========================================================================== */
/*                    Exp17_7.c : Change printf() Function                    */
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

void USART0_initialize(void)
{                                              /* initialize USART0 */
  UBRR0H = 0;                                  // 19200 baud
  UBRR0L = 51;
  UCSR0A = 0x00;                               // asynchronous normal mode
  UCSR0B = 0x18;                               // Rx/Tx enable, 8 data
  UCSR0C = 0x06;                               // no parity, 1 stop, 8 data
}

int USART0_putchar(char c)
{                                              /* print a character to USART0 */
  if (c == '\n')                               // process CR(carriage return)
    USART0_putchar('\r');

  loop_until_bit_is_set(UCSR0A, UDRE0);        // Tx ready ?
  UDR0 = c;                                    // if yes, print
  return 0;
}

int main(void)
{
  unsigned char i = 1;
  double x = 0.001;
  FILE *fp;                                    // file pointer to be opened

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "SW1=LCD, SW4=232");        // display title
  LCD_string(0xC0, "                ");
  Beep();

  USART0_initialize();                         // initialize USART0

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;                            // SW1 ?
      fp = fdevopen(LCD_putchar, 0, 0);
      LCD_command(0xC0);
      printf(" i=%03d  x=%5.3f ", i++, x);
      fclose(fp);
      x += 0.001;
      break;
    case 0x70:
      PORTB = 0x80;                            // SW4 ?
      fp = fdevopen(USART0_putchar, 0, 0);
      printf(" i=%03d  x=%5.3f\n", i++, x);
      fclose(fp);
      x += 0.001;
      break;
    default:
      break;
    }
  }
}
