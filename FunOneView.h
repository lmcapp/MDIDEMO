#pragma once


// CFunOneView ��ͼ

class CFunOneView : public CView
{
	DECLARE_DYNCREATE(CFunOneView)

protected:
	CFunOneView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFunOneView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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


