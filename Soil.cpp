// Pin setup
const int soilPin = A0;
const int ledPin = 13;
const int dryness = 600;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int moisture = analogRead(soilPin);
  Serial.print("Soil Reading: ");
  Serial.println(moisture);

  if (moisture > dryness) {
    Serial.println("Soil is dry.");
    digitalWrite(ledPin, HIGH);
    // You could turn on a motor or buzzer here
  } else {
    Serial.println("Soil is moist.");
    digitalWrite(ledPin, LOW);
  }

  delay(2000);
}