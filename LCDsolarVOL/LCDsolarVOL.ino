#include<LiquidCrystal.h>
LiquidCrystal ogma(12,11,5,4,3,2);
//rs=12,en=11,d4=5,d5=4,d6=3,d7=2
void setup() { 
  // put your setup code here, to run once:
  ogma.begin(16,2);
  ogma.print("VOLTAGE=");//printing chararcters
  ogma.setCursor(13,0);//setting positions
  ogma.print('v');
}//solar intensity(VOLTAGE) display in LCD
void loop() {
  // put your main code here, to run repeatedly:
   int value =analogRead(A0);
   float voltage= ((5.00/1023.00)*value);
   ogma.setCursor(8,0);
    ogma.print(voltage);
    delay(100); }
