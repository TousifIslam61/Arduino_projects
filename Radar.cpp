#include <Servo.h>

Servo servo;
const int triggerPin = 9;        
const int echoPin = 10;          
const int DetectiondDistance = 20;     
const int ledPin = 6;          
int servoAngle = 0;             

void setup() {
  Serial.begin(9600);
  servo.attach(3);             
  pinMode(triggerPin, OUTPUT);   
  pinMode(echoPin, INPUT);       
  pinMode(ledPin, OUTPUT);       
 

}

void loop() {
  for (servoAngle = 0; servoAngle <= 180; servoAngle += 2) {
    servo.write(servoAngle);   
    delay(30);                   
    checkDistance();            
  }

  for (servoAngle = 180; servoAngle >= 0; servoAngle -= 2) {
    servo.write(servoAngle);   
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
  
  
  if (distance <= DetectiondDistance && distance > 0) {
    Serial.print("Object detected at: ");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(ledPin, HIGH); 
    delay(100);                
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}
