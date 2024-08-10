#include "Nokia5110C.h"
int NokiaPins[] = {10, 8, 6, 4, 2};
Nokia n;
void setup(){
    n = Nokia(NokiaPins);
    n.init();
    n.SendData(20, HIGH);
}

void loop(){
  n.SendData(15, HIGH);
}
