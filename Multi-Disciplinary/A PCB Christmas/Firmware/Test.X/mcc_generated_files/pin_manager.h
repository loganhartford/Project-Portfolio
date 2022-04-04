/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15225
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()              PORTAbits.RA5
#define RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()             do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()           do { WPUAbits.WPUA5 = 0; } while(0)
#define RA5_SetAnalogMode()         do { ANSELAbits.ANSA5 = 1; } while(0)
#define RA5_SetDigitalMode()        do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set EN_MATRIX_n aliases
#define EN_MATRIX_n_TRIS                 TRISCbits.TRISC0
#define EN_MATRIX_n_LAT                  LATCbits.LATC0
#define EN_MATRIX_n_PORT                 PORTCbits.RC0
#define EN_MATRIX_n_WPU                  WPUCbits.WPUC0
#define EN_MATRIX_n_OD                   ODCONCbits.ODCC0
#define EN_MATRIX_n_ANS                  ANSELCbits.ANSC0
#define EN_MATRIX_n_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define EN_MATRIX_n_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define EN_MATRIX_n_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define EN_MATRIX_n_GetValue()           PORTCbits.RC0
#define EN_MATRIX_n_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define EN_MATRIX_n_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define EN_MATRIX_n_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define EN_MATRIX_n_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define EN_MATRIX_n_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define EN_MATRIX_n_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define EN_MATRIX_n_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define EN_MATRIX_n_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set OE_n aliases
#define OE_n_TRIS                 TRISCbits.TRISC2
#define OE_n_LAT                  LATCbits.LATC2
#define OE_n_PORT                 PORTCbits.RC2
#define OE_n_WPU                  WPUCbits.WPUC2
#define OE_n_OD                   ODCONCbits.ODCC2
#define OE_n_ANS                  ANSELCbits.ANSC2
#define OE_n_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define OE_n_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define OE_n_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define OE_n_GetValue()           PORTCbits.RC2
#define OE_n_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define OE_n_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define OE_n_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define OE_n_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define OE_n_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define OE_n_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define OE_n_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define OE_n_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set LATCH aliases
#define LATCH_TRIS                 TRISCbits.TRISC4
#define LATCH_LAT                  LATCbits.LATC4
#define LATCH_PORT                 PORTCbits.RC4
#define LATCH_WPU                  WPUCbits.WPUC4
#define LATCH_OD                   ODCONCbits.ODCC4
#define LATCH_ANS                  ANSELCbits.ANSC4
#define LATCH_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LATCH_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LATCH_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LATCH_GetValue()           PORTCbits.RC4
#define LATCH_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LATCH_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LATCH_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define LATCH_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define LATCH_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define LATCH_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define LATCH_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define LATCH_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/