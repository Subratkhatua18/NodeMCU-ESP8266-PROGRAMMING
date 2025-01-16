  
 // CIRCUIT CONNECTION
     //  ESP8266          DHT11            //  ESP8266            //  Ultrasonic Sensor                //  ESP8266         //  OLED Display
    //  ---------        -------          //  ---------              -------------------              //  ---------           --------------
     // 3.3V       ---->  VCC               // Vin          -------->     5v.                            // GPIO4 (D2) -------->  SDA
     // GND        ---->  GND               // GPIO14 (D5)  --------->    Trig                           // GPIO5 (D1) -------->  SCL
     // GPIO2 (D4) ---->  Data              // GPIO12 (D6)  --------->    Echo                           // 3.3V       -------->  VDD
                                            // GND          --------->    GND                            // GND        -------->  GND

#include <OakOLED.h>
#include <DHT.h>
#include <Wire.h>

// Define the DHT sensor pin and type
#define DHTPIN D4
#define DHTTYPE DHT11

// Define the ultrasonic sensor pins
#define echoPin 12
#define trigPin 14

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);
long duration, distance;
OakOLED oled; // Initialize the OLED display

void setup() {
    Serial.begin(9600); // Start the serial communication at 9600 baud rate
    oled.begin();  // Initialize the OLED display
    dht.begin(); // Initialize the DHT sensor

    // Set up the ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Display a welcome message on the OLED
    oled.clearDisplay();
    oled.setTextSize(2);
    oled.setTextColor(2);
    oled.setCursor(0, 0);
    oled.println("MR. SUBRAT KHATUA");
    oled.display();
    delay(3000); // Wait for 3 seconds
}

void loop() {
    float temperature = dht.readTemperature(); // Read temperature from DHT11
    float humidity = dht.readHumidity(); // Read humidity from DHT11

    // Send a pulse from the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure the echo duration
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance based on the echo duration
    distance = duration / 58.2;
    String disp = String(distance);

    // Clear the OLED display
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(9);

    // Display the temperature on the OLED
    oled.setCursor(0, 0);
    oled.print("Temperature -->");
    oled.print(temperature);
    oled.println(" C");

    // Display the humidity on the OLED
    oled.setCursor(0, 10);
    oled.print("Humidity -->");
    oled.print(humidity);
    oled.println(" %");

    // Display the distance on the OLED
    oled.setCursor(0, 20);
    oled.print("Distance -->");
    oled.print(disp);
    oled.println(" cm");
    oled.display();

    // Print the temperature, humidity, and distance to the serial monitor
    Serial.print("Current Temperature is --> ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Current Humidity is --> ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Current Distance is --> ");
    Serial.print(disp);
    Serial.println(" cm");

    delay(1000); // Wait for 1 second before repeating the loop
}

