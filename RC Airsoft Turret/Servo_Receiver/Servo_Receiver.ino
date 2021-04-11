#include <Servo.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24_config.h>
#include <SPI.h>

//Servo Setup
Servo bigServo;
int servoPin = 6;
int bigPos = 92;
// Upper and lower bounds for tilt
int upper = 120; 
int lower = 55;

Servo smallServo;
int smallServoPin = 2;
int smallPos = 0;
int firePos = 70;

Servo smallServo2;
int smallServoPin2 = 3;
int rest = 80;
int firePos2 = 80 - firePos;

// Reads from the RC
int xRead;
int yRead;
int fireRead;
int flashRead;

// Radio Setup
RF24 radio(7, 8);
RF24Network network(radio);
const uint16_t this_node = 02;

// LEDs for flashlight
int led1 = A4;
int led2 = A5;
int led3 = A3;

// Laser
int laser = A1;


void setup() {
  Serial.begin(9600);
  
  // Radio Receiver Init
  SPI.begin();
  radio.begin();
  network.begin(108, this_node);
  

  // Initialize servos
  bigServo.attach(servoPin);
  bigServo.write(bigPos);
  
  smallServo.attach(smallServoPin);
  smallServo.write(smallPos);
  
  smallServo2.attach(smallServoPin2);
  smallServo2.write(rest);

  // LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Laser
  pinMode(laser, OUTPUT);
  
}

void loop() {
  // Refreshes the network
  network.update();
  // Read the transmission
  while (network.available()) {
    // Reading transmision
    int dataArray[4] = {};
    RF24NetworkHeader header;
    network.read(header, &dataArray, sizeof(dataArray));
    
    // Assigning data from transmission
    xRead = dataArray[0];
    yRead = dataArray[1];
    fireRead = dataArray[2];
    flashRead = dataArray[3];

    // Controlling Big Servo
  if (xRead > 900) {
    bigPos += 1;
    if (bigPos > upper) {
      bigPos = upper;
      
    }
    bigServo.write(bigPos);
  }
  else if (xRead < 100) {
    bigPos -= 1;
    if (bigPos < lower) {
      bigPos = lower;
      
    }
    bigServo.write(bigPos);
  }
  
   // Test prints
    Serial.print(xRead);
    Serial.print("   ");
    Serial.print(yRead);
    Serial.print("   ");
    Serial.print(fireRead);
    Serial.print("   ");
    Serial.println(flashRead);      
  }

  // Flashlight and Laser
  if (flashRead == 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    // Laser
    digitalWrite(laser, HIGH);
  }
  else if (flashRead == 0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    // Laser
    digitalWrite(laser, LOW);
  }

  // Firing
  if (fireRead == 0) {
    smallServo.write(firePos);
    smallServo2.write(firePos2);
  }
  else if (fireRead == 1) {
    smallServo.write(smallPos);
    smallServo2.write(rest);
  }
  
}
