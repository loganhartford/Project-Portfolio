/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15225
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"

// Second Song Selection--Only define one at a time
//#define coc           // Clash of Clans login
//#define river         // The River, Garth Brooks
#define sand            // Sandstorm

// Third song Selection--Only define one at a time
//#define jcole         // No Role Modlez, J.Cole
//#define dreams        // You Make My Dream Come True, Hall and Oates
#define jungle          // Into the Jungle, Guns N' Roses

// Track which song is being played
bool silent_night_playing = 0;
bool song3_playing = 0;
bool song2_playing = 0;

bool TMR0_complete = 0;     //TMR0 waits for user input

int count = 0;              // Beat counter
uint8_t last_note = 0;      // Only update PWM if note changes
uint8_t last_prescale = 0;  // Only update PWM if prescaler changed

uint8_t presses = 0;        // Button presses

uint8_t num_songs = 3;      // Total number of songs available 
/*
                    Prototypes
 */

void shiftBytes(uint8_t highSide, uint8_t lowSide);
void Initialize_Matrix(void);
void displayMatrix(uint8_t states[8]);
void playNote(uint8_t note, uint8_t prescale);
void EXT_ISR(void);
void TMR0_ISR_(void);
void TMR1_ISR_(void);




// Silent night notes and TMR2 prescalers.
uint8_t silent_night[] = {158, 158, 158, 141, 158, 158, 
                          188, 188, 188, 188, 188, 188,
                          158, 158, 158, 141, 158, 158,
                          188, 188, 188, 188, 188, 188,
                          211, 211, 211, 211, 211, 211,
                          252, 252, 252, 252, 252, 252,
                          238, 238, 238, 238, 238, 238,
                          158, 158, 158, 158, 158, 158,
                          141, 141, 141, 141, 141, 141,
                          237, 237, 237, 252, 141, 141,
                          158, 158, 158, 141, 158, 158,
                          188, 188, 188, 188, 188, 188,
                          141, 141, 141, 141, 141, 141,
                          237, 237, 237, 252, 141, 141,
                          158, 158, 158, 141, 158, 158,
                          188, 188, 188, 188, 188, 188,
                          211, 211, 211, 211, 211, 211,
                          177, 177, 177, 211, 252, 252,
                          237, 237, 237, 237, 237, 237, 
                          188, 188, 188, 188, 188, 188,
                          237, 237, 158, 158, 188, 188,
                          158, 158, 158, 177, 211, 211,
                          238, 238, 238, 238, 238, 238, 0};
uint8_t silent_night_pre[] = {0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
                              0xC0, 0xC0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                              0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0};
// Song 2 Variables
#ifdef coc
uint8_t song2[] = {211, 158, 141, 211, 188, 188,   0,   0,   0,
                   188, 188, 158, 158, 188, 188, 141, 141, 141};
//uint8_t song2_pre[] = {0xB0, 0xB0, 0xB0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0,
//                       0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0};
uint8_t song2_pre[] = {0xC0, 0xC0, 0xC0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0};
uint8_t timer_high_2 = 0xF3;
uint8_t timer_low_2 = 0xE4;
uint8_t song2_length = 16;
#endif


#ifdef river
// Notes

uint8_t song2[] =    {238, 238, 189, 189, 158, 158,
                      158, 158, 158, 158, 141, 141, 141, 141, 158, 158, 189, 189, 189, 189, 189, 158,
                      141, 141, 141, 141, 141, 141, 158, 158, 158, 158, 158, 158,   0,   0, 189, 158,
                      141, 141, 141, 141, 141, 141, 158, 158, 158, 158, 158, 158, 158, 158, 158, 178,
                      178, 178, 189, 178, 178, 178, 158, 158, 141, 141, 158, 158, 189, 189, 158, 158, 
                      158, 158, 158, 158, 141, 141, 158, 158, 158, 158, 189, 189, 189, 189, 189, 189,};
uint8_t song2_2[] =  {141, 141, 141, 141, 141, 141, 252, 252, 189, 189, 212, 212, 178, 178, 141, 141, 
                      158, 158, 158, 158, 141, 141, 141, 141, 158, 158, 189, 189, 189, 189, 238, 212, 
                      189, 189, 189, 212, 212, 212, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 0};
