/*
 * input.h
 *
 *  Created on: 25 thg 11, 2021
 *      Author: acer
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include <stdint.h>
#include <stm32f1xx_hal.h>

uint8_t read_temp(ADC_HandleTypeDef hadc);
uint16_t read_speed(TIM_HandleTypeDef htim);

uint16_t data[2];

uint16_t cnt = 0, preCnt = 0;
#endif /* INC_INPUT_H_ */
