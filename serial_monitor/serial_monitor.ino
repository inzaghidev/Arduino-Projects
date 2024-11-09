void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // set the digital pin as output:
}

void loop() {
  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if(command == "ON")
    {
      digitalWrite(LED_BUILTIN, HIGH); // turn on LED
      Serial.println("LED is turned ON"); // send action to Serial Monitor
    }
    else
    if(command == "OFF")
    {
      digitalWrite(LED_BUILTIN, LOW);  // turn off LED
      Serial.println("LED is turned OFF"); // send action to Serial Monitor
    }
  }
}