#define PIN 35

void setup()
{
  Serial.begin(9600);
  Serial.println("Thermometer");
}

void loop()
{
  int temp = analogRead(PIN);
  temp = temp * 4.88;
  temp = temp / 10 - 50;
  temp = temp / 81.1667;
  Serial.println(temp);
  delay(2000);
}