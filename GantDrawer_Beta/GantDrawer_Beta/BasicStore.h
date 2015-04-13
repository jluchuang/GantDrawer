#pragma once
#include "stdafx.h"

#ifndef _BASICSTORE_H_
#define _BASICSTORE_H_

/*****************************************************************
** added by @chuang	
** time @20140619
** ���л�����ʩ�Ļ��࣬�����ײ�������ҡ�װ����ҡ���������ת���ҵ�
*****************************************************************/
#include "Device.h"
#include <vector>

/*****************************************************************
** ������Ϣ����
*****************************************************************/
struct request{
    int target;//������ֹ�ĵص�
    int begTime;//���������ʱ��
    int operTime;//����ִ�к�ʱ
    Device *pDev;//����������豸����ָ��

    //���ι��캯��
    request(int t,int beg,int operT,Device *p):target(t),begTime(beg),operTime(operT),pDev(p){};
    //�������캯��
    request(const request &req):target(req.target),begTime(req.begTime),operTime(req.operTime),pDev(req.pDev){};
    request &operator=(const request &req){
        if (this==&req){ 
            return *this;
        }
        target=req.target;
        begTime=req.begTime;
        operTime=req.operTime;
        pDev=req.pDev;
        return (*this);
    };
};

class BasicStore{
protected:
    //vector <request> UpRequestQueue;//���������������
    //vector <request> DownRequestQueue;//�½������������
public:
    BasicStore(void);
    virtual ~BasicStore(void);

    //��ȡ���ȼ���ߵĶ�������
    virtual const request getFirstRequest(const vector <request> &) const=0;
    //�������Ķ�������
    virtual bool dealActionRequest(const request &)=0;
    //������������е�����
    virtual void popActionRequest(vector <request> &)=0;
    //����������в���һ���µĶ�������
    virtual void pushActionRequest(const request ,vector <request> &)=0;

};

#endif