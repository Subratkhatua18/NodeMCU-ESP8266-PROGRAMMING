#include <OakOLED.h> // OLED library
OakOLED oled;
void setup() {    // Initialize serial communication
    Serial.begin(9600);     // Initialize the OLED object using the begin() function
    oled.begin();             // Clear all text from the display
    oled.clearDisplay();        // Set the size of the text (default size is 1, each increase in size adds 10 pixels in height)
    oled.setTextSize(2);      // Set the text color
    oled.setTextColor(1);     // Set the coordinates to start writing text
    oled.setCursor(0, 0);     // Print the message on the OLED
    oled.println("Mr. Subrat Khatua , Sai Sampurna Khatua");       // Display the text on the screen
    oled.display();
}

void loop() {
    // The loop function is empty since no repetitive tasks are needed for this example
}
