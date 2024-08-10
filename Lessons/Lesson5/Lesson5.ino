int ledPin = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 1000; i > 0; i -= 5){
    analogWrite(ledPin, i);
    delay(100);
  }
}
