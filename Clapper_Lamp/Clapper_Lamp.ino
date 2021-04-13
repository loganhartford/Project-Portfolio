/*
* Author: Logan Hartford
* Notes: For detection of claps and silence you will notice that the if statment looks for 
*        readings inside or outside of a certain interval. This is because the reads you 
*        get off of the mic ocilate from y+x to y-x, centered around some constate y.
*        The magnitide of x scales with volume. For this reason we cannot simply say 
*        "if read > bound do something", since the spike may acutally be < bound.
*/




// Microphone
int soundPin=A5;
int soundRead;

// Upper and lower bounds for detecting a 'clap'
int low = 450;
int high = 550;

// Upper and lower bounds for detecting silence
int lowLow = 420;
int lowHigh = 520;

// 5V Realy
int relayPin=6; 

// A tracker
int counter=0;

// For toggling the light
int lightStatus=0;

void setup() {
  
  Serial.begin(9600);

  // Pin setups
  pinMode(soundPin, INPUT);
  pinMode(relayPin, OUTPUT);
  
}

void loop() {
  // Read the mic
  soundRead=analogRead(soundPin);  
  Serial.println(soundRead);

  // Detection of the first clap
  if ((soundRead < low || soundRead > high) && (counter==0)) {
    counter=1;
    // This delay lets the first clap ring out before 
    // trying to detect silence.
    delay(75);
  }

  // Detection of silence between claps
  if (counter==1) {
    for (int i=0; i<25; i++) {
      delay(1);
      soundRead=analogRead(soundPin);
      Serial.println(soundRead);
      if (soundRead < lowLow || soundRead > lowHigh) {
        counter=0;
        break;
      }
      else {
        counter=2;
      }
    }
  }

  // Detection of second clap
  if (counter == 2) {
    for (int i = 0; i<200; i++) {
      delay(1);
      soundRead=analogRead(soundPin);
      Serial.println(soundRead);
      if (soundRead < low || soundRead > high) {
        counter =3;
        break;
      }
      else {
        counter = 0;
      }      
    }
  }

  // Toggle the light on or off
  if (counter==3 && lightStatus==0) {
    digitalWrite(relayPin, LOW);
    lightStatus=1;
    counter=0;
    Serial.println("ON");
    delay(500);
  }
  else if (counter==3 && lightStatus==1) {
    digitalWrite(relayPin, HIGH);
    lightStatus=0;
    counter=0;
    Serial.println("OFF");
    delay(500);
  }



}
