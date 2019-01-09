/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _T0_H_
#define _T0_H_

#include "ram.h"
#include "interrupts.h"
#include "cpu.h"

class VE_VMS_TIMER0
{
public:
    VE_VMS_TIMER0(VE_VMS_RAM *_ram, VE_VMS_INTERRUPTS *_intHandler, VE_VMS_CPU *_cpu, byte *_prescaler);
    ~VE_VMS_TIMER0();

    void runTimer();
    
private:
	int TRLStarted;
    int TRHStarted;
    VE_VMS_RAM *ram;
    VE_VMS_INTERRUPTS *intHandler;
    VE_VMS_CPU *cpu;
    byte *prescaler;
    
    double TRL_data;
	double TRH_data;
};

#endif // _T0_H_
