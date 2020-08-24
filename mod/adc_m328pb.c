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

int adc_get(uint8_t modx){
	ADMUX=ADC_REFS | modx;
	set_sleep_mode(SLEEP_MODE_ADC);    //Tryb noise canceller
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {sleep_enable();};     //Odblokuj mo¿liwoœæ wejœcia w tryb sleep
	sleep_cpu();                       //WejdŸ w tryb uœpienia
	sleep_disable();                   //Zablokuj mo¿liwoœæ wejœcia w tryb sleep
	return ADC;
}

ISR(ADC_vect){

}