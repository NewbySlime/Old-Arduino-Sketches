int RS = 10;
int RW = 9;
int MaxDB = 8;
int MinDB = 1;


class StringBit{
    public:
        StringBit(String s){
            CurrString = s;
            StoreBit();
            StringToBit(CurrString);
        }

        void SetString(String s){
            CurrString = s;
            StringToBit(CurrString);
        }

        int StringLenght(){
            return CurrString.length();
        }

        String GetStringBit(int index){
            return BitString[index];
        }

        String GetString(){
            return CurrString;
        }
    
    private:
        int offset = 16;
        String BitString[0];
        String CurrString;
        bool StoredBits;
        String Bits8[16*16]; //this used to store all the bits, note that this uses string as the bits
        String AllChar = "!\"#$%&'()*+,_./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUWXYZ[$]^_`abcdefghijklmnopqrstuvwxyz{|}";

        void StringToBit(String s){
            if(!StoredBits){
                StoreBit();
            }
            for(int i = 0; i < s.length(); i++){ //per char
                int n = AllChar.indexOf(s.charAt(i));
                BitString[i] = Bits8[16 + n];
            }
        }

        void StoreBit(){ //this makes from 0 to 256 in 8-bit
            char nBitArray[] = {'0','0','0','0','0','0','0','0'};
            String BitStringn(nBitArray);
            Bits8[0] = BitStringn;        

            for(int i = 1; i < 255; i++){
               bool many = false;
               for(int o = 0; o < sizeof(many); o++){
                   if(nBitArray[8-o] == '1'){
                       many = true;
                       continue;
                   }else{
                       nBitArray[7-o] = '1';
                       if(many){
                           for(int z = o; z > 0; z--){
                               nBitArray[8-z] = '0';
                           }
                       }
                       break;
                   }
               }
               BitStringn = new String(nBitArray);
               Bits8[i] = BitStringn;
           }
            StoredBits = true;
        }

        String Iterative(char[] CharArray){
            
        }
}

StringBit CurrentString("Hello");


void setup(){
    for(int i = MinDB; i<=RS; i++){
        pinMode(i, OUTPUT);
    }

    DisplayOnOff(HIGH, HIGH, LOW);
    FunctionSet(HIGH, LOW, HIGH);


}

void loop(){
    
}


void digitalWriteBatch(int pin[], int HOF[]){
    for(int i = MaxDB; i < RS; i++){
        digitalWrite(i, LOW);
    }
    int pinLength = sizeof(pin);
    for(int i = 0; i < pinLength; i++){
        digitalWrite(pin[i], HOF[i]);
    }
}

//--lcd function--
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