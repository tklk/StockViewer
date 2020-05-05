
// StockViewer_0313130.cpp : 定義應用程式的類別行為。
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
	// 依據文件命令的標準檔案
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 標準列印設定命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CStockViewer_0313130App 建構

CStockViewer_0313130App::CStockViewer_0313130App()
{
	// 支援重新啟動管理員
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果應用程式是使用 Common Language Runtime 支援 (/clr) 建置的: 
	//     1) 要使重新啟動管理員支援正常運作需要這個額外設定。
	//     2) 在專案中必須將參考加入至 System.Windows.Forms 才能進行建置。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  以唯一的 ID 字串取代下面的應用程式 ID 字串; 建議的
	// 字串格式為 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("StockViewer_0313130.AppID.NoVersion"));

	// TODO:  在此加入建構程式碼，
	// 將所有重要的初始設定加入 InitInstance 中
}

// 僅有的一個 CStockViewer_0313130App 物件

CStockViewer_0313130App theApp;


// CStockViewer_0313130App 初始設定

BOOL CStockViewer_0313130App::InitInstance()
{
	// 假如應用程式資訊清單指定使用 ComCtl32.dll 6 (含) 以後版本，
	// 來啟動視覺化樣式，在 Windows XP 上，則需要 InitCommonControls()。
	// 否則任何視窗的建立都將失敗。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 設定要包含所有您想要用於應用程式中的
	// 通用控制項類別。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 程式庫
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 需要有 AfxInitRichEdit2() 才能使用 RichEdit 控制項	
	// AfxInitRichEdit2();

	// 標準初始設定
	// 如果您不使用這些功能並且想減少
	// 最後完成的可執行檔大小，您可以
	// 從下列程式碼移除不需要的初始化常式，
	// 變更儲存設定值的登錄機碼
	// TODO:  您應該適度修改此字串
	// (例如，公司名稱或組織名稱)
	SetRegistryKey(_T("本機 AppWizard 所產生的應用程式"));
	LoadStdProfileSettings(4);  // 載入標準 INI 檔選項 (包含 MRU)


	// 登錄應用程式的文件範本。文件範本負責在文件、
	// 框架視窗與檢視間進行連接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_StockViewer_031TYPE,
		RUNTIME_CLASS(CStockViewer_0313130Doc),
		RUNTIME_CLASS(CChildFrame), // 自訂 MDI 子框架
		RUNTIME_CLASS(CStockViewer_0313130View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 建立主 MDI 框架視窗
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// 只有在 MDI 應用程式中有後置字元時，才呼叫 DragAcceptFiles
	// 這會立即發生在設定 m_pMainWnd 之後
	// 啟用拖放開啟
	m_pMainWnd->DragAcceptFiles();

	// 剖析標準 Shell 命令、DDE、檔案開啟舊檔的命令列
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 啟用 DDE 執行開啟
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 在命令列中指定的分派命令。如果已使用 
	// /RegServer、/Register、/Unregserver 或 /Unregister 啟動應用程式，將傳回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 已經初始設定主視窗，所以顯示並更新該視窗
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CStockViewer_0313130App::ExitInstance()
{
	// TODO:  處理其他您已經加入的資源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CStockViewer_0313130App 訊息處理常式


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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

	// 對話方塊資料
	enum { IDD = IDD_stockinfo1 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
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

	// 對話方塊資料
	enum { IDD = IDD_stockinfo2 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
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

	// 對話方塊資料
	enum { IDD = IDD_stockinfo3 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
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

	// 對話方塊資料
	enum { IDD = IDD_stockinfo4 }; //IDD_stockinfo (Dialog)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
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
// 執行對話方塊的應用程式命令
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

// CStockViewer_0313130App 訊息處理常式



void CHowToUse::OnBnClickedAboutbox()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	EndDialog(false);
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	//New
	CHowToUse aboutDlg2;
	aboutDlg2.DoModal();
}


void CBrowseData::OnBnClickedstockinfo1()
{
	// TODO:  在此加入控制項告知處理常式程式碼
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
	// TODO:  在此加入控制項告知處理常式程式碼
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
	// TODO:  在此加入控制項告知處理常式程式碼
	EndDialog(false);
	//New
	CTechindex aboutDlg4;
	aboutDlg4.DoModal();
	//New
	CDayWeekMonth aboutDlg5;
	aboutDlg5.DoModal();
}
