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
	if(xmod<=mcnf.mod_num){
		
	}
}
