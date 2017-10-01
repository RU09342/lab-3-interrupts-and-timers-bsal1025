#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;// P1.0 output
  P1OUT |= BIT0;
  P2DIR |= BIT0;
  P2OUT |= BIT0;
  PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode,
                                              // to activate previously configured port settings
                                              // Code Will Not Run Without This Line
  TB0CCTL0 |= CCIE;                             // CCR0 interrupt enabled
  TB0CCR0 = 65000;

  TB0CCTL1 |= CCIE;
  TB0CCR1 = 20000;
  TB0CTL |= TBSSEL__SMCLK + MC__UP;             // SMCLK, upmode

  __bis_SR_register(LPM0_bits | GIE);       // Enter LPM0 w/ interrupt
  __no_operation();
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TimerB0_ISR (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0

}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TimerB1_ISR(void)
{
    switch(__even_in_range(TB0IV, 14))
    {
    case 2: // TBCCR1 interrupt
      P2OUT ^= 0x01;
      break;
    default: ;
    }

}
