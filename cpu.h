/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _CPU_H_
#define _CPU_H_

#include <vector>
#include "ram.h"
#include "rom.h"
#include "flash.h"
#include "interrupts.h"
#include "bitwisemath.h"

class VE_VMS_CPU
{
public:

	int state;   //0: stopped. 1: started.
	int EXTOld;
    int EXTNew;
    bool P3_taken;

	VE_VMS_CPU(VE_VMS_RAM *_ram, VE_VMS_ROM *_rom, VE_VMS_FLASH *_flash, VE_VMS_INTERRUPTS *_intHandler, bool hle);
	~VE_VMS_CPU();
	
	double getCurrentFrequency();
	void setFrequency(double f);

	//Memory operations
	//Reads a byte either from ROM or Flash, depending on value of EXT
	byte readByteRF(size_t address);
	
	//Writes a byte either from ROM or Flash, depending on value of EXT
	void writeByteRF(size_t address, byte d);
	
	
	//Read
	byte *readFromROM(size_t address, size_t byteCount);
	byte *readFromRAM(size_t address, size_t byteCount);
	
	//Write
	void writeToROM(byte *data, size_t dataSize, size_t address);
	void writeToRAM(byte *data, size_t dataSize, size_t address);
	
	//Address/Data functions
	//Immediate
	byte getAddress_i8();
	
	//Relative 8-bit (signed)
	signed char getAddress_r8();
	
	//Relative 8-bit when the opcode has bit specifiers (signed)
	signed char getAddress_r8_b3();
	
	//Relative 16-bit
	size_t getAddress_r16();
	
	//Direct 9-bit
	size_t getAddress_d9();
	
	//Direct 9-bit with bit assignment
	size_t getAddress_d9_b3();
	
	//Get bits (b3)
	byte getAddress_b3();
	
	//Indirect
	size_t getAddress_R();
	
	//Absolute 12-bit
	size_t getAddress_a12();
	
	//Absolute 16-bit
	size_t getAddress_a16();
	
	//Absolute 16-bit (But can select to get operand from ROM (EXT = 0) or Flash (EXT = 1), important for when an instruction changes EXT, it will always be followed by a JMPF)
	size_t getAddress_a16(byte _EXT);

    //FLAG operations
    void FLAG_setP();
    
    void FLAG_clearP();
    
    byte FLAG_getP();
    
    void FLAG_setOV();
    
    void FLAG_clearOV();
    
    byte FLAG_getOV();
    
    void FLAG_setAC();
    
    void FLAG_clearAC();
    
    byte FLAG_getAC();
    
    void FLAG_setCY();
    
    void FLAG_clearCY();
    
    byte FLAG_getCY();


    /******************************************************
     ******************************************************
     *  Instructions and interrupts
     ******************************************************
     ******************************************************/

    void processInterrupts();

    void performHLE(size_t entryAddress);

	//Interpreter
    int processInstruction(bool dbg);
    
private:
    size_t PC; //This counts where we reached in instruction memory (Starting from first instruction executed)
    int clock;   //In nanoseconds
    double frequency;
    int interruptLevel;
    int currentInterrupt;
    bool interruptsMasked;

    int instructionCount;
    
    VE_VMS_RAM *ram;
    VE_VMS_ROM *rom;
    VE_VMS_FLASH *flash;
    VE_VMS_INTERRUPTS *intHandler;
    
    std::vector<int> interruptQueue;
    
    bool IsHLE;
};

#endif // _CPU_H_
