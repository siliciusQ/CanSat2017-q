#include "Arduino.h"
#include "utility.h"


unsigned long longFromArray(void* start) {
	// return a value of any ponter casted to "unisgned long pointer"
	return *( (unsigned long *) start );
	
}
void longToArray(byte* start, unsigned long val) {
	for (byte c=0; c<4; ++c) {
		*(start+c) = lowByte(val);
		val = val >> 8;
	}
}