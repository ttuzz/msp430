#include "uart.h"
#include <msp430.h>

void HardwareUart(void){
	P1SEL = BIT1 + BIT2;
	P1SEL2 = BIT1 + BIT2;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	P1OUT = 0;                                // All P1.x reset
}
void setup_1Mhz_9600Baud(void){
	HardwareUart();
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;
	UCA0CTL1 &= ~UCSWRST;					  // **Initialize USCI state machine**
}
void setup_1Mhz_11500Baud(void){
	HardwareUart();
	UCA0BR0 = 8;                              // 1MHz 115200
	UCA0BR1 = 0;                              // 1MHz 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
void setup_16Mhz_9600Baud(void){
	HardwareUart();
	UCA0BR0 = 130;                            // 16MHz 9600
	UCA0BR1 = 6;                              // 16MHz 9600
	UCA0MCTL = UCBRS2 + UCBRS1;               // modulation is 110b or 6
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
void setup_16Mhz_115200Baud(void){
	HardwareUart();
	UCA0BR0 = 139 ;
	UCA0BR1 = 0 ;
	UCA0MCTL = UCBRS1 + UCBRS2;
	UCA0CTL1 &= ~UCSWRST ;
}
