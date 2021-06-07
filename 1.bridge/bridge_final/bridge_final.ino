#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>

#include "HX711.h"

HX711 scale(12, 14);

float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;
float ounces;
const int buzzerPin = 2;

//Constants:
const int flexPin = A0; //pin A0 to read analog input

//Variables:



String apiKey = "AULUV71GF2VCKFIZ";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "xtz";     // replace with your wifi ssid and wpa2 key
const char *pass =  "nopass123";
const char* server = "api.thingspeak.com";

#define DHTPIN 0          //pin where the dht11 is connected

int ob1 = 16;  
int ob2 = 5;  
const int trigP = 13;  //D4 Or GPIO-2 of nodemcu
const int echoP = 15;  //D3 Or GPIO-0 of nodemcu
int vs =4; 

long duration,m;
int d,cm;
int c=0;

 
DHT dht(DHTPIN, DHT11);


int readPing(){
  delay(70);
  digitalWrite(trigP,LOW);   delayMicroseconds(5);
  digitalWrite(trigP,HIGH);  delayMicroseconds(10);
  digitalWrite(trigP,LOW);

  duration = pulseIn(echoP,HIGH);
  
  cm=(duration/2)/29.1; //*0.0341
  if (cm==0){
    cm=250;
  }
  if (cm>=250)
  {
    cm=250;
  }
  return cm;
}

long vibration(){
 m=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return m;
}


float weight() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  return units;
}

WiFiClient client;
 
void setup() 
{
    //   Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

 pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
 pinMode(echoP, INPUT);   // Sets the echoPin as an Input
 pinMode(vs, INPUT); 
 pinMode(ob1, INPUT);
 pinMode(ob2, INPUT);
 pinMode(buzzerPin,OUTPUT);
 Serial.begin(9600);      // Open serial channel at 9600 baud rate

  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
 
}



void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      int f; //save analog value

    d = readPing();
   float wt = weight();
    m=digitalRead(vs);
   // Serial.println(distance);
    //delay(300);

  f = analogRead(flexPin);         //Read and save analog value from potentiometer
  Serial.println(f);               //Print value
  delay(100);  

   if(digitalRead(ob1)==LOW){
   c++;
     }
   if(digitalRead(ob2)==LOW){
   c--;
     }
     if(c<0){
      c=0;
     }


              if (isnan(h) || isnan(t) || isnan(d)|| isnan(m)|| isnan(c)|| isnan(f)|| isnan(wt)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(d);
                             postStr +="&field4=";
                             postStr += String(m);
                             postStr +="&field5=";
                             postStr += String(c);
                               postStr +="&field6=";
                             postStr += String(f);
                              postStr +="&field7=";
                             postStr += String(wt);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius,Water level,Height: ");
                             Serial.print(d);
                              Serial.print(" Vibration: ");
                             Serial.print(m);
                             Serial.print(" No of Vehicle: ");
                             Serial.print(c);
                             Serial.print("  Humidity: ");
                             Serial.print(h);
                              Serial.print(" Bending: ");
                             Serial.print(f);
                             Serial.print(" Bridge Load: ");
                             Serial.print(wt);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");

      if ( t > 60 || d > 20 || m > 0 || c > 10 || f > 20 || wt > 20)
      {
        digitalWrite(buzzerPin,HIGH);
        Serial.println("Bridge is in Danger...");
        Serial.println("Alert has been send to base station...");
        Serial.println("Close the bridge...");
        
      }
    else{
      digitalWrite(buzzerPin,LOW);
        Serial.println("Bridge is Safe...");
        Serial.println("Everything is fine...");
        Serial.println("Data send to the base station...");
      
    }



  
  // thingspeak needs minimum 15 sec delay between updates
  delay(200);
}
