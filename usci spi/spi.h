/*
 * P2.0 - CS (active low)
 *
 * UCB			 UCA
 * P1.5 - SCLK - P1.4
 * P1.6 - MISO - P1.1
 * P1.7 - MOSI - P1.2
 *
 */
#ifndef SPI_H_
#define SPI_H_

#define SPI_DEF_SPEED 4000000
#define SPI_250kHz 250000

#define SPI_MODE_0 UCCKPH | UCMSB| UCMST | UCSYNC 			    /* CPOL=0 CPHA=0 */
#define SPI_MODE_1 UCMSB  | UCMST | UCSYNC					    /* CPOL=0 CPHA=1 */
#define SPI_MODE_2 UCCKPL | UCCKPH | UCMSB| UCMST | UCSYNC 		/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 UCCKPL | UCMSB| UCMST | UCSYNC 			    /* CPOL=1 CPHA=1 */
/*
 * UCSYNC-> uscı_spi_mod
 * UCMST-> spi_master
 * UCMSB->  MSB first
 *
 * UCCKPH->	Clock Phase 0
 * UCCKPL-> Clock Polarity 1
 */

#define Spi_pin BIT5 | BIT6 | BIT7 		//UCB spi
//#define Spi_pin BIT1 | BIT2 | BIT4	//UCA spi
#define Cs_pin  BIT0	//p2.0

unsigned long mcu_speed;
unsigned int Spi_divider;

void spi_initialize(uint32_t SMCLK_F,uint32_t BAUDRATE);
uint8_t spi_send(const uint8_t);
uint8_t spi_receive(void);
void spi_set_divisor( uint32_t clkdiv);

#endif /*SPI_H_*/
