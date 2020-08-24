/*
 * uart328pb.c
 *
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "uart328pb.h"

volatile char UART_RxBuf[UART_RX_BUF_SIZE];		// definicja bufora odbiorczego
volatile uint8_t UART_RxHead;					// indeks poczatkowy
volatile uint8_t UART_RxTail;					// indeks koncowy

volatile char UART_TxBuf[UART_TX_BUF_SIZE];		// definicja bufora nadawczego
volatile uint8_t UART_TxHead;					// indeks poczatkowy
volatile uint8_t UART_TxTail;					// indeks koncowy

void USART_Init( uint16_t baud ) {	
	UBRR0H = (uint8_t)(baud>>8);
	UBRR0L = (uint8_t)baud;						// ustawienie predkosci komunikacji	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);				// uruchomienie lini komunikacji
	UCSR0B |= (1<<RXCIE0);						// zezwolenie na przerwanie od odbiornika
	UCSR0C = (3<<UCSZ00);						// ramka 8bit 1bit stop
}