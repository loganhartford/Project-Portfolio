#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Code Versions
#define DEBUG

// Create the LCB object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
#define LASER_PHOTO_AN    A0  // Analog read of laser photoresitor
#define POT               A1  // Potentionmeter
#define LIGHT_PHOTO       A2  // Light level photo resistor

#define RESET_BUTTON      2   // User input mom switch
#define LASER_PHOTO       3   // Digital read of laser photoresitor
#define BUZZ              4   // Buzzer
#define RED               5   // RED diode of RGB LED
#define GREEN             6   // GREEN diode of RGB LED
#define BUZZ_BUTTON       7   // Button which can manually activate buzzer
#define BLUE              9   // BLUE diode of RGB LED
#define LASER             11  // Laser diode
#define LED               13  // On board or external LED

// Constants
// EEPROM memory locations
#define ONES 0
#define TENS 1
#define HUNDREDS 2
#define THOUSANDS 3
#define UPDATE_REQ 9

// Variables
int16_t beers = 0;
volatile bool motion_detected = 0;
int16_t light_level_low_pass = 0;
int16_t pot_low_pass = 0;
bool reset_requested = 0;




/*
          Function Prototypes
*/
void init_screen(void);         // Reads in initial EEPROM values and displays them
uint16_t update_count(void);    // Reads in EEPROM values, increments and the stores them
void update_screen(int beers);  // Updates screen with current number of beers
bool lights_off(void);        // Reads all analog inputs
void RGB_LED(uint8_t red, uint8_t green, uint8_t blue);
void meme_detector(int16_t beers);
void button_ISR(void);          // Services momentary switch
void laser_ISR(void);          // Services motion detector

void setup()
{
#ifdef DEBUG
  // Initialize the Serial monintor
  Serial.begin(115200);
#endif

  // Initialize the LCD
  lcd.begin();
  lcd.backlight();

  // External interrupt for button
  attachInterrupt(digitalPinToInterrupt(RESET_BUTTON), button_ISR, RISING);

  // External interrup for motion sensor
  attachInterrupt(digitalPinToInterrupt(LASER_PHOTO), laser_ISR, RISING);

  // Digital Pin Set Up
  pinMode(BUZZ, OUTPUT);      // Buzzer
  pinMode(RED, OUTPUT);       // RED pin of REG LED
  pinMode(GREEN, OUTPUT);     // GREEN pin of REG LED
  pinMode(BUZZ_BUTTON, INPUT);// Button which manually controls buzzer
  pinMode(BLUE, OUTPUT);      // BLUE pin of REG LED
  pinMode(LASER, OUTPUT);     // Laser diode
  pinMode(LED, OUTPUT);       // On board or external LED

  // Set initial pin states
  digitalWrite(BUZZ, LOW);
  digitalWrite(LASER, HIGH);
  digitalWrite(LED, LOW);
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);

  // Initialize the screen for this application
  init_screen();

  // Checks to see if the code needs to be updated before it will work
  if (EEPROM.read(UPDATE_REQ) == 111)
  {
    // This will throw the code into an infinite loop
    meme_detector(9999);
  }
}

void loop()
{
  // Halt program while the lights are off.
  while(lights_off());
  
  if (motion_detected)
  {
    beers = update_count();
    update_screen(beers);
    motion_detected = 0;
  }

  if (reset_requested)
  {
    reset_req();
  }
  
  if (digitalRead(BUZZ_BUTTON))
  {
    digitalWrite(BUZZ, HIGH);
  }
  else
  {
    digitalWrite(BUZZ, LOW);
  }
}


/*
          Functions
*/

/*
   Reads in counter from EEPROM and consolidates it into a global
   variable. Checks to see if EEPROM has been accessed on the
   device before and deals with it accordingly. Makes a function
   call to update_screen to display the initial beer count.
*/
void init_screen(void)
{
  // Read in data from EEPROM
  uint8_t ones = EEPROM.read(ONES);
  uint8_t tens = EEPROM.read(TENS);
  uint8_t hundreds = EEPROM.read(HUNDREDS);
  uint8_t thousands = EEPROM.read(THOUSANDS);

  // Check to see if the addresses have been written to before, 255 is default.
  if ((ones == 255) || (tens == 255) || (hundreds == 255) || (thousands == 255))
  {
    // Store new value in EEPROM
    EEPROM.write(ONES, 0);
    EEPROM.write(TENS, 0);
    EEPROM.write(HUNDREDS, 0);
    EEPROM.write(THOUSANDS, 0);
  }
  // Create a single int from data
  beers = ones + (10 * tens) + (100 * hundreds) + (1000 * thousands);

  // Update the screen with the initial counter
  update_screen(beers);
}

