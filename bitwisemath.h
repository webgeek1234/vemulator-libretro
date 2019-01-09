/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _BITWISEMATH_H_
#define _BITWISEMATH_H_

#include "common.h"

//These functions perform low-level bitwise operations.
//Flags [0|0|0|0|0|O|A|C/B]
///This is an 8-bit adder. Returns sum as first in array, then flags.
void add8(byte i1, byte i2, byte carry, byte *result);

void sub8(byte i1, byte i2, byte carry, byte *result);

///This is an 8-bit subtractor (op1 - op2). Returns difference as first in array, then flags.
void sub8_old(byte i1, byte i2, byte *result);

//Take complement
byte comp8(byte op);

//Convert to signed
byte toSigned8(byte op);

///Converts normal number byteo BCD
int int2BCD(int dec);

#endif // _BITWISEMATH_H_
