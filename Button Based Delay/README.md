/*
 * Button-Based Delay
 *
 *  Created on: Oct 7, 2017
 *  Last Updated on: Oct 7, 2017
 *  Author: Brandon Salamone
 */

Libraries Used:
 msp430.h is the only library used in these programs.

Dependencies:
The msp430.h library does not have any dependencies.

User Interface:
Each program takes in several values which determine how fast the LEDs involved will blink. Once the program runs, the LEDs will blink at each 
given frequency. Different clock divider settings will quicken or slow down the blinking. It is possible to have both LEDs blink at the same rate
or at different rates by setting the frequencies at the beginning of the program accordingly.   

Common Functionality Among All Processors:
All processors contain these elements in order to blink multiple LEDs at different rates:
 1. The watchdog timer is cleared
 2. The P1DIR and/or PxDIR are set such that two LEDs will be outputs
 3. The PxOUT registers, when used, are set such that the resistor associated with the button used in the code will be a pull-up resistor
 4. The PxREN, PxIE, PxIES, and PxIFG registers are always set to one of the pins corresponding to a button on each board
 5. The Tx0CCTL0 registers are always set to CCIE to enable the timer interrupts in every program
 6. The Tx0CCR0 registers are always initialized at 3277 so that one of the LEDs initially blinks at 10 Hz on startup
 7. All processor programs have a line of code that tells the processor to enter low power mode with interrupt
 8. Each program contains two ISRs. The first performs multiple important tasks. First, the second timer (A1 or B1) is initialized. Then, an LED
    is turned on to indicate that the first ISR is active. Next, the interrupt edge select is flipped to be high. Then, once the button is released,
    CCR0 is set to the time the button was held down for. After that, the LED is turned off and the interrupt edge select goes back to low before 
    the cycle starts all over again. The second ISR simply causes an LED to toggle. The rate at which it toggles will be controlled by the length of time
    the button was pressed. 

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

 3. Unlike the other processors which use Timer A, the MSP430FR2311 processor uses Timer B. This difference causes only slight adjustments to 
    the code to make it work. 