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

// SYSTEMOWE
#define DET_INT_OFF 1	//detekcja przejscia przez zero napiêcia sieciowego
#define PWR_OFF 0		//sterowanie zasilaczem dla peryferi
#define LED_OFF 0		//dioda led pomocnicza
#define TXEN_OFF 1		//sterowanie kierunkiem komunikacji RS485
#define TX_OFF 0		//sterowanie lini¹ TX
#define RX_OFF 0		//sterowanie linia RX

#define DET_INT_PIN PD3
#define PWR_PIN PC4
#define LED_PIN PC5
#define TXEN_PIN PD2
#define TX_PIN PD1
#define RX_PIN PD0

#define DET_INT_PORT D
#define PWR_PORT C
#define LED_PORT C
#define TXEN_PORT D
#define TX_PORT D
#define RX_PORT D

// STEROWNIE KANA£ 0
#define SW0_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK0_OFF 0		//sterowanie przekaznikiem
#define MTK0_OFF 0		//sterowanie triakiem
#define SWA0_OFF 0		//detekcja obecnosci modulu pomiarowego
#define DET0_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS0_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW0_PIN PD4
#define MPK0_PIN PD5
#define MTK0_PIN PD6
#define SWA0_PIN PD7
#define DET0_PIN PB0
#define RMS0_PIN PC0

#define SW0_PORT D
#define MPK0_PORT D
#define MTK0_PORT D
#define SWA0_PORT D
#define DET0_PORT B
#define RMS0_PORT C

// STEROWANIE KANA£ 1
#define SW1_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK1_OFF 0		//sterowanie przekaznikiem
#define MTK1_OFF 0		//sterowanie triakiem
//#define SWA1_OFF 0		//detekcja obecnosci modulu pomiarowego
#define DET1_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS1_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW1_PIN PB1
#define MPK1_PIN PB2
#define MTK1_PIN PC2
//#define SWA1_PIN PD7
#define DET1_PIN PC3
#define RMS1_PIN PC1

#define SW1_PORT B
#define MPK1_PORT B
#define MTK1_PORT C
//#define SWA1_PORT D
#define DET1_PORT C
#define RMS1_PORT C

void main_init(void);

int main(void)
{
    main_init();
	uint8_t n=0;
    while (1) 
    {
		if (!n){
			PORT( MTK0_PORT ) ^= (1<<MTK0_PIN);
			n=4;
		}else{
			n--;
		}
		_delay_ms(500);
    }
}

void main_init(void){
	// INICJACJA KANALU 0
	#ifdef SW0_OFF
		if(SW0_OFF==1) PORT( SW0_PORT ) |= (1<<SW0_PIN); else  PORT( SW0_PORT ) &= ~(1<<SW0_PIN);
		DDR( SW0_PORT ) &= ~(1<<SW0_PIN);
	#endif
	#ifdef MPK0_OFF
		if(MPK0_OFF==1) PORT( MPK0_PORT ) |= (1<<MPK0_PIN); else  PORT( MPK0_PORT ) &= ~(1<<MPK0_PIN);
		DDR( MPK0_PORT ) |= (1<<MPK0_PIN);
	#endif
	#ifdef MTK0_OFF
		if(MTK0_OFF==1) PORT( MTK0_PORT ) |= (1<<MTK0_PIN); else  PORT( MTK0_PORT ) &= ~(1<<MTK0_PIN);
		DDR( MTK0_PORT ) |= (1<<MTK0_PIN);
	#endif
	#ifdef SWA0_OFF
		if(SWA0_OFF==1) PORT( SWA0_PORT ) |= (1<<SWA0_PIN); else  PORT( SWA0_PORT ) &= ~(1<<SWA0_PIN);
		DDR( SWA0_PORT ) &= ~(1<<SWA0_PIN);
	#endif
	#ifdef DET0_OFF
		if(DET0_OFF==1) PORT( DET0_PORT ) |= (1<<DET0_PIN); else PORT( DET0_PORT ) &= ~(1<<DET0_PIN);
		DDR( DET0_PORT ) &= ~(1<<DET0_PIN);
	#endif
	#ifdef RMS0_OFF
		if(RMS0_OFF==1) PORT( RMS0_PORT ) |= (1<<RMS0_PIN); else PORT( RMS0_PORT ) &= ~(1<<RMS0_PIN);
		DDR( RMS0_PORT ) &= ~(1<<RMS0_PIN);
	#endif
	// INICJACJA KANALU 1
	#ifdef SW1_OFF
		if(SW1_OFF==1) PORT( SW1_PORT ) |= (1<<SW1_PIN); else  PORT( SW1_PORT ) &= ~(1<<SW1_PIN);
		DDR( SW1_PORT ) &= ~(1<<SW1_PIN);
	#endif
	#ifdef MPK1_OFF
		if(MPK1_OFF==1) PORT( MPK1_PORT ) |= (1<<MPK1_PIN); else  PORT( MPK1_PORT ) &= ~(1<<MPK1_PIN);
		DDR( MPK1_PORT ) |= (1<<MPK1_PIN);
	#endif
	#ifdef MTK1_OFF
		if(MTK1_OFF==1) PORT( MTK1_PORT ) |= (1<<MTK1_PIN); else  PORT( MTK1_PORT ) &= ~(1<<MTK1_PIN);
		DDR( MTK1_PORT ) |= (1<<MTK1_PIN);
	#endif
	#ifdef SWA1_OFF
		if(SWA1_OFF==1) PORT( SWA1_PORT ) |= (1<<SWA1_PIN); else  PORT( SWA1_PORT ) &= ~(1<<SWA1_PIN);
		DDR( SWA1_PORT ) &= ~(1<<SWA1_PIN);
	#endif
	#ifdef DET1_OFF
		if(DET1_OFF==1) PORT( DET1_PORT ) |= (1<<DET1_PIN); else PORT( DET1_PORT ) &= ~(1<<DET1_PIN);
		DDR( DET1_PORT ) &= ~(1<<DET1_PIN);
	#endif
	#ifdef RMS1_OFF
		if(RMS1_OFF==1) PORT( RMS1_PORT ) |= (1<<RMS1_PIN); else PORT( RMS1_PORT ) &= ~(1<<RMS1_PIN);
		DDR( RMS1_PORT ) &= ~(1<<RMS1_PIN);
	#endif
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