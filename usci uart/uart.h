#ifndef UART_H_
#define UART_H_

#include <stdint.h>

char TXuart;
char RXuart;

void disable_uart(void);
void init_uart (uint32_t SMCLK_F,uint16_t BAUDRATE);

void UART_Echo (void);
void UART_W_Char(unsigned  char chr);
void UART_W_String (char *pui8Buffer);
void UART_W_String_With_Size (char *pui8Buffer,int rtp);
void UART_W_Long(unsigned long n);

#endif /* UART_H_ */
