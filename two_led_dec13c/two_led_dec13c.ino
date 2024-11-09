int led1 = 18;
int led2 = 19;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
}