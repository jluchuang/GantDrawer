#include "stdafx.h"

#include "RandGenerator.h"

#include <time.h>

int RandGenerator::generateRandNum(int beg,int en){
    int pos=0,dis=0;
    if (beg==en) {
        return beg;
    }
    if (beg>en){
        pos=en;
        dis=beg-en+1;
        return rand()%dis+pos;
    }
    else{
        pos=beg;
        dis=en-beg+1;
        return rand()%dis+pos;
    }
}
void  RandGenerator::generateRandNumPair(int beg,int en,int &first,int &second){
    //��ǰ����û�п������ɵ����������ͬһ������������
    first=generateRandNum(beg,en);
    second=generateRandNum(beg,en);
    /*while (first==second){
        second=generateRandNum(beg,en);
    }*/
}