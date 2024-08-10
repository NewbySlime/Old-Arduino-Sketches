RFID::RFID(int SCK, int MOSI, int MISO, int RST, int NSS){
    int out[] = {SCK,MOSI,RST,NSS};
    for(int i = 0; i < 4; i++) pinMode(out[i], OUTPUT);
    RFID::SCK = SCK;
    RFID::MOSI = MOSI;
    RFID::MISO = MISO; pinMode(MISO, INPUT);
    RFID::RST = RST;
    digitalWrite(RST, HIGH);
    RFID::NSS = NSS;
    digitalWrite(NSS, HIGH);
}

byte RFID::SendData(boolean RW, byte Address, byte* Input){
    Address += RW ? 1 : 0;
    int InputL = sizeof(Input)/sizeof(Input[0]);
    digitalWrite(RFID::SCK, LOW);
    digitalWrite(RFID::NSS, LOW);
    shiftOut(RFID::MOSI, RFID::SCK, MSBFIRST, Address);
    int i = -1;
    while(i++ < InputL){
        byte I = Input[i];
        if(InputL == 1) I = Input; 
        digitalWrite(RFID::SCK, LOW);
        shiftOut(RFID::MOSI, RFID::SCK, MSBFIRST, I);
    }
    digitalWrite(RFID::NSS, HIGH);
    return RW ? shiftIn(RFID::MISO, RFID::SCK, MSBFIRST) : 0;
}

byte RFID::CmdReg(boolean RW, boolean RcvOff, boolean PowerDown, byte Command){
    RcvOff ? bitSet(Command,5):bitClear(Command,5);
    PowerDown ? bitSet(Command,4):bitClear(Command,4);
    byte res = RFID::SendData(RW, CommandReg,Command);
    return res;
}
