#ifndef utility_h
#define utiity_h

#include "Arduino.h"


#define castArrayTo(a, b) *( (a *) (b) )
void longToArray(byte* start, unsigned long val);


#endif