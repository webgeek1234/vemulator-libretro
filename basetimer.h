/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _BASETIMER_H_
#define _BASETIMER_H_

#include "ram.h"
#include "interrupts.h"
#include "cpu.h"

class VE_VMS_BASETIMER
{
public:
    VE_VMS_BASETIMER(VE_VMS_RAM *_ram, VE_VMS_INTERRUPTS *_intHandler, VE_VMS_CPU *_cpu);
    ~VE_VMS_BASETIMER();

    void runTimer();
    
private:
	double BTR;    //14-bit
	VE_VMS_RAM *ram;
	VE_VMS_INTERRUPTS *intHandler;
	VE_VMS_CPU *cpu;
};

#endif // _BASETIMER_H_
