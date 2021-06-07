int trigPin=12; int echoPin=13;
int ledPin = 11;
long duration,cm;
int x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin,OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  cm=(duration/2)/29.1; //*0.0341
  /*Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  delay(100);*/ 

  if(cm>0 && cm<11)
  {
   x = ((255/100)*100);analogWrite(ledPin, x);
  }
  else if(cm>12 && cm<30)
  {
    x = ((255/100)*20);analogWrite(ledPin, x);
  }
  else
  {
    x = ((255/100)*0);analogWrite(ledPin, x);
  }
  
  //cm=map(cm,0,100,255,0);
    // analogWrite(ledPin, cm);
     Serial.println(cm);
     delay(200);
   
}
