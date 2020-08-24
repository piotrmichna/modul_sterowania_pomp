/*
 * uart328pb.h
 *
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 


#ifndef UART328PB_H_
#define UART328PB_H_

#define UART_BAUD 115200									// predkosc
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1) // UBRR dla U2X=0

#define UART_RX_BUF_SIZE 16									// rozmiar bufora odbiorczego
#define UART_RX_BUF_MASK ( UART_RX_BUF_SIZE - 1)			// maska bufora

#define UART_TX_BUF_SIZE 16									// rozmiar bufora nadawczego
#define UART_TX_BUF_MASK ( UART_TX_BUF_SIZE - 1)			// maska bufora

void USART_Init( uint16_t baud );

#endif /* UART328PB_H_ */