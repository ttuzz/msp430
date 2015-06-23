/*
 Erhan YILMAZ
 17-05-2014
 MSP430 denetleyiciler için DS1302 gerçek zamanlý saat kütüphanesidir.
 MSP430G2553 denetleyicisinde 1MHz dahili osilatör ile test edilmiþtir.
 */

#include "msp430.h"		// MSP430 baþlýk dosyasý
#include "ds1302.h"		// DS1302 baþlýk dosyasý

// DS1302 baþlangýç ayarlarýný yapan fonksiyon
void DS1302_Ayarla(void){
	unsigned char temp;
	DS1302_SCLK_PORT_DIR  |=  DS1302_SCLK_BIT;
	DS1302_SCLK_PORT_SEL  &= ~DS1302_SCLK_BIT;
	DS1302_SCLK_PORT_SEL2 &= ~DS1302_SCLK_BIT;
	DS1302_IO_PORT_DIR    |=  DS1302_IO_BIT;
	DS1302_IO_PORT_SEL    &= ~DS1302_IO_BIT;
	DS1302_IO_PORT_SEL2   &= ~DS1302_IO_BIT;
	DS1302_CE_PORT_DIR    |=  DS1302_CE_BIT;
	DS1302_CE_PORT_SEL    &= ~DS1302_CE_BIT;
	DS1302_CE_PORT_SEL2   &= DS1302_CE_BIT;
	LOW_CE;
	LOW_SCLK;
	DS1302_Veri_Yaz(0x80,0);
	DS1302_Veri_Yaz(0x90,0xa4);
	temp=DS1302_Veri_Oku(0x81);
	if((temp & 0x80) != 0)
	DS1302_Veri_Yaz(0x80,0);
}

// DS1302'ye bir byte veri yazan fonksiyon
void DS1302_Byte_Yaz(unsigned char veri){
	unsigned char temp;
	HIGH_IO_DIR;
	for(temp=0;temp<8;temp++){
	LOW_IO;
	if(veri & 0x01) HIGH_IO;
	veri >>= 1;
	LOW_SCLK;
	HIGH_SCLK;
	}
}

// DS1302'den bir byte veri okuyan fonksiyon
unsigned char DS1302_Byte_Oku(void){
	unsigned char temp,veri=0;
	LOW_IO_DIR;
	for(temp=0;temp<8;temp++){
	HIGH_SCLK;
	LOW_SCLK;
	veri >>= 1;
	if(READ_IO) veri |= 0x80;
	}
	return veri;
}

// DS1302'nin belirtilen adresine bir byte veri yazan fonksiyon
void DS1302_Veri_Yaz(unsigned char adres, unsigned char veri){
	LOW_SCLK;
	HIGH_CE;
	DS1302_Byte_Yaz(adres);
	DS1302_Byte_Yaz(veri);
	LOW_CE;
}

// DS1302'nin belirtilen adresinden bir byte veri okuyan fonksiyon
unsigned char DS1302_Veri_Oku(unsigned char adres){
	unsigned char temp;
	HIGH_CE;
	DS1302_Byte_Yaz(adres);
	temp = DS1302_Byte_Oku();
	LOW_CE;
	return temp;
}

// Girilen desimal sayýyý BCD sayýya çeviren fonksiyon
unsigned char BCD_Cevir(unsigned char sayi){
   unsigned char niblel, nibleh;
   niblel = sayi%10;
   nibleh = sayi/10;
   return((nibleh<<4)+niblel);
}

// Girilen BCD sayýyý desimal sayýya çeviren fonksiyon
unsigned char Sayi_Cevir(unsigned char BCD){
	unsigned char temp1,temp2;
	temp1=((BCD>>4)&0x0f)*10;
	temp2=BCD&0x0f;
	BCD=temp1+temp2;
	return BCD;
}

// DS1302'ye saat ve tarih ayarlarýný kayýt eden fonksiyon
void DS1302_Saat_Tarih_Yaz(struct _DS1302 *DS1302){
	DS1302_Veri_Yaz(0x86,BCD_Cevir(DS1302->AyinGunu));
	DS1302_Veri_Yaz(0x88,BCD_Cevir(DS1302->Ay));
	DS1302_Veri_Yaz(0x8c,BCD_Cevir(DS1302->Sene));
	DS1302_Veri_Yaz(0x8a,BCD_Cevir(DS1302->HaftaninGunu));
	DS1302_Veri_Yaz(0x84,BCD_Cevir(DS1302->Saat));
	DS1302_Veri_Yaz(0x82,BCD_Cevir(DS1302->Dakika));
	DS1302_Veri_Yaz(0x80,0x00);
}

// DS1302'den saat ve tarih bilgilerini okuyan fonksiyon
void DS1302_Saat_Tarih_Oku(struct _DS1302 *DS1302){
	DS1302->Saniye = Sayi_Cevir(DS1302_Veri_Oku(0x81)&0x7f);
	DS1302->Dakika = Sayi_Cevir(DS1302_Veri_Oku(0x83));
	DS1302->Saat = Sayi_Cevir(DS1302_Veri_Oku(0x85));
	DS1302->AyinGunu = Sayi_Cevir(DS1302_Veri_Oku(0x87));
	DS1302->Ay = Sayi_Cevir(DS1302_Veri_Oku(0x89));
	DS1302->HaftaninGunu = Sayi_Cevir(DS1302_Veri_Oku(0x8b));
	DS1302->Sene = Sayi_Cevir(DS1302_Veri_Oku(0x8d));
}
