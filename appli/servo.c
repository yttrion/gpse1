#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "stm32f1_uart.h"
#include "stm32f1_rtc.h"
#include "stm32f1xx_hal.h"


/*
typedef enum
{
	POS_RESET 			= 150,
	POS_HORIZONTAL	 = 50,
	POS_PATE_EN_AVANT = 75
}pos_e;
typedef enum
{
	SERVO_FORWARD_LEFT_VERTICAL = 0,
	SERVO_FORWARD_LEFT_HORIZONTAL,
	SERVO_NB
};

typedef struct
{
	uint8_t pos[SERVO_NB];

}full_pos_t;

static full_pos_t reset_position = (full_pos_t){POS_RESET, POS_RESET, POS_RESET, 2, 1, 6, 7, 8};

static full_pos_t full_pos_to_walk[10] = {	(full_pos_t){2, POS_PATE_EN_AVANT, 			3, 				2, 				1, 			6, 		7, 		8}	,
											(full_pos_t){2, 4, 3, 2, 1, 6, 7, 8}	}	;




void SERVO_set_full_pos(full_pos_t * full_pos)
{
	for(uint8_t i = 0; i<SERVO_NB; i++)
	{
		SERVO_set_pos(i, full_pos->pos[i]);
	}
}

*/
//ms

//pour tout reseter :
//SERVO_set_full_pos(&reset_position);



#define PERIOD_TIMER 10
static uint16_t current_position;


//Test function for all servos
void SERVO_rand(void){
	static uint16_t position = 0;
	position = (position > 99) ? 0 : (position + 99); //de 0 � 100%, par pas de 5%
	SERVO_set_position(position, TRUE);
	HAL_Delay(210); //anti-rebond "de fortune" en cadencant la lecture du bouton
}

void SERVO_reset(void){

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

void SERVO_init(void){

	//Init reg
	TIMER_run_us(TIMER1_ID, PERIOD_TIMER * 1000, FALSE); //10000us = 10ms
	TIMER_run_us(TIMER4_ID, PERIOD_TIMER * 1000, FALSE); //10000us = 10ms
	//Init timers channels

	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE); //GENOU AV G
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2, 150, FALSE, FALSE); //GENOU AV D
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE); //PIED AV G
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_4, 150, FALSE, FALSE); //PIED AV D
	TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 150, FALSE, FALSE); //GENOU ARR G
	TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, 150, FALSE, FALSE); //GENOU ARR D
	TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_3, 150, FALSE, FALSE); //PIED ARR G
	TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_4, 150, FALSE, FALSE); //PIED ARR D
	
}

uint16_t SERVO_get_position(void){
	return current_position;
}

void SERVO_set_position(uint16_t position, bool_e delayed)
{
	//if (position > 100){position = 100;}
	//TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, position+100);
	//TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, position+100);
	//TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, position+100);	
	//TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, (100-position)+100);

	//TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, position+100);
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, position+100);
	//TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, (100-position)+100); //Inverse
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, position+50); //Sensible
	

	current_position = position;

}


void SERVO_pompes(void){
		static uint16_t position = 0;
		position = (position > 99) ? 0 : (position + 99); //de 0 � 100%, par pas de 5%
		HAL_Delay(10);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, position+100);	
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, (100-position)+100);
		current_position = position;
		HAL_Delay(150);
}

void SERVO_rot_r(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 200); //LEVE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 220); //LEVE PIER AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170); //RAMENE GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 170); //RAMENE GENOU AR D
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 100); //PARS GENOU AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 200); //PARS GENOU AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 90); //LEVE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 90); //LEVE PIED ARR G
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 140);	//BAISSE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 140); //BAISSE PIED AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 100); //PARS GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100); //PARS GENOU AR D
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); //RAMENE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 170); //RAMENE PIED ARR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 170); //POSE PIED ARR G
		HAL_Delay(100);
}

void SERVO_rot_l(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 200); //LEVE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 220); //LEVE PIER AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 90); //RAMENE GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 90); //RAMENE GENOU AR D
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 200); //PARS GENOU AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 100); //PARS GENOU AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 90); //LEVE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 90); //LEVE PIED ARR G
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 140); //BAISSE PIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 140); //BAISSE PIED AR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170); //PARS GENOU AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 170); //PARS GENOU AR D
		HAL_Delay(100);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); //RAMENE GENOUPIED AV G
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 170); //RAMENE GENOU ARR D
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 170); //POSE PIED ARR G
		HAL_Delay(100);
}