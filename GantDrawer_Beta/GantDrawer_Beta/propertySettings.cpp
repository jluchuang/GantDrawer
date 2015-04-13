#include "stdafx.h"
#include "propertySettings.h"

/*****************************************************************
** added by @chuang	
** time @20140513
** 后台数据驱动，数据变量声明
*****************************************************************/

////解析XML需要用到的对象
//MSXML2::IXMLDOMDocument2Ptr m_plDomDocumment;
//MSXML2::IXMLDOMElementPtr m_pDocRoot;

//全局变量，保存当前显示的调度结果涉及到的设备信息
vector <CString> posVec;

//全局变量，储存动作信息，从输入文件中读入
vector <actionInfo> actionVec;

//全局变量，储存“位置信息”与图形中“横轴线”的位置对应关系
map <CString,double> posScreenYMap;

//当前对象编号，上一个动作执行后对应的最右X坐标位置
map <int,CPoint> acLastScreenMap;

//WQ类型
vector <CString> weaponType;

//WQ类型与界面显示的颜色对应关系
map <CString,COLORREF> weaponColorMap;

//动作对应的屏幕矩形区域
vector <actionRect> acRecVec;

//升降井口位置,用于显示过滤
map <CString,int> ElevatorMap;

//当前显示升降阱口对应的编号
int currentShowPos;

//当前显示的升降井口对应对应的设备集合
vector <DeviceInfo> AllDevices;

CString config_OperResultFile;//调度结果配置文件对应路径
CString config_WQTypesFile;//武器类型配置文件对应路径
CString config_ConstructFile;//船体结构配置文件对应路径

int titalTime;//总调度时间


//设置位置信息对应的绘图位置信息
void setPosScreenYMap(CString pos,double screenY)
{
	typedef pair<CString,double> posScreenYpair;

	posScreenYpair tempPair=make_pair(pos,screenY);
	
	posScreenYMap.insert(tempPair);
}

//设置动作编号objNo对应的上衣个动作对应的X坐标信息
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

//设置动作队列
void setActions()
{
	actionInfo tempAc;
	tempAc.actionDes=_T("测试动作1");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=45;
	tempAc.endTime=50;
	tempAc.pos=_T("Store8");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("测试动作2");
	tempAc.actionObj=_T("WQAAB");
	tempAc.startTime=45;
	tempAc.endTime=80;
	tempAc.pos=_T("Store9");
	tempAc.objNo=2;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("测试动作3");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=55;
	tempAc.endTime=70;
	tempAc.pos=_T("Elevator2");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);

	tempAc.actionDes=_T("测试动作4");
	tempAc.actionObj=_T("WQAA");
	tempAc.startTime=70;
	tempAc.endTime=100;
	tempAc.pos=_T("Elevator1");
	tempAc.objNo=1;
	actionVec.push_back(tempAc);
}

//设置武器类型和显示颜色的对应关系
void setWeaponTypeColorMap(CString wType, COLORREF colo)
{
	typedef pair <CString,COLORREF> weaponColorPair;
	weaponColorPair tempPair;
	tempPair=make_pair(wType,colo);
	weaponColorMap.insert(tempPair);
}

//设置WQ类型
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
	//创建一个<Device>节点
	MSXML2::IXMLDOMElementPtr pDeviceNode=pDocument->createElement(_T("Device"));

	//在父结点中加入<Device>节点
	pParentNode->appendChild(pDeviceNode);
	//写入字段名
	MSXML2::IXMLDOMElementPtr pDeviceNameNode=pDocument->createElement(_T("Name"));
	pDeviceNameNode->text=_bstr_t(deviceName);

	//写入Type
	MSXML2::IXMLDOMElementPtr pTypeNode=pDocument->createElement(_T("Pos"));
	pTypeNode->text=_bstr_t(Type);

	pDeviceNode->appendChild(pDeviceNameNode);
	pDeviceNode->appendChild(pTypeNode);

}

