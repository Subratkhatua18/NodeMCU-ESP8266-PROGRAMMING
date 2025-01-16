#include<OakOLED.h>
#include <ESP8266WiFi.h>

OakOLED oled;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // Initialize the BUILTIN_LED pin as an output
  oled.begin();
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(1);
  Serial.println("STARTING");

}

void loop() {
  // put your main code here, to run repeatedly:
    oled.setCursor(0,30);
  oled.println("HELLO");
  oled.display();
     delay(1000);
    oled.clearDisplay();
 
}