uint8_t song2_pre[] = {};
uint8_t timer_high_2 = 0xE8;
uint8_t timer_low_2 = 0x25;
uint8_t song2_length = 133;
#endif

#define sand

#ifdef sand
// Notes
const uint8_t b = 252;
const uint8_t c = 238;
const uint8_t d = 212;
const uint8_t e = 189;
const uint8_t f = 178;
const uint8_t g = 158;
const uint8_t a = 141;

uint8_t song2[] =    {252, 252, 252, 252, 252, 0, 252, 252, 252, 252, 252, 252, 252,   0, 
                      189, 189, 189, 189, 189, 189, 189, 0, 212, 212, 212, 212, 212, 212, 212, 141,
                      252, 252, 252, 252, 252, 252, 0, 252, 252, 252, 252, 252, 252, 252, 189,   0, 
                      252, 252, 252, 252, 252, 0, 252, 252, 252, 252, 252, 252, 252, 212,};
uint8_t song2_pre[] = {};
uint8_t timer_high_2 = 0xE7;
uint8_t timer_low_2 = 0xC8;
uint8_t song2_length = 60;
#endif

// Song 3 Variables
#ifdef jcole
uint8_t song3[] = {212, 0, 
                   212, 238, 
                   252, 238, 
                   252, 141, 
                   158, 158,
                   212,   0,
                   212, 212,
                     0,   0,
                     0,   0, 
                   212, 238, 
                   252, 238, 
                   252, 141, 
                   158, 158,
                   212,   0,
                   212, 212,
                     0,   0};
uint8_t song3_pre[] = {0xD0, 0xD0, 
                       0xD0, 0xD0, 
                       0xD0, 0xD0, 
                       0xD0, 0xE0,
                       0xE0, 0xE0,
                       0xE0, 0xE0,
                       0xE0, 0xE0,
                       0xD0, 0xD0,
                       0xD0, 0xD0, 
                       0xD0, 0xD0, 
                       0xD0, 0xD0, 
                       0xD0, 0xE0,
                       0xE0, 0xE0,
                       0xE0, 0xE0,
                       0xE0, 0xE0,
                       0xD0, 0xD0};
//uint8_t song3_pre[] = {0xC0, 0xC0, 
//                       0xC0, 0xC0, 
//                       0xC0, 0xC0,
//                       0xC0, 0xD0,
//                       0xD0, 0xD0,
//                       0xD0, 0xD0,
//                       0xD0, 0xD0,
//                       0xC0, 0xC0,
//                       0xC0, 0xC0, 
//                       0xC0, 0xC0, 
//                       0xC0, 0xC0,
//                       0xC0, 0xD0,
//                       0xD0, 0xD0,
//                       0xD0, 0xD0,
//                       0xD0, 0xD0,
//                       0xC0, 0xC0};
uint8_t timer_high_3 = 0xED;
uint8_t timer_low_3 = 0xD6;
uint8_t song3_length = 31;
uint8_t cole_counter = 0;
#endif

#ifdef dreams
//const uint8_t b = 252;
//const uint8_t c = 238;
//const uint8_t d = 212;
//const uint8_t e = 189;
//const uint8_t f = 178;
//const uint8_t g = 158;
//const uint8_t a = 141;
uint8_t song3[] =  {  0,   0, 212, 212, 212, 212, 212, 212,
                    212, 212, 212, 212,   0, 212, 212, 212,
                    212, 212, 212, 212, 212, 212, 212, 212,
                    212, 212, 212, 212,   0, 212, 212, 212,
                      0,   0, 212, 212, 212, 212, 212, 212,
                    212, 212, 212, 212,   0, 212, 212, 212,
                    212, 212, 212, 212, 212, 212, 212, 212,
                    212, 212, 212, 212,   0,   0, 
                    237, 212, 178, 
                    178, 178, 178, 178, 178, 178, 212, 238,
                    178, 178, 212, 178, 178, 178, 212, 238,
                    212, 178,   0,   0,   0,   0, 212, 238,
                    141, 158, 178, 178, 178, 178, 178, 212,
                    238, 178,   0,   0,   0,   0, 141, 141,
                    141, 141, 158, 158, 158, 158, 178, 141,
                    141, 158, 178, 212, 212, 212,   0,   0,};
