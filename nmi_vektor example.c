//derleme çalıştırıldıktan sonra terminate (durdurulmadan) nmi aktif olmuyor
//NMI düşen kenar tetiklemeli

//kesme gerçekleştikten sonra otomatik olarak kendini disable yapıyor .tekrar kullanılması şçin set edilmesi lazım
#include <msp430.h>				

int main(void) {
IE1=NMIIE;                    //enable nmi
WDTCTL=WDTPW+WDTHOLD+WDTNMI;  //select nmi function on RST/NMI

  P1DIR=BIT0+BIT6;
  P1OUT=BIT0;
 //__bis_SR_register(GIE) ;
  for(;;){};
}

#pragma vector=NMI_VECTOR
__interrupt void nmi(void)
{
P1OUT^= (BIT0+BIT6);

IFG1&=~NMIIFG;                      //clear nmi interrupt flag
IE1=NMIIE;                          // enable nmi
//WDTCTL = WDTPW + WDTHOLD+WDTNMI;    // select nmi function on RST/NMI
}
