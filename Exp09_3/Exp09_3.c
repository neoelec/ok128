/* ========================================================================== */
/*	        Exp09_3.c : D/A Converter Sine Wave by Interrupt	      */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <avr/pgmspace.h>
#include "c:\AvrEdit\OK128c\OK128.h"

unsigned char i;
prog_uchar sin_table[] = {                      // sine wave data table
    0x80,0x88,0x90,0x98,0xA0,0xA7,0xAF,0xB6,0xBD,0xC4,
    0xCB,0xD1,0xD7,0xDD,0xE2,0xE7,0xEB,0xEF,0xF3,0xF6,
    0xF9,0xFB,0xFD,0xFE,0xFF,0xFF,0xFF,0xFE,0xFD,0xFB,
    0xF9,0xF6,0xF3,0xEF,0xEB,0xE7,0xE2,0xDD,0xD7,0xD1,
    0xCB,0xC4,0xBD,0xB6,0xAF,0xA7,0xA0,0x98,0x90,0x88,
    0x80,0x78,0x70,0x68,0x60,0x59,0x51,0x4A,0x43,0x3C,
    0x35,0x2F,0x29,0x23,0x1E,0x19,0x15,0x11,0x0D,0x0A,
    0x07,0x05,0x03,0x02,0x01,0x01,0x01,0x02,0x03,0x05,
    0x07,0x0A,0x0D,0x11,0x15,0x19,0x1E,0x23,0x29,0x2F,
    0x35,0x3C,0x43,0x4A,0x51,0x59,0x60,0x68,0x70,0x78 };

SIGNAL(SIG_OUTPUT_COMPARE1A)                    /* OC1A interrupt function */
{
  PORTB = pgm_read_byte(&sin_table[i]);         // output data to D/A
  i++;
  if(i == 100)
    i = 0;
}

int main(void)
{
  MCU_initialize();                             // initialize MCU
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  LCD_string(0x80,"  DAC0800 D/A   ");          // display title
  LCD_string(0xC0,"100Hz Sine Wave ");
  Beep();

  TCCR1A = 0x00;                                // CTC mode(4), don't output OC1A
  TCCR1B = 0x0A;                                // 16MHz/8/(1+199) = 10kHz
  TCCR1C = 0x00;
  OCR1AH = 0x00;
  OCR1AL = 199;
  TCNT1H = 0x00;                                // clear Timer/Counter1
  TCNT1L = 0x00;

  TIMSK = 0x10;                                 // enable OC1A interrupt
  TIFR = 0x00;                                  // clear all interrupt flags
  sei();                                        // global interrupt enable

  i = 0;

  while(1);                                     // wait interrupt
}

