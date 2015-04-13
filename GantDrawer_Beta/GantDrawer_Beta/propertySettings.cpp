#include "stdafx.h"
#include "propertySettings.h"

/*****************************************************************
** added by @chuang	
** time @20140513
** ��̨�������������ݱ�������
*****************************************************************/

////����XML��Ҫ�õ��Ķ���
//MSXML2::IXMLDOMDocument2Ptr m_plDomDocumment;
//MSXML2::IXMLDOMElementPtr m_pDocRoot;

//ȫ�ֱ��������浱ǰ��ʾ�ĵ��Ƚ���漰�����豸��Ϣ
vector <CString> posVec;

//ȫ�ֱ��������涯����Ϣ���������ļ��ж���
vector <actionInfo> actionVec;

//ȫ�ֱ��������桰λ����Ϣ����ͼ���С������ߡ���λ�ö�Ӧ��ϵ
map <CString,double> posScreenYMap;

//��ǰ�����ţ���һ������ִ�к��Ӧ������X����λ��
map <int,CPoint> acLastScreenMap;

//WQ����
vector <CString> weaponType;

//WQ�����������ʾ����ɫ��Ӧ��ϵ
map <CString,COLORREF> weaponColorMap;

//������Ӧ����Ļ��������
vector <actionRect> acRecVec;

//��������λ��,������ʾ����
map <CString,int> ElevatorMap;

//��ǰ��ʾ������ڶ�Ӧ�ı��
int currentShowPos;

//��ǰ��ʾ���������ڶ�Ӧ��Ӧ���豸����
vector <DeviceInfo> AllDevices;

CString config_OperResultFile;//���Ƚ�������ļ���Ӧ·��
CString config_WQTypesFile;//�������������ļ���Ӧ·��
CString config_ConstructFile;//����ṹ�����ļ���Ӧ·��

int titalTime;//�ܵ���ʱ��


//����λ����Ϣ��Ӧ�Ļ�ͼλ����Ϣ
void setPosScreenYMap(CString pos,double screenY)
{
	typedef pair<CString,double> posScreenYpair;

	posScreenYpair tempPair=make_pair(pos,screenY);
	
	posScreenYMap.insert(tempPair);
}

//���ö������objNo��Ӧ�����¸�������Ӧ��X������Ϣ
void setAcLastScreenXMap(int objNo,CPoint lastPoint)
{
	typedef pair<int,CPoint> acLastScreenXpair;

	acLastScreenXpair tempPair=make_pair(objNo,lastPoint);

	map <int,CPoint> ::iterator iter=acLastScreenMap.find(objNo);
	if (iter==acLastScreenMap.end())
	{
		acLastScreenMap.insert(tempPair);
	}
	else
	{
		iter->second=lastPoint;
	}
}

//���ö�������
void setActions()
{
	actionInfo tempAc;
	tempAc.actionDes=_T("���Զ���1");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=45;
	tempAc.endTime=50;
	tempAc.pos=_T("Store8");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("���Զ���2");
	tempAc.actionObj=_T("WQAAB");
	tempAc.startTime=45;
	tempAc.endTime=80;
	tempAc.pos=_T("Store9");
	tempAc.objNo=2;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("���Զ���3");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=55;
	tempAc.endTime=70;
	tempAc.pos=_T("Elevator2");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("���Զ���4");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=70;
	tempAc.endTime=100;
	tempAc.pos=_T("Elevator1");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);
}

//�����������ͺ���ʾ��ɫ�Ķ�Ӧ��ϵ
void setWeaponTypeColorMap(CString wType, COLORREF colo)
{
	typedef pair <CString,COLORREF> weaponColorPair;
	weaponColorPair tempPair;
	tempPair=make_pair(wType,colo);
	weaponColorMap.insert(tempPair);
}

//����WQ����
void setWeaponType()
{
	weaponType.push_back(_T("WQAA"));
}

void initXMLParser()
{
	::CoInitialize(NULL);
	/*HRESULT hr=m_plDomDocumment.CoCreateInstance(_uuidof());*/
}


void WriteToXML()
{
	MSXML2::IXMLDOMDocument2Ptr pXMLDocument;

	pXMLDocument.CreateInstance(_uuidof(MSXML2::DOMDocument));

	MSXML2::IXMLDOMElementPtr pDevicesNode=pXMLDocument->createElement(_T("Devices"));

	pXMLDocument->appendChild(pDevicesNode);

	WriteXMLNode(pXMLDocument,pDevicesNode,_T("Elevator"),1);
	WriteXMLNode(pXMLDocument,pDevicesNode,_T("Store"),2);
	pXMLDocument->save(_T("Devices.xml"));
}

