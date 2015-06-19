/*
Zcn Zkn
20.05.2015
ozcan_oz_10@hotmail.com
*/
#include <msp430.h>
#include <stdint.h>
#include "drivers/uart.h"

#define baud_rate 9600
uint32_t mcu_fr;
char pk=0;

void goster (uint32_t SMCLK_F2,uint16_t BAUDRATE2);

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {											
    while(1);                               // do not load, trap CPU!!	
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_12MHZ;                    // Set DCO
  DCOCTL = CALDCO_12MHZ;

    P1DIR 	&= ~BIT3;				// Port1.0 giriş
  	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
  	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliği aktif

//  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
  __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled

  setup_uart(12000000,baud_rate);
  UART_Write_String("\r\nBaudRate= ");
  UART_Write_Int_To_Ascii(baud_rate);
  UART_Write_String("\r\n");
  UART_Write_String("___________________________");
  while(1) {								// Sonsuz döngü
  	while(P1IN & BIT3);						// Butona(P1.3) basılmasını bekle
  	_delay_cycles(16000);					// Buton arkını önlemek için bir süre bekle
  	while(!(P1IN & BIT3));					// Butonun(P1.3) bırakılmasını bekle

  	pk++;
	switch (pk){
	case 0: break;
	case 1:
		  DCOCTL = 0;
		  BCSCTL1 = CALBC1_1MHZ;
		  DCOCTL = CALDCO_1MHZ;
		  mcu_fr=1000000;
		  break;
	case 2:
		  DCOCTL = 0;
		  BCSCTL1 = CALBC1_8MHZ;
		  DCOCTL = CALDCO_8MHZ;
		  mcu_fr=8000000;
		  break;
	case 3:
		  DCOCTL = 0;
		  BCSCTL1 = CALBC1_12MHZ;
		  DCOCTL = CALDCO_12MHZ;
		  mcu_fr=12000000;
		  break;
	case 4:
		  DCOCTL = 0;
		  BCSCTL1 = CALBC1_16MHZ;
		  DCOCTL = CALDCO_16MHZ;
		  mcu_fr=16000000;
		  break;
	default :
		pk=0;break;

	}
	uartoff();
	setup_uart(mcu_fr,baud_rate);
	goster(mcu_fr,baud_rate);
  }
}

//_________________________________________________________________________________________
// USCI A0/B0 Transmit ISR
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void){
	while(!(IFG2 & UCA0TXIFG));
	_delay_cycles(160000);
	UCA0TXBUF=TXuart;
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

void goster (uint32_t SMCLK_F2,uint16_t BAUDRATE2){
	uint16_t tempfactor2;
UART_Write_String("\r\nMaster_Clock= ");
tempfactor2=mcu_fr/1000;
UART_Write_Int_To_Ascii(tempfactor2);UART_Write_String_With_Size("kHZ\r\n",5);
UART_Write_String("\r\nUCA0BR0= ");
tempfactor2 = SMCLK_F2/BAUDRATE2;
UART_Write_Int_To_Ascii(tempfactor2);
UART_Write_String("\r\nUCA0BR1= ");
tempfactor2 >>= 8;
UART_Write_Int_To_Ascii(tempfactor2);UART_Write_String_With_Size("\r\n",2);
}
//_________________________________________________________________________________________
