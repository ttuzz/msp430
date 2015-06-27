void IO_Write(unsigned char port1_2, unsigned char bit, unsigned char High1_Low1 ){
	if(port1_2==1){
		if 	    (High1_Low1==1){P1OUT |=  bit;} 
		else if (High1_Low1==0){P1OUT &= ~bit;}
	}
	else if(port1_2==2){
		if 	    (High1_Low1==1){P2OUT |= bit;} 
		else if (High1_Low1==0){P2OUT &= ~bit;}
	}
}