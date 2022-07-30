#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Code Versions
//#define DEBUG // Defining enabled serial monitor outputs

// Create the LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*
 *               Constants
 */
// Pins
#define LASER_PHOTO_AN    A0  // Analog read of laser photoresitor
#define POT               A1  // Potentionmeter
#define LIGHT_PHOTO       A2  // Light level photo resistor

#define RESET_BUTTON      2   // User input mom switch
#define LASER_PHOTO       3   // Digital read of laser photoresitor
#define BUZZ              4   // Buzzer
#define RED               5   // RED diode of RGB LED
#define GREEN             6   // GREEN diode of RGB LED
#define BUTTON       7   // Button which can manually activate buzzer
#define BLUE              9   // BLUE diode of RGB LED
#define LASER             11  // Laser diode
#define LED               13  // On board or external LED

// EEPROM memory locations
#define ONES 0
#define TENS 1
#define HUNDREDS 2
#define THOUSANDS 3
#define UPDATE_REQ 9

/*
 *               Variables
 */
// Universal Variables
int16_t beers = 0;  // Total count of the number of beers, stored in EEPROM
uint8_t red = 25;    // Stores the state of the RED diode
uint8_t green = 170;  // Stores the state of the GREEN diode
uint8_t blue = 250;   // Stores the state of the BLUE diode
bool RGB_LED_on = 1;

// lights_off() variables
bool lights_off_global = 1;
float light_level_low_pass = 0; // Low-pass filter of the analog read of the photoresistor
float pot_low_pass = 0;         // Low-pass filter of the analog read of the pot

int8_t red_dir = 1;
int8_t green_dir = 1;
int8_t blue_dir = 1;


// ISR Variables
volatile bool reset_requested = 0;  // Indicated the reset button has been pressed.
volatile bool can_detected = 0;     // Indicates if a can has been detected by the laser
volatile bool pressed = 0;
volatile uint8_t presses = 0;


/*
          Function Prototypes
*/
void init_screen(void);         // Reads in initial EEPROM values and displays them
uint16_t update_count(void);    // Reads in EEPROM values, increments and the stores them
void update_screen(int beers);  // Updates screen with current number of beers
bool lights_off(void);          // Reads all analog inputs
void RGB_LED(uint8_t red, uint8_t green, uint8_t blue);   // Quick was to set the state of the RGB LED
void meme_detector(int16_t beers);  // Adds effects when certain milstones are reached in the beer count
void button_ISR(void);          // Services momentary switch
void laser_ISR(void);           // Services interrupts caused by a break in the laser

void setup()
{
#ifdef DEBUG
  // Initialize the Serial monintor
  Serial.begin(115200);
#endif

Serial.begin(115200);

  // Initialize the LCD
  lcd.begin();
  lcd.backlight();

  // Digital Pin Set Up
  pinMode(BUZZ, OUTPUT);      // Buzzer
  pinMode(RED, OUTPUT);       // RED pin of REG LED
  pinMode(GREEN, OUTPUT);     // GREEN pin of REG LED
  pinMode(BUTTON, INPUT);// Button which manually controls buzzer
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
  if (EEPROM.read(UPDATE_REQ) == 111) // Set in meme_detector if beers exceeds 9999
  {
    // This will throw the code into an infinite while loop
    meme_detector(9999);
  }

  // External interrupt for button
  attachInterrupt(digitalPinToInterrupt(RESET_BUTTON), button_ISR, RISING);

  // External interrup for motion sensor
  attachInterrupt(digitalPinToInterrupt(LASER_PHOTO), laser_ISR, RISING);
}

void loop()
{
  // Halt program while the lights are off.
  lights_off_global = lights_off();
  while (lights_off_global)
  {
    lights_off_global = lights_off();;
  }

  // If a can has passed through the laser
  if (can_detected)
  {
    beers = update_count(); // Update the beer count
    meme_detector(beers);   // Check for milestones 
    update_screen(beers);   // Update the screen with new count
    can_detected = 0;       // Reset boolean
    
  }

  // If the reset button has been pushed
  if (reset_requested)
  {
    // Process reset request
    reset_req();
  }

  Serial.println(digitalRead(BUTTON));
  // Enables/disables RBG led cycle
  if (digitalRead(BUTTON))
  {
    RGB_LED_on = !RGB_LED_on;
    while (digitalRead(BUTTON));
  }

  if (RGB_LED_on)
  {
    update_LED();
  }
  else
  {
    RGB_LED(0,0,0);
  }
}


/*
          Functions
*/

