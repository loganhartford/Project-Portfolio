#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24_config.h>
#include <SPI.h>

// Create NRF network
RF24 radio(5, 6);
RF24Network network(radio);

// Creating addresses for all of the devices
const uint16_t this_node = 00;
const uint16_t node01 = 01;
const uint16_t node02 = 02;

// Control pins
int xPin = A2;
int yPin = A4;
int firePin = A1;
int flashPin = A0;
// Control Reads
int xRead;
int yRead;
int fireRead;
int flashRead;

// Reads for firing and flashlight
int fireVal=0;
int flashVal=0;

void setup() {
  // Serial Setup
  Serial.begin(9600);
  // Init NRF Network
  SPI.begin();
  radio.begin();
  network.begin(108, this_node);

  // Set-up for control reads
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(flashPin, INPUT);
  
  digitalWrite(firePin, HIGH);
  digitalWrite(flashPin, HIGH);
  

}

void loop() {
  // Refreshes the NRF Network
  network.update();
  // Reads Controls 
  xRead=analogRead(xPin);
  yRead=analogRead(yPin);
  fireRead=digitalRead(firePin);
  flashRead=digitalRead(flashPin);

  // Toggle for flashlight and laser
  if (flashRead == 0 && flashVal == 0) {
    flashVal = 1;
    delay(500);
  }
  else if (flashRead == 0 && flashVal == 1) {
    flashVal = 0;
    delay(500);
  }

  // Packaging the data for transmission
  int dataArray[4] = {xRead, yRead, fireRead, flashVal};
  // Sending the data to the stepper receiver
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, &dataArray, sizeof(dataArray));
  // sending the data to the servo receiver.
  RF24NetworkHeader header2(node02);
  bool ok2 = network.write(header2, &dataArray, sizeof(dataArray));

//  // Test Prints
//  Serial.print(xRead);
//  Serial.print("   ");
//  Serial.print(yRead);
//  Serial.print("   ");
//  Serial.print(fireRead);
//  Serial.print("   ");
//  Serial.println(flashVal);
}
