/*
 * avr_pompy.c
 *
 * Created: 22.08.2020 13:24:02
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "macr.h"
//#include "mod/mod_tpk.h"
#include "uart/uart328pb.h"

// SYSTEMOWE
#define DET_INT_OFF 1	//detekcja przejscia przez zero napiêcia sieciowego
#define PWR_OFF 0		//sterowanie zasilaczem dla peryferi
//#define LED_OFF 0		//dioda led pomocnicza
#define TXEN_OFF 1		//sterowanie kierunkiem komunikacji RS485
#define TX_OFF 0		//sterowanie lini¹ TX
#define RX_OFF 0		//sterowanie linia RX

#define DET_INT_PIN PD3
#define PWR_PIN PC4
//#define LED_PIN PC5
#define TXEN_PIN PD2
#define TX_PIN PD1
#define RX_PIN PD0

#define DET_INT_PORT D
#define PWR_PORT C
//#define LED_PORT C
#define TXEN_PORT D
#define TX_PORT D
#define RX_PORT D


void main_init(void);

int main(void)
{
    main_init();
	//mod_init();
	
	USART_Init( __UBRR);

	sei();
	
	uart_clear();
	uart_puts("START");

    while (1) 
    {
		
		_delay_ms(500);
    }
}

void main_init(void){
	// INICJACJA SYSTEMOWE
	#ifdef DET_INT_OFF
		if(DET_INT_OFF==1) PORT( DET_INT_PORT ) |= (1<<DET_INT_PIN); else PORT( DET_INT_PORT ) |= (1<<DET_INT_PIN);
		DDR( DET_INT_PORT ) &= ~(1<<DET_INT_PIN);
	#endif
	#ifdef PWR_OFF
		if(PWR_OFF==1) PORT( PWR_PORT ) |= (1<<PWR_PIN); else PORT( PWR_PORT ) &= ~(1<<PWR_PIN);
		DDR( PWR_PORT ) |= (1<<PWR_PIN);
	#endif
	#ifdef LED_OFF
		if(LED_OFF==1) PORT( LED_PORT ) |= (1<<LED_PIN); else PORT( LED_PORT ) &= ~(1<<LED_PIN);
		DDR( LED_PORT ) |= (1<<LED_PIN);
	#endif
	#ifdef TXEN_OFF
		if(TXEN_OFF==1) PORT( TXEN_PORT ) |= (1<<TXEN_PIN); else PORT( TXEN_PORT ) &= ~(1<<TXEN_PIN);
		DDR( TXEN_PORT ) |= (1<<TXEN_PIN);
	#endif
	#ifdef TX_OFF
		if(TX_OFF==1) PORT( TX_PORT ) |= (1<<TX_PIN); else PORT( TX_PORT ) &= ~(1<<TX_PIN);
		DDR( TX_PORT ) |= (1<<TX_PIN);
	#endif
	#ifdef RX_OFF
		if(RX_OFF==1) PORT( RX_PORT ) |= (1<<RX_PIN); else PORT( RX_PORT ) &= ~(1<<RX_PIN);
		DDR( RX_PORT ) &= ~(1<<RX_PIN);
	#endif
}