// m_GantDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GantDrawer_Beta.h"
#include "m_GantDlg.h"
#include "afxdialogex.h"
#include "propertySettings.h"

// m_GantDlg �Ի���

IMPLEMENT_DYNAMIC(m_GantDlg, CDialogEx)

m_GantDlg::m_GantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(m_GantDlg::IDD, pParent)
	, wqType(_T(""))
	, stTime(0)
	, posInfo(_T(""))
	, enTime(0)
	, description(_T(""))
{
	arrowAlph = 10.0;
	arrowLen=10.0;
	showTimeUnit = 5;
	this->singlePageTimeLen=100;
	this->curPageStTime=0;
	this->baseEndRight=0;
	this->baseStartLeft=0;
}

m_GantDlg::~m_GantDlg()
{
}

void m_GantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_BUTTON_DRAWGANT, drawGantButton);*/
	DDX_Control(pDX, IDC_STATIC_GANTGRAPH, gantGraph);
	DDX_Control(pDX, IDC_SCROLLBAR_HORZ, m_hScrollBar);
	DDX_Control(pDX, IDC_SCROLLBAR_VER, m_vSrcollBar);
	DDX_Text(pDX, IDC_EDIT_WQTYPE, wqType);
	DDX_Text(pDX, IDC_EDIT_STTIME, stTime);
	DDX_Text(pDX, IDC_EDIT_POS, posInfo);
	DDX_Text(pDX, IDC_EDIT_ENTIME, enTime);
	DDX_Text(pDX, IDC_EDIT_DES, description);
}


BEGIN_MESSAGE_MAP(m_GantDlg, CDialogEx)
	/*ON_BN_CLICKED(IDC_BUTTON_DRAWGANT, &m_GantDlg::OnBnClickedButtonDrawgant)*/
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//ON_MESSAGE(M_INITGANTGRAPH, &m_GantDlg::OnMInitgangraph)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// m_GantDlg ��Ϣ�������

/*****************************************************************
** added by @chuang	
** time @20140512
** �û��������gantͼ��Ϣ��Ӧ����
*****************************************************************/



//void m_GantDlg::OnBnClickedButtonDrawgant()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDC *paintDc=this->gantGraph.GetDC();
//	if (paintDc==INVALID_HANDLE_VALUE)
//	{
//		AfxMessageBox(_T("�޷���ȡ��ͼ���ھ��"));
//		return;
//	}
//
//	this->gantGraph.GetClientRect(&painRect);
//	painRect.top+=10;
//	painRect.bottom-=10;
//	painRect.right-=10;
//	painRect.left+=100;
//
//	//���û�ͼ������ɫ
//	CBrush whiteBrush;
//	whiteBrush.CreateSolidBrush(RGB(255,255,255));
//	paintDc->FillRect(painRect,&whiteBrush);
//	
//	//���û�ͼ������߿�
//	CPen blackPen;
//	blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
//	paintDc->SelectObject(&blackPen);
//	paintDc->MoveTo(painRect.TopLeft());
//	paintDc->LineTo(CPoint(painRect.right,painRect.top));
//	paintDc->LineTo(CPoint(painRect.right,painRect.bottom));
//	paintDc->LineTo(CPoint(painRect.left,painRect.bottom));
//	paintDc->LineTo(painRect.TopLeft());
//
//	//�����������������϶���Χ
//	this->m_hScrollBar.SetScrollRange(0,100);
//	this->m_vSrcollBar.SetScrollRange(0,100);
//
//	this->DrawSubGant(0,130,5);
////		
//}


