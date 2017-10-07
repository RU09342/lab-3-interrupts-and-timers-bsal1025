/*
 * Button Interrupt
 *
 *  Created on: Oct 4, 2017
 *  Last Updated on: Oct 4, 2017
 *  Author: Brandon Salamone
 */

Libraries Used:
 msp430.h is the only library used in these programs.

Dependencies:
The msp430.h library does not have any dependencies.

User Interface:
Each program is initialized with the push of a button. This causes each program to enter its ISR. Once inside the ISR, holding the button down will cause
an LED to blink. When the button is released the LED will either remain on or shut off depending on the LED state when the button is released.   

Common Functionality Among All Processors:
All processors contain these elements in order to blink multiple LEDs at different rates:
 1. The watchdog timer is cleared
 2. The P1DIR is set such that two LEDs will be outputs
 3. The PxOUT and PxREN registers are set such that the pull-up resistors are enabled in a button on each board
 4. The PxIE and PxIES are set to the same value as PxOUT and PxREN to enable and select the interrupt on the button in use
 5. The PxIFG registers are set to the inverse of the other interrupt registers to clear the interrupt flag on each processor
 6. Within every ISR is an if statement that controls which LED blinks. The functionality of this if statement is described above
    in user interface.

Key Differences Between Processors:
 1. MSP430FR2311, MSP430FR6989, and MSP430FR5994 all have an extra line of code that disables the default high-impedance mode. The MSP430F5529 and
    MSP430G2553 processors do not need this line of code. 

 2. Different Processors have different LED pin assignments. Below the LED pin assignments will be shown for each processor.
    msp430F5529: P1.0 and P4.7
    msp430FR2311: P1.0 and P2.0
    msp430FR5994: P1.0 and P1.1 *
    msp430FR5989: P1.0 and P9.7
    msp430G2553: P1.0 and P1.6 *
    
    * For these processors, the hexadecimal values pertaining to each pin can be combined into one number, since they have P1 in common.
      For example in the msp430FR5994 processor it would be: P1DIR = BIT0 | BIT1 = 0x03 

  3. Different processors also use different buttons to control the interrupt in the code. The button pins are shown below:
     msp430F5529: P1.1
     msp430FR2311: P1.1
     msp430FR5994: P5.6
     msp430FR5989: P1.1
     msp430G2553: P1.3
  
  4. The MSP430G2553 processor is set up to run the "color change" portion of the extra work from lab 2 in its ISR. On start-up, the green LED blinks. 
     When the button at P1.3 is held down, the red LED blinks instead.

