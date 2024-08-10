class RTC{
    public:
        RTC();
        RTC(int Pins[]); //CLK, DAT, RST
        void SendData(byte Input, byte Input2);
        void SetHour(int Hour, boolean ShortFormat);
        void SetMinute(int Minute);
        byte GetData(byte Input);
        long StringToByteLong(String str); // 0 - 7
        String ByteToString(byte B, int byteLength);
        double GetTimeHM();
        int GetTimeH();
        int GetTimeM();
    private:
        int power(int n1, int n2);
        int SCLK, IO, RES;
        byte HourAddress = 133;
        byte MinuteAddress = 131;
        byte SetHourAddress = 132;
        byte SetMinuteAddress = 130;
};
