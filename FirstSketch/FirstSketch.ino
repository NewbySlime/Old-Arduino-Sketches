void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT); pinMode(2, OUTPUT); pinMode(3, OUTPUT); pinMode(13, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
    for(int i = 1; i < 4; i++){
      digitalWrite(i,1);
      delay(100);
    }
    for(int i = 1; i < 4; i++){
      digitalWrite(i,0);
      delay(100);
    }
    delay(1000);
  
}
