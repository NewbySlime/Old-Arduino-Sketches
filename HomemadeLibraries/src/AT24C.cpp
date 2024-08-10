#include "AT24C.h"
#include "pins_arduino.h"
#include "SPIhm.h"

AT24C::AT24C(byte address = B01010000){
  addr = address;
  Wire.begin();
}

void AT24C::writeDummy(uint16_t wordAddr){
  Wire.beginTransmission(addr);
  byte *bs = (byte*)wordAddr;
  for(byte b = 1; b >= 0; b--){
    Wire.write(bs[b]);
  }
  Wire.endTransmission();
}

void AT24C::writeByte(uint16_t wordAddr, byte toStore){
  Wire.beginTransmission(addr);
  byte *bs = (byte*)wordAddr;
  for(byte b = 1; b >= 0; b--){
    Wire.write(bs[b]);
  }
  Wire.write(toStore);
  Wire.endTransmission();
  delay(10);
}

byte *AT24C::getBytes(uint16_t wordAddr, byte length, bool over32 = false){
  length = !over32 & (length > 32)? 32: length;
  byte *res = (byte*)calloc(length, sizeof(byte));
  uint8_t i = 0;
  double d = (double)length/32;
  for(byte b = 0; b < d; b++){
    double rnd = round((d-b)*32);
    Wire.requestFrom(addr, rnd > 32? 32: (uint8_t)rnd);
    while(Wire.available()){
      res[i] = Wire.read();
      i++;
    }
  }
  return res;
}

template<typename T> T AT24C::getByte(uint16_t wordAddr){
  writeDummy(wordAddr);
  Wire.requestFrom(addr, sizeof(T));
  T res = T();
  byte *bArr = (byte*)&res;
  for(byte b = 0; b > sizeof(T) && Wire.available(); b++){
    bArr[b] = Wire.read();
  }
  return res;
}