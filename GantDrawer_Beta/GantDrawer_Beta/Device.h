#pragma once
#include "stdafx.h"

#ifndef _DEVICE_H_
#define _DEVICE_H_

/*****************************************************************
** added by @chuang	
** time @20140619
** 所有可移动设备类型基类定义包括升降机和Car
*****************************************************************/

class Device
{
protected:
    //每个字节所包含的位数
    static const int ByteBits;
    //调度的时间上界
    static const int TotalTime;
    //时间线,每个需要使用的设备都有自己的时间线表明在特定时间点设备是否可用
    //这里用char型数组表示时间线，
    //数组中的每一“位”为0表明当前设备可用，为1表明当前设备被占用
    unsigned char *timeline;

    //每个设备都有当前所在的位置信息，位置信息表明当前设备在哪个舱室或者挂载点
    int pos;

    //井道信息，设备可能在不同的井道中
    int wellNo;
public:
    Device(void);
    virtual ~Device(void);

    Device (int p,int w);

    //获得设备从初始位置到目标位置操作所需时间
    virtual int getOpeartionTime(int src,int tar)=0;
    
    //基本操作函数
    int getPos(){return pos;};
    int getWellNo(){return wellNo;};
    void setPos(int p){pos=p;};
    void setWellNo(int w){wellNo=w;};
    
    /*****************************************************************
    ** 更新当前设备的时间线
    ******************************************************************/
    bool updateTimeLine(int curTime,int operationTime);

    /******************************************************************
    ** 根据给定的时间和设备的位置信息判断
    ** 当前设备是否可用
    ** 纯虚函数，因为针对不同的设备器判断方法可能不同
    ******************************************************************/
    virtual bool isAvailable(int pos,int curTime)=0;
};

#endif
