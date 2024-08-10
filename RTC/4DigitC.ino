Digit::Digit() {

}

Digit::Digit(int Pins[], int PinLength, int initialNumber, int delayB) { 
  int l = PinLength;
  for (int n = 0; n < l; n++) {
    if (n < 7) {
      Digit::atf[6 - n] = Pins[n];
    } else if (n == 7) {
      Digit::dot = Pins[n];
    } else if (n < 13) {
      Digit::digit[11 - n] = Pins[n];
    }
    pinMode(Pins[n], OUTPUT);
  }
  Digit::Num = initialNumber;
  Digit::delayBetween = delayB;
  uint8_t nDot[4];
  int ld = sizeof(nDot)/sizeof(nDot[0]);
  for(int i = 0; i < ld; i++){
    nDot[i] = LOW;
  }
  Digit::Dot = nDot;
  Digit::setNumber(Num);
}

void Digit::setNumber(double Number) {
  uint8_t nDot[4];
  int ld = sizeof(nDot)/sizeof(nDot[0]);
  for(int i = 0; i < ld; i++){
    nDot[i] = LOW;
  }
  Digit::Dot = nDot;
  String numStr = String(Number);
  String numberStr;
  int first = 0;
  int i = 0;
  int n = 0;
  for (char c : numStr) {
    if (c == '.') { 
      numberStr +=  numStr.substring(first, i);
      n++;
      first = i + 1;
    }
    i++;
  }
  numberStr +=  numStr.substring(first, i);
  int number = Digit::StringToInt(numberStr);
  Digit::setNumber(number);
}

void Digit::setNumber(int number) {
  uint8_t nDot[4];
  int ld = sizeof(nDot)/sizeof(nDot[0]);
  for(int i = 0; i < ld; i++){
    nDot[i] = LOW;
  }
  Digit::Dot = nDot;
  String numStr = String(number);
  for (int i = 1; i <= 4; i++) {
    int numStrLen = numStr.length();
    int n = (int)numStr.charAt(numStrLen - i) - Digit::charOffset;
    if (n < 0 || n > 9) Digit::Numbers[i - 1] = Digit::atfNum[10];
    else Digit::Numbers[i - 1] = Digit::atfNum[n];
  }
}

void Digit::Refresh() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(Digit::digit[i], LOW);
    digitalWrite(Digit::dot, Digit::Dot[i]);
    Digit::SetPin(Digit::Numbers[i]);
    delay(Digit::delayBetween);
    digitalWrite(Digit::digit[i], HIGH);
  }
}

void Digit::SetPin(String bits) {
  int i = 0;
  for (char c : bits) {
    uint8_t in = LOW;
    if (c == '1') in = HIGH;
    digitalWrite(Digit::atf[i], in);
    i++;
  }
}

int Digit::StringToInt(String str) {
  int res = 0;
  int i = str.length() - 1;
  for (char c : str) {
    int n = 1;
    int in = i;
    while (in > 0) {
      n *= 10;
      in--;
    }
    res += ((int)c - 48) * n;
    i--;
  }
  return res;
}
