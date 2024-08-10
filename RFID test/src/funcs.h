#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

//g to a, at bit 0 for dot
const byte numbers[10] = {B01111110, B01100000, B10110110, B10011110, B11001100, B11011010, B11111010, B00001110, B11111110, B11011110};

void dump_byte_array(byte *buffer, byte bufferSize);
byte getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, int n, MFRC522::PICC_Command piccmd);
void getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, MFRC522::PICC_Command piccmd);

struct CardDetailPointers{
  MFRC522::MIFARE_Key *keyA, *keyB;
  byte currentSector, *containingBlock;
};

void writeEntireSector(MFRC522 *mf, CardDetailPointers targetCard, byte sector);

void getBlock(MFRC522 *mf, CardDetailPointers card);

void changeDigit(byte sda, byte sck, byte digitByte);

void shiftOutN(byte sda, byte sck, byte b, long micro);
void cycleClock(byte sck, long delayMicro);

byte getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, int n, MFRC522::PICC_Command piccmd, byte sector);
void getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, MFRC522::PICC_Command piccm, byte sector);