#include "uart.h"
/*diðer portlar tanýmlanmadan port1 resetlenmeli
P1DIR = 0xFF;                             // All P1.x outputs
P1OUT = 0;                                // All P1.x reset
*/
void HardwareUart(void){
	P1SEL = BIT1 + BIT2;
	P1SEL2 = BIT1 + BIT2;
}
void 1Mhz_9600Baud(void){
	HardwareUart();
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;
	UCA0CTL1 &= ~UCSWRST;			  		  // **Initialize USCI state machine**
}
void 1Mhz_11500Baud(void){
	HardwareUart();
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 8;                              // 1MHz 115200
	UCA0BR1 = 0;                              // 1MHz 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}