/***********************************
*
* www.fatihinanc.com
*
* Muhammed Fatih �NAN�
* 25.10.2010
*
* MSP430 i�in 2x16 LCD K�t�phanesi
*
*
***********************************/

#define    LCD_RS       P2OUT_bit.P2OUT_6
#define    LCD_EN       P2OUT_bit.P2OUT_7

#define    LCD_DATA     P1OUT
#define    EN_ACKAPA()  ((LCD_EN = 1),(LCD_EN=0))
#define    nop()        asm("nop")

extern void lcd_write(unsigned char); // LCD ye komut g�ndermeye yarar
extern void lcd_temizle(void);        // LCD ekran� temizler
extern void lcd_puts(const char *);   // LCD ye string ifade yazar
extern void lcd_goto(char,char);      // LCD de sat�r ve st�n olarak istenilen yere gider
extern void lcd_init(void);           // LCD ba�lang�� ayarlar� yap�l�r
extern void lcd_putch(char);          // LCD ye tek karakter yazmak i�in kullan�l�r.
extern void delay_ms(unsigned int);   // Ge�ici delay