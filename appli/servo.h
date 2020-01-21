#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

void SERVO_init(bool_e ini);
uint16_t SERVO_get_position(void);
void SERVO_set_position(bool_e invert, uint8_t timer, uint8_t chan, uint16_t position);

void SERVO_reinitialisation(void);

void SERVO_pompes(void);
void SERVO_rot_r(void);
void SERVO_rot_l(void);
void SERVO_forward(void);
void SERVO_coucou(void);

#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#endif /* SERVO_H_ */
