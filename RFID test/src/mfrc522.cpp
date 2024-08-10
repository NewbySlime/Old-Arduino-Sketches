#include <mfrc522.h>


MFRC::MFRC(){
  pinMode(sck, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(mosi, OUTPUT);
  pinMode(miso, INPUT);
  pinMode(rst, OUTPUT);
  digitalWrite(rst, HIGH);
}

LinkedList<byte> MFRC::SPIRead(LinkedList<byte> addresses, long delayMicro){
  digitalWrite(sda, HIGH);
  LinkedList<byte> adrrres(addresses.size()-1, 0);
  for(int i = 0; i < addresses.size(); i++){
    LinkedList<bool> bits = byteBool(addresses[i]);
    int n = bits.size()-1, nn = -1;
    bool oddPar = true;
    LinkedList<bool> resb(bits.size(), false);
    //this caught in a loop
    for(int o = 0; o < bits.size(); o++){
  //Serial.println("test");
      resb[n] = readSendBit(mosi, bits[n], miso, sck, delayMicro);
      Serial.println(resb[n]);
      if(resb[n])
        oddPar = !oddPar;
      n += nn;
    }
    bool oddParB = readSendBit(mosi, LOW, miso, sck, delayMicro);
    if(i > 0)
      adrrres[i] = boolByte(resb, MSBFIRST);
    /*if(oddPar == oddParB)
      i--;*/
  }
  digitalWrite(sda, LOW);
  return adrrres;
}

void MFRC::SPIWrite(LinkedList<byte> addressData, long delayMicro){
  digitalWrite(sda, HIGH);
  for(int i = 0; i < addressData.size(); i++){
    LinkedList<bool> bs = byteBool(addressData[i]);
    for(int o = 0; i < bs.size(); o++){
      readSendBit(mosi, bs[o], miso, sck, delayMicro);
    }
  }
  digitalWrite(sda, LOW);
}

bool MFRC::readSendBit(uint8_t MOSI, bool input, uint8_t MISO, uint8_t sclk, long delayMicro){
  digitalWrite(sclk, LOW);
  digitalWrite(MOSI, input);
  digitalWrite(sclk, HIGH);
  bool b = digitalRead(MISO);
  delayMicroseconds(delayMicro);
  digitalWrite(sclk, LOW);
  delayMicroseconds(delayMicro);
  return b;
}

LinkedList<bool> MFRC::byteBool(byte b){
  LinkedList<bool> arr(8, false);
  for(int i = 7; i >= 0; i--){
    int p = (int)pow(2,i);
    arr[i] = (p <= b);
    if(arr[i]) b-=p;
  }
  return arr;
}

byte MFRC::boolByte(LinkedList<bool> bs, uint8_t MSBLSB){
  int n, nn;
  byte res;
  switch(MSBLSB){
    case MSBFIRST:
      n = bs.size()-1;
      nn = -1;
      break;
    case LSBFIRST:
      n = 0;
      nn = 1;
  }
  for(int i = 0; i < bs.size(); i++){
    res += (pow(2, n) * bs[n]);
    n += nn;
  }
  return res;
}

byte MFRC::addressByte(byte addr, bool readWrite){
  addr = addr<<1;
  addr |= (B10000000 * readWrite);
  addr &= B11111110;
  return addr;
}