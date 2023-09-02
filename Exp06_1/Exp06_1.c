/* ========================================================================== */
/*                Exp06_1.c : Digital Clock on Text LCD Module                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "OK128.h"

volatile unsigned char second, minute, hour, ampm;

void LCD_2digit(unsigned char number)
{                                              /* display 2-digit decimal number */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

ISR(SIG_OUTPUT_COMPARE1A)
{                                              /* OC1A interrupt function */
  second++;                                    // increment second
  if (second == 60) {                          // if second = 60, second = 0
    second = 0;
    minute++;                                  // increment minute
    if (minute == 60) {                        // if minute = 60, minute = 0
      minute = 0;
      hour++;                                  // increment hour
      if (hour == 13)                          // if hour = 13, hour = 1
        hour = 1;
      if (hour == 12) {                        // if hour = 12, adjust AM/PM
        if (ampm == 'A')
          ampm = 'P';
        else
          ampm = 'A';
      }
    }
  }

  LCD_command(0xC2);                           // display hour
  LCD_2digit(hour);
  LCD_command(0xC5);                           // display minute
  LCD_2digit(minute);
  LCD_command(0xC8);                           // display second
  LCD_2digit(second);
  LCD_command(0xCB);                           // display AM/PM
  LCD_data(ampm);
}

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " Digital Clock  ");        // display title
  LCD_string(0xC0, "  12:00:00 AM   ");

  hour = 12;                                   // initial time
  minute = 0;
  second = 0;
  ampm = 'A';

  TCCR1A = 0x00;                               // CTC mode(4), don't output OC1A
  TCCR1B = 0x0C;                               // 16MHz/256/(1+62499) = 1Hz
  TCCR1C = 0x00;
  OCR1AH = (62499 >> 8);
  OCR1AL = 62499 & 0xFF;

  TIMSK = 0x10;                                // enable OC1A interrupt
  ETIMSK = 0x00;
  TIFR = 0x00;                                 // clear all interrupt flags
  ETIFR = 0x00;
  sei();                                       // global interrupt enable

  while (1) ;
}
