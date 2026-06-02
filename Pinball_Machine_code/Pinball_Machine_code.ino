#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int trigPin = 2;
const int echoPin = 3;
float distance = 0;
int score = 0;


void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  distance = getDistance();
  Serial.print(distance);
  Serial.println("in");
  if (distance <= 5) {
    score += 1;
  }

  lcd.setCursor(7, 0);
  lcd.print(score);

  delay(1000);
}

float getDistance ()
{
  float echoTime;
  float calculatedDistance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  echoTime = pulseIn(echoPin, HIGH);
  calculatedDistance = echoTime / 148.0;
  return calculatedDistance;
}
