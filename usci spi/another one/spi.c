#include <msp430.h>
#include <stdint.h>
#include "spi.h"

void SPI_init(void){


     UCB0CTL1 |= UCSWRST;
     UCB0CTL0 = UCSYNC + UCMSB + UCCKPH + UCMST + UCMODE_0;
     // szinkron.m�d, MSB els�, Master m�d, �rajel f�zis
     UCB0CTL1 |= UCSSEL_2;     // SMCLK haszn�lata
     UCB0BR0 = 0x1;            // �rajel 1:1
     UCB0BR1 = 0;
     // Ki/Bemenetek
     P1SEL |= (SCLK + SDI + SDO);
     P1SEL2 |= (SCLK + SDI + SDO);
     P1DIR |= (SCLK + SDO);
     P2DIR |= CS;
     P2OUT |= CS;
     P1DIR &= ~SDI;

     UCB0CTL1 &= ~UCSWRST;    // SPI enged�lyez�se

} // SPI_init
uint8_t SPI_transfer(uint8_t data){


     while(!(IFG2 & UCB0TXIFG));
     UCB0TXBUF = data;
     while(!(IFG2 & UCB0RXIFG));
     return UCB0RXBUF;

} //SPI_IO
