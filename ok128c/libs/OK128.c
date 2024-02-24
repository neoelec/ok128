/* ------------------------------------------------------------------------------- */
/*  OK128.c : I/O Address Definition & User Function for OK-128 V3.0 Training Kit  */
/* ------------------------------------------------------------------------------- */

#include <avr/io.h>

#include "OK128.h"

void MCU_initialize(void)
{                                              /* initialize ATmega128 MCU & OK-128 kit */
  MCUCR = 0x80;                                // enable external memory and I/O
  XMCRA = 0x44;                                // 0x1100-0x7FFF=1 wait, 0x8000-0xFFFF=0 wait
  XMCRB = 0x80;                                // enable bus keeper, use PC0-PC7 as address

  DDRB = 0xFF;                                 // PORTB = output (D/A, LED1-4, matrix LED)
  PORTB = 0x00;
  DDRD = 0xFF;                                 // PORTD = output (matrix LED)
  PORTD = 0x00;
  DDRE = 0x0C;                                 // PORTE = output for PE3, PE2
  PORTE = 0x00;
  DDRF = 0x00;                                 // PORTF = input (KEY1-4)
  PORTF = 0x00;

  LCD_CONTROL = 0x00;                          // clear LCD/GLCD control signal
  DIG_SELECT = 0x00;                           // clear 7-segment LED
}

void Delay_us(unsigned char time_us)
{                                              /* time delay for us */
  register unsigned char i;

  for (i = 0; i < time_us; i++) {              // 4 cycle +
    asm volatile (" PUSH  R0 ");               // 2 cycle +
    asm volatile (" POP   R0 ");               // 2 cycle +
    asm volatile (" PUSH  R0 ");               // 2 cycle +
    asm volatile (" POP   R0 ");               // 2 cycle +
    asm volatile (" PUSH  R0 ");               // 2 cycle +
    asm volatile (" POP   R0 ");               // 2 cycle = 16 cycle = 1 us for 16MHz
  }
}

void Delay_ms(unsigned int time_ms)
{                                              /* time delay for ms */
  register unsigned int i;

  for (i = 0; i < time_ms; i++) {
    Delay_us(250);
    Delay_us(250);
    Delay_us(250);
    Delay_us(250);
  }
}

void Beep(void)
{                                              /* beep for 50 ms */
  PORTE |= _BV(2);                             // buzzer on
  Delay_ms(50);                                // delay 50 ms
  PORTE &= ~_BV(2);                            // buzzer off
}

void LCD_command(unsigned char command)
{                                              /* write a command(instruction) to text LCD */
  LCD_CONTROL = 0x00;                          // E = 0, Rs = 0
  LCD_DATABUS = command;                       // output command
  LCD_CONTROL = 0x01;                          // E = 1
  asm volatile (" PUSH  R0 ");                 // delay for about 250 ns
  asm volatile (" POP   R0 ");
  LCD_CONTROL = 0x00;                          // E = 0
  Delay_us(50);
}

void LCD_data(unsigned char data)
{                                              /* display a character on text LCD */
  LCD_CONTROL = 0x02;                          // E = 0, Rs = 1
  LCD_DATABUS = data;                          // output data
  LCD_CONTROL = 0x03;                          // E = 1
  asm volatile (" PUSH  R0 ");                 // delay for about 250 ns
  asm volatile (" POP   R0 ");
  LCD_CONTROL = 0x02;                          // E = 0
  Delay_us(50);
}

void LCD_string(unsigned char command, char *string)
{                                              /* display a string on LCD */
  LCD_command(command);                        // start position of string
  while (*string != '\0') {                    // display string
    LCD_data(*string);
    string++;
  }
}

void LCD_initialize(void)
{                                              /* initialize text LCD module */
  LCD_command(0x38);                           // function set(8 bit, 2 line, 5x7 dot)
  LCD_command(0x0C);                           // display control(display ON, cursor OFF)
  LCD_command(0x06);                           // entry mode set(increment, not shift)
  LCD_command(0x01);                           // clear display
  Delay_ms(2);
}

static unsigned char key_flag = 0;

unsigned char Key_input(void)
{                                              /* input key KEY1 - KEY4 */
  unsigned char key;

  key = PINF & 0xF0;                           // any key pressed ?
  if (key == 0xF0) {                           // if no key, check key off
    if (key_flag == 0)
      return key;
    else {
      Delay_ms(20);
      key_flag = 0;
      return key;
    }
  } else {                                     // if key input, check continuous key
    if (key_flag != 0)                         // if continuous key, treat as no key input
      return 0xF0;
    else {                                     // if new key, beep and delay for debounce
      Beep();
      key_flag = 1;
      return key;
    }
  }
}
