#include<WiFiManager.h>
#include<OakOLED.h>
#include<DHT.h> 
//#define WIFI_MODE //uncomment for using WIFI 
#define DHTPIN D4      // Selecting the pin at which we have connected DHT11
#define DHTTYPE DHT11 // Selecting the type of DHT sensors

DHT dht ( DHTPIN, DHTTYPE );

OakOLED oled;

WiFiClient espClient;
 
String apiKey = "SPT36YLGTJAZRB0G";     //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";


WiFiClient client;
void setup_wifi() {

  WiFiManager wifiManager;
  // wifiManager.resetSettings(); // uncomment it once to reset the saved wifi credentials inside mcu
  wifiManager.autoConnect("");

  if(WiFi.status()==WL_CONNECTED){
    Serial.println("Connected.");
    Serial.println(WiFi.SSID());
  }
  else{
    Serial.println("Wifi not connected");
  }  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // Initialize the BUILTIN_LED pin as an output
  oled.begin();
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(1);
  oled.setCursor(0,0);
  oled.println("Initializing sensors");
  oled.display();
  dht.begin (  );    // The sensor will start working
  Serial.println("Starting");
  #ifdef WIFI_MODE
  setup_wifi();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) 
      {
          Serial.println("Failed to read from DHT sensor!");
          return;
      }

#ifdef WIFI_MODE
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
    {  
    
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(t);
      postStr +="&field2=";
      postStr += String(h);
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
      Serial.print(" degrees Celcius, Humidity: ");
      Serial.print(h);
      Serial.println("%. Send to Thingspeak.");
    }
    client.stop();
    #endif
     oled.clearDisplay();
  oled.setTextSize(1.5);
  oled.setTextColor(1);
  oled.setCursor(0,0);
  oled.print("Temp: ");
  oled.println(t);
  oled.print("Humid: ");
  oled.println(h);
  // oled.print("AQI: ");
  // oled.println(air_quality);
  oled.display();
    Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);

}
