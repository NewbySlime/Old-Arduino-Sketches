//TODO: use boolean instead of uint8_t for the dots
class Digit{
    public:
    Digit();
    Digit(int Pins[], int PinLength, int initialNumber, int delayB);
    void setNumber(int number);
    void setNumber(double Number);
    void Refresh();
    int StringToInt(String str);
    
    private:
    String Numbers[4];
    uint8_t *Dot;
    //boolean *DotB;
    String atfNum[11] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011", "0000000"};
    int Num;
    int delayBetween;
    int atf[7];
    int dot;
    int digit[4];
    int charOffset = 48;
    void SetPin(String bits);
};
