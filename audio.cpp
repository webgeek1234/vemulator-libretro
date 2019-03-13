/*
Copyright (c) 2019, Mahmoud N. Jaoune
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

