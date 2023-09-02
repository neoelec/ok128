/* ========================================================================== */
/*              Exp13_3.c : Display Temperature on 7-Segment LED              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "c:\AvrEdit\OK128c\OK128.h"

unsigned char Bin2LED(unsigned char number)
{                                              /* convert binary to LED pattern */
  if (number == 0)
    return 0xFC;
  else if (number == 1)
    return 0x60;
  else if (number == 2)
    return 0xDA;
  else if (number == 3)
    return 0xF2;
  else if (number == 4)
    return 0x66;
  else if (number == 5)
    return 0xB6;
  else if (number == 6)
    return 0xBE;
  else if (number == 7)
    return 0xE4;
  else if (number == 8)
    return 0xFE;
  else if (number == 9)
    return 0xF6;
  else if (number == 10)
    return 0xEE;
  else if (number == 11)
    return 0x3E;
  else if (number == 12)
    return 0x9C;
  else if (number == 13)
    return 0x7A;
  else if (number == 14)
    return 0x9E;
  else if (number == 15)
    return 0x8E;
  else if (number == '-')
    return 0x02;
  else if (number == '.')
    return 0x01;
  else
    return 0x00;
}

void LCD_4hex(unsigned int number)
{                                              /* display 4-digit hex number */
  unsigned int i;

  i = number >> 12;                            // 16^3
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x000F;                  // 16^2
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x000F;                  // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x000F;                         // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

unsigned char digit1, digit2, digit3;

void LCD_2d1(float number)
{                                              /* floating-point number xx.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 100;                                 // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');
  digit1 = i;

  j = j % 100;                                 // 10^0
  i = j / 10;
  LCD_data(i + '0');
  digit2 = i;
  LCD_data('.');

  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
  digit3 = i;
}

int main(void)
{
  unsigned char i;
  unsigned int AD_result;
  float temperature;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  TEMPERATURE   ");        // display title
  LCD_string(0xC0, " 0000H = 00.0");
  LCD_data(0xDF);
  LCD_data('C');
  LCD_data(' ');

  ADMUX = 0x09;                                // ADC1*10 with exterenal Aref
  Delay_us(200);                               // (diferential input)

  while (1) {
    AD_result = 0;

    for (i = 0; i < 64; i++) {                 // read ADC by 64 times
      ADCSRA = 0xD7;                           // ADC start with 125 kHz
      while ((ADCSRA & 0x10) == 0x00) ;
      AD_result += ADCL + ADCH * 256;          // add A/D result 64 times
      Delay_us(10);
    }

    AD_result = AD_result / 64;
    LCD_command(0xC1);                         // display in HEX
    LCD_4hex(AD_result);

    temperature = (float)AD_result *50. / 512.; // display in temperature(XX.X)
    LCD_command(0xC9);
    LCD_2d1(temperature);

    for (i = 0; i < 100; i++) {                // display for 500 ms
      LCD_DATABUS = Bin2LED(digit1);           // ?X.X 'C
      DIG_SELECT = 0x40;
      Delay_ms(1);
      LCD_DATABUS = Bin2LED(digit2) + 0x01;    // X?.X 'C
      DIG_SELECT = 0x20;
      Delay_ms(1);
      LCD_DATABUS = Bin2LED(digit3);           // XX.? 'C
      DIG_SELECT = 0x10;
      Delay_ms(1);
      LCD_DATABUS = 0x40;                      // '
      DIG_SELECT = 0x08;
      Delay_ms(1);
      LCD_DATABUS = Bin2LED(0x0C);             // C
      DIG_SELECT = 0x04;
      Delay_ms(1);
    }

    DIG_SELECT = 0x00;                         // clear 7-segment LED
  }
}
