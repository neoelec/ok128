/* ========================================================================== */
/*                Exp16_1.c : English/Korean Language Display                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include "OK128.h"
#include "GLCD128.h"

int main(void)
{
  unsigned char i;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  GLCD_clear();                                // initialize GLCD screen
  cursor_flag = 0;                             // cursor off

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " English/Korean ");
  Beep();

  while (1) {
    GLCD_string(0, 0, "OK-128 ǡ�a V2.2");     // display screen 1
    GLCD_string(1, 0, "   03/01/2005   ");
    GLCD_string(2, 0, " �鉁 : �E��w  ");
    GLCD_string(3, 0, " �e�� : Ohm�a   ");
    Delay_ms(5000);

    GLCD_string(0, 0, "    �e�� LCD    ");     // display screen 2
    GLCD_string(1, 0, "  HG12605NY-LY  ");
    GLCD_string(2, 0, "                ");
    GLCD_string(3, 0, "128x64 �a��ϢLCD");
    Delay_ms(5000);

    GLCD_string(0, 0, " �w��/�e�i �a�� ");     // display screen 3
    GLCD_string(1, 0, "                ");
    GLCD_string(2, 0, " 8x16���a ASCII ");
    GLCD_string(3, 0, "16x16���a ���s�w");
    Delay_ms(5000);

    GLCD_string(0, 0, "   * �����a *   ");     // display screen 4
    GLCD_string(1, 0, "�a���a���a���A��");
    GLCD_string(2, 0, "   * ��ӡ�a *   ");
    GLCD_string(3, 0, "�a���a��ť�a����");
    Delay_ms(5000);

    GLCD_xy(0, 0);
    for (i = 0x00; i <= 0x3F; i++)             // from 0x00 to 0x3F
      GLCD_English(i);
    Delay_ms(5000);
    GLCD_xy(0, 0);
    for (i = 0x40; i <= 0x7F; i++)             // from 0x40 to 0x7F
      GLCD_English(i);
    Delay_ms(5000);
  }
}
