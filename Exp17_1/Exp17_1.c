/* ========================================================================== */
/*                Exp17_1.c : Read/Write ATmega128 EEPROM (1)                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"

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

void LCD_2hex(unsigned char number)
{                                              /* display 2-digit hex number */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0F;                           // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

unsigned char EEPROM_read(unsigned int address)
{                                              /* read from EEPROM */
  //  while((EECR & 0x02) == 0x02);                 // if EEWE = 1, wait

  while (EECR & (1 << EEWE)) ;                 // if EEWE = 1, wait
  EEAR = address;                              // if EEWE = 0, read
  EECR |= (1 << EERE);                         // EERE = 1
  return EEDR;                                 // return data
}

void EEPROM_write(unsigned int address, unsigned char byte)
{                                              /* write to EEPROM */
  //  while((EECR & 0x02) == 0x02);                 // if EEWE = 1, wait

  while (EECR & (1 << EEWE)) ;                 // if EEWE = 1, wait
  EEAR = address;                              // if EEWE = 0, write
  EEDR = byte;
  EECR |= (1 << EEMWE);                        // EEMWE = 1
  EECR |= (1 << EEWE);                         // EEWE = 1
}

int main(void)
{
  unsigned char byte;
  unsigned int address;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "ATmega128 EEPROM");        // display title
  LCD_string(0xC0, "0x0000=0x00/0x00");
  Beep();

  for (address = 0x0000; address <= 0x0FFF; address++) {
    LCD_command(0xC2);                         // display address
    LCD_4hex(address);

    LCD_command(0xC9);                         // display write data
    LCD_2hex(0x55);
    EEPROM_write(address, 0x55);               // if EEPROM is ready, write 0x55
    byte = EEPROM_read(address);               // if EEPROM is ready, read
    LCD_command(0xCE);                         // display read data
    LCD_2hex(byte);
    Delay_ms(500);
    if (byte != 0x55) {                        // if error, beep
      Beep();
      Delay_ms(2000);
    }

    LCD_command(0xC9);                         // display write data
    LCD_2hex(0xAA);
    EEPROM_write(address, 0xAA);               // if EEPROM is ready, write 0xAA
    byte = EEPROM_read(address);               // if EEPROM is ready, read
    LCD_command(0xCE);                         // display read data
    LCD_2hex(byte);
    Delay_ms(500);
    if (byte != 0xAA) {                        // if error, beep
      Beep();
      Delay_ms(2000);
    }
  }

  Beep();
  while (1) ;
}
