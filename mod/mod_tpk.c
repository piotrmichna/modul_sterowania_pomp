/*
 * mod_tpk.c
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 
#include <avr/io.h>
#include <stdlib.h>

typedef struct{
	char nazwa[NAZWA_NUM];
	void (*mpk)(uint8_t);
	void (*mtk)(uint8_t);
	uint8_t (*sw)(void);
	uint8_t (*swa)(void);
	uint8_t:1 mpk_f;
	uint8_t:1 mtk_f;
	uint8_t:1 sw_f;
	uint8_t:1 swa_f;
	uint8_t:4 adc_kanal;
	uint16_t i;
	uint16_t imin;
	uint16_t imax;
}TMOD;

TMOD mod[MOD_NUM];

#ifdef MPK0_OFF
void mpk0_set(uint8_t st);
#endif
#ifdef MTK0_OFF
void mtk0_set(uint8_t st);
#ifdef SW0_OFF
uint8_t sw0_get(void);
#endif
#ifdef SWA0_OFF
uint8_t swa0_get(void);
#endif
#ifdef DET0_OFF
uint8_t det0_get(void);
#endif
#ifdef MPK1_OFF
void mpk1_set(uint8_t st);
#endif
#ifdef MTK1_OFF
void mtk1_set(uint8_t st);
#ifdef SW1_OFF
uint8_t sw1_get(void);
#endif
#ifdef SWA1_OFF
uint8_t swa1_get(void);
#endif
#ifdef DET1_OFF
uint8_t det1_get(void);
#endif


void mod_init(void){
#ifdef MPK0_OFF
	mod[0].mpk=mpk0_set;
	mod[0].mpk_f=MPK0_OFF;
#else
	mod[0].mpk=0;
	mod[0].mpk_f=0;
#endif
#ifdef MTK0_OFF
	mod[0].mtk=mtk0_set;
	mod[0].mtk_f=MTK0_OFF;
#else
	mod[0].mtk=0;
	mod[0].mtk_f=0;
#endif
#ifdef SW0_OFF
	mod[0].sw=sw0_get;
	mod[0].sw_f=SW0_OFF;
#else
	mod[0].sw=0;
	mod[0].sw_f=0;
#endif
#ifdef SWA0_OFF
	mod[0].swa=swa0_get;
	mod[0].swa_f=SWA0_OFF;
#else
	mod[0].swa=0;
	mod[0].swa_f=0;
#endif

#ifdef MPK1_OFF
	mod[1].mpk=mpk1_set;
	mod[1].mpk_f=MPK1_OFF;
#else
	mod[1].mpk=0;
	mod[1].mpk_f=0;
#endif
#ifdef MTK1_OFF
	mod[1].mtk=mtk1_set;
	mod[1].mtk_f=MTK1_OFF;
#else
	mod[1].mtk=0;
	mod[1].mtk_f=0;
#endif
#ifdef SW1_OFF
	mod[1].sw=sw1_get;
	mod[1].sw_f=SW1_OFF;
#else
	mod[1].sw=0;
	mod[1].sw_f=0;
#endif
#ifdef SWA1_OFF
	mod[1].swa=swa1_get;
	mod[1].swa_f=SWA1_OFF;
#else
	mod[1].swa=0;
	mod[1].swa_f=0;
#endif

mod[0].adc_kanal=ADC0_KANAL;
mod[1].adc_kanal=ADC1_KANAL;
	
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
}

#ifdef MPK0_OFF
void mpk0_set(uint8_t st){
	if (MPK0_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( MPK0_PORT ) |= (1<<MPK0_PIN); else  PORT( MPK0_PORT ) &= ~(1<<MPK0_PIN);
}
#endif
#ifdef MTK0_OFF
void mtk0_set(uint8_t st){
	if (MTK0_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( MTK0_PORT ) |= (1<<MTK0_PIN); else  PORT( MTK0_PORT ) &= ~(1<<MTK0_PIN);
}
#endif
#ifdef SW0_OFF
uint8_t sw0_get(void){
	uint8_t st;
	st=( PIN(SW0_PORT) & (1<<SW0_PIN) );
	if (SW0_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif
#ifdef SWA0_OFF
uint8_t swa0_get(void){
	uint8_t st;
	st=( PIN(SWA0_PORT) & (1<<SWA0_PIN) );
	if (SWA0_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif
#ifdef DET0_OFF
uint8_t det0_get(void){
	uint8_t st;
	st=( PIN(DET0_PORT) & (1<<DET0_PIN) );
	if (DET0_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif

#ifdef MPK1_OFF
void mpk1_set(uint8_t st){
	if (MPK1_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( MPK1_PORT ) |= (1<<MPK1_PIN); else  PORT( MPK1_PORT ) &= ~(1<<MPK1_PIN);
}
#endif
#ifdef MTK1_OFF
void mtk1_set(uint8_t st){
	if (MTK1_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( MTK1_PORT ) |= (1<<MTK1_PIN); else  PORT( MTK1_PORT ) &= ~(1<<MTK1_PIN);
}
#endif
#ifdef SW1_OFF
uint8_t sw1_get(void){
	uint8_t st;
	st=( PIN(SW1_PORT) & (1<<SW1_PIN) );
	if (SW1_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif
#ifdef SWA1_OFF
uint8_t swa1_get(void){
	uint8_t st;
	st=( PIN(SWA1_PORT) & (1<<SWA1_PIN) );
	if (SWA1_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif
#ifdef DET1_OFF
uint8_t det1_get(void){
	uint8_t st;
	st=( PIN(DET1_PORT) & (1<<DET1_PIN) );
	if (DET1_OFF==1){
		if(st) st=0; else st=1;
	}
	return st;
}
#endif