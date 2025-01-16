// dht_with_airquality_mqtt on_OLED Display experiment

/*--> In this experiment temperature, humidity and Air quality value is showing on oled display and as well as on Node red server.

// first you have to inclue the libraries in your arduino ide.
// You can include the libraries from arduino ide
  Step 1- click on sketch on menu bar of arduino ide
  Step 2- hover on include libraries and then click on add zip library or you download libraries from manage library option.
  Step 3- Go to the folder where you have saved the zip files of the libraries.
  Step 4- Then click on open. 

TO GET THE DATA ON NODE RED SERVER YOU HAVE TO INSTALL NODE RED ON YOUR DESKTOP

TO INSTALL THE NODE RED ON YOUR SERVER FOLLOW THE BELOW STEPS

STEP 1. Open your browser and open the attached link and download node js "https://nodejs.org/en/download"
STEP 2. If you have windows 7 or lower try to download lower version of node js.(Optional)
STEP 3. Once installed, open a command prompt and run the following command to ensure Node.js and npm are installed correctly
        a> node --version
        b> npm --version
STEP 4. After that you have to run command 
        a> npm install -g --unsafe-perm node-red
STEP 5. Once installed, you are ready to run Node-RED.
STEP 6. open command prompt and run command "node-red".

  

////////////////////////////////////PIN MAPING////////////////////////////////////////
     
         oled section                   Node MCU
           GND                            GND 
           VDD                            3V3
           SCK                            D1
           SCL                            D2


   DHT 11 temp & humd section           Node MCU
           5v/3V3                         3V3
           DATA                           D4            
   
     MQ135(Air Quality) section         Node MCU
           D0                             A0
           GND                            GND
           PWR                            Vin        */


#include <ArduinoJson.h>
#include <PubSubClient.h>
#include<WiFiManager.h>
#include "OakOLED.h"
#include"MQ135.h"
#include "DHT.h"    // including the library of DHT11 temperature and humidity sensor
#define DHTPIN D4      // Selecting the pin at which we have connected DHT11
#define DHTTYPE DHT11 // Selecting the type of DHT sensors
DHT dht ( DHTPIN, DHTTYPE );
int sensorValue;

OakOLED oled;



WiFiClient espClient;
PubSubClient client(espClient);
char mqtt_server[20] = "3.111.55.21" ;
char port[6] = "1883";
char topic[40] = "WM16";

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (200)
char json[MSG_BUFFER_SIZE];
int value = 0;


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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "espClient";
   clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
   // if (client.connect("espClient", "BTbDj8IUPl7778PYLSvI", ""))
    {
      Serial.println("connected to broker: ");
      Serial.println(mqtt_server);
      //Once connected, publish an announcement...
      //client.publish(topic, "hello world");
      // ... and resubscribe
      //client.subscribe("inTopic");
    }
    
    else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_server);
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_setup(){

  client.setServer(mqtt_server, atoi(port));
}

void mqtt_loop(){
  
    if (!client.connected()) {
    reconnect();
  }
   MQ135 gasSensor = MQ135(A0);
   float air_quality = gasSensor.getPPM();
    float humidity = dht.readHumidity ( );  // Declaring h a variable and storing the humidity in it.
   float temp = dht.readTemperature ( );
  /**
     Read the measured temp data
     Return the measured temp data of float type, unit: C
  */   
  Serial.print(" Temperature:");
  Serial.print(temp);   // Only print one decimal place
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humidity);   // Only print one decimal place
  Serial.print("%");
  Serial.println("Air_Quality");
  Serial.println(air_quality);
  Serial.println("PPM");
  Serial.println();
  
  oled.clearDisplay();
  oled.setTextSize(1.5);
  oled.setTextColor(1);
  oled.setCursor(0,0);
  oled.print("Temp: ");
  oled.println(temp);
  oled.print("Humid: ");
  oled.println(humidity);
  oled.print("AQI: ");
  oled.println(air_quality);
  oled.display();
  delay(1000);


  //Creating JSON object to send
  StaticJsonDocument<200> doc;
  JsonObject root = doc.to<JsonObject>();
 
  root["temp"] = temp;
  root["t_unit"] = "C";
  root["humid"] = humidity;
  root["h_unit"]= "%";
  root["air_Q"] = air_quality;
  root["a_unit"] = "PPM";


  serializeJsonPretty(doc, Serial);
  serializeJsonPretty(doc, json);

  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    //snprintf (json, MSG_BUFFER_SIZE, "hello world #%ld", value); // was showing unexpected token h in JSON at position 0"
    Serial.print("Publish message: ");
    Serial.println(json);
    client.publish(topic, json);
  }
}

void setup() {
 // pinMode(BUILTIN_LED, OUTPUT);  
 Serial.begin(9600);   // Initialize the BUILTIN_LED pin as an output
 oled.begin();
 oled.clearDisplay();
 oled.setTextSize(1);
 oled.setTextColor(1);
 oled.setCursor(0,0);
oled.println("Initializing sensors");
  
   dht.begin (  );    // The sensor will start working
  Serial.println("Starting");
  setup_wifi(); 
    mqtt_setup();
}

void loop() {
  
  mqtt_loop();  
}