void update_LED(void)
{
    uint8_t led = random(1, 4);

    if (red >= 250)
    {
      red_dir = -1;
    }
    else if (red <= 5)
    {
      red_dir = 1;
    }

    if (green >= 250)
    {
      green_dir = -1;
    }
    else if (green <= 5)
    {
      green_dir = 1;
    }

    if (blue >= 250)
    {
      blue_dir = -1;
    }
    else if (blue <= 5)
    {
      blue_dir = 1;
    }
    
    switch (led)
    {  
      case 1:
        red += red_dir*(random(1, 4));
        break;
      case 2:
        green += green_dir*(random(1, 4));
        break;
      case 3:
        blue += blue_dir*(random(1, 4));
        break;
    }
    RGB_LED(red, green, blue);
    delay(4);
}

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
    RGB_LED(0,255,0);
    digitalWrite(BUZZ, HIGH);
    delay(75);
    digitalWrite(BUZZ, LOW);
    RGB_LED(0,0,0);
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
  float pot = 1024 - analogRead(POT);
  float light_level = analogRead(LIGHT_PHOTO)+ 200; // Add 200 to put light_level in an easier to use range

  // Accidentally bought a non-linear pot so we are going
  // to do a linear approximation
  if (pot > 178)
  {
    pot = 0.2*pot + 819;
  }
  else if (pot > 73)
  {
    pot = 1.63*pot + 566;
  }
  else if (pot > 47)
  {
    pot = 1.35*pot + 411;
  }
  else if (pot > 0)
  {
    pot = 22.35*pot - 536;
  }
  else
  {
    pot = 0;
  }

  // Low pass filter analog reads to remove large fluctuations 
  light_level_low_pass = light_level_low_pass + ((light_level - light_level_low_pass)/64);
  pot_low_pass = pot_low_pass + ((pot - pot_low_pass)/64);  

  // The following is  Unlikely to happen
  // but will prevent bugs from that dirty addtion to light_level
  // above which could potentially make light_level so large that
  // the screen could not be shut off by the pot
  if (light_level_low_pass > 900) 
  {
    light_level_low_pass = 900;
  }
  
#ifdef DEBUG
    Serial.print(pot); Serial.print(',');
    Serial.print(pot_low_pass); Serial.print(',');
    Serial.print(light_level); Serial.print(',');
    Serial.println(light_level_low_pass);
#endif
  
  if (light_level_low_pass < pot_low_pass)
  {
    lcd.noBacklight();
    digitalWrite(LASER, LOW);
    RGB_LED(0,0,0);
    return 1;
  }
  else if (lights_off_global)
  {
    lcd.backlight();
    digitalWrite(LASER, HIGH);
    can_detected = 0;
    return 0;
  }
}

void reset_count(void)
{
  // Erase values stored in EEPROM
  EEPROM.write(ONES, 0);
  EEPROM.write(TENS, 0);
  EEPROM.write(HUNDREDS, 0);
  EEPROM.write(THOUSANDS, 0);

  // Check to make sure values were written into EEPROM correctly
  if ((EEPROM.read(ONES) == 0) || (EEPROM.read(TENS) == 0) ||
      (EEPROM.read(HUNDREDS) == 0) || (EEPROM.read(THOUSANDS) == 0))
  {
    // Beep the buzzer for succees
    digitalWrite(BUZZ, HIGH);
    delay(75);
    digitalWrite(BUZZ, LOW);
    RGB_LED(0,0,0);
    beers = 0;
  }
  else
  {
    // One long beep for failure
    digitalWrite(BUZZ, HIGH);
    delay(500);
    digitalWrite(BUZZ, LOW);
  }
}

