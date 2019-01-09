/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
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

