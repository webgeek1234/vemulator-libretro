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

#include "flashfile.h"


VE_VMS_FLASH_FILE::VE_VMS_FLASH_FILE()
{

}

VE_VMS_FLASH_FILE::VE_VMS_FLASH_FILE(int index, VMS_FILE_TYPE t, int firstblock, char *name, int size, int header)
{ 
	//fileNumber means directory entry
	fileIndex = index;
	type = t;
	startBlock = firstblock;
	fileName = name;
	fileSize = size;
	headerBlock = header;
}

///Copy constructor
VE_VMS_FLASH_FILE::VE_VMS_FLASH_FILE(VE_VMS_FLASH_FILE &c)
{
	fileIndex = c.getFileIndex();
	type = c.getType();
	startBlock = c.getStartBlock();
	fileName = c.getFileName();
	fileSize = c.getFileSize();
	headerBlock = c.getHeaderBlock();
}

VMS_FILE_TYPE VE_VMS_FLASH_FILE::getType(int d)
{
	d &= 0xFF;
	if(d == 0x00) return NONE;
	else if(d == 0x33) return DATA;
	else if(d == 0xCC) return GAME;
	else return UNKNOWN;
}

//Setters and getters
VMS_FILE_TYPE VE_VMS_FLASH_FILE::getType()
{
	return type;
}

int VE_VMS_FLASH_FILE::getStartBlock()
{
	return startBlock;
}

char * VE_VMS_FLASH_FILE::getFileName()
{
	return fileName;
}

int VE_VMS_FLASH_FILE::getFileSize()
{
	return fileSize;
}

int VE_VMS_FLASH_FILE::getHeaderBlock()
{
	return headerBlock;
}

int VE_VMS_FLASH_FILE::getFileIndex() 
{ 
	return fileIndex; 
}

void VE_VMS_FLASH_FILE::setType(VMS_FILE_TYPE t)
{
	type = t;
}

void VE_VMS_FLASH_FILE::setStartBlock(int s)
{
	startBlock = s;
}

void VE_VMS_FLASH_FILE::setFileName(char *name)
{
	fileName = name;
}

void VE_VMS_FLASH_FILE::setFileSize(int size)
{
	fileSize = size;
}

void VE_VMS_FLASH_FILE::setHeaderBlock(int header)
{
	headerBlock = header;
}

void VE_VMS_FLASH_FILE::setFileIndex(int index) 
{
	fileIndex = index;
}
