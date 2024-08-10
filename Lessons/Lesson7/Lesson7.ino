int buttons[] = {1,2,3};
int leds[] = {7,8,9};
int resetButton = 5;
bool noLoop = false;

void setup(){
    for(int i = 0; i < 3; i++){
        pinMode(buttons[i], INPUT); pinMode(leds[i], OUTPUT);
    }
    digitalWrite(leds[1], HIGH);
    delay(1000);
    digitalWrite(leds[1], LOW);
    pinMode(resetButton, INPUT);
}

int one, two,three;
void loop(){
    if(!noLoop){
        for(int i = 0; i < 3; i++){
            if(digitalRead(buttons[i]) == HIGH){noLoop = true; digitalWrite(leds[i], HIGH);}
        }
    }
    if(digitalRead(resetButton) == HIGH){
        noLoop = false;
        reset();
    }
}

void reset(){
    int State = HIGH;
    for(int i = 0; i < 2; i++){
        for(int o = 0; o < 3; o++){
            digitalWrite(leds[o], State);
        }
        State = LOW;
        delay(200);
    }
}