/***********************************
*
* www.fatihinanc.com
*
* Muhammed Fatih ÝNANÇ
* 25.10.2010
*
* MSP430 için 2x16 LCD Kütüphanesi
*
*
***********************************/

#define    LCD_RS       P2OUT_bit.P2OUT_6
#define    LCD_EN       P2OUT_bit.P2OUT_7

#define    LCD_DATA     P1OUT
#define    EN_ACKAPA()  ((LCD_EN = 1),(LCD_EN=0))
#define    nop()        asm("nop")

extern void lcd_write(unsigned char); // LCD ye komut göndermeye yarar
extern void lcd_temizle(void);        // LCD ekraný temizler
extern void lcd_puts(const char *);   // LCD ye string ifade yazar
extern void lcd_goto(char,char);      // LCD de satýr ve stün olarak istenilen yere gider
extern void lcd_init(void);           // LCD baþlangýç ayarlarý yapýlýr
extern void lcd_putch(char);          // LCD ye tek karakter yazmak için kullanýlýr.
extern void delay_ms(unsigned int);   // Geçici delay