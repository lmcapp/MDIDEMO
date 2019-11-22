
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MDIDEMO.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FUNC_ONE, &CMainFrame::OnFuncOne)
	ON_COMMAND(ID_FUNC_TWO, &CMainFrame::OnFuncTwo)
	ON_COMMAND(ID_tile, &CMainFrame::Ontile)
	ON_COMMAND(ID_case, &CMainFrame::Oncase)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	Frame_one = NULL;
	Frame_two = NULL;

	oneview = NULL;
	twoview = NULL;
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (Frame_two != NULL)
	{
		Frame_two->MDIActivate();
	}
	else
	{
		Frame_two = new CDemoFrame();
		CCreateContext context;
		context.m_pNewViewClass = RUNTIME_CLASS(CFunTwoView);
		Frame_two->LoadFrame(IDR_MAINFRAME, WS_MAXIMIZE | WS_OVERLAPPEDWINDOW, this, &context);
		Frame_two->SetWindowTextW(_T("业务逻辑二"));
		Frame_two->ShowWindow(SW_SHOWMAXIMIZED);
		Frame_two->InitialUpdateFrame(NULL, true);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnFuncOne()
{
	if (Frame_one!= NULL)
	{
		Frame_one->MDIActivate();
	}
	else
	{
		Frame_one = new CDemoFrame();
		CCreateContext context;
		context.m_pNewViewClass = RUNTIME_CLASS(CFunOneView);
		Frame_one->LoadFrame(IDR_MAINFRAME, WS_MAXIMIZE | WS_OVERLAPPEDWINDOW, this, &context);
		Frame_one->SetWindowTextW(_T("业务逻辑一"));
		Frame_one->ShowWindow(SW_SHOWMAXIMIZED);
		Frame_one->InitialUpdateFrame(NULL, true);
	}
}


void CMainFrame::OnFuncTwo()
{
	if (Frame_two != NULL)
	{
		Frame_two->MDIActivate();
	}
	else
	{
		Frame_two = new CDemoFrame();
		CCreateContext context;
		context.m_pNewViewClass = RUNTIME_CLASS(CFunTwoView);
		Frame_two->LoadFrame(IDR_MAINFRAME, WS_MAXIMIZE | WS_OVERLAPPEDWINDOW, this, &context);
		Frame_two->SetWindowTextW(_T("业务逻辑二"));
		Frame_two->ShowWindow(SW_SHOWMAXIMIZED);
		Frame_two->InitialUpdateFrame(NULL, true);
	}
}


void CMainFrame::Ontile()
{
	MDITile();
}


void CMainFrame::Oncase()
{
	MDICascade();
}
