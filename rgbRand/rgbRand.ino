int write[] = {A0, A1, A2};


void setup(){
    for(int i : write){
        pinMode(i, OUTPUT);
    }
    Serial.begin(9600);
}

int value = 0;
void loop(){
    Serial.println(value);
    //analogWrite(write[1], value);
    for(int i : write){
      delay(500);
      pinMode(i, value);
    }
    value++;
}
