#include <TimerOne.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t TimeDisp1[] = {0x00,0x00,0x00,0x00};
int8_t TimeDisp2[] = {0x00,0x00,0x00,0x00};
int8_t StopwatchDisp[] = {0x00,0x00,0x00,0x00};
int8_t AlarmDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Point = 0;
unsigned char mode = 1;
unsigned char count = 0;
unsigned char Update1;
unsigned char Update2;
unsigned char Update3;
unsigned char microsecond_10 = 0;
unsigned char second = 0;
unsigned char minute = 0;
unsigned char hour = 13;
unsigned char _microsecond_10 = 0;
unsigned char _second = 0;
unsigned char _microsecond2_10 = 0;
unsigned char _second2 = 0;
unsigned char _minute = 0;
unsigned char _hour = 0;
unsigned char Modebutton = 1;
unsigned char Timebutton = 0;
unsigned char Stopwatchbutton1 = 0;
unsigned char Stopwatchbutton2 = 0;
unsigned char Alarmbutton1 = 0;
unsigned char Alarmbutton2 = 0;
unsigned char Alarmon = 0;
unsigned char Alarmcheck = 0;
const byte buttonPin1 = 5;
const byte buttonPin2 = 6;
const byte buttonPin3 = 7;
const byte ledPin1 = 12;
const byte ledPin2 = 13;
int lastButton1;
int currentButton1;
int lastButton2;
int currentButton2;
int lastButton3;
int currentButton3;

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK,DIO);

void setup()
{
  tm1637.set();
  tm1637.init();
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  currentButton1 = digitalRead(buttonPin1);
  currentButton2 = digitalRead(buttonPin2);
  currentButton3 = digitalRead(buttonPin3);
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
}
void loop()
{
  lastButton1    = currentButton1;
  currentButton1 = digitalRead(buttonPin1);
  if(lastButton1 == HIGH && currentButton1 == LOW) {
    mode ++;
    if(mode == 4)
    {
      mode = 1;
    }
  }
  lastButton2    = currentButton2;
  currentButton2 = digitalRead(buttonPin2);
  if(lastButton2 == HIGH && currentButton2 == LOW) {
    if(mode == 1){
      Timebutton = !Timebutton;
    }
    else if(mode == 2){
      Stopwatchbutton1 = !Stopwatchbutton1;
      Stopwatchbutton2 = 0;
    }
    else if(mode == 3){
      Alarmbutton1 = !Alarmbutton1;
    }
  }
  lastButton3    = currentButton3;
  currentButton3 = digitalRead(buttonPin3);
  if(lastButton3 == HIGH && currentButton3 == LOW) {
    if(mode == 1){
      Alarmon = !Alarmon;
      Alarmcheck = 0;
      if(minute == _minute && hour == _hour){
        Alarmcheck = 1;
      }
    }
    else if(mode == 2){
      Stopwatchbutton2 = 1;
      Stopwatchbutton1 = 0;
    }
    else if(mode == 3){
      Alarmbutton2 = 1;
    }
  }
  
  switch(mode)
  {
    case 1:
      if(Update1 == ON)
      {
        TimeUpdate();
        if(Timebutton == 0)
        {
          tm1637.display(TimeDisp1);
        }
        else if(Timebutton == 1)
        {
          tm1637.display(TimeDisp2);
        }
      }
      break;
    case 2:
      if(Update2 == ON)
      {
        if(Stopwatchbutton1 == 0)
        {
          _microsecond_10 = _microsecond2_10;
          _second = _second2;
          count = 0;
        }
        else if(Stopwatchbutton1 == 1)
        {
          _microsecond2_10 = _microsecond_10;
          _second2 = _second;
          count = 1;
        }
        if(Stopwatchbutton2 == 1)
        {
          _microsecond_10 = 0;
          _second = 0;
          _microsecond2_10 = 0;
          _second2 = 0;
        }
        StopwatchUpdate();
        tm1637.display(StopwatchDisp);
      }
      break;
    case 3:
      if(Update3 == ON)
      {
        if(Alarmbutton1 == 0)
        {
          if(Alarmbutton2 == 1){
            _minute ++;
            if(_minute == 60)_minute = 0;
            Alarmbutton2 = 0;
          }
        }
        else if(Alarmbutton1 == 1)
        {
           if(Alarmbutton2 == 1){
            _hour ++;
            if(_hour == 24)_hour = 0;
            Alarmbutton2 = 0;
          }
        }
        AlarmUpdate();
        tm1637.display(AlarmDisp);
      }
      break;
    default:break;
  }

  if(Alarmon == 1)
  {
    digitalWrite(ledPin1, HIGH);
    if(minute == _minute && hour == _hour && Alarmcheck == 0)
    {
      digitalWrite(ledPin2, HIGH);
      delay(500);
      digitalWrite(ledPin2, LOW);
      delay(500);
    }
    else {
      digitalWrite(ledPin2, LOW);
    }
  }
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }
}
void TimingISR()
{
  microsecond_10 ++;
  Update1 = ON;
  if(microsecond_10 == 100){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    microsecond_10 = 0;
  }
  if(count == 1){
    _microsecond_10 ++;
  }
  Update2 = ON;
  if(_microsecond_10 == 100){
       _second ++;
       if(_second == 60)
       {
         _second = 0;
       }
         _microsecond_10 = 0;
       }
  Update3 = ON;
  Point ++;
  if(Point == 50){
    ClockPoint = (~ClockPoint) & 0x01;
    Point = 0;
  }
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);
  TimeDisp1[0] = hour / 10;
  TimeDisp1[1] = hour % 10;
  TimeDisp1[2] = minute / 10;;
  TimeDisp1[3] = minute % 10;
  TimeDisp2[0] = minute / 10;
  TimeDisp2[1] = minute % 10;
  TimeDisp2[2] = second / 10;
  TimeDisp2[3] = second % 10;
  Update1 = OFF;
}
void StopwatchUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);
  StopwatchDisp[0] = _second / 10;
  StopwatchDisp[1] = _second % 10;
  StopwatchDisp[2] = _microsecond_10 / 10;
  StopwatchDisp[3] = _microsecond_10 % 10;
  Update2 = OFF;
}
void AlarmUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);
  AlarmDisp[0] = _hour / 10;
  AlarmDisp[1] = _hour % 10;
  AlarmDisp[2] = _minute / 10;;
  AlarmDisp[3] = _minute % 10;
  Update3 = OFF;
}
