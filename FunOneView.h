#pragma once


// CFunOneView 视图

class CFunOneView : public CView
{
	DECLARE_DYNCREATE(CFunOneView)

protected:
	CFunOneView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFunOneView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	afx_msg LRESULT test(WPARAM w, LPARAM l);
};


