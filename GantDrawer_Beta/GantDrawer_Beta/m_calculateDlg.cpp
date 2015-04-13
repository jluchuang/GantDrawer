// m_calculateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GantDrawer_Beta.h"
#include "m_calculateDlg.h"
#include "afxdialogex.h"



// m_calculateDlg 对话框

IMPLEMENT_DYNAMIC(m_calculateDlg, CDialogEx)

m_calculateDlg::m_calculateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(m_calculateDlg::IDD, pParent)
{
    this->seqS=NULL;
}

m_calculateDlg::~m_calculateDlg()
{
}

void m_calculateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_calculateDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &m_calculateDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// m_calculateDlg 消息处理程序


void m_calculateDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    int a[]={1,2,3,4,5,6,7,8,9,10};
    vector <int> seed(a,a+10);
    this->seqS=new SequenceSet(seed,5,10);
    cout<<(*seqS)<<endl;
    cout<<sizeof(char)<<endl;
}
