
// GantDrawer_BetaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GantDrawer_Beta.h"
#include "GantDrawer_BetaDlg.h"
#include "afxdialogex.h"
#include "m_GantDlg.h"
#include "comutil.h"
#include "propertySettings.h"
#include <clocale>
#include <set>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGantDrawer_BetaDlg 对话框




CGantDrawer_BetaDlg::CGantDrawer_BetaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGantDrawer_BetaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGantDrawer_BetaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_MainTab);
}

BEGIN_MESSAGE_MAP(CGantDrawer_BetaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CGantDrawer_BetaDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()

/***************************************************************************************
    ** added by @chuang
    ** time @20140619
    ** 申请控制台输出重定向，显示调试信息
    ***************************************************************************************/
void InitConsoleWindow(){
    int nCrt = 0;
    FILE *fp;
    AllocConsole();
    nCrt=_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);
    fp=_fdopen(nCrt,"w");
    *stdout=*fp;
    setvbuf(stdout,NULL,_IONBF,0);
}

// CGantDrawer_BetaDlg 消息处理程序

BOOL CGantDrawer_BetaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
    InitConsoleWindow();
	ShowWindow(SW_SHOWNORMAL);
	// TODO: 在此添加额外的初始化代码
	////////////////////////////////////////////////////////////////////////////////
	//程序第一次初始化

	setlocale(LC_ALL,"chs");

	//1.读入输入文件内容
	initXMLParser();
	TCHAR pFileBuf[256];
	GetCurrentDirectory(256,pFileBuf);
	config_ConstructFile.Format(_T("%s\\Config\\Devices.xml"),pFileBuf);
	config_WQTypesFile.Format(_T("%s\\Config\\WQTYPE.xml"),pFileBuf);
	config_OperResultFile.Format(_T("%s\\Config\\OperationResult.xml"),pFileBuf);
	ReloadPropertiesFromXML();

	//设置武器类型的对应线条颜色
	setWeaponTypeColorMap(_T("WQAA"),RGB(255,0,0));
	setWeaponTypeColorMap(_T("WQAAB"),RGB(0,255,0));
	//2.初始化程序Tab界面
	this->initTabs();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CGantDrawer_BetaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGantDrawer_BetaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGantDrawer_BetaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon); 
}


/*****************************************************************
** added by @chuang	
** time @20140512
** 初始化程序界面
*****************************************************************/

//Tab页面选择控制函数
void CGantDrawer_BetaDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	/*AfxMessageBox(_T("Select Changed"));*/
	int num=this->m_MainTab.GetCurSel();
	switch (num)
	{
	case 0:
		this->m_calDlg.ShowWindow(SW_SHOW);
		this->propertySettingDlg.ShowWindow(SW_HIDE);
		this->gantChildDlg.ShowWindow(SW_HIDE);
		break;
	case 1:
		this->m_calDlg.ShowWindow(SW_HIDE);
		this->propertySettingDlg.ShowWindow(SW_HIDE);
		this->gantChildDlg.ShowWindow(SW_SHOW);
		break;
	case 2:
		this->m_calDlg.ShowWindow(SW_HIDE);
		this->gantChildDlg.ShowWindow(SW_HIDE);
		this->propertySettingDlg.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CGantDrawer_BetaDlg::initTabs()
{
    CRect rect;
    this->m_MainTab.GetClientRect(&rect);
    rect.top+=40;
    rect.left+=10;
    rect.right-=10;
    rect.bottom-=20;

	this->m_MainTab.InsertItem(0,_T("方案生成"),0);
	this->m_calDlg.Create(IDD_CALCULATE,GetDlgItem(IDC_TAB));
	this->m_calDlg.ShowWindow(SW_SHOWNORMAL);
    this->m_calDlg.MoveWindow(rect);

	//设置Gant图绘制页面
	this->m_MainTab.InsertItem(1,_T("Gant绘制"),1);
	this->gantChildDlg.Create(IDD_CHILDGANT,GetDlgItem(IDC_TAB));
    this->gantChildDlg.MoveWindow(&rect);
	/*this->gantChildDlg.ShowWindow(SW_SHOWNORMAL);*/
	this->gantChildDlg.configToolTips();
	//设置Gantdlg中各控件的相对位置

	this->gantChildDlg.initCtrls();

	//设置Gant属性页面
	this->m_MainTab.InsertItem(2,_T("参数配置"),2);
	this->propertySettingDlg.Create(IDD_DIALOGPROPERTY,GetDlgItem(IDC_TAB));
	this->propertySettingDlg.MoveWindow(&rect);
	//this->propertySettingDlg.ShowWindow(SW_SHOWNORMAL);

	/*this->gantChildDlg.SendMessage(M_INITGANTGRAPH,NULL,NULL);*/
	this->propertySettingDlg.InitCtrls();
};