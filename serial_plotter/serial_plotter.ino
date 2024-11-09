void setup() {
    Serial.begin(9600); 
}

void loop() {
    int y1 = analogRead(A0);
    
    Serial.println(y1);
    
    delay(100);
}