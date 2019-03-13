/*
Copyright (c) 2019, Mahmoud Jaoune
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "bitwisemath.h"

//Flags [0|0|0|0|0|O|A|C/B]
//This is an 8-bit adder. Returns sum as first in array, then flags.
void add8(byte i1, byte i2, byte carry, byte *result)
{
	byte op1 = i1 & 0xFF;
	byte op2 = i2 & 0xFF;

	byte s = 0; //8-bits
	byte c = carry; //Assume its 1-bit

	byte flags = 0;

	byte c6 = 0;
	byte c7 = 0;

	//Start operation
	for(byte i = 0; i < 8; ++i)
	{
		//Take next bit
		byte bit1 = ((op1 & ((1 << i) & 0xFF)) >> i) & 0xFF;
		byte bit2 = ((op2 & ((1 << i) & 0xFF)) >> i) & 0xFF;

		//Sum them together
		byte z1 = (bit1 ^ bit2) & 0xFF;
		s |= ((c ^ z1) << i) & 0xFF;

		//Calculate carry
		byte c1 = (c & z1) & 0xFF;
		byte c2 = (bit1 & bit2) & 0xFF;
		c = (c1 | c2) & 0xFF;

		//Auxiliary flag set
		if(c != 0 && i == 3)
			flags |= 0x2;

		if(i == 6) c6 = c & 1;
		else if(i == 7) c7 = c & 1;
	}

	c &= 1;

	//Check carry
	if(c == 1)
		flags |= 0x1;
	//Check overflow
	if(c6 != c7)
		flags |= 0x4;
	result[0] = s & 0xFF;
	result[1] = flags & 0xFF;
}

void sub8(byte i1, byte i2, byte carry, byte *result)
{

	byte op1 = i1 & 0xFF;
	byte op2 = i2 & 0xFF;

	op2 ^= 0xFF;    //2's Complement
	op2 &= 0xFF;

	byte s = 0; //8-bits
	byte c = carry ^ 0xFF; //Assume its 1-bit
	c &= 1;

	byte flags = 0;

	byte c6 = 0;
	byte c7 = 0;

	//Start operation
	for(byte i = 0; i < 8; ++i)
	{
		//Take next bit
		byte bit1 = ((op1 & ((1 << i) & 0xFF)) >> i) & 0xFF;
		byte bit2 = ((op2 & ((1 << i) & 0xFF)) >> i) & 0xFF;

		//Sum them together
		byte z1 = (bit1 ^ bit2) & 0xFF;
		s |= ((c ^ z1) << i) & 0xFF;

		//Calculate carry
		byte c1 = (c & z1) & 0xFF;
		byte c2 = (bit1 & bit2) & 0xFF;
		c = (c1 | c2) & 0xFF;

		//Auxiliary flag set
		if(c == 0 && i == 3)
			flags |= 0x2;

		if(i == 6) c6 = c & 1;
		else if(i == 7) c7 = c & 1;
	}

	c ^= 0xFF;
	c &= 1;

	//Check carry
	if(c == 1)
		flags |= 0x1;
	//Check overflow
	if(c6 != c7)
		flags |= 0x4;

	result[0] = s & 0xFF;
	result[1] = flags & 0xFF;
}

//This is an 8-bit subtractor (op1 - op2). Returns difference as first in array, then flags.
void sub8_old(byte i1, byte i2, byte *result)
{
	byte op1 = i1 & 0xFF;
	byte op2 = i2 & 0xFF;


	byte d = 0; //8-bits
	byte b = 0; //Assume its 1-bit

	byte flags = 0;

	//Those following two will be used to calculate overflow flag later
	byte MSB1 = (op1 & 0x80) & 0xFF; //No need to shift them, since all of them are in the same place
	byte MSB2 = (op2 & 0x80) & 0xFF;

	for(byte i = 0; i < 8; ++i) 
	{
		//Take next bit
		byte bit1 = ((op1 & ((1 << i) & 0xFF)) >> i) & 0xFF;
		byte bit2 = ((op2 & ((1 << i) & 0xFF)) >> i) & 0xFF;

		//Sub them from each other
		byte z1 = (bit1 ^ bit2) & 0xFF;
		d |= ((b ^ z1) << i) & 0xFF;

		//Calculate borrow
		byte bit1_neg = (~bit1) & 0xF;   //Invert the bit (Only the bit)
		byte z1_neg = (~z1) & 0xF;

		byte b1 = (z1_neg & b) & 0xFF;
		byte b2 = (bit1_neg & bit2) & 0xFF;
		b = (b1 | b2) & 0xFF;

		//Auxiliary flag set
		if(b != 0 && i == 1)
			flags |= 0x2;
	}

	//Check carry flag
	if(b == 1)
		flags |= 0x1;

	//Check overflow
	byte resultMSB = (d & 0x80) & 0xFF;
	if((MSB1 == MSB2) && MSB1 != resultMSB)
		flags |= 0x4;
	result[0] = d & 0xFF;
	result[1] = flags & 0xFF;
}

//Take complement
byte comp8(byte op)
{
	return (((~op) & 0xFF) + 1) & 0xFF;
}

//Convert to signed
byte toSigned8(byte op)
{
	if(op < -127)
		return comp8(op);
	else return op;
}

//Converts normal number to BCD
//https://stackoverflow.com/questions/13247647/convert-integer-from-pure-binary-to-bcd
int int2BCD(int dec)
{
	int i = dec;
	int bcd = 0;
	int j = 0;
	
	for(; i > 0; i /= 10, j++)
		bcd |= (i % 10) << (j << 2);

	return bcd;
}
