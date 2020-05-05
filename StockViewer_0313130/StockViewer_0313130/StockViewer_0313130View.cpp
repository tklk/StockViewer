
// StockViewer_0313130View.cpp : CStockViewer_0313130View 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "StockViewer_0313130.h"
#endif

#include "StockViewer_0313130Doc.h"
#include "StockViewer_0313130View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStockViewer_0313130View

IMPLEMENT_DYNCREATE(CStockViewer_0313130View, CView)

BEGIN_MESSAGE_MAP(CStockViewer_0313130View, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Previous, &CStockViewer_0313130View::OnPrevious)
	ON_COMMAND(ID_Next, &CStockViewer_0313130View::OnNext)
	ON_COMMAND(ID_First, &CStockViewer_0313130View::OnFirst)
	ON_COMMAND(ID_Last, &CStockViewer_0313130View::OnLast)
	ON_UPDATE_COMMAND_UI(ID_Previous, &CStockViewer_0313130View::OnUpdatePrevious)
	ON_UPDATE_COMMAND_UI(ID_Next, &CStockViewer_0313130View::OnUpdateNext)
	ON_UPDATE_COMMAND_UI(ID_First, &CStockViewer_0313130View::OnUpdateFirst)
	ON_UPDATE_COMMAND_UI(ID_Last, &CStockViewer_0313130View::OnUpdateLast)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_None, &CStockViewer_0313130View::OnNone)
	ON_COMMAND(ID_KD, &CStockViewer_0313130View::OnKd)
	ON_UPDATE_COMMAND_UI(ID_None, &CStockViewer_0313130View::OnUpdateNone)
	ON_UPDATE_COMMAND_UI(ID_KD, &CStockViewer_0313130View::OnUpdateKd)
	ON_COMMAND(ID_MACD, &CStockViewer_0313130View::OnMacd)
	ON_UPDATE_COMMAND_UI(ID_MACD, &CStockViewer_0313130View::OnUpdateMacd)
	ON_COMMAND(ID_Day, &CStockViewer_0313130View::OnDay)
	ON_COMMAND(ID_Week, &CStockViewer_0313130View::OnWeek)
	ON_COMMAND(ID_Month, &CStockViewer_0313130View::OnMonth)
	ON_UPDATE_COMMAND_UI(ID_Day, &CStockViewer_0313130View::OnUpdateDay)
	ON_UPDATE_COMMAND_UI(ID_Week, &CStockViewer_0313130View::OnUpdateWeek)
	ON_UPDATE_COMMAND_UI(ID_Month, &CStockViewer_0313130View::OnUpdateMonth)
	ON_COMMAND(ID_White, &CStockViewer_0313130View::OnWhite)
	ON_COMMAND(ID_Black, &CStockViewer_0313130View::OnBlack)
	ON_UPDATE_COMMAND_UI(ID_White, &CStockViewer_0313130View::OnUpdateWhite)
	ON_UPDATE_COMMAND_UI(ID_Black, &CStockViewer_0313130View::OnUpdateBlack)
END_MESSAGE_MAP()

// CStockViewer_0313130View 建構/解構

CStockViewer_0313130View::CStockViewer_0313130View()
{
	// TODO:  在此加入建構程式碼
	shift = 0;
	techindex = 0;
	period = 0;
	pt = NULL; //pt = -1;
	pt2 = NULL;
	ptperiod = NULL;
	currentshift = NULL;
	numDWM = NULL;
	color = 1;
}

CStockViewer_0313130View::~CStockViewer_0313130View()
{
}

BOOL CStockViewer_0313130View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CStockViewer_0313130View 描繪

void CStockViewer_0313130View::OnDraw(CDC* pDC)
{
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int cshift, cdraw1, cdraw2;
	if (!pDoc)
		return;
		
	CRect rect1;
	GetClientRect(rect1); // 視窗大小
	int H = rect1.Height();
	int W = rect1.Width();
	
	if (period == 0)
	{
		numDWM = pDoc->data.num;
	}
	else if (period == 1)
	{
		if (pDoc->data.num % 5 != 0)
			numDWM = pDoc->data.num / 5 + 1;
		else
			numDWM = pDoc->data.num / 5;
	}
	else
	{
		if (pDoc->data.num % 20 != 0)
			numDWM = pDoc->data.num / 20 + 1;
		else
			numDWM = pDoc->data.num / 20;
	}
	if (shift > numDWM - (W - 45) / 10)
	{
		shift = numDWM - (W - 45) / 10;
	}
	/*
	if (shift > pDoc->data.num - (W - 45) / 10) //  舊視窗可顯示的資料量 < 新視窗可顯示的資料量
	{
		shift = pDoc->data.num - (W - 45) / 10; // 新視窗 shift複寫為 新視窗可顯示的資料量
	}
	*/
	pDoc->data.Draw(pDC, H, W, shift, pt2, techindex, period, color); // 畫圖

	// TODO:  在此加入原生資料的描繪程式碼
}


