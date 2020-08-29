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
#include <util/atomic.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "macr.h"
#include "mod/mod.h"
#include "uart/uart328pb.h"

// SYSTEMOWE

//#define LED_OFF 0		//dioda led pomocnicza
#define TXEN_OFF 1		//sterowanie kierunkiem komunikacji RS485
#define TX_OFF 0		//sterowanie lini¹ TX
#define RX_OFF 0		//sterowanie linia RX

//#define LED_PIN PC5
#define TXEN_PIN PD2
#define TX_PIN PD1
#define RX_PIN PD0

//#define LED_PORT C
#define TXEN_PORT D
#define TX_PORT D
#define RX_PORT D

char testAr[]={"|/-\\|/-\\"};

void main_init(void);

int main(void){
    main_init();
	
	USART_Init( __UBRR);

	sei();
	
	uart_clear();
	uart_puts("START\n\r");	
	
	//timer 1
	TCCR1B |= (1<<WGM12);				// tryb CTC
	TCCR1B |= (1<<CS10) | (1<<CS12);	// prescaler 1024
	OCR1A= 1800;						//przerwanie co 100ms
	
	uint8_t cnt=10,n=0,stan=0;
	int8_t err=0;
	int16_t pomiar=0;
	char c;

    while (1){	
		if(TIFR1 & (1<<OCF1A)){
			TIFR1 |= (1<<OCF1A);
			if (cnt){
				cnt--;
			}else{
				uart_clear();						
				c=testAr[n];
				uart_putc(' ');
				uart_putc(c);
				uart_putc(' ');
				uart_putint(pomiar,10);
				uart_puts("\n\r");
				uart_puts("ret=");
				uart_putint(err,10);
				n++;
				if(n==8) {
					n=0;					
					if(stan){
						stan=0;
						err=set_mod_on(0);
					}else{
						stan=1;
						err=set_mod_off(0);
					}					
				}
				cnt=10;
			}
			
		}
    }
}

void main_init(void){
	// INICJACJA SYSTEMOWE
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