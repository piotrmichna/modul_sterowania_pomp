/*
 * mod.c
 *
 * Created: 28.08.2020 05:13:08
 * Author : Piotr Michna
 * e-mail : pm@piotrmichna.pl
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/atomic.h>

#include "mod.h"
#include "mod_tpk.h"
#include "adc_m328pb.h"

int8_t set_mod_on(uint8_t xmod){
	int8_t ret;
	if(xmod<=mcnf.mod_num){
		if(!mcnf.mod_on_f) {
			ret=mod_on();
			if(ret) return ret;
		}
		if( !(mcnf.mod_f & (1<<xmod)) ){
			if(det_int_f){
				det_int_f=0;
			}
			if(!mod[xmod].mtk_f){
				ret=mod_set_mtk(xmod,1);
				if(ret)	return ret; else return F_ON_PROGRES;
			}else{
				if(!mod[xmod].mpk_f){
					ret=mod_set_mpk(xmod,1);
					if(ret)	return ret;  else return F_ON_PROGRES;
				}else{
					if(!mod[xmod].ena_f){
						ret=mod_set_ena(xmod,1);
						if(ret) return ret;  else return F_ON_PROGRES;
					}else{
						mod_get_adc(xmod);
						mcnf.mod_f |= (1<<xmod);
						return F_OK;
					}
				}
			}
		}else{
			return F_EMPTY_COLL;
		}		
	}else{
		return F_BRAK_MOD;
	}
}

int8_t set_mod_off(uint8_t xmod){
	int8_t ret;
	if(mcnf.mod_f & (1<<xmod)){
		if(det_int_f){
			det_int_f=0;
		}
		if(mod[xmod].ena_f){
			ret=mod_set_ena(xmod,0);
			if(ret) return ret; else return F_ON_PROGRES;
			}else{
			if(mod[xmod].mpk_f){
				ret=mod_set_mpk(xmod,0);
				if(ret)	return ret; else return F_ON_PROGRES;
				}else{
				if(mod[xmod].mtk_f){
					ret=mod_set_mtk(xmod,0);
					if(ret)	return ret; else return F_ON_PROGRES;
					}else{
					mcnf.mod_f &= ~(1<<xmod);
					mod_stop_adc(xmod);
					if(mcnf.mod_f==0) {
						mod_off();
					}
					return F_OK;
				}
			}
		}
	}else{
		return F_EMPTY_COLL;
	}
}
