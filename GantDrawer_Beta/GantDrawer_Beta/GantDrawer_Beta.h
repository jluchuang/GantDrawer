
// GantDrawer_Beta.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGantDrawer_BetaApp:
// �йش����ʵ�֣������ GantDrawer_Beta.cpp
//

class CGantDrawer_BetaApp : public CWinApp
{
public:
	CGantDrawer_BetaApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGantDrawer_BetaApp theApp;