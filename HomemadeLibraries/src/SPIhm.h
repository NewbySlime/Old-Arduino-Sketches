#include "Arduino.h"

void sendByte(byte sclk, byte sda, byte toSend, bool msborlsb);
byte getByte(byte sclk, byte sda, bool msborlsb);