uint8_t song3_pre[] = {0xE0, 0xE0, 0xD0, 0xD0, 0xE0, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xE0, 0x00, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xD0, 0xE0, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xE0, 0x00, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xD0, 0xE0, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xE0, 0x00, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xD0, 0xE0, 0xE0, 0xD0, 0xD0,
                       0xE0, 0xE0, 0xD0, 0xE0, 0x00, 0x00, 
                       0xD0, 0xD0, 0xD0, 
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xE0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,};
uint8_t timer_high_3 = 0xEA;
uint8_t timer_low_3 = 0x34;
uint8_t song3_length = 120;
bool change_lights = 0;
uint8_t dream_lights[] = {0x00, 0xE8, 0xBE, 0xFE, 0xBD, 0xA0, 0x00};
uint8_t dream_sw = 0;
#endif

#ifdef jungle
//const uint8_t b = 252;
//const uint8_t c = 238;
//const uint8_t d = 212;
//const uint8_t e = 189;
//const uint8_t f = 178;
//const uint8_t g = 158;
//const uint8_t a = 141;
uint8_t song3[] =  {212, 212, 212, 212, 212, 212, 212, 212, 212, 212,
                    252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
                    178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
                    141, 141, 238, 238, 212, 212, 189, 189, 158, 158, 141, 141, 238, 238, 212, 212,
                    189,   0, 189,   0, 189,   0, 189,   0, 189,   0, 189,   0, 189,   0, 189, 189,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212,
                    158, 158, 158, 158, 178, 178, 158, 158, 158, 158, 178, 178, 189, 189, 212, 212};
uint8_t song3_pre[] = {0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
                       0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
                       0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
                       0xE0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xC0, 0xC0, 0xC0, 0xC0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xC0, 0xC0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
                       0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xE0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0};
uint8_t timer_high_3 = 0xF1;
uint8_t timer_low_3 = 0x3A;
uint8_t song3_length = 158;
uint8_t jungle_count = 0;
bool jungle_bool = 0;
#endif

// Contains the state of the LEDs as any given point in time.
uint8_t light_array[] = {0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE};

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    // Initialize SPI
    SPI1_Initialize();
    SSP1CON1bits.SSPEN = 0;     // Clear bit to configure SPI
    TRISCbits.TRISC3 = 0;       // Set SDO as output
    TRISAbits.TRISA4 = 1;       // Set SDI as input
    TRISCbits.TRISC5 = 0;       // Set SCK as output
    //SSPCON3bits.BOEN = 1;       // SSP1BUF updates every time that a new data 
                                // byte is shifted in ignoring the BF bit
    SSP1CON1bits.SSPEN = 1;     // Set bit to enable serial port
    
    // External Interrupts
    EXT_INT_Initialize();
    INT_SetInterruptHandler(EXT_ISR);
    PIE0bits.INTE = 1; // Interrupt on by default
    
    // TMR0
    TMR0_Initialize();
    TMR0_SetInterruptHandler(TMR0_ISR_);
    T0CON0bits.T0EN = 0; // Timer off by default
    
    // TMR1
    TMR1_Initialize();
    TMR1_SetInterruptHandler(TMR1_ISR_);
    T1CONbits.TMR1ON = 0; // Timer off by default
    
    // TMR2 for PWM
    TMR2_Initialize();
    T2CONbits.TMR2ON = 0;
    
    // PWM
    PWM3_Initialize();
    
    // Shift Registers
    OE_n_SetLow();         // Enable shift register output
    LATCH_SetLow();        // Data is shifted on low-to-high transition of SCHP input
    
    // LEDs
    EN_MATRIX_n_SetLow();  // Turn on load switch
    
    // Start Up Light Sequence
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            displayMatrix(light_array);
        }
        if (i < 7)
        {
            for (int j = 0; j < 7; j++)
            {
                uint8_t light = (~light_array[j]) << 7;
                light_array[j] = (light_array[j] << 1) + (light >> 7);
            }
        }
        else
        {
            for (int j = 0; j < 7; j++)
            {
                uint8_t light = (~light_array[j]);
                light_array[j] = (light_array[j] << 1) + 1;
            }
        }
    }
    
