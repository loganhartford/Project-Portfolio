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
#define LED 13    // On board or external LED

#define PHOTO A0  // PHOTO Resisotr Input
#define POT_1 A1  // Potentiometer 1 Input

// Constants

// Variables
uint16_t beers = 0;
volatile bool motion_detected = 0;




/*
 *        Function Prototypes
 */
void init_screen(void);         // Reads in initial EEPROM values and displays them
uint16_t update_count(void);    // Reads in EEPROM values, increments and the stores them
void update_screen(int beers);  // Updates screen with current number of beers
void analog_reads(void);        // Reads all analog inputs
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
  pinMode(LED, OUTPUT); // On board or external LED


  // Initialize the screen for this application
  init_screen();
  
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
  uint8_t data[4];
  for (int i = 0; i<4; i++)
  {
    // Read in the counter data from EEPROM
    data[i] = EEPROM.read(i);
    // Check to see if the address has been written to before
    if (data[i] == 255)   // 255 is default value
    {
      // if it has not been written to before, set to 0
      data[i] = 0;
      EEPROM.write(i, data[i]);
    }
  }
  // Create a single int from data
  uint8_t ones = data[0];
  uint8_t tens = data[1];
  uint8_t hundreds = data[2];
  uint8_t thousands = data[3];
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
  uint8_t ones = EEPROM.read(0);
  uint8_t tens = EEPROM.read(1);
  uint8_t hundreds = EEPROM.read(2);
  uint8_t thousands = EEPROM.read(3);

  // Turn into a single integer
  temp = ones + (10*tens) + (100*hundreds) + (1000*thousands);
  temp++;  // Increment the counter
  // Turn back into 3 bytes of data
  ones = temp%10;
  tens = ((temp%100) - ones)/10;
  hundreds = ((temp%1000) - tens - ones)/100;
  thousands = (temp - hundreds - tens - ones)/1000;

  // Store new value in EEPROM
  EEPROM.write(0, ones);
  EEPROM.write(1, tens);
  EEPROM.write(2, hundreds);
  EEPROM.write(3, thousands);
  return temp;
}

/*
 * Updates the LCD screen with the current number of beers
 * and they're equivalent scrap value.
 */
void update_screen(int beers)
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
