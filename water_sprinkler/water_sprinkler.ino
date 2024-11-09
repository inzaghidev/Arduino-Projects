#include <WiFi.h>       // Tambahkan library WiFi
#include <WiFiClient.h> // Tambahkan library WiFiClient
#include <BlynkSimpleEsp32.h> // Tambahkan library Blynk

// Pin Configuration
const int soilMoisturePin = 34;
const int relayPin = 26;  // Pin relay terhubung ke GPIO 26

char auth[] = "ESfFeZ1Tk_7xHSjBWnpU3RTaFc30UhiF";  // Blynk authentication token

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  Blynk.begin(auth, "dapid_disini", "david2003");  // Initialize Blynk connection
    while (!Blynk.connected()) {
    delay(100);
  }

  Serial.println("Terhubung ke Blynk...");
}

void loop() {
  Blynk.run();
  if(Blynk.connected()){
  int soilMoistureValue = analogRead(soilMoisturePin);

  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  if (soilMoistureValue < 2000) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }
  Blynk.virtualWrite(V1, soilMoistureValue);
  delay(1000);
  }}