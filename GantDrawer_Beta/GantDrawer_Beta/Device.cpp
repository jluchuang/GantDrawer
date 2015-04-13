#include "StdAfx.h"
#include "Device.h"
#include <limits.h>
//��ʼ��������ʱ��
const int Device::TotalTime =20000; 
//Byte�е�λ��
const int Device::ByteBits=CHAR_BIT;

Device::Device(void){

}

Device::Device (int p,int w){
    //��ʼ��ʱ����
    int arrayLen=TotalTime/(ByteBits)+1;
    this->timeline=new unsigned char[arrayLen];
    memset(timeline,0,arrayLen);
    //��ʼ���豸��ǰλ��
    pos=p;
    //��ʼ���豸��ǰ���ھ�����Ϣ
    wellNo=w;
}

Device::~Device(void)
{
    if (timeline!=NULL){
        delete timeline;
    }
}

//bool Device::updateTimeLine(int curTime,int operationTime){
//    //�����������ʱ�䣬����ʧ�ܷ���false
//    if (curTime+operationTime>TotalTime){
//        return false;
//    }
//    //����ʱ��С��0��ֱ�ӷ���
//    if(operationTime <= 0 ){
//        return true;
//    }
//    //��ȡ��ǰʱ�����ʱ���������е��±�λ��
//    int arrayPos=curTime/(ByteBits);
//    //��ȡ��ǰʱ�����ʱ���������е�bitλ��
//    int bitPos=curTime%(ByteBits);
//
//    //�ӵ�ǰʱ��㿪ʼ������1����
//    unsigned int mask = 1;//����
//    mask=mask<<bitPos;
//    while (operationTime>0){
//        timeline[arrayPos] |= mask;
//        bitPos++;
//        //��λ
//        if (bitPos==8){
//            mask=1;
//            bitPos=0;
//            arrayPos++;
//        }
//        operationTime--;
//    }
//}