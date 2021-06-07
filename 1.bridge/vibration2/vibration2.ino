int led = 13;
int vs =D1; // vibration sensor
 
void setup(){
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT); 
  Serial.begin(9600); 
 
}
void loop(){
  long measurement =vibration();
  delay(1000);
  Serial.println(measurement);
 /* if (measurement > 50){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW); 
  }*/
}
 
long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
