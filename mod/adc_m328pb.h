/*
 * adc_m328pb.h
 *
 * Created: 24.08.2020 23:16:24
  * Author : Piotr Michna
  * e-mail : pm@piotrmichna.pl
 */ 


#ifndef ADC_M328PB_H_
#define ADC_M328PB_H_

#define ADC_SLEEP_MODE 1
//#define ADC_REFS 0		// AREF, zewnêtrzne napiecie odniesienia
//#define ADC_REFS 64		// AVcc
#define ADC_REFS 192	// Internal 1.1V

//#define ADC_PRESCALER 1		//2
//#define ADC_PRESCALER 2		//4
//#define ADC_PRESCALER 3		//8
//#define ADC_PRESCALER 4		//16
//#define ADC_PRESCALER 5		//32
//#define ADC_PRESCALER 6		//64
#define ADC_PRESCALER 7		//128

uint16_t adc_get(uint8_t modx);
void adc_stop(void);

#if ADC_SLEEP_MODE == 0
volatile uint16_t adc_res;
volatile uint8_t adc_flag;
#endif



#endif /* ADC_M328PB_H_ */