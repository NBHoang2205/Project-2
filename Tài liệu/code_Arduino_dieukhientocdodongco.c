#include<TimerOne.h>

#define PWM 5
#define DIR1 7
#define DIR2 8
//#define Kp 0.3
//#define Kd 0.001
//#define Ki 0.05
#define Kp 0.01
#define Kd 0.0002
#define Ki 0.04

double tam;
float T,xung;
float tocdo, tocdodat;
double E,E1,E2;
double alpha, beta, gamma;
double Output, LastOutput;

void setup(){
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(PWM,OUTPUT); 
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
  tocdodat=1000; tocdo=0;
  E=0; E1=0; E2=0;
  Output = 0; LastOutput = 0;
  T=0.01;
  Serial.begin(9600);
  attachInterrupt(0,Demxung,FALLING);
  Timer1.initialize(10000);  //don vi us
  Timer1.attachInterrupt(PID);
}

void loop(){

}
void Demxung()
{
  if(digitalRead(3) == LOW)
  xung++;
  else
  xung--;
}
void PID()
{ 
  tocdo=((xung/200)*(1/T)*60);
  xung=0;
  E = tocdodat - tocdo;
  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = T*T*Ki - 4*Kd - 2*T*Kp;
  gamma = 2*Kd;
  Output = (alpha*E + beta*E1 + gamma*E2 + 2*T*LastOutput)/(2*T);
  LastOutput = Output;

  E2=E1;
  E1=E;

    digitalWrite(DIR1,LOW);
    digitalWrite(DIR2,HIGH);
    analogWrite(PWM,abs(Output));
     Serial.println(tocdo);
}