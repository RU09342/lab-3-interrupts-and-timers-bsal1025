/*
 * getclock.h
 *
 *  Created on: Oct 3, 2017
 *  Last Updated: Oct 7, 2017
 *      Author: bsala_000
 */

#ifndef GETCLOCK_H_
#define GETCLOCK_H_
#include <msp430.h>
#include <stdio.h>

int getclock(char clocktype,int frequency1,int divider);     // Program to convert Hz into proper value
                                                             // for Timerx0
int getclock2(char clocktype, int frequency2, int divider);  // Program to convert Hz into proper value
                                                             // for Timerx1
int getclock(char clocktype, int frequency1, int divider)
{
    long int i;                                              // Temporary variable for if statements

    if(clocktype == 'A')                                     // ACLK portion of function
    {
        if(divider == 0)
                {
                  i = 32768/frequency1;                      // If condition is met, divide ACLK by the frequency
                  if(i < 65535)                              // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                              // Safe value to be returned to main program
                }
         if(divider == 1)
                {
                 i = 16384/frequency1;                      // If condition is met, divide ACLK by 2, then by the frequency
                  if(i < 65535)                             // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                             // Safe value to be returned to main program
                }
         if(divider == 2)
                {
                  i = 8192/frequency1;                     // If condition is met, divide ACLK by 4, then by the frequency
                   if(i < 65535)                           // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                            // Safe value to be returned to main program
                }
         if(divider == 3)
                {
                  i = 4096/frequency1;                     // If condition is met, divide ACLK by 8, then by the frequency
                   if(i < 65535)                           // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                            // Safe value to be returned to main program
                }
    }
    if(clocktype == 'S')                                   // SMCLK portion of function
    {
        if(divider == 0)
                {
                  i = 1000000/frequency1;                 // If condition is met, divide SMCLK by the frequency
                   if(i < 65535)                          // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                           // Safe value to be returned to main program
                }
        if(divider == 1)
                {
                  i = 500000/frequency1;                  // If condition is met, divide SMCLK by 2, then by the frequency
                   if(i < 65535)                          // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                           // Safe value to be returned to main program
                }
        if(divider == 2)
                {
                  i = 250000/frequency1;                 // If condition is met, divide SMCLK by 4, then by the frequency
                   if(i < 65535)                         // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                          // Safe value to be returned to main program
                }
        if(divider == 3)
                {
                  i = 125000/frequency1;                // If condition is met, divide SMCLK by 8, then by the frequency
                   if(i < 65535)                        // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                         // Safe value to be returned to main program
                }
    }
return 0;
}

int getclock2(char clocktype, int frequency2, int divider) // new function to get second value for second LED
{
    long int i;

    if(clocktype == 'A')
    {
        if(divider == 0)
                {
                  i = 32768/frequency2;          // If condition is met, divide ACLK by the frequency
                  if(i < 65535)                  // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                  // Safe value to be returned to main program
                }
         if(divider == 1)
                {
                 i = 16384/frequency2;          // If condition is met, divide ACLK by 2, then by the frequency
                  if(i < 65535)                 // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                 // Safe value to be returned to main program
                }
         if(divider == 2)
                {
                  i = 8192/frequency2;         // If condition is met, divide ACLK by 4, then by the frequency
                   if(i < 65535)               // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;                // Safe value to be returned to main program
                }
         if(divider == 3)
                {
                  i = 4096/frequency2;        // If condition is met, divide ACLK by 8, then by the frequency
                   if(i < 65535)              // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;               // Safe value to be returned to main program
                }
    }
    if(clocktype == 'S')
    {
        if(divider == 0)
                {
                  i = 1000000/frequency2;    // If condition is met, divide SMCLK by the frequency
                   if(i < 65535)             // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;              // Safe value to be returned to main program
                }
        if(divider == 1)
                {
                  i = 500000/frequency2;     // If condition is met, divide SMCLK by 2, then by the frequency
                   if(i < 65535)             // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;              // Safe value to be returned to main program
                }
        if(divider == 4)
                {
                  i = 250000/frequency2;    // If condition is met, divide SMCLK by 4, then by the frequency
                   if(i < 65535)            // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;             // Safe value to be returned to main program
                }
        if(divider == 8)
                {
                  i = 125000/frequency2;   // If condition is met, divide SMCLK by 8, then by the frequency
                   if(i < 65535)           // Prevents values that exceed 16 bits from being returned
                  return i;
                  else
                  return 10000;            // Safe value to be returned to main program
                }
    }
return 0;
}


#endif /* GETCLOCK_H_ */
