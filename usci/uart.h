#ifndef UART_H_
#define UART_H_

#include <stdint.h>

char TXuart;
char RXuart;

void uartoff(void);
void setup_uart (uint32_t SMCLK_F,uint16_t BAUDRATE);

void UART_Write_Char(unsigned  char chr);
void UART_Write_String (char *pui8Buffer);
void UART_Write_String_With_Size (char *pui8Buffer,int rtp);
void UART_Write_Int_To_Ascii(unsigned long n);

#endif /* UART_H_ */
