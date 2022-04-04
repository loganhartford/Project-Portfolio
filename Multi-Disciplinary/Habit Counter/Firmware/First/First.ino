#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);



const int resetPin = 2;
const int mPin = 3;
const int jPin = 5+;
const int pPin = 6;
const int cPin = 7;
const int lightPin = A3;

int m = 0;
int j= 0;
int p = 0;
int c = 0;

int thresh = 50;

const int db = 300;




void setup() {
  Serial.begin(9600);
  
  lcd.begin();
  lcd.backlight();

  pinMode(resetPin, INPUT);
  pinMode(mPin, INPUT);
  pinMode(jPin, INPUT);
  pinMode(pPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(lightPin, INPUT);

  digitalWrite(resetPin, HIGH);
  digitalWrite(mPin, HIGH);
  digitalWrite(jPin, HIGH);
  digitalWrite(pPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(lightPin, LOW);

  m = readEEPROM(mPin);
  j= readEEPROM(jPin);
  p = readEEPROM(pPin);
  c = readEEPROM(cPin);
}

void loop() {
  readButtons(mPin, jPin, pPin, cPin);
  displayScore(m, j, p, c);
  Serial.println(analogRead(lightPin));
  if (analogRead(lightPin) < thresh) {
    lcd.noDisplay();
    lcd.noBacklight();
  }
  while (analogRead(lightPin) < thresh) {
    Serial.println(analogRead(lightPin));
  }
  lcd.display();
  lcd.backlight();
}

void readButtons(const int mPin, const int jPin, const int pPin, const int cPin) {
  if (!digitalRead(mPin) && !digitalRead(resetPin)) {
    m = clearEEPROM(mPin);
    lcd.clear();
    delay(db);
  }
  else if (!digitalRead(jPin) && !digitalRead(resetPin)) {
    j = clearEEPROM(jPin);
    lcd.clear();
    delay(db);
  }
  else if (!digitalRead(pPin) && !digitalRead(resetPin)) {
    p = clearEEPROM(pPin);
    lcd.clear();
    delay(db);
  }
  else if (!digitalRead(cPin) && !digitalRead(resetPin)) {
    c = clearEEPROM(cPin);
    lcd.clear();
    delay(db);
  }
  
  if (!digitalRead(mPin)) {
    Serial.println("here");
    m = incEEPROM(mPin);
    delay(db);
  }
  else if(!digitalRead(jPin)) {
    j = incEEPROM(jPin);
    delay(db);
  }
  else if(!digitalRead(pPin)) {
    Serial.println("here");
    p = incEEPROM(pPin);
    delay(db);
  }
  else if(!digitalRead(cPin)) {
    c = incEEPROM(cPin);
    delay(db);
  }
}

void displayScore(int m, int j, int p, int c) {
  lcd.setCursor(0,0);
  lcd.print("M: ");
  lcd.print(m);
  lcd.setCursor(9,0);
  lcd.print("P: ");
  lcd.print(p);
  lcd.setCursor(0, 1);
  lcd.print("J: ");
  lcd.print(j);
  lcd.setCursor(9, 1);
  lcd.print("C: ");
  lcd.print(c);
}

int incEEPROM(int buttonPin) {
  if (buttonPin == mPin) {
    int ones = EEPROM.read(0);
    int tens = EEPROM.read(1);
    int huns =  EEPROM.read(2);
    int mCount = ones + 10 * tens + 100 * huns;
    mCount++;
    ones = mCount % 10;
    tens = (mCount % 100 - ones) / 10;
    huns = (mCount - tens - ones) /100;
    EEPROM.write(0, ones);
    EEPROM.write(1, tens);
    EEPROM.write(2, huns);

    return mCount;
  }
  else if (buttonPin == jPin) {
    int ones = EEPROM.read(3);
    int tens = EEPROM.read(4);
    int huns =  EEPROM.read(5);
    int mCount = ones + 10 * tens + 100 * huns;
    mCount++;
    ones = mCount % 10;
    tens = (mCount % 100 - ones) / 10;
    huns = (mCount - tens - ones) /100;
    EEPROM.write(3, ones);
    EEPROM.write(4, tens);
    EEPROM.write(5, huns);

    return mCount;
  }
  else if (buttonPin == pPin) {
    int ones = EEPROM.read(6);
    int tens = EEPROM.read(7);
    int huns =  EEPROM.read(8);
    int mCount = ones + 10 * tens + 100 * huns;
    mCount++;
    ones = mCount % 10;
    tens = (mCount % 100 - ones) / 10;
    huns = (mCount - tens - ones) /100;
    EEPROM.write(6, ones);
    EEPROM.write(7, tens);
    EEPROM.write(8, huns);

    return mCount;
  }
  else if (buttonPin == cPin) {
    int ones = EEPROM.read(9);
    int tens = EEPROM.read(10);
    int huns =  EEPROM.read(11);
    int mCount = ones + 10 * tens + 100 * huns;
    mCount++;
    ones = mCount % 10;
    tens = (mCount % 100 - ones) / 10;
    huns = (mCount - tens - ones) / 100;
    EEPROM.write(9, ones);
    EEPROM.write(10, tens);
    EEPROM.write(11, huns);

    return mCount;
  }
  else {
    return -1;
  }
}

int clearEEPROM(int buttonPin) {
  if (buttonPin == mPin) {
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);

    return 0;
  }
  else if (buttonPin == jPin) {
    EEPROM.write(3, 0);
    EEPROM.write(4, 0);
    EEPROM.write(5, 0);

    return 0;
  }
  else if (buttonPin == pPin) {
    EEPROM.write(6, 0);
    EEPROM.write(7, 0);
    EEPROM.write(8, 0);
    
    return 0;
  }
  else if (buttonPin == cPin) {
    EEPROM.write(9, 0);
    EEPROM.write(10, 0);
    EEPROM.write(11, 0);

    return 0;
  }
  else {
    return -1;
  }
}

int readEEPROM(int buttonPin) {
  if (buttonPin == mPin) {
    int ones = EEPROM.read(0);
    int tens = EEPROM.read(1);
    int huns =  EEPROM.read(2);
    return ones + 10 * tens + 100 * huns;
  }
  else if (buttonPin == jPin) {
    int ones = EEPROM.read(3);
    int tens = EEPROM.read(4);
    int huns =  EEPROM.read(5);
    return ones + 10 * tens + 100 * huns;
  }
  else if (buttonPin == pPin) {
    int ones = EEPROM.read(6);
    int tens = EEPROM.read(7);
    int huns =  EEPROM.read(8);
    return ones + 10 * tens + 100 * huns;
  }
  else if (buttonPin == cPin) {
    int ones = EEPROM.read(9);
    int tens = EEPROM.read(10);
    int huns =  EEPROM.read(11);
    return ones + 10 * tens + 100 * huns;
  }
  else {
    return -1;
  }
}
