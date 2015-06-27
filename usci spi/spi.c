/*
 * Serial Pripheral Interface
 *
 * Zcn Zkn 20 06 2015
 * energia kutuphanesinden duzenlenmistir
 */
#include <msp430.h>
#include <stdint.h>
#include "spi.h"

#ifndef __MSP430_HAS_USCI__
#error "Error! This MCU doesn't have a USCI peripheral"
#endif


void init_spi(uint32_t SMCLK_F,uint32_t BAUDRATE)
{
	Spi_divider=SMCLK_F/BAUDRATE; //must be integer value
	mcu_speed=SMCLK_F;
	UCB0CTL1 = UCSSEL_2 | UCSWRST;	// source USCI clock from SMCLK, put USCI in reset mode
	UCB0CTL0 |= SPI_MODE_00;			// SPI MODE 0 - CPOL=0 CPHA=0
									// note: UCCKPH is inverted from CPHA
//	UCA0MCTL= 0;   // No modulation just USCA0
	P1SEL  |= Spi_pin;
	P1SEL2 |= Spi_pin;

	UCB0BR0 = (unsigned char) Spi_divider&0x00FF;	// set initial speed
	UCB0BR1 = (unsigned char) ((Spi_divider >> 8) &0x00FF);

	P2OUT |= Cs_pin;					// CS on P2.0. start out disabled
	P2DIR |= Cs_pin;					// CS configured as output

	UCB0CTL1 &= ~UCSWRST;			// release for operation
}

 // spi_send() - send a byte and recv response
uint8_t spi_send(const uint8_t c)
{
	while (!(UC0IFG & UCB0TXIFG)); // wait for previous tx to complete
	UCB0TXBUF = c; // setting TXBUF clears the TXIFG flag
	while (!(UC0IFG & UCB0RXIFG)); // wait for an rx character?
	return UCB0RXBUF; // reading clears RXIFG flag
}

// spi_receive() - send dummy btye then recv response
uint8_t spi_receive(void) {
	while (!(UC0IFG & UCB0TXIFG)); // wait for any previous xmits to complete
	UCB0TXBUF = 0xFF; // Send dummy packet to get data back.
	while (!(UC0IFG & UCB0RXIFG)); // wait to recv a character?
	return UCB0RXBUF; // reading clears RXIFG flag
}

void spi_set_divisor( uint32_t clkdiv)
{
	Spi_divider=mcu_speed/clkdiv; //must be integer value
	UCB0CTL1 |= UCSWRST;		// go into reset state
	UCB0BR0 = (unsigned char) Spi_divider&0x00FF;	// set initial speed
	UCB0BR1 = (unsigned char) ((Spi_divider >> 8) &0x00FF);
	UCB0CTL1 &= ~UCSWRST;		// release for operation
}