//ˮƽ��������Ϣ������
void m_GantDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int temp1=0;
	int temp2=0;
	CString tempPos;
	/*AfxMessageBox(_T("Scroll bar"));*/
	temp1=pScrollBar->GetScrollPos();
	int nMax,nMin;
	pScrollBar->GetScrollRange(&nMin,&nMax);
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT:
		temp2=(nMax-nMin)/10;
		if (temp1-temp2>nMin)
		{
			temp1-=temp2;
		}
		else
		{
			temp1=nMin;
		}
		pScrollBar->SetScrollPos(temp1);
		break;
	case SB_LINERIGHT:
		temp2=(nMax-nMin)/10;
		if (temp1-temp2>nMin)
		{
			temp1=nMax;
		}
		else
		{
			temp1+=temp2;
		}
		pScrollBar->SetScrollPos(temp1);
		break;
	}
	int posTime=pScrollBar->GetScrollPos();
	this->curPageStTime=posTime;
	this->UpdateGant();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void m_GantDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int temp1=0;
	int temp2=0;
	/*AfxMessageBox(_T("Scroll bar"));*/
	temp1=pScrollBar->GetScrollPos();
	int nMax,nMin;
	pScrollBar->GetScrollRange(&nMin,&nMax);
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT:
		temp2=(nMax-nMin)/10;
		if (temp1-temp2>nMin)
		{
			temp1-=temp2;
		}
		else
		{
			temp1=nMin;
		}
		pScrollBar->SetScrollPos(temp1);
		break;
	case SB_LINERIGHT:
		temp2=(nMax-nMin)/10;
		if (temp1-temp2>nMin)
		{
			temp1=nMax;
		}
		else
		{
			temp1+=temp2;
		}
		pScrollBar->SetScrollPos(temp1);
		break;
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
/********************************************************************
** ���±���������propertySettings.h��
** ȫ��Ϊȫ�ֱ���
********************************************************************/

//////////////////////////////////////////////////////////////////////

// ���Ƶ�ǰstartTime��endTime֮���gantͼ��ʱ���ᵥλ������timeUint
bool m_GantDlg::DrawSubGant(int startTime, int endTime, int timeUnit)
{
	CDC *paintDc=this->gantGraph.GetDC();
	if (paintDc==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("�޷���ȡ��ͼ������"));
		return false;
	}

	this->gantGraph.GetClientRect(&painRect);
	painRect.top+=10;
	painRect.bottom-=10;
	painRect.right-=10;
	painRect.left+=100;

	//����ʱ�����
	double TimeBarY=painRect.top+20.0;
	this->baseStartLeft=painRect.left+30;
	this->baseEndRight=painRect.right-30;
	paintDc->MoveTo(this->baseStartLeft,TimeBarY);
	paintDc->LineTo(this->baseEndRight,TimeBarY);

	assert(endTime>startTime);
	double lenUnit=(baseEndRight-this->baseStartLeft)/((endTime-startTime)/timeUnit);

	//���ƿ̶�
	int d_value=0;
	if ((startTime%timeUnit)!=0)
	{
		d_value=timeUnit-startTime%timeUnit;
	}

	int tempTime=startTime+d_value;
	double startPos=this->baseStartLeft+
		((tempTime-startTime)/(endTime-startTime))*(baseEndRight-this->baseStartLeft);

	//�̶�ֵ�������������ʱ����
	CRect timeRect;
	timeRect.left=startPos-lenUnit/2;
	timeRect.right=startPos+lenUnit/2;
	timeRect.top=painRect.top+5;
	timeRect.bottom=painRect.top+20;

	//���ƿ̶���
	for (;tempTime<=endTime;tempTime+=timeUnit)
	{
		if (tempTime%2==0)
		{
			paintDc->MoveTo(CPoint(startPos,painRect.top+20));
			paintDc->LineTo(CPoint(startPos,painRect.top+40));
			timeRect.left=(startPos-lenUnit);
			timeRect.right=(startPos+lenUnit);
			CString timeStr;
			timeStr.Format(_T("%d"),tempTime);
			paintDc->DrawText(timeStr,timeRect,DT_CENTER);
		}
		paintDc->MoveTo(CPoint(startPos,painRect.top+20));
		paintDc->LineTo(CPoint(startPos,painRect.top+30));
		startPos+=lenUnit;
	}

	//����Pos������
	int posNum=posVec.size();
	if (posNum==0)
	{
		AfxMessageBox(_T("��λ����Ϣ����ͼʧ�ܣ�����"));
		return false;
	}
	double yStep=((painRect.bottom-20)-(TimeBarY+60))*1.0/(posNum-1);
	double stPosY=TimeBarY+60;

	CRect posRect;
	posRect.left=painRect.left-80;
	posRect.right=painRect.left-10;
	posRect.top=stPosY-10;
	posRect.bottom=stPosY+10;

	vector <CString>::iterator iter=posVec.begin();
	posScreenYMap.clear();
	for (;iter<posVec.end();iter++)
	{
		paintDc->MoveTo(this->baseStartLeft,stPosY);
		paintDc->LineTo(this->baseEndRight,stPosY);

		//����λ�úͻ�ͼy�����Ӧ��ϵ
		setPosScreenYMap(*iter,stPosY);

		posRect.top=stPosY-10;
		posRect.bottom=stPosY+10;
		paintDc->DrawText(*iter,posRect,DT_CENTER);

		stPosY+=yStep;
	}

	//���ƶ�����Ϣ
	this->DrawActions(startTime,endTime,actionVec);
	return false;
}