// CStockViewer_0313130View 列印

BOOL CStockViewer_0313130View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CStockViewer_0313130View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印前額外的初始設定
}

void CStockViewer_0313130View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印後的清除程式碼
}


// CStockViewer_0313130View 診斷

#ifdef _DEBUG
void CStockViewer_0313130View::AssertValid() const
{
	CView::AssertValid();
}

void CStockViewer_0313130View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockViewer_0313130Doc* CStockViewer_0313130View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockViewer_0313130Doc)));
	return (CStockViewer_0313130Doc*)m_pDocument;
}
#endif //_DEBUG


// CStockViewer_0313130View 訊息處理常式


void CStockViewer_0313130View::OnPrevious()
{
	// TODO:  在此加入您的命令處理常式程式碼
	CRect rect1;
	GetClientRect(rect1); // 視窗大小
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	shift++;
	
	if (period == 0)
	{
		numDWM = pDoc->data.num;
	}
	else if (period == 1)
	{
		if (pDoc->data.num % 5 != 0)
			numDWM = pDoc->data.num / 5 + 1;
		else
			numDWM = pDoc->data.num / 5;
	}
	else
	{
		if (pDoc->data.num % 20 != 0)
			numDWM = pDoc->data.num / 20 + 1;
		else
			numDWM = pDoc->data.num / 20;
	}
	if (shift > numDWM - (W - 45) / 10)
	{
		shift = numDWM - (W - 45) / 10;
	}
	/*
	if (shift > pDoc->data.num - (W - 45) / 10)
		shift = pDoc->data.num - (W - 45) / 10;
	*/
	Invalidate(false); // 04/27 新增 false
}


void CStockViewer_0313130View::OnNext()
{
	// TODO:  在此加入您的命令處理常式程式碼
	// 舊版本
	
	shift--;
	
	if (shift < 0)
		shift = 0;
	Invalidate(false); // 04/27 新增 false
}


void CStockViewer_0313130View::OnFirst()
{
	// TODO:  在此加入您的命令處理常式程式碼

	CRect rect1;
	GetClientRect(rect1); // 視窗大小 //GetUpdateRect(rect1);
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (period == 0)
	{
		numDWM = pDoc->data.num;
	}
	else if (period == 1)
	{
		if (pDoc->data.num % 5 != 0)
			numDWM = pDoc->data.num / 5 + 1;
		else
			numDWM = pDoc->data.num / 5;
	}
	else
	{
		if (pDoc->data.num % 20 != 0)
			numDWM = pDoc->data.num / 20 + 1;
		else
			numDWM = pDoc->data.num / 20;
	}
	shift = numDWM - (W - 45) / 10;
	//shift = pDoc->data.num - (W - 45) / 10;
	Invalidate(false); // 04/27 新增 false
}


void CStockViewer_0313130View::OnLast()
{
	// TODO:  在此加入您的命令處理常式程式碼
	shift = 0;
	Invalidate(false); // 04/27 新增 false
}


void CStockViewer_0313130View::OnUpdatePrevious(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	CRect rect1;
	GetClientRect(rect1); // 視窗大小
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (period == 0)
	{
		numDWM = pDoc->data.num;
	}
	else if (period == 1)
	{
		if (pDoc->data.num % 5 != 0)
			numDWM = pDoc->data.num / 5 + 1;
		else
			numDWM = pDoc->data.num / 5;
	}
	else
	{
		if (pDoc->data.num % 20 != 0)
			numDWM = pDoc->data.num / 20 + 1;
		else
			numDWM = pDoc->data.num / 20;
	}
	pCmdUI->Enable(shift != numDWM - (W - 45) / 10);
	//pCmdUI->Enable(shift != pDoc->data.num - (W - 45) / 10);
}


