
#define LCD_E  P0_2
#define LCD_RS P0_0
#define LCD_RW P0_1
#define LCD_4  P0_3
#define LCD_5  P0_4
#define LCD_6  P0_5
#define LCD_7  P0_6



void delay_ms(int time)
{	int i,j;
	for(j=0;j<time;j++)
	 {
 		 for(i=0;i<125;i++); 
     }
}


///Khai bao cac ham con
void LCD_enable();
void LCD_Send_4bit();
void LCD_Sendcommand();
void LCD_Putchar();
void LCD_Putschar();
void LCD_gotoxy();
void clear();

void LCD_inits();

//===========Tao xung enable==========//

  

 void LCD_Enable(void)
{
    LCD_E=1;
    delay_ms(1);
    LCD_E=0;
    delay_ms(1);   
}
//=====Ham gui 4bit=====//
void LCD_Send_4bit(unsigned char dat)
{
   LCD_4=dat & 0x01;  //lcd4
   LCD_5=(dat>>1) & 0x01; //dich sang trai 1 bit va so sanh lcd5
   LCD_6=(dat>>2) & 0x01;//lcd6
   LCD_7=(dat>>3) & 0x01;//lcd7
}

//========Ham gui lenh========//
void LCD_Sendcommand(unsigned char command)
{
 
   LCD_RS=0; //chon thanh ghi lenh
   LCD_RW=0; //cho phep ghi
   LCD_Send_4bit(command>>4); //gui 4 bit cao
   LCD_enable();
   LCD_Send_4bit(command);    //gui 4 bit thap
   LCD_enable();  
}
void LCD_Senddat(unsigned char dat)
{
 
   LCD_RS=1; //chon thanh ghi dat
   LCD_RW=0; //cho phep ghi
   LCD_Send_4bit(dat>>4); //gui 4 bit cao
   LCD_enable();
   LCD_Send_4bit(dat);    //gui 4 bit thap
   LCD_enable();
}
//========Ham khoi tao LCD============//
void LCD_inits(void)
{
   
   LCD_Send_4bit(0x00);
   delay_ms(20); //cho cho LCD hoat dong
   LCD_Sendcommand(0x03);//
   LCD_Sendcommand(0x02); //tro ve dau dong
   LCD_Sendcommand( 0x28 ); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
   LCD_Sendcommand( 0x0c); // cho phep hien thi man hinh
   LCD_Sendcommand( 0x06 ); // tang ID, khong dich khung hinh
   clear(); 
   }
//=========void thiet lap vi tri======//
void LCD_gotoxy(unsigned char x , unsigned char y)

{
  unsigned char address;
  if(y==1)
  address = (0x80+x);
  else
  address = (0xC0+x);
  delay_ms(1);
  LCD_Sendcommand(address);
  delay_ms(1);
}
//===Ham xoa man hinh===//
void clear(void)
{
  LCD_Sendcommand(0x01);  //xoa man hinh
  delay_ms(10);
}

//=======Ham gui 1 ky tu len LCD==//
void LCD_Putchar(unsigned char text)
{
   LCD_Senddat(text);
}
//=======Ham gui 1 chuoi ky tu=====//
void LCD_PutsChar(char *s)
{
   while(*s)
   {
      LCD_Putchar(*s);
      s++;
   }
}
