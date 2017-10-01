#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0+BIT6;                            // P1.0 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 65000;

  CCTL1 = CCIE;
  CCR1 = 30000;
  TACTL = TASSEL_2 + MC_3,ID_3;             // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0

}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void)
{
    switch(__even_in_range(TA0IV, 14))
    {
    case 2: // TBCCR1 interrupt
      P1OUT ^= 0x40;
      break;
    default: ;
    }

}
