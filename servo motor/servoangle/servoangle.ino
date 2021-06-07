#include<Servo.h>

Servo ogma ;//object
void setup() {  ogma.attach(9);//signal pin no
}
void loop() {//servo motor rotation
 
  //ogma.write(0);
  //delay(1000);
  ogma.write(90);
  delay(1000);
  //ogma.write(180);
  //delay(1000);
}//180 degree reverse rotation
