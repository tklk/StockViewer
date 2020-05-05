
// StockViewer_0313130.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "StockViewer_0313130.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "StockViewer_0313130Doc.h"
#include "StockViewer_0313130View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStockViewer_0313130App

BEGIN_MESSAGE_MAP(CStockViewer_0313130App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CStockViewer_0313130App::OnAppAbout)
	// �̾ڤ��R�O���з��ɮ�
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// �зǦC�L�]�w�R�O
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CStockViewer_0313130App �غc

CStockViewer_0313130App::CStockViewer_0313130App()
{
	// �䴩���s�Ұʺ޲z��
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �p�G���ε{���O�ϥ� Common Language Runtime �䴩 (/clr) �ظm��: 
	//     1) �n�ϭ��s�Ұʺ޲z���䴩���`�B�@�ݭn�o���B�~�]�w�C
	//     2) �b�M�פ������N�Ѧҥ[�J�� System.Windows.Forms �~��i��ظm�C
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  �H�ߤ@�� ID �r����N�U�������ε{�� ID �r��; ��ĳ��
	// �r��榡�� CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("StockViewer_0313130.AppID.NoVersion"));

	// TODO:  �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}

// �Ȧ����@�� CStockViewer_0313130App ����

CStockViewer_0313130App theApp;


// CStockViewer_0313130App ��l�]�w

BOOL CStockViewer_0313130App::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��l�� OLE �{���w
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// �ݭn�� AfxInitRichEdit2() �~��ϥ� RichEdit ���	
	// AfxInitRichEdit2();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO:  �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));
	LoadStdProfileSettings(4);  // ���J�з� INI �ɿﶵ (�]�t MRU)


	// �n�����ε{�������d���C���d���t�d�b���B
	// �ج[�����P�˵����i��s��
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_StockViewer_031TYPE,
		RUNTIME_CLASS(CStockViewer_0313130Doc),
		RUNTIME_CLASS(CChildFrame), // �ۭq MDI �l�ج[
		RUNTIME_CLASS(CStockViewer_0313130View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �إߥD MDI �ج[����
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// �u���b MDI ���ε{��������m�r���ɡA�~�I�s DragAcceptFiles
	// �o�|�ߧY�o�ͦb�]�w m_pMainWnd ����
	// �ҥΩ��}��
	m_pMainWnd->DragAcceptFiles();

	// ��R�з� Shell �R�O�BDDE�B�ɮ׶}�����ɪ��R�O�C
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �ҥ� DDE ����}��
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// �b�R�O�C�����w�������R�O�C�p�G�w�ϥ� 
	// /RegServer�B/Register�B/Unregserver �� /Unregister �Ұ����ε{���A�N�Ǧ^ FALSE�C
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �w�g��l�]�w�D�����A�ҥH��ܨç�s�ӵ���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CStockViewer_0313130App::ExitInstance()
{
	// TODO:  �B�z��L�z�w�g�[�J���귽
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CStockViewer_0313130App �T���B�z�`��


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//New
class CHowToUse : public CDialogEx
{
public:
	CHowToUse();

	// ��ܤ�����
	enum { IDD = IDD_stockinfo1 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAboutbox();
	afx_msg void OnBnClickedOk();
};

CHowToUse::CHowToUse() : CDialogEx(CHowToUse::IDD)
{
}

void CHowToUse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//New
class CBrowseData : public CDialogEx
{
public:
	CBrowseData();

	// ��ܤ�����
	enum { IDD = IDD_stockinfo2 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedstockinfo1();
	afx_msg void OnBnClickedOk();
};

CBrowseData::CBrowseData() : CDialogEx(CBrowseData::IDD)
{
}

void CBrowseData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//New
class CTechindex : public CDialogEx
{
public:
	CTechindex();

	// ��ܤ�����
	enum { IDD = IDD_stockinfo3 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedstockinfo2();
	afx_msg void OnBnClickedOk();
};

CTechindex::CTechindex() : CDialogEx(CTechindex::IDD)
{
}

void CTechindex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//New
class CDayWeekMonth : public CDialogEx
{
public:
	CDayWeekMonth();

	// ��ܤ�����
	enum { IDD = IDD_stockinfo4 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedstockinfo2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedstockinfo3();
};

CDayWeekMonth::CDayWeekMonth() : CDialogEx(CDayWeekMonth::IDD)
{
}

void CDayWeekMonth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CHowToUse, CDialogEx)
	ON_BN_CLICKED(IDD_ABOUTBOX, &CHowToUse::OnBnClickedAboutbox)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CBrowseData, CDialogEx)
	ON_BN_CLICKED(IDD_stockinfo1, &CBrowseData::OnBnClickedstockinfo1)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CTechindex, CDialogEx)
	ON_BN_CLICKED(IDD_stockinfo2, &CTechindex::OnBnClickedstockinfo2)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CDayWeekMonth, CDialogEx)
	ON_BN_CLICKED(IDD_stockinfo3, &CDayWeekMonth::OnBnClickedstockinfo3)
END_MESSAGE_MAP()
// �����ܤ�������ε{���R�O
void CStockViewer_0313130App::OnAppAbout()
{
	// About Box
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	// Open file stockinfo1
	CHowToUse aboutDlg2;
	aboutDlg2.DoModal();
	// Browse data stockinfo2
	CBrowseData aboutDlg3;
	aboutDlg3.DoModal();
	// Show techindex stockinfo3
	CTechindex aboutDlg4;
	aboutDlg4.DoModal();
	// Change Day Week Month
	CDayWeekMonth aboutDlg5;
	aboutDlg5.DoModal();
}

// CStockViewer_0313130App �T���B�z�`��



void CHowToUse::OnBnClickedAboutbox()
{
	// TODO:  �b���[�J����i���B�z�`���{���X
	EndDialog(false);
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	//New
	CHowToUse aboutDlg2;
	aboutDlg2.DoModal();
}


void CBrowseData::OnBnClickedstockinfo1()
{
	// TODO:  �b���[�J����i���B�z�`���{���X
	EndDialog(false);
	//New
	CHowToUse aboutDlg2;
	aboutDlg2.DoModal();
	//New
	CBrowseData aboutDlg3;
	aboutDlg3.DoModal();
}


void CTechindex::OnBnClickedstockinfo2()
{
	// TODO:  �b���[�J����i���B�z�`���{���X
	EndDialog(false);
	//New
	CBrowseData aboutDlg3;
	aboutDlg3.DoModal();
	//New
	CTechindex aboutDlg4;
	aboutDlg4.DoModal();
}


void CDayWeekMonth::OnBnClickedstockinfo3()
{
	// TODO:  �b���[�J����i���B�z�`���{���X
	EndDialog(false);
	//New
	CTechindex aboutDlg4;
	aboutDlg4.DoModal();
	//New
	CDayWeekMonth aboutDlg5;
	aboutDlg5.DoModal();
}
