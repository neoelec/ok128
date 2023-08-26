/* ========================================================================== */
/*	    Exp10_3.c : RS-232C Communication using USART0 Interrupt	      */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "c:\AvrEdit\OK128c\OK128.h"

unsigned char cursor;

SIGNAL(SIG_UART0_RECV)                          /* UART0 interrupt function */
{
  LCD_data(UDR0);                               // display a character
  cursor++;                                     // 16 character OK ?
  if(cursor == 16)
    { LCD_command(0xC0);                        // if yes, go home
      cursor = 0;
      Beep();
    }
}

void TX0_char(unsigned char data)		/* transmit a character by USART0 */
{
  while((UCSR0A & 0x20) == 0x00);		// data register empty ?
  UDR0 = data;
}

void TX0_string(unsigned char *string)          /* transmit a string by USART0 */
{
  while(*string != '\0')
    { TX0_char(*string);
       string++;
    }
}

int main(void)
{ unsigned char i;

  MCU_initialize();                             // initialize MCU
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  UBRR0H = 0;                                   // 19200 baud
  UBRR0L = 51;
  UCSR0A = 0x00;                                // asynchronous normal mode
  UCSR0B = 0x98;                                // interrupt enable, 8 data
  UCSR0C = 0x06;                                // no parity, 1 stop, 8 data
  i = UDR0;                                     // dummy read
  sei();                                        // global interrupt enable

  LCD_string(0x80,"RS-232C (USART0)");          // display title
  LCD_string(0xC0,"                ");
  Beep();

  LCD_command(0x0F);                            // cursor ON
  LCD_command(0xC0);                            // initial cursor position
  cursor = 0;

  while(1)
    { switch(Key_input())                       // key input
        { case 0xE0 : PORTB = 0x10;             // SW1 ?
                      TX0_string("SW1 was pressed.");
                      TX0_char(0x0D); TX0_char(0x0A);
                      break;
          case 0xD0 : PORTB = 0x20;             // SW2 ?
                      TX0_string("SW2 was pressed.");
                      TX0_char(0x0D); TX0_char(0x0A);
                      break;
          case 0xB0 : PORTB = 0x40;             // SW3 ?
                      TX0_string("SW3 was pressed.");
                      TX0_char(0x0D); TX0_char(0x0A);
                      break;
          case 0x70 : PORTB = 0x80;             // SW4 ?
                      TX0_string("SW4 was pressed.");
                      TX0_char(0x0D); TX0_char(0x0A);
                      break;
          default:    break;
        }
    }
}

