int water;
int relay = 18;
int soil = 25;

void setup() {
  pinMode(relay, OUTPUT); // pin output dari board relay, ini akan mengirim sinyal ke relay
  pinMode(soil, INPUT); // pin input yang berasal dari sensor tanah
  Serial.begin(9600);
}

void loop() {
  water = analogRead(soil);  // membaca sinyal yang datang dari sensor tanah
  if(water == HIGH) { // jika ketinggian air penuh maka putuskan relay
    digitalWrite(relay, HIGH); // high untuk memotong relay
  }
  else {
    digitalWrite(relay, LOW); // low untuk terus memberikan sinyal dan suplai air
  }
  delay(500); 
}