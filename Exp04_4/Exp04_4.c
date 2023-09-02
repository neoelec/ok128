/* ========================================================================== */
/*                  Exp04_4.c : Stop Watch by Timer/Counter1                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "OK128.h"

volatile unsigned int second;
volatile unsigned char minute, hour;

void Clear_time(void)
{                                              /* clear time */
  second = 0;                                  // clear time
  minute = 0;
  hour = 0;
  LCD_string(0xC0, "  00:00:00.00   ");        // clear display
}

void Set_timer1(void)
{                                              /* initialize Timer1 and OC1A */
  TCCR1A = 0x00;                               // CTC mode(4), don't output OC1A
  TCCR1B = 0x0C;                               // 16MHz/256/(1+624) = 100Hz
  TCCR1C = 0x00;
  OCR1AH = (624 >> 8);
  OCR1AL = 624 & 0xFF;
  TCNT1H = 0x00;                               // clear Timer/Counter1
  TCNT1L = 0x00;

  TIMSK = 0x10;                                // enable OC1A interrupt
  ETIMSK = 0x00;
  TIFR = 0x00;                                 // clear all interrupt flags
  ETIFR = 0x00;
}

void LCD_2digit(unsigned char number)
{                                              /* display 2-digit decimal number */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void Display_time(void)
{                                              /* display time */
  LCD_command(0xC2);                           // display hour
  LCD_2digit(hour);
  LCD_command(0xC5);                           // display minute
  LCD_2digit(minute);
  LCD_command(0xC8);                           // display second
  LCD_2digit(second / 100);
  LCD_command(0xCB);                           // display 1/100 second
  LCD_2digit(second % 100);
}

ISR(TIMER1_COMPA_vect)
{                                              /* OC1A interrupt function */
  second++;                                    // increment 1/100 second
  if (second == 6000) {                        // second = 60 ?
    second = 0;                                // if yes, second = 0 and minute++
    minute++;
    if (minute == 60) {                        // minute = 60 ?
      minute = 0;                              // if yes, minute = 0 and hour++
      hour++;
      if (hour == 100)                         // hour = 100 ?
        hour = 0;                              // if yes, hour = 0
    }
  }
  Display_time();                              // display time
}

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " AVR STOP WATCH ");        // display title
  Clear_time();                                // clear time and display
  Set_timer1();                                // initialize Timer1 and OC1A

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;                            // if SW1, start
      TCNT1H = 0x00;
      TCNT1L = 0x00;
      sei();
      break;
    case 0xB0:
      cli();                                   // if SW3, reset
      PORTB = 0x40;
      Clear_time();
      break;
    case 0x70:
      cli();                                   // if SW4, stop
      PORTB = 0x80;
      break;
    default:
      break;
    }
  }
}
