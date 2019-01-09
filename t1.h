/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _T1_H_
#define _T1_H_

#include "audio.h"
#include "ram.h"
#include "interrupts.h"

class VE_VMS_TIMER1
{
public:
    VE_VMS_TIMER1(VE_VMS_RAM *_ram, VE_VMS_INTERRUPTS *_intHandler, VE_VMS_AUDIO *_audio);
    ~VE_VMS_TIMER1();

    void runTimer();
    
private:
    int TRLStarted;
    int TRHStarted;
    
    //The counters in T1 are implicit (Not visible to the programmer)
    VE_VMS_RAM *ram;
    VE_VMS_INTERRUPTS *intHandler;
    VE_VMS_AUDIO *audio;
};

#endif // _T1_H_
