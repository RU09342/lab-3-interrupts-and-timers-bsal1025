#include <msp430.h> 

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;                            // P1.0 set to output
  P4DIR |= BIT7;                            // P4.7 set to output

  P1REN = BIT1;                             // Enable resistor on P1.1
  P1OUT = BIT1;                             // Set resistor on P1.1 to pull-up
  P1IES |= BIT1;                            // Set interrupt edge select to low
  P1IE |= BIT1;                             // Enable interrupt on P1.1
  P1IFG &= ~BIT1;                           // Clear the interrupt flag

  TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA0CCR0 = 3277;                           // Set initial frequency to 10 Hz
  TA0CTL = TASSEL_1 + MC_1;                 // ACLK, up mode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Button on P1.1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT1)                        // If button on P1.1 is pressed
    {
      TA1CTL = TASSEL_1 + MC_2;             // Enable timer A1: ACLK, continuous mode
      P1OUT ^= 0x01;                        // Toggle P1.0
      P1IES &= ~BIT1;                       // Flip edge to high
    }
    else
    {
        TA0CCR0 = TA1R;                     // Set CCR0 to amount of time timer A1 is on
        P1OUT &= ~BIT0;                     // Turn off LED on P1.0
        P1IES |= BIT1;                      // Flip edge back to low
        TA1CTL = TACLR;                     // Clear timer
    }
    P1IFG &= ~BIT1;                         // Clear interrupt flag
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)
{
       P4OUT ^= 0x80;                      // Toggle P4.7

}
