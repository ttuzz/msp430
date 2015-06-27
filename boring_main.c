#include <msp430.h>
#include "boring_main.h"

void wdtimer_nmi(void){
WDTCTL = WDTPW+WDTHOLD+WDTNMI+WDTNMIES ;
}


void Smclk_ (char Mhz){
	//DCOCTL = 0;
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
}

#pragma vector=NMI_VECTOR
__interrupt void nmi(void)
{
WDTCTL = WDT_MRST_0_064;		    //Watchdog reset 0.064ms
IFG1&=~NMIIFG;                      //clear nmi interrupt flag
IE1=NMIIE;                          // enable nmi
}
