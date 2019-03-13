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

#ifndef _FLASH_H_
#define _FLASH_H_

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "flashfile.h"
#include "ram.h"

class VE_VMS_FLASH
{
public:
    VE_VMS_FLASH(VE_VMS_RAM *_ram);
    ~VE_VMS_FLASH();

    ///Loads raw VMS data to be easily accessed.
    //romType 0: Memory Dump (.bin)
    //romType 1: VMS file
    //romType 2: DCI file
    void loadROM(byte *d, size_t buffSize, int romType, const char *fileName, bool enableSave);

    ///Returns raw VMS data and its size
    size_t getROM(byte *out);

    ///Returns data
    size_t getData(byte *out);


    //Operations
    ///Returns byte at address. (No banking)
    byte getByte(size_t address);

    ///Returns byte at address (With banking)
    byte readByte(size_t address);

    //Returns int16 at address (Little-endian)
    int getWord(size_t address);

    ///Writes int to address
    void writeByte(size_t address, byte d);

    //Writes int to raw address
    void writeByte_RAW(size_t address, byte d);

    ///Writes int16 to address (Little-endian)
    void writeWord(size_t address, byte d);

    ///Get block data (512)
    void readBlock(int blockNumber, byte *out);
    
    ///Write data to block (512)
    void writeBlock(int blockNumber, byte *in);
    
    ///Checks if card is corrupt
    bool IsCorrupt();

    ///Counts files in directory
    int countFiles();

    //File operations
    ///Get file info from directory depending on its index
    VE_VMS_FLASH_FILE getFileAt(int index);

    ///Get file info from directory depending on its name
    VE_VMS_FLASH_FILE getFile(const char *name);
    
    ///Counts number of mini-games found in ROM
    int countGames();

    //FAT operations
    ///Get data of file from FAT FS
    size_t getFileData(VE_VMS_FLASH_FILE fileinfo, byte *out);
    
private:
    //File structure
    byte *userData;
    byte *directory;
    byte *FAT;
    byte *rootBlock;
    byte *data;
    FILE *flashWriter = NULL;
    char *romName;
    bool IsRealFlash;
    bool IsSaveEnabled;
    
    VE_VMS_RAM *ram;
};

#endif // _FLASH_H_
