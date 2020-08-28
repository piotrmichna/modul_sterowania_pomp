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
#include "mod/mod_tpk.h"
#include "uart/uart328pb.h"
#include "mod/adc_m328pb.h"

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

int main(void)
{
    main_init();
	mod_init();
	adc_init();
	mod_det0_init();
	if(mod[0].ena) mod[0].ena(1);
	if(mod[0].mpk) mod[0].mpk(1);
	if(mod[0].mtk) mod[0].mtk(0);
	
	USART_Init( __UBRR);

	sei();
	
	uart_clear();
	uart_puts("START\n\r");	
	
	//timer 1
	TCCR1B |= (1<<WGM12); // tryb CTC
	TCCR1B |= (1<<CS10) | (1<<CS12);
	OCR1A= 1800;
	
	uint8_t cnt=25,n=0,stan=0;
	uint16_t pomiar=0;
	char c;
	


    while (1) 
    {	
		if(TIFR1 & (1<<OCF1A)){
			TIFR1 |= (1<<OCF1A);
			if (cnt){
				cnt--;
			}else{
				
				#if ADC_SLEEP_MODE == 0
					if(adc_flag==0)	{
						pomiar=adc_get(0);
						pomiar++;
					}else{
						
						c=testAr[n];
						uart_putc(' ');
						uart_putc(c);
						uart_putc(' ');
						uart_putint(adc_res,10);
						n++;
						if(n==8) {
							n=0;
							if(stan) stan=0; else stan=1;
							if(mod[0].mpk) mod[0].mpk(stan);
							if(mod[0].mtk) mod[0].mtk(stan);
						}
						adc_flag=0;
					}
				#else
					pomiar=adc_get(0);
					uart_clear();
					uart_puts("\n\r int1=");
					uart_putint(det_cnt,10);
					c=testAr[n];
					uart_putc(' ');
					uart_putc(c);
					uart_putc(' ');
					uart_putint(pomiar,10);
				
					n++;
					if(n==8) {
						if(stan) stan=0; else stan=1;
						if(mod[0].mpk) mod[0].mpk(stan);
						if(mod[0].mtk) mod[0].mtk(stan);
						n=0;
					}
				#endif
			
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