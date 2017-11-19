#include "Arduino.h"
#include "utility.h"


unsigned long longFromArray(byte* start) {
	unsigned long val;
	for (byte a=0; a<4; ++a)
		for (byte b=0; b<8; ++b)
			bitWrite(val, (a*8)+b, bitRead(*(start+a), b));
	return val;
	
}
void longToArray(byte* start, unsigned long val) {
	for (byte c=0; c<4; ++c) {
		*(start+c) = lowByte(val);
		val = val >> 8;
	}
}