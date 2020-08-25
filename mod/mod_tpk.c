/*
 * mod_tpk.c
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 
#include <avr/io.h>
#include <stdlib.h>

#include "../macr.h"
#include "mod_tpk.h"

extern TMOD mod[MOD_NUM];

void mod_check(void);
int mod_set_mpk(uint8_t modx, uint8_t st);
int mod_set_mtk(uint8_t modx, uint8_t st);

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
int mod_set_mpk(uint8_t modx, uint8_t st){
	if(mod[modx].mpk_f!=st){
		if(mod[modx].mpk){
			mod[modx].mpk(st);
			mod[modx].mpk_f=st;
			return st;
		}else{
			return F_BRAK_DEF;
		}
	}else{
		return F_BRAK_DEF;
	}
}

int mod_set_mtk(uint8_t modx, uint8_t st){
	if(mod[modx].mtk_f!=st){
		if(mod[modx].mtk){
			mod[modx].mtk(st);
			mod[modx].mtk_f=st;
			return st;
			}else{
			return F_BRAK_DEF;
		}
		}else{
		return F_BRAK_DEF;
	}
}

int mod_set_ena(uint8_t modx, uint8_t st){
	if(mod[modx].mtk_f!=st){
		if(mod[modx].ena){
			mod[modx].ena(st);
			mod[modx].ena_f=st;
			return st;
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