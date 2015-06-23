#ifndef __DS1302_H
#define __DS1302_H

#ifdef __cplusplus
 extern "C" {
#endif

// DS1302 port ve bit tanýmlamalarý
#define DS1302_SCLK_BIT			BIT5
#define DS1302_SCLK_PORT		P2OUT
#define DS1302_SCLK_PORT_DIR	P2DIR
#define DS1302_SCLK_PORT_SEL	P2SEL
#define DS1302_SCLK_PORT_SEL2	P2SEL2
#define DS1302_IO_BIT			BIT4
#define DS1302_IO_PORT			P2OUT
#define DS1302_IO_PORT_IN		P2IN
#define DS1302_IO_PORT_DIR		P2DIR
#define DS1302_IO_PORT_SEL		P2SEL
#define DS1302_IO_PORT_SEL2		P2SEL2
#define DS1302_CE_BIT			BIT3
#define DS1302_CE_PORT			P2OUT
#define DS1302_CE_PORT_DIR		P2DIR
#define DS1302_CE_PORT_SEL		P2SEL
#define DS1302_CE_PORT_SEL2		P2SEL2

// Haberleþme iþlemleri için gerekli makro tanýmlamalarý
#define	HIGH_SCLK	DS1302_SCLK_PORT 	|=  DS1302_SCLK_BIT	
#define	LOW_SCLK	DS1302_SCLK_PORT 	&= ~DS1302_SCLK_BIT
#define	HIGH_IO		DS1302_IO_PORT 	 	|=  DS1302_IO_BIT	
#define	LOW_IO		DS1302_IO_PORT 	 	&= ~DS1302_IO_BIT	
#define	HIGH_IO_DIR	DS1302_IO_PORT_DIR	|=  DS1302_IO_BIT	
#define	LOW_IO_DIR	DS1302_IO_PORT_DIR 	&= ~DS1302_IO_BIT
#define READ_IO		DS1302_IO_PORT_IN	&	DS1302_IO_BIT
#define	HIGH_CE		DS1302_CE_PORT 	 	|=  DS1302_CE_BIT	
#define	LOW_CE		DS1302_CE_PORT 	 	&= ~DS1302_CE_BIT
	
// Saat ve tarih bilgisini tutan yapý
struct _DS1302 {
unsigned char Saniye;
unsigned char Dakika;
unsigned char Saat;
unsigned char AyinGunu;
unsigned char Ay;
unsigned char HaftaninGunu;
unsigned char Sene;
};

// DS1302 kütüphanesinde kullanýlan fonksiyon prototipleri
void DS1302_Ayarla(void);
void DS1302_Byte_Yaz(unsigned char veri);
unsigned char DS1302_Byte_Oku(void);
void DS1302_Veri_Yaz(unsigned char adres, unsigned char veri);
unsigned char DS1302_Veri_Oku(unsigned char adres);
unsigned char Sayi_Cevir(unsigned char);
unsigned char BCD_Cevir(unsigned char);
void DS1302_Saat_Tarih_Yaz(struct _DS1302 *ptr);
void DS1302_Saat_Tarih_Oku(struct _DS1302 *ptr);

#ifdef __cplusplus
}
#endif

#endif /*__DS1302_H*/
