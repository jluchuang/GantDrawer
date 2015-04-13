
// GantDrawer_BetaDlg.h : ͷ�ļ�
//

#pragma once
#include "m_GantDlg.h"
#include "m_PropertyDlg.h"
#include "m_calculateDlg.h"

// CGantDrawer_BetaDlg �Ի���
class CGantDrawer_BetaDlg : public CDialogEx
{
// ����
public:
	CGantDrawer_BetaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GANTDRAWER_BETA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	/*****************************************************************
	** added by @chuang	
	** time @20140512
	** ��ʼ���������
	*****************************************************************/
public:
	//��Ҫ�ؼ�����
	CTabCtrl m_MainTab;//������tab�ؼ�
	m_GantDlg gantChildDlg;//gantͼ���ƶԻ�����tab0����ʾ
	m_PropertyDlg propertySettingDlg;//�������ý���Ի�����tab1����ʾ

	void initTabs();

	//��д��ϵͳ����
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	m_calculateDlg m_calDlg;
};
