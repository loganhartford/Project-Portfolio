#include <HCSR04.h>

int echoPin = 13;
int trigPin = 12;

int randSeed = A0;


int speed1 = 6;
int IN1 = 2;
int IN2 = 4;

int speed2 = 9;
int IN3 = 10;
int IN4 = 11;

int mSpeed = 100; // DO NOT GO ABOVE 200 WITHOUT VOLTAGE REGULATOR

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(speed2, OUTPUT);

  randomSeed(analogRead(randSeed));
}

/* Truth Table

    IN3 IN4
    IN1 IN2 Direction
    1   0   Reverse
    0   1   Forward
    1   1   Stop
    0   0   Stop

*/

void loop() {

//  for (int i = 0; i < 260; i+=10) 
//  {
//    driveForward(i,i);
//    delay(2000);
//  }
  driveForward(255, 64);
  delay(3000);
  driveForward(64, 255);
  delay(3000);
}




float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int pingTravelTime = pulseIn(echoPin, HIGH);
  delay(25);

  float pingTravelDistance = (pingTravelTime * 765.*5280.*12) / (3600.*1000000);
  float distanceToTarget = pingTravelDistance / 2;

  return distanceToTarget;
}

void driveForward(int speedOne, int speedTwo) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(speed1, speedOne);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(speed2, speedTwo);
}

void driveBackwards() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(speed1, mSpeed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(speed2, mSpeed);
}

void turnLeft() {
  // Right Wheel
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(speed1, mSpeed);
  // Left Wheel
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(speed2, mSpeed);
}

void turnRight() {
  // Right Wheel
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(speed1, mSpeed);
  // Left Wheel
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(speed2, mSpeed);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(speed1, mSpeed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(speed2, mSpeed);
}

void avoidObstacle() {
  int choice = random(0, 2);
  stop();
  delay(1000);
  while (measureDistance(trigPin, echoPin) < 10) {
    driveBackwards();
    Serial.println(measureDistance(trigPin, echoPin));
  }
  stop();
  delay(1000);
  int dt = 4000;
  if (choice) {
    turnLeft();
    delay(dt);
    driveForward(mSpeed, mSpeed);
    delay(1000);
  }
  else {
    turnRight();
    delay(dt);
    driveForward(mSpeed, mSpeed);
    delay(1000);
  }
}
