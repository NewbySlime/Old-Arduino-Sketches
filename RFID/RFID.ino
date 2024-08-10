#include "RFIDC.h"
//int SCK, int MOSI, int MISO, int RST, int NSS
RFID rf(13, 11, 12, 9, 10);

void setup(){
  Serial.begin(9600);
  rf.CmdReg(false, true, false, CmdGenRandID);
  byte res = rf.SendData(true, FIFODataReg, 0);
  Serial.println(res);
}

void loop(){
}
