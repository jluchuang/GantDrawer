#pragma once
#include "RandGenerator.h"
#include "SequenceSet.h"

// m_calculateDlg �Ի���

class m_calculateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_calculateDlg)

public:
	m_calculateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_calculateDlg();

// �Ի�������
	enum { IDD = IDD_CALCULATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
private:
    SequenceSet * seqS;
};
