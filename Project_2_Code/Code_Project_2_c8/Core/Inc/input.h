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

uint8_t read_temp(ADC_HandleTypeDef* hadc, uint16_t* data);
uint16_t read_speed(TIM_HandleTypeDef htim);

#endif /* INC_INPUT_H_ */
