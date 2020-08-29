/*
 * mod_tpk.c
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "../macr.h"
#include "mod_tpk.h"
#include "adc_m328pb.h"

extern TMOD mod[MOD_NUM];
extern TMOD_CNF mcnf;

extern volatile uint8_t det_int_f;
enum tryb {tryb_off, tryb_start, tryb_det, tryb_mtr, tryb_mpk, tryb_run};

void mod_check(void);
void mod_init(void);


#ifdef PWR_OFF
void pwr_set(uint8_t st);
int8_t pwr_on(void);
void pwr_off(void);
#endif

#ifdef MPK0_OFF
void mpk0_set(uint8_t st);
#endif
#ifdef MTK0_OFF
void mtk0_set(uint8_t st);
#endif
#ifdef SW0_OFF
uint8_t sw0_get(void);
#endif
#ifdef ENA0_OFF
void ena0_set(uint8_t st);
#endif
#ifdef DET0_OFF
uint8_t det0_get(void);
#endif
#ifdef MPK1_OFF
void mpk1_set(uint8_t st);
#endif
#ifdef MTK1_OFF
void mtk1_set(uint8_t st);
#endif
#ifdef SW1_OFF
uint8_t sw1_get(void);
#endif
#ifdef ENA1_OFF
void ena1_set(uint8_t st);
#endif
#ifdef DET1_OFF
uint8_t det1_get(void);
#endif


ISR(INT1_vect){
	OCR1A= 1800;
	det_int_f=1;
}

int8_t mod_on(void){
	static int8_t cnt;
	if(!mcnf.init_f) mod_init();
	mod_check();
	for(uint8_t n=0; n<MOD_NUM; n++){
		if(mod[n].sw_f) cnt++;
	}
	mcnf.mod_num=cnt;
	if(!cnt){
		return F_BRAK_MOD;
	}else{
		TCCR1B |= (1<<WGM12);				// tryb CTC
		TCCR1B |= (1<<CS10) | (1<<CS12);	// prescaler 1024
		OCR1A= 1800;						//przerwanie co 100ms
		EIMSK |= (1<<INT1);
		EICRA |= (1<<ISC11);
		cnt=0;
		
		// test detekcji napiecia 230VAC
		while(cnt<32){
			if(TIFR1 & (1<<OCF1A)){
				TIFR1 |= (1<<OCF1A);
				if(!mcnf.det_f){	// jesli nie wykryto detekcji napiecia zasilania
					if(det_int_f){
						//wykryto
						cnt=0;
						det_int_f=0;
						mcnf.det_f=1;
#ifndef PWR_OFF
						mcnf.mod_on_f=1;
						return F_OK;
#endif
					}else{
						cnt++;
						if(cnt==32) return F_BRAK_NAPIECIA;
					}
				}
#ifdef PWR_OFF			
				else{	// wlaczenie zasilania
					if(cnt<mcnf.pwr_delay){	//proga wlaczenia zasilania
						int8_t err;
						err=pwr_on();
						if(!err) {
							cnt=0;
							mcnf.mod_on_f=1;
							return F_OK;
						}else{
							cnt++;
						}						
					}else{
						return F_BLAD_PROGRAMU;
					}
				}
#endif
			}
		}
		return F_BLAD_PROGRAMU;
	}		
}

void mod_off(void){
	TCCR1B &= ~(1<<WGM12);				// tryb CTC
	TCCR1B &= ~(1<<CS10) | (1<<CS12);	// prescaler 1024
	EIMSK &= ~(1<<INT1);
	EICRA &= ~(1<<ISC11);
	OCR1A= 0;
#ifdef PWR_OFF
	pwr_off();
#endif
	mcnf.mod_on_f=0;
}



void mod_set_nazwa(char * buf, uint8_t modx){
	char * c;
	c = mod[modx].nazwa;
	uint8_t n=0;
	while(*buf!=0 && n<NAZWA_NUM){
		*(c+n)=*buf;
		n++;
		buf++;
	}
}
void mod_get_adc(uint8_t md){
	#if ADC_SLEEP_MODE == 0
		// wylacz inne przerwania
		mod[md].buf[ mod[md].buf_id ]=adc_get(md);	//wykonaj pomiar ADC dla przetwornika True RMS
		
		while(!adc_flag) {}	// oczekiwanie na zakonczenie konwersji
		adc_flag=0;
		mod[md].buf[ mod[md].buf_id ]=adc_res;
	#else
		mod[md].buf[ mod[md].buf_id ]=adc_get(md);	//wykonaj pomiar ADC dla przetwornika True RMS
	#endif
	
	// obliczenia
	uint8_t n=mod[md].buf_id+1;
	if(mod[md].buf_num<n) mod[md].buf_num=n;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		mod[md].adc_val=0;
		for(n=0;n<mod[md].buf_num;n++){
			mod[md].adc_val+=mod[md].buf[n];	
		}
		mod[md].i=mod[md].adc_val/mod[md].buf_num;
		if(mod[md].buf_num==ADC_SAMPLE_NUM){		// zapis skrajnych wartosci
			if(mod[md].i>mod[md].imax) mod[md].imax=mod[md].i;
			if(mod[md].i<mod[md].imin) mod[md].imin=mod[md].i;
		}
	}
	mod[md].buf_id++;
	if(mod[md].buf_id==ADC_SAMPLE_NUM) mod[md].buf_id=0;
}

void mod_stop_adc(uint8_t md){
	if(!mcnf.mod_f) adc_stop();
	mod[md].buf_id=0;
	mod[md].buf_num=0;
	mod[md].i=0;
	mod[md].imin=1024;
	mod[md].imax=0;
	if(mod[md].ena) mod[md].ena(0);
}


int8_t mod_set_mpk(uint8_t modx, uint8_t st){
	if(mod[modx].mpk_f!=st){
		if(mod[modx].mpk){
			mod[modx].mpk(st);
			mod[modx].mpk_f=st;
			return F_OK;
		}else{
			return F_BRAK_DEF;
		}
	}else{
		return F_BRAK_DEF;
	}
}

int8_t mod_set_mtk(uint8_t modx, uint8_t st){
	if(mod[modx].mtk_f!=st){
		if(mod[modx].mtk){
			mod[modx].mtk(st);
			mod[modx].mtk_f=st;
			return F_OK;
			}else{
			return F_BRAK_DEF;
		}
		}else{
		return F_BRAK_DEF;
	}
}

int8_t mod_set_ena(uint8_t modx, uint8_t st){
	if(mod[modx].mtk_f!=st){
		if(mod[modx].ena){
			mod[modx].ena(st);
			mod[modx].ena_f=st;
			return F_OK;
		}else{
			return F_BRAK_DEF;
		}
	}else{
		return F_BRAK_DEF;
	}
}


void mod_check(void){
	if(mod[0].sw){
		mod[0].sw_f=mod[0].sw();
	}
	if(mod[1].sw){
		mod[1].sw_f=mod[1].sw();
	}
}

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
#ifdef ENA0_OFF
	mod[0].ena=ena0_set;
	mod[0].ena_f=ENA0_OFF;
#else
	mod[0].ena=0;
	mod[0].ena_f=0;
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
#ifdef ENA1_OFF
	mod[1].ena=ena1_set;
	mod[1].ena_f=ENA1_OFF;
#else
	mod[1].ena=0;
	mod[1].ena_f=0;
#endif

mod[0].adc_kanal=ADC0_KANAL;
mod[1].adc_kanal=ADC1_KANAL;
mod[0].imin=1024;
mod[1].imin=1024;

mod[0].nazwa[0]='K';
mod[0].nazwa[1]='a';
mod[0].nazwa[2]='n';
mod[0].nazwa[3]='a';
mod[0].nazwa[4]='l';
mod[0].nazwa[5]='0';
mod[0].nazwa[6]='\0';

mod[1].nazwa[0]='K';
mod[1].nazwa[1]='a';
mod[1].nazwa[2]='n';
mod[1].nazwa[3]='a';
mod[1].nazwa[4]='l';
mod[1].nazwa[5]='1';
mod[1].nazwa[6]='\0';

	#ifdef DET_INT_OFF
		if(DET_INT_OFF==1) PORT( DET_INT_PORT ) |= (1<<DET_INT_PIN); else PORT( DET_INT_PORT ) |= (1<<DET_INT_PIN);
		DDR( DET_INT_PORT ) &= ~(1<<DET_INT_PIN);
	#endif
	#ifdef PWR_OFF
		if(PWR_OFF==1) PORT( PWR_PORT ) |= (1<<PWR_PIN); else PORT( PWR_PORT ) &= ~(1<<PWR_PIN);
		DDR( PWR_PORT ) |= (1<<PWR_PIN);
	#endif
	
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
	#ifdef ENA0_OFF
		if(ENA0_OFF==1) PORT( ENA0_PORT ) |= (1<<ENA0_PIN); else  PORT( ENA0_PORT ) &= ~(1<<ENA0_PIN);
		DDR( ENA0_PORT ) &= ~(1<<ENA0_PIN);
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
	#ifdef ENA1_OFF
		if(ENA1_OFF==1) PORT( ENA1_PORT ) |= (1<<ENA1_PIN); else  PORT( ENA1_PORT ) &= ~(1<<ENA1_PIN);
		DDR( ENA1_PORT ) &= ~(1<<ENA1_PIN);
	#endif
	#ifdef DET1_OFF
		if(DET1_OFF==1) PORT( DET1_PORT ) |= (1<<DET1_PIN); else PORT( DET1_PORT ) &= ~(1<<DET1_PIN);
		DDR( DET1_PORT ) &= ~(1<<DET1_PIN);
	#endif
	#ifdef RMS1_OFF
		if(RMS1_OFF==1) PORT( RMS1_PORT ) |= (1<<RMS1_PIN); else PORT( RMS1_PORT ) &= ~(1<<RMS1_PIN);
		DDR( RMS1_PORT ) &= ~(1<<RMS1_PIN);
	#endif
	mcnf.init_f=1;
}

#ifdef PWR_OFF
int8_t pwr_on(void){	
	static uint8_t cnt;
	if(!mcnf.pwr_f){
		if(!cnt){
			if (PWR_OFF==1) PORT( PWR_PORT ) &= ~(1<<PWR_PIN); else PORT( PWR_PORT ) |= (1<<PWR_PIN);
			cnt++;
			return 1;
		}else{
			if(cnt<mcnf.pwr_delay-1){
				cnt++;
				return 1;
			}else{
				cnt=0;
				mcnf.pwr_f=1;
				return 0;
			}
		}
	}else{
		return 0;
	}
}
void pwr_off(void){
	if(mcnf.pwr_f){
		if (PWR_OFF==1) PORT( PWR_PORT ) &= ~(1<<PWR_PIN); else PORT( PWR_PORT ) |= (1<<PWR_PIN);
		mcnf.pwr_f=0;
	}
}
#endif

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
#ifdef ENA0_OFF
void ena0_set(uint8_t st){
	if (ENA0_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( ENA0_PORT ) |= (1<<ENA0_PIN); else  PORT( ENA0_PORT ) &= ~(1<<ENA0_PIN);
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
#ifdef ENA1_OFF
void ena1_set(uint8_t st){
	if (ENA1_OFF==1){
		if(st) st=0; else st=1;
	}
	if(st) PORT( ENA1_PORT ) |= (1<<ENA1_PIN); else  PORT( ENA1_PORT ) &= ~(1<<ENA1_PIN);
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