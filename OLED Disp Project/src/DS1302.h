#include <Arduino.h>
#include "I2C.h"

class DS1302 : I2C{
  public:
    DS1302(uint8_t CLK, uint8_t DAT, uint8_t RST);

  private:
   uint8_t RSTPin;
};