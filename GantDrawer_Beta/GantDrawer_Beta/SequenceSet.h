#include "stdafx.h"
#pragma once
#ifndef _SequenceSet_H_
#define _SequenceSet_H_

/***********************************************************
** added by @chuang
** time @20140619
** SequenceSet�࣬���Ż��㷨�еĽ�ռ�ѡȡ����S
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
	** �����������ɽ�ռ��е�������м���
    ********************************************************/
    bool GenerateSeqSet(const vector <int> &seed);

    /********************************************************
	** �����������ɽ�ռ��е�һ���������
    ********************************************************/
    vector <int> GenerateOneSeq(const vector <int> &seed);

    /********************************************************
	** �жϵ�ǰ�������Ƿ��ظ�ѡ��
    ********************************************************/
    bool alreadyPicked(const vector <int> &curSeq);
public:
	//SequenceSet(void);
    //�������캯��
    SequenceSet(const SequenceSet &sSet);
    //�������ӳ�ʼ�����캯��
	SequenceSet(const vector <int> &seed,int sSize,int interTime);
    //���ظ�ֵ�����
    SequenceSet &operator=(const SequenceSet &sSet);

	~SequenceSet(void);
    ////////////////////////////////////////////////////////////////////////
    //����������������е��������
	vector <vector <int>> GetSeqSet() const {return this->seqSet;};
    int getSetSize() const{return this->setSize;};
    int getInterruptTime() const {return this->interruptTime;}
};

ostream &operator<< (ostream &os,const SequenceSet &s);

#endif