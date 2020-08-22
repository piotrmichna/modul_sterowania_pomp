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

int main(void)
{
    
    while (1) 
    {
    }
}

