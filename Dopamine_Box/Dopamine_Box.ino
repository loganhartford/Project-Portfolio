// Button pins and states:
int Button1=2;
int Button2=3;
int Button3=4;
int Button4=5;
int Button5=6;

int B1Val;
int B2Val;
int B3Val;
int B4Val;
int B5Val;

// LED pins and states:
int led1=8;
int led2=9;
int led3=10;
int led4=11;
int led5=12;

int led1Val=0;
int led2Val=0;
int led3Val=0;
int led4Val=0;
int led5Val=0;

// Passive buzzer pin
int buzzPin=13;

// Delay for desired notes from buzzer
int c=1915;
int d=1700;
int e=1519;
int f=1432;
int g=1275;
int a=1136;
int b=1014;
int c2=956;

// Photoresistor:
int lightPin=A0;
int lightVal;
int lightLevel=20; // <20 is lights off

// Happy victory noises
int j=0;
int dt=63;
int victory=0;

//RGB setup:
int redPin=A5;
int greenPin=A4;
int bluePin=A3;

void setup() {
  Serial.begin(9600);
  
  // Button Setup
  pinMode(lightPin, INPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  pinMode(Button4, INPUT);
  pinMode(Button5, INPUT);
  
  digitalWrite(Button1, HIGH);
  digitalWrite(Button2, HIGH);
  digitalWrite(Button3, HIGH);
  digitalWrite(Button4, HIGH);
  digitalWrite(Button5, HIGH);

  // LED Setup
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  // RGB Setup
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Buzzer Setup
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  // Read the buttons
  B1Val=digitalRead(Button1);
  B2Val=digitalRead(Button2);
  B3Val=digitalRead(Button3);
  B4Val=digitalRead(Button4);
  B5Val=digitalRead(Button5);

  // Read the photresistor
  lightVal=analogRead(lightPin);
  
  // Turns LEDs off when lights are off.
  if (lightVal < lightLevel) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
  // Turn LEDs back on if lights come back on.
  if (lightVal>lightLevel) {
    if (led1Val==1) {
      digitalWrite(led1, HIGH);
    }
    if (led2Val==1) {
      digitalWrite(led2, HIGH);
    }
    if (led3Val==1) {
      digitalWrite(led3, HIGH);
    }
    if (led4Val==1) {
      digitalWrite(led4, HIGH);
    }
    if (led5Val==1) {
      digitalWrite(led5, HIGH);
    }
    if (victory==1) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 200);
    analogWrite(bluePin, 0);
    }
  }
  
  //What happens when buttons are pushed
  if (B1Val==0) {
    // Turns on the associated green LED
    digitalWrite(led1, HIGH);
    
    // For the duration of the first push, the buzzer sounds a note
    while (B1Val==0 && led1Val==0) {
      // Buzzer sounds a C
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(c);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(c);
      B1Val=digitalRead(Button1); 
    }
    led1Val=1;
  }
  if (B2Val==0) {
    digitalWrite(led2, HIGH);
    while (B2Val==0 && led2Val==0) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(d);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(d);
      B2Val=digitalRead(Button2); 
    }
    led2Val=1;
  }
  if (B3Val==0) {
    digitalWrite(led3, HIGH);
    while (B3Val==0 && led3Val==0) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(e);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(e);
      B3Val=digitalRead(Button3); 
    }
    led3Val=1;
  }
  if (B4Val==0) {
    digitalWrite(led4, HIGH);
    while (B4Val==0 && led4Val==0) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(f);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(f);
      B4Val=digitalRead(Button4); 
    }
    led4Val=1;
  }
  if (B5Val==0) {
    digitalWrite(led5, HIGH);
    while (B5Val==0 && led5Val==0) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(g);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(g);
      B5Val=digitalRead(Button5); 
    }
    led5Val=1;
  }

  // Reset the box.
  if (B1Val==0 && B3Val==0) {
    // Delay for button bounce
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    analogWrite(greenPin, 0);
    led1Val=0;
    led2Val=0;
    led3Val=0;
    led4Val=0;
    led5Val=0;
    victory=0;
  }
  
  //What happens when all of the buttons have been pushed:
  if (led1Val==1 && led2Val==1 && led3Val==1 && led4Val==1 && led5Val==1 && victory==0) {
    // LED Victory Animation
    delay(200);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(100);
    digitalWrite(led5, HIGH);
    delay(150);
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);
    digitalWrite(led1, HIGH);
    
    
    delay(500);
    // First note of victory noise
    while (j<24) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(g);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(g);
      j+=1 ;
    }
    j=0;
    delay(dt);
    
    // Second note and first flash
    while (j<24) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(g);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(g);
      analogWrite(redPin, 200);
      analogWrite(greenPin, 200);
      analogWrite(bluePin, 0);
      j+=1 ;
    }
    j=0;
    delay(dt);

    // Third note and second flash
    while (j<24) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(g);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(g);
      analogWrite(redPin, 0);
      analogWrite(greenPin, 200);
      analogWrite(bluePin, 200);
      j+=1 ;
    }
    j=0;
    delay(dt);

    // Fourth note and third flash
    while (j<80) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(c2);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(c2);
      analogWrite(redPin, 200);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 200);
      j+=1 ;
    }
    // After animation and victory noise is done, the RGB led is left on green.
    victory=1;
    analogWrite(redPin, 0);
    analogWrite(greenPin, 200);
    analogWrite(bluePin, 0);
  } 
}
