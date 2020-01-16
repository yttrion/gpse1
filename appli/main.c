/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/

// Edited by Pierre-Yves Douault & Andy Cousineau

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"

//Custom imports
#include "stm32f1_rtc.h"
#include "stm32f1_pwm.h"
#include "config.h"
#include "servo.h"

#define RESET 'x'

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}


static volatile uint32_t t = 0;
void process_ms(void)
{
	if (t)
		t--;
}
	int main(void){

	//Init function
	HAL_Init();

	//Init UART
	UART_init(UART2_ID, 9600);
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	Systick_add_callback_function(&process_ms);
	

	//init servo
	SERVO_init();
	SERVO_reset();
	//HAL_Delay(2000);
	printf("[*] - BB-9 ready!\n");
	while (1) //background process
	{

		if(UART_data_ready(UART2_ID))
  			{
  				uint8_t c;
  				c = UART_get_next_byte(UART2_ID);
  				if(c=='p'){
  					printf("[*] - Push-ups enabled\n");
  					while(UART_get_next_byte(UART2_ID)!=RESET){
  	  					SERVO_pompes();
  					}
  					SERVO_reset();
  					printf("[*] - Stopped push-ups\n");

				  }
  				if(c==RESET){
  					printf("[!] - Reset position\n");
  					SERVO_reset();
  				}
  				if(c=='r'){
  					printf("[*] - Turn right\n");
					SERVO_reset();
					while(UART_get_next_byte(UART2_ID)!=RESET){
						SERVO_rot_r();
					}
					SERVO_reset();
  				}
				if(c=='l'){
  					printf("[*] - Turn left\n");
					SERVO_reset();
					while(UART_get_next_byte(UART2_ID)!=RESET){
						SERVO_rot_l();
					}
					SERVO_reset();
  				}

  			}
  			

	}


}
