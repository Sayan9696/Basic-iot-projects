#include <Servo.h>        

int trigPin=12; int echoPin=13;
long duration,cm;

#define maximum_distance 200
//boolean goesForward = false;
int distance = 100;

Servo servo_motor; //our servo name


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    servo_motor.attach(9); //our servo pin
    Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);  
  
    servo_motor.write(90);
    delay(2000);
    distance = readPing();
    delay(100);
    distance = readPing();
     delay(100);
  
}
int lookRight(){  
  servo_motor.write(40);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(150);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  digitalWrite(trigPin,LOW);   delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  
  cm=(duration/2)/29.1; //*0.0341
  if (cm==0){
    cm=250;
  }
  return cm;
}

void loop() {
  // put your main code here, to run repeatedly:
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  
  distance = readPing();
   Serial.println(distance);
  delay(300);
  if (distance <= 15){
   
     moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    }
distance = readPing();
}
