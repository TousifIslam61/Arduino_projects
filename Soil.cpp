const int soilPin = A0;
const int MP = 13;
const int dryThreshold = 500;
const int LP = 9;
const int trig = 8;
const int echo = 7;
const int DD = 5;

void setup() {
  Serial.begin(9600);
  pinMode(LP, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(MP, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(soilPin, INPUT);
}

void loop() {
  int moisture = analogRead(soilPin);
  Serial.print("Soil Reading: ");
  Serial.println(moisture);

  checkDistance();

  if (moisture > dryThreshold) {
    Serial.println("Soil is dry.");
    digitalWrite(LED_BUILTIN, HIGH);
  } 
  else {
    Serial.println("Soil is moist.");
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(100); 
}


void checkDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH); 
  int distance = duration * 0.0342 / 2;

  if (distance <= DD) {
    Serial.print("Water is enough: ");
    Serial.print(distance);
    Serial.println(" cm");             
    digitalWrite(LP, LOW);
  } 
  else if (distance > 20) {
    Serial.println("Water is less... Fill it up!");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(LP, HIGH);
  }
}