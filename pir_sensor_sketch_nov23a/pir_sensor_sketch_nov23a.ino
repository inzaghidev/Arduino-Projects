int pirSensor = 18;
int ledPin = 19;

void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int pirpin = digitalRead(pirSensor);
  int sensorValue = digitalRead(pirSensor);

  if(pirpin == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
