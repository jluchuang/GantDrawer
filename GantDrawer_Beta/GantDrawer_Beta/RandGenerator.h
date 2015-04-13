#include "stdafx.h"

#ifndef _RANDGENERATOR_H_ 
#define _RANDGENERATOR_H_

//#include <math.h>

class RandGenerator{
public:
    /*********************************************************
    ** 生成[beg,en]或[en,beg]上的随机数
    ** 后续可能会加上各种概率分布情况下的随机数生成
    *********************************************************/
    static int generateRandNum(int beg,int en);

    /*********************************************************
    ** 生成[beg,en]或[en,beg]上的一对随机数
    *********************************************************/
    static void generateRandNumPair(int beg,int en,int &first,int &second);
};

#endif