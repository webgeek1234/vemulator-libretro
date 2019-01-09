/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _ROM_H_
#define _ROM_H_

#include "common.h"

class VE_VMS_ROM
{
public:
    VE_VMS_ROM();
    ~VE_VMS_ROM();

    //Setters and getters
    byte readByte(size_t address);

    void writeByte(size_t address, byte b);

    //Memory operations
    void loadData(byte *d, size_t buffSize, size_t size);

    void loadData(byte *d, size_t buffSize);

    size_t *getData();

private:
	size_t *data;
};

#endif // _ROM_H_
