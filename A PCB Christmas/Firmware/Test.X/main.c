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

/*
                    Prototypes
 */

void shiftBytes(uint8_t highSide, uint8_t lowSide);
void Initialize_Matrix(void);
void displayMatrix(uint8_t states[8]);
void EXT_ISR(void);
void TMR0_ISR_(void);
void TMR1_ISR_(void);


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
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    // Initialize SPI
    SPI1_Initialize();
    
    // External Interrupts
    EXT_INT_Initialize();
    INT_SetInterruptHandler(EXT_ISR);
    PIE0bits.INTE = 0; // Interrupt off by default
    
    // TMR0
    TMR0_Initialize();
    TMR0_SetInterruptHandler(TMR0_ISR_);
    
    // TMR1
    TMR1_Initialize();
    TMR0_SetInterruptHandler(TMR1_ISR_);
    
    // TMR2 for PWM
    TMR2_Initialize();
    
    // PWM
    PWM3_Initialize();
    
    // Enable the output of the shift register
    OE_n_SetLow();
    // Turn on load switch
    EN_MATRIX_n_SetLow();
    // Data is shifted on low-to-high tansistion of SCHP input
    LATCH_SetLow();

    while (1)
    {
        // TEST1: SPI/Shift Register Properties
        shiftBytes(0xBF, 0x20); // High-side 2 and low-side 3 ON
//        // If correct D48 should be on.
//        __delay_ms(1); // Make sure delay function is working properly
        
        
//        // TEST2: LEDs working
//        // Should turn on each led individually.
//        uint8_t highSide = 0xFE;
//        uint8_t lowSide = 0x01;
//        for (int i = 0; i < 7; i++)
//        {
//            for (int j = 0; j < 7; j++)
//            {
//                shiftBytes(highSide, lowSide);
//                highSide = (highSide << 1) + 1;
//                __delay_ms(500);               
//            }
//            lowSide = (lowSide << 1);
//        }
//        
////        // TEST3: Multiplexing
//        uint8_t state[8] = {0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//        displayMatrix(state);
//        //D1-7 should be on, this is only possible through multiplexing.
//        
//        // TEST4: PWM and Buzzer
//        // T2PR determines the period
//        T2PR = 141; // This should correspond to 440Hz
//        T2CONbits.TMR2ON = 1; // Enable TMR
//        // May have to enable CCP, see data sheet.
//        
//        // TEST5: EXT_INT
//        __delay_ms(2000);
//        PIE0bits.INTE = 1;  // Enable external interrupts
//        shiftBytes(0xFF, 0x00); // Turn LEDs OFF
//        SLEEP();
//        
//        // TEST6: TMR0_ISR
//        T0CON0bits.T0EN = 1;
//        
//        // TEST7: TMR2_ISR
//        T1CONbits.TMR1ON = 1;
//        
//        // TEST8: Load Switch
//        shiftBytes(0xBF, 0x20); // Turn LED ON
//        __delay_ms(2000);
//        EN_MATRIX_n_SetHigh();
//        __delay_ms(2000);
//        EN_MATRIX_n_SetLow();
        
        
        
    }
}

/*
                    Functions
 */
void EXT_ISR(void)
{
    shiftBytes(0xBF, 0x20); // Turn LED ON
}

void TMR0_ISR_(void)
{
    if (TMR0_b)
    {
       shiftBytes(0xBF, 0x20); // Turn LED ON
       TMR0_b = 0;
    }
    else
    {
        shiftBytes(0xBF, 0x20); // Turn LED OFF
        TMR0_b = 1;
    }
}

void TMR1_ISR_(void)
{
    if (TMR0_b)
    {
       shiftBytes(0xBF, 0x20); // Turn LED ON
       TMR0_b = 0;
    }
    else
    {
        shiftBytes(0xBF, 0x20); // Turn LED OFF
        TMR0_b = 1;
    }
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



/**
 End of File
*/