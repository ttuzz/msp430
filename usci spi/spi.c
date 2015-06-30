#include <msp430.h>
#include <stdint.h>
#include "spi.h"


void init_spi(uint32_t SMCLK_F,uint32_t BAUDRATE,uint8_t UCAorUCB)
{
	if(UCAorUCB=='A'){
	P1SEL  |= Spi_USA_pin;
	P1SEL2 |= Spi_USA_pin;
	UCA0MCTL= 0;   // No modulation just USCA0
	port_register=1;
	}
	if(UCAorUCB=='B'){
	P1SEL  |= Spi_USB_pin;
	P1SEL2 |= Spi_USB_pin;
	port_register=2;
	}

	Spi_divider=SMCLK_F/BAUDRATE; //must be integer value
	mcu_speed=SMCLK_F;			  //for chance spi speed
	UCB0CTL1 = UCSSEL_2 | UCSWRST;	// source USCI clock from SMCLK, put USCI in reset mode
	UCB0CTL0 |= SPI_MODE_00;			// SPI MODE 0 - CPOL=0 CPHA=0
									// note: UCCKPH is inverted from CPHA

	UCB0BR0 = (unsigned char) Spi_divider&0x00FF;	// set initial speed
	UCB0BR1 = (unsigned char) ((Spi_divider >> 8) &0x00FF);

	UCB0CTL1 &= ~UCSWRST;			// release for operation
}

void spi_Speed_Change( uint32_t clkdiv)
{
	Spi_divider=mcu_speed/clkdiv; //must be integer value
	UCB0CTL1 |= UCSWRST;		// go into reset state
	UCB0BR0 = (unsigned char) Spi_divider&0x00FF;	// set initial speed
	UCB0BR1 = (unsigned char) ((Spi_divider >> 8) &0x00FF);
	UCB0CTL1 &= ~UCSWRST;		// release for operation
}

void Cs_pin_Select (unsigned char port,unsigned char pin_BITx){
	if(port==1){P1DIR |= pin_BITx;	}
	if(port==2){P2DIR |= pin_BITx;	}
}

void Cs_Disable (uint8_t Cs_pin_BITx){
	if(port_register==1){ P1OUT &=~ Cs_pin_BITx ;	}
	if(port_register==2){ P2OUT &=~ Cs_pin_BITx ;	}
}

void Cs_Enable (uint8_t Cs_pin_BITx){
	if(port_register==1){ P1OUT |= Cs_pin_BITx ;	}
	if(port_register==2){ P2OUT |= Cs_pin_BITx ;	}
}

uint8_t spi_send(const uint8_t c)
{
	while (!(UC0IFG & UCB0TXIFG)); // wait for previous tx to complete
	UCB0TXBUF = c; // setting TXBUF clears the TXIFG flag
	while (!(UC0IFG & UCB0RXIFG)); // wait for an rx character?
	return UCB0RXBUF; // reading clears RXIFG flag
}

// spi_receive() - send dummy btye then recv response
uint8_t spi_receive(void) 
{
	while (!(UC0IFG & UCB0TXIFG)); // wait for any previous xmits to complete
	UCB0TXBUF = 0xFF; // Send dummy packet to get data back.
	while (!(UC0IFG & UCB0RXIFG)); // wait to recv a character?
	return UCB0RXBUF; // reading clears RXIFG flag
}