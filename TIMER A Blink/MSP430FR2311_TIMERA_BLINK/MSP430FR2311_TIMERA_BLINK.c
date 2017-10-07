#include <getclock.h>

int main(void)
{
    char clocktype = 'S';                   // Enter S for SMCLK or A for ACLK
    int frequency1 = 2;                     // Enter frequency in Hz for LED 1.0
    int frequency2 = 4;                     // Enter frequency in Hz for LED 2.0
    int divider = 3;                        // Set clock divider to 0 for full speed
                                            // 1 for half speed, 2 for 1/4 speed,
                                            // and 3 for 1/8 speed
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;                            // P1.0 as an output
  P1OUT |= BIT0;                            // Set P1 as an output
  P2DIR |= BIT0;                            // Set P2.0 as an output
  P2OUT |= BIT0;                            // Set P2 as an output
  PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode,
                                            // to activate previously configured port settings
                                            // Code Will Not Run Without This Line

  TB0CCTL0 |= CCIE;                         // CCR0 interrupt enabled
  TB0CCR0 = getclock(clocktype,frequency1,divider); // Tells Timer to Count Up to output
                                                    // value of getclock before rolling over

  TB0CCTL1 |= CCIE;                                  // CCR1 interrupt enabled
  TB0CCR1 = getclock2(clocktype,frequency2,divider); // Tells Timer to Count Up to output
                                                     // value of getclock2 before rolling over
  TB0CTL |= TBSSEL__SMCLK + MC__UP+ID_3;             // SMCLK, upmode, 1/8 clock divider

  __bis_SR_register(LPM0_bits | GIE);                // Enter LPM0 w/ interrupt
  __no_operation();
}

// Timer B0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TimerB0_ISR (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0

}
// Timer B1 interrupt service routine
#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void)
{
    switch(__even_in_range(TB0IV, 14))     // Switch statement that tells the compiler to switch the
                                           // interrupt vector if and only if the value is even
                                           // between 0 and 14
    {
    case 2:
    P2OUT ^= 0x01;                        // If the value passed through the switch statement is 2
                                          // toggle P2.0
      break;
    default: ;                            // Otherwise do nothing
    }

}

