#pragma once
#include "afxwin.h"
#include "propertySettings.h"

// m_GantDlg 对话框
//#define M_INITGANTGRAPH 1030

class m_GantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_GantDlg)

public:
	m_GantDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_GantDlg();

// 对话框数据
	enum { IDD = IDD_CHILDGANT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

/*****************************************************************
** added by @chuang	
** time @20140512
** 绘图部分逻辑声明
*****************************************************************/
public:
	//绘图控件变量
	// 绘制Gant图按钮
	/*CButton drawGantButton;*/
	// gant图绘制时使用的Static控件
	CStatic gantGraph;
	// 水平滚动条
	CScrollBar m_hScrollBar;
	// 垂直滚动条
	CScrollBar m_vSrcollBar;

	//时空图绘制矩形区域
	CRect painRect;
	//是否已经完成图形绘制
	bool hasDrawnFlag;

	// 绘制当前startTime和endTime之间的gant图，时间轴单位步长是timeUint
	bool DrawSubGant(int startTime, int endTime, int timeUnit);
	// 绘制动作信息
	void DrawActions(int stTime,int enTime,vector<actionInfo> &acVec);

	// 箭头与直线之间的角度
	double arrowAlph;
	// 箭头的长度
	double arrowLen;
	// 绘制直线箭头
	void DrawArrow(CDC *pDc,CPen* pPen,CPoint src,CPoint tar);

	//添加提示信息控件
	CToolTipCtrl m_ttc;

	//消息响应函数
	//绘图按钮被按下
	/*afx_msg void OnBnClickedButtonDrawgant();*/

	//重写水平滚动条和垂直滚动条消息响应函数
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	/*afx_msg LRESULT OnMInitgangraph(WPARAM wParam, LPARAM lParam);*/
public:
	afx_msg void OnPaint();

	// 以下两个函数暂时没有作用
	// 注册提示信息
	void configToolTips(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 初始化详细信息显示对应的空间布局
	void init_DetailCtrls(void);
	void initCtrls(void);
	// WQ类型显示信息
	CString wqType;
	// 起始时间显示信息
	int stTime;
	// 位置显示信息
	CString posInfo;
	// 结束时间显示信息
	int enTime;
	// 动作描述显示信息
	CString description;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 获取鼠标当前位置的动作在actionVec中的编号
	int getPtAcNo(CPoint mousePt);


	//Gant图显示的单位刻度时间
	int showTimeUnit;
	//单页所显示的时长
	int singlePageTimeLen;
	//当前显示对应的起始时间
	int curPageStTime;
	// 滚动条拖动，更新当前Gant图
	void UpdateGant();
	//绘图中的横轴线x起点和终点
	int baseStartLeft;
	int baseEndRight;
};