
// GantDrawer_BetaDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGantDrawer_BetaDlg �Ի���




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
    ** �������̨����ض�����ʾ������Ϣ
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

// CGantDrawer_BetaDlg ��Ϣ�������

BOOL CGantDrawer_BetaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
    InitConsoleWindow();
	ShowWindow(SW_SHOWNORMAL);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	////////////////////////////////////////////////////////////////////////////////
	//�����һ�γ�ʼ��

	setlocale(LC_ALL,"chs");

	//1.���������ļ�����
	initXMLParser();
	TCHAR pFileBuf[256];
	GetCurrentDirectory(256,pFileBuf);
	config_ConstructFile.Format(_T("%s\\Config\\Devices.xml"),pFileBuf);
	config_WQTypesFile.Format(_T("%s\\Config\\WQTYPE.xml"),pFileBuf);
	config_OperResultFile.Format(_T("%s\\Config\\OperationResult.xml"),pFileBuf);
	ReloadPropertiesFromXML();

	//�����������͵Ķ�Ӧ������ɫ
	setWeaponTypeColorMap(_T("WQAA"),RGB(255,0,0));
	setWeaponTypeColorMap(_T("WQAAB"),RGB(0,255,0));
	//2.��ʼ������Tab����
	this->initTabs();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGantDrawer_BetaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGantDrawer_BetaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon); 
}


/*****************************************************************
** added by @chuang	
** time @20140512
** ��ʼ���������
*****************************************************************/

//Tabҳ��ѡ����ƺ���
void CGantDrawer_BetaDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	this->m_MainTab.InsertItem(0,_T("��������"),0);
	this->m_calDlg.Create(IDD_CALCULATE,GetDlgItem(IDC_TAB));
	this->m_calDlg.ShowWindow(SW_SHOWNORMAL);
    this->m_calDlg.MoveWindow(rect);

	//����Gantͼ����ҳ��
	this->m_MainTab.InsertItem(1,_T("Gant����"),1);
	this->gantChildDlg.Create(IDD_CHILDGANT,GetDlgItem(IDC_TAB));
    this->gantChildDlg.MoveWindow(&rect);
	/*this->gantChildDlg.ShowWindow(SW_SHOWNORMAL);*/
	this->gantChildDlg.configToolTips();
	//����Gantdlg�и��ؼ������λ��

	this->gantChildDlg.initCtrls();

	//����Gant����ҳ��
	this->m_MainTab.InsertItem(2,_T("��������"),2);
	this->propertySettingDlg.Create(IDD_DIALOGPROPERTY,GetDlgItem(IDC_TAB));
	this->propertySettingDlg.MoveWindow(&rect);
	//this->propertySettingDlg.ShowWindow(SW_SHOWNORMAL);

	/*this->gantChildDlg.SendMessage(M_INITGANTGRAPH,NULL,NULL);*/
	this->propertySettingDlg.InitCtrls();
};