//afx_msg LRESULT m_GantDlg::OnMInitgangraph(WPARAM wParam, LPARAM lParam)
//{
//	//�˴��������⣬���ڻ�������������������������Ļ���Ļ�ͻ�һ������
//	AfxMessageBox(_T("������Ϣ�ѱ���"));
//
//	CDC *paintDc=this->gantGraph.GetDC();
//	if (paintDc==INVALID_HANDLE_VALUE)
//	{
//		AfxMessageBox(_T("�޷���ȡ��ͼ���ھ��"));
//		return 0;
//	}
//
//	//�����������������϶���Χ
//	this->m_hScrollBar.SetScrollRange(0,100);
//	this->m_vSrcollBar.SetScrollRange(0,100);
//
//	this->gantGraph.GetClientRect(&painRect);
//	painRect.top+=10;
//	painRect.bottom-=10;
//	painRect.right-=10;
//	painRect.left+=100;
//
//	////���û�ͼ������ɫ
//	//CBrush whiteBrush;
//	//whiteBrush.CreateSolidBrush(RGB(255,255,255));
//	//paintDc->FillRect(painRect,&whiteBrush);
//
//	////���û�ͼ������߿�
//	//CPen blackPen;
//	//blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
//	//paintDc->SelectObject(&blackPen);
//	//paintDc->MoveTo(painRect.TopLeft());
//	//paintDc->LineTo(CPoint(painRect.right,painRect.top));
//	//paintDc->LineTo(CPoint(painRect.right,painRect.bottom));
//	//paintDc->LineTo(CPoint(painRect.left,painRect.bottom));
//	//paintDc->LineTo(painRect.TopLeft());
//
//	this->DrawSubGant(0,130,5);
//	return 0;
//}


// ���ƶ�����Ϣ
void m_GantDlg::DrawActions(int stTime,int enTime,vector<actionInfo> &acVec)
{
	CDC *paintDc=this->gantGraph.GetDC();
	if (paintDc==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("�޷���ȡ��ͼ���ھ��"));
		return;
	}
	/*AfxMessageBox(_T("���ƶ�����Ϣ"));*/
	CPen actionPen;
	actionPen.CreatePen(PS_SOLID,3,RGB(128,255,0));
	
	vector <actionInfo>::iterator iter;
	acLastScreenMap.clear();
	int acNo=0;
	acRecVec.clear();
	for (iter=acVec.begin();iter<acVec.end();iter++)
	{
		//���жϵ�ǰ�����Ƿ����ڵ�ǰ����ʾ����
		if (currentShowPos!=0&&iter->objSrc!=currentShowPos)
		{
			continue;
		}

		//1.��ȡ�����û�����ɫ

		//2.ת������ʱ��=>��ͼ�߶�X����λ��
		int acStTime=iter->startTime;
		int acEnTime=iter->endTime;

		//�жϵ�ǰ�����Ƿ����˵�ǰ����ʾʱ�䷶Χ��
		if (acStTime>=enTime||acEnTime<=stTime)
		{
			acNo++;
			continue;
		}

		double stXPos=0.0;
		double enXPos=0.0;
		if (acStTime>stTime&&acEnTime<enTime)
		{
			stXPos=this->baseStartLeft+
				((acStTime-stTime)*1.0/(enTime-stTime))*(this->baseEndRight-this->baseStartLeft);
			enXPos=this->baseStartLeft+
				((acEnTime-stTime)*1.0/(enTime-stTime))*(this->baseEndRight-this->baseStartLeft);;
		}
		else
		{
			if (acStTime>stTime&&acEnTime>enTime)
			{
				stXPos=this->baseStartLeft+
					((acStTime-stTime)*1.0/(enTime-stTime))*(this->baseEndRight-this->baseStartLeft);
				enXPos=this->baseEndRight;
			}
			else
			{
				stXPos=this->baseStartLeft;
				enXPos=this->baseStartLeft+
					((acEnTime-stTime)*1.0/(enTime-stTime))*(this->baseEndRight-this->baseStartLeft);
			}
		}

		//3.��ȡ������Ӧλ�ú�����Ϣ
		double acYPos=0.0;
		map<CString,double>::iterator iterMap=posScreenYMap.find(iter->pos);
		if (iterMap!=posScreenYMap.end())
		{
			acYPos=iterMap->second;
		}

		//4.���ƶ���
		//��ö�Ӧ��������ɫ
		map<CString,COLORREF>::iterator iterColo=weaponColorMap.find(iter->actionObj);
		if (iterColo!=weaponColorMap.end())
		{
			actionPen.DeleteObject();
			actionPen.CreatePen(PS_SOLID,3,iterColo->second);
		}
		paintDc->SelectObject(actionPen);
		paintDc->MoveTo(stXPos,acYPos);
		paintDc->LineTo(enXPos,acYPos);
		actionRect  acRec;
		acRec.acRect.left=stXPos;
		acRec.acRect.right=enXPos;
		acRec.acRect.top=acYPos-2;
		acRec.acRect.bottom=acYPos+2;
		acRec.acNo=acNo++;
		acRecVec.push_back(acRec);

		//5.��ȡ������һ�������X������Ӧ��λ��
		map <int,CPoint>::iterator pLastScreen=acLastScreenMap.find(iter->objNo);
		if (pLastScreen!=acLastScreenMap.end())
		{
			paintDc->MoveTo(pLastScreen->second);
			paintDc->LineTo(stXPos,acYPos);
			this->DrawArrow(paintDc,&actionPen,pLastScreen->second,CPoint(stXPos,acYPos));
		}
		setAcLastScreenXMap(iter->objNo,CPoint(enXPos,acYPos));
	}
}


