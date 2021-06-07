//MakewithREX Bot controller android app
#include <Servo.h>  
int Lir = 8;// This is our input pin
int Rir = 2;
 // HIGH MEANS NO OBSTACLE
 int Lc=0;int Rc=0;
 int avg=0; int x=0;
 int f=1;

//sensor pins
/*#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2
*/
int trigPin=12; int echoPin=13;
long duration,cm;



#define maximum_distance 200
//boolean goesForward = false;
int distance = 100;

// NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

char getstr;
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

int lookRight(){  
  servo_motor.write(60);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(120);
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


void _mForward()
{ 
  
  digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
 // Serial.println("go forward!");
}
void _mBack()
{
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  Serial.println("go back!");
}
void _mleft()
{
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(1000);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  Serial.println("go left!");
}
void _mright()
{
  
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(1000);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  Serial.println("go right!");
  
}
void _mStop()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  Serial.println("Stop!");
}

void setup()
{ 
   pinMode(Lir, INPUT);
    pinMode(Rir, INPUT);
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
 
    servo_motor.attach(9); //our servo pin
   
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);  



  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  /*distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  */distance = readPing();
  delay(100);
}


void loop()
  { int m=25;
   int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  _mForward(); 
 // delay(50);
  //Lc=0;Rc=0;avg=0;x=0;
  if(digitalRead(Lir)==LOW); 
    Lc++;
    Serial.println("Lc");
    Serial.println(Lc);
     if(digitalRead(Lir)!=LOW);
     
  if(digitalRead(Rir)==LOW); 
    Rc++;
    Serial.println("Rc");
    Serial.println(Rc);
     if(digitalRead(Rir)!=LOW);

   avg=(Lc+Rc)/2;
  delay(50);
  
   if(avg>=10 && f==1)
  {
    _mStop();
    _mright();
    delay(1000);
    _mStop();
    _mright(); 
    Lc=0;Rc=0;avg=0;x=0; 
    f=0;
  }  
     if(avg>=10 && f==0)
     {
      _mStop();
      _mleft();
      delay(1000);
      _mStop();
      _mleft(); 
      Lc=0;Rc=0;avg=0;x=0;
      f=1;
     }
  
  distance = readPing();
   //Serial.println(distance);
  delay(300);
  
  
    if (distance <= 20){
      Serial.println(distance);
     _mStop();
    delay(300);
    _mBack();
    delay(1000);
    _mStop();
    delay(300);
    distanceRight = lookRight();
    /*Serial.println("Right:");
    Serial.println(distanceRight);*/
    delay(300);
    distanceLeft = lookLeft();
    /*Serial.println("Left:");
    Serial.println(distanceLeft);*/
    delay(300);
     
     if (m >= distanceRight){
      _mleft();
      _mStop();
    }
    else if(m > distanceLeft)
    {
      _mright();
      _mStop();
    }
  }
  else{
    _mForward(); 
  }


distance = readPing();

   //else{ 
  getstr=Serial.read();
 if(getstr=='F')
  {
    _mForward();
  }
  else if(getstr=='B')
  {
    _mBack();
    delay(200);
  }
  else if(getstr=='R')// according to my robot. otherwise L
  {
    _mleft();
    delay(200);
  }
  else if(getstr=='L') // according to my robot. otherwise R
  {
    _mright();
    delay(200);
  }
  else if(getstr=='X')
  {
     _mStop();     
  }
   
   distance = readPing();
}
