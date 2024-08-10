#include "4DigitC.h"
#include "RTCC.h"
int pins[] = {12, 10, 8}; // res/ce, dat/io, clk
int IOPin = pins[1];
int SCLK = pins[2];
int Pins4D[] = {37, 29, 35, 25, 36, 34, 28, 26, 27, 30, 33, 38};
int PinsR[] = {8,10,12};

RTC rtc;
Digit dgt;
void setup(){
	rtc = RTC(PinsR);
  //rtc.SetMinute(byte(88)); 58
  //rtc.SetHour(15, true);
}

void loop(){ 
  double m = rtc.GetTimeHM();
  dgt.setNumber(m);
  while(micros() % 60000 > 1000)
  dgt.Refresh();
}
