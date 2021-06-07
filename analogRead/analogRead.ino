void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  int value =analogRead(A0);
  float voltage= ((5.00/1023.00)*value);
  Serial.println(voltage);
  delay(100);

}