void CStockViewer_0313130View::OnUpdateNext(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(shift != 0);
}


void CStockViewer_0313130View::OnUpdateFirst(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	CRect rect1;
	GetClientRect(rect1); // 視窗大小
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (period == 0)
	{
		numDWM = pDoc->data.num;
	}
	else if (period == 1)
	{
		if (pDoc->data.num % 5 != 0)
			numDWM = pDoc->data.num / 5 + 1;
		else
			numDWM = pDoc->data.num / 5;
	}
	else
	{
		if (pDoc->data.num % 20 != 0)
			numDWM = pDoc->data.num / 20 + 1;
		else
			numDWM = pDoc->data.num / 20;
	}
	pCmdUI->Enable(shift != numDWM - (W - 45) / 10);
	//pCmdUI->Enable(shift != pDoc->data.num - (W - 45) / 10);
}


void CStockViewer_0313130View::OnUpdateLast(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(shift != 0);
}


void CStockViewer_0313130View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt = point;
	CView::OnLButtonDown(nFlags, point);
}


void CStockViewer_0313130View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	// 舊版本
	/*
	shift = shift + (point.x - pt.x) / 10;
	pt.x = -1;
	if (shift < 0)
		shift = 0;
	CRect rect1;
	GetClientRect(rect1);
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (shift > pDoc->data.num - (W - 45) / 10)
		shift = pDoc->data.num - (W - 45) / 10;
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
	*/
	// 新版本
	pt = NULL;
	CView::OnLButtonUp(nFlags, point);
}


void CStockViewer_0313130View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt2 = point;
	// 舊版本
	/*
	Invalidate(false);
	CView::OnMouseMove(nFlags, point);
	*/	
	CRect rect1;
	GetClientRect(rect1);
	int W = rect1.Width();
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;	
	if (pt.x != NULL)
	{
		if (point.x - pt.x < 0)
		{
			shift--;
		}
		else
		{
			shift++;
		}
		if (shift < 0)
		{
			shift = 0;
		}
		if (shift > pDoc->data.num - (W - 45) / 10)
		{
			shift = pDoc->data.num - (W - 45) / 10;
		}
		pt = point;
	}
	Invalidate(false);
	CView::OnMouseMove(nFlags, point);
}


