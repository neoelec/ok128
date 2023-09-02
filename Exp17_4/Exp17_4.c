/* ========================================================================== */
/*                       Exp17_4.c : External Interrupt                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "OK128.h"

unsigned int INT6_count, INT7_count;

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned int i;
  unsigned char flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

ISR(INT6_vect)
{                                              /* INT6 interrupt function */
  INT6_count++;                                // increment INT6 counter
  LCD_command(0x8D);                           // display INT6 counter
  LCD_3d(INT6_count);

  PORTB = 0x10;                                // turn on LED1
  Delay_ms(500);
  PORTB = 0x00;                                // turn off LED1
}

ISR(INT7_vect)
{                                              /* INT7 interrupt function */
  INT7_count++;                                // increment INT7 counter
  LCD_command(0xCD);                           // display INT7 counter
  LCD_3d(INT7_count);

  PORTB = 0x80;                                // turn on LED4
  Delay_ms(500);
  PORTB = 0x00;                                // turn off LED4
}

int main(void)
{
  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "SW1 : INT6 = 000");        // display title
  LCD_string(0xC0, "SW4 : INT7 = 000");
  Beep();

  DDRE |= 0xC0;                                // PORTE7-6 = output
  PORTE = 0x40;                                // initialize PORTE7-6

  EICRB = 0xB0;                                // INT7 = falling, INT6 = rising
  EIMSK = 0xC0;                                // enable INT7, INT6
  EIFR = 0x00;
  sei();                                       // global interrupt enable

  PORTB = 0x00;                                // turn off all LEDs

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTE &= 0xBF;                           // if SW1, generate INT6(rising edge)
      PORTE |= 0x40;
      break;
    case 0x70:
      PORTE |= 0x80;                           // if SW4, generate INT7(falling edge)
      PORTE &= 0x7F;
      break;
    default:
      break;
    }
  }
}
