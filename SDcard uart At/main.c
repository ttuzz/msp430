/*zcnzkn	20.05.2015
 *
 * uarttan girilen doya ismini sd kartta dosya mevcutsa
 * içerği uartla gönderen program
 *
 * AT\r\n bağlantı kontrol
 * AT+SD="filename.extent"\r\n
 * AT+SD="folder/folder/filename.extent"\r\n
 *
 *Not : uartta rx \n yazılana kadar bekliyor.
 *
 */
#include <msp430.h>
#include <string.h>
#include <stdint.h>
#include "pff2a/src/diskio.h"
#include "pff2a/src/pff.h"
#include "drivers/spi.h"
#include "main.h"
#include "drivers/uart.h"
#include "ekler/fifo.h"
	FRESULT rc;
	FATFS fatfs;
	WORD  br,bw;

	struct my_fifo uart_fifo;

#define	WRITE_DATA_PACKET_SIZE	128	//Sdcard fifo
BYTE bWriteBuffer[WRITE_DATA_PACKET_SIZE];
char DATA_PACKET_SIZE[3];

void
main (void){
	WDTCTL 	=  WDTPW + WDTHOLD;
	DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;

    P1DIR = 0xFF;                             // All P1.x outputs
    setup_16Mhz_9600Baud();	//uart setup

	P2DIR	|= BIT1 + BIT2;			// Port2.1-2 çıkış
	P2SEL	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanılacak
	P2SEL2	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanılacak
	P2OUT	&= ~(BIT1 + BIT2);		// Port2.1-2 çıkışlarını sıfırla

	spi_initialize();				// USCI_B0 birimini SPI için hazırla

	intTochar3byte(DATA_PACKET_SIZE,WRITE_DATA_PACKET_SIZE); //bir seferde max göndericek paket sayısını ascii'ye çevir

	__bis_SR_register(GIE);
	UARTSend("MCU Ready\r\n");
	while(1){
	//	if(sd_card_mount()==F_SD_OK){ }
		IE2 |= UCA0RXIE;                         	 // Enable USCI_A0 RX interrupt Uart
		__bis_SR_register(LPM0_bits);
		if(RXuart=='\n'){	//\n datası gelene kadar okuma yapıyor gelmesse haat verir
			recievedefiner();
		}
	}
}
//_________________________________________________________________________________________
// USCI A0/B0 Transmit ISR
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void){
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF=TXuart;
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}
// USCI A0/B0 Receive ISR
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
if(IFG2&UCA0RXIFG){	// USCI_A0 RX buffer capture?
RXuart = UCA0RXBUF;
fifo_write(&uart_fifo, RXuart);		//fifo veri alması
IE2 &= ~UCA0RXIE;                       // Disable USCI_A0 RX interrupt
__bic_SR_register_on_exit(CPUOFF);        // Exit Low Power MODE
  }
}
//_________________________________________________________________________________________
SDCHCK sd_card_mount (void){
	trytimes=0;
	while(trytimes<=trytmscont){
		if(pf_mount(&fatfs)==RES_OK){return SD_OK;}
		trytimes++;
	}return SD_ER;
}
//_________________________________________________________________________________________
/*
 * rtp=gelen dosya adı kaç hane ? uzantısı dahil
 * *path gelen dosya adı uzantısı dahil
 */
