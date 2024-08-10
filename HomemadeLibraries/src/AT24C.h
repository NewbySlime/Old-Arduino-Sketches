#include "Arduino.h"
#include "Wire.h"

class AT24C{
  public:
    AT24C(byte address = B01010000);
    void writeByte(uint16_t wordAddr, byte b);
    
    //must call free after using the byte returned
    byte *getBytes(uint16_t wordAddr, byte length, bool over32 = false);
    template<typename T> T getByte(uint16_t wordAddr);
  
  private:
    void writeDummy(uint16_t wordAddr);
    byte addr;
};