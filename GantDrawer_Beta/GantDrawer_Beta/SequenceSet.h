#include "stdafx.h"
#pragma once
#ifndef _SequenceSet_H_
#define _SequenceSet_H_

/***********************************************************
** added by @chuang
** time @20140619
** SequenceSet类，序优化算法中的解空间选取集合S
***********************************************************/
#include <vector>
using namespace std;

class SequenceSet
{
private:
	vector <vector<int>> seqSet;
    bool isGenerated;
    int setSize;
    int interruptTime;

	/********************************************************
	** 根据种子生成解空间中的随机序列集合
    ********************************************************/
    bool GenerateSeqSet(const vector <int> &seed);

    /********************************************************
	** 根据种子生成解空间中的一条随机序列
    ********************************************************/
    vector <int> GenerateOneSeq(const vector <int> &seed);

    /********************************************************
	** 判断当前的序列是否被重复选择
    ********************************************************/
    bool alreadyPicked(const vector <int> &curSeq);
public:
	//SequenceSet(void);
    //拷贝构造函数
    SequenceSet(const SequenceSet &sSet);
    //根据种子初始化构造函数
	SequenceSet(const vector <int> &seed,int sSize,int interTime);
    //重载赋值运算符
    SequenceSet &operator=(const SequenceSet &sSet);

	~SequenceSet(void);
    ////////////////////////////////////////////////////////////////////////
    //基本操作，获得类中的相关属性
	vector <vector <int>> GetSeqSet() const {return this->seqSet;};
    int getSetSize() const{return this->setSize;};
    int getInterruptTime() const {return this->interruptTime;}
};

ostream &operator<< (ostream &os,const SequenceSet &s);

#endif