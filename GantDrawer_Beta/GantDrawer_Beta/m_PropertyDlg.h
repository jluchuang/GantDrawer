#pragma once
#include "afxwin.h"


// m_PropertyDlg �Ի���

class m_PropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_PropertyDlg)

public:
	m_PropertyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_PropertyDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGPROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// WQ���Ͷ�Ӧ������ɫѡ��
	CButton WQColorCh;
	void InitCtrls(void);
	////////////////////////////////////////////////////////////////
	//���ò��ֿؼ���Ӧ

	// ����ṹ�����ļ�·��
	CString m_ConstructFilePath;
	// ���������ļ�·��
	CString m_WQTypeConfigPath;
	// ���Ƚ���ļ�·��
	CString m_OperationResultFilePath;

	//����ṹ���ð�ť�����Ӧ
	afx_msg void OnBnClickedButtonConstruct();
	//���Ƚ�����ð�ť�����Ӧ
	afx_msg void OnBnClickedButtonInput();
	//�����������ð�ť�����Ӧ
	afx_msg void OnBnClickedButtonWqtype();
	//�������ð�ť�����Ӧ
	afx_msg void OnBnClickedButtonSavesetting();

	// ���¶�ȡ�����ļ���Ϣ
	void m_ResetConfig(void);

	////////////////////////////////////////////////////////////////
    //��ʾ���ֿؼ���Ӧ

	//������������ѡ��
	afx_msg void OnCbnSelchangeComboElevator();
	//������ɫ������Ӧ
	afx_msg void OnBnClickedButtonColor();
	// ��ǰѡ����ʾ���������
	CComboBox currentElevator;
};
