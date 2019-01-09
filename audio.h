/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <math.h>
#include "libretro.h"
#include "common.h"
#include "cpu.h"
#include "ram.h"

class VE_VMS_AUDIO
{
public:
    VE_VMS_AUDIO(VE_VMS_CPU *_cpu, VE_VMS_RAM *_ram);
    
    ~VE_VMS_AUDIO();

    void generateSignal(retro_audio_sample_t &audio_cb);
    
    void setAudioFrequency(double f);

    void setT1(int b);

    void setT1C(int b);
    
    void setEnabled(bool e);

    void runAudioCheck();
    
    int16_t *getSignal();

private:
	int T1LR_reg;
	int T1LC_reg;
	bool IsEnabled;
	int T1LR_old;
	
	double frequency;	//This is supposed to be the CPU's frequency, but we have made the CPU's clock fixed
	
	int16_t *sampleArray;
	
	VE_VMS_CPU *cpu;
	VE_VMS_RAM *ram;
};

#endif // _AUDIO_H_
