/*
 * PID.C
 *
 *  Created on: Nov 25, 2021
 *      Author: acer
 */
#include <PID.h>
#include <stdint.h>

uint16_t preError = 0, error = 0, sumError = 0;
float rateError = 0;

uint8_t PID(uint16_t actualSpeed, uint16_t desireSpeed)
{
	error = desireSpeed - actualSpeed;
	sumError += error*T;
	rateError =(float)(error - preError)/T;
	uint8_t duty = Kd*error + Ki*sumError + Kd*rateError;

	preError = error;
	return duty;
}



/**
  * @brief Config PID
  * @param T: sampling cycle: recommend value = 0.01s
  * @retval None
  */
#if 0
void PID_Config(uint8_t Kp, uint8_t Ki, uint8_t Kd, float T)
{
	alpha = 2*T*Kp + Ki*T*T + 2*Kd;
	beta = T*T*Ki - 4*Kd - 2*T*Kp;
	gamma = 2*Kd;

}
#endif
/**
  * @brief Config PID
  * @param
  * @retval None
  */
#if 0
void PID(uint16_t setPoint_Speed, uint16_t actual_Speed)
{
	static uint16_t e0 = 0, e1 = 0, e2 = 0;
	e0 = setPoint_Speed - actual_Speed;
	duty = (alpha*e0 + beta*e1 + gamma*e2 + pre_duty) / (2*T);
	pre_duty = duty;
	e2 = e1;
	e1 = e0;
	TIM2_PWM_Set_Duty(duty);
}
#endif
