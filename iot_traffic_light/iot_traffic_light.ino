#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLaEpVpnAs"
#define BLYNK_TEMPLATE_NAME "IoT Traffic Light"
#define BLYNK_AUTH_TOKEN "q4xxjW6hGnRPhdY1RT1feGL4DI7cdIJx"

#define Merah 21
#define Kuning 19
#define Hijau 18

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Inzaghi";
char pass[] = "cemara32";
int pinValue0 = 0;
int pinValue1 = 0;
int pinValue2 = 0;

BLYNK_WRITE(V0) {
  pinValue0 = param.asInt();
  if (pinValue0 == 1) {
    digitalWrite(Merah, HIGH);
  }
  else {
    digitalWrite(Merah, LOW);
  }
}

BLYNK_WRITE(V1) {
  pinValue1 = param.asInt();
  if (pinValue1 == 1) {
    digitalWrite(Kuning, HIGH);
  }
  else {
    digitalWrite(Kuning, LOW);
  }
}

BLYNK_WRITE(V2) {
  pinValue2 = param.asInt();
  if (pinValue2 == 1) {
    digitalWrite(Hijau, HIGH);
  }
  else {
    digitalWrite(Hijau, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(Merah, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);
  Serial.println("Hello, ESP32!");
}

void loop() {
  Blynk.run();
  timer.run(); 
}
