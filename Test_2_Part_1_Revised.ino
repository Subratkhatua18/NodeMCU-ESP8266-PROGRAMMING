#include<OakOLED.h>
#include<DHT.h>
#define DHTPIN D4      // Selecting the pin at which we have connected DHT11
#define DHTTYPE DHT11


DHT dht ( DHTPIN, DHTTYPE );

OakOLED oled;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  oled.begin();
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(1);
  oled.setCursor(0,0);
  oled.println("INITIALIZING SENSORS");
  oled.display();
  delay(1000);
  dht.begin (  );
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  oled.clearDisplay();
  oled.setTextSize(1.5);
  oled.setTextColor(1);
  oled.setCursor(0,0);
  oled.print("Temp: ");
  oled.println(t);
  oled.print("Humid: ");
  oled.println(h);
  oled.display();
  delay(10000);

}
