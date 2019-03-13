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

#include "basetimer.h"

VE_VMS_BASETIMER::VE_VMS_BASETIMER(VE_VMS_RAM *_ram, VE_VMS_INTERRUPTS *_intHandler, VE_VMS_CPU *_cpu)
{
	ram = _ram;
	intHandler = _intHandler;
	cpu = _cpu;
	BTR = 0;
}

VE_VMS_BASETIMER::~VE_VMS_BASETIMER()
{
}

void VE_VMS_BASETIMER::runTimer() 
{
	int BTCR_data = ram->readByte_RAW(BTCR);

	bool BTStarted = (BTCR_data & 64) != 0;
	bool Int0Enabled = (BTCR_data & 1) != 0;
	bool Int1Enabled = (BTCR_data & 4) != 0;
	int int1cycle;

	int cycleControl = ((BTCR_data & 16) >> 4) | ((BTCR_data & 32) >> 4);

	switch (cycleControl)
	{
		case 0:
			int1cycle = 32;
			break;
		case 1:
			int1cycle = 128;
			break;
		case 2:
			int1cycle = 512;
			break;
		case 3:
			int1cycle = 2048;
			break;
		default:
			int1cycle = 2048;
	}

	if(BTStarted)
	{
		BTR += 32786.0 / cpu->getCurrentFrequency();

		//Throw interrupt 1 source when cycle chosen is reached
		if(BTR >= int1cycle) 
		{
			BTCR_data |= 8;
			ram->writeByte_RAW(BTCR, BTCR_data);

			if (Int1Enabled) 
				intHandler->setINT3();

		}


		if((BTR > 16383) || (BTR > 63 && ((BTCR_data & 128) != 0)))
		{
			//Throw full (14-bit) overflow interrupt (Interrupt 0 source)
			BTCR_data |= 2;
			ram->writeByte_RAW(BTCR, BTCR_data);

			if(Int0Enabled)
				intHandler->setINT3();

			if(BTR > 16383) BTR = 0;
		}
	}
}
