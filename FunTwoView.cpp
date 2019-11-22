// FunTwoView.cpp : 实现文件
//

#include "stdafx.h"

#include "MDIDEMO.h"
#include "MainFrm.h"
#include "FunTwoView.h"


// CFunTwoView

IMPLEMENT_DYNCREATE(CFunTwoView, CFormView)

CFunTwoView::CFunTwoView()
	: CFormView(IDD_FUNTWOVIEW)
{
	
}

CFunTwoView::~CFunTwoView()
{
}

void CFunTwoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFunTwoView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CFunTwoView::OnBnClickedButton1)
	ON_MESSAGE(WM_SOCKET, &CFunTwoView::socketmessage)
	ON_BN_CLICKED(IDC_BUTTON2, &CFunTwoView::OnBnClickedButton2)
END_MESSAGE_MAP()


// CFunTwoView 诊断

#ifdef _DEBUG
void CFunTwoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFunTwoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFunTwoView 消息处理程序


void CFunTwoView::OnBnClickedButton1()//给业务一发送消息
{
	CString str = _T("123456");
	//::SendMessage(((CMainFrame*)AfxGetMainWnd())->Frame_one->GetSafeHwnd(), WM_TEXT,(WPARAM)&str, NULL);
	//::SendMessage(((CMainFrame*)AfxGetMainWnd())->Frame_one->GetSafeHwnd(), WM_CLOSE, (WPARAM)&str, NULL);
    //int a =	::PostMessage(((CMainFrame*)AfxGetMainWnd())->Frame_one->GetActiveView()->GetSafeHwnd(), WM_TEXT, (WPARAM)&str, NULL);
	
    const char *p= { "123456" };
	std::string a = get_stringfromchar(p);
	char *q = get_charfromstring(a);
	const char *w = get_charfromstring(a);
	wchar_t *q1 = char_to_wchar(q);
	char *q2 = wchar_to_char(q1);

	CString str1 = string_to_cstring(&a);
	std::string b = cstring_to_string(&str1);

   const char *q8= cstring_to_char(&str1);
   CString str3 = char_to_cstring((char*)q8);

    delete[]q8;
	delete[]q1;
	delete[]q2;

	//CString ipaddress = _T("192.168.1.116");
	//server.m_connect(6667, NULL, Server);
	
//	client.Set_HWND(this->GetSafeHwnd());
//	client.m_connect(6667, (LPCTSTR)ipaddress, Client);
	m_port.OpenComm(1);
}

LRESULT CFunTwoView::socketmessage(WPARAM w, LPARAM l)
{
	SOCKET s = (SOCKET)w;
	int a = WSAGETSELECTEVENT(l);
	CString str;
	char p[3] = { 0 };
	switch (WSAGETSELECTEVENT(l))
	{
	case FD_READ:		
		client.LRecv( p,2);		
		str.Format(_T("接受到信息:%S"), p);
		MessageBox(str);
		break;
	case FD_WRITE:
		MessageBox(_T("连接成功！"));
		break;
	case FD_ACCEPT:
		MessageBox(_T("accept"));
		break;
	case FD_CLOSE:
		MessageBox(_T("close"));
		break;
	case FD_CONNECT:
		MessageBox(_T("FD_CONNECT"));
		break;
	}
	return 0;
}


void CFunTwoView::OnBnClickedButton2()
{
	char p[] = { "hello" };
	int a = sizeof(p);
	m_port.WriteComm(p,sizeof(p));
}
