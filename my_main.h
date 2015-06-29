
#ifndef MY_MAIN_H_
#define MY_MAIN_H_

unsigned long SMCLK_;
char  sm_factor;


void Smclk_ (char Mhz);
void wdtimer_nmi (void);

void gpio_H_L(unsigned char port1_2, unsigned char  BITx, unsigned char High1_Low1 );
void delay_s (unsigned int s);
void delay_ms (unsigned int ms);
void delay_us (unsigned int us);

#endif /* MY_MAIN_H_ */
