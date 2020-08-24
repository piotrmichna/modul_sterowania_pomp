/*
 * adc_m328pb.c
 *
 * Created: 24.08.2020 23:17:46
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/sleep.h>

#include "adc_m328pb.h"

void adc_init(void){
	ADMUX=ADC_REFS;					//wybranie napiecia odniesienia
	ADCSRA=(1<<ADEN) | (1<<ADIE);	//wlaczenie przetwornika i zezwolenie naprzerwanie
	ADCSRA |= ADC_REFS;				//ustawienie preskalera
}
