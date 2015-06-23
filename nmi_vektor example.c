//derleme çalıştırıldıktan sonra terminate (durdurulmadan) nmi aktif olmuyor

//kesme gerçekleştikten sonra otomatik olarak kendini disable yapıyor .tekrar kullanılması şçin set edilmesi lazım
#include <msp430.h>

int main(void) {
//WDTCTL=WDTPW+WDTHOLD+WDTNMI;         // WDT off NMI lo/hi   buton bırakıldığında
WDTCTL=WDTPW+WDTHOLD+WDTNMI+WDTNMIES;  // WDT off NMI hi/lo	  butona basıldığında
IE1 |= NMIIE;                          // Enable NMI

  P1DIR=BIT0+BIT6;
  P1OUT^=BIT0;
 //__bis_SR_register(GIE) ;
  for(;;){};
}

#pragma vector=NMI_VECTOR
__interrupt void nmi(void)
{
P1OUT^= (BIT6);
//WDTCTL = WDT_MRST_0_064;		//Watchdog reset 0.064ms
IFG1&=~NMIIFG;                      //clear nmi interrupt flag
IE1=NMIIE;                          // enable nmi
//WDTCTL = WDTPW + WDTHOLD+WDTNMI;    // select nmi function on RST/NMI
}
