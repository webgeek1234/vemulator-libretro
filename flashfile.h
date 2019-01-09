/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _FLASHFILE_H_
#define _FLASHFILE_H_

enum VMS_FILE_TYPE
{
	DATA,
	GAME,
	NONE,
	UNKNOWN = -1
};

///This describes a file inside the VMS
class VE_VMS_FLASH_FILE
{
	
public:	
    VE_VMS_FLASH_FILE();

    VE_VMS_FLASH_FILE(int index, VMS_FILE_TYPE t, int firstblock, char *name, int size, int header);

    ///Copy constructor
    VE_VMS_FLASH_FILE(VE_VMS_FLASH_FILE &c);

    static VMS_FILE_TYPE getType(int d);

    //Setters and getters
    VMS_FILE_TYPE getType();

    int getStartBlock();

    char *getFileName();

    int getFileSize();

    int getHeaderBlock();

    int getFileIndex();

    void setType(VMS_FILE_TYPE t);

    void setStartBlock(int s);

    void setFileName(char *name);

    void setFileSize(int size);

    void setHeaderBlock(int header);

    void setFileIndex(int index);
    
private:
    VMS_FILE_TYPE type;
    int startBlock;
    char *fileName;
    int fileSize;   ///In blocks
    int headerBlock;
    int fileIndex;
};

#endif // _FLASHFILE_H_
