//zcnzkn 4.6.2015

//derleme çalıştırıldıktan sonra terminate (durdurulmadan) nmi aktif olmuyor
//NMI düşen kenar tetiklemeli

//kesme gerçekleştikten sonra otomatik olarak kendini disable yapıyor .tekrar kullanılması için set edilmesi lazım
#include <msp430.h>				

int main(void) {
IE1=NMIIE;                    //enable nmi
WDTCTL=WDTPW+WDTHOLD+WDTNMI;  //select nmi function on RST/NMI

BCSCTL1 = CALBC1_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.
DCOCTL = CALDCO_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.

P1DIR 	= 0xF7;					// 11110111  p1.3 button
P1SEL	&= ~BIT3;
P1SEL2	&= ~BIT3;				
P1REN	|= BIT3;				
P1OUT	|= BIT3;				


for(;;){
	while((P1IN & BIT3));
	_delay_cycles(160000);
	while(!(P1IN & BIT3));
	 P1OUT^= BIT0;
  }
}
//eğer p1.3 butonuna basılıysa bırakıldığında WDT reset'le reset at,değilse NMI'ı tekrar set et ve geri dön
#pragma vector=NMI_VECTOR
__interrupt void nmi(void)
{
if(!(P1IN & BIT3)){
_delay_cycles(160000);
while(!(P1IN & BIT3));
 P1OUT^= BIT6;
WDTCTL = WDT_MRST_0_064;
}
IFG1&=~NMIIFG;
IE1=NMIIE;
}
