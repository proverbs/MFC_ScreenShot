
// MFC_ScreenShot.h : MFC_ScreenShot Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFC_ScreenShotApp:
// �йش����ʵ�֣������ MFC_ScreenShot.cpp
//

class CMFC_ScreenShotApp : public CWinAppEx
{
public:
	CMFC_ScreenShotApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_ScreenShotApp theApp;
