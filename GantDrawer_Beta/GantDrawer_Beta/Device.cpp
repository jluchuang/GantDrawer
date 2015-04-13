#include "StdAfx.h"
#include "Device.h"
#include <limits.h>
//初始化调度总时间
const int Device::TotalTime =20000; 
//Byte中的位数
const int Device::ByteBits=CHAR_BIT;

Device::Device(void){

}

Device::Device (int p,int w){
    //初始化时间线
    int arrayLen=TotalTime/(ByteBits)+1;
    this->timeline=new unsigned char[arrayLen];
    memset(timeline,0,arrayLen);
    //初始化设备当前位置
    pos=p;
    //初始化设备当前所在井道信息
    wellNo=w;
}

Device::~Device(void)
{
    if (timeline!=NULL){
        delete timeline;
    }
}

//bool Device::updateTimeLine(int curTime,int operationTime){
//    //超出总体调度时间，调度失败返回false
//    if (curTime+operationTime>TotalTime){
//        return false;
//    }
//    //操作时间小于0，直接返回
//    if(operationTime <= 0 ){
//        return true;
//    }
//    //获取当前时间点在时间线数组中的下标位置
//    int arrayPos=curTime/(ByteBits);
//    //获取当前时间点在时间线数组中的bit位置
//    int bitPos=curTime%(ByteBits);
//
//    //从当前时间点开始进行置1操作
//    unsigned int mask = 1;//掩码
//    mask=mask<<bitPos;
//    while (operationTime>0){
//        timeline[arrayPos] |= mask;
//        bitPos++;
//        //进位
//        if (bitPos==8){
//            mask=1;
//            bitPos=0;
//            arrayPos++;
//        }
//        operationTime--;
//    }
//}