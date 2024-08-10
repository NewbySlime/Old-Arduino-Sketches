class Nokia{
    public:
        Nokia();
        Nokia(int Pins[]); //RST, CE, DC, Din, SCLK
        void SendData(byte Input, uint8_t  DCin);
        void init();
        void Reset();
        
    private:
        int RST,CE,DC,Din,SCLK;
};
