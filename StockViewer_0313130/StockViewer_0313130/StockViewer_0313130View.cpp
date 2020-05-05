
// StockViewer_0313130View.cpp : CStockViewer_0313130View ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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
	// �зǦC�L�R�O
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

// CStockViewer_0313130View �غc/�Ѻc

CStockViewer_0313130View::CStockViewer_0313130View()
{
	// TODO:  �b���[�J�غc�{���X
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
	// TODO:  �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CStockViewer_0313130View �yø

void CStockViewer_0313130View::OnDraw(CDC* pDC)
{
	CStockViewer_0313130Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int cshift, cdraw1, cdraw2;
	if (!pDoc)
		return;
		
	CRect rect1;
	GetClientRect(rect1); // �����j�p
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
	if (shift > pDoc->data.num - (W - 45) / 10) //  �µ����i��ܪ���ƶq < �s�����i��ܪ���ƶq
	{
		shift = pDoc->data.num - (W - 45) / 10; // �s���� shift�Ƽg�� �s�����i��ܪ���ƶq
	}
	*/
	pDoc->data.Draw(pDC, H, W, shift, pt2, techindex, period, color); // �e��

	// TODO:  �b���[�J��͸�ƪ��yø�{���X
}


// CStockViewer_0313130View �C�L

BOOL CStockViewer_0313130View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CStockViewer_0313130View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  �[�J�C�L�e�B�~����l�]�w
}

void CStockViewer_0313130View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  �[�J�C�L�᪺�M���{���X
}


// CStockViewer_0313130View �E�_

#ifdef _DEBUG
void CStockViewer_0313130View::AssertValid() const
{
	CView::AssertValid();
}

void CStockViewer_0313130View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockViewer_0313130Doc* CStockViewer_0313130View::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockViewer_0313130Doc)));
	return (CStockViewer_0313130Doc*)m_pDocument;
}
#endif //_DEBUG


// CStockViewer_0313130View �T���B�z�`��


void CStockViewer_0313130View::OnPrevious()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	CRect rect1;
	GetClientRect(rect1); // �����j�p
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
	Invalidate(false); // 04/27 �s�W false
}


void CStockViewer_0313130View::OnNext()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	// �ª���
	
	shift--;
	
	if (shift < 0)
		shift = 0;
	Invalidate(false); // 04/27 �s�W false
}


void CStockViewer_0313130View::OnFirst()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X

	CRect rect1;
	GetClientRect(rect1); // �����j�p //GetUpdateRect(rect1);
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
	Invalidate(false); // 04/27 �s�W false
}


void CStockViewer_0313130View::OnLast()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	shift = 0;
	Invalidate(false); // 04/27 �s�W false
}


void CStockViewer_0313130View::OnUpdatePrevious(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	CRect rect1;
	GetClientRect(rect1); // �����j�p
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
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(shift != 0);
}


void CStockViewer_0313130View::OnUpdateFirst(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	CRect rect1;
	GetClientRect(rect1); // �����j�p
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
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(shift != 0);
}


void CStockViewer_0313130View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	pt = point;
	CView::OnLButtonDown(nFlags, point);
}


void CStockViewer_0313130View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	// �ª���
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
	// �s����
	pt = NULL;
	CView::OnLButtonUp(nFlags, point);
}


void CStockViewer_0313130View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	pt2 = point;
	// �ª���
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
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	switch (nChar)
	{
		case VK_LEFT: //��V����
			OnPrevious();
			break;
		case VK_RIGHT: //��V�k��
			OnNext();
			break;
		case VK_HOME: //Home��
			OnFirst();
			break;
		case VK_END: //End��
			OnLast();
			break;
		case VK_NUMPAD0: //�Ʀr0��
			OnNone();
			break;
		case VK_NUMPAD1: //�Ʀr1��
			OnKd();
			break;
		case VK_NUMPAD2: //�Ʀr2��
			OnMacd();
			break;
		case VK_F1: //F1��
			OnDay();
			break;
		case VK_F2: //F2��
			OnWeek();
			break;
		case VK_F3: //F3��
			OnMonth();
			break;
		case VK_F4: //F3��
			OnWhite();
			break;
		case VK_F5: //F3��
			OnBlack();
			break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStockViewer_0313130View::OnNone()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	techindex = 0;
	Invalidate(false); // 05/10 �s�W
}


void CStockViewer_0313130View::OnKd()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	if (techindex == 1)
	{
		techindex = 0;
	}
	else
	{
		techindex = 1;
	}
	Invalidate(false); // 05/10 �s�W
}


void CStockViewer_0313130View::OnMacd()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	if (techindex == 2)
	{
		techindex = 0;
	}
	else
	{
		techindex = 2;
	}
	Invalidate(false); // 05/10 �s�W
}


void CStockViewer_0313130View::OnUpdateNone(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(techindex != 0); // 05/10 �s�W
}


void CStockViewer_0313130View::OnUpdateKd(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(techindex != 1 ); // 05/10 �s�W
}


void CStockViewer_0313130View::OnUpdateMacd(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(techindex != 2); // 05/10 �s�W
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
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	//��g��u�ഫ
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
	//��g��u�ഫ code����
	period = 0;
	Invalidate(false); // 05/10 �s�W
}


void CStockViewer_0313130View::OnWeek()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	//��g��u�ഫ
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
	//��g��u�ഫ code����
	if (period == 1)
	{
		period = 0;
	}
	else
	{
		period = 1;
	}
	Invalidate(false); // 05/20 �s�W
}


void CStockViewer_0313130View::OnMonth()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	//��g��u�ഫ
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
	//��g��u�ഫ code����
	if (period == 2)
	{
		period = 0;
	}
	else
	{
		period = 2;
	}
	Invalidate(false); // 05/20 �s�W
}


void CStockViewer_0313130View::OnUpdateDay(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(period != 0); // 05/20 �s�W
}


void CStockViewer_0313130View::OnUpdateWeek(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(period != 1); // 05/20 �s�W
}


void CStockViewer_0313130View::OnUpdateMonth(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(period != 2); // 05/20 �s�W
}


void CStockViewer_0313130View::OnWhite()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
	color = 1;
	Invalidate(false);
}


void CStockViewer_0313130View::OnBlack()
{
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
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
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(color != 1);
}


void CStockViewer_0313130View::OnUpdateBlack(CCmdUI *pCmdUI)
{
	// TODO:  �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->Enable(color != 2);
}
