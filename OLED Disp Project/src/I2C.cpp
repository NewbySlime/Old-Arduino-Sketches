#include "I2C.h"

I2C::I2C(uint8_t S, uint8_t SC){
  SDAPin = S;
  SCLKPin = SC;
}

void I2C::pulseO(bool * bits, long delayus){
  for(int i = 0; i < (sizeof(bits)/sizeof(bits[0])); i++){
    digitalWrite(SDAPin, bits[i]);
    digitalWrite(SCLKPin, HIGH);
    delayMicroseconds(delayus);
    digitalWrite(SCLKPin, LOW);
    delayMicroseconds(delayus);
  }
}

void I2C::pulseO(byte b, uint8_t MSBLSB, long delayus){
  pulseO(getArray(b, MSBLSB), delayus);
}

byte I2C::pulseI(bool * arrCA, uint8_t MSBLSB, long delayus){
  pulseO(arrCA, delayus);
  for(int i = 0; i < (sizeof(arrCA)/sizeof(arrCA[0]));i++){
    digitalWrite(SCLKPin, HIGH);
    delayMicroseconds(delayus);
    arrCA[abs(MSBLSB - i)] = digitalRead(SDAPin);
    digitalWrite(SCLKPin, LOW);
    delayMicroseconds(delayus);
  }
  return getByte(arrCA);
}

byte I2C::pulseI(byte CA, uint8_t MSBLSB, long delayus){
  return pulseI(getArray(CA, MSBLSB), MSBLSB, delayus);
}

void I2C::sendData(bool * arrC, bool * arrD, long delayus){
  pulseO(arrC, delayus);
  pulseO(arrD, delayus);
}

void I2C::sendData(byte Command, byte Data, uint8_t MSBLSB, long delayus){
  sendData(getArray(Command, MSBLSB), getArray(Data, MSBLSB), delayus);
}

bool * I2C::getArray(byte b, uint8_t MSBLSB){
  bool res[8];
  //TODO: add some prevention when MSBLSB isn't the same as the defined one
  for(int i = 0; i < 8; i++){
    int p = pow(2, 7-i);
    bool b1 = p < b;
    res[abs(MSBLSB - i)] = b1;
    b = (b1 * (b - p)) + (!b1 * b);
  }
  return res;
}

byte getByte(bool * arr){
  uint8_t res = 0;
  for(int i = 8; i >= 0; i--) res += pow(2, i);
  return byte(res);
}