// ����ֱ�߼�ͷ
void m_GantDlg::DrawArrow(CDC *pDc,CPen* pPen,CPoint src,CPoint tar)
{
	assert(pDc!=NULL);
	assert(pPen!=NULL);

	if (src==tar)
	{
		return;
	}

	//�����������
	CPen* pOldPen=pDc->SelectObject(pPen);

	CPoint leftP,rightP;

	//����Դ�����е�������ϵ�������ͷ��������
	if (src.y<tar.y&&src.x<+tar.x)
	{
		double a=atan((double)((src.x-tar.x)/(src.y-tar.y)));
		leftP.x=tar.x+this->arrowLen*sin(a-this->arrowAlph);
		leftP.y=tar.y+this->arrowLen*cos(a-this->arrowAlph);

		rightP.x=tar.x+this->arrowLen*sin(a+this->arrowAlph);
		rightP.y=tar.y+this->arrowLen*cos(a+this->arrowAlph);
	}
	else
	{
		if (src.y>tar.y&&src.x>=tar.x)
		{
			double a=atan((double)((src.x-tar.x)/(src.y-tar.y)));
			leftP.x=tar.x-this->arrowLen*sin(a-this->arrowAlph);
			leftP.y=tar.y-this->arrowLen*cos(a-this->arrowAlph);

			rightP.x=tar.x-this->arrowLen*sin(a+this->arrowAlph);
			rightP.y=tar.y-this->arrowLen*cos(a+this->arrowAlph);
		}
		else
		{
			if (src.y>tar.y&&src.x<=tar.x)
			{
				double a=atan((double)((tar.x-src.x)/(src.y-tar.y)));
				leftP.x=tar.x+this->arrowLen*sin(a-this->arrowAlph);
				leftP.y=tar.y-this->arrowLen*cos(a-this->arrowAlph);

				rightP.x=tar.x+this->arrowLen*sin(a+this->arrowAlph);
				rightP.y=tar.y-this->arrowLen*cos(a+this->arrowAlph);
			}
			else
			{
				if (src.y<tar.y&&src.x>=tar.x)
				{
					double a=atan((double)((src.x-tar.x)/(tar.y-src.y)));
					leftP.x=tar.x-this->arrowLen*sin(a-this->arrowAlph);
					leftP.y=tar.y+this->arrowLen*cos(a-this->arrowAlph);

					rightP.x=tar.x-this->arrowLen*sin(a+this->arrowAlph);
					rightP.y=tar.y+this->arrowLen*cos(a+this->arrowAlph);
				}
			}
		}
	}

	if (src.y==tar.y)
	{
		if (src.x>tar.x)
		{
			leftP.x=tar.x-this->arrowLen*sin(90-this->arrowAlph);
			leftP.y=tar.y+this->arrowLen*cos(90-this->arrowAlph);

			rightP.x=tar.x-this->arrowLen*sin(90-this->arrowAlph);
			rightP.y=tar.y-this->arrowLen*cos(90-this->arrowAlph);
		}
		else
		{
			leftP.x=tar.x+this->arrowLen*sin(90-this->arrowAlph);
			leftP.y=tar.y+this->arrowLen*cos(90-this->arrowAlph);

			rightP.x=tar.x+this->arrowLen*sin(90-this->arrowAlph);
			rightP.y=tar.y-this->arrowLen*cos(90-this->arrowAlph);
		}
	}

	pDc->MoveTo(tar);
	pDc->LineTo(leftP);
	pDc->MoveTo(tar);
	pDc->LineTo(rightP);

	pDc->SelectObject(pOldPen);
}


