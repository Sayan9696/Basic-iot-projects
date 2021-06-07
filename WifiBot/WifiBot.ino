#include <ESP8266WiFi.h>
#include <Servo.h>//mention your pin no for us and servo

String  i;
WiFiServer server(80);
const int LeftMotorForward = D0;
const int LeftMotorBackward = D1;
const int RightMotorForward = D2;
const int RightMotorBackward = D3;

int trig_pin=11;//
int echo_pin =12;//
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

// NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

void setup()
{
  i = "";

  Serial.begin(9600);

  pinMode(LeftMotorForward, OUTPUT); // GPIO pin16=D0 of NodeMCU 12E or in place of '16' you can write'D0' directly || -->Connected to motordriver 
  pinMode(LeftMotorBackward, OUTPUT);  // GPIO pin5=D1 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
  pinMode(RightMotorForward, OUTPUT);  // GPIO pin4=D2 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
  pinMode(RightMotorBackward, OUTPUT);  // GPIO pin0=D3 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
    
    WiFi.disconnect();
  delay(2000);
  Serial.println("Connecting to WIFI");
   WiFi.begin("sayan","sp123456");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }Serial.println("I am Connected");
  Serial.println("My Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();

   servo_motor.attach(D5); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);

 int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 15){
    _mStop();
    delay(300);
    _mBack();
    delay(400);
   _mStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      _mright();
      delay(3000);
      _mStop();
      _mleft();
      
    }
    //else if(distance >= distanceRight)
    else{
      _mleft();
      delay(3000);
     _mStop();
      _mright();
    }
 
 /* else{
    _mForward(); 
  }*/
    distance = readPing();
}

    
    if (i == "Forward") {
      _mForward();
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("forward");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "Reverse") {
      _mBack();
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("reverse");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "Right") {
      _mright();
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("right");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "Left") {
      _mleft();
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("left");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "Stop") {
      _mStop();
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("stop");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    distance = readPing();

}

void _mForward()
{ 
  
  digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  Serial.println("go forward!");
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

  delay(500);
  
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
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  
}
void _mStop()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  Serial.println("Stop!");
}

int readPing(){
  delay(70);
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);
  
long duration=pulseIn(echo_pin,HIGH);
  
int cm = (duration/2)/29.1;
  /*if (cm==0){
    cm=250;
  }*/
  return cm;
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
