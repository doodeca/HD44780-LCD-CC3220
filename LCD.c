/*
 * LCD.c
 *
 *   Created on:  Dec 11, 2020
 *  Last update:  Dec 13, 2020
 *       Author:  Jaap Sontrop
 *
 */

#include "LCD.h"
#include <unistd.h>
#include <stdio.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"

void send_nibble(unsigned char data) {
     //data nibble aan juiste datapins koppelen
     if(data & 0x10) // DB4
         GPIO_write(D4, 1);
     else
         GPIO_write(D4, 0);

     if(data & 0x20) // DB5
         GPIO_write(D5, 1);
     else
         GPIO_write(D5, 0);

     if(data & 0x40) // DB6
         GPIO_write(D6, 1);
     else
         GPIO_write(D6, 0);

     if(data & 0x80) // DB7
         GPIO_write(D7, 1);
     else
         GPIO_write(D7, 0);

     sleep(0.01);
     // Enable lijn pulsen om data in te klokken
     GPIO_write(LCD_EN, 1);
     sleep(0.02); // delay 20ms
     GPIO_write(LCD_EN, 0);
}

void send_data(unsigned char data){
    GPIO_write(LCD_RS, 1); // RS hoog om data te sturen
    send_nibble(data & 0xF0);

    GPIO_write(LCD_RS, 1); // RS hoog om data te sturen
    send_nibble((data<<4) & 0xF0);
}

void send_cmd(unsigned char data){
    GPIO_write(LCD_RS, 0); // RS laag om commando te sturen
    send_nibble(data & 0xF0);

    GPIO_write(LCD_RS, 0); // RS laag om commando te sturen
    send_nibble((data<<4) & 0xF0);
}

void lcd_init() {
     GPIO_write(LCD_RS, 0); // RS laag voor commando

     // 100 ms wachten tot lcd driver gestart is
     sleep(0.1);

     // Display driver in 4 bit mode
     send_nibble(0x30);
     send_nibble(0x30);
     send_nibble(0x30);
     send_nibble(0x20);

     // 2 lijnen, 5 x 8 dots font
     send_nibble(0x20);
     send_nibble(0xB0);

     // Display On
     send_nibble(0x00);
     send_nibble(0xF0);

     // Display Clear
     send_nibble(0x00);
     send_nibble(0x80);

     // Entry Mode
     send_nibble(0x00);
     send_nibble(0x10);

     send_nibble(0x00);
     send_nibble(0x60);
     // EIND INIT

     send_nibble(0x00);
     send_nibble(0xE0);
}

void send_str(unsigned char *data){
    int i;
    char buffer[20];
    strcpy(buffer, data); // string van pointer naar buffer schrijven
    for(i = 0; i < strlen(buffer); i++){
        send_data(buffer[i]); // karakter versturen
    }
}
