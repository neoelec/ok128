/* ========================================================================== */
/*	   Exp08_2.c : A/D Converter ADC3 Input by Free Running Mode	      */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "c:\AvrEdit\OK128c\OK128.h"

void LCD_4hex(unsigned int number)              /* display 4-digit hex number */
{ unsigned int i;

  i = number >> 12;                             // 16^3
  if(i <= 9) LCD_data(i + '0');
  else       LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x000F;                   // 16^2
  if(i <= 9) LCD_data(i + '0');
  else       LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x000F;                   // 16^1
  if(i <= 9) LCD_data(i + '0');
  else       LCD_data(i - 10 + 'A');

  i = number & 0x000F;                          // 16^0
  if(i <= 9) LCD_data(i + '0');
  else       LCD_data(i - 10 + 'A');
}

void LCD_1d1(float number)		        /* floating-point number x.x */
{ unsigned int i, j;

  j = (int)(number*10. + 0.5);
  i = j / 10;					// 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;					// 10^-1
  LCD_data(i + '0');
}

int main(void)
{ unsigned char i;
  unsigned int sum;

  MCU_initialize();                             // initialize MCU
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  LCD_string(0x80,"   ADC3 (VR1)   ");          // display title
  LCD_string(0xC0," 0000H = 0.0[V] ");
  Beep();

  ADMUX = 0x03;                                 // select ADC3 with external AREF
  ADCSRA = 0xE7;                                // ADC start with free running mode
  Delay_ms(1);

  while(1)
    { sum = 0;
      for(i=0; i<16; i++)                       // read ADC by 16 times
        { sum += ADCL + ADCH*256;               // add A/D result 16 times
          Delay_ms(1);
        }

      sum = sum >> 4;                           // divide sum by 16

      LCD_command(0xC1);                        // display in HEX
      LCD_4hex(sum);
      LCD_command(0xC9);                        // display in voltage(X.X)
      LCD_1d1(sum*5./1024.);                    // Volt = sum*5/1024

      Delay_ms(200);                            // delay 200 ms
    }
}