SDCHCK sd_card_pf_open (void){	//uarttan gönderilen dosyayı açmayı dener
	trytimes=0;
	while(trytimes<=trytmscont){
		if( pf_open(dosyaAdUzanti)==RES_OK){return SD_OK;}
		trytimes++;
	}return SD_ER;
}
//_________________________________________________________________________________________
SDCHCK sd_card_pf_close(void){
	trytimes=0;
	while(trytimes<=trytmscont){
		if(pf_write(0, 0, &bw)==RES_OK){return SD_OK;}
		trytimes++;
	}return SD_ER;
}
//_________________________________________________________________________________________
SDCHCK sd_card_read (void){		//dosyayı baştan sona okumak için pf_lseek komutuna ihtiyaç yok
	trytimes=0;
	paketsayici=0;

while(dosyaninboyutu>=WRITE_DATA_PACKET_SIZE){
	if(sd_card_read_devamı()==SD_OK){
		dosyaninboyutu=dosyaninboyutu-WRITE_DATA_PACKET_SIZE;
		paketsayici++;
		//datayı gonder  //ne kadar veri yollanacagını haber ver
		UARTSend("AT+");
		UARTSend(DATA_PACKET_SIZE);	//ascii olarak uzunluk bilgisini gönder
		UARTSend("=\"");
		UARTSendWithSize(bWriteBuffer,WRITE_DATA_PACKET_SIZE);		//veriyi gönder
		UARTSend("\"\r\n");
	}else{return SD_ER;}	//hata oluştu geri dön
	if(dosyaninboyutu==0){return SD_OK;}//dosya boyutu WRITE_DATA_PACKET_SIZE'nın tam katıysa
}

if(dosyaninboyutu<WRITE_DATA_PACKET_SIZE){
	if(sd_card_read_devamı()==SD_OK){
		paketsayici++;
	//	bWriteBuffer[dosyaninboyutu]='\0'; //fifonun son üst adresini temizle
		intTochar3byte(asciiuzunluk,dosyaninboyutu); //gönderilecek data sayısını ascii koduna dönüştür
		//ne kadar veri yollanacagını haber ver
		UARTSend("AT+");
		UARTSend(asciiuzunluk);	//ascii olarak uzunluk bilgisini gönder
		UARTSend("=\"");
		UARTSendWithSize(bWriteBuffer,dosyaninboyutu);		//veriyi gönder
		UARTSend("\"\r\n");
		return SD_OK;
	}else{return SD_ER;}	//hata oluştu geri dön
}
}
//_________________________________________________________________________________________
SDCHCK sd_card_read_devamı (void){
while(trytimes<=trytmscont){
if(pf_read(bWriteBuffer,WRITE_DATA_PACKET_SIZE,&br)==RES_OK){
	trytimes=0;     //hata sayıcıyı sıfırla
	return SD_OK;
}trytimes++;		//okuyamadı hata kayıtçısını 1 arttır tekrar dene
}if(trytimes>trytmscont){ return SD_ER;}	//hata oluştu geri dön
}
//_________________________________________________________________________________________
/*
void
sd_card_write (void){
	for (bSayac=0; bSayac<=WRITE_DATA_PACKET_SIZE; bSayac++){
	//if( bWriteBuffer[bSayac] >= 'a' && bWriteBuffer[bSayac] <= 'z')	// Karakter küçük harf mi?
		bWriteBuffer[bSayac] -= 0x20;								// Evet ise büyük harf yap.
	}
//	do{rc = pf_lseek(550);DLY_US(1000);}while(rc);
	do{rc =pf_write(bWriteBuffer,WRITE_DATA_PACKET_SIZE,&br);DLY_US(1000);}while(rc);	//geri yaz
	UARTSend(UART0_BASE,"pf_write OK\n\r");
}
*/
//_________________________________________________________________________________________
void intTochar3byte (char *kdr,int descriment){
	int i;
//	descriment--;	//bir byte fazla geliyor
	for(i=2;i>=0;i--){
		kdr[i] = descriment%10 + 0x30;
		descriment /= 10;
	}
}
//_________________________________________________________________________________________
void DLY_US (void){
}
//_________________________________________________________________________________________
CHECK fifo_check(char * nextChar){
	int j=0;
	while(!(fifo_available(&uart_fifo) == 0)){		//distance değeri 0 olana kadar çevrim (max. çevrim)
		swap=fifo_read(&uart_fifo);
	    if(swap == nextChar[j]){			//check edilmek istenilen datanın ilk harfini sıralı fifoda aratır
	    	while(swap == nextChar[j]){		//ilk harf fifoda bulundu diğer harfler istenildiği gibi sıralı mı ?
	    		j++;
				if(nextChar[j] == '\0'){return CH_TRUE;}	//checkdeki tüm karakterler fifoda kontrol edildi mi ?
				swap=fifo_read(&uart_fifo);
	    	}
	    	return CH_FALSE;
	    }

	}
	return CH_FALSE;
}
//_________________________________________________________________________________________
void UARTSend (char *pui8Buffer){
	while(*pui8Buffer!='\0'){
		while(!(IFG2 & UCA0TXIFG));	//gönderme mesgulken bekle
		TXuart=*pui8Buffer;
		*pui8Buffer++;
		IE2 |= UCA0TXIE;                         	 // Enable USCI_A0 TX interrupt Uart
		}
}
void UARTSendWithSize (char *pui8Buffer,int rtp){
	while(rtp--){
		while(!(IFG2 & UCA0TXIFG));	//gönderme mesgulken bekle
		TXuart=*pui8Buffer;
		*pui8Buffer++;
		IE2 |= UCA0TXIE;                         	 // Enable USCI_A0 TX interrupt Uart
		}
}
void UARTSendSingleChar (char single){
		while(!(IFG2 & UCA0TXIFG));	//gönderme mesgulken bekle
		TXuart=single;
		IE2 |= UCA0TXIE;                      	 // Enable USCI_A0 TX interrupt Uart
}
//_________________________________________________________________________________________
void recievedefiner (void){
	int revcont=0;
	char p;
	int kl=0;	//dosya adı hanesi sayıcısı
	get_struct_indis(&uart_fifo);	//gelen son datanın adresini kaydet

	if(fifo_check("AT\r\n")==CH_TRUE){
		UARTSend("Msp430_OK\r\n");revcont=1;
	}

	set_struct_indis(&uart_fifo);	//kaydedilmiş noktaya dön
	if(fifo_check("AT+SD=\"")==CH_TRUE){
//		UARTSend("OK ");
		p=fifo_read(&uart_fifo);kl++;
		while(!(p=='\"')){
			dosyaAdUzanti[kl-1]=p;
			UARTSendSingleChar(p);
			p=fifo_read(&uart_fifo);kl++;
		}
		while(docsize-kl){	//dosyaAdUzanti'nin kalan yerlerini 00 yapar
		dosyaAdUzanti[kl-1]='\0';kl++;		//dosya uzantısından sonraki ilk haneyi \0 yapar
		}
		UARTSend("\r\n");

		SdCardProtokol();
		revcont=1;
	}

	if(revcont==0){	//karşılaştırmada sonuç alamadıysa
	UARTSend("ERROR\r\n");
	}
	 fifo_init(&uart_fifo);	//fifo adresilerini sıfırla
}
//_________________________________________________________________________________________
void SdCardProtokol (void){
//	spi_initialize();				// USCI_B0 birimini SPI için hazırla
	if(sd_card_mount()==SD_OK){UARTSend("SDcard_mount_OK\r\n");	//sd kart acıldı
	if(sd_card_pf_open()){UARTSend("SDcard_pf_open_OK\r\n\r\n");	//istenilen dosya açıldı
	if(sd_card_read()){UARTSend("\r\nSDcard_pf_read_OK\r\n");		//dosya okuma tamamladı
	if(sd_card_pf_close()){UARTSend("SDcard_pf_close_OK\r\n");	//dosyayı kapatma tamamladı
		UARTSend("all_complate\r\n");
	}else{UARTSend("eror_4\r\n");}
	}else{UARTSend("eror_3\r\n");}
	}else{UARTSend("eror_2\r\n");}
	}else{UARTSend("eror_1\r\n");}

}







