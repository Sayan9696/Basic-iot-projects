void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
}
void loop() {
  if(Serial.available()>0)
{
  char a;
  a=Serial.read();
   if(a=='1')
   {
    digitalWrite(12,HIGH);
   }
    else if(a=='0')
   {
      digitalWrite(12,LOW); 
   }
}}
