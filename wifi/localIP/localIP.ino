#include <ESP8266WiFi.h>        // Include the Wi-Fi library
//using local
const char* ssid     = "sayan";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "sp123456";     // The password of the Wi-Fi network
WiFiServer server(80);
void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  WiFi.mode(WIFI_STA);
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  server.begin();
}

void loop() { 
  WiFiClient client = server.available();   // Listen for incoming clients
  for(int i=100;i<200;i++){
  client.println(i);
  delay(100);
  }
}
