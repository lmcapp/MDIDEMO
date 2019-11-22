
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	Frame_one = NULL;
	Frame_two = NULL;

	oneview = NULL;
	twoview = NULL;
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
		Frame_two->SetWindowTextW(_T("ҵ���߼���"));
		Frame_two->ShowWindow(SW_SHOWMAXIMIZED);
		Frame_two->InitialUpdateFrame(NULL, true);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



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
		Frame_one->SetWindowTextW(_T("ҵ���߼�һ"));
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
		Frame_two->SetWindowTextW(_T("ҵ���߼���"));
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
