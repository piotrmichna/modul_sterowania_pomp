/*
 * adc_m328pb.c
 *
 * Created: 24.08.2020 23:17:46
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc_m328pb.h"
#if ADC_SLEEP_MODE == 1
	#include <util/atomic.h>
	#include <avr/sleep.h>
#endif


#if ADC_SLEEP_MODE == 0
	extern volatile uint16_t adc_res;
	extern volatile uint8_t adc_flag;
#endif

volatile uint8_t adc_run;
void adc_stop(void){
	adc_run=0;
}

void adc_init(void){
	ADMUX=ADC_REFS;					//wybranie napiecia odniesienia
	ADCSRA=(1<<ADEN) | (1<<ADIE);	//wlaczenie przetwornika i zezwolenie naprzerwanie
	ADCSRA |= ADC_PRESCALER;		//ustawienie preskalera
	adc_run=1;
}

uint16_t adc_get(uint8_t modx){
	ADMUX=ADC_REFS | modx;
	ADCSRA=(1<<ADEN) | (1<<ADIE);	//wlaczenie przetwornika i zezwolenie naprzerwanie
	ADCSRA |= ADC_PRESCALER;		//ustawienie preskalera
	if(modx==1) DIDR0=(1<<ADC1D);
	if(modx==0) DIDR0=(1<<ADC0D);
	#if ADC_SLEEP_MODE == 1
		ADCSRA |= (1<<ADATE);
		set_sleep_mode(SLEEP_MODE_ADC);    //Tryb noise canceller
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {sleep_enable();};     //Odblokuj mo¿liwoœæ wejœcia w tryb sleep
		sleep_cpu();                       //WejdŸ w tryb uœpienia
		sleep_disable();                   //Zablokuj mo¿liwoœæ wejœcia w tryb sleep
		if(!adc_run) ADCSRA=0;
		return ADC;
		
	#else
		ADCSRA |= (1<<ADSC);
		adc_flag=0;
		return 0;
	#endif
	
}

ISR(ADC_vect){
	#if ADC_SLEEP_MODE == 0
		adc_res=ADC;
		adc_flag=1;
		ADCSRA=0;
	#endif
}