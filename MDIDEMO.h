
// MDIDEMO.h : MDIDEMO Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

// CMDIDEMOApp:
// �йش����ʵ�֣������ MDIDEMO.cpp
//

class CMDIDEMOApp : public CWinApp
{
public:
	CMDIDEMOApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
