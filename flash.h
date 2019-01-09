/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
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
