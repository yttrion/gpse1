#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "stm32f1_uart.h"
#include "stm32f1_rtc.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_sys.h"

/*
   (servo index, pin to attach pwm)
   __________ __________ _________________
  |(1,3)_____)(1,1)      (1,2)(______(1,4)|
  |__|       |left FRONT right|        |__|
             |                |
             |                |
             |                |
   _________ |                | __________
  |(4,3)_____)(4,1)______(4,2)(______(4,4)|
  |__|                                 |__|
*/



//timer_id_e timers = [TIMER1_ID, TIMER4_ID];
//typedef enum { TIM_CHANNEL_1,TIM_CHANNEL_2,TIM_CHANNEL_3,TIM_CHANNEL_4 } channels_e;
/*
typedef enum {
	POS_reset = 150,
	POS_open = 130,
	POS_close = 170,
	POS_o_pied = 110,
	POS_c_pied = 190
} pos_e;

typedef enum channels_e{
	CHANNEL_1 = 0x00000000U,
	CHANNEL_2 = 0x00000004U,
	CHANNEL_3 = 0x00000008U,
	CHANNEL_4 = 0x0000000CU
};


//Definition des servos
typedef struct {
	bool_e inverted;
	uint8_t timer;
	uint8_t channel;
} servo_t;

void SERVO_reinitialisation(){

	for(int i=0; i<8; i++){
		SERVO_set_position(servo_e[i][0], servo_e[i][1], servo_e[i][2], 150);
	}


}

servo_t servo_e[8][3] = {
						{FALSE, 0, CHANNEL_1},
						{FALSE, 0, CHANNEL_2},
						{FALSE, 0, CHANNEL_3},
						{FALSE, 0, CHANNEL_4},
						{FALSE, 3, CHANNEL_1},
						{FALSE, 3, CHANNEL_2},
						{FALSE, 3, CHANNEL_3},
						{FALSE, 3, CHANNEL_4}};

*/







#define PERIOD_TIMER 10
static uint16_t current_position;




void SERVO_init(bool_e ini){
	if(ini){
		//Init reg
		TIMER_run_us(TIMER1_ID, PERIOD_TIMER * 1000, FALSE); //10000us = 10ms
		TIMER_run_us(TIMER4_ID, PERIOD_TIMER * 1000, FALSE); //10000us = 10ms
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE); //GENOU AV G
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2, 150, FALSE, FALSE); //GENOU AV D
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE); //PIED AV G
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_4, 150, FALSE, FALSE); //PIED AV D
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 150, FALSE, FALSE); //GENOU ARR G
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, 150, FALSE, FALSE); //GENOU ARR D
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_3, 150, FALSE, FALSE); //PIED ARR G
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_4, 150, FALSE, FALSE); //PIED ARR D
	
	} else {
		//Position initiale des servos
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 150);	//GENOU AV G
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 150);	//GENOU AV D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150);	//PIED AV G
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 150);	//PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 150);	//GENOU ARR G	
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 150);	//GENOU ARR D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 150);	//PIED ARR G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 150);	//PIED ARR D
	}

}



uint16_t SERVO_get_position(void){
	return current_position;
}

void SERVO_set_position(bool_e invert, timer_id_e timer, uint8_t chan, uint16_t position){

	if(!invert){
		TIMER_set_duty(timer, chan, position+100);
	} else {
		TIMER_set_duty(timer, chan, (100-position)+100);
	}
	current_position = position;

}


void SERVO_pompes(void){
	static uint16_t position = 0;
	position = (position > 99) ? 0 : (position + 99);
	HAL_Delay(10);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, position+100);	
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, (100-position)+100);
	current_position = position;
	HAL_Delay(175);
}

void SERVO_rot_r(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 170); //LEVE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 220); //LEVE PIER AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170); //RAMENE GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 200); //RAMENE GENOU AR D
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 100); //PARS GENOU AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 200); //PARS GENOU AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 90); //LEVE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 90); //LEVE PIED ARR G
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 100);	//BAISSE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 140); //BAISSE PIED AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 100); //PARS GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 130); //PARS GENOU AR D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100); //RAMENE GENOU AR D
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); //RAMENE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 170); //RAMENE PIED ARR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 170); //POSE PIED ARR G
		HAL_Delay(150);
}

void SERVO_rot_l(void){	
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 190); //LEVE PIED AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 130); //LEVE PIER AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 130); //PARS GENOU AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 130); //PARS GENOU AR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 110); //PARS GENOU AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 170); //PARS GENOU AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150); //POSE PIED AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 150); //POSE PIER AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 100); //LEVE PIED AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 190); //LEVE PIED ARR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170); //PARS GENOU AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 170); //PARS GENOU AR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); //PARS GENOU AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 150); //PARS GENOU AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 130); //POSE PIED ARR G
		HAL_Delay(30);



}


void SERVO_forward(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 190); //LEVE PIED AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 110); //PARS GENOU AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150); //POSE PIED AV G
		HAL_Delay(60);

		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 100); //LEVE PIED AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 190); //PARS GENOU AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		HAL_Delay(60);

		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 190); //LEVE PIED ARR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 130); //PARS GENOU AR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 130); //POSE PIED ARR G
		HAL_Delay(60);



		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 130); //LEVE PIER AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 170); //PARS GENOU AR D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 150); //POSE PIER AR D
		HAL_Delay(60);




		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 130); //PARS GENOU AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); //PARS GENOU AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 170); //PARS GENOU AR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 150); //PARS GENOU AR D
		HAL_Delay(60);
		
		
}


void SERVO_coucou(void){
	SERVO_init(FALSE);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 200);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 180);

	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 180);
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 180);
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 190);
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 110);
	HAL_Delay(200);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 80);
	HAL_Delay(200);
}

void SERVO_test(void){
	static uint16_t position = 0;
	position = (position > 99) ? 0 : (position + 99); //de 0 � 100%, par pas de 5%
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, position+100);
	HAL_Delay(210); //anti-rebond "de fortune" en cadencant la lecture du bouton
}



















// 	KAME  //
