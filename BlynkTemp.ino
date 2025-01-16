#include <OakOLED.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN D4 
#define DHTTYPE DHT11

#define echoPin 12
#define trigPin 14 

DHT dht(DHTPIN, DHTTYPE); 
long duration, distance;
OakOLED oled; 

void setup() {
    Serial.begin(9600);
    oled.begin();  
    dht.begin();

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    oled.clearDisplay();
    oled.setTextSize(2);
    oled.setTextColor(2);
    oled.setCursor(0, 0);
    oled.println("MR. SUBRAT KHATUA");
    oled.display();
    delay(3000);
}
void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = duration / 58.2;
    String disp = String(distance);

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(4);

    oled.setCursor(0,0);
    oled.print("Temperature -->");
    oled.print(temperature);
    oled.println(" C");

    oled.setCursor(0,10);
    oled.print("Humidity -->");
    oled.print(humidity);
    oled.println(" %");

    oled.setCursor(0,20);
    oled.print("Distance -->");
    oled.print(disp);
    oled.println(" cm");
    oled.display();

    Serial.print("Current Temperature is --> ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Current Humidity is --> ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Current Distance is --> ");
    Serial.print(disp);
    Serial.println(" cm");
     delay(1000);
}
