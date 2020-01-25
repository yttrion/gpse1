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
  |(4,3)_____)(4,1)N______(4,2)(______(4,4)N|
  |__|                                 |__|
*/


//int turn_l_pos [16] = {190,130,130,130,110,170,150,150,100,190,170,170,170,150,170,130};
//int turn_for_pos [16] = {190,130,130,130,110,170,150,150,100,190,170,170,170,150,170,130};


#define nbSERVO = 8
#define PERIOD_TIMER 10

static uint16_t current_position;


void SERVO_init(bool_e ini){
	if(ini){
		//Init reg
		TIMER_run_us(TIMER1_ID, PERIOD_TIMER * 1000, FALSE);
		TIMER_run_us(TIMER4_ID, PERIOD_TIMER * 1000, FALSE);
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_4, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_3, 150, FALSE, FALSE);
		TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_4, 150, FALSE, FALSE);
	
	} else {
		//Position initiale des servos
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 150);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 150);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 150);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 150);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 150);
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
	HAL_Delay(150);
}

void SERVO_rot_r(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 170); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 220); 
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 200); 
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 100); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 200); 
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 90); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 90); 
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 100);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 140); 
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 100); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 130); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100); 
		HAL_Delay(150);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 170); 
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); 
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 170); 
		HAL_Delay(150);
}

void SERVO_rot_l(void){	
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 190);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 130);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 130);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 130);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 110);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 170);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_4, 150);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 100);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 190);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 170);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 170);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 170);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 150);
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170);
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 130);
		HAL_Delay(30);
}


void SERVO_forward(void){
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 190); //LEVE PIED AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, 110); //PARS GENOU AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, 150); //POSE PIED AV G
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 100); //LEVE PIED AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, 190); //PARS GENOU AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 170); //POSE PIED AV D
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 190); //LEVE PIED ARR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 130); //PARS GENOU AR G
		HAL_Delay(30);
		TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_3, 130); //POSE PIED ARR G
		HAL_Delay(30);
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


	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 110);
	TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, 190);

	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, 190);
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
