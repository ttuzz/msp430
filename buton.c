    P1DIR 	&= ~BIT3;				// Port1.0 giriş
  	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
  	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliği aktif



    P1DIR 	&= ~BIT3;
  	P1SEL	&= ~BIT3;
  	P1SEL2	&= ~BIT3;
  	P1REN	|= BIT3;
  	P1OUT	|= BIT3;



  	while(P1IN & BIT3);						
  	_delay_cycles(16000);					
  	while(!(P1IN & BIT3));					



#define LED0 P1OUT_bit.P1OUT_0
#define LED1 P1OUT_bit.P1OUT_1
#define P1REN7 P1REN_bit.P1REN_7
#define P1OUT7 P1OUT_bit.P1OUT_7
#define P1IE7 P1IE_bit.P1IE_7
#define P1IES7 P1IES_bit.P1IES_7
#define P1IFG7 P1IFG_bit.P1IFG_7

P1DIR = 0x7F; //P1.7 Giriş, diğerleri çıkış...
P1OUT7 = 1; //P1.7 de pull-up direnci seçiliyor.
P1REN7 = 1; //P1.7 deki pull-up direnci aktif.
P1IE7 = 1; //P1.7 için kesme aktif ediliyor.
P1IES7 = 0; //P1.7 kesmesi için yükselen kenar
P1IFG7 = 0; //P1.7 kesme bayrağı temizleniyor.

__delay_cycles(1000000);