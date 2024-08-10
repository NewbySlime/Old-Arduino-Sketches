#include <funcs.h>

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

byte getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, int n, MFRC522::PICC_Command piccmd, byte sector){
  if(n >= 0){
    byte keyBlock = sector*4-1;
    for(uint16_t i = 0; i < 256; i++){
      if(getKey(mf, akey, n-1, piccmd, sector) == -1)
        return -1;
      MFRC522::StatusCode status = mf->PCD_Authenticate(piccmd, keyBlock, akey, &mf->uid);
      if(status == MFRC522::STATUS_OK){
        Serial.println(F("The key has found, the key is: "));
        dump_byte_array(akey->keyByte, 6);
        Serial.println();
        return -1;
      }
      akey->keyByte[n] = i;
      while(!mf->PICC_IsNewCardPresent())delay(1);
      while(!mf->PICC_ReadCardSerial())delay(1);
      dump_byte_array(akey->keyByte, 6);
      Serial.println();
    }
  }
}

void getKey(MFRC522 *mf, MFRC522::MIFARE_Key *akey, MFRC522::PICC_Command piccmd, byte sector){
  getKey(mf, akey, 5, piccmd, sector);
}

//except blockAddr #3 #7 and so on, where the key is in there
void writeEntireSector(MFRC522 *mf, CardDetailPointers fromCard, CardDetailPointers targetCard, byte sector){
  for(int i = 4*(sector-1); i < sector*4; i++){
    
  }
}

void getBlock(MFRC522 *mf, CardDetailPointers card){
  static byte resByte[48];
  byte buffer[16];
  byte bufferSize = 16;
  while(!mf->PICC_ReadCardSerial());
  mf->PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, card.currentSector*4-1, card.keyA, &mf->uid);
  mf->MIFARE_Read(card.currentSector, buffer, &bufferSize);
}

void changeDigit(byte sda, byte sck, byte digit){
  shiftOutN(sda, sck, numbers[digit], 10);
}

void shiftOutN(byte sda, byte sck, byte b, long delayMicro){
  digitalWrite(sck, LOW);
  for(int i = 7; i >= 0; i--){
    digitalWrite(sck, HIGH);
    uint8_t p = pow(2, i);
    bool bb = p <= b;
    b -= p * bb;
    digitalWrite(sda, bb);
    delayMicroseconds(delayMicro);
    digitalWrite(sck, LOW);
    delayMicroseconds(delayMicro);
  }
}

void cycleClock(byte sck, long delayMicro){
  digitalWrite(sck, HIGH);
  delayMicroseconds(delayMicro);
  digitalWrite(sck, LOW);
  delayMicroseconds(delayMicro);
}