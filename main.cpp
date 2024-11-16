#include <Servo.h>

Servo myServo;
const int triggerPin = 9;     
const int echoPin = 10;       
const int thresholdDistance = 20; 
const int transistorPin = 8;   
int servoAngle = 0;            
void setup() {
  Serial.begin(9600);
  myServo.attach(3);           
  pinMode(triggerPin, OUTPUT); 
  pinMode(echoPin, INPUT);     
  pinMode(transistorPin, OUTPUT); 
  
  digitalWrite(transistorPin, LOW);
}

void loop() {
  
  for (servoAngle = 0; servoAngle <= 180; servoAngle += 2) {
    myServo.write(servoAngle);   
    delay(30);                   
    checkDistance();             
  }

  // Move the servo from 180 to 0 degrees
  for (servoAngle = 180; servoAngle >= 0; servoAngle -= 2) {
    myServo.write(servoAngle);   
    delay(30);                   
    checkDistance();            
  }
}


void checkDistance() {

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;


  if (distance <= thresholdDistance && distance > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}
