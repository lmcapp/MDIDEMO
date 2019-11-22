
// MDIDEMO.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MDIDEMO.h"
#include "MainFrm.h"

#include "ChildFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIDEMOApp

BEGIN_MESSAGE_MAP(CMDIDEMOApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMDIDEMOApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CMDIDEMOApp::OnFileNew)
	ON_COMMAND(ID_FILE_CLOSE, &CMDIDEMOApp::OnFileClose)
	ON_COMMAND(ID_tuichu, &CMDIDEMOApp::Ontuichu)
END_MESSAGE_MAP()


// CMDIDEMOApp ����

CMDIDEMOApp::CMDIDEMOApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MDIDEMO.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMDIDEMOApp ����

CMDIDEMOApp theApp;


// CMDIDEMOApp ��ʼ��

BOOL CMDIDEMOApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ������ MDI ��ܴ���
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	// ��ͼ���ع��� MDI �˵��Ϳ�ݼ���
	//TODO: ��Ӹ��ӳ�Ա�����������ض�
	//	Ӧ�ó��������Ҫ�ĸ��Ӳ˵����͵ĵ���
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MDIDEMOTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_MDIDEMOTYPE));
	m_hopmenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MDIDEMOTYPE));
	m_hinitmenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));



	// �������ѳ�ʼ���������ʾ����������и���
	pFrame->SetWindowTextW(_T("δ��¼"));
	m_nCmdShow = SW_SHOWMAXIMIZED;
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	return TRUE;
}

int CMDIDEMOApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CMDIDEMOApp ��Ϣ�������

void CMDIDEMOApp::OnFileNew() 
{
	//CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	//// �����µ� MDI �Ӵ���
	//pFrame->CreateNewChild(
	//	RUNTIME_CLASS(CChildFrame), IDR_MDIDEMOTYPE, m_hMDIMenu, m_hMDIAccel);

	SetMenu(AfxGetApp()->m_pMainWnd->m_hWnd, m_hopmenu);
	AfxGetApp()->m_pMainWnd->SetWindowText(_T(" �ѵ�¼ "));
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMDIDEMOApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMDIDEMOApp ��Ϣ�������





void CMDIDEMOApp::OnFileClose()
{
	
}


void CMDIDEMOApp::Ontuichu()
{
	if (((CMainFrame *)AfxGetMainWnd())->Frame_one!=NULL)
	{
		((CMainFrame *)AfxGetMainWnd())->Frame_one->SendMessage(WM_CLOSE);
		((CMainFrame *)AfxGetMainWnd())->Frame_one = NULL;
	}

	if (((CMainFrame *)AfxGetMainWnd())->Frame_two != NULL)
	{
		((CMainFrame *)AfxGetMainWnd())->Frame_two->SendMessage(WM_CLOSE);
		((CMainFrame *)AfxGetMainWnd())->Frame_two = NULL;
	}

	SetMenu(AfxGetApp()->m_pMainWnd->m_hWnd, m_hinitmenu);
	AfxGetApp()->m_pMainWnd->SetWindowTextW(_T("δ��¼"));
}
