/*
 * mod_tpk.h
 *
 * Created: 23.08.2020 06:41:43
  * Author : Piotr Michna
  * e-mail : pm@piotrmichna.pl
 */ 


#ifndef MOD_TPK_H_
#define MOD_TPK_H_

// STEROWNIE KANA£ 0
#define SW0_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK0_OFF 0		//sterowanie przekaznikiem
#define MTK0_OFF 0		//sterowanie triakiem
#define SWA0_OFF 0		//detekcja obecnosci modulu pomiarowego
#define DET0_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS0_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW0_PIN PD4
#define MPK0_PIN PD5
#define MTK0_PIN PD6
#define SWA0_PIN PD7
#define DET0_PIN PB0
#define RMS0_PIN PC0

#define SW0_PORT D
#define MPK0_PORT D
#define MTK0_PORT D
#define SWA0_PORT D
#define DET0_PORT B
#define RMS0_PORT C

// STEROWANIE KANA£ 1
#define SW1_OFF 1		//detekcja obecnosci modulu sterujacego
#define MPK1_OFF 0		//sterowanie przekaznikiem
#define MTK1_OFF 0		//sterowanie triakiem
//#define SWA1_OFF 0		//detekcja obecnosci modulu pomiarowego
#define DET1_OFF 1		//detekcja napiecia na wyjscu modulu pomiarowego
#define RMS1_OFF 0		//sygnal pomiarowy True RMS dla pro¹du odbiornika

#define SW1_PIN PB1
#define MPK1_PIN PB2
#define MTK1_PIN PC2
//#define SWA1_PIN PD7
#define DET1_PIN PC3
#define RMS1_PIN PC1

#define SW1_PORT B
#define MPK1_PORT B
#define MTK1_PORT C
//#define SWA1_PORT D
#define DET1_PORT C
#define RMS1_PORT C

void mod_init(void);



#endif /* MOD_TPK_H_ */