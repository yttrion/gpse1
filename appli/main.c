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

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if (t)
		t--;
}

int main(void)
{
	//Init function
	HAL_Init();
	UART_init(UART2_ID, 115200);
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
	Systick_add_callback_function(&process_ms);

	//init servo
	SERVO_init();
	HAL_Delay(2000);
	while (1) //background process
	{
		if (!t)
		{
			t = 200;
			HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);
			//SERVO_process_test();
			SERVO_auto();
		}
	}
}
