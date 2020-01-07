#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#define PERIOD_TIMER 10 //ms

static uint16_t current_position;

//Pins for servos
//typedef enum {1,2} servos;

//Test function for all servos
void SERVO_auto(void)
{
	static uint16_t position = 0;
	position = (position > 99) ? 0 : (position + 99); //de 0 � 100%, par pas de 5%
	SERVO_set_position(position, TRUE);
	HAL_Delay(10); //anti-rebond "de fortune" en cadencant la lecture du bouton
}

void SERVO_init(void)
{
	//initialisation et lancement du timer1 � une p�riode de 10 ms
	TIMER_run_us(TIMER1_ID, PERIOD_TIMER * 1000, FALSE); //10000us = 10ms

	//Init timers
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2, 150, FALSE, FALSE);
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE);
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_4, 150, FALSE, FALSE);

	//Default position
	SERVO_set_position(0, FALSE);
}

uint16_t SERVO_get_position(void)
{
	return current_position;
}

//position est exprim�e de 0 � 100.
void SERVO_set_position(uint16_t position, bool_e delayed)
{
	if (position > 100)
		position = 100;

	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, position + 100);
	//if (delayed){HAL_Delay(100);}
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_2, position + 100);
	//if (delayed){HAL_Delay(100);}
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, position + 100);
	//if (delayed){HAL_Delay(100);}
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_4, position + 100);
	current_position = position;
}
