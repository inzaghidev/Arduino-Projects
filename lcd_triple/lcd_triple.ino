int redLED = 18;
int yellowLED = 19; // Ganti dengan pin yang mendukung output digital
int blueLED = 21;

void setup()
{
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop()
{
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(blueLED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
}