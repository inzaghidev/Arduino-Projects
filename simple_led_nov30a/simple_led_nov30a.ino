void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(18, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(18, HIGH); // turn the LED on
  Serial.println("Lampu ON");
  delay(1000);             // wait for 500 milliseconds
  digitalWrite(18, LOW);  // turn the LED off
  Serial.println("Lampu OFF");
  delay(1000);             // wait for 500 milliseconds
}