void WriteXMLNode(MSXML2::IXMLDOMDocument2Ptr pDocument,
	MSXML2::IXMLDOMNodePtr pParentNode,
	CString deviceName,
	long Type)
{
	//����һ��<Device>�ڵ�
	MSXML2::IXMLDOMElementPtr pDeviceNode=pDocument->createElement(_T("Device"));

	//�ڸ�����м���<Device>�ڵ�
	pParentNode->appendChild(pDeviceNode);
	//д���ֶ���
	MSXML2::IXMLDOMElementPtr pDeviceNameNode=pDocument->createElement(_T("Name"));
	pDeviceNameNode->text=_bstr_t(deviceName);

	//д��Type
	MSXML2::IXMLDOMElementPtr pTypeNode=pDocument->createElement(_T("Pos"));
	pTypeNode->text=_bstr_t(Type);

	pDeviceNode->appendChild(pDeviceNameNode);
	pDeviceNode->appendChild(pTypeNode);

}

//////////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��е�����λ����Ϣ���豸��Ϣ
//���ļ��еĶ�ȡ���ݰ�����
//1.����λ��(Device)��Ϣ:������Devs�У������е��øú���Ӧ��AllDevices
//       ��Ϊ�������ݸ�Devs
//2.��������Ϣ��������Devs�У������������ƺ����ŵĶ�Ӧ��ϵ����������Ҫ
//       ������������ֶ���ִ�д�������һ�������壬������øú���Ӧ��ȫ��
//       ����ElevatorMap���ݸ�posMap
void ReadDevices(CString xmlConfig,vector <DeviceInfo> &Devs,
	map <CString,int> &posMap)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//���������ĵ�
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//����������ʵ��
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//������ؽڵ�
	MSXML2::IXMLDOMNodeListPtr pNodes=pRootNode->selectNodes(_T("Device"));

	//��ȡ���е�Devs��Ϣ
	CString s;
	long size=pNodes->length;
	for (int i=0;i<size;i++)
	{
		MSXML2::IXMLDOMNodePtr pNode=pNodes->item[i];
		MSXML2::IXMLDOMNodePtr pNameNode=pNode->selectSingleNode(_T("Name"));
		MSXML2::IXMLDOMNodePtr pTypeNode=pNode->selectSingleNode(_T("Pos"));
		//s.Format(_T("%sname:%s,Type:%s\r\n"),s,(LPCTSTR)pNameNode->text,(LPCTSTR)pTypeNode->text);
		//AfxMessageBox(s);
		s.Format(_T("%s"),(LPCTSTR)pTypeNode->text);
		int pos=_ttoi(s);
		CString tempPos;
		tempPos.Format(_T("%s"),(LPCTSTR)pNameNode->text);

		DeviceInfo tempdev;
		tempdev.deviceName=tempPos;
		tempdev.devicePos=pos;
		Devs.push_back(tempdev);
	}

	//��ȡ���е�Elevator��Ϣ
	MSXML2::IXMLDOMNodeListPtr pPosNodes=pRootNode->selectNodes(_T("Position"));

	size=pPosNodes->length;
	for (int i=0;i<size;i++)
	{
		MSXML2::IXMLDOMNodePtr pNode=pPosNodes->item[i];
		MSXML2::IXMLDOMNodePtr pNameNode=pNode->selectSingleNode(_T("PosName"));
		MSXML2::IXMLDOMNodePtr pNoNode=pNode->selectSingleNode(_T("PosNo"));
	
		CString tempPos;
		tempPos.Format(_T("%s"),(LPCTSTR)pNameNode->text);
		CString tempNo;
		tempNo.Format(_T("%s"),(LPCTSTR)pNoNode->text);
		int posNo;
		posNo=_ttoi(tempNo);

		posMap.insert(make_pair(tempPos,posNo));
	}
}
/////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��е�WQ������Ϣ��������vector WQType��
//�ú�����ȡ���ݰ���:
//1.WQ����:�����ȷ���������Ƶ���WQ���ͣ�������WQs�У�
//         �����е���Ӧ��ȫ�ֱ���WQType���ݸ�WQs
void ReadWQTypes(CString xmlConfig,vector <CString> &WQs)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//���������ĵ�
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//����������ʵ��
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//������ؽڵ�
	MSXML2::IXMLDOMNodeListPtr pNodes=pRootNode->selectNodes(_T("WQType"));

	CString s;
	long size=pNodes->length;
	for (int i=0;i<size;i++)
	{
		MSXML2::IXMLDOMNodePtr pNode=pNodes->item[i];
		CString tempStr;
		tempStr.Format(_T("%s"),(LPCTSTR)pNode->text);
		WQs.push_back(tempStr);
	}
}

