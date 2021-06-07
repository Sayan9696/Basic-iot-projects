#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>


String apiKey = "AULUV71GF2VCKFIZ";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "xtz";     // replace with your wifi ssid and wpa2 key
const char *pass =  "nopass123";
const char* server = "api.thingspeak.com";

#define DHTPIN 0          //pin where the dht11 is connected


const int trigP = 13;  //D4 Or GPIO-2 of nodemcu
const int echoP = 15;  //D3 Or GPIO-0 of nodemcu
int vs =4; 

long duration,m;
int d,cm;
 
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
 Serial.begin(9600);      // Open serial channel at 9600 baud rate
 
}





void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();

    d = readPing();
    //m = vibration();
    m=digitalRead(vs);
   // Serial.println(distance);
    //delay(300);
      
              if (isnan(h) || isnan(t) || isnan(d)|| isnan(m)) 
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
                             Serial.print("  Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(300);
}
