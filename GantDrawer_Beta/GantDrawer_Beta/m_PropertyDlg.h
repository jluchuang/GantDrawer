#pragma once
#include "afxwin.h"


// m_PropertyDlg 对话框

class m_PropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_PropertyDlg)

public:
	m_PropertyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_PropertyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGPROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// WQ类型对应线条颜色选择
	CButton WQColorCh;
	void InitCtrls(void);
	////////////////////////////////////////////////////////////////
	//配置部分控件响应

	// 船体结构配置文件路径
	CString m_ConstructFilePath;
	// 武器配置文件路径
	CString m_WQTypeConfigPath;
	// 调度结果文件路径
	CString m_OperationResultFilePath;

	//船体结构配置按钮点击响应
	afx_msg void OnBnClickedButtonConstruct();
	//调度结果配置按钮点击响应
	afx_msg void OnBnClickedButtonInput();
	//武器类型配置按钮点击响应
	afx_msg void OnBnClickedButtonWqtype();
	//保存设置按钮点击响应
	afx_msg void OnBnClickedButtonSavesetting();

	// 重新读取配置文件信息
	void m_ResetConfig(void);

	////////////////////////////////////////////////////////////////
    //显示部分控件响应

	//升降阱下拉表选择
	afx_msg void OnCbnSelchangeComboElevator();
	//线条颜色设置响应
	afx_msg void OnBnClickedButtonColor();
	// 当前选中显示的升降阱道
	CComboBox currentElevator;
};
