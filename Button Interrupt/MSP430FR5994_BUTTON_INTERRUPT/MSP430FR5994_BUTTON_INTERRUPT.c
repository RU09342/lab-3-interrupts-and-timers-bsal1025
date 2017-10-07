#include <msp430.h>

void main (void)
{

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= BIT0;                            // Set P1.0 to output direction
    P1OUT &= ~BIT0;

    P5REN |= BIT6;                            // Enable P1.6 internal resistance
    P5OUT |= BIT6;                            // Set P1.6 as pull-Up resistance
    P5IES &= BIT6;                            // P1.6 Lo/Hi edge
    P5IFG &= ~BIT6;                           // P1.6 IFG cleared
    P5IE |= BIT6;                             // P1.6 interrupt enabled

    PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode
                                              // Required for Code to Properly Function

    __bis_SR_register( GIE );                 // Enable interrupts globally

}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
  if( !(P5IN & BIT6))                      // If push button P5.6 is pressed
  {
         P1OUT ^= BIT0;                    // XOR P1.0
         __delay_cycles(100000);           // Delay to see blinking
  }
}
