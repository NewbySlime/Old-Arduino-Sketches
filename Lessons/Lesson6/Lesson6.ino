void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); pinMode(3, INPUT);
}
int input;
void loop() {
  // put your main code here, to run repeatedly:
  input = digitalRead(3);
  digitalWrite(LED_BUILTIN, input);
}
