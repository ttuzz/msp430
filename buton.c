    P1DIR 	&= ~BIT3;				// Port1.0 giriş
  	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
  	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
  	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliği aktif


  	while(P1IN & BIT3);						
  	_delay_cycles(16000);					
  	while(!(P1IN & BIT3));					
