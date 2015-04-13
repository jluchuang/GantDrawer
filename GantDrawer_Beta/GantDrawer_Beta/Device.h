#pragma once
#include "stdafx.h"

#ifndef _DEVICE_H_
#define _DEVICE_H_

/*****************************************************************
** added by @chuang	
** time @20140619
** ���п��ƶ��豸���ͻ��ඨ�������������Car
*****************************************************************/

class Device
{
protected:
    //ÿ���ֽ���������λ��
    static const int ByteBits;
    //���ȵ�ʱ���Ͻ�
    static const int TotalTime;
    //ʱ����,ÿ����Ҫʹ�õ��豸�����Լ���ʱ���߱������ض�ʱ����豸�Ƿ����
    //������char�������ʾʱ���ߣ�
    //�����е�ÿһ��λ��Ϊ0������ǰ�豸���ã�Ϊ1������ǰ�豸��ռ��
    unsigned char *timeline;

    //ÿ���豸���е�ǰ���ڵ�λ����Ϣ��λ����Ϣ������ǰ�豸���ĸ����һ��߹��ص�
    int pos;

    //������Ϣ���豸�����ڲ�ͬ�ľ�����
    int wellNo;
public:
    Device(void);
    virtual ~Device(void);

    Device (int p,int w);

    //����豸�ӳ�ʼλ�õ�Ŀ��λ�ò�������ʱ��
    virtual int getOpeartionTime(int src,int tar)=0;
    
    //������������
    int getPos(){return pos;};
    int getWellNo(){return wellNo;};
    void setPos(int p){pos=p;};
    void setWellNo(int w){wellNo=w;};
    
    /*****************************************************************
    ** ���µ�ǰ�豸��ʱ����
    ******************************************************************/
    bool updateTimeLine(int curTime,int operationTime);

    /******************************************************************
    ** ���ݸ�����ʱ����豸��λ����Ϣ�ж�
    ** ��ǰ�豸�Ƿ����
    ** ���麯������Ϊ��Բ�ͬ���豸���жϷ������ܲ�ͬ
    ******************************************************************/
    virtual bool isAvailable(int pos,int curTime)=0;
};

#endif
