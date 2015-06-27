//___________________________________________________________________________
    P1DIR 	&= ~BIT3;				// Port1.0 giriş
  	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
  	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliği aktif
//___________________________________________________________________________
unsigned char leds = 0b00000000;
//___________________________________________________________________________
return(0);}
//___________________________________________________________________________
  	while(P1IN & BIT3);						
  	_delay_cycles(16000);					
  	while(!(P1IN & BIT3));					
//___________________________________________________________________________
#define TRUE 1
#define FALSE 0
#define CS BIT0
/** MACRO for selecting or deselecting chip select for the ENC28J60.**/
#define SEL_MAC(x)  (x==TRUE) ? (P2OUT&=(~CS)) : (P2OUT|=CS) 
//___________________________________________________________________________
void port2_kesme_ayarlari (void){
    P2DIR &= ~BIT2;                         // Port2.0 giriş.
    P2REN |=  BIT2;                         // Port2.0 direnci aktif.
    P2OUT |=  BIT2;                         // Port2.0 direnci Pull-Up.
    P2IE  |=  BIT2;                         // Port2.0 kesmesini aç.
    P2IES |=  BIT2;                         // Düşen kenar kesmesini seç.
    P2IFG |=  BIT2;                         // Kesme bayrağını temizle.
}
// Port 2 kesme vektörü
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{

  while(!(P2IN & BIT2)); // Buton bırakılana kadar bekle.
  P2IFG &= ~BIT2;                         // Kesme bayrağını temizle.
  _bic_SR_register_on_exit(CPUOFF);

}
//___________________________________________________________________________

  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator