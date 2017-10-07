/*
 * getclock.h
 *
 *  Created on: Oct 3, 2017
 *      Author: bsala_000
 */

#ifndef GETCLOCK_H_
#define GETCLOCK_H_
#include <msp430.h>
#include <stdio.h>

int getclock(char clocktype,int frequency1,int divider);
int getclock2(char clocktype, int frequency2, int divider);

int getclock(char clocktype, int frequency1, int divider)
{
    long int i;

    if(clocktype == 'A')
    {
        if(divider == 0)
                {
                  i = 32768/frequency1;
                  if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 1)
                {
                 i = 16384/frequency1;
                  if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 2)
                {
                  i = 8192/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 3)
                {
                  i = 4096/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
    }
    if(clocktype == 'S')
    {
        if(divider == 0)
                {
                  i = 1000000/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 1)
                {
                  i = 500000/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 2)
                {
                  i = 250000/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 3)
                {
                  i = 125000/frequency1;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
    }
return 0;
}

int getclock2(char clocktype, int frequency2, int divider)
{
    long int i;

    if(clocktype == 'A')
    {
        if(divider == 0)
                {
                  i = 32768/frequency2;
                  if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 1)
                {
                 i = 16384/frequency2;
                  if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 2)
                {
                  i = 8192/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
         if(divider == 3)
                {
                  i = 4096/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
    }
    if(clocktype == 'S')
    {
        if(divider == 0)
                {
                  i = 1000000/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 1)
                {
                  i = 500000/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 4)
                {
                  i = 250000/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
        if(divider == 8)
                {
                  i = 125000/frequency2;
                   if(i < 65535)
                  return i;
                  else
                  return 10000;
                }
    }
return 0;
}


#endif /* GETCLOCK_H_ */

