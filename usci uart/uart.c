/*
 * source=https://gist.github.com/ThuanBK55/640aabf9dbb56e3c5f5c
 * 9600 baud ayarlarýnda hepsi sorunsuz
 * 14400 hepsinde sorunlu
 *
 *düzenleme 20.6.2015
 *intterruplar taþýndý intterrup üzerinde düzenleme yapýldý
 *bazý küçük düzenlemeler yapýldý
 */
#include "uart.h"
#include <stdint.h>
#include <msp430g2553.h>


void disable_uart (void){
	UCA0CTL1 |= UCSWRST; // put state machine in reset
}

void initialize_uart (uint32_t SMCLK_F,uint16_t BAUDRATE){
	uint16_t tempfactor;
P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
P1SEL2 |= BIT1 + BIT2;

UCA0CTL0 =0 ;		//Parity none,LSB first,8-bit data,one stop bits
UCA0CTL1 |= UCSSEL_2; // SMCLK

tempfactor = SMCLK_F/BAUDRATE;
UCA0BR0 = (unsigned char) tempfactor&0x00FF;
UCA0BR1 = (unsigned char) ((tempfactor >> 8) &0x00FF);
UCA0MCTL |=UCBRS_5;	// Modulation UCBRSx = 5
UCA0CTL1 &=~ UCSWRST; // **Initialize USCI state machine**

}
void UART_Write_Char(unsigned  char chr){
	while(!(IFG2 & UCA0TXIFG));		//gönderme mesgulken bekle
	TXuart= chr;
	IE2 |= UCA0TXIE;                         		 // Enable USCI_A0 TX interrupt Uart
}
void UART_Write_String (char *pui8Buffer){
	while(*pui8Buffer!='\0'){
		while(!(IFG2 & UCA0TXIFG));	//gönderme mesgulken bekle
		TXuart=*pui8Buffer;
		*pui8Buffer++;
		IE2 |= UCA0TXIE;                         	 // Enable USCI_A0 TX interrupt Uart
		}
}

void UART_Write_String_With_Size (char *pui8Buffer,int rtp){
	while(rtp--){
		while(!(IFG2 & UCA0TXIFG));	//gönderme mesgulken bekle
		TXuart=*pui8Buffer;
		*pui8Buffer++;
		IE2 |= UCA0TXIE;                         	 // Enable USCI_A0 TX interrupt Uart
		}
}

void UART_Write_Int_To_Ascii(unsigned long n)	//unsigned long max. 4.294.967.295  10char size
{	unsigned char bufferint[11];
	bufferint[10]='\0';
	if(n==0){UART_Write_Char('0');return;}
	char i=0;
	while(n>0 & i<=9){	bufferint[i]=n%10+'0';n/=10;i++;	}
	while(i--){UART_Write_Char(bufferint[i]);}
}
//_________________________________________________________________________________________
// USCI A0/B0 Transmit ISR
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void){
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF=TXuart;
	while(!(IFG2 & UCA0TXIFG));
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}
// USCI A0/B0 Receive ISR
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
if(IFG2&UCA0RXIFG){	// USCI_A0 RX buffer capture?
RXuart = UCA0RXBUF;
IE2 &= ~UCA0RXIE;                       // Disable USCI_A0 RX interrupt
__bic_SR_register_on_exit(CPUOFF);        // Exit Low Power MODE
  }
}
//_________________________________________________________________________________________
