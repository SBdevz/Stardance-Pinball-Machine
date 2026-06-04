#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int trigPin = 2;
const int echoPin = 3;
float distance = 0;

int score = 0;
int game = 0;
int countdown = 31;

#include <Servo.h>
Servo servo1;


void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);
  lcd.clear();

  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  servo1.attach(4);
  servo1.write(0);
}

void loop() {
  distance = getDistance();
  Serial.print(distance);
  Serial.println("in");
  if (game == 1) {
    if (distance <= 5) {
      score += 1;
      ball();
      delay(1000);
    }

    lcd.setCursor(4, 1);
    lcd.print("Score: ");
    lcd.print(score);

    countdown -= 1;
    lcd.setCursor(7, 0);
    lcd.print(countdown);
    lcd.print(" ");
    
    delay(1000);
  }

  if (countdown == 0) {
      game = 0;
  }

  if (digitalRead(7) == LOW) {
      game = 1;
    }
  if (digitalRead(6) == LOW) {
    game = 0;
  }

  if (game == 0) {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Final Score:");
    lcd.setCursor(7, 1);
    lcd.print(score);
    delay(5000);
    score = 0;
    countdown = 31;
    lcd.clear();
  } 
}

void ball() {
  servo1.write(90);
  delay(500);
  servo1.write(0);
  delay(500);
  countdown = 31;
  delay(1000);
}

float getDistance() {
  float echoTime;
  float calculatedDistance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  echoTime = pulseIn(echoPin, HIGH);
  calculatedDistance = echoTime / 148.0;
  return calculatedDistance;
}
