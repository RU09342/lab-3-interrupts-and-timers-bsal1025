/*
 * MSP430F5529_TIMERA_BLINK.c
 *
 *  Created on: Sep 30, 2017
 *      Author: bsala_000
 */

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0; // P1.0 output
  P4DIR |= BIT7;
  TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA0CCR0 = 65000;


  TA0CCTL1 = CCIE;
  TA0CCR1 = 30000;
  TA0CTL = TASSEL_2 + MC_3 + ID_3;             // SMCLK, upmode

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
      P4OUT ^= 0x80;
      break;
    default: ;
    }

}
