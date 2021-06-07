#include<Servo.h>//header file
Servo ogma ;//object
void setup() {
  ogma.attach(D5);//signal pin no
}
void loop() {
  int x=analogRead(A0);//analogRead for joystick signals
  //joystick analog value 0 to 1023
  //mapping servo motor angle 0 to 180 degree
    x=map(x,0,1023, 0,180); 
    ogma.write(x);//servo motor angle
    delay(100);
}  
