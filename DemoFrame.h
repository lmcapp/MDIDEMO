#pragma once


// CDemoFrame 框架

class CDemoFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDemoFrame)
public:
	CDemoFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDemoFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


