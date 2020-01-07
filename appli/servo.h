#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

void SERVO_init(void);
void SERVO_set_position(uint16_t position);
void SERVO_process_test(void);
void SERVO_process_azimuth(uint16_t position);
void SERVO_auto(void);
uint16_t SERVO_get_position(void);



#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#endif /* SERVO_H_ */