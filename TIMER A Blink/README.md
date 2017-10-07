/*
 * Timer A Blink
 *
 *  Created on: Oct 4, 2017
 *  Last Updated on: Oct 7, 2017
 *  Author: Brandon Salamone
 */

Libraries Used:
 msp430.h and stdio.h are used in these programs.

Dependencies:
The file getclock.h is dependent on both msp430.h and stdio.h and the program files are dependent upon getclock.h.

User Interface:
Each program takes in several values which determine how fast the LEDs involved will blink. Once the program runs, the LEDs will blink at each 
given frequency. Different clock divider settings will quicken or slow down the blinking. It is possible to have both LEDs blink at the same rate
or at different rates by setting the frequencies at the beginning of the program accordingly.   

Common Functionality Among All Processors:
All processors contain these elements in order to blink multiple LEDs at different rates:
 1. The watchdog timer is cleared
 2. The P1DIR and/or PxDIR are set such that two LEDs will be outputs
 3. The PxOUT registers, when used, are set such that the GPIO will be an output in each program
 4. All programs use functions found in getclock.h to convert a frequency in Hz provided by the user into a value the timer interrupts can use
 5. The Tx0CCTL0 and Tx0CCTL1 registers are always set to CCIE to enable the timer interrupts in every program
 6. The Tx0CCR0 registers are always set to the value that the getclock function outputs so as to attain the proper frequency
 7. The TxCCR1 registers are always set to the value that the getclock2 function outputs so as to attain the proper frequency
 8. All processor programs have a line of code that tells the processor to enter low power mode with interrupt
 9. Each program contains two ISRs. The first is always the same in that the only command issued is to toggle the LED on P1.0 The second ISR
    is more complicated in that it uses a switch statement to determine when it is appropriate to blink the second LED. Without this switch
    statement, the second LED will not blink.

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
