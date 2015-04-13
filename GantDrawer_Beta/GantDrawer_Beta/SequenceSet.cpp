#include "StdAfx.h"
#include "SequenceSet.h"
#include "RandGenerator.h"

//SequenceSet::SequenceSet(void)
//{
//}

SequenceSet::SequenceSet(const vector <int> &seed,int sSize,int interTime){
    this->interruptTime=interTime;
    this->isGenerated=false;
    this->setSize=sSize;
    GenerateSeqSet(seed);
    this->isGenerated=true;
}

SequenceSet::SequenceSet(const SequenceSet &sSet){
    this->interruptTime=sSet.interruptTime;
    this->isGenerated=sSet.isGenerated;
    this->seqSet=sSet.seqSet;
    this->setSize=sSet.setSize;
}

SequenceSet::~SequenceSet(void)
{
}

SequenceSet &SequenceSet::operator=(const SequenceSet &sSet)
{
    //如果被赋值对象与赋值对象相同，不进行赋值操作
    if (this==&sSet){
        return *this;
    }
    else{
        this->interruptTime=sSet.interruptTime;
        this->isGenerated=sSet.isGenerated;
        this->seqSet=sSet.seqSet;
        this->setSize=sSet.setSize;
        return *this;
    }
}

ostream &operator<< (ostream &os,const SequenceSet &s){
    os<<"集合大小："<<s.getSetSize()<<endl;
	os<<"扰动次数："<<s.getInterruptTime()<<endl;
	
	vector <vector <int>> seqSet=s.GetSeqSet();

	for(int i=0;i<seqSet.size();i++){
        os<<"序列 "<<i<<":";
		for(int j=0;j<seqSet[i].size();j++){
			os<<seqSet[i][j]<<"  ";
		}
        os<<endl;
	}

	return os;
}

bool SequenceSet::GenerateSeqSet(const vector<int> &seed){
    //空种子无法生成集合
    if (seed.size()==0){
        return false;
    }
    //随机选择生成序列
    for (int i=0;i<this->setSize;i++){
       vector <int>curSeq = GenerateOneSeq(seed);
       if (alreadyPicked(curSeq)){
           i--;
       }
       else{
           this->seqSet.push_back(curSeq);
       }
    }
}

vector <int> SequenceSet::GenerateOneSeq(const vector <int> &seed){
    vector <int> result(seed);
    //扰动交换操作生成随机序列
    for (int i=0;i<this->interruptTime;i++){
        //generate swap pair
        int first=0;
        int second=0;
        RandGenerator::generateRandNumPair(0,seed.size()-1,first,second);

        //swap
        int temp=result[first];
        result[first]=result[second];
        result[second]=temp;
    }
    return result;
}

bool SequenceSet::alreadyPicked(const vector<int> &curSeq){
    //选取集合中第一条序列时不用判重操作
    if (seqSet.size()==0)
    {
        return false;
    }
    //初始假设新生成的序列已经被选入集合
    bool flag=true;
    //判断当前序列是否已经被选取
    for (int i=0;i<seqSet.size();i++) {
        //判断已经选择的第i条序列是否与最新生成的序列相同
        for(int j=0;j<curSeq.size();j++){
            if (curSeq[j]!=seqSet[i][j]){
                //新生成的序列与第i条序列不同，置flag为false
                flag=false;
                break;
            }
        }
        //如果新生成的序列与第i条序列相同，表明已经选择过，返回true
        if (flag) {
            return flag;
        }
        //新生成序列与第i条序列不同，为了继续进行下一次判断，将flag重置回true
        else{
            flag=true;
        }
    }
    //集合中当前元素都已经判断完毕，表明新生成序列可以被加入集合
    return false;
}