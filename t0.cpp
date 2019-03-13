/*
Copyright (c) 2019, Mahmoud Jaoune
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

#include "t0.h"

VE_VMS_TIMER0::VE_VMS_TIMER0(VE_VMS_RAM *_ram, VE_VMS_INTERRUPTS *_intHandler, VE_VMS_CPU *_cpu, byte *_prescaler)
{
	ram = _ram;
	intHandler = _intHandler;
	cpu = _cpu;
	prescaler = _prescaler;
	
	TRLStarted = 0;
    TRHStarted = 0;
    
    TRL_data = 0;
    TRH_data = 0;
}

VE_VMS_TIMER0::~VE_VMS_TIMER0()
{
	
}

void VE_VMS_TIMER0::runTimer() 
{
	int TCNT_data = ram->readByte_RAW(T0CNT); //Timer control register

	bool TRLEnabled;
	bool TRHEnabled;
	bool TRLONGEnabled;

	TRLEnabled = (TCNT_data & 64) != 0;
	TRHEnabled = (TCNT_data & 128) != 0;
	TRLONGEnabled = (TCNT_data & 32) != 0;
	
	//int clockSource = ((TCNT_data & 16) >> 4) & 0xFF;

	//if(clockSource == 1) return;    //External pin, not supported

	//Increase timers
	if(TRLEnabled) 
	{
		if(TRLStarted++ == 0) 
		{
			TRL_data = ram->readByte_RAW(T0LR);
			//printf("Started T0RL\n");
		}
		else if(*prescaler == 1) TRL_data++;
	} 
	else 
	{
		TRL_data = ram->readByte_RAW(T0LR);
		TRLStarted = 0;
	}

	if(TRHEnabled) 
	{
		if(TRHStarted++ == 0) 
		{
			TRH_data = ram->readByte_RAW(T0HR);
			//printf("Started T0RH\n");
		}
		else if(!TRLONGEnabled)
		{
			if(*prescaler == 1)
				TRH_data++;
		}
		
	} 
	else 
	{
		TRH_data = ram->readByte_RAW(T0HR);
		TRHStarted = 0;
	}
	
	//if(TRLONGEnabled) printf("Long mode.\n");

	//Overflow in TRL_data, 8-bit mode
	if(TRL_data > 255 && !TRLONGEnabled)
	{
		TCNT_data |= 2;

		if (TCNT_data & 1) intHandler->setINT2();

		//Stop timer
		//TCNT_data &= 0xBF;

		//Reload contents
		TRL_data = ram->readByte_RAW(T0LR);
	}
	//Overflow in TRL_data, 16-bit mode
	else if(TRL_data > 255 && TRLONGEnabled)
	{
		TRH_data++;


		if (TCNT_data & 1) intHandler->setINT2();
		//Reload contents
		TRL_data = ram->readByte_RAW(T0LR);
		//TRL_data = 0;
	}

	//Overflow in TRH_data, 8-bit mode
	if(TRH_data > 255 && !TRLONGEnabled)
	{
		//printf("T0RH overflow 8-bit\n");
		TCNT_data |= 8;

		if (TCNT_data & 4) intHandler->setT0HOV();

		//Stop timer
		TCNT_data &= 0x7F;	//Not forcefully stopping it causes a hang in Chao Adventure 1 when navigating through the menu

		//Reload contents
		TRH_data = ram->readByte_RAW(T0HR);
	}
	//Overflow in 16-bit mode
	else if(TRH_data > 255 && TRLONGEnabled)
	{
		//printf("T0 LONG overflow 16-bit\n");
		TCNT_data |= 2;
		TCNT_data |= 8;

		if (TCNT_data & 4) intHandler->setT0HOV();

		//Stop both timers
		//TCNT_data &= 0x3F;

		//Reload contents
		TRL_data = ram->readByte_RAW(T0LR);
		TRH_data = ram->readByte_RAW(T0HR);
	}
	
	ram->writeByte_RAW(T0L, TRL_data);
	ram->writeByte_RAW(T0H, TRH_data);

	
	ram->writeByte_RAW(T0CNT, TCNT_data);
}
    