//////////////////////////////////////////////////////////////////////////
//读取配置文件中的所有位置信息和设备信息
//该文件中的读取内容包括：
//1.所有位置(Device)信息:保存在Devs中，程序中调用该函数应将AllDevices
//       作为参数传递给Devs
//2.升降阱信息：保存在Devs中，即升降阱名称和其编号的对应关系，程序中主要
//       依靠编号来区分动作执行从属于哪一个升降阱，程序调用该函数应将全局
//       变量ElevatorMap传递给posMap
void ReadDevices(CString xmlConfig,vector <DeviceInfo> &Devs,
	map <CString,int> &posMap)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//创建对象文档
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//创建解析器实例
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//查找相关节点
	MSXML2::IXMLDOMNodeListPtr pNodes=pRootNode->selectNodes(_T("Device"));

	//读取所有的Devs信息
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

	//读取所有的Elevator信息
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
//读取配置文件中的WQ类型信息，保存在vector WQType中
//该函数读取内容包括:
//1.WQ类型:即调度方案中所设计到的WQ类型，保存在WQs中，
//         程序中调用应将全局变量WQType传递给WQs
void ReadWQTypes(CString xmlConfig,vector <CString> &WQs)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//创建对象文档
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//创建解析器实例
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//查找相关节点
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
//读取配置文件中的调度结果信息，保存在vector acVec中
//该函数读取配置文件中的内容包括:
//1.actions:即调度结果中的所有调度操作，读取结果保存在Acs中，
//          每个action所包括的数据段均是头文件中所定义的数据
//          类型actionInfo，程序中调用应该将全局变量
//          actionVec做为参数传递给Acs
//2.totalTime:调度方案调度方案的总执行时间，保存在全局变量中
void ReadActions(CString xmlConfig,vector <actionInfo> &Acs)
{
	CComPtr <MSXML2::IXMLDOMDocument2> spXMLDOM;

	//创建对象文档
	HRESULT hr=spXMLDOM.CoCreateInstance(_uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		_com_error er(hr);
		AfxMessageBox(er.ErrorMessage());
		/*EndDialog(1);*/
	}

	//创建解析器实例
	_bstr_t xml=_bstr_t(xmlConfig.GetBuffer());
	hr=spXMLDOM->load(xml);
	/*hr=spXMLDOM->load(_T("Devices.xml"))*/;
	MSXML2::IXMLDOMElementPtr pRootNode=spXMLDOM->documentElement;

	//查找相关节点
	MSXML2::IXMLDOMNodeListPtr pNodes=pRootNode->selectNodes(_T("Action"));

	//读取调度执行动作，保存在Acs中
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

	//读取调度总花费时间
	MSXML2::IXMLDOMNodePtr pTotalTimeNode=pRootNode->selectSingleNode(_T("TotalTime"));
	CString total;
	total.Format(_T("%s"),(LPCTSTR)pTotalTimeNode->text);
	titalTime=_ttoi(total);
}

void ReloadPropertiesFromXML()
{
	//重新读取位置信息
	AllDevices.clear();
	ElevatorMap.clear();
	ReadDevices(config_ConstructFile,AllDevices,ElevatorMap);
	resetShowDevices(currentShowPos,posVec);

	/*AfxMessageBox(config_WQTypesFile);*/
	//重新读取WQ类型信息
	weaponType.clear();
	ReadWQTypes(config_WQTypesFile,weaponType);

	//重新读取调度结果信息
	actionVec.clear();
	ReadActions(config_OperResultFile,actionVec);
}

//////////////////////////////////////////////////////////////////////////////////
//重新设置当前显示的升降井位置（Position）调度过程中所涉及到的设备信息（Devices）
//参数：
//1.showPos【in】：当前显示的升降井位置编号
//2.deviceShown【in,out】：当前显示的调度结果所涉及到的设备集合
//      程序调用中应将posVec传递给devicesShown
//程序一旦运行，配置文件中的所有位置信息就已经读入内存并保存在AllDevices中
//通过对应设备的位置编号就可以查询到对应设备属于哪一部升降井
void resetShowDevices(const int showPos,vector <CString> &devicesShown)
{
	devicesShown.clear();

	//设置显示设备信息
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