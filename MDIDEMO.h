
// MDIDEMO.h : MDIDEMO 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

// CMDIDEMOApp:
// 有关此类的实现，请参阅 MDIDEMO.cpp
//

class CMDIDEMOApp : public CWinApp
{
public:
	CMDIDEMOApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

	HMENU m_hopmenu;
	HMENU m_hinitmenu;


public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnFileClose();
	afx_msg void Ontuichu();
};

extern CMDIDEMOApp theApp;
