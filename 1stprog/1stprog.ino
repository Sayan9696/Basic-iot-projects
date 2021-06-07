void setup() {
  // put your setup code here, to run once:
pinMode(D7,OUTPUT);
pinMode(D8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //[digitalWrite(pin number,state)]
 for(int i=0;i<5;i++){
  digitalWrite(D7,HIGH);
  delay(100);
  digitalWrite(D7,LOW);
  delay(100);}
  for(int i=0;i<5;i++){
  digitalWrite(D8,HIGH);
  delay(2000);
  digitalWrite(D8,LOW);
  delay(1000);}
}
