// FunOneView.cpp : 实现文件
//

#include "stdafx.h"
#include "MDIDEMO.h"
#include "MainFrm.h"
#include "FunOneView.h"


// CFunOneView

IMPLEMENT_DYNCREATE(CFunOneView, CView)

CFunOneView::CFunOneView()
{

}

CFunOneView::~CFunOneView()
{
}

BEGIN_MESSAGE_MAP(CFunOneView, CView)
	ON_MESSAGE(WM_TEXT, &CFunOneView::test)
END_MESSAGE_MAP()


// CFunOneView 绘图

void CFunOneView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CFunOneView 诊断

#ifdef _DEBUG
void CFunOneView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CFunOneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFunOneView 消息处理程序


BOOL CFunOneView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message==WM_TEXT)
	{
		MessageBox(_T("PreTranslateMessage"));
	}


	return CView::PreTranslateMessage(pMsg);
}


BOOL CFunOneView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (message == WM_TEXT)
	{
		CString str = _T("onwndmsg");

		MessageBox(str);
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}
LRESULT CFunOneView::test(WPARAM w, LPARAM l)
{
	CString *str = (CString *)w;

	MessageBox(*str);
	return 10;
}