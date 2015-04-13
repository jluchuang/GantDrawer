#include "stdafx.h"
#include "Elevator.h"

bool Elevator::isAvailable(int p,int curTime){
    if (this->pos!=pos){
        return false;
    }
    int arrayPos=curTime/ByteBits;
    int bitPos=curTime%ByteBits;
    unsigned int mask=1;
    mask=mask<<bitPos;
    if (mask&timeline[arrayPos]){
        return true;
    }
    else{
        return false;
    }
}