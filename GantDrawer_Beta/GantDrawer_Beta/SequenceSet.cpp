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
    //�������ֵ�����븳ֵ������ͬ�������и�ֵ����
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
    os<<"���ϴ�С��"<<s.getSetSize()<<endl;
	os<<"�Ŷ�������"<<s.getInterruptTime()<<endl;
	
	vector <vector <int>> seqSet=s.GetSeqSet();

	for(int i=0;i<seqSet.size();i++){
        os<<"���� "<<i<<":";
		for(int j=0;j<seqSet[i].size();j++){
			os<<seqSet[i][j]<<"  ";
		}
        os<<endl;
	}

	return os;
}

bool SequenceSet::GenerateSeqSet(const vector<int> &seed){
    //�������޷����ɼ���
    if (seed.size()==0){
        return false;
    }
    //���ѡ����������
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
    //�Ŷ��������������������
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
    //ѡȡ�����е�һ������ʱ�������ز���
    if (seqSet.size()==0)
    {
        return false;
    }
    //��ʼ���������ɵ������Ѿ���ѡ�뼯��
    bool flag=true;
    //�жϵ�ǰ�����Ƿ��Ѿ���ѡȡ
    for (int i=0;i<seqSet.size();i++) {
        //�ж��Ѿ�ѡ��ĵ�i�������Ƿ����������ɵ�������ͬ
        for(int j=0;j<curSeq.size();j++){
            if (curSeq[j]!=seqSet[i][j]){
                //�����ɵ��������i�����в�ͬ����flagΪfalse
                flag=false;
                break;
            }
        }
        //��������ɵ��������i��������ͬ�������Ѿ�ѡ���������true
        if (flag) {
            return flag;
        }
        //�������������i�����в�ͬ��Ϊ�˼���������һ���жϣ���flag���û�true
        else{
            flag=true;
        }
    }
    //�����е�ǰԪ�ض��Ѿ��ж���ϣ��������������п��Ա����뼯��
    return false;
}