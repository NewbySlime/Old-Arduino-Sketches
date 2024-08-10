#include "SPIhm.h"

const int delayMicro = 10;

void sendByte(byte sclk, byte sda, byte toSend, bool msborlsb){
  digitalWrite(sclk, LOW);
  for(int i = msborlsb ? 7 : 0 ; i < 8 && i >= 0; i += msborlsb? -1: 1){
    bool b = (1 << i) == (toSend & (1 << i));
    Serial.println(b);
    digitalWrite(sda, 1 << i == toSend & (1 << i));
    digitalWrite(sclk, HIGH);
    delayMicroseconds(delayMicro);
    digitalWrite(sclk, LOW);
    delayMicroseconds(delayMicro);
  }
  Serial.println(F("Done"));
}

byte getByte(byte sclk, byte sda, bool msborlsb){
  digitalWrite(sda, LOW);
  pinMode(sda, INPUT);
  digitalWrite(sclk, LOW);
  byte res = 0;
  for(int i = msborlsb? 7: 0; i < 8 && i >= 0; i += msborlsb? -1: 1){
    digitalWrite(sclk, HIGH);
    delayMicroseconds(delayMicro);
    Serial.println(digitalRead(sda));
    //res |= digitalRead(sda) << i;
    digitalWrite(sclk, LOW);
    delayMicroseconds(delayMicro);
  }
  pinMode(sda, OUTPUT);
  return res;
}