////////////////////////////////////////////////////////////////////////
//��ȡ�����ļ��еĵ��Ƚ����Ϣ��������vector acVec��
//�ú�����ȡ�����ļ��е����ݰ���:
//1.actions:�����Ƚ���е����е��Ȳ�������ȡ���������Acs�У�
//          ÿ��action�����������ݶξ���ͷ�ļ��������������
//          ����actionInfo�������е���Ӧ�ý�ȫ�ֱ���
//          actionVec��Ϊ�������ݸ�Acs
//2.totalTime:���ȷ������ȷ�������ִ��ʱ�䣬������ȫ�ֱ�����
void ReadActions(CString xmlConfig,vector <actionInfo> &Acs)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//���������ĵ�
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//����������ʵ��
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//������ؽڵ�
	MSXML2::IXMLDOMNodeListPtr pNodes=pRootNode->selectNodes(_T("Action"));

	//��ȡ����ִ�ж�����������Acs��
	CString s;
	long size=pNodes->length;
	for (int i=0;i<size;i++)
	{
		MSXML2::IXMLDOMNodePtr pNode=pNodes->item[i];
		actionInfo tempAc;
		CString tempStr;
		MSXML2::IXMLDOMNodePtr pName=pNode->selectSingleNode(_T("Pos"));
		tempAc.pos.Format(_T("%s"),(LPCTSTR)pName->text);

		MSXML2::IXMLDOMNodePtr pStTime=pNode->selectSingleNode(_T("StartTime"));
		tempStr.Format(_T("%s"),(LPCTSTR)pStTime->text);
		tempAc.startTime=_ttoi(tempStr);

		MSXML2::IXMLDOMNodePtr pEnTime=pNode->selectSingleNode(_T("EndTime"));
		tempStr.Format(_T("%s"),(LPCTSTR)pEnTime->text);
		tempAc.endTime=_ttoi(tempStr);

		MSXML2::IXMLDOMNodePtr pDes=pNode->selectSingleNode(_T("Description"));
		tempAc.actionDes.Format(_T("%s"),(LPCTSTR)pDes->text);

		MSXML2::IXMLDOMNodePtr pObj=pNode->selectSingleNode(_T("Object"));
		tempAc.actionObj.Format(_T("%s"),(LPCTSTR)pObj->text);

		MSXML2::IXMLDOMNodePtr pObjNO=pNode->selectSingleNode(_T("ObjectNo"));
		tempStr.Format(_T("%s"),(LPCTSTR)pObjNO->text);
		tempAc.objNo=_ttoi(tempStr);

		MSXML2::IXMLDOMNodePtr pObjsrc=pNode->selectSingleNode(_T("ObjSrc"));
		tempStr.Format(_T("%s"),(LPCTSTR)pObjsrc->text);
		tempAc.objSrc=_ttoi(tempStr);

		Acs.push_back(tempAc);
	}

	//��ȡ�����ܻ���ʱ��
	MSXML2::IXMLDOMNodePtr pTotalTimeNode=pRootNode->selectSingleNode(_T("TotalTime"));
	CString total;
	total.Format(_T("%s"),(LPCTSTR)pTotalTimeNode->text);
	titalTime=_ttoi(total);
}

void ReloadPropertiesFromXML()
{
	//���¶�ȡλ����Ϣ
	AllDevices.clear();
	ElevatorMap.clear();
	ReadDevices(config_ConstructFile,AllDevices,ElevatorMap);
	resetShowDevices(currentShowPos,posVec);

	/*AfxMessageBox(config_WQTypesFile);*/
	//���¶�ȡWQ������Ϣ
	weaponType.clear();
	ReadWQTypes(config_WQTypesFile,weaponType);

	//���¶�ȡ���Ƚ����Ϣ
	actionVec.clear();
	ReadActions(config_OperResultFile,actionVec);
}

//////////////////////////////////////////////////////////////////////////////////
//�������õ�ǰ��ʾ��������λ�ã�Position�����ȹ��������漰�����豸��Ϣ��Devices��
//������
//1.showPos��in������ǰ��ʾ��������λ�ñ��
//2.deviceShown��in,out������ǰ��ʾ�ĵ��Ƚ�����漰�����豸����
//      ���������Ӧ��posVec���ݸ�devicesShown
//����һ�����У������ļ��е�����λ����Ϣ���Ѿ������ڴ沢������AllDevices��
//ͨ����Ӧ�豸��λ�ñ�žͿ��Բ�ѯ����Ӧ�豸������һ��������
void resetShowDevices(const int showPos,vector <CString> &devicesShown)
{
	devicesShown.clear();

	//������ʾ�豸��Ϣ
	vector <DeviceInfo>::iterator iter;
	for (iter=AllDevices.begin();iter<AllDevices.end();iter++)
	{
		if (currentShowPos==0)
		{
			devicesShown.push_back(iter->deviceName);
			continue;
		}
		if (iter->devicePos==0)
		{
			devicesShown.push_back(iter->deviceName);
			continue;
		}
		if (currentShowPos==1||currentShowPos==2)
		{
			if (iter->devicePos==4||iter->devicePos==currentShowPos)
			{
				devicesShown.push_back(iter->deviceName);
				continue;
			}
		}
		if (currentShowPos==iter->devicePos)
		{
			devicesShown.push_back(iter->deviceName);
		}
	}
}