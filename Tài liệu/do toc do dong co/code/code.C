#include <AT89X52.h>
#include <pwm.c>
#include <stdio.h>
#include <lcd1.h>

#define bt_up	  P1_0 
#define bt_down	  P1_1


signed int pulse = 0, pulse1 = 0;
unsigned char sample_count = 0; // dem so lan ngat timer 1
char str[16];

  void set_pwm_();



//Ham hien thi toc do va phan tram xung

void display()
{
	LCD_gotoxy(0,1);
	sprintf(str,"xung: %3i",pwm_);
	LCD_PutsChar(str);
	LCD_gotoxy(0,2);
	sprintf(str,"Toc do:%5i v/s",(signed int)((float)pulse1/8.35));
	LCD_PutsChar(str);
}

void set_pwm_()
{
	 if(pwm_>0)
		 {
			 set_pwm_duty(pwm_); 
			 DIR=1;
	     }
		 else if(pwm_<0)
		 {
		 	set_pwm_duty(-pwm_); 
			DIR=0;
		 }
		

}

void button()
{	  int c=0;
	  if(bt_up==0) 
	  	{	delay_ms(100);
			while(bt_up==0)
			{	c++;
				if(c==30000) 
				{
					while(bt_up==0)
					{
					if(pwm_<50)
						pwm_++;
						set_pwm_();
					delay_ms(5);
					display();
					}
				   c=0;
				}
			}
			if(pwm_<50)
				pwm_++;
		   set_pwm_();
			c=0;
		}
		 if(bt_down==0) 
	  	{	delay_ms(100);
			while(bt_down==0)
			{	c++;
				if(c==30000) 
				{
					while(bt_down==0)
					{
					if(pwm_>-50)
						pwm_--;
					set_pwm_();
					delay_ms(5);
					display();
					}
				    c=0;
				}
			}
			if(pwm_>-50)
				pwm_--;
			set_pwm_();
			c=0;
		}
}

//--------------------TIMER1-----------------

// khoi tao timer 1
void timer1_init()
{
		EA = 1;// cho phep ngat toan cuc
	ET1 = 1; //Cho phep ngat timer 1;

	TMOD &= 0x0F;
	TMOD |= 0x10; //timer 1 che do 16bit
	TH1 = 0x9E;
	TL1 = 0x58; //tu 9F58 den FFFF la 25000 pulse ~ 25ms
	TR1 = 1;
	
	
}

//-------------------EXTERNAL1----------------
void ngatngoai0_init()
{
	EA=1;
	EX0 = 1;// cho phep ngat ngoai 1
	IT0 = 1;//ngat theo suon
	
}

 
//timer 1
//sau 25ms thi thuc hien chuong trinh phuc vu ngat

void Timer1overflow(void) interrupt 3
{	
	
	EX0 = 0;//cam ngat ngoai
	pulse1 = pulse;
	pulse=0;
	TH1 = 0x9E;
	TL1 = 0x58; //tu 9F58 den FFFF la 25000 xung ~ 25ms
	TR1 = 1;
	EX0 = 1;//bat ngat ngoai
}

//khi nao co xung thi dem
void External0(void) interrupt 0
{
	if(P3_3 == 0)
		pulse++;
	else pulse--;
}


void main()
{	pwm_pin1=0;
	pwm_pin2=0;
	pwm_en=0;
	LCD_inits();	
    timer1_init();
	ngatngoai0_init();
	pwm_init();
	
	while(1)
	{  	
		 display();
		 button();
		 set_pwm_();
	}
}

