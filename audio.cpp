/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
*/

#include "audio.h"

VE_VMS_AUDIO::VE_VMS_AUDIO(VE_VMS_CPU *_cpu, VE_VMS_RAM *_ram)
{
	T1LR_reg = 0;
	T1LC_reg = 128;
	IsEnabled = false;
	T1LR_old = -1;
	
	ram = _ram;
	cpu = _cpu;
	
	sampleArray = (int16_t *)calloc(2*SAMPLE_RATE, sizeof(int16_t));	//Multiplied by 2 because 2 channels
	
	frequency = 146539.3;
}

VE_VMS_AUDIO::~VE_VMS_AUDIO()
{
	free(sampleArray);
}

void VE_VMS_AUDIO::generateSignal(retro_audio_sample_t &audio_cb)
{
	if(!IsEnabled) 
	{
		audio_cb(0, 0);
		return;
	}
	
	double T1LC_reg_D = T1LC_reg;
	double T1LR_reg_D = T1LR_reg;

	//1 second is equal to 32768 samples

	int16_t waveWidth = (int16_t) ((256 - T1LR_reg_D) * (SAMPLE_RATE / frequency));    //1 Wave (In samples not seconds)

	double lowLevelWidth = abs((((T1LC_reg_D - T1LR_reg_D)/(256 - T1LR_reg_D)) * waveWidth));

	//lowLevelWidth = 0.5 * waveWidth;	//Many mini-games don't care about T1LD, 0.5 would play a sound close to the original.

	for(int i = 0; i < SAMPLE_RATE / FPS; i++)
	{
		int16_t amplitude = 0x7FFF;
		if(waveWidth != 0) 
		{
			if((i%waveWidth) < lowLevelWidth) amplitude = 0;
		}
		
		audio_cb(amplitude, amplitude);
	}
}

void VE_VMS_AUDIO::setAudioFrequency(double f)
{
	frequency = f;
}

void VE_VMS_AUDIO::setT1(int b)
{
	T1LR_reg = b & 0xFF;
}

void VE_VMS_AUDIO::setT1C(int b)
{
	T1LC_reg = b & 0xFF;
}

void VE_VMS_AUDIO::setEnabled(bool e)
{
	IsEnabled = e;
}

void VE_VMS_AUDIO::runAudioCheck() 
{
	if(!IsEnabled) 
	{
		size_t count = SAMPLE_RATE * 2;
		
		//Empty signal (No sound)
		for(size_t i = 0; i < count; i++)
			sampleArray[i] = 0;
			
		T1LR_old = -1;
	}
	else if(T1LR_old != T1LR_reg) 
		//generateSignal();

	T1LR_old = T1LR_reg;

}

int16_t *VE_VMS_AUDIO::getSignal()
{
	return sampleArray;
}

