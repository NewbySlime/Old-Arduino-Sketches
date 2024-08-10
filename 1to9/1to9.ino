int one[] = {LOW,HIGH,HIGH,LOW,LOW,LOW,LOW,
  HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH,
  HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,
  LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH,
  HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH,
  HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,
  HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,
  HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,
  HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH};

int manyPins = 7;
int maxNums = 7*9;
int n = 7;

void setup() {
  // put your setup code here, to run once:
  for(int i = 1; i <= manyPins; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int o = 1;
  for(int i = n - 7; i < n; i++){
    digitalWrite(o, one[i]);
    delay(10);
    o++;
  }
  if(n >= maxNums) n = 0;
  n += 7;
  delay(930);
}
