#include <Arduino.h>

#define SER 8
#define OE 9
#define RCLK 11
#define SRCLK 12
#define SRCLR 13

#define trig A5
#define echo A4

#define button 2

//bit3 is for the dot
const PROGMEM byte bitsPM[] = {B11101110, B01100000, B11001101, B11101001, B01100011, B10101011, B10101111, B11100000, B11101111, B11101011};
const int charOffset = 48;
// D1 to D4
const int digitPin[] = {3,4,6,7};
byte *digit4;
const int speedSound = 343;
//const int bit16Max = 65535;
float delays = 0.01;

void shiftO(uint8_t dataPin, uint8_t clockPin, uint8_t MSBLSB, byte bits, unsigned long delayS, boolean delayMSUS){
  int i = MSBLSB * 7,
  n = 7,
  inc = (MSBLSB * -2) + 1;
  uint8_t bitsHL[8];
  //assignments always from MSB but the array to access is always dependant
  while(i < 8 && i >= 0){
    int nbit = (int)(pow(2, n)+0.1);
    bitsHL[7-i] = ((bits - nbit) >= 0) * HIGH;
    bits -= nbit * bitsHL[7-i];
    n--;
    i += inc;
  }
  for(int o = 0; o < 8; o++){
    digitalWrite(dataPin, bitsHL[o]);
    digitalWrite(clockPin, HIGH);
    if(delayMSUS) delay(delayS);
    else delayMicroseconds(delayS);
    digitalWrite(clockPin, LOW);
    if(delayMSUS) delay(delayS);
    else delayMicroseconds(delayS);
  }
}

void send(byte bits){
  digitalWrite(SRCLR, HIGH);
  digitalWrite(OE, LOW);
  shiftO(SER, SRCLK, LSBFIRST, bits, 10, false);
  digitalWrite(RCLK, HIGH);
  delayMicroseconds(10);
  digitalWrite(RCLK, LOW);
}

void updateDisplay(){
  for(int i = 0; i < 4; i++){
    if(digit4[i] == 0) continue;
    send(digit4[i]);
    digitalWrite(digitPin[3-i], LOW);
    delay(1);
    digitalWrite(digitPin[3-i], HIGH);
  }
}

double Range(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int usSec = pulseInLong(echo, HIGH, 10000000);
  Serial.println(usSec);
  return (double)usSec*speedSound/(2*1000000);
}

void to4Digit(String Num){
  int i = 3;
  byte dgt[4];
  for(int n = 0; n < 4; n++) dgt[n] = 0;
  for(int o = Num.length() - 1; o >= 0 && i >= 0; o--) {
    char c = Num.charAt(o);
    if(c == '.'){
      dgt[i] |= (1<<4);
    }else{
      dgt[i] |= pgm_read_byte_near(bitsPM + (int(c) - charOffset));
      i--;
    }
  }
  while(i >= 0){
    dgt[i] = 0;
    i--;
  }
  digit4 = dgt;
}


void setup(){
  //note: 64 prescaler is normal
  Serial.begin(9600);
  noInterrupts();
  TCCR0A = 0;
  TCCR0B = 0;
  TIMSK0 = 0;
  TIMSK0 = (1<<TOIE0);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TIMSK1 |= (1<<OCIE1A);
  TCCR1B |= (1<<CS12) | (1<<WGM12);
  OCR1A = 0xFFFF*delays;
  interrupts();
  int pins[] = {OE, RCLK, SER, SRCLK, SRCLR, trig};
  int n = sizeof(pins)/sizeof(pins[0]);
  digitalWrite(SRCLR, LOW);
  delay(1);
  digitalWrite(SRCLR, HIGH);
  pinMode(echo, INPUT);
  pinMode(button, INPUT);
  for(int i = 0; i < 4; i++){
    pinMode(digitPin[i], OUTPUT);
    digitalWrite(digitPin[i], HIGH);
  }
  for(int i = 0; i < n; i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop(){
  if(digitalRead(button)){
    TIMSK1 &= !(1<<OCIE1A);
    to4Digit(String(Range()));
    TIMSK1 |= (1<<OCIE1A);
  }
}

ISR(TIMER1_COMPA_vect){
  updateDisplay();
}