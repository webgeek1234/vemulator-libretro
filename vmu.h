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

#ifndef _VMU_H_
#define _VMU_H_

#include <time.h>
#include "common.h"
#include "ram.h"
#include "cpu.h"
#include "video.h"
#include "rom.h"
#include "audio.h"
#include "t0.h"
#include "t1.h"
#include "basetimer.h"
#include "interrupts.h"
#include "bitwisemath.h"

class VMU
{
public:
	VE_VMS_RAM *ram;
	VE_VMS_ROM *rom;
	VE_VMS_FLASH *flash;
	VE_VMS_CPU *cpu;
	VE_VMS_TIMER0 *t0;
	VE_VMS_TIMER1 *t1;
	VE_VMS_BASETIMER *baseTimer;
	VE_VMS_INTERRUPTS *intHandler;
	VE_VMS_VIDEO *video;
	VE_VMS_AUDIO *audio;

    VMU(uint16_t *_frameBuffer);
    
    ~VMU();
    

    int loadBIOS(const char *filePath);

    void halt();

    void setDate();

    //Sets system variables in RAM
    void initBIOS();

    void startCPU();

    void initializeHLE();

    void runCycle();
    
    void reset();
    
private:
    int ccount;
    long cycle_count;
    long time_reg;
    long frame_skip;
    double CPS;
    byte prescaler;
    int pcount;
    int oldPRR;

    int OSC;
    int OCR_old;
    bool threadReady;
    bool inSleepState;
    bool BIOSExists;
    bool enableSound;
    bool useT1ELD;
    
    int cycles_left; //This counts how many cycles an instruction has, and gets decreased each cycle. Next instruction is processed when it gets 0.
    
    uint16_t *frameBuffer;
};

#endif // _VMU_H_
