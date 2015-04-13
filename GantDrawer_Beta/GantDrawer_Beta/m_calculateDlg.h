#pragma once
#include "RandGenerator.h"
#include "SequenceSet.h"

// m_calculateDlg 对话框

class m_calculateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_calculateDlg)

public:
	m_calculateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_calculateDlg();

// 对话框数据
	enum { IDD = IDD_CALCULATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
private:
    SequenceSet * seqS;
};
