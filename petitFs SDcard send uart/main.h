/*
 * main.h
 *
 *  Created on: 20 May 2015
 *      Author: trntla
 */

#ifndef MAIN_H_
#define MAIN_H_

char TXuart;
char RXuart;

//gelen datayı kontrol etmek için
typedef enum {
	CH_TRUE = 1,			/* 1 */
	CH_FALSE				/* 0 */
} CHECK;

typedef enum {
	SD_OK = 1,			/* 1 */
	SD_ER				/* 0 */
} SDCHCK;


void SdCardProtokol (void);
SDCHCK sd_card_mount (void);
SDCHCK sd_card_pf_open (void);
SDCHCK sd_card_read (void);
SDCHCK sd_card_read_devamı (void);
SDCHCK sd_card_pf_close(void);
void intTochar3byte (char *kdr,int descriment);
void DLY_US (void);
CHECK fifo_check(char * nextChar);

void UARTSend (char *pui8Buffer);
void UARTSendWithSize (char *pui8Buffer,int rtp);
void UARTSendSingleChar (char single);

void recievedefiner (void);

int trytimes=0;		//hata durumunu say
int trytmscont=20;  //hata oluşursa kaç kere tekrar etsin ?

#define F_SD_ER 0		//sd card üzerinde yapılan işlem başarısız
#define F_SD_OK 1		//sd card üzerinde yapılan işlem başarılı

#define docsize 48
char dosyaAdUzanti[docsize];
char asciiuzunluk[3];
char swap;
int paketsayici=1; 	//okunmaya başlanan dosyanın kaçıncı sektöründe

#endif /* MAIN_H_ */
