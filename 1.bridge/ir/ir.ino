int obstaclePin = D0;  // This is our input pin
int hasObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
  int c=0;int f=0;
void setup() {
 // pinMode(LED, OUTPUT);
  pinMode(obstaclePin, INPUT);
  Serial.begin(9600);  
}
void loop() {
 // hasObstacle = digitalRead(obstaclePin);//Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  //while(digitalRead(obstaclePin)==LOW);
   if(digitalRead(obstaclePin)==LOW){
   c++;
     Serial.println(c);
    delay(1000);}
  // while(digitalRead(obstaclePin)==HIGH);   
}
