#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

// Blynk Connection
char auth[] = "y2i79PJVVn64Lj2PpXQJa-EkpqCntwa0";
char ssid[] = "Cheeseburger";
char pass[] = "Mylogan1";

// DHT Init
int DHTPIN = 2;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Soil Moisture Stuff
int moistPin = A0;
float wet = 300;
float dry = 650;


// Timer for sending data
BlynkTimer timer;

// Servo Init
int servo1 = D6;
int servo2 = D7;
Servo Servo1;
Servo Servo2;
int s1Pos = 82;
int s2Pos = 20;

// The temperature range for greenhouse
float openTemp = 40;
float closeTemp = 30;


void setup() {
  // Serial Monitor
  Serial.begin(9600);

  // Start DHT
  dht.begin();
  pinMode(DHTPIN, INPUT);

  // Soil Moisture
  pinMode(moistPin, INPUT);

  // Servo Setup
  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  
  Servo1.attach(servo1);
  Servo2.attach(servo2);
  // initial positions
  Servo1.write(s1Pos);
  Servo2.write(s2Pos);

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  

  
}

void loop() {
  // Sends data to blynk 
  Blynk.run();
  timer.run();

  // Read the DHT
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  int moisture = analogRead(A0);
  
  // Prints
  Serial.print(humidity);
  Serial.print("   ");
  Serial.print(temp);
  Serial.print("   ");
  Serial.println(moisture);

  // Opens hatch if its too hot
  if (temp > openTemp) {
    while (s1Pos >= 0) {
    delay(30);
    s1Pos--;
    s2Pos++;
    Servo1.write(s1Pos);
    Servo2.write(s2Pos);
    }
  }
  // Closes it once it cools down
  else if (temp < closeTemp) {
    while (s1Pos <= 82) {
    delay(30);
    s1Pos++;
    s2Pos--;
    Servo1.write(s1Pos);
    Servo2.write(s2Pos);
    }
  }
}

// sendSensor() reads data from the dht and sends it to the blynk app
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float moistureLevel = ((dry - analogRead(A0)) / (dry - wet)) * 10; 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, moistureLevel);
}