/*
   Reads in the current counter form EEPROM, consolidates it
   and then increments the data. The incremented data is then
   expanded and written back into the EEPROM. The consolidated,
   incremented data is returned.
*/
uint16_t update_count(void)
{
  uint16_t temp;
  // Read in values from EEPROM
  uint8_t ones = EEPROM.read(ONES);
  uint8_t tens = EEPROM.read(TENS);
  uint8_t hundreds = EEPROM.read(HUNDREDS);
  uint8_t thousands = EEPROM.read(THOUSANDS);

  // Turn into a single integer
  temp = ones + (10 * tens) + (100 * hundreds) + (1000 * thousands);
  temp++;  // Increment the counter
  // Turn back into 3 bytes of data
  ones = temp % 10;
  tens = ((temp % 100) - ones) / 10;
  hundreds = ((temp % 1000) - tens - ones) / 100;
  thousands = (temp - hundreds - tens - ones) / 1000;

  // Store new value in EEPROM
  EEPROM.write(ONES, ones);
  EEPROM.write(TENS, tens);
  EEPROM.write(HUNDREDS, hundreds);
  EEPROM.write(THOUSANDS, thousands);

  // Check to make sure values were written into EEPROM correctly
  if ((EEPROM.read(ONES) == ones) || (EEPROM.read(TENS) == tens) ||
      (EEPROM.read(HUNDREDS) == hundreds) || (EEPROM.read(THOUSANDS) == thousands))
  {
    // Beep the buzzer for succees
    digitalWrite(BUZZ, HIGH);
    delay(75);
    digitalWrite(BUZZ, LOW);
    return temp;
  }
  else
  {
    // One long beep for failure
    digitalWrite(BUZZ, HIGH);
    delay(500);
    digitalWrite(BUZZ, LOW);
    return -1;
  }
}

/*
   Updates the LCD screen with the current number of beers
   and they're equivalent scrap value.
*/
void update_screen(int16_t beers)
{
  uint8_t space = 0;
  if (beers < 10)
  {
    space = 3;
  }
  else if (beers < 100)
  {
    space = 2;
  }
  else if (beers < 1000)
  {
    space = 1;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beers Drank:");
  lcd.setCursor((12 + space), 0);
  lcd.print(beers);

  lcd.setCursor(0, 1);
  lcd.print("Scrap:");
  lcd.setCursor((9 + space), 1);
  float scrap = beers * 0.1;
  lcd.print("$");
  lcd.print(scrap);
}

/*
   Carries out analog reads on the potentiometers and photoresitor.
   The photo resistor value is proprtional to the brightness of the
   room and is used to detemine if the screen should be on or off.
   Potentiomenter 1's value determines the light threshold for
   turning the screen off.
*/
bool lights_off(void)
{
  uint16_t pot = analogRead(POT);
  uint16_t light_level = analogRead(LIGHT_PHOTO);
//  Serial.print(pot); Serial.print(',');
//  Serial.println(light_level);

  light_level_low_pass = light_level_low_pass + ((light_level - light_level_low_pass)>>8);
  pot_low_pass = pot_low_pass + ((pot - pot_low_pass)>>8);

    Serial.print(pot_low_pass); Serial.print(',');
    Serial.println(light_level_low_pass);

  
  if (light_level_low_pass < pot_low_pass)
  {
    lcd.noBacklight();
    digitalWrite(LASER, LOW);
    motion_detected = 0; // Turning the laser off will cause an unwanted interrupt
    RGB_LED(0,0,0);
    return 1;
  }
  else
  {
    lcd.backlight();
    digitalWrite(LASER, HIGH);
    return 0;
  }
}

/*
 * This fucntion is called when the reset button is pressed. It delivers
 * instructions to the screen which will allow the user to reset the count,
 * or leave it as is.
 */
 void reset_req(void)
 {
    uint32_t time_ms = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press 6x more");
    lcd.setCursor(0, 1);
    lcd.print("to reset (");
    lcd.print(6000 - time);
    
    while (time < 6000)
    {
      delay(1);
      time_ms++;  
    }
 }

/*
   A quick way to change the state of the RGB LED
*/
void RGB_LED(uint8_t red, uint8_t green, uint8_t blue)
{
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

/*
   Detects when the number of beers is some special or funny
   number and does a special animation with lights, screen
   and LED.
*/
void meme_detector(int16_t beers)
{
  // 6
  if (beers == 6)
  {

  }
  // 69
  else if (beers == 69)
  {

  }
  // 420
  else if (beers == 420)
  {

  }
  // 666
  else if (beers == 666)
  {

  }
  // 777
  else if (beers == 777)
  {

  }
  // 1111
  else if (beers == 1111)
  {

  }
  // 6969
  else if (beers == 6969)
  {

  }
  // 9999
  else if (beers == 9999)
  {
    // Code is only designed to handle upto 9999 beers
    RGB_LED(255, 0, 0); // Set LED to red
    lcd.setCursor(0, 0);
    lcd.print("Update Required");
    lcd.setCursor(0, 1);
    lcd.print("Talk to Motto");
    // Wrtie EEPROM update REQ can be detected on start-up
    EEPROM.write(UPDATE_REQ, 111);
    while (1);
  }
}

/*
   This ISR is called each time the momentary switch pushed.
   The button is used to make changes to the device including reseting
   the counter.
*/
void button_ISR(void)
{
  //digitalWrite(RED, digitalRead(RED) ^ 1);
  reset_requested = 1;
}

/*
   This ISR is called each time the motion detector detects motion.
   This is what casues the counter to be incremented and the screen
   updated.
*/
void laser_ISR(void)
{
  motion_detected = 1;
}
