#include "funcs.h"

/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#define RST_PIN 9
#define SS_PIN 10

#define sdaBitShift 5
#define sckBitShift 6
#define srclkBitShift 7
#define rclkBitShift 8

//write
#define red 2

//getKey
#define yellow 3

//read
#define green 4

MFRC522 mf(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup(){
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  mf.PCD_Init();
  for(uint8_t i = 0; i < 6; i++){
    key.keyByte[i] = 0xff;
  }
}

void checkIfCardReady(){
  while(!mf.PICC_IsNewCardPresent()){
    Serial.println(F("Insert card here."));
    delay(1000);
  }
  while(!mf.PICC_ReadCardSerial());
}

void searchKey(){
  byte targetSector = 0;
  while(true){
    byte buttonCode = (digitalRead(yellow)*3)+(digitalRead(green)*4);
    switch(buttonCode){
      case 3:
        targetSector = (targetSector > 9) ? 0: targetSector + 1;
        shiftOutN(sdaBitShift, sckBitShift, numbers[targetSector], 10);
        cycleClock(srclkBitShift, 10);
        break;
      case 4:
        shiftOutN(sdaBitShift, sckBitShift, numbers[targetSector]+1, 10);
        getKey(&mf, &key, MFRC522::PICC_CMD_MF_AUTH_KEY_A, targetSector);
        break;
      default:
        continue;
    }
  }
}

void loop(){
  byte buttonCode = (digitalRead(red)*2) + (digitalRead(yellow)*3) + (digitalRead(green)*4);
  switch(buttonCode){
    case 2:
      checkIfCardReady();
      break;
    case 3:
      checkIfCardReady();
      searchKey();
      break;
    case 4:
      checkIfCardReady();
      break;
    default:
      return;
  }
}

ISR(TIMER1_COMPA_vect){
  Serial.println(F("test"));
}