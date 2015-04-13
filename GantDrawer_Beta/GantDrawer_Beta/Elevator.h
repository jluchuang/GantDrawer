#include "stdafx.h"

#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "Device.h"

class Elevator:public Device{
public:
    bool isAvailable(int pos,int curTime);
private:
};

#endif