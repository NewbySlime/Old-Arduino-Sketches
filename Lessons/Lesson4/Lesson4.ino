void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
}
int an = 1;
void loop() {
  // put your main code here, to run repeatedly:
  an = analogRead(A0);
  if(an == 0) an = 1;
  digitalWrite(1, HIGH);
  delay(5000/an);
  digitalWrite(1, LOW);
  delay(100);
}