void CStockViewer_0313130View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	switch (nChar)
	{
		case VK_LEFT: //方向左鍵
			OnPrevious();
			break;
		case VK_RIGHT: //方向右鍵
			OnNext();
			break;
		case VK_HOME: //Home鍵
			OnFirst();
			break;
		case VK_END: //End鍵
			OnLast();
			break;
		case VK_NUMPAD0: //數字0鍵
			OnNone();
			break;
		case VK_NUMPAD1: //數字1鍵
			OnKd();
			break;
		case VK_NUMPAD2: //數字2鍵
			OnMacd();
			break;
		case VK_F1: //F1鍵
			OnDay();
			break;
		case VK_F2: //F2鍵
			OnWeek();
			break;
		case VK_F3: //F3鍵
			OnMonth();
			break;
		case VK_F4: //F3鍵
			OnWhite();
			break;
		case VK_F5: //F3鍵
			OnBlack();
			break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStockViewer_0313130View::OnNone()
{
	// TODO:  在此加入您的命令處理常式程式碼
	techindex = 0;
	Invalidate(false); // 05/10 新增
}


void CStockViewer_0313130View::OnKd()
{
	// TODO:  在此加入您的命令處理常式程式碼
	if (techindex == 1)
	{
		techindex = 0;
	}
	else
	{
		techindex = 1;
	}
	Invalidate(false); // 05/10 新增
}


void CStockViewer_0313130View::OnMacd()
{
	// TODO:  在此加入您的命令處理常式程式碼
	if (techindex == 2)
	{
		techindex = 0;
	}
	else
	{
		techindex = 2;
	}
	Invalidate(false); // 05/10 新增
}


void CStockViewer_0313130View::OnUpdateNone(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(techindex != 0); // 05/10 新增
}


void CStockViewer_0313130View::OnUpdateKd(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(techindex != 1 ); // 05/10 新增
}


void CStockViewer_0313130View::OnUpdateMacd(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(techindex != 2); // 05/10 新增
}

/*
int ptperiod;
int currentshift;
if (shift != 0)
{
ptperiod = period;
if (ptperiod != period)
{
if (ptperiod == 1)
currentshift = shift * 5;
if (ptperiod == 2)
currentshift = shift * 20;
if (ptperiod == 0)
currentshift = shift;
if (period == 0)
shift = currentshift;
if (period == 1)
{
if (currentshift % 5 != 0)
shift = currentshift / 5 + 1;
else
shift = currentshift / 5;
}
if (period == 2)
{
if (currentshift % 20 != 0)
shift = currentshift / 20 + 1;
else
shift = currentshift / 20;
}
}
}
*/

void CStockViewer_0313130View::OnDay()
{
	// TODO:  在此加入您的命令處理常式程式碼
	//日週月線轉換
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (shift != 0)
	{
		ptperiod = period;
		if (ptperiod != 0)
		{
			if (ptperiod == 1)
				if (pDoc->data.num % 5 != 0)
					currentshift = shift * 5 + pDoc->data.num % 5;
				else
					currentshift = shift * 5;
			if (ptperiod == 2)
				if (pDoc->data.num % 20 != 0)
					currentshift = shift * 20 + pDoc->data.num % 20;
				else
					currentshift = shift * 20;
			shift = currentshift;
		}
	}
	//日週月線轉換 code結束
	period = 0;
	Invalidate(false); // 05/10 新增
}


void CStockViewer_0313130View::OnWeek()
{
	// TODO:  在此加入您的命令處理常式程式碼
	//日週月線轉換
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (shift != 0)
	{
		ptperiod = period;
		if (ptperiod != 1)
		{
			if (ptperiod == 2)
				if (pDoc->data.num % 20 != 0)
					currentshift = shift * 20 + pDoc->data.num % 20;
				else
					currentshift = shift * 20;
			if (ptperiod == 0)
				currentshift = shift;
			shift = currentshift / 5;
		}
		if (period == 1)
		{
			if (pDoc->data.num % 5 != 0)
				currentshift = shift * 5 + pDoc->data.num % 5;
			else
				currentshift = shift * 5;
			shift = currentshift;
		}
	}
	//日週月線轉換 code結束
	if (period == 1)
	{
		period = 0;
	}
	else
	{
		period = 1;
	}
	Invalidate(false); // 05/20 新增
}


void CStockViewer_0313130View::OnMonth()
{
	// TODO:  在此加入您的命令處理常式程式碼
	//日週月線轉換
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (shift != 0)
	{
		ptperiod = period;
		if (ptperiod != 2)
		{
			if (ptperiod == 1)
				if (pDoc->data.num % 5 != 0)
					currentshift = shift * 5 + pDoc->data.num % 5;
				else
					currentshift = shift * 5;
			if (ptperiod == 0)
				currentshift = shift;
			shift = currentshift / 20;
		}
		if (ptperiod == 2)
		{
			if (pDoc->data.num % 20 != 0)
				currentshift = shift * 20 + pDoc->data.num % 20;
			else
				currentshift = shift * 20;
			shift = currentshift;
		}
	}
	//日週月線轉換 code結束
	if (period == 2)
	{
		period = 0;
	}
	else
	{
		period = 2;
	}
	Invalidate(false); // 05/20 新增
}


void CStockViewer_0313130View::OnUpdateDay(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(period != 0); // 05/20 新增
}


void CStockViewer_0313130View::OnUpdateWeek(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(period != 1); // 05/20 新增
}


void CStockViewer_0313130View::OnUpdateMonth(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(period != 2); // 05/20 新增
}


void CStockViewer_0313130View::OnWhite()
{
	// TODO:  在此加入您的命令處理常式程式碼
	color = 1;
	Invalidate(false);
}


void CStockViewer_0313130View::OnBlack()
{
	// TODO:  在此加入您的命令處理常式程式碼
	if (color == 2)
	{
		color = 1;
	}
	else
	{
		color = 2;
	}
	Invalidate(false);
}


void CStockViewer_0313130View::OnUpdateWhite(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(color != 1);
}


void CStockViewer_0313130View::OnUpdateBlack(CCmdUI *pCmdUI)
{
	// TODO:  在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->Enable(color != 2);
}
