#include <msp430.h> 

unsigned char TXi2c,TXuart,RXi2c,RXuart;
void initUART (void);

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                	 // Stop WDT
	if (CALBC1_1MHZ==0xFF)						 // If calibration constant erased
	{
		while(1);                                // do not load, trap CPU!!
	}
	DCOCTL = 0;                              	 // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                   	 // Set DCO
	DCOCTL = CALDCO_1MHZ;
//_________________________________
	P1DIR = 0xFF;                             // All P1.x outputs
	P1OUT = 0;                                // All P1.x reset
//_________________________________
	initUART();
	 __bis_SR_register(GIE);
	
	for(;;){
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt Uart
	__bis_SR_register(LPM0_bits);
	TXuart=RXuart;
	IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt Uart
	}
}
void initUART (void){  //9600 baud
	P1SEL = BIT1 + BIT2;
	P1SEL2 = BIT1 + BIT2;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;
	UCA0CTL1 &= ~UCSWRST;					  // **Initialize USCI state machine**
}
//_____________________________________________________________________________________
// USCI A0/B0 Transmit ISR
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
	if(IFG2&UCA0TXIE)						
	{
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF=TXuart;
	}
	IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}
// USCI A0/B0 Receive ISR
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	if(IFG2&UCA0RXIFG)						// USCI_A0 RX buffer capture?
	{
	RXuart = UCA0RXBUF;
	}
	IE2 &=~UCA0RXIE;
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
//_____________________________________________________________________________________
