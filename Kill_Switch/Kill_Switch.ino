#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Create Servo Object
Servo servo;

// Connect to Wi-Fi and Blynk project
char auth[] = "VhrKbeuXlAiMNeFXjsO5Gb1Xfgx2CtVa";
char ssid[] = "Cheeseburger Mesh";
char pass[] = "Vatalaro67";

void setup() {
  
  // Serial Monitor
  Serial.begin(9600);

  // Blynk init
  Blynk.begin(auth, ssid, pass);

  // Servo Init
  servo.attach(2); // NodeMCU D4 pin
}

void loop() {
  // Keeps connection to project
  Blynk.run();
  
}

// Reads app data from V1 and writes it to the servo
BLYNK_WRITE(V1){
   servo.write(param.asInt());
}
