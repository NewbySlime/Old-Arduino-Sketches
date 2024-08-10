#include "Arduino.h"

#define LSB 7
#define MSB 0

class I2C{
  public:
    I2C(uint8_t SDA, uint8_t SCLK);
    void sendData(byte Command, byte Data, uint8_t MSBLSB, long delayus), sendData(bool * arrC, bool * arrD, long delayus);
    byte getData(byte Command, byte Data);
    void pulseO(bool * bits, long delayus), pulseO(byte b, uint8_t MSBLSB, long delayus);
    byte pulseI(byte CommandAddress, uint8_t MSBLSB, long delayus), pulseI(bool * arrCA, uint8_t MSBLSB, long delayus);

  private:
    uint8_t SDAPin, SCLKPin;
    bool * getArray(byte b, uint8_t MSBLSB);
    byte getByte(bool * Arr);
};