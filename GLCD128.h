#ifndef __GLCD128_H__
#define __GLCD128_H__

#include <stdint.h>

extern uint8_t xcharacter, ycharacter;         // x character(0-3), y character(0-15)
extern uint8_t cursor_flag, xcursor, ycursor;  // x and y cursor position(0-3, 0-15)

extern void GLCD_command(uint8_t signal, uint8_t command);  /* write a command */
extern void GLCD_data(uint8_t signal, uint8_t character); /* write a data */
extern void GLCD_clear(void);                  /* clear GLCD screen */
extern void GLCD_xy(uint8_t x, uint8_t y);     /* set English character position */
extern void GLCD_xy_row(uint8_t x, uint8_t y, uint8_t row); /* set character upper/lower row */
extern void GLCD_English(uint8_t Ecode);       /* display a 8x16 Dot English(ASCII) */
extern void GLCD_Korean(uint16_t Kcode);       /* display a 16x16 Dot Korean */
extern void GLCD_string(uint8_t x, uint8_t y, char *string);  /* display a string */

#endif /* __GLCD128_H__ */
