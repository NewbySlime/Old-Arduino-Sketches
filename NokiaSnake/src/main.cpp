#include <Arduino.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include "Snake.h"

#define CLKPin 8
#define DINPin 9
#define DCPin 11
#define CSPin 12
#define RSTPin 13

#define xAxisPin A2
#define yAxisPin A3
float threshold = 0.3;
int JoyStickLow = (int)1024*threshold;
int JoyStickHigh = (int)1024*(1- threshold);
const float delaySnake = 1;
int delayms = 500;

Adafruit_PCD8544 pcd(CLKPin, DINPin, DCPin, CSPin, RSTPin);
int PixelsPerGrid = 4;
Snake snk((int)pcd.width()/PixelsPerGrid, (int)pcd.height()/PixelsPerGrid, PixelsPerGrid, delayms);

void setup() {
  //Timer
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TIMSK1 |= (1<<OCIE1A);
  TCCR1A |= (1<<COM1A0);
  TCCR1B |= (1<<CS12) | (1<<WGM12);
  OCR1A = 0xFFFF*delaySnake;
  TCCR0A = 0;
  TCCR0B |= (1<<CS01) | (1<<CS00);
  TIMSK0 = 0;
  //TIMSK0 |= (1<<TOIE0);
  Serial.begin(9600);
  //Serial.println("front");
  pcd.begin();
  pcd.writeFillRect(3,4,40,40,BLACK);
  pcd.display();
  delay(1000);
  pcd.clearDisplay();
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  snk.Start();
  //pinMode(A1, INPUT);
}

void loop() {
  //Serial.println(analogRead(A1));
  int xar = analogRead(xAxisPin), yar = analogRead(yAxisPin);
  int xarb = abs(xar-512), yarb = abs(yar-512);
  //1: x axis, -1: y axis
  bool b = xarb<yarb;
  int xy = (abs(xarb-yarb) > 1024*0.2) * ((b * -1) + (!b * 1));
  if(xy != 0){
    int A = (b * yar) + (!b * xar);
    bool u = A > JoyStickHigh, d = A < JoyStickLow;
    int dir = (u * 1) + (!u * ((d * 2)+(!d * -2)));
    dir += xy;
    //Serial.println(dir);
    snk.NextMove(dir);
  }
}

ISR(TIMER1_COMPA_vect){
  //noInterrupts();
  //update the snake class and update the display
  snk.Update();
  Serial.println(snk.getString());
  //Serial.println(millis());
  //snk.Update();
  //snk.SendToLCD(&pcd);
  //interrupts();
}