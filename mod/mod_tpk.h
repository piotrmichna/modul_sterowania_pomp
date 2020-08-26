/*
 * mod_tpk.h
 *
 * Created: 23.08.2020 06:41:43
  * Author : Piotr Michna
  * e-mail : pm@piotrmichna.pl
 */ 


#ifndef MOD_TPK_H_
#define MOD_TPK_H_

#define MOD_NUM 2
#define NAZWA_NUM 15
#define ADC_SAMPLE_NUM 5	// ilosc prubek do usrednienia max 63

// STEROWNIE KANA£ 0
#define ADC0_KANAL 0		//nr kanalu ADC
#define SW0_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK0_OFF 0		//sterowanie przekaznikiem
#define MTK0_OFF 0		//sterowanie triakiem
#define ENA0_OFF 1		//detekcja obecnosci modulu pomiarowego
#define DET0_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS0_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW0_PIN PD4
#define MPK0_PIN PD5
#define MTK0_PIN PD6
#define ENA0_PIN PD7
#define DET0_PIN PB0
#define RMS0_PIN PC0

#define SW0_PORT D
#define MPK0_PORT D
#define MTK0_PORT D
#define ENA0_PORT D
#define DET0_PORT B
#define RMS0_PORT C

// STEROWANIE KANA£ 1
#define ADC1_KANAL 1		//nr kanalu ADC
#define SW1_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK1_OFF 0		//sterowanie przekaznikiem
#define MTK1_OFF 0		//sterowanie triakiem
#define ENA1_OFF 1		//detekcja obecnosci modulu pomiarowego
#define DET1_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS1_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW1_PIN PB1
#define MPK1_PIN PB2
#define MTK1_PIN PC2
#define ENA1_PIN PC5
#define DET1_PIN PC3
#define RMS1_PIN PC1

#define SW1_PORT B
#define MPK1_PORT B
#define MTK1_PORT C
#define ENA1_PORT C
#define DET1_PORT C
#define RMS1_PORT C

// KODY ZWRACANE Z FUNKCJI
#define F_OK 0
#define F_BRAK_MOD -1
#define F_BRAK_ADC -2
#define F_BRAK_NAPIECIA -3
#define F_BRAK_DEF -4

typedef struct{
	char nazwa[NAZWA_NUM];
	void (*mpk)(uint8_t);
	void (*mtk)(uint8_t);
	void (*ena)(uint8_t);
	uint8_t (*sw)(void);
	uint8_t mpk_f :1;
	uint8_t mtk_f :1;
	uint8_t sw_f :1;
	uint8_t ena_f :1;
	uint8_t adc_kanal :4;
	uint16_t buf[ADC_SAMPLE_NUM];
	uint16_t adc_val;
	uint8_t adc_flag :1;
	uint8_t buf_id :0;
	uint8_t buf_num;
	uint16_t i;
	uint16_t imin;
	uint16_t imax;
}TMOD;

TMOD mod[MOD_NUM];

void mod_init(void);
void mod_set_nazwa(char * buf, uint8_t modx);



#endif /* MOD_TPK_H_ */