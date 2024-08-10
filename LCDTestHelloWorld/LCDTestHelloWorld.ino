int RS = 3;
int RW = 4;
int E  = 5;
int MaxDB = 13;
int MinDB = 6;
String HelloWorld[] = {"01001000", "01100101", "01101100", "01101100", "01101111", "00010000", "01010111", "01101111", "01110010", "01101100", "01100100"};

void setup(){
    for(int i = RS; i<=MaxDB; i++){
        pinMode(i, OUTPUT);
    }
    for(int i = 0; i < sizeof(HelloWorld); i++){
        String CurString = HelloWorld[i];
        for(int o = 0; o < CurString.length(); o++){
            if(CurString.charAt(o) == '1'){
                digitalWrite(CurString.length() - o, HIGH);
            }else{
                digitalWrite(CurString.length() - o, LOW);
            }
            
        }
    }

    /*
    -display on
    -function set
    -write data
    -shift cursor
    */

    {
    DisplayOnOff(HIGH, HIGH, LOW);
    FunctionSet(HIGH, LOW, HIGH);
    for(int i = 0; i < sizeof(HelloWorld); i++){
        String newString = HelloWorld[i];
        int StringLenght = newString.length();
        int BitArray[8];
        for(int o = 0; o < StringLenght; o++){
            if(newString.charAt(o) == '1'){
                BitArray[o] = HIGH;
            }else{
                BitArray[o] = LOW;
            }
        }
        WriteReadData(LOW, BitArray);
        CursorOrDisplayShift(LOW, HIGH);
    }
    }   
}

void loop(){

}

void digitalWriteBatch(int pin[], int HOF[]){
    for(int i = RS; i < MaxDB; i++){
        digitalWrite(i, LOW);
    }
    int pinLength = sizeof(pin);
    for(int i = 0; i < pinLength; i++){
        digitalWrite(pin[i], HOF[i]);
    }
}

//--function--
void ClearDisplay(){digitalWrite(1, HIGH);}

void ReturnHome(){digitalWrite(2, HIGH);}

void EntryModeSet(int IDHOL, int ShiftHOL){
    int pinN[] = {3,2,1};
    int HL[] = {HIGH, IDHOL, ShiftHOL};
    digitalWriteBatch(pinN, HL);
    //digitalWriteBatch({3,2,1}, {HIGH, IDHOL, ShiftHOL});
}

void DisplayOnOff(int Display, int Cursor, int Blink){
    int pinN[] = {4,3,2,1};
    int HL[] = {HIGH, Display, Cursor, Blink};
    digitalWriteBatch(pinN, HL);
    //digitalWriteBatch({4,3,2,1}, {HIGH, Display, Cursor, Blink});
}

void CursorOrDisplayShift(int DispCurs, int LeftRight){
    int pinN[] = {5,4,3};
    int HL[] = {HIGH, DispCurs, LeftRight};
    digitalWriteBatch(pinN, HL);
    //digitalWriteBatch({5,4,3}, {HIGH, DispCurs, LeftRight});
}

void FunctionSet(int DataLenght, int DisplayLine, int DisplayFont){
    int pinN[] = {6,5,4,3};
    int HL[] = {HIGH, DataLenght, DisplayLine, DisplayFont};
    digitalWriteBatch(pinN, HL);
    //digitalWriteBatch({6,5,4,3}, {HIGH, DataLenght, DisplayLine, DisplayFont});
}

void WriteReadData(int WriteRead, int Bit8Data[]){
    int pinN[] = {10,9};
    int HL[] = {HIGH, WriteRead};
    digitalWriteBatch(pinN, HL);
    //digitalWriteBatch({10,9}, {HIGH, WriteRead})
    for(int i = 0; i < sizeof(Bit8Data); i++){
        digitalWrite(8 - i, Bit8Data[8 - i]);
    }
}
