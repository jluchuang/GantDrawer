// m_PropertyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GantDrawer_Beta.h"
#include "m_PropertyDlg.h"
#include "afxdialogex.h"
#include "propertySettings.h"


// m_PropertyDlg �Ի���

IMPLEMENT_DYNAMIC(m_PropertyDlg, CDialogEx)

m_PropertyDlg::m_PropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(m_PropertyDlg::IDD, pParent)
	, m_ConstructFilePath(_T(""))
	, m_WQTypeConfigPath(_T(""))
	, m_OperationResultFilePath(_T(""))
{
	TCHAR pFileBuf[256];
	GetCurrentDirectory(256,pFileBuf);
	this->m_ConstructFilePath.Format(_T("%s\\Config\\Devices.xml"),pFileBuf);
	this->m_WQTypeConfigPath.Format(_T("%s\\Config\\WQTYPE.xml"),pFileBuf);
	this->m_OperationResultFilePath.Format(_T("%s\\Config\\OperationResult.xml"),pFileBuf);
}

m_PropertyDlg::~m_PropertyDlg()
{
}

void m_PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTRUCT, m_ConstructFilePath);
	DDX_Text(pDX, IDC_EDIT_WQTYPE, m_WQTypeConfigPath);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_OperationResultFilePath);
	DDX_Control(pDX, IDC_COMBO_ELEVATOR, currentElevator);
}


BEGIN_MESSAGE_MAP(m_PropertyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONSTRUCT, &m_PropertyDlg::OnBnClickedButtonConstruct)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &m_PropertyDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_WQTYPE, &m_PropertyDlg::OnBnClickedButtonWqtype)
	ON_CBN_SELCHANGE(IDC_COMBO_ELEVATOR, &m_PropertyDlg::OnCbnSelchangeComboElevator)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &m_PropertyDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_SAVESETTING, &m_PropertyDlg::OnBnClickedButtonSavesetting)
END_MESSAGE_MAP()

/*****************************************************************
** added by @chuang	
** time @20140512
** ��ʼ���������
*****************************************************************/

// ��ʼ�����ý���ؼ�λ��
void m_PropertyDlg::InitCtrls(void)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);

	CRect tempRect;

	//���á�������Ϣ��λ��
	CWnd *pWnd=GetDlgItem(IDC_STATIC_CONFIG);
	CRect ConfigRect;
	ConfigRect.left=ClientRect.left;
	ConfigRect.right=(ClientRect.right+ClientRect.left)/2-10+ClientRect.left;
	ConfigRect.top=ClientRect.top;
	ConfigRect.bottom=ClientRect.bottom;
	pWnd->MoveWindow(ConfigRect);

	//����ṹ����
	pWnd=GetDlgItem(IDC_STATIC_CONSTRUCT);
	tempRect.left=ConfigRect.left+10;
	tempRect.right=(ConfigRect.left+ConfigRect.right)/4+ConfigRect.left;
	tempRect.top=ConfigRect.top+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_EDIT_CONSTRUCT);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-(ConfigRect.left+ConfigRect.right)/4-10;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_BUTTON_CONSTRUCT);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-10;
	pWnd->MoveWindow(tempRect);

	//���Ƚ������
	pWnd=GetDlgItem(IDC_STATIC_INPUT);
	tempRect.left=ConfigRect.left+10;
	tempRect.right=(ConfigRect.right-ConfigRect.left)/4+ConfigRect.left;
	tempRect.top=tempRect.bottom+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_EDIT_INPUT);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-(ConfigRect.right-ConfigRect.left)/4-10;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_BUTTON_INPUT);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-10;
	pWnd->MoveWindow(tempRect);

	//WQ���Ͳ���
	pWnd=GetDlgItem(IDC_STATIC_WQTYPE);
	tempRect.left=ConfigRect.left+10;
	tempRect.right=(ConfigRect.right-ConfigRect.left)/4+ConfigRect.left;
	tempRect.top=tempRect.bottom+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_EDIT_WQTYPE);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-(ConfigRect.right-ConfigRect.left)/4-10;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_BUTTON_WQTYPE);
	tempRect.left=tempRect.right+10;
	tempRect.right=ConfigRect.right-10;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_BUTTON_SAVESETTING);
	tempRect.left=(ConfigRect.left+ConfigRect.right)/2;
	tempRect.right=ConfigRect.right-10;
	tempRect.top=tempRect.bottom+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	//���á���ʾ���á�λ��
	pWnd=GetDlgItem(IDC_STATIC_SETTING);
	CRect SettingsRect;
	SettingsRect.left=(ClientRect.right+ClientRect.left)/2+10;
	SettingsRect.right=ClientRect.right;
	SettingsRect.top=ClientRect.top;
	SettingsRect.bottom=ClientRect.bottom;
	pWnd->MoveWindow(SettingsRect);

	//������ѡ�񲿷�
	pWnd=GetDlgItem(IDC_STATIC_ELEVATOR);
	tempRect.left=SettingsRect.left+10;
	tempRect.right=(SettingsRect.right-SettingsRect.left)/3+SettingsRect.left;
	tempRect.top=SettingsRect.top+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_COMBO_ELEVATOR);
	tempRect.left=tempRect.right+10;
	tempRect.right=SettingsRect.right-10;
	pWnd->MoveWindow(tempRect);

	//��ʼ�������б�ѡ������
	map <CString,int>::iterator iter;
	for (iter=ElevatorMap.begin();iter!=ElevatorMap.end();iter++)
	{
		this->currentElevator.AddString(iter->first);
	}

	//������ѡ�񲿷�
	pWnd=GetDlgItem(IDC_STATIC_COLOR);
	tempRect.left=SettingsRect.left+10;
	tempRect.right=(SettingsRect.right-SettingsRect.left)/3+SettingsRect.left;
	tempRect.top=tempRect.bottom+20;
	tempRect.bottom=tempRect.top+20;
	pWnd->MoveWindow(tempRect);

	pWnd=GetDlgItem(IDC_BUTTON_COLOR);
	tempRect.left=tempRect.right+10;
	tempRect.right=SettingsRect.right-10;
	pWnd->MoveWindow(tempRect);
}

