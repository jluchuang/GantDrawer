
// GantDrawer_BetaDlg.h : 头文件
//

#pragma once
#include "m_GantDlg.h"
#include "m_PropertyDlg.h"
#include "m_calculateDlg.h"

// CGantDrawer_BetaDlg 对话框
class CGantDrawer_BetaDlg : public CDialogEx
{
// 构造
public:
	CGantDrawer_BetaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GANTDRAWER_BETA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	/*****************************************************************
	** added by @chuang	
	** time @20140512
	** 初始化程序界面
	*****************************************************************/
public:
	//主要控件变量
	CTabCtrl m_MainTab;//主界面tab控件
	m_GantDlg gantChildDlg;//gant图绘制对话框，在tab0中显示
	m_PropertyDlg propertySettingDlg;//属性设置界面对话框，在tab1中显示

	void initTabs();

	//重写的系统函数
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	m_calculateDlg m_calDlg;
};
