Nokia::Nokia(){
  
}

Nokia::Nokia(int Pins[]){
    Nokia::RST = Pins[0]; digitalWrite(Nokia::RST, LOW);
    Nokia::CE = Pins[1]; digitalWrite(Nokia::CE, HIGH);
    Nokia::DC = Pins[2];
    Nokia::Din = Pins[3];
    Nokia::SCLK = Pins[4];
}

void Nokia::SendData(byte Input, uint8_t DCin){
    digitalWrite(Nokia::CE, LOW);
    digitalWrite(Nokia::DC, DCin); 
    shiftOut(Nokia::Din, Nokia::SCLK, MSBFIRST, Input);
    digitalWrite(Nokia::CE, HIGH);
}

void Nokia::Reset(){
    digitalWrite(Nokia::RST, LOW);
    delayMicroseconds(1500);
    digitalWrite(Nokia::RST, HIGH);
}

void Nokia::init(){
    Nokia::Reset();
}
