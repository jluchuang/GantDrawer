#include "stdafx.h"

#ifndef _RANDGENERATOR_H_ 
#define _RANDGENERATOR_H_

//#include <math.h>

class RandGenerator{
public:
    /*********************************************************
    ** ����[beg,en]��[en,beg]�ϵ������
    ** �������ܻ���ϸ��ָ��ʷֲ�����µ����������
    *********************************************************/
    static int generateRandNum(int beg,int en);

    /*********************************************************
    ** ����[beg,en]��[en,beg]�ϵ�һ�������
    *********************************************************/
    static void generateRandNumPair(int beg,int en,int &first,int &second);
};

#endif