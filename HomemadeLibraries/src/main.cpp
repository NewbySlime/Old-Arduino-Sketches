#include "AT24C.h"
#include "math.h"

void setup() {
  Serial.begin(9600);
  AT24C at;
  at.writeByte(10, (byte)'b');
  byte b = at.getByte<byte>(10);
  Serial.println((char)b);
}


void loop() {
  // put your main code here, to run repeatedly:
}