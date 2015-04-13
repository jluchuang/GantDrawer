#include "stdafx.h"

#ifndef PROPERTY_SET_H
#define PROPERTY_SET_H

/*****************************************************************
** added by @chuang	
** time @20140513
** 后台数据驱动，数据结构定义
*****************************************************************/

#include <set>
#include <vector>
#include <map>

using namespace std;

//动作
struct actionInfo 
{
	CString pos;//动作发生位置
	int startTime;//动作发生起始时间
	int endTime;//动作结束时间
	CString actionDes;//动作描述
	CString actionObj;//执行动作的对象
	int objNo;//对象编号（绘制箭头的时候使用）
	int objSrc;//对象的起始点（标记升降井口号），用于过滤显示
};

//动作在绘图区对应的位置
struct actionRect
{
	CRect acRect;//动作在屏幕上对应的矩形区
	int acNo;//动作在actionVec中的编号
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
//全局变量数据声明

//全局变量，保存配置文件中的pos信息
extern vector <CString> posVec;

//全局变量，储存动作信息，从输入文件中读入
extern vector <actionInfo> actionVec;

//全局变量，储存“位置信息”与图形中“横轴线”的位置对应关系
extern map <CString,double> posScreenYMap;

//当前对象编号，上一个动作执行后对应的最右X坐标位置
extern map <int,CPoint> acLastScreenMap;

//WQ类型
extern vector <CString> weaponType;

//WQ类型与界面显示的颜色对应关系
extern map <CString,COLORREF> weaponColorMap;

//动作对应的屏幕矩形区域
extern vector <actionRect> acRecVec;

//升降井口位置,用于显示过滤
extern map <CString,int> ElevatorMap;

//当前显示升降阱口对应的编号
extern int currentShowPos;

//当前显示的升降井口对应对应的设备集合
extern vector <DeviceInfo> AllDevices;

extern CString config_OperResultFile;//调度结果配置文件对应路径
extern CString config_WQTypesFile;//武器类型配置文件对应路径
extern CString config_ConstructFile;//船体结构配置文件对应路径

extern int titalTime;//总调度时间

//////////////////////////////////////////////////////////////////////////
//全局基本函数声明

//设置位置信息对应的绘图位置信息
extern void setPosScreenYMap(CString pos,double screenY);

//设置动作队列
extern void setActions();

//设置WQ类型
extern void setWeaponType();

//设置武器类型和显示颜色的对应关系
extern void setWeaponTypeColorMap(CString wType, COLORREF colo);

//设置动作编号objNo对应的上衣个动作对应的X坐标信息
extern void setAcLastScreenXMap(int objNo,CPoint lastPoint);

extern void initXMLParser();
extern void WriteToXML();

//////////////////////////////////////////////////////////////////////////
//读取配置文件中的所有位置信息和设备信息
//该文件中的读取内容包括：
//1.所有位置(Device)信息:保存在Devs中，程序中调用该函数应将AllDevices
//       作为参数传递给Devs
//2.升降阱信息：保存在Devs中，即升降阱名称和其编号的对应关系，程序中主要
//       依靠编号来区分动作执行从属于哪一个升降阱，程序调用该函数应将全局
//       变量ElevatorMap传递给posMap
extern void ReadDevices(CString xmlConfig,vector <DeviceInfo> &Devs,map <CString,int> &posMap);

//////////////////////////////////////////////////////////////////////////
//读取配置文件中的WQ类型信息，保存在vector WQType中
//该函数读取内容包括:
//1.WQ类型:即调度方案中所设计到的WQ类型，保存在WQs中，
//         程序中调用应将全局变量WQType传递给WQs
extern void ReadWQTypes(CString xmlConfig,vector <CString> &WQs);

//////////////////////////////////////////////////////////////////////////
//读取配置文件中的调度结果信息，保存在vector acVec中
//该函数读取配置文件中的内容包括:
//1.actions:即调度结果中的所有调度操作，读取结果保存在Acs中，
//          每个action所包括的数据段均是头文件中所定义的数据
//          类型actionInfo，程序中调用应该将actionVec做为参
//          数传递给Acs
//2.totalTime:调度方案调度方案的总执行时间，保存在全局变量中
extern void ReadActions(CString xmlConfig,vector <CString> &Acs);

extern void WriteXMLNode(MSXML2::IXMLDOMDocument2Ptr pDocument,
	MSXML2::IXMLDOMNodePtr pParentNode,
	CString deviceName,
	long Type);

//从xml文件中读取配置信息
extern void ReloadPropertiesFromXML();

//////////////////////////////////////////////////////////////////////////////////
//重新设置当前显示的升降井位置（Position）调度过程中所涉及到的设备信息（Devices）
//参数：
//1.showPos【in】：当前显示的升降井位置编号
//2.deviceShown【in,out】：当前显示的调度结果所涉及到的设备集合
//      程序调用中应将posVec传递给devicesShown
//程序一旦运行，配置文件中的所有位置信息就已经读入内存并保存在AllDevices中
//通过对应设备的位置编号就可以查询到对应设备属于哪一部升降井
extern void resetShowDevices(const int showPos,vector <CString> &devicesShown);


#endif