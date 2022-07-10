#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Code Versions
#define DEBUG

// Create the LCB object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
#define BUTTON 2  // User input mom switch
#define MOTION 3  // Motion sensor input
#define BUZZ 4    // Buzzer
#define RED 5     // RED diode of RGB LED
#define GREEN 6   // GREEN diode of RGB LED
#define BLUE 9    // BLUE diode of RGB LED
#define LED 13    // On board or external LED

#define PHOTO A0  // PHOTO Resisotr Input
#define POT_1 A1  // Potentiometer 1 Input

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




/*
 *        Function Prototypes
 */
void init_screen(void);         // Reads in initial EEPROM values and displays them
uint16_t update_count(void);    // Reads in EEPROM values, increments and the stores them
void update_screen(int beers);  // Updates screen with current number of beers
void analog_reads(void);        // Reads all analog inputs
void RGB_LED(uint8_t red, uint8_t green, uint8_t blue);
void meme_detector(int16_t beers);
void button_ISR(void);          // Services momentary switch
void motion_ISR(void);          // Services motion detector

void setup() 
{
  #ifdef DEBUG
  // Initialize the Serial monintor
  Serial.begin(115200);
  #endif
  
  // Initialize the LCD
  lcd.init(); 
  lcd.backlight();

  // External interrupt for button
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_ISR, RISING);

  // External interrup for motion sensor
  attachInterrupt(digitalPinToInterrupt(MOTION), motion_ISR, RISING);

  // Pin Set Up
  pinMode(BUZZ, OUTPUT);  // Buzzer
  pinMode(RED, OUTPUT);   // RED pin of REG LED
  pinMode(GREEN, OUTPUT); // GREEN pin of REG LED
  pinMode(BLUE, OUTPUT);  // BLUE pin of REG LED
  pinMode(LED, OUTPUT);   // On board or external LED
  
  digitalWrite(BUZZ, LOW);
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
  if (motion_detected)
  {
      beers = update_count();
      update_screen(beers);
      motion_detected = 0;
  }
  analog_reads();
}


/*
 *        Functions
 */

/*
 * Reads in counter from EEPROM and consolidates it into a global
 * variable. Checks to see if EEPROM has been accessed on the
 * device before and deals with it accordingly. Makes a function 
 * call to update_screen to display the initial beer count.
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
  beers = ones + (10*tens) + (100*hundreds) + (1000*thousands);
  
  // Update the screen with the initial counter
  update_screen(beers);
}

/*
 * Reads in the current counter form EEPROM, consolidates it 
 * and then increments the data. The incremented data is then 
 * expanded and written back into the EEPROM. The consolidated,
 * incremented data is returned.
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
  temp = ones + (10*tens) + (100*hundreds) + (1000*thousands);
  temp++;  // Increment the counter
  // Turn back into 3 bytes of data
  ones = temp%10;
  tens = ((temp%100) - ones)/10;
  hundreds = ((temp%1000) - tens - ones)/100;
  thousands = (temp - hundreds - tens - ones)/1000;

  // Store new value in EEPROM
  EEPROM.write(ONES, ones);
  EEPROM.write(TENS, tens);
  EEPROM.write(HUNDREDS, hundreds);
  EEPROM.write(THOUSANDS, thousands);

  // Check to make sure values were written into EEPROM correctly
  if((EEPROM.read(ONES) == ones) || (EEPROM.read(TENS) == tens) || 
  (EEPROM.read(HUNDREDS) == hundreds) || (EEPROM.read(THOUSANDS) == thousands))
  {
    // Beep the buzzer twice for succees
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
 * Updates the LCD screen with the current number of beers
 * and they're equivalent scrap value.
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
  lcd.setCursor(0,0);
  lcd.print("Beers Drank:");
  lcd.setCursor((12+space),0);
  lcd.print(beers);
  
  lcd.setCursor(0,1);
  lcd.print("Scrap:");
  lcd.setCursor((9+space),1);
  float scrap = beers * 0.1;
  lcd.print("$");
  lcd.print(scrap);
}

/*
 * Carries out analog reads on the potentiometers and photoresitors.
 * The photo resistor value is proprtional to the brightness of the
 * room and is used to detemine if the screen should be on or off.
 * Potentiomenter 1's value determines the light threshold for 
 * turning the screen off.
 */
void analog_reads(void)
{
  uint16_t pot_1 = analogRead(POT_1);
  uint16_t light_level = analogRead(PHOTO);
  Serial.print(pot_1); Serial.print(',');
  Serial.println(light_level);

  if (light_level > pot_1)
  {
    lcd.noBacklight();
  }
  else
  {
    lcd.backlight();
  }
}

/*
 * A quick way to change the state of the RGB LED
 */
void RGB_LED(uint8_t red, uint8_t green, uint8_t blue)
{
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

/*
 * Detects when the number of beers is some special or funny
 * number and does a special animation with lights, screen
 * and LED.
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
    lcd.setCursor(0,0);
    lcd.print("Update Required");
    lcd.setCursor(0,1);
    lcd.print("Talk to Motto");
    // Wrtie EEPROM update REQ can be detected on start-up
    EEPROM.write(UPDATE_REQ, 111);
    while (1);
  }
}

/*
 * This ISR is called each time the momentary switch pushed.
 * The button is used to make changes to the device including reseting
 * the counter.
 */
void button_ISR(void)
{
  digitalWrite(LED, digitalRead(LED)^1);
}

/*
 * This ISR is called each time the motion detector detects motion.
 * This is what casues the counter to be incremented and the screen 
 * updated.
 */
void motion_ISR(void)
{
  motion_detected = 1;
}
