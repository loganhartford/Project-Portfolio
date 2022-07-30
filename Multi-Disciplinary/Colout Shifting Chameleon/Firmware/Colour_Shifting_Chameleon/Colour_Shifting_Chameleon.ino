#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define commonAnode false 
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// LED pins
int redpin = 3;                                                  
int greenpin = 5;                                                
int bluepin = 6;
int redpin2 = 9;                                                  
int greenpin2 = 10;                                                
int bluepin2 = 11;

// Motion Sensor
int motionPin = 4;
int motion;

// Write values
int red;
int green;
int blue;

// delays
int dt=12;
int dt2=4;

void setup() {
  Serial.begin(9600);
  // LED Setup
  pinMode(redpin, OUTPUT);                                        
  pinMode(greenpin, OUTPUT);                                       
  pinMode(bluepin, OUTPUT);
  pinMode(redpin2, OUTPUT);                                        
  pinMode(greenpin2, OUTPUT);                                       
  pinMode(bluepin2, OUTPUT);
  
  pinMode(motionPin, INPUT);
  
  // RGB sensor init
  tcs.begin();
  // Creation of gammatable
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
  }
}

void loop() {
  // Read motion sensor
  motion = digitalRead(motionPin);
  
  //start at green
  red=0;
  green=255;
  blue=0;

  //Fade to yellow
  while (red < 255) {
    motion = digitalRead(motionPin);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    red++;
  }
  // To red
  while (green > 0) {
    motion = digitalRead(motionPin);
    Serial.println(motion);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    green--;
  }
  //To magenta
  while (blue < 255) {
    motion = digitalRead(motionPin);
    Serial.println(motion);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    blue++;
  }
  // To Blue
  while (red > 0) {
    motion = digitalRead(motionPin);
    Serial.println(motion);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    red--;
  }
  // To cyan
  while (green < 255) {
    motion = digitalRead(motionPin);
    Serial.println(motion);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    green++;
  }
  // Back to green
  while (blue > 0) {
    motion = digitalRead(motionPin);
    Serial.println(motion);
    if (motion) {
      break;
    }
    
    delay(dt);
    analogWrite(redpin, red);
    analogWrite(greenpin, green);
    analogWrite(bluepin, blue);
    analogWrite(redpin2, red);
    analogWrite(greenpin2, green);
    analogWrite(bluepin2, blue);
    blue--;
  }
  
// Motion Sensor Detecting Stuff!
  if (motion) {  
    delay(500);
    // Reading RGB Sensor    
    uint16_t clear, red2, green2, blue2;
    tcs.setInterrupt(false);                                        
    delay(60);                                                       
    tcs.getRawData(&red2, &green2, &blue2, &clear);                      
    tcs.setInterrupt(true);
    
    uint32_t sum = clear;
    float r, g, b;

    //Setting up the colours we want to fade to
    r = red2; r /= sum;
    g = green2; g /= sum;
    b = blue2; b /= sum;
    r *= 256; g *= 256; b *= 256;
    float finalRed = gammatable[(int)r] * 2.7; 
    float finalGreen = gammatable[(int)g] * 4.2;
    float finalBlue = gammatable[(int)b]  * 6;
    // Setting limits on colours
    if (finalRed > 255) {
      finalRed=255;
    }
    if (finalGreen > 255) {
      finalGreen=255;
    }
    if (finalBlue > 255) {
      finalBlue=255;
    }
    // Test Prints
    Serial.print((int)finalRed);
    Serial.print("   ");
    Serial.print((int)finalGreen);
    Serial.print("   ");
    Serial.println((int)finalBlue);

    float initialRed = red;
    float initialGreen = green;
    float initialBlue = blue;

    // Fade into the reading
    for (int i=0; i<255; i++) {
      delay(dt2);
      float currentRed = ((float)initialRed * (255 - i) + (finalRed * i))/255;
      float currentGreen = ((float)initialGreen * (255 - i) + (finalGreen * i))/255;
      float currentBlue = ((float)initialBlue * (255 - i) + (finalBlue * i))/255;
    
      analogWrite(redpin, (int)currentRed);
      analogWrite(greenpin, (int)currentGreen);
      analogWrite(bluepin, (int)currentBlue);
      analogWrite(redpin2, (int)currentRed);
      analogWrite(greenpin2, (int)currentGreen);
      analogWrite(bluepin2, (int)currentBlue); 
    }
   
    
    analogWrite(redpin, (int)finalRed);                          
    analogWrite(greenpin, (int)finalGreen);                        
    analogWrite(bluepin, (int)finalBlue);
    analogWrite(redpin2, (int)finalRed);                          
    analogWrite(greenpin2, (int)finalGreen);                        
    analogWrite(bluepin2, (int)finalBlue);
    delay(5000); 

    // Fade from reading back to green
    initialRed = finalRed;
    initialGreen = finalGreen;
    initialBlue = finalBlue;
    
    finalRed=0;
    finalGreen=255;
    finalBlue=0;

    for (int i=0; i<255; i++) {
      delay(dt2);
      float currentRed = ((float)initialRed * (255 - i) + (finalRed * i))/255;
      float currentGreen = ((float)initialGreen * (255 - i) + (finalGreen * i))/255;
      float currentBlue = ((float)initialBlue * (255 - i) + (finalBlue * i))/255;
    
      analogWrite(redpin, (int)currentRed);
      analogWrite(greenpin, (int)currentGreen);
      analogWrite(bluepin, (int)currentBlue);
      analogWrite(redpin2, (int)currentRed);
      analogWrite(greenpin2, (int)currentGreen);
      analogWrite(bluepin2, (int)currentBlue); 
    }
  } 
}