//    while(1)
//    {
//        displayMatrix(dream_lights);
//    }
        
    // TMR0 and TMR1 will run during sleep
    while (1)
    {
        T0CON0bits.T0EN = 1;        // Enable TMR0
        shiftBytes(0xFE, 0x08);     // ON indicator
        OE_n_SetLow();              // Enable shift register output 
        EN_MATRIX_n_SetLow();       // Turn on load switch
        if (presses && TMR0_complete)
        {
            T0CON0bits.T0EN = 0;    // Disable TMR0 to prevent interrupts
            
            // Set up light_array and playing boolean
            switch (presses)
            {
                case 1:  // Silent night
                    light_array[0] = 0x88;
                    light_array[1] = 0x44;
                    light_array[2] = 0x22;
                    light_array[3] = 0x11;
                    light_array[4] = 0x88;
                    light_array[5] = 0x44;
                    light_array[6] = 0x22;
                    silent_night_playing = 1;
                    break;
                case 2: // Song 2
#ifdef coc
                    light_array[0] = 0xFE;
                    light_array[1] = 0xFE;
                    light_array[2] = 0xFE;
                    light_array[3] = 0xFE;
                    light_array[4] = 0xFE;
                    light_array[5] = 0xFE;
                    light_array[6] = 0xFE;
#endif
#ifdef river
                    light_array[0] = 0xFF;
                    light_array[1] = 0xFF;
                    light_array[2] = 0xFF;
                    light_array[3] = 0xFF;
                    light_array[4] = 0xFF;
                    light_array[5] = 0xFF;
                    light_array[6] = 0xFF;
#endif
                    song2_playing = 1;
                    break;
                case 3: // Song 3
#ifdef dreams
                    light_array[0] = 0x00;
                    light_array[1] = 0xE8;
                    light_array[2] = 0xBE;
                    light_array[3] = 0xFE;
                    light_array[4] = 0xBD;
                    light_array[5] = 0xA0;
                    light_array[6] = 0x00;
#endif
#ifdef jcole
                    light_array[0] = 0xFF;
                    light_array[1] = 0xFF;
                    light_array[2] = 0xFF;
                    light_array[3] = 0xFF;
                    light_array[4] = 0xFF;
                    light_array[5] = 0xFF;
                    light_array[6] = 0xFF;
                    cole_counter = 0;
#endif
#ifdef jungle
                    light_array[0] = 0xFF;
                    light_array[1] = 0xFF;
                    light_array[2] = 0xFF;
                    light_array[3] = 0xFF;
                    light_array[4] = 0xFF;
                    light_array[5] = 0xFF;
                    light_array[6] = 0xFF;
                    jungle_count  = 0;
                    jungle_bool = 0;
#endif
                    
                    song3_playing = 1;
                    break; 
            }
            T1CONbits.TMR1ON = 1;   // Enable TMR1
            T2CONbits.TMR2ON = 1;   // Enable PWM TMR
            
            // Silent night
            while (presses == 1) 
            {   
                playNote(silent_night[count], silent_night_pre[count]);
                displayMatrix(light_array);
            }
            // Song 2
            while (presses == 2)
            {
#ifdef river
                if (count > 84)
                {
                    uint8_t pre = 0xD0l;
                    if ((count >= 91) && (count <= 96))
                    {
                        pre = 0xC0;
                    }
                    else 
                    {
                        pre = 0xD0;
                    }
                    playNote(song2_2[count - 85], pre);
                    displayMatrix(light_array);
                }
                else 
                {
                    playNote(song2[count], 0xD0);
                    displayMatrix(light_array);  
                }
#endif
#ifdef sand           
                playNote(song2[count], 0xD0);
                displayMatrix(light_array);
#endif
            }
            // Song 3
            while (presses == 3)
            {
                playNote(song3[count], song3_pre[count]);
                displayMatrix(light_array);
            }
            presses = 0;                // Reset presses 
            silent_night_playing = 0;   // Reset playing booleans
            song2_playing = 0;
            song3_playing = 0;
            T1CONbits.TMR1ON = 0;       // Disable TMR1
            T2CONbits.TMR2ON = 0;       // Disable PWM TMR
        }
        // If no button was pushed or a song was just played, go to sleep.
        if (TMR0_complete && (!presses))
        {
            T0CON0bits.T0EN = 0;    // Disable TMR0
            T1CONbits.TMR1ON = 0;   // Disable TMR1
            T2CONbits.TMR2ON = 0;   // Disable TM2
            PIR0bits.INTF = 0;      // Clear flag
            PIE0bits.INTE = 1;      // Enable external interrupts
            OE_n_SetHigh();         // Disable shift register output
            EN_MATRIX_n_SetHigh();  // Disable load swich
            SLEEP();
        }
    }
}

