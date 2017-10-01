#include <msp430.h>

void main (void)
{

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= BIT0|BIT6;                            // Set P1.0 to output direction
    P1OUT &= ~(BIT0|BIT6);

    P1REN |= BIT3;                            // Enable P1.1 internal resistance
    P1OUT |= BIT3;                            // Set P1.1 as pull-Up resistance
    P1IES &= BIT3;                           // P1.1 Lo/Hi edge
    P1IFG &= ~BIT3;                           // P1.1 IFG cleared
    P1IE |= BIT3;                             // P1.1 interrupt enabled

    __bis_SR_register( GIE );                 // Enable interrupts globally

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if( !(P1IN & 0x08) )        // Button on P1.3 (S2) pressed
        {
          P1OUT ^= 0x01;            // Toggle LED on P1.0
          __delay_cycles( 250000 );   // Delay to see blinking
        }
        else                        // Button released
        {
          P1OUT ^= 0x40;            // Toggle LED on P1.6
          __delay_cycles( 250000 );   // Delay to see blinking
        }
}
