#define BLYNK_TEMPLATE_ID "TMPL62iIxKxBD"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitor Indoor"
#define BLYNK_AUTH_TOKEN "906tOwqwtrG-jZHH4TQbFXtk-0TG-xA0"

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 5 // Pin data DHT11 terhubung ke pin 5
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "AirQuality"; // Masukkan nama WiFi Anda
const char *password = "AirQualityMonitor"; // Masukkan kata sandi WiFi Anda
char auth[] = BLYNK_AUTH_TOKEN; // Masukkan token Blynk Anda

const int MQ135Pin = 33; // Pin analog MQ135 terhubung ke pin 33
const int MQ7Pin = 32; // Pin analog MQ7 terhubung ke pin 32
const int blueLEDPin = 4; // Pin digital untuk LED biru
const int redLEDPin = 2; // Pin digital untuk LED merah

// Parameter untuk konversi MQ135
float R0_MQ135 = 1.0; // Ganti dengan nilai kalibrasi Anda
float NO2Curve[3] = {2.602, 0.22, -0.46}; // Kurva karakteristik dari datasheet MQ135

// Parameter untuk konversi MQ7
float R0_MQ7 = 1.0; // Ganti dengan nilai kalibrasi Anda
float CoCurve[3] = {2.3, 0.72, -0.34}; // Kurva karakteristik dari datasheet MQ7

void setup() {
  Serial.begin(9600);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  dht.begin();

  // Memulai koneksi WiFi
  Serial.print("Connecting to WiFi ... ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float MQ135Value = analogRead(MQ135Pin);
  float MQ7Value = analogRead(MQ7Pin);

  // Mengonversi nilai analog ke voltase
  float voltageMQ135 = MQ135Value * (3.3 / 4095.0);
  float voltageMQ7 = MQ7Value * (3.3 / 4095.0);

  // Menghitung Rs untuk MQ135 dan MQ7
  float Rs_MQ135 = ((3.3 * 10.0) / voltageMQ135) - 10.0;
  float Rs_MQ7 = ((3.3 * 10.0) / voltageMQ7) - 10.0;

  // Menghitung ratio Rs/R0
  float ratioMQ135 = Rs_MQ135 / R0_MQ135;
  float ratioMQ7 = Rs_MQ7 / R0_MQ7;

  // Mengonversi ratio Rs/R0 ke PPM menggunakan kurva karakteristik
  float ppmNO2 = pow(10, ((log10(ratioMQ135) - NO2Curve[1]) / NO2Curve[2]) + NO2Curve[0]);
  float ppmCO = pow(10, ((log10(ratioMQ7) - CoCurve[1]) / CoCurve[2]) + CoCurve[0]);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("C\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" %\tNO2 PPM: ");
  Serial.print(ppmNO2);
  Serial.print("\tCO PPM: ");
  Serial.println(ppmCO);

  // Menentukan status suhu
  String temperatureStatus;
  if (temperature < 25) {
    temperatureStatus = "Dingin";
  } else if (temperature > 30) {
    temperatureStatus = "Panas";
  } else {
    temperatureStatus = "Normal";
  }

  Serial.print("Status Suhu: ");
  Serial.println(temperatureStatus);

  // Menentukan kualitas udara berdasarkan NO2
  String airQualityNO2;
  if (ppmNO2 > 100) {
    airQualityNO2 = "Buruk";
  } else {
    airQualityNO2 = "Bagus";
  }

  // Menentukan kualitas udara berdasarkan CO
  String airQualityCO;
  if (ppmCO > 100) {
    airQualityCO = "Buruk";
  } else {
    airQualityCO = "Bagus";
  }

  // Menentukan kualitas udara keseluruhan
  String airQuality;
  if (airQualityNO2 == "Buruk" || airQualityCO == "Buruk") {
    airQuality = "Buruk";
  } else {
    airQuality = "Bagus";
  }

  Serial.print("Kualitas Udara: ");
  Serial.println(airQuality);

  // Logika untuk mengatur LED berdasarkan kualitas udara
  if (airQuality == "Buruk") {
    digitalWrite(blueLEDPin, LOW); // Matikan LED biru
    digitalWrite(redLEDPin, HIGH); // Nyalakan LED merah
  } else {
    digitalWrite(blueLEDPin, HIGH); // Nyalakan LED biru
    digitalWrite(redLEDPin, LOW); // Matikan LED merah
  }

  // Mengirim data ke Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, ppmNO2);
  Blynk.virtualWrite(V3, ppmCO);
  Blynk.virtualWrite(V4, airQuality);

  delay(2000); // Delay untuk membaca sensor setiap 2 detik
}
