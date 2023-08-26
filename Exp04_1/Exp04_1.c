/* ========================================================================== */
/*	             Exp04_1.c : Timer/Counter1 Interrupt(1Hz)	              */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "c:\AvrEdit\OK128c\OK128.h"

SIGNAL(SIG_OUTPUT_COMPARE1A)                    /* OC1A interrupt function */
{
  PORTB = PORTB ^ 0x80;                         // toggle LED4
}

int main(void)
{
  MCU_initialize();                             // initialize MCU
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  LCD_string(0x80,"     Timer1     ");          // display title
  LCD_string(0xC0," 1 Hz Interrupt ");
  Beep();

  PORTB = 0x80;                                 // LED4 on

  TCCR1A = 0x00;                                // CTC mode(4), don't output OC1A
  TCCR1B = 0x0C;                                // 16MHz/256/(1+62499) = 1Hz
  TCCR1C = 0x00;
  OCR1AH = (62499 >> 8);
  OCR1AL = 62499 & 0xFF;
  TCNT1H = 0x00;                                // clear Timer/Counter1
  TCNT1L = 0x00;

  TIMSK = 0x10;                                 // enable OC1A interrupt
  ETIMSK = 0x00;
  TIFR = 0x00;                                  // clear all interrupt flags
  ETIFR = 0x00;
  sei();                                        // global interrupt enable

  while(1);                                     // wait interrupt
}

