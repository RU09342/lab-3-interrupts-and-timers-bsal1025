#include <msp430fr5994.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0+BIT1;                            // P1.0 output
  TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA0CCR0 = 65000;

  TA0CCTL1 = CCIE;
  TA0CCR1 = 30000;
  TA0CTL = TASSEL__SMCLK + MC_3;             // SMCLK, upmode
  PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode,
                                              // to activate previously configured port settings
                                              // Code Will Not Run Without This Line

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
      P1OUT ^= 0x02;
      break;
    default: ;
    }

}
