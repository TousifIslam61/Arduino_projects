#include <Servo.h>

Servo myServo;
const int triggerPin = 9;     // Trigger pin for the ultrasonic sensor
const int echoPin = 10;        // Echo pin for the ultrasonic sensor
const int thresholdDistance = 20; // Distance threshold for detection (in cm)
const int transistorPin = 8;   // PNP transistor control pin
int servoAngle = 0;            // Current angle of the servo

void setup() {
  Serial.begin(9600);
  myServo.attach(3);           // Attach the servo to pin 3
  pinMode(triggerPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT);     // Set echo pin as input
  pinMode(transistorPin, OUTPUT); // Set transistor control pin as output

  // Turn on the transistor to power the servo
  digitalWrite(transistorPin, LOW); // LOW turns the PNP transistor ON
}

void loop() {
  // Move the servo from 0 to 180 degrees
  for (servoAngle = 0; servoAngle <= 180; servoAngle += 2) {
    myServo.write(servoAngle);   // Move the servo
    delay(30);                   // Delay for smooth movement
    checkDistance();             // Check for distance
  }

  // Move the servo from 180 to 0 degrees
  for (servoAngle = 180; servoAngle >= 0; servoAngle -= 2) {
    myServo.write(servoAngle);   // Move the servo
    delay(30);                   // Delay for smooth movement
    checkDistance();             // Check for distance
  }
}

// Function to measure distance using the ultrasonic sensor
void checkDistance() {
  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger on
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Read the echo
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Convert to cm

  // Check if the distance is below the threshold
  if (distance <= thresholdDistance && distance > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    // Object detected within the threshold
    // You can add any action here if needed
    // e.g., stop the servo, light an LED, etc.
  }
}
