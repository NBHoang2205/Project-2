/*
 * input.c
 *
 *  Created on: 25 thg 11, 2021
 *      Author: acer
 */
#include "input.h"


uint16_t cnt = 0, preCnt = 0;


uint8_t read_temp(ADC_HandleTypeDef* hadc, uint16_t* data)
{
	HAL_ADC_Start_DMA(hadc, (uint32_t*)data, 2);
	HAL_DMA_PollForTransfer(hadc->DMA_Handle, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	uint8_t	temp = ((float)data[0]/ 4096) * 3.3 * 100;
	return temp;
}

uint16_t read_speed(TIM_HandleTypeDef htim)
{
	cnt = __HAL_TIM_GET_COUNTER(&htim);
	//pulse of 10ms --*100--> pulse of 1s --/334--> rpm
	uint16_t speed = (cnt - preCnt)*100 / 334;
	preCnt = cnt;
	return speed;
}

