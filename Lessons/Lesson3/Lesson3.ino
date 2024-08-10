int pins = 3;
void setup() {
  // put your setup code here, to run once:
  for(int i = 1; i <= pins; i++){
    pinMode(i, OUTPUT);
  }
}

int time[] = {10, 1, 5};
void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 3; i++){
    digitalWrite(i+1, HIGH);
    delay(time[i] * 1000);
    digitalWrite(i+1, LOW);
    delay(50);
  }
}
