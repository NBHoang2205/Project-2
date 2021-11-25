/*
 * PID.h
 *
 *  Created on: Nov 25, 2021
 *      Author: acer
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>
//variable for PID
#define T		0.01
#define Kp		1
#define Ki		10
#define Kd		0.1

uint8_t PID(uint16_t actualSpeed, uint16_t desireSpeed);

uint16_t preError = 0, error = 0, sumError = 0;
float rateError = 0;

#endif /* INC_PID_H_ */
