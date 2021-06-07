int trigPin=12; int echoPin=13;
int ledPin = 11;
long duration,cm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);  
  pinMode(ledPin,OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(trigPin,LOW);   delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  
  cm=(duration/2)/29.1; //*0.0341
  if (cm==0){
    cm=250;
  }
  Serial.println(cm);
    Serial.println(cm);
  /*Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  delay(100);*/ 
  cm=map(cm,0,100,255,0);
     analogWrite(ledPin, cm);
      Serial.println(cm);
     delay(300);
   
}
