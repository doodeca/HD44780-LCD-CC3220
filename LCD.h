/*
 * LCD.h
 *
 *   Created on:  Dec 11, 2020
 *  Last update:  Dec 13, 2020
 *       Author:  Jaap Sontrop
 *
 *  Deze library is gemaakt voor het aansturen van een
 *  display met een HD44780 driver en een CC3220S MCU
 *
 *  Gebaseerd op werk van aostanin: https://github.com/aostanin/avr-hd44780
 *  Datasheet: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *
 */

#ifndef LCD_H_
#define LCD_H_

#define CLEAR_LCD   0x01    // scherm leegmaken
#define RET_HOME    0x02    // cursor terug naar beginpositie
#define CURSOR_POS  0x08    // positie instellen, CURSOR_POS | ADRES

// regels voor 4x20 display, bij 2x16 display alleen LINE_1 en LINE_3 gebruiken
#define LINE_1      0x00
#define LINE_2      0x40
#define LINE_3      0x14
#define LINE_4      0x54

void send_cmd(unsigned char data);      // versturen van commando/instructie naar display
void send_data(unsigned char data);     // versturen van een karakter naar display
void send_nibble(unsigned char data);   // versturen van 4 bits data
void lcd_init();                        // initialiseren van display
void send_str(unsigned char *data);     // string naar display sturen


#endif /* LCD_H_ */
