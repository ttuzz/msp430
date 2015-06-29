#include <msp430.h>
#include "my_main.h"


void wdtimer_nmi(void){
WDTCTL = WDTPW+WDTHOLD+WDTNMI+WDTNMIES ;
IE1 |= NMIIE;
}

void Smclk_ (char Mhz){
	DCOCTL = 0;
	switch(Mhz){
	case 1:
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
		SMCLK_=1000000;
	case 8:
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;
		SMCLK_=8000000;
	case 12:
		BCSCTL1 = CALBC1_12MHZ;
		DCOCTL = CALDCO_12MHZ;
		SMCLK_=12000000;
	case 16:
		BCSCTL1 = CALBC1_16MHZ;
		DCOCTL = CALDCO_16MHZ;
		SMCLK_=16000000;
	}
	sm_factor=SMCLK_/1000000;
}
void delay_s (unsigned int s)  {s =s *sm_factor;	while (s--) {		__delay_cycles(1000000);	}}
void delay_ms(unsigned int ms) {ms=ms*sm_factor;	while (ms--) {		__delay_cycles(1000);	}}
void delay_us(unsigned int us) {us=us*sm_factor;	while (us--) {		__delay_cycles(1);	}}

void gpio_H_L(unsigned char port1_2, unsigned char  BITx, unsigned char High1_Low1 ){
	if(port1_2==1){
		if 	    (High1_Low1==1){P1OUT |=  BITx;}
		else if (High1_Low1==0){P1OUT &= ~BITx;}
	}
	else if(port1_2==2){
		if 	    (High1_Low1==1){P2OUT |= BITx;}
		else if (High1_Low1==0){P2OUT &= ~BITx;}
	}
}

#pragma vector=NMI_VECTOR
__interrupt void nmi(void)
{
WDTCTL = WDT_MRST_0_064;		    //Watchdog reset 0.064ms
IFG1&=~NMIIFG;                      //clear nmi interrupt flag
IE1=NMIIE;                          // enable nmi
}
