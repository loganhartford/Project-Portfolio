
// LED Pins
const int green = 13;
const int yellow1 = A1;
const int yellow2 = A0;
const int yellow3 = A2;
const int red1 = A4;
const int red2 = A3;

// Capacitative Soil Moisture Pin
const int moist = A5;

// Observed wet and dry values of this particular sensor
const int wet = 203;
const int dry = 495;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(green, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  
  pinMode(moist, INPUT);
}

void loop() {

  // Read the soil moisture
  int soil = analogRead(moist);
  Serial.println(soil);

  // Create 6 'units' to signify the 6 LEDs
  int unit = (dry - wet)/6;

  // Turns combination of LEDs on based soil moisture readings
  if (soil < wet + unit) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    digitalWrite(yellow3, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
  if (wet + unit < soil && soil < wet + 2*unit) {
    digitalWrite(green, LOW);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    digitalWrite(yellow3, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
  if (wet + 2*unit < soil && soil < wet + 3*unit) {
    digitalWrite(green, LOW);
    digitalWrite(yellow1, LOW);
    digitalWrite(yellow2, HIGH);
    digitalWrite(yellow3, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
  if (wet + 3*unit < soil && soil < wet + 4*unit) {
    digitalWrite(green, LOW);
    digitalWrite(yellow1, LOW);
    digitalWrite(yellow2, LOW);
    digitalWrite(yellow3, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
  if (wet + 4*unit < soil && soil < wet + 5*unit) {
    digitalWrite(green, LOW);
    digitalWrite(yellow1, LOW);
    digitalWrite(yellow2, LOW);
    digitalWrite(yellow3, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
  if (wet + 5*unit < soil) {
    digitalWrite(green, LOW);
    digitalWrite(yellow1, LOW);
    digitalWrite(yellow2, LOW);
    digitalWrite(yellow3, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(red2, HIGH);

    // When soil is completely dry, blinks last LED red
    while (wet + 5*unit < soil) {
      soil = analogRead(moist);
      digitalWrite(red2, HIGH);
      delay(500);
      digitalWrite(red2, LOW);
      if (!(wet + 5*unit < soil)) {
        break;
      }
      delay(1000);
    }
  }
}
