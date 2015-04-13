#pragma once
#include "afxwin.h"
#include "propertySettings.h"

// m_GantDlg �Ի���
//#define M_INITGANTGRAPH 1030

class m_GantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_GantDlg)

public:
	m_GantDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_GantDlg();

// �Ի�������
	enum { IDD = IDD_CHILDGANT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

/*****************************************************************
** added by @chuang	
** time @20140512
** ��ͼ�����߼�����
*****************************************************************/
public:
	//��ͼ�ؼ�����
	// ����Gantͼ��ť
	/*CButton drawGantButton;*/
	// gantͼ����ʱʹ�õ�Static�ؼ�
	CStatic gantGraph;
	// ˮƽ������
	CScrollBar m_hScrollBar;
	// ��ֱ������
	CScrollBar m_vSrcollBar;

	//ʱ��ͼ���ƾ�������
	CRect painRect;
	//�Ƿ��Ѿ����ͼ�λ���
	bool hasDrawnFlag;

	// ���Ƶ�ǰstartTime��endTime֮���gantͼ��ʱ���ᵥλ������timeUint
	bool DrawSubGant(int startTime, int endTime, int timeUnit);
	// ���ƶ�����Ϣ
	void DrawActions(int stTime,int enTime,vector<actionInfo> &acVec);

	// ��ͷ��ֱ��֮��ĽǶ�
	double arrowAlph;
	// ��ͷ�ĳ���
	double arrowLen;
	// ����ֱ�߼�ͷ
	void DrawArrow(CDC *pDc,CPen* pPen,CPoint src,CPoint tar);

	//�����ʾ��Ϣ�ؼ�
	CToolTipCtrl m_ttc;

	//��Ϣ��Ӧ����
	//��ͼ��ť������
	/*afx_msg void OnBnClickedButtonDrawgant();*/

	//��дˮƽ�������ʹ�ֱ��������Ϣ��Ӧ����
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	/*afx_msg LRESULT OnMInitgangraph(WPARAM wParam, LPARAM lParam);*/
public:
	afx_msg void OnPaint();

	// ��������������ʱû������
	// ע����ʾ��Ϣ
	void configToolTips(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ʼ����ϸ��Ϣ��ʾ��Ӧ�Ŀռ䲼��
	void init_DetailCtrls(void);
	void initCtrls(void);
	// WQ������ʾ��Ϣ
	CString wqType;
	// ��ʼʱ����ʾ��Ϣ
	int stTime;
	// λ����ʾ��Ϣ
	CString posInfo;
	// ����ʱ����ʾ��Ϣ
	int enTime;
	// ����������ʾ��Ϣ
	CString description;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// ��ȡ��굱ǰλ�õĶ�����actionVec�еı��
	int getPtAcNo(CPoint mousePt);


	//Gantͼ��ʾ�ĵ�λ�̶�ʱ��
	int showTimeUnit;
	//��ҳ����ʾ��ʱ��
	int singlePageTimeLen;
	//��ǰ��ʾ��Ӧ����ʼʱ��
	int curPageStTime;
	// �������϶������µ�ǰGantͼ
	void UpdateGant();
	//��ͼ�еĺ�����x�����յ�
	int baseStartLeft;
	int baseEndRight;
};