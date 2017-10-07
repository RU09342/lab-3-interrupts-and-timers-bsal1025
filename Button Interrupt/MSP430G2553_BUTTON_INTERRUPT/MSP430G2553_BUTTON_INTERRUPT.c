#include <msp430.h>

void main (void)
{

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= BIT0|BIT6;                       // Set P1.0 and P1.6 in the output direction
    P1OUT &= ~(BIT0|BIT6);                    // Set P1.0 and P1.6 as outputs

    P1REN |= BIT3;                            // Enable P1.3 internal resistance
    P1OUT |= BIT3;                            // Set P1.3 as pull-Up resistance
    P1IES &= BIT3;                            // P1.3 Lo/Hi edge
    P1IFG &= ~BIT3;                           // P1.3 IFG cleared
    P1IE |= BIT3;                             // P1.3 interrupt enabled

    __bis_SR_register( GIE );                 // Enable interrupts globally

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if( !(P1IN & 0x08) )              // Button on P1.3 (S2) pressed
        {
          P1OUT ^= 0x01;              // Toggle LED on P1.0
          __delay_cycles( 250000 );   // Delay to see blinking
        }
        else                          // Button released
        {
          P1OUT ^= 0x40;              // Toggle LED on P1.6
          __delay_cycles( 250000 );   // Delay to see blinking
        }
}
