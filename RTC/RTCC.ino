RTC::RTC(){
  
}
RTC::RTC(int Pins[]){
    RTC::SCLK = Pins[0];
    RTC::IO = Pins[1];
    RTC::RES = Pins[2];
    int l = sizeof(Pins)/sizeof(Pins[0]);
    for(int i = 0; i < l; i++){
        pinMode(Pins[i], OUTPUT);
    }
}

void RTC::SendData(byte Input, byte Input2){
    digitalWrite(RTC::RES, HIGH);
    byte bs[2] = {Input, Input2};
    for(int i = 0; i < 2; i++){
        digitalWrite(RTC::SCLK, LOW);
        shiftOut(RTC::IO, RTC::SCLK, LSBFIRST, bs[i]);
    }
    digitalWrite(RTC::RES, LOW);
}

byte RTC::GetData(byte Input){
    digitalWrite(RTC::RES, HIGH);
    digitalWrite(RTC::SCLK, LOW);
    shiftOut(RTC::IO, RTC::SCLK, LSBFIRST, Input);
    byte res = shiftIn(RTC::IO, RTC::SCLK, LSBFIRST);
    digitalWrite(RTC::RES, LOW);
    return res;
}

long RTC::StringToByteLong(String str){
    int i = str.length() - 1;
    long res = 0;
    for(char c: str){
        if(c == '1'){
            int n = power(2,i);
            res += n;
        }
        i--;
    }
    return res;
}

String RTC::ByteToString(byte B, int byteLength){
    int BI = (int)B;
    String res = "";
    int i;
    for(i = byteLength - 1; i >= 0 && BI > 0; i--){
        int n = power(2,i);
        if(BI/n < 1){
            res += '0';
            continue;
        }
        else{
            BI = BI%n;
            res += '1';
        }
    }
    while(i >= 0){
        res += '0';
        i--;
    }
    return res;
}

int RTC::power(int n1, int n2){
  int res = 1;
  for(int i = 1; i <= n2; i++){
    res *= n1;
  }
  return res;
}

double RTC::GetTimeHM(){
    double res = (RTC::GetTimeH()) + (RTC::GetTimeM() * 0.01);
    return res;
}

int RTC::GetTimeH(){
  String Str = RTC::ByteToString(RTC::GetData(RTC::HourAddress), 8);
  int res;
  int n = 4;
  int add = 0;
  char *cs;
  Str.toCharArray(cs, Str.length());
  if(cs[2] != '1'){
      add = 12;
  }
  String StrSub = Str.substring(n);
  res = (int)RTC::StringToByteLong(StrSub);
  res += add;
  return res;
}

int RTC::GetTimeM(){
    String Str = RTC::ByteToString(RTC::GetData(RTC::MinuteAddress), 8);
    String sub1 = Str.substring(1, 4);
    String sub2 = Str.substring(4);    
    int res = (int)(RTC::StringToByteLong(sub1) * 10) + RTC::StringToByteLong(sub2);
    return res;
}

void RTC::SetHour(int Hour, boolean ShortFormat){
  int res = 0;
  if(ShortFormat){
      if(Hour > 12){
          Hour  -= 12;
          res += 32;
      }
      res += Hour + 128;
  }else res += Hour;
  byte Input = byte(res);
  RTC::SendData(RTC::SetHourAddress, Input);
}
void RTC::SetMinute(int Minute){
  double d1 = Minute/10;
  int i1 = int(Minute);
  int i2 = int((d1 - i1) * 10);
  byte Input = byte(RTC::StringToByteLong(RTC::ByteToString(byte(i1), 4) + RTC::ByteToString(byte(i2), 4)));
  RTC::SendData(RTC::SetMinuteAddress, Input);
}
