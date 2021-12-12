#ifndef _PWM_H_
#define _PWM_H_

void pwm_init();

void pwm_set_duty(unsigned char duty);

void pwm_set(unsigned int output, unsigned int spt);

//void Timer0Overflow() interrupt 1

#endif
