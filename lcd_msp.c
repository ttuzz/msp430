#include    "msp430.h"
#include    "lcd_msp.h"

void delay_ms(unsigned int ms)
{
ms*=100;
for(;ms>0;ms--);
}

void lcd_write(unsigned char c)
{
nop();
LCD_DATA = (( c & 0xF0 )>>4);
EN_ACKAPA();
LCD_DATA = ((c & 0x0F));
EN_ACKAPA();
}

void lcd_temizle(void)
{
LCD_RS = 0;
lcd_write(0x1);
delay_ms(2);
}

void lcd_puts(const char * s)
{
nop();
LCD_RS = 1;
while(*s)
lcd_write(*s++);
}

void lcd_putch(char c)
{
LCD_RS = 1;
lcd_write(c);
}

void lcd_goto(char x, char y)
{
LCD_RS = 0;
if(x==1)
lcd_write(0x80+((y-1)%16));
else
lcd_write(0xC0+((y-1)%16));
}

void lcd_init()
{
LCD_RS = 0;
LCD_EN = 0;

delay_ms(15);
LCD_EN = 1;
lcd_write(0x02);  // Ýmleç 0x0 konumunda
delay_ms(2);

lcd_write(0x28);  // 4 Bit , Çift Satýr LCD
lcd_write(0x0C);  // Ýmleç Gizleniyor
lcd_temizle();    // Ekran Temizleniyor
lcd_write(0x06);  // Saða doðru yazma aktif
lcd_write(0x80);  // LCD Birinci Satýr Konumunda
}
