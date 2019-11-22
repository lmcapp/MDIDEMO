
// MainFrm.h : CMainFrame 类的接口
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

// 特性
public:

// 操作
public:
	CDemoFrame *Frame_one;
	CDemoFrame *Frame_two;

	CFunOneView *oneview;
	CFunTwoView *twoview;
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFuncOne();
	afx_msg void OnFuncTwo();
	afx_msg void Ontile();
	afx_msg void Oncase();
};


