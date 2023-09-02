/* ========================================================================== */
/*               Exp10_2.c : RS-232C Communication using USART1               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"

unsigned char RX1_char_scan(void)
{                                              /* receive a character by USART1 */
  if ((UCSR1A & 0x80) == 0x00)                 // if data not received,
    return 0x00;                               //    return with 0x00
  else                                         // if data received,
    return UDR1;                               //    return with data
}

unsigned char RX1_char(void)
{                                              /* receive a character by USART1 */
  while ((UCSR1A & 0x80) == 0x00) ;            // data received ?
  return UDR1;
}

void TX1_char(unsigned char data)
{                                              /* transmit a character by USART1 */
  while ((UCSR1A & 0x20) == 0x00) ;            // data register empty ?
  UDR1 = data;
}

void TX1_string(char *string)
{                                              /* transmit a string by USART1 */
  while (*string != '\0') {
    TX1_char(*string);
    string++;
  }
}

int main(void)
{
  unsigned char i, cursor;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  UBRR1H = 0;                                  // 19200 baud
  UBRR1L = 51;
  UCSR1A = 0x00;                               // asynchronous normal mode
  UCSR1B = 0x18;                               // Rx/Tx enable, 8 data
  UCSR1C = 0x06;                               // no parity, 1 stop, 8 data
  i = UDR1;                                    // dummy read

  LCD_string(0x80, "RS-232C (USART1)");        // display title
  LCD_string(0xC0, "                ");
  Beep();

  LCD_command(0x0F);                           // cursor ON
  LCD_command(0xC0);                           // initial cursor position
  cursor = 0;

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;                            // SW1 ?
      TX1_string("SW1 was pressed.");
      TX1_char(0x0D);
      TX1_char(0x0A);
      break;
    case 0xD0:
      PORTB = 0x20;                            // SW2 ?
      TX1_string("SW2 was pressed.");
      TX1_char(0x0D);
      TX1_char(0x0A);
      break;
    case 0xB0:
      PORTB = 0x40;                            // SW3 ?
      TX1_string("SW3 was pressed.");
      TX1_char(0x0D);
      TX1_char(0x0A);
      break;
    case 0x70:
      PORTB = 0x80;                            // SW4 ?
      TX1_string("SW4 was pressed.");
      TX1_char(0x0D);
      TX1_char(0x0A);
      break;
    default:
      break;
    }

    i = RX1_char_scan();                       // receive data if any
    if (i != 0x00) {
      LCD_data(i);                             // display a character
      cursor++;                                // 16 character OK ?
      if (cursor == 16) {
        LCD_command(0xC0);                     // if yes, go home
        cursor = 0;
        Beep();
      }
    }
  }
}
