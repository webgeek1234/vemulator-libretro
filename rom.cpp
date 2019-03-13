/*
Copyright (c) 2019, Mahmoud N. Jaoune
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

#include "rom.h"

VE_VMS_ROM::VE_VMS_ROM()
{
	data = new size_t[0x100000];
}

VE_VMS_ROM::~VE_VMS_ROM()
{
	delete []data;
}

//Setters and getters
byte VE_VMS_ROM::readByte(size_t address)
{
	return data[address] & 0xFF;
}

void VE_VMS_ROM::writeByte(size_t address, byte b)
{
	data[address] = b & 0xFF;
}

//Memory operations
void VE_VMS_ROM::loadData(byte *d, size_t buffSize, size_t size)
{
	if(buffSize < size) return;
	for(size_t i = 0; i < size; i++)
		data[i] = d[i];
}

void VE_VMS_ROM::loadData(byte *d, size_t buffSize)
{
	for(size_t i = 0; i < buffSize; i++)
		data[i] = d[i];
}

size_t *VE_VMS_ROM::getData()
{
	return data;
}