void m_GantDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	this->DrawSubGant(curPageStTime,curPageStTime+singlePageTimeLen,this->showTimeUnit);
}


// ע����ʾ��Ϣ
void m_GantDlg::configToolTips(void)
{
	EnableToolTips(TRUE);
	m_ttc.Create(this);
	m_ttc.Activate(TRUE);
	CWnd *pw=GetDlgItem(IDC_STATIC_GANTGRAPH);
	m_ttc.AddTool(pw,_T("��ʾ��Ϣ����"));
}


BOOL m_GantDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_ttc.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


// ��ʼ����ϸ��Ϣ��ʾ��Ӧ�Ŀռ䲼��
void m_GantDlg::init_DetailCtrls(void)
{
	CRect dlgRect;
	GetClientRect(&dlgRect);

	//����GroupBox�ؼ�λ��
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_STATIC_ACDETAIL);

	CRect detailCtrilsRect;
	detailCtrilsRect.left=dlgRect.left;
	detailCtrilsRect.right=dlgRect.right;
	detailCtrilsRect.top=dlgRect.bottom-130;
	detailCtrilsRect.bottom=dlgRect.bottom;
	pwnd->MoveWindow(detailCtrilsRect);

	CRect CtrlRect;//���ؼ�������
	//WQ������Ϣ
	//��̬������
	pwnd=GetDlgItem(IDC_STATIC_WQTYPE);
	CtrlRect.top=detailCtrilsRect.top+20;
	CtrlRect.left=detailCtrilsRect.left+10;
	CtrlRect.bottom=CtrlRect.top+20;
	CtrlRect.right=CtrlRect.left+100;
	pwnd->MoveWindow(CtrlRect);
	//��̬�����ֶ�Ӧ��̬������Ӧ����
	pwnd=GetDlgItem(IDC_EDIT_WQTYPE);
	CtrlRect.left=CtrlRect.right+10;
	CtrlRect.right=(detailCtrilsRect.left+detailCtrilsRect.right)/2-10;
	pwnd->MoveWindow(CtrlRect);

	//λ����Ϣ����
	pwnd=GetDlgItem(IDC_STATIC_POS);
	CtrlRect.top=CtrlRect.bottom+20;
	CtrlRect.left=detailCtrilsRect.left+10;
	CtrlRect.bottom=CtrlRect.top+20;
	CtrlRect.right=CtrlRect.left+100;
	pwnd->MoveWindow(CtrlRect);
	//��̬�����ֶ�Ӧ��̬������Ӧ����
	pwnd=GetDlgItem(IDC_EDIT_POS);
	CtrlRect.left=CtrlRect.right+10;
	CtrlRect.right=(detailCtrilsRect.left+detailCtrilsRect.right)/2-10;
	pwnd->MoveWindow(CtrlRect);

	//��ʼʱ����Ϣ����
	pwnd=GetDlgItem(IDC_STATIC_STTIME);
	CtrlRect.top=detailCtrilsRect.top+20;
	CtrlRect.left=(detailCtrilsRect.left+detailCtrilsRect.right)/2+10;
	CtrlRect.bottom=CtrlRect.top+20;
	CtrlRect.right=CtrlRect.left+100;
	pwnd->MoveWindow(CtrlRect);
	//��̬�����ֶ�Ӧ��̬������Ӧ����
	pwnd=GetDlgItem(IDC_EDIT_STTIME);
	CtrlRect.left=CtrlRect.right+10;
	CtrlRect.right=detailCtrilsRect.right-10;
	pwnd->MoveWindow(CtrlRect);

	//��ֹʱ����Ϣ����
	pwnd=GetDlgItem(IDC_STATIC_ENTIME);
	CtrlRect.top=CtrlRect.bottom+20;
	CtrlRect.left=(detailCtrilsRect.left+detailCtrilsRect.right)/2+10;
	CtrlRect.bottom=CtrlRect.top+20;
	CtrlRect.right=CtrlRect.left+100;
	pwnd->MoveWindow(CtrlRect);
	//��̬�����ֶ�Ӧ��̬������Ӧ����
	pwnd=GetDlgItem(IDC_EDIT_ENTIME);
	CtrlRect.left=CtrlRect.right+10;
	CtrlRect.right=detailCtrilsRect.right-10;
	pwnd->MoveWindow(CtrlRect);

	//��ϸ������Ϣ����
	pwnd=GetDlgItem(IDC_STATIC_DES);
	CtrlRect.top=CtrlRect.bottom+20;
	CtrlRect.left=detailCtrilsRect.left+10;
	CtrlRect.bottom=CtrlRect.top+20;
	CtrlRect.right=CtrlRect.left+100;
	pwnd->MoveWindow(CtrlRect);
	//��̬�����ֶ�Ӧ��̬������Ӧ����
	pwnd=GetDlgItem(IDC_EDIT_DES);
	CtrlRect.left=CtrlRect.right+10;
	CtrlRect.right=detailCtrilsRect.right-10;
	pwnd->MoveWindow(CtrlRect);
}


