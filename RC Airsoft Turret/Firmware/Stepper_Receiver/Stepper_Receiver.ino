#include <Stepper.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24_config.h>
#include <SPI.h>

// Radio Setup
RF24 radio(7, 8);
RF24Network network(radio);
const uint16_t this_node = 01;


// Stepper Setup
int stepsPerRevolution=2048;
Stepper myStepper(stepsPerRevolution, 4,10,9,6);
int motSpeed=10;

// Reads from the RC
int xRead;
int yRead;
int fireRead;
int flashRead;

// Underglow lights
int redPin = A3;
int redPin2 = A4;

void setup() {

  Serial.begin(9600);

  // Radio Receiver Init
  SPI.begin();
  radio.begin();
  network.begin(108, this_node);

  // Init Stepper
  myStepper.setSpeed(motSpeed);

  // Underglow pins
  pinMode(redPin, OUTPUT);
  pinMode(redPin2, OUTPUT);
  
}

void loop() {
  // Refresh the network
  network.update();
  // Read the transmission
  while (network.available()) {
    // Read the transmission
    int dataArray[4] = {};
    RF24NetworkHeader header;
    network.read(header, &dataArray, sizeof(dataArray));
    
    // Assign data from transmission
    xRead = dataArray[0];
    yRead = dataArray[1];
    fireRead = dataArray[2];
    flashRead = dataArray[3];

    // Test prints
    Serial.print(xRead);
    Serial.print("   ");
    Serial.print(yRead);
    Serial.print("   ");
    Serial.print(fireRead);
    Serial.print("   ");
    Serial.println(flashRead);
         
  }

  // Control the stepper
  if (yRead > 600) {
    myStepper.step(20);
  }
  else if (yRead < 400) {
    myStepper.step(-20);
  }

  // Turn the underglow on or off
  if (flashRead == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(redPin2, HIGH);
  }
  if (flashRead == 0) {
    digitalWrite(redPin, LOW);
    digitalWrite(redPin2, LOW);
  }

}
