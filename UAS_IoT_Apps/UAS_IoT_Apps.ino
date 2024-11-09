#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLn5qV7oU1"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "-BF9of1uu60nxcXNvkp0BvG0RVliohMB"
#include "DHT.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Replace with your network credentials
const char* ssid = "Mahasiswa Pradita";
const char* password = "";

// Replace with your Blynk auth token
char auth[] = "-BF9of1uu60nxcXNvkp0BvG0RVliohMB";

// Deklarasi variabel
int timer1;
int timer2;
float Time;
int flag1 = 0;
int flag2 = 0;
float distance = 19.0;
int speed;
int ir_s1 = 22;
int ir_s2 = 23;
int led = 18;
int led2 = 19;
int buzzer = 5;
int sensorPin = 36;
int relay = 21;
int dhtpin =  17;
int DHTTYPE = DHT11;
int max_speed = 20;
int powerMode;

DHT dht(dhtpin, DHTTYPE);

// Define a timer object to read the load cell data and update the Blynk app
BlynkTimer timer;

// Menampilkan kecepatan
// BLYNK_WRITE(V8) {
//   Serial.println(param.asInt());
//   max_speed = param.asInt();
// }

// BLYNK_WRITE(V0) {
//   powerMode = param.asInt();
// }

void setup() {
  Serial.begin(9600);

  // // Connect to Wi-Fi network
  // WiFi.begin(ssid, password);
  // Serial.println("Connecting to Wi-Fi");

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting...");
  // }

  // Serial.println("Connected to Wi-Fi");

  // Connect to Blynk
  // Blynk.config(auth);
  // if(Blynk.connect()){
  //   Serial.println("Connected to Blynk");
  // } else {
  //   Serial.println("Failed to connect to Blynk");
  // }

  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(relay, OUTPUT);

  Serial.println("DHTxx test!");
  dht.begin();

  // Call the readWeight function every 1 second
  timer.setInterval(0L, readSensor);
}

void loop() {
  // Run the Blynk event loop
  // Blynk.run();

  // Run the timer loop
  timer.run();

  // if (powerMode == 1) {
  //   timer.run();
  // } else if (powerMode == 0) {
  //   digitalWrite(relay, HIGH);
  //   Serial.println("Tidak Berjalan");
  // }
}

void readSensor() {
  digitalWrite(relay, HIGH);
  // Membaca nilai sensor cahaya
  int sensorValue = analogRead(sensorPin); 
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Mengubah nilai sensor menjadi string
  String sensorString = String(sensorValue);

  // Menggabungkan string
  String nilai_sensor_cahaya = sensorString + " Lm";

  // Mengubah nilai sensor menjadi string
  String speedString = String(speed);

  // Menggabungkan string
  String nilai_sensor_speed;

  // Membaca nilai sensor suhu dan kelembaban
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Jika output digital dari sensor LOW (cahaya gelap)
  if (sensorValue > 3000) { 
    // digitalWrite(relay, LOW);
    digitalWrite(led, HIGH); 
    digitalWrite(led2, HIGH);
  } else {
    // digitalWrite(relay, HIGH);
    digitalWrite(led, LOW); 
    digitalWrite(led2, LOW);
  }

  // Jika gagal membaca dari sensor DHT
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Jika suhu >= 30 derajat
  if(temperature >= 30.0){
    digitalWrite(relay, LOW);
    Blynk.virtualWrite(V7, "ON");
    delay(5000);
    digitalWrite(relay, HIGH);
  } else {
    digitalWrite(relay, HIGH);
    Blynk.virtualWrite(V7, "OFF"); 
  }

  // Menghitung kecepatan
  if(digitalRead(ir_s1) == LOW && flag1==0) {
    timer1 = millis(); 
    flag1=1;
  }
  if(digitalRead(ir_s2) == LOW && flag2==0) {
    timer2 = millis(); 
    flag2=1;
  }
  if (flag1==1 && flag2==1) {
    if(timer1 > timer2) {
      Time = timer1 - timer2;
    } else if(timer2 > timer1) {
      Time = timer2 - timer1;
    }
    Time = Time / 1000;
    speed = (distance / Time) * 3.6; 
  }

  // Menampilkan suhu dan kelembaban
  Serial.print("Max Speed:");
  Serial.println(max_speed);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if(speed == 0) { 
    if(flag1 == 0 && flag2 == 0) {
      Serial.println("No car detected");
    } else {
      Serial.println("Searching...");
    } 
  } else {
    Serial.println("Speed:");
    Serial.print(speed);
    Serial.print(" Km/Hr  "); 

  // Mengubah nilai sensor menjadi string
  String speedString = String(speed);

  // Menggabungkan string
  nilai_sensor_speed = speedString + " Km/Hr";

    if(speed > max_speed) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }    
    delay(500);
    digitalWrite(buzzer, LOW);
    speed = 0;
    flag1 = 0;
    flag2 = 0;    
  }

  Blynk.virtualWrite(V4, temperature); 
  Blynk.virtualWrite(V5, nilai_sensor_cahaya);
  Blynk.virtualWrite(V6, nilai_sensor_speed); 
}