#include "stdafx.h"

#ifndef PROPERTY_SET_H
#define PROPERTY_SET_H

/*****************************************************************
** added by @chuang	
** time @20140513
** ��̨�������������ݽṹ����
*****************************************************************/

#include <set>
#include <vector>
#include <map>

using namespace std;

//����
struct actionInfo 
{
	CString pos;//��������λ��
	int startTime;//����������ʼʱ��
	int endTime;//��������ʱ��
	CString actionDes;//��������
	CString actionObj;//ִ�ж����Ķ���
	int objNo;//�����ţ����Ƽ�ͷ��ʱ��ʹ�ã�
	int objSrc;//�������ʼ�㣨����������ںţ������ڹ�����ʾ
};

//�����ڻ�ͼ����Ӧ��λ��
struct actionRect
{
	CRect acRect;//��������Ļ�϶�Ӧ�ľ�����
	int acNo;//������actionVec�еı��
};

struct DeviceInfo 
{
	CString deviceName;
	int devicePos;

	DeviceInfo ()
	{
	}

	DeviceInfo (CString deName,int dePos)
	{
		deviceName=deName;
		devicePos=dePos;
	}

	DeviceInfo (const DeviceInfo &Dev)
	{
		deviceName=Dev.deviceName;
		devicePos=Dev.devicePos;
	}
};

typedef DeviceInfo * pDevice;
typedef actionInfo * pAction;

/////////////////////////////////////////////////////////////////////////
//ȫ�ֱ�����������

//ȫ�ֱ��������������ļ��е�pos��Ϣ
extern vector <CString> posVec;

//ȫ�ֱ��������涯����Ϣ���������ļ��ж���
extern vector <actionInfo> actionVec;

//ȫ�ֱ��������桰λ����Ϣ����ͼ���С������ߡ���λ�ö�Ӧ��ϵ
extern map <CString,double> posScreenYMap;

//��ǰ�����ţ���һ������ִ�к��Ӧ������X����λ��
extern map <int,CPoint> acLastScreenMap;

//WQ����
extern vector <CString> weaponType;

//WQ�����������ʾ����ɫ��Ӧ��ϵ
extern map <CString,COLORREF> weaponColorMap;

//������Ӧ����Ļ��������
extern vector <actionRect> acRecVec;

//��������λ��,������ʾ����
extern map <CString,int> ElevatorMap;

//��ǰ��ʾ������ڶ�Ӧ�ı��
extern int currentShowPos;

//��ǰ��ʾ���������ڶ�Ӧ��Ӧ���豸����
extern vector <DeviceInfo> AllDevices;

extern CString config_OperResultFile;//���Ƚ�������ļ���Ӧ·��
extern CString config_WQTypesFile;//�������������ļ���Ӧ·��
extern CString config_ConstructFile;//����ṹ�����ļ���Ӧ·��

extern int titalTime;//�ܵ���ʱ��

//////////////////////////////////////////////////////////////////////////
//ȫ�ֻ�����������

//����λ����Ϣ��Ӧ�Ļ�ͼλ����Ϣ
extern void setPosScreenYMap(CString pos,double screenY);

//���ö�������
extern void setActions();

//����WQ����
extern void setWeaponType();

//�����������ͺ���ʾ��ɫ�Ķ�Ӧ��ϵ
extern void setWeaponTypeColorMap(CString wType, COLORREF colo);

//���ö������objNo��Ӧ�����¸�������Ӧ��X������Ϣ
extern void setAcLastScreenXMap(int objNo,CPoint lastPoint);

extern void initXMLParser();
extern void WriteToXML();

//////////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��е�����λ����Ϣ���豸��Ϣ
//���ļ��еĶ�ȡ���ݰ�����
//1.����λ��(Device)��Ϣ:������Devs�У������е��øú���Ӧ��AllDevices
//       ��Ϊ�������ݸ�Devs
//2.��������Ϣ��������Devs�У������������ƺ����ŵĶ�Ӧ��ϵ����������Ҫ
//       ������������ֶ���ִ�д�������һ�������壬������øú���Ӧ��ȫ��
//       ����ElevatorMap���ݸ�posMap
extern void ReadDevices(CString xmlConfig,vector <DeviceInfo> &Devs,map <CString,int> &posMap);

//////////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��е�WQ������Ϣ��������vector WQType��
//�ú�����ȡ���ݰ���:
//1.WQ����:�����ȷ���������Ƶ���WQ���ͣ�������WQs�У�
//         �����е���Ӧ��ȫ�ֱ���WQType���ݸ�WQs
extern void ReadWQTypes(CString xmlConfig,vector <CString> &WQs);

//////////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��еĵ��Ƚ����Ϣ��������vector acVec��
//�ú�����ȡ�����ļ��е����ݰ���:
//1.actions:�����Ƚ���е����е��Ȳ�������ȡ���������Acs�У�
//          ÿ��action�����������ݶξ���ͷ�ļ��������������
//          ����actionInfo�������е���Ӧ�ý�actionVec��Ϊ��
//          �����ݸ�Acs
//2.totalTime:���ȷ������ȷ�������ִ��ʱ�䣬������ȫ�ֱ�����
extern void ReadActions(CString xmlConfig,vector <CString> &Acs);

extern void WriteXMLNode(MSXML2::IXMLDOMDocument2Ptr pDocument,
	MSXML2::IXMLDOMNodePtr pParentNode,
	CString deviceName,
	long Type);

//��xml�ļ��ж�ȡ������Ϣ
extern void ReloadPropertiesFromXML();

//////////////////////////////////////////////////////////////////////////////////
//�������õ�ǰ��ʾ��������λ�ã�Position�����ȹ��������漰�����豸��Ϣ��Devices��
//������
//1.showPos��in������ǰ��ʾ��������λ�ñ��
//2.deviceShown��in,out������ǰ��ʾ�ĵ��Ƚ�����漰�����豸����
//      ���������Ӧ��posVec���ݸ�devicesShown
//����һ�����У������ļ��е�����λ����Ϣ���Ѿ������ڴ沢������AllDevices��
//ͨ����Ӧ�豸��λ�ñ�žͿ��Բ�ѯ����Ӧ�豸������һ��������
extern void resetShowDevices(const int showPos,vector <CString> &devicesShown);


#endif