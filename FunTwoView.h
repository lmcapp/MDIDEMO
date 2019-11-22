#pragma once



#include "LMFC.h"
// CFunTwoView ������ͼ
using namespace LChangeValueType;
using namespace LSocket;
using namespace LCOMPORT;
using LSocket::MySocket;
using LCOMPORT::MyComPort;

class CFunTwoView : public CFormView
{
	DECLARE_DYNCREATE(CFunTwoView)

protected:
	CFunTwoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFunTwoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FUNTWOVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//---------------socket_test


	LSocket::MySocket server;
	LSocket::MySocket client;
	MyComPort m_port;
	//-------------socket xiaoxi
	afx_msg LRESULT socketmessage(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedButton2();
};


