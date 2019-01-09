/*
	VeMUlator project (Originally developed by MJaoune <mjaoune55@gmail.com>) and any files affiliated with it come with ABSOLUTELY NO WARRANTY under any circumstances; use at your own risk.
	Though it would be really appreciated if my name gets credited as "original developer" in case of redistribution.
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
