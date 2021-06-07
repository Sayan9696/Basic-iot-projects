int vib_pin=D1;
int led_pin=13;
void setup() {
   Serial.begin(115200);
    delay(10);
  pinMode(vib_pin,INPUT);
  pinMode(led_pin,OUTPUT);
}

void loop() {
  int val;
  val=digitalRead(vib_pin);

    Serial.println("Connecting to ");
       Serial.println(val);
       delay(500);
  
  /*if(val==1)
  {
    digitalWrite(led_pin,HIGH);
    delay(1000);
    digitalWrite(led_pin,LOW);
    delay(1000);
   }
   else
   digitalWrite(led_pin,LOW);
*/}
