#pragma once
#include "stdafx.h"

#ifndef _BASICSTORE_H_
#define _BASICSTORE_H_

/*****************************************************************
** added by @chuang	
** time @20140619
** 所有缓存设施的基类，包括底层贮存舱室、装配舱室、缓存区、转运室等
*****************************************************************/
#include "Device.h"
#include <vector>

/*****************************************************************
** 请求消息定义
*****************************************************************/
struct request{
    int target;//动作终止的地点
    int begTime;//发出申请的时间
    int operTime;//动作执行耗时
    Device *pDev;//发出申请的设备对象指针

    //传参构造函数
    request(int t,int beg,int operT,Device *p):target(t),begTime(beg),operTime(operT),pDev(p){};
    //拷贝构造函数
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
    //vector <request> UpRequestQueue;//上升操作请求队列
    //vector <request> DownRequestQueue;//下降操作请求队列
public:
    BasicStore(void);
    virtual ~BasicStore(void);

    //获取优先级最高的动作请求
    virtual const request getFirstRequest(const vector <request> &) const=0;
    //处理具体的动作请求
    virtual bool dealActionRequest(const request &)=0;
    //弹出请求队列中的请求
    virtual void popActionRequest(vector <request> &)=0;
    //向请求队列中插入一个新的动作请求
    virtual void pushActionRequest(const request ,vector <request> &)=0;

};

#endif