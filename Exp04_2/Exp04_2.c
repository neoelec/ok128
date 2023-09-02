/* ========================================================================== */
/*                Exp04_2.c : Timer/Counter0 Interrupt(250Hz)                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "OK128.h"

volatile unsigned char interrupt_count;        // interrupt counter

ISR(TIMER0_COMP_vect)
{                                              /* OC0 interrupt function */
  PORTB = PORTB ^ 0x80;                        // toggle LED4
  interrupt_count--;
  if (interrupt_count == 0) {                  // 250th interrupt ?
    interrupt_count = 250;                     // if yes, toggle LED3
    PORTB = PORTB ^ 0x40;
  }
}

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "     Timer0     ");        // display title
  LCD_string(0xC0, "250 Hz Interrupt");
  Beep();

  PORTB = 0xC0;                                // LED4 and 3 on

  TCCR0 = 0x0E;                                // CTC mode(2), don't output OC0
  ASSR = 0x00;                                 // use internal clock
  OCR0 = 249;                                  // 16MHz/256/(1+249) = 250Hz
  TCNT0 = 0x00;                                // clear Timer/Counter0

  TIMSK = 0x02;                                // enable OC0 interrupt
  TIFR = 0x00;                                 // clear all interrupt flags
  sei();                                       // global interrupt enable

  interrupt_count = 250;                       // interrupt counter

  while (1) ;                                  // wait interrupt
}
