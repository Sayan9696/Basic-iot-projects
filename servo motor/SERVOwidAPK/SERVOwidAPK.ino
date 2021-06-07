#include<Servo.h>//header file
Servo ogma ;//object
void setup() {  ogma.attach(9);
  Serial.begin(9600); 
  }
void loop() {
  if(Serial.available()>0)
{
  char a;
  a=Serial.read();
  if(a=='0')
   {   ogma.write(0);//angle given}
   else if(a=='1')
   {  ogma.write(30);//angle given}
   else if(a=='2')
   { ogma.write(60);//angle given  }
   else if(a=='3')
   {  ogma.write(90);//angle given }
    
    else if(a=='4')
   {  ogma.write(120);//angle given}
    else if(a=='5')
   {    ogma.write(150);//angle given
       }
    else if(a=='6')
   {
         ogma.write(180);//angle given
        
 }  
}
}
