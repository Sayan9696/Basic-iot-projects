int ledPin = D7;
void setup() {
  Serial.begin(9600); pinMode(D7,OUTPUT);}
void loop() {
  if(Serial.available()>0)
{char a; a=Serial.read();
  if(a=='0')
   {   int x = ((255/100)*0);analogWrite(ledPin, x);}
    else if(a=='1')
   {
           float x = ((255/100)*10);    analogWrite(ledPin, x);
 }
 else if(a=='2')
   {
           float x = ((255/100)*20);   analogWrite(ledPin, x);
    }
       else if(a=='3')
   {
           float x = ((255/100)*30);     analogWrite(ledPin, x);
    }
    
    else if(a=='4')
   {
           float x = ((255/100)*40);     analogWrite(ledPin, x);
    }
    else if(a=='5')
   {
           float x = ((255/100)*50);    analogWrite(ledPin, x);
 }
    else if(a=='6')
   {
           float x = ((255/100)*60);    analogWrite(ledPin, x);
 }
    else if(a=='7')
   {
           float x = ((255/100)*70);      analogWrite(ledPin, x);
 }
    else if(a=='8')
   {
           float x = ((255/100)*80);     analogWrite(ledPin, x);
 }
    else if(a=='9')
   {
           float x = ((255/100)*100);     analogWrite(ledPin, x);
 }
}
}
