void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  Serial.println(analogRead(0));
  delay(100);
}
