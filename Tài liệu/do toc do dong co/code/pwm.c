#include <pwm.h>
unsigned char pwm_pin=0,DIR=0	;
signed int pwm_=0;
#define pwm_pin1 P3_6
#define pwm_pin2 P3_5
#define pwm_en   P3_7


unsigned int T, Ton, Toff;
unsigned int Ton_h, Ton_l, Toff_h, Toff_l;
unsigned int T_on, T_off;
void pwm_init()
{
	// Khoi tao timer 0
	TMOD &= 0xF0;
	TMOD |= 0x01;	// Chon timer 0 che do 16 bit
	ET0 = 1;	//Cho phep ngat timer 0
	EA = 1; 	// Cho phep ngat toan cuc
	TH0 = 0xFF;
	TL0 = 0x01;
	
	TR0 = 1;
}

// duty tu 0 den 100
void set_pwm_duty(unsigned char duty)
{
	if(duty==0) {pwm_en=0;}
	else pwm_en=1;
	if(duty==1) duty=2;
	if(duty >= 100)
	{
		pwm_pin = 1;
		ET0 = 0;
	}
	else if (duty <= 0)
	{
		pwm_pin = 0;
		ET0 = 0;
	}
	else
	{
		Ton = duty * 10; //(chu ky may) // thoi gian o muc 1 la duty/100*1000 chu ky may, 1 chu ky = 1000 chu ky may = 1ms
		T_on = (65548 - Ton);
		Ton_h = T_on >> 8;	
		Ton_l = T_on & 0x00FF;
		
		Toff = 1000 - Ton;
		T_off = (65548 - Toff);
		Toff_h = T_off >> 8;
		Toff_l = T_off & 0x00FF;
		
		ET0 = 1;
	}
}



void Timer0Overflow() interrupt 1
{
	pwm_pin = !pwm_pin;
	if(pwm_==0) pwm_pin=0;
	pwm_pin1=pwm_pin & DIR;
	pwm_pin2=pwm_pin & (!DIR);
	if(pwm_pin == 1)
	{
		TH0 = Ton_h;
		TL0 = Ton_l;
	}
	else
	{
		TH0 = Toff_h;
		TL0 = Toff_l;
	}
}	