void m_GantDlg::initCtrls(void)
{
	CWnd *pWnd;//�ؼ������ʱ����
	//���ư�ť
	/*pWnd=this->gantChildDlg.GetDlgItem(IDC_BUTTON_DRAWGANT);
	pWnd->SetWindowPos(NULL,rect.right-100,rect.bottom-100,0,0,SWP_NOZORDER|SWP_NOSIZE);*/

	CRect rect;
	GetClientRect(&rect);

	//����gantͼ��λ��
	pWnd=GetDlgItem(IDC_STATIC_GANTGRAPH);
	CRect gantRect;
	gantRect.top=rect.top;
	gantRect.left=rect.left;
	gantRect.right=rect.right-40;
	gantRect.bottom=rect.bottom-150;
	pWnd->MoveWindow(gantRect);

	//����ˮƽSCROLLBARλ��
	pWnd=GetDlgItem(IDC_SCROLLBAR_HORZ);
	CRect hScrollRect;
	hScrollRect.top=gantRect.bottom;
	hScrollRect.left=gantRect.left+100;
	hScrollRect.right=gantRect.right;
	hScrollRect.bottom=gantRect.bottom+20;
	pWnd->MoveWindow(hScrollRect);

	//���ô�ֱSCROLLBARλ��
	pWnd=GetDlgItem(IDC_SCROLLBAR_VER);
	CRect vScrollRect;
	vScrollRect.top=gantRect.top;
	vScrollRect.left=gantRect.right;
	vScrollRect.right=gantRect.right+20;
	vScrollRect.bottom=gantRect.bottom;
	pWnd->MoveWindow(vScrollRect);

	//�����������������϶���Χ
	this->m_hScrollBar.SetScrollRange(0,titalTime);
	this->m_vSrcollBar.SetScrollRange(0,100);

	this->init_DetailCtrls();
}


void m_GantDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (PtInRect(painRect,point))
	{
		int acNo=this->getPtAcNo(point);
		if (acNo!=-1)
		{
			HCURSOR hCur=LoadCursor(NULL,IDC_HAND);
			::SetCursor(hCur);
			this->wqType=actionVec[acNo].actionObj;
			this->stTime=actionVec[acNo].startTime;
			this->enTime=actionVec[acNo].endTime;
			this->description=actionVec[acNo].actionDes;
			this->posInfo=actionVec[acNo].pos;
			UpdateData(FALSE);
		}
		else
		{
			this->wqType=_T("�޶�Ӧ��Ϣ");
			this->stTime=0;
			this->enTime=0;
			this->description=_T("�޶�Ӧ��Ϣ");
			this->posInfo=_T("�޶�Ӧ��Ϣ");
			UpdateData(FALSE);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


// ��ȡ��굱ǰλ�õĶ�����actionVec�еı��
int m_GantDlg::getPtAcNo(CPoint mousePt)
{
	vector <actionRect>::iterator iter=acRecVec.begin();
	for (;iter<acRecVec.end();iter++)
	{
		if (PtInRect(iter->acRect,mousePt))
		{
			return iter->acNo;
		}
	}
	return -1;
}


// �������϶������µ�ǰGantͼ
void m_GantDlg::UpdateGant(void)
{
	CDC *paintDc=this->gantGraph.GetDC();
	if (paintDc==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("�޷���ȡ��ͼ���ھ��"));
		return;
	}
	/*CBrush grayBrash(COLOR_WINDOW);
	paintDc->FillRect(painRect,&grayBrash);*/
	InvalidateRect(painRect);
	PostMessage(WM_PAINT,NULL,NULL);
}
