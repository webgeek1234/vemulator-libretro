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

#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include "common.h"

class VE_VMS_INTERRUPTS
{
	
public:
    VE_VMS_INTERRUPTS();
    ~VE_VMS_INTERRUPTS();

    //Setters
    void setReset();
    void clearReset();

    void setINT0();
    void clearINT0();

    void setINT1();
    void clearINT1();

    void setINT2();
    void clearINT2();

    void setINT3();
    void clearINT3();
    void setT0HOV();
    void clearT0HOV();

    void setT1HLOV();
    void clearT1HLOV();

    void setSIO0();
    void clearSIO0();

    void setSIO1();
    void clearSIO1();

    void setRFB();
    void clearRFB();

    void setP3();
    void clearP3();

    //Getters
    byte getReset();
    byte getINT0();
    byte getINT1();
    byte getINT2();
    byte getINT3();
    byte getT0HOV();
    byte getT1HLOV();
    byte getSIO0();
    byte getSIO1();
    byte getRFB();
    byte getP3();
    
    bool P3_Taken;
    
private:  
	//Interrupts
    byte Reset;
    byte INT0;
    byte INT1;
    byte INT2;
    byte INT3;
    byte T0HOV;
    byte T1HLOV;
    byte SIO0;
    byte SIO1;
    byte RFB;
    byte P3_data;
};

#endif // _INTERRUPTS_H_
