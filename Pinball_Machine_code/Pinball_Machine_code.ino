#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int trigPin = 2;
const int echoPin = 3;
float distance = 0;

int score = 0;
int game = 0;
int countdown = 31;

bool played = 0;

#include <Servo.h>
Servo servo1;

unsigned long CountdownTime = 0;
unsigned long SensorTime = 0;


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

  unsigned long currentTime = millis();  //Half a second delay to check for scored balls so multiple balls dont get released

  if (currentTime - SensorTime >= 50) {
    SensorTime = currentTime;
    distance = getDistance();
  }

  Serial.print(distance);
  Serial.println("in");
  if (game == 1) {
    if ( distance > 0 && distance <= 5) {
      score += 1;
      ball();
    }

    lcd.setCursor(4, 1);  //Display the score
    lcd.print("Score: ");
    lcd.print(score);

    if (currentTime - CountdownTime >= 1000) {  //Decreases the countdown every second without pausing the whole program
      CountdownTime = currentTime;
      countdown -= 1;
      lcd.setCursor(7, 0);
      lcd.print(countdown);
      lcd.print(" ");
    }

  }

  if (countdown == 0) {  //When the countdown ends, end the game
      game = 0;
  }

  if (digitalRead(7) == LOW && game == 0 && played == 0) {  //Button to start the game
      game = 1;
      played = 1;
      CountdownTime = millis();
      SensorTime = millis();
      ball();
    }
  if (digitalRead(6) == LOW) {  //Button to end the game
    game = 0;
  }

  if (game == 0 && played == 1) {  //Final score displayed after the game ends
    played = 0;
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

void ball() {  //release a ball
  servo1.write(180);
  delay(500);
  servo1.write(75);
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
