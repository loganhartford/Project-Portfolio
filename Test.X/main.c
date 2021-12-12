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

// Add thing for delay fuction or creat your own.

bool TMR0_b = 0;
int count = 0;
uint8_t presses = 0;
uint8_t last_note = 0;
bool silent_night_playing = 0;
bool TMR0_complete = 0;
uint8_t num_songs = 2;
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
                          238, 238, 238, 238, 238, 238};
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

uint8_t silent_night_lights[] = {0x88, 0x44, 0x22, 0x11, 0x88, 0x44, 0x22};
uint8_t light_array[] = {0};

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
    //T2PR = 0x80;
    
    // PWM
    PWM3_Initialize();
    
    // Disable the output of the shift register
    OE_n_SetHigh();
    // Turn off load switch
    EN_MATRIX_n_SetHigh();
    // Data is shifted on low-to-high transition of SCHP input
    LATCH_SetLow();
    
    // Make sure lights are off initially.
    shiftBytes(0xFF, 0x00);

//    while (1)
//    {
//         play_note(silent_night[count], silent_night_pre[count]);
//        //T2CONbits.TMR2ON = 0;
//        count++;
//        if (count > 138) SLEEP();
//        __delay_ms(250);
//    }
    
    // TMR0 and TMR1 will run during sleep
    while (1)
    {
        T0CON0bits.T0EN = 1;        // Enable TMR0
        shiftBytes(0x00, 0x01); // Testing
        OE_n_SetLow();          // ^^
        EN_MATRIX_n_SetLow();   // ^^
        if (presses && TMR0_complete)
        {
            OE_n_SetLow();          // Enable shift registers
            EN_MATRIX_n_SetLow();   // Turn on load switch
            T0CON0bits.T0EN = 0;    // Disable TMR0
            switch (presses)
            {
                // Silent night
                case 1:
                    light_array[0] = 0x88;
                    light_array[1] = 0x44;
                    light_array[2] = 0x22;
                    light_array[3] = 0x11;
                    light_array[4] = 0x88;
                    light_array[5] = 0x44;
                    light_array[6] = 0x22;
                    silent_night_playing = 1;
                    break;
                case 2:
                    light_array[0] = 0x00;
                    light_array[1] = 0x00;
                    light_array[2] = 0x00;
                    light_array[3] = 0x00;
                    light_array[4] = 0x00;
                    light_array[5] = 0x00;
                    light_array[6] = 0x00;
                    //silent_night_playing = 1;
            }
            T1CONbits.TMR1ON = 1;   // Enable TMR1
            T2CONbits.TMR2ON = 1;   // Enable PWM TMR
            
            // Silent night
            while (presses == 1)
            {   
                playNote(silent_night[count], silent_night_pre[count]);
                displayMatrix(light_array);
            }
            while (presses == 2)
            {
                playNote(silent_night[1], silent_night_pre[1]);
                displayMatrix(light_array);
            }
            presses = 0; // *
            silent_night_playing = 0;
            T1CONbits.TMR1ON = 0;   // Disable TMR1
            T2CONbits.TMR2ON = 0;
            OE_n_SetHigh();         // Disable shift registers
            EN_MATRIX_n_SetHigh();  // Turn off load switch
        }
        if (TMR0_complete)
        {
            T0CON0bits.T0EN = 0;    // Disable TMR0
            PIR0bits.INTF = 0;      // Clear flag
            PIE0bits.INTE = 1;      // Enable external interrupts
            OE_n_SetHigh();          // TEst
            EN_MATRIX_n_SetHigh();  // ^^
            SLEEP();
        }
    }
}

/*
                    Functions
 */
void EXT_ISR(void)
{
    presses++;          // Increment presses
    TMR0_Reload();      // Reset TMR0
    //T0CON0bits.T0EN = 1;
    // If someone presses the button during a song
    if (T1CONbits.TMR1ON)
    {
        //T1CONbits.TMR1ON = 0;
        presses = 0;
        count = 0;
    }
    else
    {  
        TMR0_complete = 0;
    }
    if (presses > num_songs)
    {
        presses = 0;
    }
}

void TMR0_ISR_(void)
{
    TMR0_complete = 1;
}

void TMR1_ISR_(void)
{
    if (silent_night_playing)
    {
        if (count < 24 || ((count > 48) && (count < 96)))
        {
            if (((count + 1) & 0x02) && ((count + 1) & 0x01))
            {
                for (int i = 0; i < 7; i++)
                {
                    uint8_t lights = light_array[i] >> 7;
                    light_array[i] = (light_array[i] << 1) + lights;
                }  
            }
        }
        else if (count > 126)
        {
            for (int i = 0; i < 7; i++)
            {
                light_array[i] = (light_array[i] << 1) + 1;
            }
        }
        else 
        {
            for (int i = 0; i < 7; i++)
            {
                uint8_t lights = light_array[i] >> 7;
                light_array[i] = (light_array[i] << 1) + lights;
            }
        }
          
    }
    count++;
    if ((count > 138) && silent_night_playing)
    {
        presses = 0;            // Reset presses
        count = 0;              // Reset beat counter
    }
}

void playNote(uint8_t note, uint8_t prescale)
{
    if (note != last_note)
    {
        T2CON = prescale;
        T2PR = note;  
    }
    last_note = note;
}

void Initialize_Matrix(void)
{
    // Turn on load switch
    EN_MATRIX_n_SetLow(); // Don't forget this for testing the buzzer
    shiftBytes(0xFF, 0x00); // Make sure all FETS are off
    OE_n_SetLow(); // Enable output;
}

void shiftBytes(uint8_t highSide, uint8_t lowSide) 
{
    // Make sure output is enabled, handle this is sleep/wake.
    // Write bytes into registers
    SPI1_ExchangeByte(lowSide);
    SPI1_ExchangeByte(highSide); // Verify this is the correct order to write out.
    // Shift data to the output
    LATCH_SetHigh();
    // Reset for next time
    LATCH_SetLow();
}

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

void resetLightArray(uint8_t presses)
{
    switch (presses)
    {
        case 1:
            light_array[0] = 0x88;
            light_array[1] = 0x44;
            light_array[2] = 0x22;
            light_array[3] = 0x11;
            light_array[4] = 0x88;
            light_array[5] = 0x44;
            light_array[6] = 0x22;     
    }
}



/**
 End of File
*/