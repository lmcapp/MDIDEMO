
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "DemoFrame.h"
#include "FunOneView.h"
#include "FunTwoView.h"

#define  WM_TEXT WM_USER+1000
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:
	CDemoFrame *Frame_one;
	CDemoFrame *Frame_two;

	CFunOneView *oneview;
	CFunTwoView *twoview;
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFuncOne();
	afx_msg void OnFuncTwo();
	afx_msg void Ontile();
	afx_msg void Oncase();
};


