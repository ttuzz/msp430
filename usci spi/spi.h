#ifndef SPI_H_
#define SPI_H_

#define Spi_USA_pin BIT1 | BIT2 | BIT4
#define Spi_USB_pin BIT5 | BIT6 | BIT7

#define SPI_MODE_0 UCCKPH | UCMSB| UCMST | UCSYNC 			    /* CPOL=0 CPHA=0 */
#define SPI_MODE_00 UCCKPH | UCMSB| UCMST | UCSYNC | UCMODE_0   /* CPOL=0 CPHA=0 */
#define SPI_MODE_1 UCMSB  | UCMST | UCSYNC					    /* CPOL=0 CPHA=1 */
#define SPI_MODE_2 UCCKPL | UCCKPH | UCMSB| UCMST | UCSYNC 		/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 UCCKPL | UCMSB| UCMST | UCSYNC 			    /* CPOL=1 CPHA=1 */
/*
 * UCSYNC-> usci_spi_mod
 * UCMST-> spi_master
 * UCMSB->  MSB first
 *
 * UCCKPH->	Clock Phase 0
 * UCCKPL-> Clock Polarity 1
 */
 unsigned long mcu_speed;
 unsigned int Spi_divider;

 void init_spi(uint32_t SMCLK_F,uint32_t BAUDRATE);
 void spi_Speed_Change( uint32_t clkdiv);
 void Cs_pin_Select (unsigned char port,unsigned char pin_BITx);
 void Cs_Disable (uint8_t Cs_pin_BITx);
 void Cs_Enable (uint8_t Cs_pin_BITx);

 uint8_t spi_send(const uint8_t c);
 uint8_t spi_receive(void);


#endif /*SPI_H_*/