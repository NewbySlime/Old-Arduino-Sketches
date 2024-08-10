#include "DS1302.h"

DS1302::DS1302(uint8_t CLK, uint8_t DAT, uint8_t RST) : I2C(DAT, CLK){
  RSTPin = RST;
}