//����ṹ���ð�ť����¼���Ӧ
void m_PropertyDlg::OnBnClickedButtonConstruct()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defaultTypes(".xml");
	CString allTypes("xml�ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*||");
	//MessageBox((LPCTSTR)"hehere");
	CFileDialog filedlg(true,//�������ļ��Ի���falseΪ�����ļ��Ի���
		defaultTypes,//�򿪵��ļ�����
		NULL,//Ĭ�ϴ򿪵��ļ���
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,//��ֻ���ļ�
		allTypes//���п��Դ򿪵��ļ�����
		);
	INT_PTR fileDlgResponse = filedlg.DoModal();
	if(fileDlgResponse==IDOK)
	{
		CString m_filePath=filedlg.GetPathName();//��ȡ�ļ�·��
		CString mpath=m_filePath;
		/*SetDlgItemText(IDC_TxtPath,mpath);*/

		this->m_ConstructFilePath=mpath;
		UpdateData(false);
	}
}


void m_PropertyDlg::OnBnClickedButtonInput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defaultTypes(".xml");
	CString allTypes("xml�ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*||");
	//MessageBox((LPCTSTR)"hehere");
	CFileDialog filedlg(true,//�������ļ��Ի���falseΪ�����ļ��Ի���
		defaultTypes,//�򿪵��ļ�����
		NULL,//Ĭ�ϴ򿪵��ļ���
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,//��ֻ���ļ�
		allTypes//���п��Դ򿪵��ļ�����
		);
	INT_PTR fileDlgResponse = filedlg.DoModal();
	if(fileDlgResponse==IDOK)
	{
		CString m_filePath=filedlg.GetPathName();//��ȡ�ļ�·��
		CString mpath=m_filePath;
		/*SetDlgItemText(IDC_TxtPath,mpath);*/

		this->m_OperationResultFilePath=mpath;
		UpdateData(false);
	}
}


void m_PropertyDlg::OnBnClickedButtonWqtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defaultTypes(".xml");
	CString allTypes("xml�ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*||");
	//MessageBox((LPCTSTR)"hehere");
	CFileDialog filedlg(true,//�������ļ��Ի���falseΪ�����ļ��Ի���
		defaultTypes,//�򿪵��ļ�����
		NULL,//Ĭ�ϴ򿪵��ļ���
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,//��ֻ���ļ�
		allTypes//���п��Դ򿪵��ļ�����
		);
	INT_PTR fileDlgResponse = filedlg.DoModal();
	if(fileDlgResponse==IDOK)
	{
		CString m_filePath=filedlg.GetPathName();//��ȡ�ļ�·��
		CString mpath=m_filePath;
		/*SetDlgItemText(IDC_TxtPath,mpath);*/

		this->m_WQTypeConfigPath=mpath;
		UpdateData(false);
	}
}

void m_PropertyDlg::OnBnClickedButtonSavesetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_ResetConfig();

}

void m_PropertyDlg::OnCbnSelchangeComboElevator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex=this->currentElevator.GetCurSel();
	CString curSel;
	this->currentElevator.GetLBText(nIndex,curSel);
	map <CString,int>::iterator iter;
	iter=ElevatorMap.find(curSel);
	if (iter!=ElevatorMap.end())
	{
		currentShowPos=iter->second;
		resetShowDevices(currentShowPos,posVec);
	}
	else
	{
		AfxMessageBox(_T("��ʾλ����Ϣ����������ѡ��"));
	}
}


void m_PropertyDlg::OnBnClickedButtonColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


/////////////////////////////////////////////////////////////////
// �����µ������ļ�·��
// ���ԭ�е��ڴ汣��ĸ��ֵ��Ȼ�����Ϣ
// ���µ������ļ��ж�ȡ��Ӧ����

// ���¶�ȡ�����ļ���Ϣ
void m_PropertyDlg::m_ResetConfig(void)
{
	//AfxMessageBox(_T("here"));
	currentShowPos=0;
	config_OperResultFile=this->m_OperationResultFilePath;
	config_ConstructFile=this->m_ConstructFilePath;
	config_WQTypesFile=this->m_WQTypeConfigPath;
	ReloadPropertiesFromXML();
}
