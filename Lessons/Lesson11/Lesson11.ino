
int photoresistorPin = A0;
int passBuzzer = 11;
void setup(){
    pinMode(photoresistorPin, INPUT);
    pinMode(passBuzzer, OUTPUT);
}

void loop(){
    int in = analogRead(photoresistorPin);
    tone(passBuzzer, 200 + in / 4, 500);
}