/*
                    Functions
 */
// Wakes from sleep and increments number of button pushes
void EXT_ISR(void)
{
    uint8_t debounce = 0;
    while (debounce < 20)
    {
        if (RA2_GetValue())
        {
            debounce++;
            __delay_ms(1);
        }
        else
        {
            debounce = 0;
        }
    }
    presses++;          // Increment presses
    TMR0_Reload();      // Reset TMR0
    
    // If someone presses the button during a song, go to sleep.
    if (T1CONbits.TMR1ON)
    {
        presses = 0;
        count = 0;
    }
    // If a song was not playing, then make sure TMR0 bool is cleared.
    else
    {  
        TMR0_complete = 0;
    }
    // Stops presses from being larger than the number of options
    if (presses > num_songs)
    {
        presses = 0;
    }
}

// Waits for user input, if this times out, it goes to sleep or plays a song.
void TMR0_ISR_(void)
{
    TMR0_complete = 1;
}

// Increment the beat counter and manipulate the LED matrix.
void TMR1_ISR_(void)
{
    count++;    // Increment beat counter
    
    // Update the silent night LED matrix.
    if (silent_night_playing)
    {
        if (count < 24 || ((count > 48) && (count < 96)))
        {
            if (last_note != silent_night[count])
            {
                for (int i = 0; i < 7; i++)
                {
                    uint8_t lights = light_array[i] >> 7;
                    light_array[i] = (light_array[i] << 1) + lights;
                }  
            }
        }
        else if (count > 119 && (last_note != silent_night[count]))
        {
            for (int i = 0; i < 7; i++)
            {
                light_array[i] = (light_array[i] << 1) + 1;
            }
        }
        else if (count < 120) 
        {
            for (int i = 0; i < 7; i++)
            {
                uint8_t lights = light_array[i] >> 7;
                light_array[i] = (light_array[i] << 1) + lights;
            }
        }    
    }
    
    // Update the song 2 LED matrix
    if (song2_playing)
    {
#ifdef river
        if (count < 34)
        {
            if (last_note != song2[count])
            {
                for (int i = 0; i < 7; i++)
                {
                    light_array[i] = light_array[i] >> 1;
                }
            }  
        }
        else if (count < 37)
        {
            for (int i = 0; i < 7; i++)
            {
                light_array[i] = 0x00;
            }
        }
        else if (count > 37 && count < 44)
        {
            for (int j = 0; j < 7; j++)
            {
                uint8_t light = (~light_array[j]) << 7;
                light_array[j] = (light_array[j] << 1) + (light >> 7);
            }
        }
        else if (count > 44 && count < 125)
        {
            for (int i = 0; i < 7; i++)
            {
                uint8_t lights = light_array[i] >> 7;
                light_array[i] = (light_array[i] << 1) + lights;
            } 
        }
        else
        {
            for (int j = 0; j < 7; j++)
            {
                uint8_t light = (~light_array[j]);
                light_array[j] = (light_array[j] << 1) + 1;
            }
        }
#endif
#ifdef coc
        if (count < 8)
        {
          for (int i = 0; i < 7; i++)
            {
                light_array[i] = (light_array[i] << 1);
            }  
        }
        else if (count == 8)
        {
            for (int i = 0; i < 7; i++)
            {
                light_array[i] = 0xAA;
            } 
        }
        else
        {
            if (count & 0x01)
            {
                uint8_t lights = light_array[0] >> 7;
                for (int i = 0; i < 7; i++)
                {
                    light_array[i] = (light_array[i] << 1) + lights;
                }
            }
        }
#endif
    }
    
    // Update the song 3 LED matrix
    if (song3_playing)
    {
#ifdef dreams
       if (count < 58)
       {
           if ((last_prescale != song3_pre[count]) && (song3[count] != 0))
           {
               if (change_lights)
               {
                   for (int i = 0; i < 7; i++)
                    {
                        light_array[i] = dream_lights[i];
                    }
                   change_lights = 0;
               }
               else 
               {
                   for (int i = 0; i < 7; i++)
                    {
                        light_array[i] = ~dream_lights[i];
                    }
                   change_lights = 1;              
               }
           }
       }
       else if (count < 62)
       {
           for (int i = 0; i < 7; i++)
            {
                light_array[i] = 0xFF;
            }
       }
       else
       {
           if ((last_note != song3[count]) || (last_prescale != song3_pre[count]))
           {
                dream_sw++;
                if (song3[count] == 0) dream_sw = 4;
                switch(dream_sw)
                {
                case 1:
                    light_array[0] = 0xFF;
                    light_array[1] = 0xFF;
                    light_array[2] = 0xF3;
                    light_array[3] = 0xE3;
                    light_array[4] = 0xE3;
                    light_array[5] = 0xFF;
                    light_array[6] = 0xFF;
                    break;
                case 2:
                    for (int i = 0; i < 7; i++)
                     {
                         light_array[i] = ~dream_lights[i];
                     }
                    break;
                case 3:
                    for (int i = 0; i < 7; i++)
                     {
                         light_array[i] = 0x00;
                     }
                    break;
                default:
                    dream_sw = 0;
                    for (int i = 0; i < 7; i++)
                     {
                         light_array[i] = 0xFF;
                     }
                    break;
                }  
           } 
       }
#endif
#ifdef jcole
       if (song3[count] == 212)
       {
           for (int i = 0; i < 7; i++)
            {
                light_array[i] = 0x00;
            }
       }
       else if (song3[count] == 0)
       {
           for (int i = 0; i < 7; i++)
            {
                light_array[i] = 0xFF;
            }
       }
       else
       {
           if ((light_array[1] == 0x00) || (light_array[1] == 0xFF))
           {                
                for (int i = 0; i < 7; i++)
                {
                    light_array[i] = 0xF9;
                }
           }
           else
           {
                if (last_note != song3[count])
                {
                    for (int i = 0; i < 7; i++)
                    {
                        uint8_t lights = (light_array[i]) << 1;
                        lights = lights >> 7;
                        light_array[i] = (light_array[i] << 1) + lights;
                        lights = (light_array[i]) << 1;
                        lights = lights >> 7;
                        light_array[i] = (light_array[i] << 1) + lights;
                    }  
                }
           }
       }
#endif
#ifdef jungle
        if (count < 10)
        {
           for (int i = 0; i < 7; i++)
             {
                 light_array[i] = 0xF3;
             } 
        }
        else if (count < 20)
        {
           for (int i = 0; i < 7; i++)
             {
                 light_array[i] = 0x0F;
             } 
        }
        else if (count < 29)
        {
           for (int i = 0; i < 7; i++)
             {
                 light_array[i] = 0xFC;
             } 
        }
       else if (count == 29)
        {
           for (int i = 0; i < 7; i++)
             {
                 light_array[i] = 0x7F;
             } 
        }
       else if (song3[count] == 0)
        {
           for (int i = 0; i < 7; i++)
           {
                light_array[i] = 0x7F;
           } 
        }
       else if (count < 46 && (last_note != song3[count]))
       {
           for (int i = 0; i < 7; i++)
           {
                light_array[i] = light_array[i] >> 1;
           } 
       }
       else if (count < 62 && count > 45)
        {
           for (int i = 0; i < 7; i++)
           {
                light_array[i] = 0x00;
           } 
        }
       else if (count >= 62)
       {
           jungle_count++;
           if (jungle_count == 1)
           {
                light_array[0] = 0x88;
                light_array[1] = 0x44;
                light_array[2] = 0x22;
                light_array[3] = 0x11;
                light_array[4] = 0x88;
                light_array[5] = 0x44;
                light_array[6] = 0x22;
           }
           else if (jungle_count < 9)
           {
               if (last_note != song3[count])
               {
                    for (int i = 0; i < 7; i++)
                    {
                        uint8_t lights = light_array[i] >> 7;
                        light_array[i] = (light_array[i] << 1) + lights;
                    }
               }
           }
           else if (jungle_count < 16)
           {
               if (last_note != song3[count])
               {
                   uint8_t jungle_sw = (jungle_count - 8)/2;
                   switch (jungle_sw)
                   {
                       case 0: 
                            for (int i = 0; i < 7; i++)
                            {
                                light_array[i] = 0x81;
                            } 
                            break;
                        case 1:  
                            for (int i = 0; i < 7; i++)
                            {
                                light_array[i] = 0xC3;
                            } 
                            break;
                        case 2:  
                            for (int i = 0; i < 7; i++)
                            {
                                light_array[i] = 0xE7;
                            } 
                            break;
                        case 3:  
                            for (int i = 0; i < 7; i++)
                            {
                                light_array[i] = 0xFF;
                            } 
                            break;
                   }
               }
           }
           else
           {
               jungle_count = 0;
           }
           
           
       }
       
#endif
    }
    

    // Set the BPM to the correct value for song 2
    if (song2_playing)
    {
#ifdef sand
        playNote(0, 0);
#endif
        TMR1H = timer_high_2;
        TMR1L = timer_low_2;
    }
    
    // Set the BPM to the correct value for song 3
    if (song3_playing)
    {
        TMR1H = timer_high_3;
        TMR1L = timer_low_3;
    }
    
    // If silent night is over, sleep
    if ((count > 138) && silent_night_playing)
    {
        presses = 0;            // Reset presses
        count = 0;              // Reset beat counter
    }
    
    // If song 2 is over, sleep
    else if ((count > song2_length) && song2_playing)
    {
        presses = 0;            // Reset presses
        count = 0;              // Reset beat counter
    }
    
    // If song 3 t is over, sleep
    else if ((count > song3_length) && song3_playing)
    {
        presses = 0;            // Reset presses
        count = 0;              // Reset beat counter
#ifdef jcole
        if (cole_counter < 2)
        {
            count = 0;
            presses = 3;
            cole_counter++;
        }
#endif
    }
    
    
}

