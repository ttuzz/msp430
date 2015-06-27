#ifndef SPI_H
#define SPI_H

#define TRUE 1
#define FALSE 0

#define SCLK    BIT5   // P1.5
#define SDI     BIT7   // P1.7
#define SDO     BIT6   // P1.6
#define CS      BIT0   // P2.0

#define CSACTIVE(x)  (x==TRUE) ? (P2OUT&=(~CS)) : (P2OUT|=CS)
#define CS_ENABLE       P2OUT &= ~CS
#define CS_DISABLE      P2OUT |= CS


void SPI_init(void);                  // SPI init
uint8_t SPI_transfer(uint8_t data);   // SPI K�ld�s/fogad�s

#endif
