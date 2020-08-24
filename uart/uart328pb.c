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