#include <Arduino.h>
#include <LinkedList.h>

#define odd 2
#define Even 3

#define rst 9
#define sda 10
#define mosi 11
#define miso 12
#define sck 13

#define CommandReg 0x01

class MFRC{
  public:
    MFRC();
    LinkedList<byte> SPIRead(LinkedList<byte> addresses, long delayMicro);
    void SPIWrite(LinkedList<byte> addressData, long delayMicro);
    bool readSendBit(uint8_t MOSI, bool input, uint8_t MISO, uint8_t sclk, long delayMicro);
    LinkedList<bool> byteBool(byte b);
    byte boolByte(LinkedList<bool> bs, uint8_t MSBLSB);
    byte addressByte(byte addr, bool readWrite);
};
