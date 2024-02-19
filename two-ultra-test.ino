#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int sdaPin = 0; // Replace with the actual SDA pin
const int sckPin = 1; // Replace with the actual SCK pin


Adafruit_SSD1306 display(128, 64, &Wire, -1);
// defines pins numbers
const int trigPin1 = 11;
const int echoPin1 = 10;

const int trigPin2 = 5;
const int echoPin2 = 6;

// defines variables
long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  display.begin();
  display.display(); // Call display() to show splash screen immediately

  delay(2000); // Delay for 2 seconds to show splash screen
  display.clearDisplay(); // Clear the display buffer

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);  // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);        // Starts the serial communication

}

void loop() {
  display.clearDisplay();
  display.drawCircle(display.width() / 2, display.height() / 2, 20, WHITE);
  display.display();

  // Clears the trigPin for sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 microseconds for sensor 1
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Reads the echoPin for sensor 1, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);

  // Calculating the distance for sensor 1 in centimeters
  distance1 = duration1 * 0.0343 / 2; // Adjust the multiplier

  // Check if the value is within a reasonable range for sensor 1
  if (distance1 >= 2 && distance1 <= 400) {
    // Prints the distance on the Serial Monitor for sensor 1
    Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.println(" cm");
  } else {
    Serial.println("Distance 1 out of range");
  }

  // Clears the trigPin for sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 microseconds for sensor 2
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Reads the echoPin for sensor 2, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculating the distance for sensor 2 in centimeters
  distance2 = duration2 * 0.034 / 2;

  // Check if the value is within a reasonable range for sensor 2
  if (distance2 >= 2 && distance2 <= 400) {
    // Prints the distance on the Serial Monitor for sensor 2
    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.println(" cm");
  } else {
    Serial.println("Distance 2 out of range");
  }

  delay(1000);  // Delay between sensor readings
}
