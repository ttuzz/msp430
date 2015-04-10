#include <msp430.h> 

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
    //______________________________________
	TA0CCR0 = 62500; 					// Timer0 kesme periyodu 5ms
	TA0CTL = TASSEL_2 + MC_2+ ID_3; 	// SMCLK + Continous up + divider/8 (SMCLK/8)
    //______________________________________
    P2DIR |=  BIT2;
    P2OUT =0;
    //______________________________________
	__bis_SR_register(GIE);
	for(;;){
		TA0CCTL0 |= CCIE; 				//Capture/compare interrupt enable
	__bis_SR_register(LPM0_bits);
	TA0CCR0 = 62500;
	}
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
P2OUT ^=  BIT2;
TA0CCTL0 &=~CCIE;
__bic_SR_register_on_exit (LPM0_bits);
}
/*
 * 1000000 Hz / 8 = 125000 Hz =0,000008 second
 * 0,000008 * 62500 =0,5 second
 */