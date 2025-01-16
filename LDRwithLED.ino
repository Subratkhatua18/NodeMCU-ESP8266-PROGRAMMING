#include <OakOLED.h>
const int ldrPin = A0;
const int led = D3;
OakOLED oled;
void setup()
{
  Serial.begin(9600);
   oled.begin();
  pinMode(ldrPin, INPUT);
  pinMode(led, OUTPUT);

}
void loop()
{
    
   

  int rawData = analogRead(ldrPin);
  Serial.println(rawData);
  if(rawData < 200)
  {
     digitalWrite(led, HIGH);
     oled.clearDisplay();
      oled.setTextSize(2);
    oled.setTextColor(2);
    oled.setCursor(0, 0);
    oled.println("Light ON");
       oled.display();

  }
  else
  {
      digitalWrite(led, LOW);
     oled.clearDisplay();
      oled.setTextSize(2);
    oled.setTextColor(2);
    oled.setCursor(0, 1);
    oled.println("Light OFF");
   oled.display();

  }
      oled.setTextSize(1.5);
      oled.setTextColor(4);
      oled.setCursor(0, 30);
      oled.print("Intensity -->");
      oled.print(rawData);
      oled.println(" ohm");
      oled.display();

  Serial.print("light Intensity is -->");
  Serial.print(rawData);
  Serial.println(" Ω");
  delay(1000);
}
