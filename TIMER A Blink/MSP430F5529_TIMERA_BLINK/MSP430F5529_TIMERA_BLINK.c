/*
 * MSP430F5529_TIMERA_BLINK.c
 *
 *  Created on: Sep 30, 2017
 *      Author: bsala_000
 */
#include <getclock.h>

int main(void)
{
    char clocktype = 'S';                   // Enter S for SMCLK or A for ACLK
    int frequency1 = 2;                     // Enter frequency in Hz for LED 1.0
    int frequency2 = 4;                     // Enter frequency in Hz for LED 4.7
    int divider = 2;                        // Set clock divider to 0 for full speed
                                            // 1 for half speed, 2 for 1/4 speed,
                                            // and 3 for 1/8 speed
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;                            // P1.0 set to output
  P4DIR |= BIT7;                            // P4.7 set to output
  TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA0CCR0 = getclock(clocktype,frequency1,divider);  // Tells Timer to Count Up to output
                                                     // value of getclock before rolling over


  TA0CCTL1 = CCIE;                                   // CCR1 interrupt enabled
  TA0CCR1 = getclock2(clocktype,frequency2,divider); // Tells timer to count up to output value of
                                                     // getclock2 before rolling over
  TA0CTL = TASSEL_2 + MC_3 + ID_2;                   // SMCLK, upmode, 1/4 clock divider

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

// Timer A1 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void)
{
    switch(__even_in_range(TA0IV, 14))     // Switch statement that tells the compiler to switch the
                                           // interrupt vector if and only if the value is even
                                           // between 0 and 14
    {
    case 2:
      P4OUT ^= 0x80;                      // If the value passed through the switch statement is 2
                                          // toggle P4.7
      break;
    default: ;                            // Otherwise do nothing
    }

}
