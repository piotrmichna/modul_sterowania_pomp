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

int main(void)
{
    
    while (1) 
    {
    }
}