// Updates PWM registers with correct period and prescaler.
void playNote(uint8_t note, uint8_t prescale)
{
    // If the note is the same as before don't update.
    if (note != last_note)
    {
        T2PR = note;  
    }
    // If the prescale is the same as before don't update
    if (prescale != last_prescale)
    {
        T2CON = prescale;
    }
    last_note = note;
    last_prescale = prescale;
}

// I never use this
void Initialize_Matrix(void)
{
    // Turn on load switch
    EN_MATRIX_n_SetLow(); // Don't forget this for testing the buzzer
    shiftBytes(0xFF, 0x00); // Make sure all FETS are off
    OE_n_SetLow(); // Enable output;
}

// Shifts bytes into the shift registers
void shiftBytes(uint8_t highSide, uint8_t lowSide) 
{
    // Write bytes into registers
    SPI1_ExchangeByte(lowSide);
    SPI1_ExchangeByte(highSide);
    // Shift data to the output
    LATCH_SetHigh();
    // Reset for next time
    LATCH_SetLow();
}

// Displays the matrix
void displayMatrix(uint8_t states[8])
{
    // Have a global array with the desired states of the high FETS
    // Then Write out each state with the corresponding lowside FET enabled
    uint8_t lowSide = 0x00;
    for (int i = 0; i < 7; i++)
    {
        if (!lowSide)
        {
            lowSide++;
        }
        else 
        {
            lowSide = lowSide << 1; 
        }
        
        shiftBytes(states[i], lowSide);
        __delay_ms(1);
    } 
}



/**
 End of File
*/