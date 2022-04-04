#include <Servo.h>

const int vertServo = 11;
const int horServo = 3;
const int laser = A2;

const int upper = 20;
const int lower = 55;

const int left = 120;
const int right = 60;

Servo vServo;
Servo hServo;


void setup() {
  Serial.begin(9600);

  pinMode(vertServo, OUTPUT);
  pinMode(horServo, OUTPUT);
  vServo.attach(vertServo);
  hServo.attach(horServo);
  

  pinMode(laser, OUTPUT);
 
}

void loop() {
  digitalWrite(laser, HIGH);
  vServo.write(30);
  hServo.write(90);
  
  int x = 90;
  int y = 30;
  int lastX = 0;
  int lastY = 0;
  int d1 = 0;
  while (true) {
    lastX = x;
    lastY = y;
    x = random(60, 120);
    y = random(20, 55);
    float diffX = lastX - x;
    float diffY = lastY - y;
    int m = max(abs(diffX), abs(diffY));
    for (int i = 0; i < m; i++) {
      hServo.write(int(lastX - (diffX / m * i)));
      vServo.write(int(lastY - (diffY / m * i)));
      delay(m);
    }
    hServo.write(x);
    vServo.write(y);
    if (diffX > diffY) {
      d1 = 2000 + 2000/(left - right) * abs(diffX); 
    }
    else {
      d1 = 2000 + 2000/(upper - lower) * abs(diffY);
    }
    delay(d1);
  }
}