/*
 * This fucntion is called when the reset button is pressed. It delivers
 * instructions to the screen which will allow the user to reset the count,
 * or leave it as is.
 */
 void reset_req(void)
 {
    RGB_LED(255,0,0);
    uint32_t time_ms = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press 6x more");
    lcd.setCursor(0, 1);
    lcd.print("to reset (");
    lcd.print(6);
    lcd.print("s)");
    
    while (time_ms < 6000)
    {
      if (pressed && (presses <= 6))
      {
        lcd.setCursor(0, 0);
        lcd.print("Press ");
        lcd.print(6-presses);
        lcd.print("x more");
        pressed = 0;
      }
      if (!(time_ms%1000))
      {
        lcd.setCursor(0, 1);
        lcd.print("to reset (");
        lcd.print((6000 - time_ms)/1000);
        lcd.print("s)");
      }
      delay(1);
      time_ms++;  
    }
    if (presses >= 6)
    {
      reset_count();
    }
    reset_requested = 0;
    presses = 0;
    pressed = 0;
    RGB_LED(0,0,0);
    update_screen(beers);
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
    // Set LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("That was a 6/6");
    lcd.setCursor(0, 1);
    lcd.print("pint my boy.");
    // Buzzer/Light display
    for (int i = 0; i < 6; i++)
    {
      uint8_t led = 0;
      led = 42*i;
      RGB_LED(0, led, 0);
      digitalWrite(BUZZ, HIGH);
      delay(150);
      digitalWrite(BUZZ, LOW);
      delay(75);
      RGB_LED(0, 0, 0);
    }
    delay(5000);
  }
  // 69
  else if (beers == 69)
  {
    // Set LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       69");
    lcd.setCursor(0, 1);
    lcd.print("      Nice.");
    // Buzzer/Light display
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(BUZZ, HIGH);
      delay(75);
      digitalWrite(BUZZ, LOW);
      delay(75);
    }
    int t = 0;
    while (t < 1250)
    {
      t++;
      update_LED();
    }
  }
  // 420
  else if (beers == 420)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      420");
    lcd.setCursor(0, 1);
    lcd.print("   Blaze It.");
    // Buzzer/Light display
    for (int i = 0; i < 3; i++)
    {
      RGB_LED(255, 0, 0);
      digitalWrite(BUZZ, HIGH);
      delay(75);
      digitalWrite(BUZZ, LOW);
      delay(75);
      RGB_LED(0, 255, 0);
      digitalWrite(BUZZ, HIGH);
      delay(75);
      digitalWrite(BUZZ, LOW);
      delay(75);
      RGB_LED(255, 255, 0);
      digitalWrite(BUZZ, HIGH);
      delay(200);
      digitalWrite(BUZZ, LOW);
      delay(200);
    }
    RGB_LED(0,255,0);
    delay(5000);
    RGB_LED(0,0,0);
  }
  // 666
  else if (beers == 666)
  {
    // Set LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       666!");
    lcd.setCursor(0, 1);
    lcd.print("     spooky.");
    // Buzzer/Light display
    for (int i = 0; i < 3; i++)
    {
      uint8_t led = 0;
      led = 80*i;
      RGB_LED(led, 0, 0);
      digitalWrite(BUZZ, HIGH);
      delay(500);
      digitalWrite(BUZZ, LOW);
      delay(75);
      RGB_LED(0, 0, 0);
    }
    RGB_LED(255,0,0);
    delay(5000);
    RGB_LED(0,0,0);
  }
  // 777
  else if (beers == 777)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       777!");
    lcd.setCursor(0, 1);
    lcd.print("Winner/Gagnant!");
    // Buzzer/Light display
    for (int i = 0; i < 20; i++)
    {
      RGB_LED(255, 255, 0);
      digitalWrite(BUZZ, HIGH);
      delay(50);
      digitalWrite(BUZZ, LOW);
      delay(50);
      RGB_LED(0, 0, 0);
    }
    RGB_LED(255,255,0);
    delay(5000);
    RGB_LED(0,0,0);
  }
  // 1111
  else if (beers == 1111)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     11:11");
    lcd.setCursor(0, 1);
    lcd.print("  Make a Wish!");
    // Buzzer/Light display
    RGB_LED(0,255,0);
    digitalWrite(BUZZ, HIGH);
    delay(1111);
    digitalWrite(BUZZ, LOW);
    delay(5000);
    RGB_LED(0,0,0);
  }
  // 6969
  else if (beers == 6969)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Double 69???");
    lcd.setCursor(0, 1);
    lcd.print("  Hella Nice.");
    // Buzzer/Light display
    for (int i = 0; i < 4; i++)
    {
      RGB_LED(255, 0, 255);
      digitalWrite(BUZZ, HIGH);
      delay(75);
      digitalWrite(BUZZ, LOW);
      delay(200);
      RGB_LED(0, 0, 0);
    }
    RGB_LED(255,0,255);
    delay(5000);
    RGB_LED(0,0,0);
  }
  // 9999
  else if (beers >= 9999)
  {
    // Code is only designed to handle upto 9999 beers
    RGB_LED(255, 0, 0); // Set LED to red
    
    // Set LCD
    lcd.setCursor(0, 0);
    lcd.print("Update Required");
    lcd.setCursor(0, 1);
    lcd.print("Talk to Motto");
    
    // Wrtie EEPROM update REQ can be detected on start-up
    EEPROM.write(UPDATE_REQ, 111);

    // Hold up the code
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
  if (reset_requested)
  {
    pressed = 1;
    presses++;
  }
  else
  {
    reset_requested = 1;
  }
}

/*
   This ISR is called each time the motion detector detects motion.
   This is what casues the counter to be incremented and the screen
   updated.
*/
void laser_ISR(void)
{
  if (!lights_off_global)
  {
    can_detected = 1;
  }
  
}
