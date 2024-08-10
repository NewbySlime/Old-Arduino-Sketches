int atf[] = {2,3,4,5,6,7,8};
int digit[] = {9,10,11,12};
int dot = 13;
int delayD = 30;
int charOffset;

class Number{
    public:
        Number(){
            Num = 0;
            delayBetween = 0;
            setNumber(Num);
        }
        Number(int initialNumber, int delayB){
            Serial.println(initialNumber);
            Num = initialNumber;
            delayBetween = delayB;
            setNumber(Num); 
        }

        void setNumber(int number){
            String numStr = String(number);
            for(int i = 1; i <= 4; i++){
                int numStrLength = numStr.length();
                int n = (int)numStr.charAt(numStrLength - i) - 48;
                if(n < 0) Numbers[4 - i] = atfNum[0];
                else Numbers[4 - i] = atfNum[n];
            }
        }

        void Refresh(){
            for(int i = 4 - 1; i >= 0; i--){
                digitalWrite(digit[i], LOW);
                SetPin(Numbers[i]);
                delay(delayBetween);
                digitalWrite(digit[i], HIGH);
            }
        }

        int getNumber(){return Num;}
    
    private:
        String Numbers[4];
        String atfNum[10] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};
        //abcdef, bc, abged, abgcd, fgbc, afgcd, afedcg, abc, abcdefg, afgbcd
        int Num;
        int delayBetween;
        void SetPin(String bits){
            int i = 0;
            for(char c : bits){
                uint8_t in = HIGH;
                if(c == '0') in = LOW;
                digitalWrite(atf[0+i], in);
                i++;
            }
        }

};

Number Nu;
int n = 0;
void setup(){
    for(int n : atf){
        pinMode(n, OUTPUT);
    }
    for(int m : digit){
        pinMode(m, OUTPUT);
        digitalWrite(m, HIGH);
    }
    pinMode(dot, OUTPUT);
    Nu = *new Number(n, delayD);
}

void loop(){
    Nu.Refresh();
    delay(100);
    n++;
    Nu.setNumber(n);
}
